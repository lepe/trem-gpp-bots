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

#include "g_local.h"

#define BOT_FWD_FULL_VAL  	127
#define BOT_FWD_VAL  		100
#define BOT_WALK_VAL  		64
#define BOT_BCK_VAL  		-100
#define BOT_RIGHT_VAL 		100
#define BOT_LEFT_VAL 		-100
#define BOT_CROUCH_VAL		-1
#define BOT_WALLWALK_VAL	-1
#define BOT_JUMP_VAL  		20
/*
 * Bot movement related functions
 */

/**
 * Bot will start performing an advanced movement.
 * @param self
 * @param block [botMove]: prevent that specific move to be done during the queue action
 *   (use BOT_EMPTY_MOVE, to allow all movements)
 */
void BotStartMove( gentity_t *self, botMove block) {
	self->bot->move.exec = qtrue;
	self->bot->move.blockedAction = block;
}
/**
 * Perform bot movements (read from queue)
 * movement functions are declared in g_bot_control.c
 * @param self [gentity_t]
 */
void BotDoMove( gentity_t *self, int msec ) {
	int time;
	botMove move;
	if(self->bot->move.exec == qtrue && self->bot->move.read < BOT_MOVE_QUEUE) {
		move = self->bot->move.queue[ self->bot->move.read ].action;
		//if there is some action:
		if( move > BOT_EMPTY_MOVE ) {
			if(self->bot->timer.move == 0) {
				BotControl( self, move );
				self->bot->timer.move += msec;
			} else {
				time = self->bot->move.queue[ self->bot->move.read ].time;
				if(self->bot->timer.move > time) {
					BotCleanMove( self );
					self->bot->move.read++;
					self->bot->timer.move = 0;
				} else {
					self->bot->timer.move += msec;
				}
			}
		} else { //we hit the end of the movement
			self->bot->timer.move = 0;
			self->bot->move.blockedAction = BOT_EMPTY_MOVE;
			BotClearQueue( self );
		}
	}
}
/**
 * Adds a movement to the queue (used mainly to create sequence of movements)
 * if no time is required, use either the shortcut, like BotRun(), or 
 * use BotControl();
 * @param self
 * @param move
 */
void BotAddMove( gentity_t *self, botMove move, int time ) {
	if(self->bot->move.exec == qfalse) {
		if(self->bot->move.write == BOT_MOVE_QUEUE) {
			G_Printf("%s: Movement dropped (%d) with time (%d)! Please set BOT_MOVE_QUEUE to a higher value.\n",self->client->pers.netname ,move,time);
		} else {
			if(self->bot->move.queue[ self->bot->move.write ].action == BOT_EMPTY_MOVE) {
				self->bot->move.queue[ self->bot->move.write ].action = move;
				self->bot->move.queue[ self->bot->move.write ].time = time;
				self->bot->move.write++;
			}
		}
	} //else: drop it
}
/**
 * When time expires, return to previous condition
 * "move.exec" means previously executed action 
 * @param self
 */
void BotCleanMove( gentity_t *self ) {
	char *movement;
	/* 
	 * We need to clear the upmove value in the next cycle after
	 * jumping or we can't jump again immediately.
	 */
	switch(self->bot->move.queue[ self->bot->move.read ].action) {
		case BOT_JUMP:
			self->client->pers.cmd.upmove = 0;
			movement = "JUMP";
		break;
		case BOT_MOVE_LEFT:
		case BOT_MOVE_RIGHT:
			if(self->bot->move.queue[ self->bot->move.read ].time > 0) {
				self->client->pers.cmd.rightmove = 0;
				movement = "RESET LEFT-RIGHT";
			}
			break;
		case BOT_MOVE_FWD:
		case BOT_MOVE_BACK:
		case BOT_RUN:
			if(self->bot->move.queue[ self->bot->move.read ].time > 0) {
				self->client->pers.cmd.forwardmove = 0;
				movement = "RESET FWD-BACK";
			}
			break;
		case BOT_GESTURE:
		case BOT_MAIN_ATTACK:
		case BOT_SEC_ATTACK:
		case BOT_MID_ATTACK:
			self->client->pers.cmd.buttons = 0;
			movement = "RESET BUTTONS";
			break;
		default:
			movement = "";
			break;
	}
	G_BotDebug(self, BOT_VERB_DETAIL, BOT_DEBUG_CONTROL, "Clear: %s\n", movement);
}
/**
 * Executes the action to control the bot
 * @param self
 */
void BotControl( gentity_t *self, botMove move ) {
	char *movement;
	//If we are executing something and it matches the blockedAction,  don't do anything
	if(self->bot->timer.move > 0) {
		if(move == self->bot->move.blockedAction) return;
		if(move == BOT_RESET_BUTTONS || move == BOT_RESET_LEFT_RIGHT || move == BOT_RESET_FWD_BACK || move == BOT_STOP) return;
	}
	switch(move) {
		case BOT_WAIT: 
			/*this is a dummy movement. Is used to preserve previous momentum. 
			 *For example, if you want the bot to go left and after 2 sec to jump, 
			 *you can set: BotMoveLeft( self ); BotWait( self, 2000 ); BotJump( self );
			 */
			movement = "WAIT";
			break;
		case BOT_RUN: 				
			self->client->pers.cmd.forwardmove = BOT_FWD_FULL_VAL;
			movement = "RUN";
			break;
		case BOT_WALK: //silent walk
			self->client->pers.cmd.forwardmove = BOT_WALK_VAL;
			movement = "WALK";
			break;
		case BOT_JUMP: 				
			self->client->pers.cmd.upmove = BOT_JUMP_VAL;
			movement = "JUMP";
			break;
		case BOT_STOP: 				
			self->client->pers.cmd.buttons = 0;
			self->client->pers.cmd.forwardmove = 0;
			self->client->pers.cmd.rightmove = 0;
			movement = "STOP";
			break;
		case BOT_CROUCH: 			
			self->client->pers.cmd.upmove = BOT_CROUCH_VAL;
			movement = "CROUCH";
			break;
		case BOT_WALLWALK:			
			if( BG_ClassHasAbility( self->client->ps.stats[ STAT_CLASS ], SCA_WALLCLIMBER ) ) { //LEPE: if possible
				self->client->pers.cmd.upmove = BOT_WALLWALK_VAL;
				movement = "WALLWALK";
			}
			break;
		case BOT_STAND:
			self->client->pers.cmd.upmove = 0;
			movement = "STAND";
			break;
		case BOT_MOVE_LEFT: 		
			self->client->pers.cmd.rightmove = BOT_LEFT_VAL;
			movement = "MOVE LEFT";
			break;
		case BOT_MOVE_RIGHT:		
			self->client->pers.cmd.rightmove = BOT_RIGHT_VAL;
			movement = "MOVE RIGHT";
			break;
		case BOT_MOVE_FWD:			
			self->client->pers.cmd.forwardmove = BOT_FWD_VAL;
			movement = "MOVE FORWARD";
			break;
		case BOT_MOVE_BACK: 		
			self->client->pers.cmd.forwardmove = BOT_BCK_VAL;
			movement = "MOVE BACKWARD";
			break;
		case BOT_LOOK_CENTER:
			self->client->ps.delta_angles[ PITCH ] = 0;
			movement = "LOOK CENTER";
			break;
		case BOT_LOOK_UP:			
 			self->client->ps.delta_angles[ PITCH ] -= ANGLE2SHORT( BOT_TURN_VAL ); //this makes bots to move aim in Z angles
			movement = "LOOK UP";
			break;
		case BOT_LOOK_DOWN: 		
 			self->client->ps.delta_angles[ PITCH ] += ANGLE2SHORT( BOT_TURN_VAL ); //this makes bots to move aim in Z angles
			movement = "LOOK DOWN";
			break;
		case BOT_LOOK_RANDOM:
			self->client->ps.delta_angles[ YAW ] = ANGLE2SHORT( G_Rand_Range(1, 360) );
			movement = "LOOK RANDOM";
			break;		
		case BOT_LOOK_LEFT:			
			self->client->ps.delta_angles[ YAW ] += ANGLE2SHORT( BOT_TURN_VAL );
			movement = "LOOK LEFT";
			break;
		case BOT_LOOK_RIGHT:		
			self->client->ps.delta_angles[ YAW ] -= ANGLE2SHORT( BOT_TURN_VAL );
			movement = "LOOK RIGHT";
			break;
		case BOT_MAIN_ATTACK:
			self->client->pers.cmd.buttons |= BUTTON_ATTACK;
			movement = "MAIN BUTTON";
			break;
		case BOT_SEC_ATTACK:
			self->client->pers.cmd.buttons |= BUTTON_ATTACK2;
			movement = "SEC. BUTTON";
			break;
		case BOT_MID_ATTACK:
			self->client->pers.cmd.buttons |= BUTTON_USE_HOLDABLE;
			movement = "MID. BUTTON";
			break;
		case BOT_GESTURE:
			self->client->pers.cmd.buttons |= BUTTON_GESTURE;
			movement = "GESTURE";
			break;
		case BOT_RESET_BUTTONS:
			self->client->pers.cmd.buttons = 0;
			movement = "RESET BUTTONS";
			break;
		case BOT_RESET_LEFT_RIGHT:
			self->client->pers.cmd.rightmove = 0;
			movement = "RESET LEFT-RIGHT";
			break;
		case BOT_RESET_FWD_BACK:
			self->client->pers.cmd.forwardmove = 0;
			movement = "RESET FWD-BACK";
			break;
		default:
			movement = "";
			G_Printf("Invalid Bot Movement: %d\n", move);
			break;
	}
	G_BotDebug(self, BOT_VERB_DETAIL, BOT_DEBUG_CONTROL, "Movement: %s\n", movement);
}
/**
 * Clears queue (usually when bot is dead)
 * @param self
 */
void BotClearQueue( gentity_t *self )
{
	int q;
	for(q = 0; q < BOT_MOVE_QUEUE; q++) {
		self->bot->move.queue[ q ].action = BOT_EMPTY_MOVE;
		self->bot->move.queue[ q ].time = 0;
	}
	self->bot->move.write = 0;
	self->bot->move.read = 0;
	self->bot->move.exec = qfalse;
    G_BotDebug(self, BOT_VERB_DETAIL, BOT_DEBUG_CONTROL, "Queue Cleared.\n");
}

/**
 * Test if bot is moving
 * @param self
 * @param move
 */
qboolean BotIsMoving( gentity_t *self, botMove move ) 
{
	switch(move) {
		case BOT_RUN: 			return self->client->pers.cmd.forwardmove == BOT_FWD_FULL_VAL;
		case BOT_WALK: 			return self->client->pers.cmd.forwardmove == BOT_WALK_VAL;
		case BOT_JUMP: 			return self->client->pers.cmd.upmove == BOT_JUMP_VAL;
		case BOT_STOP: 			return self->client->pers.cmd.forwardmove == 0 && self->client->pers.cmd.rightmove == 0;
		case BOT_CROUCH:		return self->client->pers.cmd.upmove == BOT_CROUCH_VAL;
		case BOT_WALLWALK:		return self->client->pers.cmd.upmove == BOT_WALLWALK_VAL;
		case BOT_STAND:			return self->client->pers.cmd.upmove == 0;
		case BOT_MOVE_LEFT: 	return self->client->pers.cmd.rightmove == BOT_LEFT_VAL;
		case BOT_MOVE_RIGHT:	return self->client->pers.cmd.rightmove == BOT_RIGHT_VAL;
		case BOT_MOVE_FWD:		return self->client->pers.cmd.forwardmove > 0;
		case BOT_MOVE_BACK: 	return self->client->pers.cmd.forwardmove < 0;
		case BOT_MAIN_ATTACK:	return self->client->pers.cmd.buttons & BUTTON_ATTACK;
		case BOT_SEC_ATTACK: 	return self->client->pers.cmd.buttons & BUTTON_ATTACK2;
		case BOT_MID_ATTACK: 	return self->client->pers.cmd.buttons & BUTTON_USE_HOLDABLE;
		default: //nothing here
			G_Printf("WARN: IsMovement not implemented, returning false: %d\n",move);
			break;
	}
	return qfalse;
}

/**
 * Move bot to point without using AIM (EXPERIMENTAL)
 * depends on self->bot->move.topoint
 * @param self
 */
void BotMoveToPoint( gentity_t *self, vec3_t point ) {
	VectorCopy(point, self->bot->move.topoint);
}
void BotMoveToPointClear( gentity_t *self ) {
	VectorClear(self->bot->move.topoint);
}
void BotMoveToPointExec( gentity_t *self ) {
	if(VectorLength(self->bot->move.topoint) > 0) {
		if(Distance(self->bot->move.topoint, self->s.pos.trBase) > BOT_MOVE_PACE) {
			int angle = botGetAngleToPoint(self, self->bot->move.topoint);
			// Convert angle to positive value
			if(angle < 0) angle += 360;
			// Move the bot:
			if (angle == 0 || angle == 360) {
				BotMoveFwd( self );
				BotControl( self , BOT_RESET_LEFT_RIGHT);
			} else if(angle > 0 && angle < 90) {
				BotMoveFwd( self );
				BotMoveRight( self );
			} else if(angle == 90) {
				BotMoveRight( self );
				BotControl( self , BOT_RESET_FWD_BACK);
			} else if(angle > 90 && angle < 180) {
				BotMoveBack( self );
				BotMoveRight( self );
			} else if(angle == 180) {
				BotMoveBack( self );
				BotControl( self , BOT_RESET_LEFT_RIGHT);
			} else if(angle > 180 && angle < 270) {
				BotMoveBack( self );
				BotMoveLeft( self );
			} else if(angle == 270) {
				BotMoveLeft( self );
				BotControl( self , BOT_RESET_FWD_BACK);
			} else if(angle > 270 && angle < 360) {
				BotMoveFwd( self );
				BotMoveLeft( self );
			}
			//get the amount in X and Y and Z that we have to move to.
			//it hast to be based in a fixed amount towards the goal.
		} else {
			BotStop( self );
			BotCrouch( self );
			VectorClear(self->bot->move.topoint);
		}
	}
}
/**
 * Move AIM gradually to reach a point. (EXPERIMENTAL)
 * depends on self->bot->move.lookat
 * @param self
 */
void BotAimToPoint( gentity_t *self, vec3_t point ) {
	VectorCopy(point, self->bot->move.lookat);
}
void BotAimToPointClear( gentity_t *self ) {
	VectorClear(self->bot->move.lookat);
}
void BotAimToPointExec( gentity_t *self ) {
	if(abs(self->bot->move.lookat[ PITCH ] - self->client->ps.delta_angles[ PITCH ]) > BOT_TURN_SHORT) {
		if(self->bot->move.lookat[ PITCH ] > self->client->ps.delta_angles[ PITCH ]) {
			self->client->ps.delta_angles[ PITCH ] -= BOT_TURN_SHORT;
		} else {
			self->client->ps.delta_angles[ PITCH ] += BOT_TURN_SHORT;
		}
		//we will move towards that coordinate at a fixed pace until we reach it.
	} else {
		self->client->ps.delta_angles[ PITCH ] = self->bot->move.lookat[ PITCH ];
	}
	if(abs(self->bot->move.lookat[ YAW ] - self->client->ps.delta_angles[ YAW ]) > BOT_TURN_SHORT) {
		if(self->bot->move.lookat[ YAW ] > self->client->ps.delta_angles[ YAW ]) {
			self->client->ps.delta_angles[ YAW ] -= BOT_TURN_SHORT;
		} else {
			self->client->ps.delta_angles[ YAW ] += BOT_TURN_SHORT;
		}
	} else {
		self->bot->move.lookat[ YAW ] = self->client->ps.delta_angles[ YAW ];
	}
}

//------------------ PUBLIC FUNCTIONS -----------------
/*
 * These functions serve as shurtcut for: BotAddMove() 
 * to use custome timed actions use BotAddMove instead.
 */
void BotRun( gentity_t *self )		{ BotControl( self, BOT_RUN ); }
void BotWalk( gentity_t *self )		{ BotControl( self, BOT_WALK ); }
void BotJump( gentity_t *self )		{ BotAddMove( self, BOT_JUMP, 500 ); BotStartMove( self, BOT_EMPTY_MOVE ); }
void BotStop( gentity_t *self )		{ BotControl( self, BOT_STOP ); }
void BotMoveRight( gentity_t *self ){ BotControl( self, BOT_MOVE_RIGHT ); }
void BotMoveLeft( gentity_t *self )	{ BotControl( self, BOT_MOVE_LEFT ); }
void BotMoveFwd( gentity_t *self )	{ BotControl( self, BOT_MOVE_FWD ); }
void BotMoveBack( gentity_t *self )	{ BotControl( self, BOT_MOVE_BACK ); }
void BotWallWalk( gentity_t *self )	{ BotControl( self, BOT_WALLWALK ); }
void BotCrouch( gentity_t *self )	{ BotControl( self, BOT_CROUCH ); }
void BotStand ( gentity_t *self )	{ BotControl( self, BOT_STAND ); }
void BotGesture ( gentity_t *self )	{ BotControl( self, BOT_GESTURE ); }
void BotMainAttack ( gentity_t *self ){ BotControl( self, BOT_MAIN_ATTACK ); }
void BotSecAttack ( gentity_t *self ){ BotControl( self, BOT_SEC_ATTACK ); }
void BotMidAttack ( gentity_t *self ){ BotControl( self, BOT_MID_ATTACK ); }
/*
 LOOK functions
 */
void BotLookUp( gentity_t *self, int degrees )	 {
 	self->client->ps.delta_angles[ PITCH ] -= ANGLE2SHORT( degrees ); 
	G_BotDebug(self, BOT_VERB_DETAIL, BOT_DEBUG_CONTROL, "Look Up: %d deg.\n", degrees);
}
void BotLookDown( gentity_t *self, int degrees ) { 
 	self->client->ps.delta_angles[ PITCH ] += ANGLE2SHORT( degrees ); 
	G_BotDebug(self, BOT_VERB_DETAIL, BOT_DEBUG_CONTROL, "Look Down: %d deg.\n", degrees);
}
void BotLookLeft( gentity_t *self, int degrees ) { 
	self->client->ps.delta_angles[ YAW ] += ANGLE2SHORT( degrees );
	G_BotDebug(self, BOT_VERB_DETAIL, BOT_DEBUG_CONTROL, "Look Left: %d deg.\n", degrees);
}
void BotLookRight( gentity_t *self, int degrees ){ 
	self->client->ps.delta_angles[ YAW ] -= ANGLE2SHORT( degrees );
	G_BotDebug(self, BOT_VERB_DETAIL, BOT_DEBUG_CONTROL, "Look Right: %d deg.\n", degrees);
}
//########### ALIEN SPECIFIC ################
//void Charge( gentity_t *self ) {}
void Bot_Pounce( gentity_t *self, int angle )	{ 
	BotControl( self, BOT_LOOK_CENTER );
	BotLookUp( self, angle );
	BotAddMove( self, BOT_SEC_ATTACK, LEVEL3_POUNCE_TIME_UPG ); 
	BotAddMove( self, BOT_LOOK_CENTER, 0 );
	BotStartMove( self, BOT_SEC_ATTACK );
}

//########### HUMAN SPECIFIC ################

//void BotFlyUp( gentity_t *self )	{ BotAddMove( self, BOT_RUN ); }
//void BotFlyDown( gentity_t *self )	{ BotAddMove( self, BOT_RUN ); }
void Bot_FullLuci( gentity_t *self )	{ 
	BotAddMove( self, BOT_MAIN_ATTACK, LCANNON_CHARGE_TIME_MAX - 500 ); 
	BotStartMove( self, BOT_SEC_ATTACK);
}
//########### COMMON ################
/**
 * Strafe movement.
 * @param self [gentity_t] : BOT
 * @param length [int] : how far the strafe will be performed.
 *                       set it to zero to make it random
 */
void Bot_Strafe( gentity_t *self ) {
	//if(g_human_strafe.integer > 0) {
	int length = G_Rand_Range(200, 800);
	if(G_Rand() < 50) {
		BotAddMove( self, BOT_MOVE_RIGHT, length );
		BotAddMove( self, BOT_MOVE_LEFT, length );
	} else {
		BotAddMove( self, BOT_MOVE_LEFT, length );
		BotAddMove( self, BOT_MOVE_RIGHT, length );
	}
	BotStartMove( self , BOT_EMPTY_MOVE);
}

