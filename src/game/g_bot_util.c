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

/**
 * Check if target is in attack/shoot range to the BOT
 * @param self [gentity_t] a BOT
 * @param target [gentity_t] buildable, player or bot
 * @return boolean
 * 
 * TODO: split this code into human/alien?
 */
qboolean botTargetInRange( gentity_t *self, gentity_t *target ) {
	trace_t   trace;
	gentity_t *traceEnt;
	vec3_t  forward, right, up;
	vec3_t  muzzle;
	AngleVectors( self->client->ps.viewangles, forward, right, up );
	CalcMuzzlePoint( self, forward, right, up, muzzle );

	if( !self || !target )
		return qfalse;

	if( target->health <= 0 )
		return qfalse;
	
	if( self->client->ps.stats[ STAT_TEAM ] == TEAM_ALIENS &&
		 self->client->ps.stats[ STAT_CLASS ] != PCL_ALIEN_LEVEL3_UPG &&
		 self->client->ps.stats[ STAT_CLASS ] != PCL_ALIEN_LEVEL3 &&
		 target->s.pos.trBase[2] - self->s.pos.trBase[2] > 150)
		return qfalse;
	if(self->client->ps.weapon == WP_PAIN_SAW && 
		target->s.pos.trBase[2] - self->s.pos.trBase[2] > 150)
	{
		return qfalse;
	}
	else if(self->client->ps.weapon == WP_FLAMER && 
		target->s.pos.trBase[2] - self->s.pos.trBase[2] > 200)
	{
		return qfalse;
	}
	if(self->client->ps.stats[ STAT_TEAM ] == TEAM_ALIENS)
	{
		if(self->client->ps.stats[ STAT_CLASS ] == PCL_ALIEN_LEVEL4 && 
			Distance( self->s.pos.trBase, target->s.pos.trBase ) > g_level4_range.integer)
		{return qfalse;}
		else if(self->client->ps.stats[ STAT_CLASS ] == PCL_ALIEN_LEVEL3_UPG && 
			Distance( self->s.pos.trBase, target->s.pos.trBase ) > g_level3UPG_range.integer)
		{return qfalse;}
		else if(self->client->ps.stats[ STAT_CLASS ] == PCL_ALIEN_LEVEL3 && 
			Distance( self->s.pos.trBase, target->s.pos.trBase ) > g_level3_range.integer)
		{return qfalse;}
		else if(self->client->ps.stats[ STAT_CLASS ] == PCL_ALIEN_LEVEL2_UPG && 
			Distance( self->s.pos.trBase, target->s.pos.trBase ) > g_level2UPG_range.integer)
		{return qfalse;}
		else if(self->client->ps.stats[ STAT_CLASS ] == PCL_ALIEN_LEVEL2 && 
			Distance( self->s.pos.trBase, target->s.pos.trBase ) > g_level2_range.integer)
		{return qfalse;}
		else if(self->client->ps.stats[ STAT_CLASS ] == PCL_ALIEN_LEVEL1_UPG && 
			Distance( self->s.pos.trBase, target->s.pos.trBase ) > g_level1UPG_range.integer)
		{return qfalse;}
		else if(self->client->ps.stats[ STAT_CLASS ] == PCL_ALIEN_LEVEL1 && 
			Distance( self->s.pos.trBase, target->s.pos.trBase ) > g_level1_range.integer)
		{return qfalse;}
		else if(self->client->ps.stats[ STAT_CLASS ] == PCL_ALIEN_LEVEL0 && 
			Distance( self->s.pos.trBase, target->s.pos.trBase ) > g_level0_range.integer)
		{return qfalse;}
		else if(self->client->ps.stats[ STAT_CLASS ] == PCL_ALIEN_BUILDER0 && 
			Distance( self->s.pos.trBase, target->s.pos.trBase ) > 100)
		{return qfalse;}
		else if(self->client->ps.stats[ STAT_CLASS ] == PCL_ALIEN_BUILDER0_UPG && 
			Distance( self->s.pos.trBase, target->s.pos.trBase ) > 200)
		{return qfalse;}
	}
	else if((self->client->ps.stats[ STAT_CLASS ] == PCL_HUMAN || 
		self->client->ps.stats[ STAT_CLASS ] == PCL_HUMAN_BSUIT ) && 
		Distance( self->s.pos.trBase, target->s.pos.trBase ) > g_human_range.integer)
	{return qfalse;}
	else
	{
		if(Distance( self->s.pos.trBase, target->s.pos.trBase ) > 3000)
		{return qfalse;}
	}
	//BG_FindViewheightForClass(  self->client->ps.stats[ STAT_CLASS ], &vh, NULL );
	//top[2]=vh;
	//VectorAdd( self->s.pos.trBase, top, top);
	//draw line between us and the target and see what we hit
	//trap_Trace( &trace, self->s.pos.trBase, NULL, NULL, target->s.pos.trBase, self->s.number, MASK_SHOT );

	trap_Trace( &trace, muzzle, NULL, NULL, target->s.pos.trBase, self->s.number, MASK_SHOT );
	traceEnt = &g_entities[ trace.entityNum ];
    //if( trace.fraction < 1.0 )
    //{return qfalse;}
    // check that we hit a human and not an object
    //if( !traceEnt->client )
    // return qfalse;

    //check our target is in LOS
    if(!(traceEnt == target))
            return qfalse;

	return qtrue;
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

/*
 * Bot AIM at target
 * Perform calculations on where to shoot / attack
 * @param self [gentity_t] a BOT
 * @param target [gentity_t] buildable, player or bot
 * @return boolean (always true)
 */
qboolean botAimAtTarget( gentity_t *self, gentity_t *target ) {
    int tooCloseDistance = 100; //LEPE
    int distance = 0;
	vec3_t dirToTarget, angleToTarget, highPoint, targetUp, targetStraight, realBase;

	// Calculate the point on top of model (head) (well, 15% lower).
	VectorCopy( target->s.pos.trBase, highPoint );
	highPoint[2] += target->r.maxs[2] * 0.85;

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

	//TODO: move this from here to g_bot_human.c
	if( target->s.eType == ET_BUILDABLE || target->s.eType == PCL_ALIEN_LEVEL4 ) {	//LEPE: Nades on buildings or tyrants
	    if(BG_InventoryContainsUpgrade(UP_GRENADE,self->client->ps.stats)) {
            G_BotDebug(BOT_VERB_DETAIL, BOT_DEBUG_UTIL + BOT_DEBUG_HUMAN + BOT_DEBUG_THINK, "NADE ACTIVATED!\n");
            BG_ActivateUpgrade(UP_GRENADE,self->client->ps.stats);
	    }
	}
	// Grab the angles to use with delta_angles
	vectoangles( dirToTarget, angleToTarget );
	self->client->ps.delta_angles[ 0 ] = ANGLE2SHORT( angleToTarget[ 0 ] );
	self->client->ps.delta_angles[ 1 ] = ANGLE2SHORT( angleToTarget[ 1 ] );
	//self->client->ps.delta_angles[ 2 ] = ANGLE2SHORT( angleToTarget[ 2 ] );

    //LEPE: added if... Humans keep jumping when they are too close of a buildable
    if(target->s.eType == ET_BUILDABLE) {
        distance = botGetDistanceBetweenPlayer(self, target);
        if(distance > tooCloseDistance)
            BotStand( self ); //do nothing (stand position)
        else if (self->client->ps.stats[ STAT_TEAM ] == TEAM_HUMANS) {
            BotCrouch( self ); //keep down
		}
    } else {
        if(angleToTarget[0] > -350 && angleToTarget[0] < -180) { // down
            if( self->client->ps.stats[ STAT_TEAM ] == TEAM_HUMANS ) {
            	BotCrouch( self ); //keep down
            }
        }
        else if(angleToTarget[0] < -6.0 && angleToTarget[0] > -180) { // up
				BotJump( self );
        }
        else { // don't do anything
			BotStand( self );
        }
    }

//	trap_SendServerCommand( -1, va( "print \"%f\n\"", angleToTarget[0]) );

	return qtrue;
}

/**
 * Find closest enemy
 * @param self [gentity_t] a BOT
 * @return boolean (true if Enemy found)
 * //TODO: convert this function to use prioritization and split aliens/humans
 */
qboolean botFindClosestEnemy( gentity_t *self ) {
	int vectorRange = MGTURRET_RANGE * 3; //TODO: convert this to bot range
	int i;
	int total_entities;
	int entityList[ MAX_GENTITIES ];
	/**
	int possibleTargets[ MAX_GENTITIES ]; //should we limit the number?
	int closerTarget;
	int closerTargetDistance;
	 */
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
			(target->s.eType == ET_BUILDABLE && target->buildableTeam != self->client->ps.stats[ STAT_TEAM ]) ) 
		{
			if( botTargetInRange( self, target ) ) {
				self->bot->Enemy = target;
				return qtrue;
				//if(!LevelThinking( self, THINK_LEVEL_1 )) return qtrue; //in case the bot is impulsive, will stop here
			}
		}
	}
	//who is attacking you?
	//who is closer?
	//if(!LevelThinking( self, THINK_LEVEL_3 )) return qtrue; //in case the bot is cautious
	//self->bot->funcs.Target( self );
	return qfalse; //TODO: return accordingly
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
			if(botTargetInRange( self, target ) ) {
				//Do not follow if its following
				leader = target;
				while(leader->bot->Friend && max < 20) {
					leader = leader->bot->Friend;
					max++;
				}
				if(leader != self) {
					self->bot->Friend = leader;
					leader->bot->Friend = NULL; //be sure he is not following anyone
					G_BotDebug(BOT_VERB_DETAIL, BOT_DEBUG_UTIL,"%s following %s\n", self->client->pers.netname, leader->client->pers.netname);
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
@param buildable [buildable_t] Buildable type
@param r [float] range to check
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

    if( ent->s.modelindex == buildable && !( ent->s.eFlags & EF_DEAD ) )
      return ent;
  }

  return NULL;
}
