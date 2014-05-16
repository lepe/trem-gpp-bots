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
 */
void BotStartMove( gentity_t *self ) {
	self->bot->move.exec = qtrue;
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
	/* 
	 * We need to clear the upmove value in the next cycle after
	 * jumping or we can't jump again immediately.
	 */
	switch(self->bot->move.queue[ self->bot->move.read ].action) {
		case BOT_JUMP:
			self->client->pers.cmd.upmove = 0;
		break;
		case BOT_MOVE_LEFT:
		case BOT_MOVE_RIGHT:
			if(self->bot->move.queue[ self->bot->move.read ].time > 0) {
				self->client->pers.cmd.rightmove = 0;
			}
			break;
		case BOT_MOVE_FWD:
		case BOT_MOVE_BACK:
		case BOT_RUN:
			if(self->bot->move.queue[ self->bot->move.read ].time > 0) {
				self->client->pers.cmd.forwardmove = 0;
			}
			break;
		case BOT_POUNCE:
			self->client->pers.cmd.buttons = 0;
 			self->client->ps.delta_angles[ PITCH ] -= ANGLE2SHORT( 45.0f ); //this makes bots to move aim in Z angles
			break;
		case BOT_GESTURE:
		case BOT_FULL_LUCI:
		case BOT_MAIN_ATTACK:
		case BOT_SEC_ATTACK:
		case BOT_MID_ATTACK:
			self->client->pers.cmd.buttons = 0;
			break;
		default:
			break;
	}
}
/**
 * Executes the action to control the bot
 * @param self
 */
void BotControl( gentity_t *self, botMove move ) {
	G_BotDebug(self, BOT_VERB_DETAIL, BOT_DEBUG_CONTROL, "Movement: %d\n", move);
	switch(move) {
		case BOT_WAIT: 
			/*this is a dummy movement. Is used to preserve previous momentum. 
			 *For example, if you want the bot to go left and after 2 sec to jump, 
			 *you can set: BotMoveLeft( self ); BotWait( self, 2000 ); BotJump( self );
			 */
			break;
		case BOT_RUN: 				
			self->client->pers.cmd.forwardmove = BOT_FWD_FULL_VAL;
			break;
		case BOT_JUMP: 				
			self->client->pers.cmd.upmove = BOT_JUMP_VAL;
			break;
		case BOT_STOP: 				
			self->client->pers.cmd.buttons = 0;
			self->client->pers.cmd.forwardmove = 0;
			self->client->pers.cmd.rightmove = 0;
			break;
		case BOT_CROUCH: 			
			self->client->pers.cmd.upmove = BOT_CROUCH_VAL;
			break;
		case BOT_WALLWALK:			
			if( BG_ClassHasAbility( self->client->ps.stats[ STAT_CLASS ], SCA_WALLCLIMBER ) ) { //LEPE: if possible
				self->client->pers.cmd.upmove = BOT_WALLWALK_VAL;
			}
			break;
		case BOT_STAND:
			self->client->pers.cmd.upmove = 0;
			break;
		case BOT_MOVE_LEFT: 		
			self->client->pers.cmd.rightmove = BOT_LEFT_VAL;
			break;
		case BOT_MOVE_RIGHT:		
			self->client->pers.cmd.rightmove = BOT_RIGHT_VAL;
			break;
		case BOT_MOVE_FWD:			
			self->client->pers.cmd.forwardmove = BOT_FWD_VAL;
			break;
		case BOT_MOVE_BACK: 		
			self->client->pers.cmd.forwardmove = BOT_BCK_VAL;
			break;
		case BOT_LOOK_CENTER:
			self->client->ps.delta_angles[ PITCH ] = 0;
			break;
		case BOT_LOOK_UP:			
 			self->client->ps.delta_angles[ PITCH ] -= ANGLE2SHORT( BOT_TURN_VAL ); //this makes bots to move aim in Z angles
			break;
		case BOT_LOOK_DOWN: 		
 			self->client->ps.delta_angles[ PITCH ] += ANGLE2SHORT( BOT_TURN_VAL ); //this makes bots to move aim in Z angles
			break;
		case BOT_LOOK_LEFT:			
			self->client->ps.delta_angles[ YAW ] += ANGLE2SHORT( BOT_TURN_VAL );
			break;
		case BOT_LOOK_RIGHT:		
			self->client->ps.delta_angles[ YAW ] -= ANGLE2SHORT( BOT_TURN_VAL );
			break;
		case BOT_POUNCE:
			self->client->pers.cmd.buttons |= BUTTON_ATTACK2;
 			self->client->ps.delta_angles[ PITCH ] -= ANGLE2SHORT( 45.0f ); 
			break;
		case BOT_MAIN_ATTACK:
		case BOT_FULL_LUCI:
			self->client->pers.cmd.buttons |= BUTTON_ATTACK;
			break;
		case BOT_SEC_ATTACK:
			self->client->pers.cmd.buttons |= BUTTON_ATTACK2;
			break;
		case BOT_MID_ATTACK:
			self->client->pers.cmd.buttons |= BUTTON_USE_HOLDABLE;
			break;
		case BOT_GESTURE:
			self->client->pers.cmd.buttons |= BUTTON_GESTURE;
			break;
		case BOT_RESET_BUTTONS:
			self->client->pers.cmd.buttons = 0;
			break;
		default:
			G_Printf("Invalid Bot Movement: %d\n", move);
			break;
	}
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
}


//------------------ PUBLIC FUNCTIONS -----------------
/*
 * These functions serve as shurtcut for: BotAddMove() 
 * to use custome timed actions use BotAddMove instead.
 */
void BotRun( gentity_t *self )		{ BotControl( self, BOT_RUN ); }
void BotJump( gentity_t *self )		{ BotAddMove( self, BOT_JUMP, 500 ); BotStartMove( self ); }
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
 LOOK functions should be separated from Move QUEUE as they will make everything slower
 still I have to think a way to slow down the movement and prevent it from being instant
 */
void BotLookUp( gentity_t *self, int degrees )	 {
	int d;
	for(d = 0; d < (degrees / BOT_TURN_VAL); d++) {	
		//BotAddMove( self, BOT_LOOK_UP, 10 ); 
	}
}
void BotLookDown( gentity_t *self, int degrees ) { 
	int d;
	for(d = 0; d < (degrees / BOT_TURN_VAL); d++) {	
		//BotAddMove( self, BOT_LOOK_DOWN, 10 ); 
	}
}
void BotLookLeft( gentity_t *self, int degrees ) { 
	int d;
	for(d = 0; d < (degrees / BOT_TURN_VAL); d++) {	
		//BotAddMove( self, BOT_LOOK_LEFT, 10 ); 
	}
}
void BotLookRight( gentity_t *self, int degrees ){ 
	int d;
	for(d = 0; d < (degrees / BOT_TURN_VAL); d++) {	
		//BotAddMove( self, BOT_LOOK_RIGHT, 10 ); 
	}
}
/**
 * Shortcut for multiple changes in visual angle
 * This function should not be used for normal aim as
 * it result in a performance lose.
 * @param self
 * @param X
 * @param Y
 */
void BotTurn( gentity_t *self, int pitch, int yaw ){
	//LEFT RIGHT
	if(yaw < 0) BotLookLeft( self, yaw );
	else BotLookRight( self, yaw );
	//UP DOWN
	if(pitch < 0) BotLookDown( self, pitch );
	else BotLookUp( self, pitch );
	
}

//########### ALIEN SPECIFIC ################
//void Charge( gentity_t *self ) {}
void Bot_Pounce( gentity_t *self, int angle )	{ 
	BotLookUp( self, angle ); 
	BotAddMove( self, BOT_POUNCE, LEVEL3_POUNCE_TIME_UPG ); 
	BotStartMove( self );
}

//########### HUMAN SPECIFIC ################

//void BotFlyUp( gentity_t *self )	{ BotAddMove( self, BOT_RUN ); }
//void BotFlyDown( gentity_t *self )	{ BotAddMove( self, BOT_RUN ); }
void Bot_FullLuci( gentity_t *self )	{ 
	BotAddMove( self, BOT_FULL_LUCI, LCANNON_CHARGE_TIME_MAX - 500 ); 
	BotStartMove( self );
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
	BotStartMove( self );
}

