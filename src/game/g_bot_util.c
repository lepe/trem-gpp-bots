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
    return (int)(rand() % (start - end)) + end;
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
 * @return float (angle)
 */
int botGetAngleBetweenPlayer( gentity_t *self, gentity_t *player ) {
	return abs(SHORT2ANGLE(self->client->ps.delta_angles[ YAW ]) - SHORT2ANGLE(player->client->ps.delta_angles[ YAW ]));
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

	if( target->s.eType != ET_BUILDABLE ) {	//LEPE: except when are buildables 
	    dirToTarget[0] += self->bot->profile.skill * sin( self->client->time1000 );
	    dirToTarget[1] += self->bot->profile.skill * cos( self->client->time1000 );
	} 

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
        else { // don't do anything
			BotStand( self );
        }
	}
	return qtrue;
}

/**
 * Find closest enemy
 * @param self [gentity_t] a BOT
 * @return boolean (true if Enemy found)
 * //TODO: convert this function to use prioritization
 */
qboolean botFindClosestEnemy( gentity_t *self ) {
	int vectorRange = MGTURRET_RANGE * 3; //TODO: convert this to bot range
	int i;
	int total_entities;
	int entityList[ MAX_GENTITIES ];
	int distance;
	int closerTargetDistance = g_human_range.integer;
	qboolean targetFound = qfalse;
	gentity_t *closerTarget;
	vec3_t    range;
	vec3_t    mins, maxs;
	gentity_t *target;

	VectorSet( range, vectorRange, vectorRange, vectorRange );
	VectorAdd( self->client->ps.origin, range, maxs );
	VectorSubtract( self->client->ps.origin, range, mins );

	total_entities = trap_EntitiesInBox( mins, maxs, entityList, MAX_GENTITIES );

	for( i = 0; i < total_entities; i++ ) {
		target = &g_entities[ entityList[ i ] ];
		//Search for any enemy entity (player or structure)
		if( (target->client && target->client->ps.stats[ STAT_TEAM ] != self->client->ps.stats[ STAT_TEAM ]) ||
			((target->s.eType == ET_BUILDABLE && target->buildableTeam != self->client->ps.stats[ STAT_TEAM ]) && target->powered) ) 
		{
			distance = botGetDistanceBetweenPlayer(self, target);
			if( distance < closerTargetDistance && G_Visible(self, target, CONTENTS_SOLID) ) {
				closerTargetDistance = distance;
				closerTarget = target;
				//G_Printf("Found target at distance: %d\n",distance);
				targetFound = qtrue;
				//if(!LevelThinking( self, THINK_LEVEL_1 )) return qtrue; //in case the bot is impulsive, will stop here
			}
		}
	}
	if(targetFound) {
		self->bot->Enemy = closerTarget;
	} else {
		self->bot->Enemy = NULL;
	}
	//who is attacking you?
	//who is closer?
	//if(!LevelThinking( self, THINK_LEVEL_3 )) return qtrue; //in case the bot is cautious
	//self->bot->funcs.Target( self );
	return targetFound; 
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
				while(leader->bot->Friend && max < 20) {
					leader = leader->bot->Friend;
					max++;
				}
				if(leader != self) {
					self->bot->Friend = leader;
					leader->bot->Friend = NULL; //be sure he is not following anyone
					G_BotDebug(self, BOT_VERB_DETAIL, BOT_DEBUG_UTIL,"following %s\n", leader->client->pers.netname);
				}
				return qtrue;
			}
		}
	}
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
gentity_t *botFindDamagedStructure( gentity_t *self, float r ) 
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
	
    if( ent->health < BG_Buildable( ent->s.modelindex )->health && !( ent->s.eFlags & EF_DEAD ) && ent->spawned )
      return ent;
  }

  return NULL;
}
