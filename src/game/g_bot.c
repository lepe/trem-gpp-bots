/*
===========================================================================
Copyright (C) 2007 Amine Haddad

This file is part of Tremulous.

The original works of vcxzet (lamebot3) were used a guide to create TremBot.

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
*/

/* Current version: v0.01 */

#include "g_local.h"

#ifndef RAND_MAX
#define RAND_MAX 32768
#endif

void G_BotReload( gentity_t *ent, int clientNum )
{
	ClientDisconnect( clientNum );
	G_BotAdd( ent->client->pers.netname, ent->client->pers.teamSelection, ent->botSkillLevel, clientNum );
	trap_SendServerCommand( -1, "print \"Interfering bot reloaded\n\"" );
}

void G_DeleteBots( void )
{
	int i;
	gentity_t *bot;
	bot = &g_entities[ 0 ];
	for( i = 0; i < level.maxclients; i++, bot++ )
	{
		if(bot->r.svFlags & SVF_BOT) 
		{ClientDisconnect(bot->client->ps.clientNum);}
	}
}

void G_BotAdd( char *name, team_t team, int skill, int ignore ) {
	int i;
	int clientNum;
	char userinfo[MAX_INFO_STRING];
	int reservedSlots = 0;
	gentity_t *bot;
	
	reservedSlots = trap_Cvar_VariableIntegerValue( "sv_privateclients" );
	
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
	if(clientNum < level.maxclients - reservedSlots - 1) {
		trap_Print("no more slots for bot\n");
		return;
	}
	
	bot = &g_entities[ clientNum ];
	bot->inuse = qtrue;
	
	//default bot data
	bot->botCommand = BOT_REGULAR;
	bot->botFriend = NULL;
	bot->botEnemy = NULL;
	bot->botFriendLastSeen = 0;
	bot->botEnemyLastSeen = 0;
	if(skill < 1){skill = 1;}
	bot->botSkillLevel = skill;
	bot->botTeam = team;
	bot->pathChosen = qfalse;
	bot->nextNode = qfalse;
	bot->state = FINDNEWPATH;
	bot->blocked = qfalse;
	bot->checktime = level.time;
	bot->patheditor = qfalse;
	bot->r.svFlags |= SVF_BOT;
	//ResetPaths(bot,0);
	/*
	for(i2 = 0;i2 < level.numPaths;i2++)
	{
		bot->OldPaths[i2].nextid[0] = -1;
		bot->OldPaths[i2].nextid[1] = -1;
		bot->OldPaths[i2].nextid[2] = -1;
		bot->OldPaths[i2].nextid[3] = -1;
		bot->OldPaths[i2].nextid[4] = -1;
		bot->SkipPaths[i2] = -1;
	}*/
	// register user information
	userinfo[0] = '\0';
	Info_SetValueForKey( userinfo, "name", name );
	Info_SetValueForKey( userinfo, "rate", "25000" ); //25000
	Info_SetValueForKey( userinfo, "snaps", "40" );

	trap_SetUserinfo( clientNum, userinfo );

	// have it connect to the game as a normal client
	if(ClientConnect(clientNum, qtrue) != NULL ) {
		// won't let us join
		return;
	}
// 	bot->r.svFlags |= SVF_BOT;
// 	bot->client->sess.spectatorState |= PM_SPECTATOR;
	ClientBegin( clientNum );
	Com_Printf("Bot added!\n");
	G_ChangeTeam( bot, team );
}

void G_BotDel( int clientNum ) {
	gentity_t *bot;

	bot = &g_entities[clientNum];
	if( !( bot->r.svFlags & SVF_BOT ) ) {
		trap_Print( va("'^7%s^7' is not a bot\n", bot->client->pers.netname) );
		return;
	}
	bot->inuse = qfalse;
	ClientDisconnect(clientNum);
}

void G_BotCmd( gentity_t *master, int clientNum, char *command, int skill ) {
  gentity_t *bot;
  
  bot = &g_entities[clientNum];
  if( !( bot->r.svFlags & SVF_BOT ) ) {
    return;
  }
  
  bot->botFriend = NULL;
  bot->botEnemy = NULL;
  bot->botFriendLastSeen = 0;
  bot->botEnemyLastSeen = 0;
  
  /*ROTAX
  if (g_ambush.integer >= 1)
  {
    trap_Print( va("You can't change aliens behavior during ambush mode\n") );
    return;
  }*/
  
  if( !Q_stricmp( command, "regular" ) ) {
	  
    bot->botCommand = BOT_REGULAR;
  	//trap_SendServerCommand(-1, "print \"regular mode\n\"");
  	
   } else if( !Q_stricmp( command, "idle" ) ) {
	   
    bot->botCommand = BOT_IDLE;
    //trap_SendServerCommand(-1, "print \"idle mode\n\"");
    
  } /*else if( !Q_stricmp( command, "attack" ) ) {
	  
    bot->botCommand = BOT_ATTACK;
    //trap_SendServerCommand(-1, "print \"attack mode\n\"");
    
  } */else if( !Q_stricmp( command, "standground" ) ) {
	  
    bot->botCommand = BOT_STAND_GROUND;
    //trap_SendServerCommand(-1, "print \"stand ground mode\n\"");
    
  }/* else if( !Q_stricmp( command, "defensive" ) ) {
	  
    bot->botCommand = BOT_DEFENSIVE;
    //trap_SendServerCommand(-1, "print \"defensive mode\n\"");
    
  } else if( !Q_stricmp( command, "followprotect" ) ) {
	  
    bot->botCommand = BOT_FOLLOW_FRIEND_PROTECT;
    bot->botFriend = master;
    //trap_SendServerCommand(-1, "print \"follow-protect mode\n\"");
    
  } */else if( !Q_stricmp( command, "followattack" ) ) {
	  
    bot->botCommand = BOT_FOLLOW_FRIEND_ATTACK;
    bot->botFriend = master;
    //trap_SendServerCommand(-1, "print \"follow-attack mode\n\"");
    
  } else if( !Q_stricmp( command, "followidle" ) ) {
	  
    bot->botCommand = BOT_FOLLOW_FRIEND_IDLE;
    bot->botFriend = master;
    //trap_SendServerCommand(-1, "print \"follow-idle mode\n\"");
    
  } else if( !Q_stricmp( command, "teamkill" ) ) {
	  
    bot->botCommand = BOT_TEAM_KILLER;
    
  } else if( !Q_stricmp( command, "skill" ) ) {
    bot->botSkillLevel = skill;
    //trap_SendServerCommand(-1, "print \"team kill mode\n\"");
    
  } else {
	
    bot->botCommand = BOT_REGULAR;
    //trap_SendServerCommand(-1, "print \"regular (unknown) mode\n\"");
    
  }
  
  return;
}

int distanceToTargetNode( gentity_t *self )
{
	int distance,Ax,Ay,Az,Bx,By,Bz = 0;
	Ax = level.paths[self->targetPath].coord[0];
	Ay = level.paths[self->targetPath].coord[1];
	Az = level.paths[self->targetPath].coord[2];
	Bx = self->s.pos.trBase[0];
	By = self->s.pos.trBase[1];
	Bz = self->s.pos.trBase[2];
	distance = sqrt((Ax - Bx)*(Ax - Bx) + (Ay - By)*(Ay - By) + (Az - Bz)*(Az - Bz));
	return distance;
}

qboolean botAimAtPath( gentity_t *self )
{
	vec3_t dirToTarget, angleToTarget;
	vec3_t top = { 0, 0, 0};
// 	int vh = 0;
// 	BG_FindViewheightForClass(  self->client->ps.stats[ STAT_CLASS ], &vh, NULL );
	top[2]=BG_ClassConfig( self->client->ps.stats[ STAT_CLASS ] )->viewheight;
	VectorAdd( self->s.pos.trBase, top, top);
	VectorSubtract( level.paths[self->targetPath].coord, top, dirToTarget );
	VectorNormalize( dirToTarget );
	vectoangles( dirToTarget, angleToTarget );
 	self->client->ps.delta_angles[ 0 ] = ANGLE2SHORT( angleToTarget[ 0 ] );
	self->client->ps.delta_angles[ 1 ] = ANGLE2SHORT( angleToTarget[ 1 ] );
	return qtrue;
}

void G_FrameAim( gentity_t *self )
{
	if(!( self->r.svFlags & SVF_BOT ) || self->client->ps.stats[ STAT_CLASS ] == PCL_NONE)
	{
		return;
	}
	if(self->botEnemy && self->botEnemy->health <= 0)
		self->botEnemy = NULL;
	/*else
	{
		if(botTargetInRange( self, self->botEnemy ) == qfalse)
		{
			self->botEnemy = NULL;
		}
	}*/
	if(self->botFriend && self->botFriend->health <= 0)
		self->botFriend = NULL;
	/*else
	{
		if(botTargetInRange( self, self->botFriend ) == qfalse)
		{
			self->botFriend = NULL;
		}
	}*/
	if(self->botFriend->health <= 0)
		self->botFriend = NULL;
	if(!self->botEnemy && !self->botFriend && self->state == TARGETPATH && level.time - self->enemytime > 2500)
	{
		botAimAtPath(self);
	}
	else if(self->botEnemy)
	{
		botAimAtTarget(self, self->botEnemy);
	}
	else if(self->botFriend)
	{
		botAimAtTarget(self, self->botFriend);
	}
}

void G_FastThink( gentity_t *self )
{
	int forwardMove = 127;
	if( !( self->r.svFlags & SVF_BOT ) || self->client->ps.stats[ STAT_CLASS ] == PCL_NONE)
	{
		return;
	}
	if(self->botEnemy)
	{
		botShootIfTargetInRange(self,self->botEnemy);
		/*if(botTargetInRange( self, self->botEnemy ) == qfalse)
		{
			self->botEnemy = NULL;
		}*/
		self->enemytime = level.time;
	}
	if(self->botFriend)
	{
		if(botTargetInRange( self, self->botFriend ) == qfalse)
		{
			self->botFriend = NULL;
		}
		self->enemytime = level.time;
	}
	if(!self->botEnemy && !self->botFriend && self->state == TARGETPATH && level.time - self->enemytime > 2500)
	{
		self->client->pers.cmd.buttons = 0;
		self->client->pers.cmd.upmove = 0;
		self->client->pers.cmd.rightmove = 0;
		if((self->isblocked == qtrue || 
			VectorLength( self->client->ps.velocity ) < 50.0f) && level.time - self->enemytime > 1000)
		{
			self->client->pers.cmd.buttons |= BUTTON_GESTURE;
			self->client->pers.cmd.rightmove = -100;
  			if(self->client->time1000 >= 500)
  			{
				self->client->pers.cmd.rightmove = 100;
			}
			if(level.time - self->jumptime > 3000 &&
				(( self->client->ps.stats[ STAT_TEAM ] == TEAM_HUMANS && self->client->ps.stats[ STAT_STAMINA ] > 0 ) ||
				self->client->ps.stats[ STAT_TEAM ] == TEAM_ALIENS))
			{
				self->client->pers.cmd.upmove = 20;
				if(level.time - self->jumptime > 4000)
				self->jumptime = level.time;
			}
		}
		self->client->pers.cmd.forwardmove = forwardMove;
		if(self->lastpathid >= 0)
		{
			switch(level.paths[self->lastpathid].action)
			{
				case BOT_WALLCLIMB: if( BG_ClassHasAbility( self->client->ps.stats[ STAT_CLASS ], SCA_WALLCLIMBER ) ) { //LEPE: before BOT_JUMP
							self->client->pers.cmd.upmove = -1;
							}
							break;
				case BOT_JUMP:	if(level.time - self->jumptime > 3000)
						{
							if( self->client->ps.stats[ STAT_TEAM ] == TEAM_HUMANS && 
								self->client->ps.stats[ STAT_STAMINA ] < 0 )
							{break;}
							self->client->pers.cmd.upmove = 20;
							if(level.time - self->jumptime > 4000)
							self->jumptime = level.time;
						}
						break;
				case BOT_KNEEL: if(self->client->ps.stats[ STAT_TEAM ] == TEAM_HUMANS)
						{
							self->client->pers.cmd.upmove = -1;
						}
						break;
				case BOT_POUNCE:if(self->client->pers.classSelection == PCL_ALIEN_LEVEL3 && 
							self->client->ps.stats[ STAT_MISC ] < LEVEL3_POUNCE_JUMP_MAG)
							self->client->pers.cmd.buttons |= BUTTON_ATTACK2;
						else if(self->client->pers.classSelection == PCL_ALIEN_LEVEL3_UPG && 
							self->client->ps.stats[ STAT_MISC ] < LEVEL3_POUNCE_JUMP_MAG_UPG)
							self->client->pers.cmd.buttons |= BUTTON_ATTACK2;
						break;
				default: break;
			}
			if(level.time - self->timeFoundPath > level.paths[self->lastpathid].timeout)
			{
				self->state = FINDNEWPATH;
				self->timeFoundPath = level.time;
			}
		}
		else if( level.time - self->timeFoundPath > 10000 )
		{
			self->state = FINDNEWPATH;
			self->timeFoundPath = level.time;
		}
		if(distanceToTargetNode(self) < 70)
		{
			self->state = FINDNEXTPATH;
			self->timeFoundPath = level.time;
		}
		if(self->client->ps.stats[ STAT_TEAM ] == TEAM_HUMANS && 
			self->client->ps.stats[ STAT_STAMINA ] < 100 && 
			level.time - self->jumptime > 3000)
		{
			self->client->pers.cmd.upmove = -1;
			self->client->pers.cmd.buttons = 0;
			self->client->pers.cmd.rightmove = 0;
			self->client->pers.cmd.forwardmove = 0;
			self->enemytime = level.time;
			self->timeFoundPath += 100;
		}
	}
	//else if(!self->botEnemy && !self->botFriend && self->state == LOST)
	//{
		//Run around wild?
	//}
}

void findnewpath( gentity_t *self )
{
	trace_t trace;
	int i,distance,Ax,Ay,Az,Bx,By,Bz = 0;
	int closestpath = 0;
	int closestpathdistance = 2000;
	qboolean pathfound = qfalse;
	self->lastpathid = -1;
	for(i = 0; i < level.numPaths; i++) //find a nearby path that wasn't used before
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
		if(distance < 5000)
		{
			if(closestpathdistance > distance)
			{
				closestpath = i;
				closestpathdistance = distance;
				pathfound = qtrue;
			}
		}
	}
	if(pathfound == qtrue)
	{
		self->targetPath = closestpath;
		self->timeFoundPath = level.time;
		self->state = TARGETPATH;
		self->isblocked = qfalse;
	}
	else
	{
		self->state = LOST;
		self->client->pers.cmd.forwardmove = 0;
		self->client->pers.cmd.upmove = -1;
		self->client->pers.cmd.rightmove = 0;
		self->client->pers.cmd.buttons = 0;
		self->client->pers.cmd.buttons |= BUTTON_GESTURE;
	}
	return;
}

void findnextpath( gentity_t *self )
{
	int randnum = 0;
	int i,nextpath = 0;
	int possiblenextpath = 0;
	int possiblepaths[5];
	int lasttarget = self->targetPath;
	possiblepaths[0] = possiblepaths[1] = possiblepaths[2] = possiblepaths[3] = possiblepaths[4] = 0;
	for(i = 0; i < 5; i++)
	{
		if(level.paths[self->targetPath].nextid[i] < level.numPaths &&
			level.paths[self->targetPath].nextid[i] >= 0)
		{
			if(self->lastpathid >= 0)
			{
				if(self->lastpathid == level.paths[self->targetPath].nextid[i])
				{
					continue;
				}
			}
			possiblepaths[possiblenextpath] = level.paths[self->targetPath].nextid[i];
			possiblenextpath++;
		}
	}
	if(possiblenextpath == 0)
	{	
		self->state = FINDNEWPATH;
		return;
	}
	else
	{
		self->state = TARGETPATH;
		if(level.paths[self->targetPath].random < 0)
		{
			nextpath = 0;
		}
		else
		{
			srand( trap_Milliseconds( ) );
			randnum = (int)(( (double)rand() / ((double)(RAND_MAX)+(double)(1)) ) * possiblenextpath);
			nextpath = randnum;
			//if(nextpath == possiblenextpath)
			//{nextpath = possiblenextpath - 1;}
		}
		self->lastpathid = self->targetPath;
		self->targetPath = possiblepaths[nextpath];
		for(i = 0;i < 5;i++)
		{
			if(level.paths[self->targetPath].nextid[i] == lasttarget)
			{
				i = 5;
			}
		}

		self->timeFoundPath = level.time;
		return;
	}
	return;
}

void pathfinding( gentity_t *self )
{
	switch(self->state)
	{
		case FINDNEWPATH: findnewpath(self); break;
		case FINDNEXTPATH: findnextpath(self); break;
		case TARGETPATH: break; //done in G_FrameThink
		case LOST: findnewpath(self);break; //LOL :(
		default: break;
	}
}

void Bot_Buy( gentity_t *self )
{
	qboolean boughtweap = qfalse;
	//qboolean boughtup = qfalse;
	qboolean buybatt = qfalse;
	qboolean energyweap = qfalse;
	weapon_t weapon;
	upgrade_t upgrade;
	//int maxAmmo, maxClips;
	int clientNum = self->client - level.clients;
	if(self->client->ps.stats[ STAT_TEAM ] != TEAM_HUMANS){return;}
	upgrade = UP_LIGHTARMOUR;
	if(BG_InventoryContainsUpgrade( upgrade, self->client->ps.stats ))
	{
		BG_RemoveUpgradeFromInventory( upgrade, self->client->ps.stats );
		G_AddCreditToClient( self->client, (short)BG_Upgrade( upgrade )->price, qfalse );
	}
	upgrade = UP_HELMET;
	if(BG_InventoryContainsUpgrade( upgrade, self->client->ps.stats ))
	{
		BG_RemoveUpgradeFromInventory( upgrade, self->client->ps.stats );
		G_AddCreditToClient( self->client, (short)BG_Upgrade( upgrade )->price, qfalse );
	}
	upgrade = UP_BATTPACK;
	if(BG_InventoryContainsUpgrade( upgrade, self->client->ps.stats ))
	{
		BG_RemoveUpgradeFromInventory( upgrade, self->client->ps.stats );
		G_AddCreditToClient( self->client, (short)BG_Upgrade( upgrade )->price, qfalse );
	}
	weapon = WP_MACHINEGUN;
	if( BG_InventoryContainsWeapon( weapon, self->client->ps.stats ) )
	{
		self->client->ps.stats[ STAT_WEAPON ] = WP_NONE;
		self->client->ps.stats[ STAT_WEAPON ] = WP_NONE;
		//G_AddCreditToClient( self->client, (short)BG_Weapon( weapon )->price, qfalse );
	}
	weapon = WP_CHAINGUN;
	if( BG_InventoryContainsWeapon( weapon, self->client->ps.stats ) )
	{
		self->client->ps.stats[ STAT_WEAPON ] = WP_NONE;
		G_AddCreditToClient( self->client, (short)BG_Weapon( weapon )->price, qfalse );
	}
	weapon = WP_LAS_GUN;
	if( BG_InventoryContainsWeapon( weapon, self->client->ps.stats ) )
	{
		self->client->ps.stats[ STAT_WEAPON ] = WP_NONE;
		G_AddCreditToClient( self->client, (short)BG_Weapon( weapon )->price, qfalse );
	}
	weapon = WP_LUCIFER_CANNON;
	if( BG_InventoryContainsWeapon( weapon, self->client->ps.stats ) )
	{
		self->client->ps.stats[ STAT_WEAPON ] = WP_NONE;
		G_AddCreditToClient( self->client, (short)BG_Weapon( weapon )->price, qfalse );
	}
	weapon = WP_FLAMER;
	if( BG_InventoryContainsWeapon( weapon, self->client->ps.stats ) )
	{
		self->client->ps.stats[ STAT_WEAPON ] = WP_NONE;
		G_AddCreditToClient( self->client, (short)BG_Weapon( weapon )->price, qfalse );
	}
	weapon = WP_PULSE_RIFLE;
	if( BG_InventoryContainsWeapon( weapon, self->client->ps.stats ) )
	{
		self->client->ps.stats[ STAT_WEAPON ] = WP_NONE;
		G_AddCreditToClient( self->client, (short)BG_Weapon( weapon )->price, qfalse );
	}
	weapon = WP_MASS_DRIVER;
	if( BG_InventoryContainsWeapon( weapon, self->client->ps.stats ) )
	{
		self->client->ps.stats[ STAT_WEAPON ] = WP_NONE;
		G_AddCreditToClient( self->client, (short)BG_Weapon( weapon )->price, qfalse );
	}
	weapon = WP_SHOTGUN;
	if( BG_InventoryContainsWeapon( weapon, self->client->ps.stats ) )
	{
		self->client->ps.stats[ STAT_WEAPON ] = WP_NONE;
		G_AddCreditToClient( self->client, (short)BG_Weapon( weapon )->price, qfalse );
	}
	weapon = WP_PAIN_SAW;
	if( BG_InventoryContainsWeapon( weapon, self->client->ps.stats ) )
	{
		self->client->ps.stats[ STAT_WEAPON ] = WP_NONE;
		G_AddCreditToClient( self->client, (short)BG_Weapon( weapon )->price, qfalse );
	}
	if(g_humanStage.integer == 2)
	{
		upgrade = UP_BATTLESUIT;
		if(!BG_InventoryContainsUpgrade( upgrade, self->client->ps.stats ) && 
			BG_Upgrade( upgrade )->price <= (short)self->client->ps.persistant[ PERS_CREDIT ] &&
			!(BG_Weapon( upgrade )->slots & BG_SlotsForInventory( self->client->ps.stats )))
		{
			BG_AddUpgradeToInventory( upgrade, self->client->ps.stats );
			G_AddCreditToClient( self->client, -(short)BG_Upgrade( upgrade )->price, qfalse );
		}
	}
	upgrade = UP_LIGHTARMOUR;
	if(!BG_InventoryContainsUpgrade( upgrade, self->client->ps.stats ) && 
		BG_Upgrade( upgrade )->price <= (short)self->client->ps.persistant[ PERS_CREDIT ] &&
		!(BG_Weapon( upgrade )->slots & BG_SlotsForInventory( self->client->ps.stats )) && 
		!BG_InventoryContainsUpgrade( UP_BATTLESUIT, self->client->ps.stats ))
	{
		BG_AddUpgradeToInventory( upgrade, self->client->ps.stats );
		G_AddCreditToClient( self->client, -(short)BG_Upgrade( upgrade )->price, qfalse );
	}
	if(g_humanStage.integer == 1)
	{
		upgrade = UP_HELMET;
		if(!BG_InventoryContainsUpgrade( upgrade, self->client->ps.stats ) && 
			BG_Upgrade( upgrade )->price <= (short)self->client->ps.persistant[ PERS_CREDIT ] &&
			!(BG_Weapon( upgrade )->slots & BG_SlotsForInventory( self->client->ps.stats )) && 
			!BG_InventoryContainsUpgrade( UP_BATTLESUIT, self->client->ps.stats ))
		{
			BG_AddUpgradeToInventory( upgrade, self->client->ps.stats );
			G_AddCreditToClient( self->client, -(short)BG_Upgrade( upgrade )->price, qfalse );
		}
	}
	if(g_humanStage.integer == 2 && g_bot_lcannon.integer > 0)
	{
		weapon = WP_LUCIFER_CANNON;
		if( !BG_InventoryContainsWeapon( weapon, self->client->ps.stats ) &&
			BG_Weapon( weapon )->price <= (short)self->client->ps.persistant[ PERS_CREDIT ] &&
			!(BG_Weapon( weapon )->slots & BG_SlotsForInventory( self->client->ps.stats )))
		{
			boughtweap = qtrue;
			buybatt = qtrue;
			energyweap = qtrue;
		}
	}
	if(g_humanStage.integer == 1 && boughtweap == qfalse && g_bot_flamer.integer > 0)
	{
		weapon = WP_FLAMER;
		if( !BG_InventoryContainsWeapon( weapon, self->client->ps.stats ) &&
			BG_Weapon( weapon )->price <= (short)self->client->ps.persistant[ PERS_CREDIT ] &&
			!(BG_Weapon( weapon )->slots & BG_SlotsForInventory( self->client->ps.stats )))
		{
			boughtweap = qtrue;
		}
	}
	if(g_humanStage.integer == 1 && boughtweap == qfalse && g_bot_prifle.integer > 0)
	{
		weapon = WP_PULSE_RIFLE;
		if( !BG_InventoryContainsWeapon( weapon, self->client->ps.stats ) &&
			BG_Weapon( weapon )->price <= (short)self->client->ps.persistant[ PERS_CREDIT ] &&
			!(BG_Weapon( weapon )->slots & BG_SlotsForInventory( self->client->ps.stats )))
		{
			boughtweap = qtrue;
			buybatt = qtrue;
			energyweap = qtrue;
		}
	}
	if(boughtweap == qfalse && g_bot_chaingun.integer > 0)
	{
		weapon = WP_CHAINGUN;
		if( !BG_InventoryContainsWeapon( weapon, self->client->ps.stats ) &&
			BG_Weapon( weapon )->price <= (short)self->client->ps.persistant[ PERS_CREDIT ] &&
			!(BG_Weapon( weapon )->slots & BG_SlotsForInventory( self->client->ps.stats )))
		{
			boughtweap = qtrue;
		}
	}
	if(boughtweap == qfalse && g_bot_mdriver.integer > 0)
	{
		weapon = WP_MASS_DRIVER;
		if( !BG_InventoryContainsWeapon( weapon, self->client->ps.stats ) &&
			BG_Weapon( weapon )->price <= (short)self->client->ps.persistant[ PERS_CREDIT ] &&
			!(BG_Weapon( weapon )->slots & BG_SlotsForInventory( self->client->ps.stats )))
		{
			boughtweap = qtrue;
			buybatt = qtrue;
			energyweap = qtrue;
		}
	}
	if(boughtweap == qfalse && g_bot_lasgun.integer > 0)
	{
		weapon = WP_LAS_GUN;
		if( !BG_InventoryContainsWeapon( weapon, self->client->ps.stats ) &&
			BG_Weapon( weapon )->price <= (short)self->client->ps.persistant[ PERS_CREDIT ] &&
			!(BG_Weapon( weapon )->slots & BG_SlotsForInventory( self->client->ps.stats )))
		{
			boughtweap = qtrue;
			buybatt = qtrue;
			energyweap = qtrue;
		}
	}
	if(boughtweap == qfalse && g_bot_shotgun.integer > 0)
	{
		weapon = WP_SHOTGUN;
		if( !BG_InventoryContainsWeapon( weapon, self->client->ps.stats ) &&
			BG_Weapon( weapon )->price <= (short)self->client->ps.persistant[ PERS_CREDIT ] &&
			!(BG_Weapon( weapon )->slots & BG_SlotsForInventory( self->client->ps.stats )))
		{
			boughtweap = qtrue;
		}
	}
	if(boughtweap == qfalse && g_bot_psaw.integer > 0)
	{
		weapon = WP_PAIN_SAW;
		if( !BG_InventoryContainsWeapon( weapon, self->client->ps.stats ) &&
			BG_Weapon( weapon )->price <= (short)self->client->ps.persistant[ PERS_CREDIT ] &&
			!(BG_Weapon( weapon )->slots & BG_SlotsForInventory( self->client->ps.stats )))
		{
			boughtweap = qtrue;
		}
	}
	if(boughtweap == qfalse && g_bot_mgun.integer > 0)
	{
		weapon = WP_MACHINEGUN;
		if( !BG_InventoryContainsWeapon( weapon, self->client->ps.stats ) &&
			BG_Weapon( weapon )->price <= (short)self->client->ps.persistant[ PERS_CREDIT ] &&
			!(BG_Weapon( weapon )->slots & BG_SlotsForInventory( self->client->ps.stats )))
		{
			boughtweap = qtrue;
		}
	}
	if(boughtweap == qtrue)
	{
// 		BG_AddWeaponToInventory( weapon, self->client->ps.stats );
		self->client->ps.stats[ STAT_WEAPON ] = weapon;
		self->client->ps.ammo = BG_Weapon( weapon )->maxAmmo;
		self->client->ps.clips = BG_Weapon( weapon )->maxClips;
		G_AddCreditToClient( self->client, -(short)BG_Weapon( weapon )->price, qfalse );
		G_ForceWeaponChange( self, weapon );
	}
	else
	{
		weapon = WP_BLASTER;
		G_ForceWeaponChange( self, weapon );
	}
	upgrade = UP_BATTPACK;
	if(!BG_InventoryContainsUpgrade( upgrade, self->client->ps.stats ) && 
		BG_Upgrade( upgrade )->price <= (short)self->client->ps.persistant[ PERS_CREDIT ] &&
		!(BG_Weapon( upgrade )->slots & BG_SlotsForInventory( self->client->ps.stats )) && 
		!BG_InventoryContainsUpgrade( UP_BATTLESUIT, self->client->ps.stats ) && 
		buybatt == qtrue)
	{
		BG_AddUpgradeToInventory( upgrade, self->client->ps.stats );
		G_AddCreditToClient( self->client, -(short)BG_Upgrade( upgrade )->price, qfalse );
	}
	else
	{buybatt = qfalse;}
	G_GiveClientMaxAmmo( self, energyweap );
	/*
	BG_FindAmmoForWeapon( self->s.weapon, &maxAmmo, &maxClips );
	if( BG_FindUsesEnergyForWeapon( self->s.weapon ) && buybatt )
	{
		maxAmmo = (int)( (float)maxAmmo * BATTPACK_MODIFIER );
	}
	BG_PackAmmoArray( self->s.weapon, self->client->ps.ammo, self->client->ps.powerups, maxAmmo, maxClips );*/
	//if(boughtup == qtrue || boughtweap == qtrue)
	//{ClientUserinfoChanged( clientNum );}
	ClientUserinfoChanged( clientNum, qfalse );
	self->buytime = level.time;
	return;
}


void Bot_Evolve( gentity_t *self )
{
	vec3_t origin;
	qboolean classfound = qfalse;
	class_t class = PCL_NONE;
	int levels;
	int clientNum;
	qboolean lowclass = qfalse;
	if(self->client->ps.stats[ STAT_TEAM ] != TEAM_ALIENS){return;}
	clientNum = self->client - level.clients;
	self->evolvetime = level.time;
// 	if(g_ambush.integer > 0)
// 	{
// 		classfound = qtrue;
// 		if(self->client->ps.stats[ STAT_CLASS ] == PCL_ALIEN_BUILDER0)
// 		{
// 			int randclass = 0;
// 			int randmax = 0;
// 			srand( trap_Milliseconds( ) );
// 			randmax = g_ambush_stage.integer;
// 			if(randmax > 9){randmax = 9;}
// 			/*switch(g_ambush_stage.integer)
// 			{ 
// 				case 1:case 2:case 3:return;break;
// 				case 4:case 5:case 6:randmax = 1;break;
// 				case 7:case 8:case 9:randmax = 2;break;
// 				case 10:case 11:case 12:randmax = 3;break;
// 				case 13:case 14:case 15:randmax = 4;break;
// 				case 16:case 17:case 18:randmax = 5;break;
// 				case 19:case 20:case 21:randmax = 6;break;
// 				case 22:case 23:case 24:randmax = 7;break;
// 				case 25:case 26:case 27:randmax = 8;break;
// 				case 28:case 29:case 30:randmax = 9;break;
// 				case 31:case 32:case 33:case 34:randmax = 9;break;
// 				default: randmax = 9; break;
// 			}*/
// 			randclass = (int)(( (double)rand() / ((double)(RAND_MAX)+(double)(1)) ) * randmax);
// 			switch(randclass)
// 			{
// 				case 0:class = PCL_ALIEN_BUILDER0_UPG;break;
// 				case 1:class = PCL_ALIEN_LEVEL0;break;
// 				case 2:class = PCL_ALIEN_LEVEL1;break;
// 				case 3:class = PCL_ALIEN_LEVEL1_UPG;break;
// 				case 4:class = PCL_ALIEN_LEVEL2;break;
// 				case 5:class = PCL_ALIEN_LEVEL2_UPG;break;
// 				case 6:class = PCL_ALIEN_LEVEL3;break;
// 				case 7:class = PCL_ALIEN_LEVEL3_UPG;break;
// 				case 8:class = PCL_ALIEN_LEVEL4;break;
// 				default:class = PCL_ALIEN_LEVEL4;break;
// 			}
// 			classfound = qtrue;
// 		}
// 		else{classfound = qfalse;}
// 		if(classfound == qtrue)
// 		{
// 			if(!G_RoomForClassChange( self, class, origin ))
// 			{return;}
// 			lowclass = qtrue;
// 		}
// 		else if(classfound == qfalse && g_bot_evolve.integer <= 0)
// 		{
// 			return;
// 		}
// 	}
	if(classfound == qfalse)
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
	if(classfound == qfalse)
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
	if(classfound == qfalse)
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
	if(classfound == qfalse)
	{
		class = PCL_ALIEN_LEVEL2_UPG;
 		
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
	if(classfound == qfalse)
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
	if(classfound == qfalse)
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
	if(classfound == qfalse)
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
		self->evolvetime = level.time;
		self->client->pers.cmd.buttons = 0;
		self->client->pers.cmd.upmove = 0;
		self->client->pers.cmd.rightmove = 0;
		return;
	}
	self->evolvetime = level.time;
	return;
}


void G_BotThink( gentity_t *self )
{
	int distance = 0;
	int clicksToStopChase = 30; //5 seconds
	int tooCloseDistance = 100; // about 1/3 of turret range
	int forwardMove = 127; // max speed
	int tempEntityIndex = -1;
	//int maxAmmo, maxClips,i;
	int ammo,clips;
	trace_t   tr;
	vec3_t    end;
	vec3_t    mins, maxs;
	vec3_t  forward, right, up;
	vec3_t  muzzle;
	gentity_t *traceEnt;
	qboolean followFriend = qfalse;
	if( !( self->r.svFlags & SVF_BOT ) || self->client->ps.stats[ STAT_CLASS ] == PCL_NONE )
	{
		return;
	}
	self->isblocked = qfalse;
	if(self->state == TARGETPATH && !self->botEnemy && !self->botFriend && level.time - self->enemytime > 2500)
	{
		//AngleVectors( self->client->ps.viewangles, forward, right, up );
		//CalcMuzzlePoint( self, forward, right, up, muzzle );
		VectorSet( mins, -20, -20, -20 );
		VectorSet( maxs, 20, 20, 20 );
		AngleVectors( self->client->ps.viewangles, forward, right, up );
		CalcMuzzlePoint( self, forward, right, up, muzzle );
		VectorMA( muzzle, 20, forward, end );
		trap_Trace( &tr, muzzle, mins, maxs, end, self->s.number, MASK_SHOT );
		traceEnt = &g_entities[ tr.entityNum ];
		
// 		if(traceEnt->health > 0)
		if( (float)Distance( self->client->oldOrigin, self->r.currentOrigin ) < 2.3 )
		{
		  self->isblocked = qtrue;
		  self->state = FINDNEWPATH;
		}
		else
		{self->isblocked = qfalse;}
	}
	if(self->botEnemy || self->botFriend)
	{
		//self->client->pers.cmd.buttons = 0;
		self->client->pers.cmd.forwardmove = 0;
		self->client->pers.cmd.upmove = 0;
		self->client->pers.cmd.rightmove = 0;
		self->timeFoundPath = level.time;
	}
	// reset botEnemy if enemy is dead
	if(self->botEnemy->health <= 0) {
		self->botEnemy = NULL;
	}
	else if(level.time - self->checktime > 3000)
	{
		self->checktime = level.time;
		if(botTargetInRange( self, self->botEnemy ) == qfalse)
		{
			self->botEnemy = NULL;
		}
	}
	// if friend dies, reset status to regular
	if(self->botFriend->health <= 0) {
		self->botCommand = BOT_REGULAR;
		self->botFriend = NULL;
	}
	//LEPE: uncommented this IF
	//Use blaster if weapon out of ammo. self->s.weapon is current weapon that might not be out.
 	if(self->client->ps.stats[ STAT_TEAM ] == TEAM_HUMANS && 
 		self->client->ps.weapon != WP_BLASTER && 
 		self->client->ps.weapon != WP_PAIN_SAW && 
 		self->client->ps.weapon != WP_GRENADE && 
 		level.time - self->buytime > 1000)
 	{
 // 		BG_UnpackAmmoArray( self->client->ps.weapon, self->client->ps.ammo, self->client->ps.powerups, &ammo, &clips );
 		if(self->client->ps.ammo <= 0 && self->client->ps.clips <= 0)
 		{
 			G_ForceWeaponChange( self, WP_BLASTER );
 		}
 		//G_Say( self, NULL, SAY_TEAM, "OMG I NEEDS AMMOH!!!");
 	}
	//Use medkit if low hp
	if(self->client->ps.stats[ STAT_TEAM ] == TEAM_HUMANS && 
		BG_InventoryContainsUpgrade( UP_MEDKIT, self->client->ps.stats ) &&
		self->health <= 40)
	{BG_ActivateUpgrade( UP_MEDKIT, self->client->ps.stats );}

	//Buy stuff from arm if within range
	if(G_BuildableRange( self->client->ps.origin, 100, BA_H_ARMOURY ) && 
		self->client->ps.stats[ STAT_TEAM ] == TEAM_HUMANS &&
		level.time - self->buytime > 5000)
	{
		Bot_Buy(self);
	}
	if( self->client->ps.stats[ STAT_TEAM ] == TEAM_HUMANS && 
		(G_BuildableRange( self->client->ps.origin, 100, BA_H_REACTOR ) ||
		G_BuildableRange( self->client->ps.origin, 100, BA_H_REPEATER )) && 
		level.time - self->buytime > 6000)
	{
		G_GiveClientMaxAmmo( self, qtrue );
		self->buytime = level.time;
	}
 	if(self->client->ps.stats[ STAT_TEAM ] == TEAM_ALIENS &&
 		level.time - self->evolvetime > 500)
 	{Bot_Evolve(self);}
	if(self->client->ps.stats[ STAT_TEAM ] == TEAM_HUMANS)
	{
		if(self->client->ps.weapon == WP_MACHINEGUN && g_bot_mgun.integer <= 0)
		{
			G_ForceWeaponChange( self, WP_BLASTER );
		}
		if(self->client->ps.weapon == WP_SHOTGUN && g_bot_shotgun.integer <= 0)
		{
			G_ForceWeaponChange( self, WP_BLASTER );
		}
		if(self->client->ps.weapon == WP_PAIN_SAW && g_bot_psaw.integer <= 0)
		{
			G_ForceWeaponChange( self, WP_BLASTER );
		}
		if(self->client->ps.weapon == WP_LAS_GUN && g_bot_lasgun.integer <= 0)
		{
			G_ForceWeaponChange( self, WP_BLASTER );
		}
		if(self->client->ps.weapon == WP_MASS_DRIVER && g_bot_mdriver.integer <= 0)
		{
			G_ForceWeaponChange( self, WP_BLASTER );
		}
		if(self->client->ps.weapon == WP_PULSE_RIFLE && g_bot_prifle.integer <= 0)
		{
			G_ForceWeaponChange( self, WP_BLASTER );
		}
		if(self->client->ps.weapon == WP_FLAMER && g_bot_flamer.integer <= 0)
		{
			G_ForceWeaponChange( self, WP_BLASTER );
		}
		if(self->client->ps.weapon == WP_LUCIFER_CANNON && g_bot_lcannon.integer <= 0)
		{
			G_ForceWeaponChange( self, WP_BLASTER );
		}
		if(self->client->ps.weapon == WP_CHAINGUN && g_bot_chaingun.integer <= 0)
		{
			G_ForceWeaponChange( self, WP_BLASTER );
		}
	}
	// what mode are we in?
	switch(self->botCommand) {
		case BOT_REGULAR:
			// if there is enemy around, rush them and attack.
			if(self->botEnemy) {
				// we already have an enemy. See if still in LOS.
				if(!botTargetInRange(self,self->botEnemy)) {
					// if it's been over clicksToStopChase clicks since we last seen him in LOS then do nothing, else follow him!
					if(self->botEnemyLastSeen > clicksToStopChase) {
						// forget him!
						self->botEnemy = NULL;
						self->botEnemyLastSeen = 0;
					} else {
						//chase him
						self->botEnemyLastSeen++;
					}
				} else {
					// we see him!
					self->botEnemyLastSeen = 0;
				}
			}
			
			if(!self->botEnemy) {
				// try to find closest enemy
				if(level.time - self->searchtime >  self->botSkillLevel)
				{
					self->searchtime = level.time;
					self->checktime = level.time;
					tempEntityIndex = botFindClosestEnemy(self, qfalse);
					if(tempEntityIndex >= 0)
						self->botEnemy = &g_entities[tempEntityIndex];
				}
			}
			
			if(!self->botEnemy) {
				pathfinding(self); //Roam the map!!!
			} else {
				self->timeFoundPath = level.time;
// 				self->state = FINDNEWPATH;
				// enemy!
				distance = botGetDistanceBetweenPlayer(self, self->botEnemy);
				//botAimAtTarget(self, self->botEnemy);
				
				// enable wallwalk
				if( BG_ClassHasAbility( self->client->ps.stats[ STAT_CLASS ], SCA_WALLCLIMBER ) )
				{
					self->client->pers.cmd.upmove = -1;
				}
				else if( self->client->ps.stats[ STAT_TEAM ] == TEAM_ALIENS && level.time - self->jumptime > 3000 && 
					self->client->ps.stats[ STAT_CLASS ] != PCL_ALIEN_LEVEL3_UPG && 
					self->client->ps.stats[ STAT_CLASS ] != PCL_ALIEN_LEVEL3)
				{
					self->client->ps.velocity[2] =  BG_Class( self->client->ps.stats[ STAT_CLASS ] )->jumpMagnitude;
					self->client->pers.cmd.upmove = 20;
					if(level.time - self->jumptime > 4000)
					self->jumptime = level.time;
				}
							
				//botShootIfTargetInRange(self,self->botEnemy);


				//ROTAX
				if(self->botEnemy->client || self->client->ps.stats[ STAT_TEAM ] == TEAM_ALIENS)
				{
					if(self->client->ps.stats[ STAT_TEAM ] == TEAM_HUMANS && 
						g_human_strafe.integer > 0)
					{
  						self->client->pers.cmd.rightmove = -100;
  						if(self->client->time1000 >= 500)
  							self->client->pers.cmd.rightmove = 100;
					}
					//self->client->pers.cmd.forwardmove = forwardMove;
					if(self->client->ps.stats[ STAT_TEAM ] == TEAM_HUMANS && 
						Distance( self->s.pos.trBase, self->botEnemy->s.pos.trBase ) < 300 && 
						self->client->ps.weapon != WP_PAIN_SAW && 
						self->client->ps.weapon != WP_FLAMER)
					{
						self->client->pers.cmd.forwardmove = -100;
					}
					else
					{
						self->client->pers.cmd.forwardmove = forwardMove;
// 						if (g_ambush.integer > 0)
// 						{
// 							int uhyb = 0;
//   							//if (g_ambush_dodge_random.integer <= 0)
// 							//	g_ambush_dodge_random.integer = 1;
//   				  
//   							if (g_ambush_dodge.integer > 0)
// 							{
// 								srand( trap_Milliseconds( ) );
// 								uhyb = (rand() % g_ambush_dodge.integer);
//     								if(self->client->time1000 >= 500)
//     									self->client->pers.cmd.rightmove = uhyb;
// 								else
// 									self->client->pers.cmd.rightmove = -uhyb;
//   							}
// 						}
// 						else
// 						{
  							self->client->pers.cmd.rightmove = -100;
  							if(self->client->time1000 >= 500)
  								self->client->pers.cmd.rightmove = 100;
// 						}
					}
				}
				else
				{
					if(self->client->ps.stats[ STAT_TEAM ] == TEAM_HUMANS)//Human target buildable
					{
						if(self->client->ps.weapon == WP_PAIN_SAW)
						{
							self->client->pers.cmd.forwardmove = forwardMove;
						}
						else if(self->client->ps.weapon == WP_FLAMER)
						{
							self->client->pers.cmd.forwardmove = forwardMove;
						}
						else
						{
							self->client->pers.cmd.upmove = -1;
						}
					}
				}
			}
			
			break;
			
		case BOT_IDLE:
			// just stand there and look pretty.
			break;
			
		//case BOT_ATTACK: //same as regular..
			// .. not sure ..
			//break;
			
		case BOT_STAND_GROUND:
			// stand ground but attack enemies if you can reach.
			if(self->botEnemy) {
				// we already have an enemy. See if still in LOS.
				if(!botTargetInRange(self,self->botEnemy)) {
					//we are not in LOS
					self->botEnemy = NULL;
				}
			}
			
			if(!self->botEnemy) {
				// try to find closest enemy
				tempEntityIndex = botFindClosestEnemy(self, qfalse);
				if(tempEntityIndex >= 0)
					self->botEnemy = &g_entities[tempEntityIndex];
			}
			
			if(!self->botEnemy) {
				// no enemy
			} else {
				// enemy!
				distance = botGetDistanceBetweenPlayer(self, self->botEnemy);
				//botAimAtTarget(self, self->botEnemy);
				
				// enable wallwalk
				if( BG_ClassHasAbility( self->client->ps.stats[ STAT_CLASS ], SCA_WALLCLIMBER ) ) {
					self->client->pers.cmd.upmove = -1;
				}
				
				//botShootIfTargetInRange(self,self->botEnemy); //# LEPE

				//ROTAX
				if(self->botEnemy->client || self->client->ps.stats[ STAT_TEAM ] == TEAM_ALIENS)
				{
					if(self->client->ps.stats[ STAT_TEAM ] == TEAM_HUMANS && 
						g_human_strafe.integer > 0)
					{
  						self->client->pers.cmd.rightmove = -100;
  						if(self->client->time1000 >= 500)
  							self->client->pers.cmd.rightmove = 100;
					}
					//self->client->pers.cmd.forwardmove = forwardMove;
					if(self->client->ps.stats[ STAT_TEAM ] == TEAM_HUMANS && 
						Distance( self->s.pos.trBase, self->botEnemy->s.pos.trBase ) < 300 && 
						self->client->ps.weapon != WP_PAIN_SAW && 
						self->client->ps.weapon != WP_FLAMER)
					{
						self->client->pers.cmd.forwardmove = -100;
					}
					else
					{
						self->client->pers.cmd.forwardmove = forwardMove;
  							self->client->pers.cmd.rightmove = -100;
  							if(self->client->time1000 >= 500)
  								self->client->pers.cmd.rightmove = 100;
					}
				}
				else
				{
					if(self->client->ps.stats[ STAT_TEAM ] == TEAM_HUMANS)//Human target buildable
					{
						if(self->client->ps.weapon == WP_PAIN_SAW)
						{
							self->client->pers.cmd.forwardmove = forwardMove;
						}
						else if(self->client->ps.weapon == WP_FLAMER)
						{
							self->client->pers.cmd.forwardmove = forwardMove;
						}
						else
						{
							self->client->pers.cmd.upmove = -1;
						}
					}
				}

			}
			
			break;
			
		//case BOT_DEFENSIVE:
			// if there is an enemy around, rush them but not too far from where you are standing when given this command
		//	break;
			
		//case BOT_FOLLOW_FRIEND_PROTECT:
			// run towards friend, attack enemy
		//	break;
			
		case BOT_FOLLOW_FRIEND_ATTACK:
			// run with friend until enemy spotted, then rush enemy
			if(self->botEnemy) {
				// we already have an enemy. See if still in LOS.
				if(!botTargetInRange(self,self->botEnemy)) {
					// if it's been over clicksToStopChase clicks since we last seen him in LOS then do nothing, else follow him!
					if(self->botEnemyLastSeen > clicksToStopChase) {
						// forget him!
						self->botEnemy = NULL;
						self->botEnemyLastSeen = 0;
					} else {
						//chase him
						self->botEnemyLastSeen++;
					}
				} else {
					// we see him!
					self->botEnemyLastSeen = 0;
				}
				
				//if we are chasing enemy, reset counter for friend LOS .. if its true
				if(self->botEnemy) {
					if(botTargetInRange(self,self->botFriend)) {
						self->botFriendLastSeen = 0;
					} else {
						self->botFriendLastSeen++;
					}
				}
			}
			
			if(!self->botEnemy) {
				// try to find closest enemy
				tempEntityIndex = botFindClosestEnemy(self, qfalse);
				if(tempEntityIndex >= 0)
					self->botEnemy = &g_entities[tempEntityIndex];
			}
			
			if(!self->botEnemy) {
				// no enemy
				if(self->botFriend) {
					// see if our friend is in LOS
					if(botTargetInRange(self,self->botFriend)) {
						// go to him!
						followFriend = qtrue;
						self->botFriendLastSeen = 0;
					} else {
						// if it's been over clicksToStopChase clicks since we last seen him in LOS then do nothing, else follow him!
						if(self->botFriendLastSeen > clicksToStopChase) {
							// forget him!
							followFriend = qfalse;
						} else {
							self->botFriendLastSeen++;
							followFriend = qtrue;
						}
					}
					
					if(followFriend) {
						distance = botGetDistanceBetweenPlayer(self, self->botFriend);
						//botAimAtTarget(self, self->botFriend);
						
						// enable wallwalk
						if( BG_ClassHasAbility( self->client->ps.stats[ STAT_CLASS ], SCA_WALLCLIMBER ) ) {
							self->client->pers.cmd.upmove = -1;
						}
						
						//botShootIfTargetInRange(self,self->botEnemy);
						if(distance>tooCloseDistance) {
							self->client->pers.cmd.forwardmove = forwardMove;
							self->client->pers.cmd.rightmove = -100;
							if(self->client->time1000 >= 500)
								self->client->pers.cmd.rightmove = 100;
						}
					}
				}
			} else {
				// enemy!
				distance = botGetDistanceBetweenPlayer(self, self->botEnemy);
				//botAimAtTarget(self, self->botEnemy);
				
				// enable wallwalk
				if( BG_ClassHasAbility( self->client->ps.stats[ STAT_CLASS ], SCA_WALLCLIMBER ) ) {
					self->client->pers.cmd.upmove = -1;
				}
				
				botShootIfTargetInRange(self,self->botEnemy);
				self->client->pers.cmd.forwardmove = forwardMove;
				self->client->pers.cmd.rightmove = -100;
				if(self->client->time1000 >= 500)
					self->client->pers.cmd.rightmove = 100;
			}
			
			break;
			
		case BOT_FOLLOW_FRIEND_IDLE:
			// run with friend and stick with him no matter what. no attack mode.
			if(self->botFriend) {
				// see if our friend is in LOS
				if(botTargetInRange(self,self->botFriend)) {
					// go to him!
					followFriend = qtrue;
					self->botFriendLastSeen = 0;
				} else {
					// if it's been over clicksToStopChase clicks since we last seen him in LOS then do nothing, else follow him!
					if(self->botFriendLastSeen > clicksToStopChase) {
						// forget him!
						followFriend = qfalse;
					} else {
						//chase him
						self->botFriendLastSeen++;
						followFriend = qtrue;
					}
					
				}
				
				if(followFriend) {
					distance = botGetDistanceBetweenPlayer(self, self->botFriend);
					//botAimAtTarget(self, self->botFriend);
					
					// enable wallwalk
					if( BG_ClassHasAbility( self->client->ps.stats[ STAT_CLASS ], SCA_WALLCLIMBER ) ) {
						self->client->pers.cmd.upmove = -1;
					}
					
					//botShootIfTargetInRange(self,self->botFriend);
					if(distance>tooCloseDistance) {
						self->client->pers.cmd.forwardmove = forwardMove;
						self->client->pers.cmd.rightmove = -100;
						if(self->client->time1000 >= 500)
							self->client->pers.cmd.rightmove = 100;
					}
				}
			}
			
			break;
			
		//case BOT_TEAM_KILLER: break; //We don't need this. 
			/*
			if(self->botEnemy) {
				if(!botTargetInRange(self,self->botEnemy)) {
					if(self->botEnemyLastSeen > clicksToStopChase) {
						self->botEnemy = NULL;
						self->botEnemyLastSeen = 0;
					} else {
						self->botEnemyLastSeen++;
					}
				} else {
					self->botEnemyLastSeen = 0;
				}
			}
			
			if(!self->botEnemy) {
				tempEntityIndex = botFindClosestEnemy(self, qtrue);
				if(tempEntityIndex >= 0)
					self->botEnemy = &g_entities[tempEntityIndex];
			}
			
			if(!self->botEnemy) {
			} else {
				distance = botGetDistanceBetweenPlayer(self, self->botEnemy);
				if( BG_ClassHasAbility( self->client->ps.stats[ STAT_CLASS ], SCA_WALLCLIMBER ) ) {
					self->client->pers.cmd.upmove = -1;
				}
				
				botShootIfTargetInRange(self,self->botEnemy);
				self->client->pers.cmd.forwardmove = forwardMove;
				self->client->pers.cmd.rightmove = -100;
				if(self->client->time1000 >= 500)
					self->client->pers.cmd.rightmove = 100;
			}
			
			break;
			*/
		default:
			// dunno.
			break;
	}
}

void G_BotSpectatorThink( gentity_t *self )
{
	team_t teamnum;
	int clientNum;
	if( /*g_bot.integer <= 0 || */self->client->ps.pm_flags & PMF_QUEUED /*|| self->client->ps.stats[ STAT_CLASS ] != PCL_NONE*/)
	{
		//we're queued to spawn, all good
		
		return;
	}
// 	if( self->client->sess.sessionTeam == TEAM_NONE )
// 	{
		
		teamnum = self->client->pers.teamSelection;
		clientNum = self->client->ps.clientNum;
		if( teamnum == TEAM_HUMANS )
		{
			self->client->pers.classSelection = PCL_HUMAN;
			self->client->ps.stats[ STAT_CLASS ] = PCL_HUMAN;
			self->client->pers.humanItemSelection = WP_MACHINEGUN;
			//self->client->pers.humanItemSelection = WP_HBUILD; //LEPE
			G_PushSpawnQueue( &level.humanSpawnQueue, clientNum );
		}
		else if( teamnum == TEAM_ALIENS)
		{
// 			//ROTAX
// 			if (g_ambush.integer == 1)
// 			{   
// 				if (ROTACAK_ambush_rebuild_time_temp < level.time && ((level.time - level.startTime) > (g_ambush_sec_to_start.integer * 1000)) )
// 				{
// 					srand( trap_Milliseconds( ) );
// 					self->client->pers.classSelection = PCL_ALIEN_BUILDER0;
// 					self->client->ps.stats[ STAT_CLASS ] = PCL_ALIEN_BUILDER0;
// 					G_PushSpawnQueue( &level.alienSpawnQueue, clientNum );
// 				}
// 			}
// 			else
// 			{
				self->client->pers.classSelection = PCL_ALIEN_LEVEL0;
				self->client->ps.stats[ STAT_CLASS ] = PCL_ALIEN_LEVEL0;
				G_PushSpawnQueue( &level.alienSpawnQueue, clientNum );
// 			}
// 		}
	}
}

// qboolean botAimAtTarget( gentity_t *self, gentity_t *target ) {
// 	int Ax,Ay,Az,Bx,By,Bz = 0;
// 	vec3_t dirToTarget, angleToTarget;
// 	vec3_t top = { 0, 0, 0};
// 	vec3_t  forward, right, up;
// 	vec3_t  muzzle,delta;
// 	float deltangle,deltangle2,diffangle,diffangle2;
// 	AngleVectors( self->client->ps.viewangles, forward, right, up );
// 	CalcMuzzlePoint( self, forward, right, up, muzzle );
// 	if(self->client->ps.stats[ STAT_CLASS ] == PCL_ALIEN_LEVEL3 || 
// 		self->client->ps.stats[ STAT_CLASS ] == PCL_ALIEN_LEVEL3_UPG)
// 	{
// 		Ax = target->s.pos.trBase[0];
// 		Ay = target->s.pos.trBase[1];
// 		Az = target->s.pos.trBase[2];
// 		Bx = self->s.pos.trBase[0];
// 		By = self->s.pos.trBase[1];
// 		Bz = self->s.pos.trBase[2];
// 		if(self->client->ps.stats[ STAT_CLASS ] == PCL_ALIEN_LEVEL3)
// 		{top[2] = (int)(sqrt((Ax - Bx)*(Ax - Bx) + (Ay - By)*(Ay - By) + (Az - Bz)*(Az - Bz)) / 3);}
// 		else
// 		{top[2] = (int)(sqrt((Ax - Bx)*(Ax - Bx) + (Ay - By)*(Ay - By) + (Az - Bz)*(Az - Bz)) / 5);}
// 	}
// 	VectorAdd( target->s.pos.trBase, top, top);
// 	VectorSubtract( top, muzzle, dirToTarget );
// 	VectorNormalize( dirToTarget );
// 	vectoangles( dirToTarget, angleToTarget );
// 	deltangle = SHORT2ANGLE(self->client->ps.delta_angles[0]);
// 	deltangle2 = SHORT2ANGLE(self->client->ps.delta_angles[1]);
// 	diffangle = AngleSubtract(angleToTarget[0],deltangle);
// 	diffangle2 = AngleSubtract(angleToTarget[1],deltangle2);
// 	if(diffangle > self->botSkillLevel)
// 	{
// 		delta[0] = deltangle + self->botSkillLevel;
// 	}
// 	else if(diffangle < -self->botSkillLevel)
// 	{
// 		delta[0] = deltangle - self->botSkillLevel;
// 	}
// 	else
// 	{
// 		delta[0] = angleToTarget[0];
// 	}
// 	if(diffangle2 > self->botSkillLevel)
// 	{
// 		delta[1] = deltangle2 + self->botSkillLevel;
// 	}
// 	else if(diffangle2 < -self->botSkillLevel)
// 	{
// 		delta[1] = deltangle2 - self->botSkillLevel;
// 	}
// 	else
// 	{
// 		delta[1] = angleToTarget[1];
// 	}
//  	self->client->ps.delta_angles[0] = ANGLE2SHORT(delta[0]);
// 	self->client->ps.delta_angles[1] = ANGLE2SHORT(delta[1]);
// 	return qtrue;
// }

qboolean botAimAtTarget( gentity_t *self, gentity_t *target ) {
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
	
	dirToTarget[0] += self->botSkillLevel * sin( self->client->time1000 );
	dirToTarget[1] += self->botSkillLevel * cos( self->client->time1000 );
	// Grab the angles to use with delta_angles
	vectoangles( dirToTarget, angleToTarget );
	self->client->ps.delta_angles[ 0 ] = ANGLE2SHORT( angleToTarget[ 0 ] );
	self->client->ps.delta_angles[ 1 ] = ANGLE2SHORT( angleToTarget[ 1 ] );
	self->client->ps.delta_angles[ 2 ] = ANGLE2SHORT( angleToTarget[ 2 ] );



	        if(angleToTarget[0] > -350 && angleToTarget[0] < -180) {
			if( self->client->ps.stats[ STAT_TEAM ] == TEAM_HUMANS ) {
				// down
				self->client->pers.cmd.upmove = -1;
			}
	        }
	        else if(angleToTarget[0] < -6.0 && angleToTarget[0] > -180) {
	                // up
	                self->client->pers.cmd.upmove = 127;
	        }
	        else {
	                // don't do anything
	                self->client->pers.cmd.upmove = 0;
	        }

//	trap_SendServerCommand( -1, va( "print \"%f\n\"", angleToTarget[0]) );

	return qtrue;
}

qboolean botTargetInRange( gentity_t *self, gentity_t *target ) {
	trace_t   trace;
	gentity_t *traceEnt;
	vec3_t  forward, right, up;
	vec3_t  muzzle;
	AngleVectors( self->client->ps.viewangles, forward, right, up );
	CalcMuzzlePoint( self, forward, right, up, muzzle );

	if( !self || !target )
		return qfalse;

//   //ROTAX - niceni budov
// 	if( !self->client || (!target->client && g_ambush_att_buildables.integer == 0) )
// 		return qfalse;
// 
// 	if( target->client->ps.stats[ STAT_STATE ] & SS_HOVELING )
// 		return qfalse;

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
	//	return qfalse;
	
	//check our target is in LOS
	if(!(traceEnt == target))
		return qfalse;

	return qtrue;
}

// int botFindClosestEnemy( gentity_t *self, qboolean includeTeam ) {
// 	// return enemy entity index, or -1
// 	//int vectorRange = MGTURRET_RANGE * 3;
// 	int i;
// 	//int total_entities;
// 	//int entityList[ MAX_GENTITIES ];
// 	//vec3_t    range;
// 	//vec3_t    mins, maxs;
// 	gentity_t *target;
// 
// 	//if (g_ambush.integer == 1)//ROTAX
// 	//  vectorRange = 1.0f * g_ambush_range.integer;
// 	
// 	//VectorSet( range, vectorRange, vectorRange, vectorRange );
// 	//VectorAdd( self->client->ps.origin, range, maxs );
// 	//VectorSubtract( self->client->ps.origin, range, mins );
// 	
// 	//total_entities = trap_EntitiesInBox( mins, maxs, entityList, MAX_GENTITIES );
// 	
// 	// check list for enemies
// 	for( i = 0; i < MAX_GENTITIES/*total_entities*/; i++ ) {
// 		target = &g_entities[ i ];//entityList[ i ] ];
// // 		if(target->health <= 0 || botGetDistanceBetweenPlayer( self, target ) > g_ambush_range.integer || !botTargetInRange( self, target ))
// // 		{continue;}
// // 		//ROTAX - niceni budov
// // 		if (g_ambush_att_buildables.integer == 0)
// // 		{
// // 			if (target->client && self != target && target->client->ps.stats[ STAT_TEAM ] != self->client->ps.stats[ STAT_TEAM ])
// // 			{
// //   				//if( botTargetInRange( self, target ) ) {
// //   					return i;
// //   				//}
// // 			}
// // 		}
// // 		else if (g_ambush_att_buildables.integer == 1)
// // 		{
//       if ((target->client && self != target && target->client->ps.stats[ STAT_TEAM ] != self->client->ps.stats[ STAT_TEAM ])
//       || (!target->client && self != target && self->client->ps.stats[ STAT_TEAM ] == TEAM_ALIENS && self->client->ps.stats[ STAT_CLASS ] != PCL_ALIEN_LEVEL0 &&
//       (target->s.modelindex == BA_H_SPAWN
//       || target->s.modelindex == BA_H_MGTURRET
//       || target->s.modelindex == BA_H_TESLAGEN
//       || target->s.modelindex == BA_H_ARMOURY
//       || target->s.modelindex == BA_H_DCC
//       || target->s.modelindex == BA_H_MEDISTAT
//       || target->s.modelindex == BA_H_REACTOR
//       || target->s.modelindex == BA_H_REPEATER)) ||
// 	(!target->client && self != target && self->client->ps.stats[ STAT_TEAM ] == TEAM_HUMANS && (
// 	target->s.modelindex == BA_A_SPAWN ||
// 	target->s.modelindex == BA_A_BARRICADE ||
// 	target->s.modelindex == BA_A_BOOSTER ||
// 	target->s.modelindex == BA_A_ACIDTUBE ||
// 	target->s.modelindex == BA_A_HIVE ||
// 	target->s.modelindex == BA_A_TRAPPER ||
// 	target->s.modelindex == BA_A_OVERMIND ||
// 	(!target->client && self != target && self->client->ps.stats[ STAT_CLASS ] == PCL_ALIEN_LEVEL0 && (target->s.modelindex == BA_H_MGTURRET || target->s.modelindex == BA_H_TESLAGEN)))))
//       {
//   			// aliens ignore if it's in LOS because they have radar
//   			//if(self->client->ps.stats[ STAT_TEAM ] == TEAM_ALIENS) {
//   			//	return entityList[ i ];
//   			//} else {
//   				//if( botTargetInRange( self, target ) ) {
//   					return i;
//   				//}
//   			//}
// //       }
// 	}
// 	}
// 	/*
// 	if(includeTeam) {
// 		// check list for enemies in team
// 		for( i = 0; i < total_entities; i++ ) {
// 			target = &g_entities[ entityList[ i ] ];
// 			
// 			if( target->client && self !=target && target->client->ps.stats[ STAT_TEAM ] == self->client->ps.stats[ STAT_TEAM ] ) {
// 				// aliens ignore if it's in LOS because they have radar
// 				//if(self->client->ps.stats[ STAT_TEAM ] == TEAM_ALIENS) {
// 				//	return entityList[ i ];
// 				//} else {
// 					//if( botTargetInRange( self, target ) ) {
// 						return entityList[ i ];
// 					//}
// 				//}
// 			}
// 		}
// 	}
// 	*/
// 	return -1;
// }

int botFindClosestEnemy( gentity_t *self, qboolean includeTeam ) {
	// return enemy entity index, or -1
	int vectorRange = MGTURRET_RANGE * 3;
	int i;
	int total_entities;
	int entityList[ MAX_GENTITIES ];
	vec3_t    range;
	vec3_t    mins, maxs;
	gentity_t *target;

	VectorSet( range, vectorRange, vectorRange, vectorRange );
	VectorAdd( self->client->ps.origin, range, maxs );
	VectorSubtract( self->client->ps.origin, range, mins );

	total_entities = trap_EntitiesInBox( mins, maxs, entityList, MAX_GENTITIES );

	// check list for enemies
// 	for( i = 0; i < total_entities; i++ ) {
// 		target = &g_entities[ entityList[ i ] ];
// 
// 		if( (target->s.eType == ET_BUILDABLE || target->client) && self != target ) {
// 			if( target->s.eType == ET_BUILDABLE ) {
// 				if( target->client->ps.stats[ STAT_TEAM ]  != self->client->ps.stats[ STAT_TEAM ] ) {
// 				  trap_Print("Shooting reactor\n");
//                                         // aliens ignore if it's in LOS because they have radar
//                                         if(self->client->ps.stats[ STAT_TEAM ] == TEAM_ALIENS) {
//                                                 return entityList[ i ];
//                                         } else {
//                                                 if( botTargetInRange( self, target ) ) {
//                                                         return entityList[ i ];
// 						}
//                                         }
// 				}
// 			}
// 			else {
// 				if( target->client->ps.stats[ STAT_TEAM ] != self->client->ps.stats[ STAT_TEAM ] ) {
// 					// aliens ignore if it's in LOS because they have radar
// 					if(self->client->ps.stats[ STAT_TEAM ] == TEAM_ALIENS) {
// 						return entityList[ i ];
// 					} else {
// 						if( botTargetInRange( self, target ) ) {
// 							return entityList[ i ];
// 						}
// 					}
// 				}
// 			}
// 		}
// 	}
	for( i = 0; i < total_entities; i++ ) {
		target = &g_entities[ entityList[ i ] ];

		if( target->client && self != target && target->client->ps.stats[ STAT_TEAM ] != self->client->ps.stats[ STAT_TEAM ] ) {
			// aliens ignore if it's in LOS because they have radar
			if(self->client->ps.stats[ STAT_TEAM ] == TEAM_ALIENS) {
				return entityList[ i ];
			} else {
				if( botTargetInRange( self, target ) ) {
					return entityList[ i ];
				}
			}
		}
		
		if( target->s.eType == ET_BUILDABLE && self != target && target->buildableTeam != self->client->ps.stats[ STAT_TEAM ] ) {
			// aliens ignore if it's in LOS because they have radar
			if(self->client->ps.stats[ STAT_TEAM ] == TEAM_ALIENS) {
				return entityList[ i ];
			} else {
				if( botTargetInRange( self, target ) ) {
					return entityList[ i ];
				}
			}
		}
	}

	if(includeTeam) {
		// check list for enemies in team
		for( i = 0; i < total_entities; i++ ) {
			target = &g_entities[ entityList[ i ] ];

			if( target->client && self !=target && target->client->ps.stats[ STAT_TEAM ] == self->client->ps.stats[ STAT_TEAM ] ) {
				// aliens ignore if it's in LOS because they have radar
				if(self->client->ps.stats[ STAT_TEAM ] == TEAM_ALIENS) {
					return entityList[ i ];
				} else {
					if( botTargetInRange( self, target ) ) {
						return entityList[ i ];
					}
				}
			}
		}
	}

	return -1;
}

// really an int? what if it's too long? If it is, we are fuxed.
int botGetDistanceBetweenPlayer( gentity_t *self, gentity_t *player ) {
	return Distance( self->s.pos.trBase, player->s.pos.trBase );
}

qboolean botShootIfTargetInRange( gentity_t *self, gentity_t *target )
{
	if(botTargetInRange(self,target))
	{
	  //ROTAX
			int nahoda = 0;
			srand( trap_Milliseconds( ) );
			//nahoda = (rand() % 20);
			nahoda = (int)(( (double)rand() / ((double)(RAND_MAX)+(double)(1)) ) * 20);
			self->client->pers.cmd.buttons = 0;
			if (self->client->pers.classSelection == PCL_ALIEN_BUILDER0)
			{
				self->client->pers.cmd.buttons |= BUTTON_GESTURE;
			}
			else if (self->client->pers.classSelection == PCL_ALIEN_BUILDER0_UPG)//adv granger
			{
				if (nahoda > 10)
 					self->client->pers.cmd.buttons |= BUTTON_ATTACK2;
				else
					self->client->pers.cmd.buttons |= BUTTON_USE_HOLDABLE;
			}
			else if (self->client->pers.classSelection == PCL_ALIEN_LEVEL1_UPG)//adv basilisk
			{
				if (nahoda > 15)
					self->client->pers.cmd.buttons |= BUTTON_ATTACK2;
				else
					self->client->pers.cmd.buttons |= BUTTON_ATTACK;
			}
			else if (self->client->pers.classSelection == PCL_ALIEN_LEVEL2_UPG)//adv marauder
			{
				if (Distance( self->s.pos.trBase, target->s.pos.trBase ) > LEVEL2_CLAW_RANGE)
					self->client->pers.cmd.buttons |= BUTTON_ATTACK2;
				else
					self->client->pers.cmd.buttons |= BUTTON_ATTACK;
			}
			else if (self->client->pers.classSelection == PCL_ALIEN_LEVEL3)//dragon
			{
				if(Distance( self->s.pos.trBase, target->s.pos.trBase ) > 150 && 
					self->client->ps.stats[ STAT_MISC ] < LEVEL3_POUNCE_JUMP_MAG)
					self->client->pers.cmd.buttons |= BUTTON_ATTACK2;
				else
					self->client->pers.cmd.buttons |= BUTTON_ATTACK;
			}
			else if (self->client->pers.classSelection == PCL_ALIEN_LEVEL3_UPG)//adv dragon
			{
				if(/*self->client->ps.ammo[WP_ALEVEL3_UPG] > 0 &&*/ 
					Distance( self->s.pos.trBase, target->s.pos.trBase ) > 150 )
					self->client->pers.cmd.buttons |= BUTTON_USE_HOLDABLE;
				else
				{	
					if(Distance( self->s.pos.trBase, target->s.pos.trBase ) > 150 && 
						self->client->ps.stats[ STAT_MISC ] < LEVEL3_POUNCE_JUMP_MAG_UPG)
						self->client->pers.cmd.buttons |= BUTTON_ATTACK2;
					else
						self->client->pers.cmd.buttons |= BUTTON_ATTACK;
				}
			}
			else if (self->client->pers.classSelection == PCL_ALIEN_LEVEL4)//tyrant
			{
				if (Distance( self->s.pos.trBase, target->s.pos.trBase ) > LEVEL4_CLAW_RANGE)
					self->client->pers.cmd.buttons |= BUTTON_ATTACK2;
				else
					self->client->pers.cmd.buttons |= BUTTON_ATTACK;
			}
			else//others
			{
				if(self->client->ps.stats[ STAT_TEAM ] == TEAM_HUMANS)//Human target buildable
				{
					if(self->client->ps.weapon == WP_FLAMER)
					{
						if(Distance( self->s.pos.trBase, target->s.pos.trBase ) < 200)
							self->client->pers.cmd.buttons |= BUTTON_ATTACK;
					}
					else if(self->client->ps.weapon == WP_LUCIFER_CANNON)
					{
						self->client->pers.cmd.buttons |= BUTTON_ATTACK2;
					}
					else
					{
						self->client->pers.cmd.buttons |= BUTTON_ATTACK;
					}
				}
				else
				{
					self->client->pers.cmd.buttons |= BUTTON_ATTACK;
				}
			}
			return qtrue;
			//if (nahoda == 15 || nahoda == 16)
        		//	self->client->pers.cmd.buttons |= BUTTON_GESTURE;
			//if (nahoda > 11 && nahoda < 15)
        		//	self->client->pers.cmd.upmove = 20;
	}
	self->botEnemy = NULL;
	return qfalse;
}
