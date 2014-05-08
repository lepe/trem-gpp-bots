/*
===========================================================================
Copyright (C) 2014 Alberto Lepe (aka GlobalWarming)
https://github.com/lepe/trem-gpp-bots

This file is part of Tremulous.

GPP-Bot module is based on PBOT code ported to GPP by "Celestial_Rage" 
(ROTAX?) based on 2007's Amine Haddad TremBot code --which is based on the 
original works of vcxzet (lamebot3)--.

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
 * Alien bot code
 */

#include "g_local.h"

void BotInitAlien( gentity_t *self ) {
	//Initialization of TEAM funtions
	self->bot->funcs.team.spec				= BotBeforeSpawnAlien;
	self->bot->funcs.team.target			= BotTargetAlien;
	self->bot->funcs.team.think				= BotAlienThink;
	//--- state functions
	self->bot->funcs.team.status[ATTACK]	= BotAttackAlien;
	self->bot->funcs.team.status[HEAL]		= BotHealAlien;
	self->bot->funcs.team.status[BUILD]		= BotBuildAlien;
	self->bot->funcs.team.status[IMPROVE]	= BotEvolve;
	//--- nav state functions
	self->bot->funcs.team.nav[TARGETPATH]	= BotNavigateAlien;
	self->bot->funcs.team.nav[BLOCKED]		= BotBlockedAlien;
	//default % of evolving
	self->bot->set.tyrant[S3] 		= 100;
	self->bot->set.adv_goon[S3]		= 100;
	self->bot->set.adv_goon[S2]		= 100;
	self->bot->set.goon[S3] 		= 100;
	self->bot->set.goon[S2] 		= 100;
	self->bot->set.goon[S1] 		= 100;
	self->bot->set.adv_marauder[S3]	= 100;
	self->bot->set.adv_marauder[S2]	= 100;
	self->bot->set.marauder[S3] 	= 100;
	self->bot->set.marauder[S2] 	= 100;
	self->bot->set.marauder[S1]		= 100;
	self->bot->set.adv_basilisk[S3]	= 100;
	self->bot->set.adv_basilisk[S2]	= 100;
	self->bot->set.basilisk[S3] 	= 100;
	self->bot->set.basilisk[S2] 	= 100;
	self->bot->set.basilisk[S1] 	= 100;
}
/**
 * Decide if spawn as dretch or granger
 * @param self
 * //TODO: add decision
 */
void BotBeforeSpawnAlien( gentity_t *self )
{
	int clientNum;
    clientNum = self->client->ps.clientNum;
	//is enemy near egg? YES -> dretch
	//are any building destroyed near egg? (need to keep record of initial builds) NO -> dretch
	//any granger near egg? YES -> dretch
    G_BotDebug(BOT_VERB_DETAIL, BOT_DEBUG_ALIEN + BOT_DEBUG_THINK, "Bot is about to spawn\n");
	self->client->pers.classSelection = PCL_ALIEN_LEVEL0;
	self->client->ps.stats[ STAT_CLASS ] = PCL_ALIEN_LEVEL0;
	G_PushSpawnQueue( &level.alienSpawnQueue, clientNum );
}
/**
 * Some decisions that may happen always. 
 * This function must only contain logic blocks (IF, SWITCH, etc) and
 * state suggestions.
 * The intention of this function is to suggest a state to bots
 * on different thinking levels based on current state.
 * DO NOT reset timers here or implement any action
 * @param self
 */
void BotAlienThink( gentity_t *self )
{
	//DRETCH: ignore structures that can't destroy
	if(self->bot->Enemy && self->client->pers.classSelection == PCL_ALIEN_LEVEL0) {
		if(self->bot->Enemy->spawned && self->bot->Enemy->s.eType == ET_BUILDABLE) {
			self->bot->Enemy = NULL;
			BotResetState( self, ATTACK );
		}
	}
	///////////////////////// LEVEL 1 /////////////////////////
	if(!BotKeepThinking( self , THINK_LEVEL_1)) return;

	//TODO: prevent aliens bots to evolve 2 or more times consecutively.
	if(self->bot->state != ATTACK && self->client->pers.credit >= ALIEN_CREDITS_PER_KILL && level.time - self->bot->timer.improve > 5000) {
		self->bot->think.state[ THINK_LEVEL_1 ] = IMPROVE;
	}
	
 	if(BotKeepThinking( self, THINK_LEVEL_3 )) { 
		if(!self->bot->Enemy) { 
			if(botFindClosestFriend( self )) {
				//self->bot->think.state[ THINK_LEVEL_3 ] = FOLLOW;
			}
		}
	}
	
}
/**
 * Special movement for aliens:
 * @param self
 */
void BotNavigateAlien( gentity_t *self )
{
	if( BG_ClassHasAbility( self->client->ps.stats[ STAT_CLASS ], SCA_WALLCLIMBER ) ) { //LEPE: if possible
		if(G_Rand() < 70) {
			BotWallWalk( self );
		} else {
			BotStand( self );
		}
	} else if(G_Rand() < 90 &&
			(self->client->pers.classSelection == PCL_ALIEN_LEVEL2 || 
			self->client->pers.classSelection == PCL_ALIEN_LEVEL2_UPG)) {
				BotJump( self );
	} else if((self->client->pers.classSelection == PCL_ALIEN_LEVEL3 && 
			  self->client->ps.stats[ STAT_MISC ] < LEVEL3_POUNCE_JUMP_MAG) || 
			 (self->client->pers.classSelection == PCL_ALIEN_LEVEL3_UPG && 
			  self->client->ps.stats[ STAT_MISC ] < LEVEL3_POUNCE_JUMP_MAG_UPG)) {
				BotRun( self );
				Bot_Pounce( self, 30 );
	} else if(self->client->pers.classSelection == PCL_ALIEN_LEVEL4) {
		BotSecAttack( self );
	}
}
/**
 * If an alien bot get's blocked...
 * alien will try to wallwalk if possible (and jump every X tries)
 * in the case it can not do wallwalk, it will try
 * to jump as much as possible. 
 * The bot will try to go either one way (left) or the other (right) with
 * some random behaviour.
 * @param self
 * //TODO: nav timer was changed so it is called several times more than before. we need to make the conditions
 *         fail proof anytime even if timers are adjusted
 */
void BotBlockedAlien( gentity_t *self )
{
	int try = self->bot->path.blocked_try;
	qboolean canwallwalk = ( BG_ClassHasAbility( self->client->ps.stats[ STAT_CLASS ], SCA_WALLCLIMBER ) );
	qboolean rand = G_Rand() < 50;
	
	if(canwallwalk) BotWallWalk( self ); //if possible

	G_BotDebug(BOT_VERB_DETAIL, BOT_DEBUG_ALIEN + BOT_DEBUG_NAVSTATE, "[ %d ] Trying to unblock. Rand: %d\n", try, rand );
	if(try <= 0) {
		BotMoveFwd( self );
		BotJump( self );
		VectorCopy(self->r.currentOrigin, self->bot->path.blocked_origin);
	} else if(try < BOT_TIMER_NAV_SECOND) {
		if(rand) BotControl( self, BOT_LOOK_RIGHT );
		if(!canwallwalk || try % BOT_TIMER_NAV_SECOND == 0) BotJump( self ); 
	} else if(try > BOT_TIMER_NAV_SECOND) {
		if(rand) BotControl( self, BOT_LOOK_LEFT );
		if(!canwallwalk || try % BOT_TIMER_NAV_SECOND == 0) BotJump( self );
	}
	
	if(try >= BOT_TIMER_NAV_SECOND * 4) {
		self->bot->path.blocked_try = 0; 
		G_BotDebug(BOT_VERB_DETAIL, BOT_DEBUG_ALIEN + BOT_DEBUG_NAVSTATE, "Reset blocked_try to 0\n" );
	} else {
		//we set next try 
		self->bot->path.blocked_try++;
	}	
}
/**
 * Evolve to a higher class
 * @param self [gentity_t] a BOT
 */
void BotEvolve( gentity_t *self )
{
	vec3_t origin;
	qboolean classfound = qfalse;
	class_t class = PCL_NONE;
	int levels;
	int clientNum;
	qboolean lowclass = qfalse;
	clientNum = self->client - level.clients;
	self->bot->timer.improve = level.time;
	if(G_Rand() < self->bot->set.tyrant[g_alienStage.integer] && classfound == qfalse && g_bot_tyrant.integer > 0)
	{
		class = PCL_ALIEN_LEVEL4;
 		levels = BG_ClassCanEvolveFromTo( self->client->pers.classSelection,
 						class,
 						self->client->pers.credit, g_alienStage.integer, 0 );
 		if(BG_ClassIsAllowed( class ) && 
 			 
 			G_Overmind( ) &&
 			G_RoomForClassChange( self, class, origin ) && 
 			!( self->client->ps.stats[ STAT_STATE ] & SS_WALLCLIMBING ) && 
 			 
 			levels >= 0)
 		{
 			classfound = qtrue;
 		}
		if( !BG_ClassIsAllowed( class ) )
      {
        classfound=qfalse;
      }

      if( !BG_ClassAllowedInStage( class, g_alienStage.integer ) )
      {
        classfound=qfalse;
      }
	if(classfound != qfalse)
	  classfound=qtrue;
	  
	}
	if(G_Rand() < self->bot->set.adv_goon[g_alienStage.integer] && classfound == qfalse && g_bot_advgoon.integer > 0)
	{
		class = PCL_ALIEN_LEVEL3_UPG;
		levels = BG_ClassCanEvolveFromTo( self->client->pers.classSelection,
						class,
						self->client->pers.credit,
                                      g_alienStage.integer, 0 );
		if(BG_ClassIsAllowed( class ) && 
			 
			G_Overmind( ) &&
			G_RoomForClassChange( self, class, origin ) && 
			!( self->client->ps.stats[ STAT_STATE ] & SS_WALLCLIMBING ) && 
			 
			levels >= 0)
		{
			classfound = qtrue;
		}
				if( !BG_ClassIsAllowed( class ) )
      {
        classfound=qfalse;
      }

      if( !BG_ClassAllowedInStage( class, g_alienStage.integer ) )
      {
        classfound=qfalse;
      }
	if(classfound != qfalse)
	  classfound=qtrue;
	}
	if(G_Rand() < self->bot->set.adv_marauder[g_alienStage.integer] && classfound == qfalse && g_bot_advmara.integer > 0)
	{
		class = PCL_ALIEN_LEVEL2_UPG;
 		levels = BG_ClassCanEvolveFromTo( self->client->pers.classSelection,
 						class,
 						self->client->pers.credit,
                                      g_alienStage.integer, 0 );
 		if(BG_ClassIsAllowed( class ) && 
 			 
 			G_Overmind( ) &&
 			G_RoomForClassChange( self, class, origin ) && 
 			!( self->client->ps.stats[ STAT_STATE ] & SS_WALLCLIMBING ) && 
 			levels >= 0)
 		{
 			classfound = qtrue;
 		}
				if( !BG_ClassIsAllowed( class ) )
      {
        classfound=qfalse;
      }

      if( !BG_ClassAllowedInStage( class, g_alienStage.integer ) )
      {
        classfound=qfalse;
      }
	if(classfound != qfalse)
	  classfound=qtrue;
	}
	if(G_Rand() < self->bot->set.marauder[g_alienStage.integer] && classfound == qfalse && g_bot_mara.integer > 0)
	{
		class = PCL_ALIEN_LEVEL2;
 		levels = BG_ClassCanEvolveFromTo( self->client->pers.classSelection,
 						class,
 						self->client->pers.credit,
                                      g_alienStage.integer, 0 );
 		if(BG_ClassIsAllowed( class ) && 
 			 
 			G_Overmind( ) &&
 			G_RoomForClassChange( self, class, origin ) && 
 			!( self->client->ps.stats[ STAT_STATE ] & SS_WALLCLIMBING ) && 
 			levels >= 0)
 		{
 			classfound = qtrue;
 		}
				if( !BG_ClassIsAllowed( class ) )
      {
        classfound=qfalse;
      }

      if( !BG_ClassAllowedInStage( class, g_alienStage.integer ) )
      {
        classfound=qfalse;
      }
	if(classfound != qfalse)
	  classfound=qtrue;
	}
	if(G_Rand() < self->bot->set.adv_basilisk[g_alienStage.integer] && classfound == qfalse && g_bot_advbasi.integer > 0)
	{
		class = PCL_ALIEN_LEVEL1_UPG;
 		levels = BG_ClassCanEvolveFromTo( self->client->pers.classSelection,
 						class,
 						self->client->pers.credit,
                                      g_alienStage.integer, 0 );
 		if(BG_ClassIsAllowed( class ) && 
 			 
 			G_Overmind( ) &&
 			G_RoomForClassChange( self, class, origin ) && 
 			!( self->client->ps.stats[ STAT_STATE ] & SS_WALLCLIMBING ) && 
 			 
 			levels >= 0)
 		{
 			classfound = qtrue;
 		}
	}
	if(G_Rand() < self->bot->set.goon[g_alienStage.integer] && classfound == qfalse && g_bot_goon.integer > 0)
	{
		class = PCL_ALIEN_LEVEL3;
 		levels = BG_ClassCanEvolveFromTo( self->client->pers.classSelection,
 						class,
 						self->client->pers.credit,
                                      g_alienStage.integer, 0 );
 		if(BG_ClassIsAllowed( class ) && 
 			 
 			G_Overmind( ) &&
 			G_RoomForClassChange( self, class, origin ) && 
 			!( self->client->ps.stats[ STAT_STATE ] & SS_WALLCLIMBING ) && 
 			 
 			levels >= 0)
 		{
 			classfound = qtrue;
 		}
				if( !BG_ClassIsAllowed( class ) )
      {
        classfound=qfalse;
      }

      if( !BG_ClassAllowedInStage( class, g_alienStage.integer ) )
      {
        classfound=qfalse;
      }
	if(classfound != qfalse)
	  classfound=qtrue;
	}
	if(G_Rand() < self->bot->set.basilisk[g_alienStage.integer] && classfound == qfalse && g_bot_basi.integer > 0)
	{
		class = PCL_ALIEN_LEVEL1;
 		levels = BG_ClassCanEvolveFromTo( self->client->pers.classSelection,
 						class,
 						self->client->pers.credit,
                                      g_alienStage.integer, 0 );
 		if(BG_ClassIsAllowed( class ) && 
 			 
 			G_Overmind( ) &&
 			G_RoomForClassChange( self, class, origin ) && 
 			!( self->client->ps.stats[ STAT_STATE ] & SS_WALLCLIMBING ) && 
 			 
 			levels >= 0)
 		{
 			classfound = qtrue;
 		}
				if( !BG_ClassIsAllowed( class ) )
      {
        classfound=qfalse;
      }

      if( !BG_ClassAllowedInStage( class, g_alienStage.integer ) )
      {
        classfound=qfalse;
      }
	if(classfound != qfalse)
	  classfound=qtrue;
	}
	if(classfound == qtrue)
	{
		if(class == PCL_NONE || class == PCL_HUMAN || class == PCL_HUMAN_BSUIT){return;}
		self->client->pers.evolveHealthFraction = (float)self->client->ps.stats[ STAT_HEALTH ] /
		(float)BG_Class( self->client->ps.stats[ STAT_CLASS ] )->health;
		if( self->client->pers.evolveHealthFraction < 0.0f )
			self->client->pers.evolveHealthFraction = 0.0f;
		else if( self->client->pers.evolveHealthFraction > 1.0f )
			self->client->pers.evolveHealthFraction = 1.0f;
		if(lowclass == qfalse){G_AddCreditToClient( self->client, -(short)levels, qtrue );}
		self->client->pers.classSelection = class;
		ClientUserinfoChanged( clientNum, qfalse );
		VectorCopy( origin, self->s.pos.trBase );
		ClientSpawn( self, self, self->s.pos.trBase, self->s.apos.trBase );	
		self->bot->timer.improve = level.time;
		self->client->pers.cmd.buttons = 0;
		self->client->pers.cmd.upmove = 0;
		self->client->pers.cmd.rightmove = 0;
		return;
	}
	self->bot->timer.improve = level.time;
	BotResetState( self, IMPROVE );
	return;
}
/**
 * Attack to target if its in range 
 * @param self [gentity_t] a BOT
 * @param target [gentity_t] a buildable, player or bot
 */
void BotAttackAlien( gentity_t *self )
{
	int closeDistance = LEVEL2_AREAZAP_RANGE; 
	int veryCloseDistance = LEVEL4_CLAW_RANGE; 
	int tempEntityIndex = -1;
	int rand = 0;
	int distance = botGetDistanceBetweenPlayer(self, self->bot->Enemy);
	int anglediff = 0;
	//TODO: move this code to target prioritization
	//Use: g_utils.c : G_ClosestEnt(  ) to get the closest entities around ?
	
	if(distance > closeDistance) { //LEPE: if is far, search for a closer target
		// try to find closest enemy
		tempEntityIndex = botFindClosestEnemy(self);
		if(tempEntityIndex >= 0) {
			self->bot->Enemy = &g_entities[tempEntityIndex];
			distance = botGetDistanceBetweenPlayer(self, self->bot->Enemy);
		}
	}
	//If we are closer than what humans can reach to us
	if(distance < g_human_range.integer)
	{
			rand = G_Rand();
				
			BotWallWalk( self ); // enable wallwalk if possible
			
			BotRun( self );
			//If we are not close enough and the target is a bot or a player, strafe
			//TODO: we could apply bot difficulty here. Like, easy bots will not strafe
			if(distance > veryCloseDistance && self->bot->Enemy->s.eType == ET_PLAYER) {
				Bot_Strafe( self );
			} else {
				//TODO: test it
				BotClearQueue( self ); //remove queued movements (probably Strafe), as we are too close
			}

			self->client->pers.cmd.buttons = 0;
			if (self->client->pers.classSelection == PCL_ALIEN_BUILDER0)
			{
				if (distance <= LEVEL0_BITE_RANGE) {
 					BotSecAttack( self );
				} else {
					BotGesture( self );
				}
			}
			else if (self->client->pers.classSelection == PCL_ALIEN_BUILDER0_UPG)//adv granger
			{
				if (distance <= LEVEL0_BITE_RANGE) {
 					BotSecAttack( self );
				} else {
					BotMidAttack( self );
				}
			}
			else if (self->client->pers.classSelection == PCL_ALIEN_LEVEL0)//dretch
            {
				//do nothing special yet
            }
			else if (self->client->pers.classSelection == PCL_ALIEN_LEVEL1)//basilisk
			{
				if (distance <= LEVEL1_CLAW_RANGE) {
					BotMainAttack( self );
				}
				if (distance <= LEVEL1_GRAB_RANGE) {
					BotStop( self );
					BotMoveFwd( self );
					anglediff = botGetAngleBetweenPlayer( self, self->bot->Enemy );
					if(anglediff > 90 && anglediff <= 180) {
						BotMoveLeft( self );
					} else if(anglediff > 180 && anglediff < 270) {
						BotMoveRight( self );
					} else {
						BotJump( self );
						BotMainAttack( self );
					}
				}
			}
			else if (self->client->pers.classSelection == PCL_ALIEN_LEVEL1_UPG)//adv basilisk
			{
				if (distance <= LEVEL1_CLAW_U_RANGE) {
					BotMainAttack( self );
				} 
				if (distance <= LEVEL1_PCLOUD_RANGE) {
 					BotSecAttack( self );
				}
				if (distance <= LEVEL1_GRAB_U_RANGE) {
					BotStop( self );
					BotMoveFwd( self );
					anglediff = botGetAngleBetweenPlayer( self, self->bot->Enemy );
					if(anglediff > 90 && anglediff <= 180) {
						BotMoveLeft( self );
					} else if(anglediff > 180 && anglediff < 270) {
						BotMoveRight( self );
					} else {
						BotJump( self );
					}
				}
			}
			else if (self->client->pers.classSelection == PCL_ALIEN_LEVEL2)//marauder
			{
				if (distance <= LEVEL2_CLAW_RANGE) {
					BotMainAttack( self );
				}
			}
			else if (self->client->pers.classSelection == PCL_ALIEN_LEVEL2_UPG)//adv marauder
			{
				if (distance <= LEVEL2_CLAW_U_RANGE) {
					BotMainAttack( self );
				} 
				if (distance <= LEVEL2_AREAZAP_RANGE) {
 					BotSecAttack( self );
				}
			}
			else if (self->client->pers.classSelection == PCL_ALIEN_LEVEL3)//dragon
			{
				if(distance > LEVEL3_CLAW_RANGE && self->client->ps.stats[ STAT_MISC ] < LEVEL3_POUNCE_JUMP_MAG) {
 					BotSecAttack( self );
				} else {
					BotMainAttack( self );
				}
			}
			else if (self->client->pers.classSelection == PCL_ALIEN_LEVEL3_UPG)//adv dragon
			{
				//it can shoot and attack at the same time
				if(self->client->ps.ammo > 0 && distance > 150) {
					   BotMidAttack( self ); 
				}
				if(distance > LEVEL3_CLAW_UPG_RANGE && self->client->ps.stats[ STAT_MISC ] < LEVEL3_POUNCE_JUMP_MAG_UPG) {
 					BotSecAttack( self ); //TODO: should Bot_Pounce be used here?
				} else {
					BotMainAttack( self );
				}
			}
			else if (self->client->pers.classSelection == PCL_ALIEN_LEVEL4)//tyrant
			{
				if (distance > LEVEL4_CLAW_RANGE) {
 					BotSecAttack( self );
				} else {
					BotMainAttack( self );
				}
			}
			return;
	} else {
		BotResetState( self, ATTACK );
		self->bot->Enemy = NULL;
		BotControl( self, BOT_RESET_BUTTONS );
	}
}

/**
 * Think the best target to attack
 * this function may change the bot->Enemy
 * @param self
 */
void BotTargetAlien( gentity_t *self ) {
	//simple rank
	//self->bot->Enemy = &target;	
}

/**
 * Granger build
 * @param client
 */
void BotBuildAlien( gentity_t *self ) {
	
}

/**
 * Search for booster of basilisk to heal
 * @param client
 */
void BotHealAlien( gentity_t *self ) {
	//Heal if near booster or basilisk
	if(level.time - self->bot->timer.improve > 5000) 
	{
		self->bot->timer.improve = level.time;
		self->bot->Struct = botFindClosestBuildable( self, 500, BA_A_BOOSTER );
		//Heal by basilisk
		if(!self->bot->Struct && self->health <= 40) {
			self->bot->Friend = botFindClosestBasilisk( self, 400 );
			if(self->bot->Friend) {
				self->bot->state = FOLLOW;
			}
		}
	}
}

/*
================
Based on botFindClosestBuildable
Finds a basilisk within range
@param self [gentity_t] BOT
@param r [float] range to check
================
*/
gentity_t *botFindClosestBasilisk( gentity_t *self, float r )
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

    if( ent->health > 0 && 
			(ent->client->ps.stats[ STAT_CLASS ] == PCL_ALIEN_LEVEL1 || 
			ent->client->ps.stats[ STAT_CLASS ] == PCL_ALIEN_LEVEL1_UPG)) {
      return ent;
	}
  }

  return NULL;
}

/**
 * Perform group logic for Aliens
 */
void G_BotGroupThinkAlien( void ) {

} 
