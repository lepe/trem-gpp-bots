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
	//self->bot->funcs.team.target			= BotTargetAlien;
	self->bot->funcs.team.targetRank		= BotTargetRankAlien;
	self->bot->funcs.team.think				= BotAlienThink;
	//--- state functions
	self->bot->funcs.team.status[IDLE]		= BotIdleAlien;
	self->bot->funcs.team.status[ATTACK]	= BotAttackAlien;
	self->bot->funcs.team.status[HEAL]		= BotHealAlien;
	self->bot->funcs.team.status[BUILD]		= BotBuildAlien;
	self->bot->funcs.team.status[IMPROVE]	= BotEvolve;
	self->bot->funcs.team.status[RETREAT]	= BotRetreatAlien;
	//--- nav state functions
	self->bot->funcs.team.nav[TARGETPATH]	= BotNavigateAlien;
	self->bot->funcs.team.nav[BLOCKED]		= BotBlockedAlien;
	//default % of evolving
	self->bot->set.tyrant[S3] 		= 90;
	self->bot->set.adv_goon[S3]		= 80;
	self->bot->set.adv_goon[S2]		= 90;
	self->bot->set.goon[S3] 		= 5;
	self->bot->set.goon[S2] 		= 5;
	self->bot->set.goon[S1] 		= 90;
	self->bot->set.adv_marauder[S3]	= 70;
	self->bot->set.adv_marauder[S2]	= 70;
	self->bot->set.marauder[S3] 	= 5;
	self->bot->set.marauder[S2] 	= 70;
	self->bot->set.marauder[S1]		= 70;
	self->bot->set.adv_basilisk[S3]	= 30;
	self->bot->set.adv_basilisk[S2]	= 60;
	self->bot->set.basilisk[S3] 	= 5;
	self->bot->set.basilisk[S2] 	= 50;
	self->bot->set.basilisk[S1] 	= 70;
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
    G_BotDebug(self, BOT_VERB_DETAIL, BOT_DEBUG_ALIEN + BOT_DEBUG_THINK, "Bot is about to spawn\n");
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
	
	///////////////////////// LEVEL 3 /////////////////////////
 	if(BotKeepThinking( self, THINK_LEVEL_3 )) { 
		if(!self->bot->Enemy) { 
			botFindClosestFriend( self );
		}
	}
	///////////////////////// LEVEL MAX /////////////////////////
 	if(BotKeepThinking( self, THINK_LEVEL_MAX )) { 
		if(self->client->pers.classSelection > PCL_ALIEN_LEVEL1_UPG && botGetHealthPct( self ) < 30) {
		//	self->bot->think.state[ THINK_LEVEL_3 ] = RETREAT; Not yet. We need to evaluate more the situation
		}
	}
	
}
/**
 * Special movement for aliens:
 * @param self
 */
void BotNavigateAlien( gentity_t *self )
{
	int angle;
	int distance = distanceToTargetNode(self);
	if( BG_ClassHasAbility( self->client->ps.stats[ STAT_CLASS ], SCA_WALLCLIMBER ) ) { //LEPE: if possible
		if(G_Rand() < 70) {
			BotWallWalk( self );
		} else {
			BotStand( self );
		}
	} else if((self->client->pers.classSelection == PCL_ALIEN_LEVEL2 || 
			self->client->pers.classSelection == PCL_ALIEN_LEVEL2_UPG)) {
				if(distance > 400) {
					BotJump( self );
				}
	} else if((self->client->pers.classSelection == PCL_ALIEN_LEVEL3 && 
			  self->client->ps.stats[ STAT_MISC ] < LEVEL3_POUNCE_JUMP_MAG) || 
			 (self->client->pers.classSelection == PCL_ALIEN_LEVEL3_UPG && 
			  self->client->ps.stats[ STAT_MISC ] < LEVEL3_POUNCE_JUMP_MAG_UPG)) {
				if(distance > 400) {
						 if(distance < 500) angle = 10;
					else if(distance < 700) angle = 15;
					else if(distance < 900) angle = 20;
					else if(distance < 1200) angle = 25;
					else angle = 45;
					Bot_Pounce( self, angle );
				}
	} else if(self->client->pers.classSelection == PCL_ALIEN_LEVEL4) {
		if(distance > 250) {
			BotSecAttack( self );
		}
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
	
	if(canwallwalk) BotWallWalk( self ); //if possible

	G_BotDebug(self, BOT_VERB_DETAIL, BOT_DEBUG_ALIEN + BOT_DEBUG_NAVSTATE, "[ %d ] Trying to unblock. Rand: %d\n", try, rand );
	if(try <= 0) {
		BotMoveFwd( self );
		BotJump( self );
		VectorCopy(self->r.currentOrigin, self->bot->path.blocked_origin);
	} else if(try < BOT_TIMER_NAV_SECOND) {
		if(!canwallwalk || try % BOT_TIMER_NAV_SECOND == 0) BotJump( self ); 
	} else if(try == BOT_TIMER_NAV_SECOND) {
		BotFindNewPath( self ); //Testing
		BotControl( self, BOT_LOOK_RANDOM );
	} else if(try > BOT_TIMER_NAV_SECOND) {
		if(!canwallwalk || try % BOT_TIMER_NAV_SECOND == 0) BotJump( self );
	}
	
	if(try >= BOT_TIMER_NAV_SECOND * 4) {
		self->bot->path.blocked_try = 0; 
		G_BotDebug(self, BOT_VERB_DETAIL, BOT_DEBUG_ALIEN + BOT_DEBUG_NAVSTATE, "Reset blocked_try to 0\n" );
		//If there is a friend nearby, try to follow him
		botFindClosestFriend( self );
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
	class_t class = PCL_NONE;
	qboolean classfound = qfalse;
	qboolean lowclass = qfalse;
	int levels;
	int clientNum;
	int randval;
	int sincelast;

	clientNum = self->client - level.clients;
	sincelast = level.time - self->bot->timer.improve; //TODO: use sincelast to decide probability
	
	//Do not evolve right away.
	if(sincelast < 5000) return;
	
	self->bot->timer.improve = level.time;

	randval = (G_Rand() - ((self->client->pers.credit / ALIEN_MAX_CREDITS) * 100));
	
	if(randval < self->bot->set.tyrant[g_alienStage.integer] && g_bot_tyrant.integer > 0)
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
	  
	}
	if(randval < self->bot->set.adv_goon[g_alienStage.integer] && classfound == qfalse && g_bot_advgoon.integer > 0)
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
	}
	if(randval < self->bot->set.adv_marauder[g_alienStage.integer] && classfound == qfalse && g_bot_advmara.integer > 0)
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
	}
	if(randval < self->bot->set.marauder[g_alienStage.integer] && classfound == qfalse && g_bot_mara.integer > 0)
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
	}
	if(randval < self->bot->set.adv_basilisk[g_alienStage.integer] && classfound == qfalse && g_bot_advbasi.integer > 0)
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
	if(randval < self->bot->set.goon[g_alienStage.integer] && classfound == qfalse && g_bot_goon.integer > 0)
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
	}
	if(randval < self->bot->set.basilisk[g_alienStage.integer] && classfound == qfalse && g_bot_basi.integer > 0)
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
		if(lowclass == qfalse){
			G_AddCreditToClient( self->client, -(short)levels, qtrue );
		}
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
	int veryCloseDistance = LEVEL4_CLAW_RANGE; 
	int distance = botGetDistanceBetweenPlayer(self, self->bot->Enemy);
	int anglediff = 0;
	qboolean flank = qfalse;
	qboolean jumpOnZero = qfalse;
	//If we are closer than what humans can reach to us
	if(distance < g_human_range.integer)
	{
			BotWallWalk( self ); // enable wallwalk if possible

			BotRun( self );
			//If we are not close enough and the target is a bot or a player, strafe
			//TODO: we could apply bot difficulty here. Like, easy bots will not strafe
			if(distance > (veryCloseDistance * 2)) {
				Bot_Strafe( self );
			} else if(distance < veryCloseDistance) {
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
					flank = qtrue;
					jumpOnZero = qtrue;
            }
			else if (self->client->pers.classSelection == PCL_ALIEN_LEVEL1)//basilisk
			{
				if (distance <= LEVEL1_CLAW_RANGE) {
					BotMainAttack( self );
				}
				if (distance <= LEVEL1_GRAB_RANGE) {
					flank = qtrue;
					jumpOnZero = qtrue;
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
					flank = qtrue;
					jumpOnZero = qtrue;
				}
			}
			else if (self->client->pers.classSelection == PCL_ALIEN_LEVEL2)//marauder
			{
				if (distance <= LEVEL2_CLAW_RANGE) {
					BotMainAttack( self );
					flank = qtrue;
					jumpOnZero = qtrue;
				}
				if(self->bot->Enemy->s.eType == ET_PLAYER) {
					BotJump( self );
				}
			}
			else if (self->client->pers.classSelection == PCL_ALIEN_LEVEL2_UPG)//adv marauder
			{
				if (distance <= LEVEL2_CLAW_U_RANGE) {
					BotMainAttack( self );
					flank = qtrue;
					jumpOnZero = qtrue;
				} 
				if (distance <= LEVEL2_AREAZAP_RANGE) {
 					BotSecAttack( self );
				}
				if(self->bot->Enemy->s.eType == ET_PLAYER) {
					BotJump( self );
				}
			}
			else if (self->client->pers.classSelection == PCL_ALIEN_LEVEL3)//dragon
			{
				if(distance > LEVEL3_CLAW_RANGE && self->client->ps.stats[ STAT_MISC ] == 0) { // < LEVEL3_POUNCE_JUMP_MAG) {
 					//BotSecAttack( self );
					Bot_Pounce( self , 10 );
				} else {
					BotMainAttack( self );
					flank = qtrue;
				}
			}
			else if (self->client->pers.classSelection == PCL_ALIEN_LEVEL3_UPG)//adv dragon
			{
				//it can shoot and attack at the same time
				if(self->client->ps.ammo > 0 && distance > 150) {
					   BotMidAttack( self ); 
				}
				if(distance > LEVEL3_CLAW_UPG_RANGE && self->client->ps.stats[ STAT_MISC ] == 0) { // < LEVEL3_POUNCE_JUMP_MAG_UPG) {
 					//BotSecAttack( self ); 
					Bot_Pounce( self , 10 );
				} else {
					BotMainAttack( self );
					flank = qtrue;
				}
			}
			else if (self->client->pers.classSelection == PCL_ALIEN_LEVEL4)//tyrant
			{
				if (distance > LEVEL4_CLAW_RANGE) {
 					BotSecAttack( self );
				} else {
					BotMainAttack( self );
					flank = qtrue;
				}
			}
			if(flank) {
				anglediff = botGetAngleBetweenPlayersView( self, self->bot->Enemy );
				if(anglediff > 90 && anglediff <= 180) {
					BotMoveLeft( self );
				} else if(anglediff > 180 && anglediff < 270) {
					BotMoveRight( self );
				} else {
					//in any structure, move but not jump
					if(self->bot->Enemy->s.eType == ET_BUILDABLE) {
						if(G_Rand() < 20 || !(BotIsMoving(self, BOT_MOVE_LEFT) || (BotIsMoving(self, BOT_MOVE_RIGHT)))) {
							if(G_Rand() < 50) {
								BotMoveLeft( self );
							} else {
								BotMoveRight( self );
							}
						}
					} else if(jumpOnZero) {
						BotJump( self );
					}
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
 * Things that happen when doing nothing
 * @param self
 */
void BotIdleAlien( gentity_t *self ) {

}
/**
 * @param self
 * //TODO: replace hardcoded values
 */
int BotTargetRankAlien(gentity_t *self, gentity_t *target, float rank ) {
	int sd;
	qboolean BS;
	qboolean Armor;
	qboolean Helmet;
	qboolean Naked;

	if(!G_Visible(self, target, CONTENTS_SOLID)) {
		return 0;
	}
	sd = G_TimeTilSuddenDeath() <= 0 ? 2 : 1;
	if(target->s.eType == ET_BUILDABLE) {
		if(self->client->pers.classSelection > PCL_ALIEN_LEVEL0 || !target->powered) {
			if(self->health >= 100) rank += 30;
			else if(self->health >= 200) rank += 60;

			switch(target->s.modelindex) {
				case BA_H_SPAWN: 	rank += (50 * sd); break;
				case BA_H_REACTOR:  rank += (30 * sd); break;
				case BA_H_MEDISTAT:	rank += (25 * sd); break;
				case BA_H_ARMOURY:  rank += (20 * sd); break;
				case BA_H_REPEATER: rank += (25 * sd); break;
				case BA_H_DCC: 		rank += (15 * sd); break;
				default: 			rank += (10 * sd); break;
			}
			//Above Adv.Marauder, target more to structures
			if(self->client->pers.classSelection > PCL_ALIEN_LEVEL2) {
				rank += 40;
			}
		} else {
			return 0;
		}
	} else if(target->client) {
		BS = target->client->pers.classSelection == PCL_HUMAN_BSUIT;
		Helmet = BG_InventoryContainsUpgrade( UP_HELMET, target->client->ps.stats );
		Armor = BG_InventoryContainsUpgrade( UP_LIGHTARMOUR, target->client->ps.stats );
		Naked = !(Armor || Helmet);
		switch(self->client->pers.classSelection) {
			case PCL_ALIEN_BUILDER0:	
			case PCL_ALIEN_BUILDER0_UPG:
				switch(target->client->ps.weapon) {
					default: rank -= 30; break;
				}
			break;
			case PCL_ALIEN_LEVEL0:
				switch(target->client->ps.weapon) {
					case WP_BLASTER:
					case WP_MACHINEGUN:
					case WP_PAIN_SAW:
						rank += 30; break;
					case WP_SHOTGUN:
					case WP_LAS_GUN:
					case WP_CHAINGUN:
						break;
					case WP_MASS_DRIVER: 
					case WP_FLAMER:
					case WP_PULSE_RIFLE:
					case WP_LUCIFER_CANNON:
						rank -= 30; break;
					default: break;
				}
			break;
			case PCL_ALIEN_LEVEL1:
			case PCL_ALIEN_LEVEL1_UPG:
				switch(target->client->ps.weapon) {
					case WP_BLASTER:
					case WP_MACHINEGUN:
					case WP_PAIN_SAW:
						rank += 30; break;
					case WP_SHOTGUN:
					case WP_LAS_GUN:
						rank += 10; break;
					case WP_MASS_DRIVER: 
						rank -= 10; break;
					case WP_CHAINGUN:
					case WP_FLAMER:
					case WP_PULSE_RIFLE:
					case WP_LUCIFER_CANNON:
					default:
						break;
				}
				if(!BS) {
					rank += 20;
				}
			break;
			case PCL_ALIEN_LEVEL2:
			case PCL_ALIEN_LEVEL2_UPG:
				switch(target->client->ps.weapon) {
					case WP_BLASTER:
					case WP_MACHINEGUN:
					case WP_PAIN_SAW:
					case WP_LAS_GUN:
					case WP_PULSE_RIFLE:
					case WP_LUCIFER_CANNON:
						rank += 30; break;
					case WP_FLAMER:
					case WP_SHOTGUN:
					case WP_CHAINGUN:
					case WP_MASS_DRIVER: 
					default:
						break;
				}
			break;
			case PCL_ALIEN_LEVEL3:
				switch(target->client->ps.weapon) {
					case WP_BLASTER:
					case WP_MACHINEGUN:
					case WP_PAIN_SAW:
					case WP_SHOTGUN:
					case WP_LAS_GUN:
					case WP_FLAMER:
					case WP_MASS_DRIVER: 
						rank += 30; break;
					case WP_CHAINGUN:
					case WP_PULSE_RIFLE:
					case WP_LUCIFER_CANNON:
						rank -= 20; break;
					default: break;
				}
			break;
			case PCL_ALIEN_LEVEL3_UPG:
				switch(target->client->ps.weapon) {
					case WP_BLASTER:
					case WP_MACHINEGUN:
					case WP_PAIN_SAW:
					case WP_SHOTGUN:
					case WP_LAS_GUN:
					case WP_FLAMER:
					case WP_MASS_DRIVER: 
						rank += 30; break;
					case WP_CHAINGUN:
					case WP_PULSE_RIFLE:
					case WP_LUCIFER_CANNON:
						break;
					default: break;
				}
			break;
			case PCL_ALIEN_LEVEL4:
				switch(target->client->ps.weapon) {
					case WP_BLASTER:
					case WP_MACHINEGUN:
					case WP_PAIN_SAW:
					case WP_SHOTGUN:
					case WP_LAS_GUN:
					case WP_FLAMER:
					case WP_MASS_DRIVER: 
						rank += 10; break;
					case WP_CHAINGUN:
					case WP_PULSE_RIFLE:
					case WP_LUCIFER_CANNON:
						rank += 30; break;
					default: break;
				}
			break;
			default: break;
		}
		if(BS) {
			rank -= 10;
		} else if(Naked) {
			rank += 30;
		}
	}
	return (int)rank;
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
		if(!self->bot->Struct && botGetHealthPct( self ) <= 40) {
			self->bot->Friend = botFindClosestBasilisk( self, 400 );
		}
	}
}
/**
 * Go back
 * @param self
 */
void BotRetreatAlien( gentity_t *self )
{
	//wait until you are 100% 
	if(botGetHealthPct( self ) > 90) 
	{
		BotResetState( self, RETREAT );
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
