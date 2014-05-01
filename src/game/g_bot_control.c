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

//Private functions


/**
 * Perform bot movements (read from queue)
 * movement functions are declared in g_bot_control.c
 * @param self [gentity_t]
 */
void BotDoMove( gentity_t *self, int msec ) {
	int time;
	botMove move;
	
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
				self->bot->move.queue[ self->bot->move.read ].action = BOT_EMPTY_MOVE; //reset
				self->bot->move.queue[ self->bot->move.read ].time = 0; //reset
				self->bot->move.read++;
				if(self->bot->move.read == BOT_MOVE_QUEUE) {
					self->bot->move.read = 0;
				}
				self->bot->timer.move = 0;
			} else {
				self->bot->timer.move += msec;
			}
		}
	} else { //else reset to zero
		self->bot->timer.move = 0;
	}
}
/**
 * Adds a movement to the queue
 * @param self
 * @param move
 */
void BotAddMove( gentity_t *self, botMove move, int time ) {
	if(self->bot->move.queue[ self->bot->move.write ].action == BOT_EMPTY_MOVE) {
		self->bot->move.queue[ self->bot->move.write ].action = move;
		self->bot->move.queue[ self->bot->move.write ].time = time;
		self->bot->move.write++;
		if(self->bot->move.write == BOT_MOVE_QUEUE) {
			self->bot->move.write = 0;
		}
	} else {
		/* 
		 * Queue is not large enough or sometimes we are adding elements to the queue in a faster
		 * pace than we read them. Other reason is that we are adding a high time value to the queue, which
		 * fill the queue quickly. For example:
		 * if we add this: BotAddMove( self, BOT_MOVE_FWD, 10000 ); 
		 * Bots will move forward for 10 seconds. Meanwhile, other processes may be adding more movements to
		 * the queue reaching the limit. To prevent locking the queue, you can split the action in smaller parts.
		 */
		G_Printf("Movement dropped! Please set BOT_MOVE_QUEUE to a higher value or fix times --see BotAddMove()--.\n");
	}
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
 			self->client->ps.delta_angles[ 0 ] = self->client->ps.delta_angles[ 0 ] + ANGLE2SHORT( 45 ); //this makes bots to move aim in Z angles
			break;
		case BOT_GESTURE:
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
	G_BotDebug( BOT_VERB_DETAIL, BOT_DEBUG_CONTROL, "Movement: %d\n", move);
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
			self->client->pers.cmd.upmove = 0;
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
		case BOT_LOOK_UP:			
 			self->client->ps.delta_angles[ 0 ] = self->client->ps.delta_angles[ 0 ] - ANGLE2SHORT( BOT_TURN_VAL ); //this makes bots to move aim in Z angles
			break;
		case BOT_LOOK_DOWN: 		
 			self->client->ps.delta_angles[ 0 ] = self->client->ps.delta_angles[ 0 ] + ANGLE2SHORT( BOT_TURN_VAL ); //this makes bots to move aim in Z angles
			break;
		case BOT_LOOK_LEFT:			
			self->client->ps.delta_angles[ 1 ] = self->client->ps.delta_angles[ 1 ] + ANGLE2SHORT( BOT_TURN_VAL );
			break;
		case BOT_LOOK_RIGHT:		
			self->client->ps.delta_angles[ 1 ] = self->client->ps.delta_angles[ 1 ] - ANGLE2SHORT( BOT_TURN_VAL );
			break;
		case BOT_POUNCE:
			self->client->pers.cmd.buttons |= BUTTON_ATTACK2;
 			self->client->ps.delta_angles[ 0 ] = self->client->ps.delta_angles[ 0 ] - ANGLE2SHORT( 45 ); 
			break;
		case BOT_GESTURE:
			self->client->pers.cmd.buttons |= BUTTON_GESTURE;
			break;
		default:
			G_Printf("Invalid Bot Movement: %d\n", move);
			break;
	}
}
//------------------ PUBLIC FUNCTIONS -----------------
/*
 * These functions serve as shurtcut for: BotAddMove() 
 * to use custome timed actions use BotAddMove instead.
 */
void BotRun( gentity_t *self )		{ BotAddMove( self, BOT_RUN, BOT_MOVE_NO_TIME_LIMIT ); }
void BotJump( gentity_t *self )		{ BotAddMove( self, BOT_JUMP, 500 ); }
void BotStop( gentity_t *self )		{ BotAddMove( self, BOT_STOP, BOT_MOVE_NO_TIME_LIMIT ); }
void BotMoveRight( gentity_t *self ){ BotAddMove( self, BOT_MOVE_RIGHT, BOT_MOVE_NO_TIME_LIMIT ); }
void BotMoveLeft( gentity_t *self )	{ BotAddMove( self, BOT_MOVE_LEFT, BOT_MOVE_NO_TIME_LIMIT ); }
void BotMoveFwd( gentity_t *self )	{ BotAddMove( self, BOT_MOVE_FWD, BOT_MOVE_NO_TIME_LIMIT ); }
void BotMoveBack( gentity_t *self )	{ BotAddMove( self, BOT_MOVE_BACK, BOT_MOVE_NO_TIME_LIMIT ); }
void BotPounce( gentity_t *self )	{ BotLookUp( self, 45 ); BotAddMove( self, BOT_POUNCE, 2000 ); }
//void BotCharge( gentity_t *self )	{ BotAddMove( self, BOT_RUN, BOT_MOVE_NO_TIME_LIMIT ); }
void BotWallWalk( gentity_t *self )	{ BotAddMove( self, BOT_WALLWALK, BOT_MOVE_NO_TIME_LIMIT ); }
void BotCrouch( gentity_t *self )	{ BotAddMove( self, BOT_CROUCH, BOT_MOVE_NO_TIME_LIMIT ); }
void BotStand ( gentity_t *self )	{ BotAddMove( self, BOT_STAND, BOT_MOVE_NO_TIME_LIMIT ); }
void BotGesture ( gentity_t *self )	{ BotAddMove( self, BOT_GESTURE, 0 ); }
//void BotFlyUp( gentity_t *self )	{ BotAddMove( self, BOT_RUN, BOT_MOVE_NO_TIME_LIMIT ); }
//void BotFlyDown( gentity_t *self )	{ BotAddMove( self, BOT_RUN, BOT_MOVE_NO_TIME_LIMIT ); }

/*
 LOOK functions should be separated from Move QUEUE as they will make everything slower
 still I have to think a way to slow down the movement and prevent it from being instant
 */
void BotLookUp( gentity_t *self, int degrees )	 {
	int d;
	for(d = 0; d < (degrees / BOT_TURN_VAL); d++) {	
		BotAddMove( self, BOT_LOOK_UP, 10 ); 
	}
}
void BotLookDown( gentity_t *self, int degrees ) { 
	int d;
	for(d = 0; d < (degrees / BOT_TURN_VAL); d++) {	
		BotAddMove( self, BOT_LOOK_DOWN, 10 ); 
	}
}
void BotLookLeft( gentity_t *self, int degrees ) { 
	int d;
	for(d = 0; d < (degrees / BOT_TURN_VAL); d++) {	
		BotAddMove( self, BOT_LOOK_LEFT, 10 ); 
	}
}
void BotLookRight( gentity_t *self, int degrees ){ 
	int d;
	for(d = 0; d < (degrees / BOT_TURN_VAL); d++) {	
		BotAddMove( self, BOT_LOOK_RIGHT, 10 ); 
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
/*
static void Charge( gentity_t *self ) {


}

//########### HUMAN SPECIFIC ################

static void FlyUp( gentity_t *self ) {

}
static void FlyDown( gentity_t *self ) {

}
*/
//########### COMBOS ################
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
}
