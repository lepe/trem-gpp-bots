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
 * Common code between aliens and humans
 * NOTE: if a function is not implemented is that all code is implemented
 * on team code. Apply only general code here and AVOID using if(TEAM == "ALIENS")
 * like code here.
 * 
 * Some function declarations are commented, like:
	//self->bot->funcs.base.status[IMPROVE]	= BotImprove;
 * Uncomment them if you want to implement it.
 */

#include "g_local.h"

const int BOT_TIMER[] = { 500, 1000, 2000, 4000, 4000 };
//----- initialize bots ----
void BotInit( gentity_t *self ) {
	/* 
	 * Think Load distribuition chart:
	 * 
	 *     MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM  (MIN)
	 *     1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1  (L1)
	 *       2   2   2   2   2   2   2   2   2   2    (L2)
	 *     3       3       3       3       3       3  (L3)
	 *         X       X       X       X       X      (MAX)
	 */
	//we move timers phase a little bit to distribuite load
	self->bot->timer.think[THINK_LEVEL_3]   = BOT_TIMER_THINK_LEVEL_3_START_AT; 
	self->bot->timer.think[THINK_LEVEL_MAX] = BOT_TIMER_THINK_LEVEL_MAX_START_AT;
	//Base functions
	self->bot->funcs.base.spec				= BotSpectator;
	//self->bot->funcs.base.target			= BotGetTarget;
	self->bot->funcs.base.think 			= BotThink; 
	self->bot->funcs.base.aim				= BotAim; 
	self->bot->funcs.base.move				= BotDoMove; //in bot_control.c
	//----- common states ----
	self->bot->funcs.base.status[IDLE]		= BotIdle;
	self->bot->funcs.base.status[EXPLORE]	= BotExplore;
	self->bot->funcs.base.status[ATTACK]	= BotAttack;
	//self->bot->funcs.base.status[DEFEND]	= BotDefend;
	self->bot->funcs.base.status[FOLLOW]	= BotFollow;
	//self->bot->funcs.base.status[RETREAT]	= BotRetreat;
	//self->bot->funcs.base.status[EVADE]		= BotEvade;
	self->bot->funcs.base.status[HEAL]		= BotHeal;
	////self->bot->funcs.base.status[REPAIR] <-- implemented in human
	//self->bot->funcs.base.status[BUILD]		= BotBuild;
	//self->bot->funcs.base.status[RUSH]		= BotRush;
	//self->bot->funcs.base.status[PATROL]	= BotPatrol;
	//self->bot->funcs.base.status[IMPROVE]	= BotImprove;
	//----- navigation states (most are in g_bot_nav.c) ----
	self->bot->state 						= EXPLORE;
	self->bot->path.state 					= FINDNEWPATH;
	self->bot->funcs.base.nav[TARGETPATH]   = BotTargetPath;
	self->bot->funcs.base.nav[FINDNEXTPATH] = BotFindNextPath;
	self->bot->funcs.base.nav[FINDNEWPATH]  = BotFindNewPath;
	self->bot->funcs.base.nav[BLOCKED]  	= BotBlocked;
	self->bot->funcs.base.nav[LOST]  	    = BotLost;
}

/**
 * Think before spawn
 * @param self
 */
void BotSpectator( gentity_t *self ){
	int t;
	//If we die, we reset states
	for(t = 0; t < THINK_LEVEL_MAX + 1; t++) {
		self->bot->think.state[t] = UNDEFINED;
	}
	BotClearQueue( self );
	BotStop( self );
	BotStand( self );
	self->bot->path.state = FINDNEWPATH;
	self->bot->path.pathChosen = qfalse;
	self->bot->path.nextNode = qfalse;
	self->bot->path.targetPath = 0;
	self->bot->path.targetNode = 0;
	self->bot->path.lastpathid = 0;
	self->bot->path.numCrumb   = 0;
	self->bot->path.lastJoint  = 0;
	self->bot->path.blocked_try= 0;
	G_BotDebug(BOT_VERB_DETAIL, BOT_DEBUG_COMMON + BOT_DEBUG_THINK, "Bot is spectator\n");
	//TODO: check what else we need to reset
}
/**
 * Decide which target to attack
 * @param self
 */
void BotGetTarget( gentity_t *self ){}

/**
 * Main Think process 
 * This function must only contain logic blocks (IF, SWITCH, etc) and
 * state suggestions.
 * The intention of this function is to suggest a state to bots
 * on different thinking levels based on current state.
 * DO NOT reset timers here or implement any action (except to reset some value)
 * @param self [gentity_t] a BOT
 */
void BotThink( gentity_t *self )
{
	//We suggest to explore unless they are in manual mode
	if(!g_bot_manual.integer) {
		self->bot->think.state[ THINK_LEVEL_MIN ] = EXPLORE;
	}

	///////////////////////// LEVEL 1 /////////////////////////
	if(BotKeepThinking( self , THINK_LEVEL_1)) return;
	
	if(botFindClosestEnemy( self )) {
		self->bot->think.state[ THINK_LEVEL_1 ] = ATTACK;
	}
	
	switch(self->bot->state) {
		case ATTACK:
			//TODO: this first IF condition should be inside ATTACK function as we need to
			//keep record that it was able to kill it. Depending on target type, it should
			//decide what state should be next.
			if(self->bot->Enemy){
				//Prevent firing to friends
				self->bot->Friend = NULL;
				if(self->bot->Enemy->health <= 0) {
					self->bot->Enemy = NULL;
					self->client->pers.cmd.buttons = 0;
					BotResetState( self, ATTACK );
					BotClearQueue( self );
				}
			} else {
				BotResetState( self, ATTACK );
				BotClearQueue( self );
			}
			///////////////////////// LEVEL 2 /////////////////////////
			if(BotKeepThinking( self , THINK_LEVEL_2)) {
			
				if(self->bot->Enemy) {
					if(botGetDistanceBetweenPlayer(self, self->bot->Enemy) > g_human_range.integer) {
						self->bot->Enemy = NULL;
						BotResetState( self, ATTACK );
					}
				}
				
			}
			///////////////////////// LEVEL 3 /////////////////////////
			if(BotKeepThinking( self , THINK_LEVEL_3)) {
			}
			///////////////////////// LEVEL MAX /////////////////////////
			if(BotKeepThinking( self , THINK_LEVEL_MAX)) {
			}
			break;
			
		case FOLLOW:
			if(self->bot->Friend) {
				if(self->bot->Friend->health <= 0) {
					//TODO: report to CHAT function
					self->bot->Friend = NULL;
					BotResetState( self, FOLLOW );
				}
			} else {
				BotResetState( self, FOLLOW );
			}
			///////////////////////// LEVEL 2 /////////////////////////
			if(BotKeepThinking( self , THINK_LEVEL_2)) {
			
				if(self->bot->Friend) {
					//TODO: change fixed value to a variable
					if(botGetDistanceBetweenPlayer(self, self->bot->Enemy) > 300) {
						self->bot->Friend = NULL;
						BotResetState( self, FOLLOW );
					}
				}
				
			}
			break;
		case HEAL: 
			//wait until you are 100% 
			if(self->health == 100) 
			{
				if(self->bot->Struct) {
					self->bot->Struct = NULL;
				}
				BotResetState( self, HEAL );
			} 
			break;
		default:
			break;
	}
}
/**
 * Bot will aim to path, target, etc. according to state
 * @param self [gentity_t]
 */
void BotAim( gentity_t *self )
{
	switch(self->bot->state) {
		case EXPLORE:
		case RETREAT:
		case RUSH:
		case PATROL:
				botAimAtPath(self);
			break;
		case ATTACK:
		case DEFEND:
			if(self->bot->Enemy) {
				botAimAtTarget(self, self->bot->Enemy, qtrue);
			}
			break;
		case FOLLOW:
			if(self->bot->Friend) {
				botAimAtTarget(self, self->bot->Friend, qtrue);
			}
			break;
		case REPAIR:
		case BUILD:
		case IMPROVE:
		case HEAL:
			if(self->bot->Struct) {
				botAimAtTarget(self, self->bot->Struct, qfalse);
			}
			break;
		default:
			break;
	}
}
/**
 * Test if we should keep thinking:
 * 
 * Minimum level of thinking: ~ every 500ms
 * Level 1 of thinking: ~ 1 second
 * Level 2 of thinking: ~ 2 seconds
 * Level 3 of thinking: ~ 4 seconds
 * Max thinking level:  ~ 4 seconds after Level 3
 * 
 * NOTE: Level 1 decisions can stop any following code, however
 * Level 2 and up, should be encapsulated themselves as their
 * execution happen in different intervals (see level chart).
 *  
 * @param self [gentity_t] a BOT
 */
qboolean BotKeepThinking( gentity_t *self, botThinkLevel level )
{
	//TODO: calculate impulsive behaviour
	if(self->bot->timer.think[level] >= BOT_TIMER[level]) {
		return qtrue;
	} else {
		return qfalse;
	}
}
/**
 * Resets any state to undefined in any level
 * @param self [gentity_t] : bot
 * @param state [botState] : state to reset
 */
void BotResetState( gentity_t *self, botState state )
{
	int t;
	for(t = 0; t < THINK_LEVEL_MAX + 1; t++) {
		if(self->bot->think.state[t] == state) {
			self->bot->think.state[t] = UNDEFINED;
		}
	}
}
/**
 * Perform group logic
 * called directly from g_main.c
 * use: g_bot_group_think = 1000 //each second //TODO
 */
void G_BotGroupThink( void ) {

} 
/**
 * Bot will explore the map (initial state)
 * @param self
 */
void BotExplore( gentity_t *self ){
	BotStand( self );
	BotRun( self );
	BotControl( self, BOT_LOOK_CENTER );
	//TODO: if bot gets stuck, decrease node essence.
}
/**
 * Do nothing... 
 * @param self
 */
void BotIdle( gentity_t *self ){
	//set Bot's ping
	self->client->ps.ping = G_Rand_Range(100, 200);
}
/**
 * Bot will attack to a target
 * @param self
 */
void BotAttack( gentity_t *self ){
	self->bot->timer.foundPath = level.time;
}
/**
 * Bot will defend base (camp). If away from spawn, it will retreat first
 * @param self
 */
void BotDefend( gentity_t *self ){}
/**
 * Bot will follow other players/bot
 * @param self
 */
void BotFollow( gentity_t *self ){
	self->bot->timer.foundPath = level.time;
}
/**
 * Bot will retreat to its origin.
 * @param self
 */
void BotRetreat( gentity_t *self ){}
/**
 * Bot will try to evade enemy but will try to get as close as possible
 * @param self
 */
void BotEvade( gentity_t *self ){}
/**
 * Bot will try to heal itself
 * @param self
 */
void BotHeal( gentity_t *self ){
	if(self->bot->Struct) 
	{
		if(botGetDistanceBetweenPlayer( self, self->bot->Struct) < 50) {
			BotStop( self );
		}
	}
}
/**
 * Bot will try to be useful building something
 * @param self
 */
void BotBuild( gentity_t *self ){}
/**
 * Bot will attack at full speed and follow only essence 
 * @param self
 */
void BotRush( gentity_t *self ){}
/**
 * Bot will attack but will stay close to its spawn, returning now and then
 * @param self
 */
void BotPatrol( gentity_t *self ){}
/**
 * Use your evos/creds to improve
 * @param self
 */
void BotImprove( gentity_t *self ){}
