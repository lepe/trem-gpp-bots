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
 * Navigation code
 */

#include "g_local.h"

#define GOOD_ESSENCE 1
#define BAD_ESSENCE -1
#define NO_ESSENCE 0

void BotTargetPath( gentity_t *self )
{
	G_BotDebug(self, BOT_VERB_DETAIL, BOT_DEBUG_NAV + BOT_DEBUG_NAVSTATE, "(0) Current NAV state: %d\n", self->bot->path.state);
	//check if we lost track of the path we were targeting. If we did, find new one
	if((self->bot->path.lastpathid >= 0 && level.time - self->bot->timer.foundPath > level.paths[self->bot->path.lastpathid].timeout) ||
		level.time - self->bot->timer.foundPath > 10000)
	{
		{
			if(g_bot_manual_nav.integer) {
				G_BotDebug(self, BOT_VERB_DETAIL, BOT_DEBUG_NAV + BOT_DEBUG_NAVSTATE, "(1) NAV State would have changed to: %d\n", FINDNEWPATH);
			} else {					
				G_BotDebug(self, BOT_VERB_DETAIL, BOT_DEBUG_NAV + BOT_DEBUG_NAVSTATE, "(1) NAV State changed to: %d\n", FINDNEWPATH);
				self->bot->path.state = FINDNEWPATH;
			}
		}
	}
	//G_Printf("Target: %d, Distance %d\n",self->bot->path.targetPath, distanceToTargetNode(self));
	if(distanceToTargetNode(self) < 70) 
	{
		if(g_bot_manual_nav.integer) {
			G_BotDebug(self, BOT_VERB_DETAIL, BOT_DEBUG_NAV + BOT_DEBUG_NAVSTATE, "(3) NAV State would have changed to: %d\n", FINDNEXTPATH);
		} else {
			G_BotDebug(self, BOT_VERB_DETAIL, BOT_DEBUG_NAV + BOT_DEBUG_NAVSTATE, "(3) NAV State changed to: %d\n", FINDNEXTPATH);
			self->bot->path.state = FINDNEXTPATH;
		}
	}
	//If we haven't move enough, check if we are blocked
	if(level.time - self->bot->timer.foundPath > 1000 && VectorLength( self->client->ps.velocity ) < 10.0f && (float)Distance( self->client->oldOrigin, self->r.currentOrigin ) < 50 ) //2.3
	{
		if(g_bot_manual_nav.integer) {
			G_BotDebug(self, BOT_VERB_DETAIL, BOT_DEBUG_NAV + BOT_DEBUG_NAVSTATE, "(4) NAV State would have changed to: %d\n", BLOCKED);
		} else {
			G_BotDebug(self, BOT_VERB_DETAIL, BOT_DEBUG_NAV + BOT_DEBUG_NAVSTATE, "(4) NAV State changed to: %d\n", BLOCKED);
	    	self->bot->path.state = BLOCKED;
		}
	} else {
		//G_BotDebug(self, BOT_VERB_DETAIL, BOT_DEBUG_NAV + BOT_DEBUG_NAVSTATE, "NOT BLOCKED %d: \n",self->bot->path.state);
		//we are not blocked, so don't keep trying
		//self->bot->path.blocked_try = 0; 
	}
}

/**
 * Try to locate another path (for example, when bot is blocked)
 * @param self [gentity_t] a BOT
 */
void BotFindNewPath( gentity_t *self )
{
	trace_t trace;
	int i,distance,Ax,Ay,Az,Bx,By,Bz = 0;
	int closestpath = 0;
	int closestpathdistance = 2000;
	qboolean pathfound = qfalse;
	self->bot->path.lastpathid = -1;
	for(i = 0; i < level.numPaths; i++) //find a nearby node
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
        if(distance < closestpathdistance)
        {
            closestpath = i;
            closestpathdistance = distance;
            pathfound = qtrue;
        }
	}
	if(pathfound == qtrue)
	{
		G_BotDebug(self, BOT_VERB_DETAIL, BOT_DEBUG_NAV + BOT_DEBUG_NAVSTATE, "New Path found\n");
		self->bot->path.targetPath = closestpath;
		self->bot->timer.foundPath = level.time;
		if(g_bot_manual_nav.integer) {
			G_BotDebug(self, BOT_VERB_DETAIL, BOT_DEBUG_NAV + BOT_DEBUG_NAVSTATE, "(5) NAV State would have changed to: %d\n", TARGETPATH);
		} else {
			G_BotDebug(self, BOT_VERB_DETAIL, BOT_DEBUG_NAV + BOT_DEBUG_NAVSTATE, "(5) NAV State changed to: %d\n", TARGETPATH);
			self->bot->path.state = TARGETPATH;
		}
	}
	else
	{
		G_BotDebug(self, BOT_VERB_DETAIL, BOT_DEBUG_NAV + BOT_DEBUG_NAVSTATE, "New Path NOT found\n");
		//TODO: for now is treated as BLOCKED but should be LOST
		if(g_bot_manual_nav.integer) {
			G_BotDebug(self, BOT_VERB_DETAIL, BOT_DEBUG_NAV + BOT_DEBUG_NAVSTATE, "(6) NAV State would have changed to: %d\n", BLOCKED);
		} else {
			G_BotDebug(self, BOT_VERB_DETAIL, BOT_DEBUG_NAV + BOT_DEBUG_NAVSTATE, "(6) NAV State hanged to: %d\n", BLOCKED);
			self->bot->path.state = BLOCKED;
		}
	}
	return;
}

/**
 * Decide which is the next path to go
 * @param self [gentity_t] a BOT
 */
void BotFindNextPath( gentity_t *self )
{
	int totalessence = 0; //LEPE: ant algorithm
    int accumessence = 0;
	int pathessence[5];
	int pathrank[5];
    int essence = NO_ESSENCE;
    int randnum = 0;
	int i,j,nextpath = 0;
	int possiblenextpath = 0;
	int possiblepaths[5];
    qboolean known = qfalse;

    G_BotDebug(self, BOT_VERB_DETAIL, BOT_DEBUG_NAV + BOT_DEBUG_NAVSTATE,"Last Path Id: %d\n",self->bot->path.lastpathid);
    G_BotDebug(self, BOT_VERB_DETAIL, BOT_DEBUG_NAV + BOT_DEBUG_NAVSTATE,"Target Path: %d\n",self->bot->path.targetPath);
	possiblepaths[0] = possiblepaths[1] = possiblepaths[2] = possiblepaths[3] = possiblepaths[4] = 0;
	for(i = 0; i < 5; i++)
	{
		if(level.paths[self->bot->path.targetPath].nextid[i] < level.numPaths &&
			level.paths[self->bot->path.targetPath].nextid[i] >= 0)
		{
			if(self->bot->path.lastpathid >= 0)
			{
				if(self->bot->path.lastpathid == level.paths[self->bot->path.targetPath].nextid[i])
				{
					continue;
				}
			}
			possiblepaths[possiblenextpath] = level.paths[self->bot->path.targetPath].nextid[i];
			possiblenextpath++;
		}
	}
    G_BotDebug(self, BOT_VERB_DETAIL, BOT_DEBUG_NAV + BOT_DEBUG_NAVSTATE,"Path Options: %i, %i, %i, %i, %i\n",possiblepaths[0],possiblepaths[1],possiblepaths[2],possiblepaths[3],possiblepaths[4]);
	if(possiblenextpath == 0)
	{	
		if(g_bot_manual_nav.integer) {
			G_BotDebug(self, BOT_VERB_DETAIL, BOT_DEBUG_NAV + BOT_DEBUG_NAVSTATE, "(7) NAV State would have changed to: %d\n", FINDNEWPATH);
		} else {
			G_BotDebug(self, BOT_VERB_DETAIL, BOT_DEBUG_NAV + BOT_DEBUG_NAVSTATE, "(7) NAV State changed to: %d\n", FINDNEWPATH);
			self->bot->path.state = FINDNEWPATH;
		}
		return;
	}
	else
	{
		if(g_bot_manual_nav.integer) {
			G_BotDebug(self, BOT_VERB_DETAIL, BOT_DEBUG_NAV + BOT_DEBUG_NAVSTATE, "(8) NAV State would have changed to: %d\n", TARGETPATH);
		} else {
			G_BotDebug(self, BOT_VERB_DETAIL, BOT_DEBUG_NAV + BOT_DEBUG_NAVSTATE, "(8) NAV State changed to: %d\n", TARGETPATH);
			self->bot->path.state = TARGETPATH;
		}
		if(possiblenextpath == 1)
		{
			nextpath = 0;
		}
		else
		{
			if(g_bot_essence.integer == 1) {
				//bots decide here which path to follow based on the strength of the essence, previous nodes and possible unexplored nodes
				//-------------
				G_BotDebug(self, BOT_VERB_DETAIL, BOT_DEBUG_NAV + BOT_DEBUG_PATH, "Possible Paths: %d .",possiblenextpath);
				for(i =0; i < possiblenextpath; i++) {
					G_BotDebug(self, BOT_VERB_DETAIL, BOT_DEBUG_NAV + BOT_DEBUG_PATH,"[ %d :",possiblepaths[i]);
					known = qfalse;
					for(j=0; j < self->bot->path.numCrumb; j++) {
						if(self->bot->path.crumb[j] == possiblepaths[i]) {
							known = qtrue;
							break;
						}
					} 
					pathessence[i] = level.paths[possiblepaths[i]].essence;
					essence = pathessence[i] > 50 ? GOOD_ESSENCE : (pathessence[i] < 50 ? BAD_ESSENCE : NO_ESSENCE);
					G_BotDebug(self, BOT_VERB_DETAIL, BOT_DEBUG_NAV + BOT_DEBUG_PATH,"%d",pathessence[i]);
					if(known == qfalse && essence == GOOD_ESSENCE) {
						G_BotDebug(self, BOT_VERB_DETAIL, BOT_DEBUG_NAV + BOT_DEBUG_PATH," x 50");
						pathrank[i] = 50;                    
					} else if(known == qfalse && essence == NO_ESSENCE) {
						G_BotDebug(self, BOT_VERB_DETAIL, BOT_DEBUG_NAV + BOT_DEBUG_PATH," x 30");
						pathrank[i] = 30;                    
					} else if(known == qtrue && (essence == GOOD_ESSENCE || essence == NO_ESSENCE)) {
						G_BotDebug(self, BOT_VERB_DETAIL, BOT_DEBUG_NAV + BOT_DEBUG_PATH," x 15");
						pathrank[i] = 15;                    
					} else if(known == qfalse) { //bad essence implied
						G_BotDebug(self, BOT_VERB_DETAIL, BOT_DEBUG_NAV + BOT_DEBUG_PATH," x 5");
						pathrank[i] = 5;                    
					} else { //known && bad essence implied
						G_BotDebug(self, BOT_VERB_DETAIL, BOT_DEBUG_NAV + BOT_DEBUG_PATH," x 1");
						pathrank[i] = 1;                    
					}
					totalessence += pathessence[i] * pathrank[i];
					G_BotDebug(self, BOT_VERB_DETAIL, BOT_DEBUG_NAV + BOT_DEBUG_PATH,"] TOTAL: %d\n",totalessence);
				}
				self->bot->path.lastJoint = self->bot->path.targetPath; //when was the last time we had to choose a path (used to create negative essence)
				randnum = G_Rand();
				for(i =0; i < possiblenextpath; i++) {
					accumessence += ((pathessence[i] * pathrank[i]) * 100) / totalessence;
					if(randnum <= accumessence) {
						G_BotDebug(self, BOT_VERB_NORMAL, BOT_DEBUG_NAV + BOT_DEBUG_PATH,"SELECTED : %d\n",possiblepaths[i]);
						nextpath = i;
						break;
					}
				}
			} else {
				nextpath = G_Rand_Range(0,possiblenextpath-1);
						G_BotDebug(self, BOT_VERB_NORMAL, BOT_DEBUG_NAV + BOT_DEBUG_PATH,"RANDOMLY SELECTED : %d\n",possiblepaths[i]);
			}
		}
		//LEPE: set next crumb
		setCrumb( self, possiblepaths[nextpath] );
		self->bot->path.lastpathid = self->bot->path.targetPath;
		self->bot->path.targetPath = possiblepaths[nextpath];
		self->bot->timer.foundPath = level.time;
		return;
	}
	return;
}

/**
 * What to do if the bot is blocked
 * We use bot->path.blocked_try to use different
 * strategies.
 * @param self
 */
void BotBlocked( gentity_t *self ) {
	//if (G_Rand() < 10) BotGesture( self );
	if(!g_bot_manual_nav.integer) {
		if(Distance( self->bot->path.blocked_origin, self->r.currentOrigin ) > 50) {
			self->bot->path.state = TARGETPATH;
			self->bot->path.blocked_try = 0;
			G_BotDebug(self, BOT_VERB_DETAIL, BOT_DEBUG_COMMON + BOT_DEBUG_NAVSTATE, "Blocked: Path state (TARGETPATH): %d\n", TARGETPATH);
		}
	}
}

/**
 * What to do if the bot is lost
 * @param self
 */
void BotLost( gentity_t *self ) {
	//nothing yet
}

/**
 * Calculates the distance between BOT and target Node
 * @param self [gentity_t] a BOT
 * @return int
 */
int distanceToTargetNode( gentity_t *self )
{
	int distance,Ax,Ay,Az,Bx,By,Bz = 0;
	Ax = level.paths[self->bot->path.targetPath].coord[0];
	Ay = level.paths[self->bot->path.targetPath].coord[1];
	Az = level.paths[self->bot->path.targetPath].coord[2];
	Bx = self->s.pos.trBase[0];
	By = self->s.pos.trBase[1];
	Bz = self->s.pos.trBase[2];
	distance = sqrt((Ax - Bx)*(Ax - Bx) + (Ay - By)*(Ay - By) + (Az - Bz)*(Az - Bz));
	return distance;
}
/**
 * Aims to the target path (this allows a bot to walk straight)
 * @param self [gentity_t] a BOT
 * @return boolean
 */
qboolean botAimAtPath( gentity_t *self )
{
	if(self->bot->path.state == TARGETPATH) {
		vec3_t dirToTarget, angleToTarget;
		vec3_t top = { 0, 0, 0 };
	// 	int vh = 0;
	// 	BG_FindViewheightForClass(  self->client->ps.stats[ STAT_CLASS ], &vh, NULL );
		top[2]=BG_ClassConfig( self->client->ps.stats[ STAT_CLASS ] )->viewheight;
		VectorAdd( self->s.pos.trBase, top, top);
		VectorSubtract( level.paths[self->bot->path.targetPath].coord, top, dirToTarget );
		VectorNormalize( dirToTarget );
		vectoangles( dirToTarget, angleToTarget );
		//self->client->ps.delta_angles[ PITCH ] = ANGLE2SHORT( angleToTarget[ PITCH ] ); //this makes bots to move aim in Z angles
		self->client->ps.delta_angles[ YAW ] = ANGLE2SHORT( angleToTarget[ YAW ] );
		//self->bot->move.lookat[ YAW ] = ANGLE2SHORT( angleToTarget[ YAW ] );
	}
	return qtrue;
}

/**
 * LEPE: Ant algorithm.
 * It increases the path essence on event
 * @param self [gentity_t] a BOT
 */
void increasePathEssence( gentity_t *self ) {
	int i;
	for(i = 0; i < self->bot->path.numCrumb; i++) {
		if(level.paths[ self->bot->path.crumb[i] ].essence < 50) level.paths[ self->bot->path.crumb[i] ].essence = 50;
		if(level.paths[ self->bot->path.crumb[i] ].essence < 100) {
			level.paths[ self->bot->path.crumb[i] ].essence ++ ; //for now just increment in 1...
			G_BotDebug(self, BOT_VERB_DETAIL, BOT_DEBUG_NAV + BOT_DEBUG_PATH,"Increasing: %i of total: %i (value: %i)\n",self->bot->path.crumb[i], self->bot->path.numCrumb, level.paths[ self->bot->path.crumb[i] ].essence);
		}
	}
}
/**
 * LEPE: Ant algorithm.
 * It sets crumbs for each bot.
 * If a crumb already existed, go back to that one.
 * @param self [gentity_t] a BOT
 * @param closestpath [int] 'next' selected node
 */
void setCrumb( gentity_t *self, int closestpath )
{
    int i;
    int nc = 0; //temp store numCrumb
    qboolean regret = qfalse; //regret last decision: mark as negative essence
    for(i = 0; i < self->bot->path.numCrumb; i++) {
        if(self->bot->path.crumb[i] == closestpath) {
            G_BotDebug(self, BOT_VERB_NORMAL, BOT_DEBUG_NAV + BOT_DEBUG_PATH,"Returning to: %i to node: %i\n",self->bot->path.numCrumb,closestpath);
            nc = i;
        } else if(nc > 0) {
            if(self->bot->path.crumb[i] == self->bot->path.lastJoint) {
                regret = qtrue;
            } 
        }
        if(regret == qtrue) {
           G_BotDebug(self, BOT_VERB_NORMAL, BOT_DEBUG_NAV + BOT_DEBUG_PATH,"Regreting: %i\n",self->bot->path.crumb[i]);
           level.paths[self->bot->path.crumb[i]].essence = 1; 
        }
    }
    if(nc > 0) {
        self->bot->path.numCrumb = nc;
    }
    G_BotDebug(self, BOT_VERB_DETAIL, BOT_DEBUG_NAV + BOT_DEBUG_PATH,"Setting crumb : %i to node: %i\n",self->bot->path.numCrumb,closestpath);
    self->bot->path.crumb[ self->bot->path.numCrumb ] = closestpath;
	if(self->bot->path.numCrumb < level.numPaths) self->bot->path.numCrumb++;
    return;
}

