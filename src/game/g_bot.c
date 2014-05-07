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
 * Mainly general commands to manage bots 
 */
#include "g_local.h"

/**
 * Add one bot into a team
 * @param name [string] bot's name
 * @param team [team_t] alien or human
 * @param skill [int] bot's skill (affects aim, reaction time, etc)
 * @param ignore [int] do not add it in X client number (unpractical, not really used)
 */
void G_BotAdd( char *name, team_t team, int skill, int ignore ) {
	int i;
	int clientNum;
	char userinfo[MAX_INFO_STRING];
	int reservedSlots = 0;
	gentity_t *ent;
    namelog_t *namelog;
    char name_s[ MAX_NAME_LENGTH ];
    char name_tmp_s[ MAX_NAME_LENGTH ];
	
	reservedSlots = trap_Cvar_VariableIntegerValue( "sv_privateclients" );

    // LEPE: check if no player/bot exists with that name	
    G_SanitiseString(name, name_s, sizeof(name_s) );
    for( namelog = level.namelogs; namelog; namelog = namelog->next ) {
        if( namelog->slot >= 0 ) {
            for( i = 0; i < MAX_NAMELOG_NAMES && namelog->name[ i ][ 0 ]; i++ ) {
                G_SanitiseString(namelog->name[ i ], name_tmp_s, sizeof(name_tmp_s) );
                if( i == namelog->nameOffset && namelog->slot > -1 && !strcmp( name_s, name_tmp_s ) ) {
                    trap_Print("Nick already exists\n");
                    return;
                }
            }
        }
    }
	// find what clientNum to use for bot
	// LEPE: clientNum calculation was modified to prevent player hijacking
        // We will assign slots from maxclients - 1 to maxclients - reservedSlots - 1
	clientNum = -1;
	for( i = level.maxclients - 1; i > level.maxclients - reservedSlots - 1; i-- ) {
		if( i == ignore )
		{continue;}
		if( !g_entities[i].inuse ) {
			clientNum = i;
			break;
		}
	}
	if(clientNum == -1)
	{
		trap_Print("Error: Bots were not assigned correctly\n"); //LEPE
		return;
	}
	if(clientNum < level.maxclients - reservedSlots - 1) 
	{
		trap_Print("no more slots for bot\n");
		return;
	}
	
	ent = &g_entities[ clientNum ];
	ent->inuse = qtrue;
	ent->bot = (bot_t *)BG_Alloc( sizeof(bot_t) );
//	ent->bot->path.crumb = BG_Alloc( sizeof(level.paths) );
	ent->bot->profile.skill = skill < 1 ? 1 : skill;
	
	ent->r.svFlags |= SVF_BOT;
    //LEPE: used in ant algorithm
    G_BotDebug(BOT_VERB_DETAIL, BOT_DEBUG_GENERAL + BOT_DEBUG_PATH, "Setting crumbs to 0\n");
	// register user information
	userinfo[0] = '\0';
	Info_SetValueForKey( userinfo, "name", name );
	Info_SetValueForKey( userinfo, "rate", "25000" ); //25000
	Info_SetValueForKey( userinfo, "snaps", "40" );
	//so we can connect if server is password protected
	if(g_needpass.integer == 1) {
		  Info_SetValueForKey( userinfo, "password", g_password.string);
	}
	trap_SetUserinfo( clientNum, userinfo );
	
	// have it connect to the game as a normal client
	if(ClientConnect(clientNum, qtrue) != NULL ) {
		// won't let us join
		return;
	}
// 	bot->r.svFlags |= SVF_BOT;
// 	bot->client->sess.spectatorState |= PM_SPECTATOR;
	ClientBegin( clientNum );
    G_BotDebug(BOT_VERB_IMPORTANT, BOT_DEBUG_GENERAL, "Bot Added: %s\n", name_s);
	G_ChangeTeam( ent, team );
	BotInit( ent );
    if(team == TEAM_HUMANS) {
		BotInitHuman( ent );
		level.humanBots++;
    } else if(team == TEAM_ALIENS) {
		BotInitAlien( ent );
		level.alienBots++;
	}
	//TODO: load profile
}
/**
 * Delete a specific bot
 * @param clientNum [int] bot client id
 */
void G_BotDel( int clientNum ) {
	gentity_t *ent;

	ent = &g_entities[clientNum];
	if( !( ent->r.svFlags & SVF_BOT ) ) {
		trap_Print( va("'^7%s^7' is not a bot\n", ent->client->pers.netname) );
		return;
	}
    G_BotDebug(BOT_VERB_IMPORTANT, BOT_DEBUG_GENERAL, "Bot deleted: %s\n", ent->client->pers.netname);
	ent->inuse = qfalse;
	//BG_Free(ent->bot->path.crumb); 
	BG_Free(ent->bot);
    //LEPE:
    if(ent->stageTeam == TEAM_HUMANS && level.humanBots > 0) {
        level.humanBots--;
    } else if(ent->stageTeam == TEAM_ALIENS && level.alienBots > 0) {
        level.alienBots--;
    }
	ClientDisconnect(clientNum);
}
/**
 * Deletes all bots
 */
void G_BotDelAll( void )
{
	int i;
	gentity_t *bot;
	bot = &g_entities[ 0 ];
	for( i = 0; i < level.maxclients; i++, bot++ )
	{
		if(bot->r.svFlags & SVF_BOT)  {
			G_BotDel(i);
		}
	}
}
/**
 * Removes and add again a Bot (unused?)
 * @param self [gentity_t] a BOT
 */
void G_BotReload( gentity_t *ent, int clientNum )
{
	ClientDisconnect( clientNum );
	G_BotAdd( ent->client->pers.netname, ent->client->pers.teamSelection, ent->bot->profile.skill, clientNum );
	trap_SendServerCommand( -1, "print \"Interfering bot reloaded\n\"" );
}
/**
 * Execute a command related to bots
 * @param master [gentity_t] player who executed the command
 * @param clientNum [int] bot client id
 * @param command [string] :
 *          - regular , idle , standground, followattack, etc. (change bot mode)
 *          - skill (change bot skill)
 * 			- kill (kill the bot)
 * 			- give (fund a bot)
 * @param value [int] skill value or give value (for aliens 500 is about 1 evo)
 * 
 * //TODO: bot modes will be removed
 */
void G_BotCmd( int clientNum, char *command, int value, int value2 ) {
  gentity_t *ent;
  
  ent = &g_entities[clientNum];
  if( !( ent->r.svFlags & SVF_BOT ) ) {
    return;
  }
  if( !Q_stricmp( command, "skill" ) ) {

    ent->bot->profile.skill = value;

  } else if( !Q_stricmp( command, "give" ) ) { //LEPE: give money/evos to ent

    G_AddCreditToClient( ent->client, (short)value, qfalse );

  } else if( !Q_stricmp( command, "kill" ) ) { //LEPE: kill ent

    ent->client->ps.stats[ STAT_HEALTH ] = ent->health = 0;
    player_die( ent, ent, ent, 10000, MOD_SUICIDE );
	
  } else if( !Q_stricmp( command, "state" ) ) { //LEPE: change bot state. Requires g_bot_manual = 1
	  
	  if(g_bot_manual.integer) {
	  	  ent->bot->think.state[ THINK_LEVEL_MAX ] = value;
	  }
	  
  } else if( !Q_stricmp( command, "nav" ) ) { //LEPE: change bot state. Requires g_bot_manual = 1
	  
	  if(g_bot_manual_nav.integer) {
	  	  ent->bot->path.state = value;
	  }
	  
  } else if( !Q_stricmp( command, "move" ) ) { //LEPE: move bot manually. Requires g_bot_manual = 1
	  
	  if(g_bot_manual.integer) {
		  if(value > BOT_EMPTY_MOVE && value <= BOT_STOP) {
		  	BotAddMove( ent, (botMove)value, value2 );
		  } else {
			  switch(value) {
				  case 20: BotLookUp( ent , value2 ); break;
				  case 21: BotLookDown( ent , value2 ); break;
				  case 22: BotLookLeft( ent , value2 ); break;
				  case 23: BotLookRight( ent , value2 ); break;
				  case 30: Bot_Strafe( ent ); break;
				  default:
		  	 		trap_SendServerCommand(-1, "print \"unknown move value\n\"");
					break;
			  } 
		  }
	  }
	  
  } else if( !Q_stricmp( command, "rawud" ) ) { //LEPE: up / down
	  
	  if(g_bot_manual.integer) {
	  	  ent->client->pers.cmd.upmove = value;
	  }
  } else if( !Q_stricmp( command, "rawlr" ) ) { //LEPE: left / right
	  
	  if(g_bot_manual.integer) {
	  	  ent->client->pers.cmd.rightmove = value;
	  }
  } else if( !Q_stricmp( command, "rawfb" ) ) { //LEPE: fwd / back
	  
	  if(g_bot_manual.integer) {
	  	  ent->client->pers.cmd.forwardmove = value;
	  }
	  
  } else {
	
    trap_SendServerCommand(-1, "print \"unknown command\n\"");
    
  }
  return;
}
