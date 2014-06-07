/*
===========================================================================
Copyright (C) 2014 Alberto Lepe (aka GlobalWarming)
https://github.com/lepe/trem-gpp-bots

This file is part of Tremulous.

GPPBot module is based on pbot code ported to GPP by "Celestial_Rage" based
on 2007's Amine Haddad TremBot code --which is based on the original works
of vcxzet (lamebot3)--.

Tremulous is free software; you can redistribute it
and/or modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 2 of the License,
or (at your option) any later version.

Tremulous is distributed in the hope that it will be
useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Tremulous; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
===========================================================================
 * Forum: http://forum.acidtu.be
 * Contribuitors (in alphabetical order):
 * 	dGr8LookinSparky
 * 	Igneel
 * 	Pikachu
 * 	ViruS
*/

/* 
 * Auxiliary methods
 */

#include "g_local.h"

/**
 * Generates a number between 0-100
 * @return int
 */
int G_Rand( void ) {
    return (int)rand() % 101;
}
/**
 * Generates a number between 2 numbers
 * @return int
 */
int G_Rand_Range( int start, int end ) {
    return (int)(rand() % (end - start)) + start;
}

// ROTAX: really an int? what if it's too long? If it is, we are fuxed.
/**
 * Get Distance between player and target
 * @param self [gentity_t] a BOT
 * @param player [gentity_t] a buildable, player or bot
 * @return int
 */
int botGetDistanceBetweenPlayer( gentity_t *self, gentity_t *player ) {
	return (int)Distance( self->s.pos.trBase, player->s.pos.trBase );
}

/**
 * Get the difference between angles (bot and target).
 * If the target is facing to the same angle as the bot is, that should be 0
 * If the target is facing the bot, it should be 180
 * @param self [gentity_t] a BOT
 * @param player [gentity_t] a player or bot
 * @return int (angle)
 */
int botGetAngleBetweenPlayersView( gentity_t *self, gentity_t *player ) {
	if(!player->client) return 0;
	return abs(SHORT2ANGLE(self->client->ps.delta_angles[ YAW ]) - SHORT2ANGLE(player->client->ps.delta_angles[ YAW ]));
}

/**
 * Get the angle from bot position to a XY point (Z is ignored)
 * @param self [gentity_t] a BOT
 * @param player [gentity_t] a player or bot
 * @return int (angle)
 */
int botGetAngleToPoint( gentity_t *self, vec3_t point ) {
	vec3_t dirToTarget, angles;
	float angle;
	//Make a vector from trBase -> topoint  
	VectorSubtract(point, self->s.pos.trBase, dirToTarget);
	// Get the absolute angle of the new vector
	vectoangles( dirToTarget, angles );
	// Get the angle relative to bot's view
	angle = SHORT2ANGLE(self->client->ps.delta_angles[ YAW ]) - angles[ YAW ];
	// Convert angle to positive value
	if(angle < 0) angle += 360;
	return (int)angle;
}
/**
 * Get the angle from bot to target (in terms of where the bot is 
 * looking and where the target is located)  (Z is ignored)
 * @param self
 * @param target
 * @return int (angle)
 */
int botGetAngleToTarget( gentity_t *self, gentity_t *target ) {
	return botGetAngleToPoint( self , target->s.pos.trBase );
}

/*
 * Bot AIM at target
 * Perform calculations on where to shoot / attack
 * @param self [gentity_t] a BOT
 * @param target [gentity_t] buildable, player or bot
 * @return boolean (always true)
 */
qboolean botAimAtTarget( gentity_t *self, gentity_t *target, qboolean pitch ) {
	vec3_t dirToTarget, angleToTarget, highPoint, targetUp, targetStraight, realBase;
	int wobble;
	
	// Calculate the point on top of model (head) (well, 15% lower). 50% lower for humans
	VectorCopy( target->s.pos.trBase, highPoint );
	highPoint[2] += target->r.maxs[2] * (self->client->ps.stats[ STAT_TEAM ] == TEAM_HUMANS ? 0.50 : 0.85);

	// Make a vector from trBase -> highPoint
	VectorSubtract( highPoint, target->s.pos.trBase, targetUp );

	// Find the point where we actually shoot from
	VectorCopy( self->s.pos.trBase, realBase );
	realBase[2] += self->client->ps.viewheight;

	// Find the vector that points from our gun to his base
	VectorSubtract( target->s.pos.trBase, realBase, targetStraight );

	// Create our vector that points our gun to his face
	VectorAdd( targetStraight, targetUp, dirToTarget );

	wobble = (target->s.eType == ET_BUILDABLE ? 0 : BOT_WOBBLE);// + self->bot->var.angleToTarget;
	if(self->client->ps.eFlags & EF_POISONCLOUDED) {
		wobble += G_Rand();
	}
	dirToTarget[0] += (wobble * sin( self->client->time1000 ));
	dirToTarget[1] += (wobble * cos( self->client->time1000 ));

	// Grab the angles to use with delta_angles
	vectoangles( dirToTarget, angleToTarget );
	if(pitch) {
		//self->bot->move.lookat[ PITCH ] = ANGLE2SHORT( angleToTarget[ PITCH ] );
		self->client->ps.delta_angles[ PITCH ] = ANGLE2SHORT( angleToTarget[ PITCH ] );
	}
	self->client->ps.delta_angles[ YAW ] = ANGLE2SHORT( angleToTarget[ YAW ] );
	//self->bot->move.lookat[ YAW ] = ANGLE2SHORT( angleToTarget[ YAW ] );
	//self->client->ps.delta_angles[ ROLL ] = ANGLE2SHORT( angleToTarget[ ROLL ] );

    //LEPE: added if... Humans keep jumping when they are too close of a buildable
	//it was done here for simplification as angles are already calculated. However
	//this code should be moved to g_bot_human.c
	if(self->client->ps.stats[ STAT_TEAM ] == TEAM_HUMANS) {
        if(angleToTarget[0] > -350 && angleToTarget[0] < -180) { // down
            BotCrouch( self ); //keep down
        }
        else if(angleToTarget[0] < -6.0 && angleToTarget[0] > -180) { // up
			if(!G_Visible(self, target, CONTENTS_SOLID)) BotJump( self );
        }
	}
	return qtrue;
}
/**
 * Locate the closest node to an entity
 * @param self [gentity_t]
 * @return int (node id)
 */
int botFindClosestNode( gentity_t *self ) {
	trace_t trace;
	int i,distance,Ax,Ay,Az,Bx,By,Bz = 0;
	int closestpath = -1;
	int closestpathdistance = 2000;
	for(i = 0; i < level.numPaths; i++) //find a nearby node
	{
		trap_Trace( &trace, self->s.pos.trBase, NULL, NULL, level.paths[i].coord, self->s.number, MASK_SHOT );
		if( trace.fraction < 1.0 )
		{continue;}
		Ax = level.paths[i].coord[0];
		Ay = level.paths[i].coord[1];
		Az = level.paths[i].coord[2];
		Bx = self->s.pos.trBase[0];
		By = self->s.pos.trBase[1];
		Bz = self->s.pos.trBase[2];
		distance = sqrt((Ax - Bx)*(Ax - Bx) + (Ay - By)*(Ay - By) + (Az - Bz)*(Az - Bz));
        if(distance < closestpathdistance)
        {
            closestpath = i;
            closestpathdistance = distance;
        }
	}
	return closestpath;
}
/**
 * Found any path to rout
 * @param path
 * @param goal
 * @param start
 * @return 
 */
qboolean botFindPath( int *path , int goal, int start ) {
    int i, j, curr_node, next_node;
    qboolean exists;
    curr_node = path[ start-1 ];
    for(i = 0; i < 5; i++) {
        next_node = level.paths[ curr_node ].nextid[ i ];
        if(next_node > -1 && next_node < level.numPaths) {
            exists = qfalse;
            for(j = 0; j < BOT_FIND_PATH_MAX; j++) {
                if(next_node == path[ j ]) {
                    exists = qtrue;
                    break;
                }
            }
            if(!exists) {
                path[start] = next_node;
                if(next_node == goal) {
                    //clean unused values
                    for(j = start+1; j < BOT_FIND_PATH_MAX; j++) {
                        path[ j ] = -1;
                    }
                    return qtrue;
                } else if(start == BOT_FIND_PATH_MAX - 1) {
                    return qfalse;
                } else {
                    if(botFindPath( path , goal, start+1 )) {
                        return qtrue;
                    }
                }
            }
        } else {
            continue; //we don't break to allow "empty nodes" in the middle
        }
    }
    return qfalse;
}


/**
 * Find closest enemy
 * @param self [gentity_t] a BOT
 * @return boolean (true if Enemy found)
 */
int botFindEnemy( gentity_t *self, int maxRange ) {
	int i;
	int total_entities;
	int entityList[ MAX_GENTITIES ];
	int rank, rankdbg;
	int bestRank = 0;
	int bestTarget;
	qboolean targetFound = qfalse;
	vec3_t    range;
	vec3_t    mins, maxs;
	gentity_t *target;

	VectorSet( range, maxRange, maxRange, maxRange );
	VectorAdd( self->client->ps.origin, range, maxs );
	VectorSubtract( self->client->ps.origin, range, mins );

	total_entities = trap_EntitiesInBox( mins, maxs, entityList, MAX_GENTITIES );

	for( i = 0; i < total_entities; i++ ) {
		target = &g_entities[ entityList[ i ] ];
		if(target && target->inuse && target->health > 0 &&
		  (target->client || target->s.eType == ET_BUILDABLE) &&! botSameTeam(self, target))
		{
			//Perform common target calculations
			rank = self->bot->funcs.base.targetRank(self, target);
			rankdbg = rank;
			//Perform team based calculations (we pass rank to use it as base value)
			rank = self->bot->funcs.team.targetRank(self, target, rank);
			if(rank) increasePathEssence( self , target, (int)((float)rank / 10.0f) );
			if(rank > bestRank) {
				G_BotDebug(self, BOT_VERB_DETAIL, BOT_DEBUG_UTIL + BOT_DEBUG_TARGET, "%3i %4i %4i %5i %s\n",
						entityList[ i ],
						rankdbg,
						rank,
						botGetDistanceBetweenPlayer(self, target),
						target->client ? target->client->pers.netname : target->classname
						);
				bestRank = rank;
				targetFound = qtrue;
				bestTarget = entityList[ i ];
			}
		}
	}
	if(targetFound) {
		G_BotDebug(self, BOT_VERB_DETAIL, BOT_DEBUG_UTIL + BOT_DEBUG_TARGET, "Best Target: %d\n", bestTarget);
		return bestTarget;
	} else {
		return BOT_NO_ENEMY;
	}
}
/**
 * Find closest friend
 * @param self [gentity_t] a BOT
 * @return boolean (true if Friend found)
 * //TODO: apply chain or group concepts and leadership algorithm
 */
qboolean botFindClosestFriend( gentity_t *self ) {
	int vectorRange = MGTURRET_RANGE * 3; //TODO: convert this to bot range
	int i;
	int total_entities;
	int entityList[ MAX_GENTITIES ];
	vec3_t    range;
	vec3_t    mins, maxs;
	gentity_t *target;
	gentity_t *leader;
	int max = 0;
	
	VectorSet( range, vectorRange, vectorRange, vectorRange );
	VectorAdd( self->client->ps.origin, range, maxs );
	VectorSubtract( self->client->ps.origin, range, mins );

	total_entities = trap_EntitiesInBox( mins, maxs, entityList, MAX_GENTITIES );

	for( i = 0; i < total_entities; i++ ) {
		target = &g_entities[ entityList[ i ] ];
		//Search for any friend player
		if(target != self && target->client && target->client->ps.stats[ STAT_TEAM ] == self->client->ps.stats[ STAT_TEAM ] )
		{
			if( botGetDistanceBetweenPlayer(self, target) < 500 ) {
				//Do not follow if its following
				leader = target;
				if(leader->bot) {
					while(leader->bot && leader->bot->Friend && max < 20) {
						leader = leader->bot->Friend;
						max++;
					}
					if(leader != self) {
						self->bot->Friend = leader;
						if(leader->bot) {
							leader->bot->Friend = NULL; //be sure he is not following anyone
						}
						G_BotDebug(self, BOT_VERB_DETAIL, BOT_DEBUG_UTIL,"following %s\n", leader->client->pers.netname);
					}
					return qtrue;
				} else { //its a player... follow him
					self->bot->Friend = leader;
					return qtrue;
				}
			}
		}
	}
	self->bot->Friend = NULL; 
	return qfalse;
}

/*
================
Based on g_buildable.c : G_FindBuildable and G_BuildableRange
Finds a buildable of the specified type within range
@param self [gentity_t] BOT
@param r [float] range to check
@param buildable [buildable_t] Buildable type
================
*/
gentity_t *botFindClosestBuildable( gentity_t *self, float r, buildable_t buildable )
{
  int       entityList[ MAX_GENTITIES ];
  vec3_t    range;
  vec3_t    mins, maxs;
  int       i, num;
  gentity_t *ent;

  VectorSet( range, r, r, r );
  VectorAdd( self->client->ps.origin, range, maxs );
  VectorSubtract( self->client->ps.origin, range, mins );

  num = trap_EntitiesInBox( mins, maxs, entityList, MAX_GENTITIES );

  for( i = 0; i < num; i++ )
  {
    ent = &g_entities[ entityList[ i ] ];

    if( ent->s.eType != ET_BUILDABLE )
      continue;
	
    if( ent->buildableTeam == TEAM_HUMANS && !ent->powered )
      continue;
	
	if(!G_Visible(self, ent, CONTENTS_SOLID))
  	  continue;

    if( ent->s.modelindex == buildable && !( ent->s.eFlags & EF_DEAD ) )
      return ent;
  }

  return NULL;
}
/**
 * Find the closest Damaged structure (HUMANS)
 * //TODO: repair prioritization
	@param self [gentity_t] BOT
	@param r [float] range to check
 	@return gentity_t
 */
gentity_t *botFindDamagedStructure( gentity_t *self, float r, int damage ) 
{
  int       entityList[ MAX_GENTITIES ];
  vec3_t    range;
  vec3_t    mins, maxs;
  int       i, num;
  gentity_t *ent;

  VectorSet( range, r, r, r );
  VectorAdd( self->client->ps.origin, range, maxs );
  VectorSubtract( self->client->ps.origin, range, mins );

  num = trap_EntitiesInBox( mins, maxs, entityList, MAX_GENTITIES );

  for( i = 0; i < num; i++ )
  {
    ent = &g_entities[ entityList[ i ] ];

    if( ent->s.eType != ET_BUILDABLE )
      continue;
	
    if( ent->buildableTeam == TEAM_HUMANS && !ent->powered )
      continue;

	if(!G_Visible(self, ent, CONTENTS_SOLID))
  	  continue;
	
    if( botGetHealthPct( ent ) < damage && !( ent->s.eFlags & EF_DEAD ) && ent->spawned )
      return ent;
  }

  return NULL;
}

/**
 * This function return health as a percentage either for players or buildings
 * @param self
 * @return 
 */
int botGetHealthPct( gentity_t *ent ) 
{
	int health_pct;
	if(ent->s.eType == ET_BUILDABLE) {
		health_pct = (float)((float)ent->health / (float)BG_Buildable( ent->s.modelindex )->health) * 100;
 	} else {
		health_pct = (float)((float)ent->health / (float)BG_Class( ent->client->ps.stats[ STAT_CLASS ] )->health) * 100;
	}
	return health_pct;
}
/**
 * Similiar to OnSameTeam BUT it also include structures
 * @param ent
 * @param ent2
 * @return 
 */
qboolean botSameTeam( gentity_t *ent1, gentity_t *ent2 )
{
	qboolean same = qfalse;
	
	if(ent1->client && ent2->client) {
		same = (ent1->client->ps.stats[ STAT_TEAM ] == ent2->client->ps.stats[ STAT_TEAM ]);
	} else if(ent1->client && ent2->s.eType == ET_BUILDABLE) {
		same = (ent1->client->ps.stats[ STAT_TEAM ] == ent2->buildableTeam);
	} else if(ent2->client && ent1->s.eType == ET_BUILDABLE) {
		same = (ent2->client->ps.stats[ STAT_TEAM ] == ent1->buildableTeam);
	} else if(ent1->s.eType == ET_BUILDABLE && ent2->s.eType == ET_BUILDABLE) {
		same = (ent1->buildableTeam == ent1->buildableTeam);
	}
	
	return same;
}

/**
 * Check if bot is hitting a target within a period of time
 * @param self [gentity_t]
 * @param time [int] 
 */
qboolean botHitTarget( gentity_t *self, int time ) {
	qboolean hit;
	if(self->target_ent == self->bot->Enemy) {
		hit = (self->bot->Enemy->credits[ self->s.clientNum ] > self->bot->var.targetHits);
		if(hit) {
			self->bot->timer.hit = level.time;
		} else if(level.time - self->bot->timer.hit > time) {
			hit = qfalse;
		} else {
			hit = qtrue;
		}
	} else {
		return qfalse;
	}
	return hit;
}

/**
 * Reset hit counter
 * @param self
 */
void botResetHitTarget( gentity_t *self ) {
	self->bot->timer.hit = level.time; 
	if(self->bot->Enemy) {
		self->bot->var.targetHits = self->bot->Enemy->credits[ self->s.clientNum ];
	} else {
		self->bot->var.targetHits = 0;
	}
}
