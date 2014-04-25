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

#define BOT_SHORT_RANGE 	0
#define BOT_MEDIUM_RANGE 	1
#define BOT_LONG_RANGE 		2

//Adjust this value if move actions are being discarded
#define BOT_MOVE_QUEUE		50
#define BOT_MOVE_NO_TIME_LIMIT	0
#define BOT_TURN_VAL		30.0f
#define BOT_TURN_ANGLE_DIV	(360.0f / (float)BOT_TURN_VAL)

/*
 * Bot's general headers
 */
typedef struct
{
	vec3_t	coord;
	int	nextid[5];
	int	random;
	int	timeout;
	int	action;
    int essence; //LEPE: used for ant colony algorithm
} path;

typedef enum
{
	//By Verbosity (if not specified, is NORMAL)
	BOT_VERB_DETAIL 	= -1,	//Messages that we don't want to spam the debug output	(verbose)
	BOT_VERB_NORMAL 	=  0,	//Messages that won't spam the output but not need to be shown always
	BOT_VERB_IMPORTANT 	=  1,	//Messages that must be shown always on debug (quiet)
} botDebugVerbosity;

/**
 * Debug flags for bots.
 * Example: G_BotDebug(BOT_VERB_DETAIL, BOT_DEBUG_MAIN + BOT_DEBUG_THINK + BOT_DEBUG_ALIEN, "This is test # %d\n", 1);
 * In order to turn ON/OFF debug options, cvars are used, example:
 * > g_debugBotThink 1
 * If you add one more debug type here, also add the cvar in g_main.c 
 */
typedef enum
{
	//By function
	BOT_DEBUG_THINK  	= 1 << 0, 	//Anything related to think levels (what to buy, evolve, targets, spectate, etc)
	BOT_DEBUG_STATE	 	= 1 << 1,	//Debug changes in States
	BOT_DEBUG_NAVSTATE 	= 1 << 2,	//Debug changes in Navigation States (inside EXPLORE state)
	BOT_DEBUG_PATH		= 1 << 3,	//Debug nodes, essence, ant algorithm, etc
	BOT_DEBUG_PROFILE	= 1 << 4,	//Debug how profile affected the outcome of something
		//<-------- new "debug by functions" should be inserted here
	//By files
	BOT_DEBUG_GENERAL	= 1 << 5,	//Debug g_bot.c
	BOT_DEBUG_MAIN		= 1 << 6,	//Debug g_main.c (bot related)
	BOT_DEBUG_ADMIN		= 1 << 7,	//Debug g_admin.c (bot related)
	BOT_DEBUG_ACTIVE	= 1 << 8,	//Debug g_active.c (bot related)
	BOT_DEBUG_ALIEN		= 1 << 9,	//Debug g_bot_alien.c
	BOT_DEBUG_HUMAN		= 1 << 10,	//Debug g_bot_human.c
	BOT_DEBUG_CONTROL	= 1 << 11,	//Debug g_bot_control.c
	BOT_DEBUG_UTIL		= 1 << 12,	//Debug g_bot_util.c
	BOT_DEBUG_COMMON	= 1 << 13,	//Debug g_bot_common.c
	BOT_DEBUG_SAY		= 1 << 14,	//Debug g_bot_say.c
	BOT_DEBUG_NAV		= 1 << 15, 	//Debug g_bot_nav.c
		//<-------- new "debug by file" should be inserted here. (No more than 30 or we are hitting the INT limit!)
} botDebugType;

typedef enum
{
	BOT_EMPTY_MOVE, 		//0
	BOT_WAIT,				//1
	BOT_RUN,				//2
	BOT_JUMP,				//3
	BOT_CROUCH,				//4
	BOT_WALLWALK,			//5
	BOT_STAND,				//6
	BOT_MOVE_LEFT,			//7
	BOT_MOVE_RIGHT,			//8
	BOT_MOVE_FWD,			//9
	BOT_MOVE_BACK,			//10
	BOT_LOOK_UP,			//11
	BOT_LOOK_DOWN,			//12
	BOT_LOOK_LEFT,			//13
	BOT_LOOK_RIGHT,			//14
	BOT_POUNCE,				//15
	BOT_GESTURE,			//16
		//<-- add movements here
	BOT_STOP				//17
} botMove;

typedef enum
{
	THINK_LEVEL_MIN, //quick thinking
	THINK_LEVEL_1,
	THINK_LEVEL_2,
	THINK_LEVEL_3,
			//<-- add more levels if required (add them in g_bot_common.c too)
	THINK_LEVEL_MAX  //deep thinking
} botThinkLevel;

typedef enum
{
	UNDEFINED,		//used to automatically change states
	// Valid States:
	EXPLORE,		//explore the map: this will become one of the following:
	ATTACK,			//engage in combat
	DEFEND,			//stay in an area for some time (camp)
	FOLLOW, 		//following another player
	RETREAT, 		//go back to base
	EVADE, 			//perform evasive technique
	HEAL,			//heal itself
	REPAIR,			//repair building
	BUILD,			//build something
	RUSH,			//rushing into the enemy
	PATROL,			//patrol the area
	IMPROVE,		//improve: buy for humans, evolve for aliens
		//<-- add new states here	(add to: g_bot_common, g_bot_alien.c and g_bot_human.c)
	IDLE			//just think. it is also used as enum count
} botState;

typedef enum
{
	TARGETPATH,		//walking to a node
	FINDNEXTPATH,	//looking for the next node //TODO: this and targetpath are not the same?
	FINDNEWPATH,	//looking for any close node
	BLOCKED, 		//blocked, trying to get out of there... 
		//<-- add new states here (add to: g_bot_common, g_bot_alien.c and g_bot_human.c)
	LOST			//lost... doing random stuff (like crying) //used also for enum count
} botNavState;

typedef struct
{
  //GENERAL
  gentity_t		*Enemy;
  gentity_t		*Friend;
  gentity_t		*Struct; //used for repairing or healing
  botState		state;
  //THINK: variables used to decide per thinking level
  struct {
	  botState 		state[THINK_LEVEL_MAX + 1];
	  gentity_t		*target[THINK_LEVEL_MAX + 1];
  } think;
  //PATH: variables and properties related to Navigation
  struct {
	  botNavState	state;
	  qboolean		nextNode;
	  qboolean		pathChosen;
	  int			targetPath;
	  int			targetNode;
	  int			lastpathid;
	  int		    crumb[1000]; //path node history
	  //int		    *crumb; //path node history
	  int           numCrumb; //counter of max path length
	  int           lastJoint; //keep id of last junction
	  int 			blocked_try; //We increase this value each time we try to unblock the bot
  } path;
  //MOVE: variables and properties related to Movements
  struct {
	  struct {
		  botMove action;
		  int time; // time to wait until next action (in ms)
	  } queue[BOT_MOVE_QUEUE];
	  int read; //index used to know which queue slot to read from 
	  int write; //index used to know which queue slot to write into
  } move;
  //PROPERTIES: these values may not change during the game.
  struct {
	  struct {
	  	 int think[THINK_LEVEL_MAX + 1]; //cycle time for each think level
		 int action; //how often we perform actions (states)
		 int aim;	 //how often we aim
	  } time;
  } props;
  //TIMER: used to time actions (variables).
  struct {
	  int	think[THINK_LEVEL_MAX + 1]; //think timer per level
	  int	improve; 	//buytime for humans, evolvetime for aliens
	  int	aim; 		//variable used to time every aim loop (see props.time.aim)
	  int	action; 	//variable used to time every action loop (see props.time.action)
	  int 	move; 		//used in g_bot_control.c for the movement queue
	  int	foundPath; 	//on BotFindN***Path(): if a new/next path is found, we reset this timer
  } timer;
  //PROFILE: bot personality
  struct {
	  int	obedient; //follows esssence or it goes to explore often
	  int	aggressive; //try to attack more often or stays at base (camp) and repairs/build more
	  int	cooperative; //try to keep close to other bots
	  int	bold; //(daring). Will keep attacking even low HP or will try to pursue more.
	  int	greedy; //will try to save creds/evos as much as possible. On the other hand: will spent everything as it gain it
	  int	evasive; //The more, it will try not to go straight to the target but will be slower. 
	  int	talkative; //How much it talks
	  int	impulsive; //How much it takes to take decisions
	  int	skill; //deprecated?
  } profile;
  //SETTINGS: 
 /*
  * In the case of humans, human properties represent % of buying that item (from S1 to S3, this is: 0-2).
  * alien properties represent short and long distances to keep from those classes.
  * 
  * For aliens, aliens properties represent % of evolving to it (S1 to S3). 
  * human properties represent the distance to keep from that target.
  * 
  * @see: BOT_SHORT_RANGE, BOT_MEDIUM_RANGE, BOT_LONG_RANGE
  */
  struct {
	  int	armour[3];
	  int	battery[3];
	  int	painsaw[3];
	  int	shotgun[3];
	  int	lasgun[3];
	  int	chaingun[3];
	  int	helmet[3];
	  int	nade[3];
	  int	prifle[3];
	  int	flamer[3];
	  int	mdriver[3];
	  int	battlesuit[3];
	  int	lcannon[3];
	  //--- aliens:
	  int	basilisk[3];
	  int	adv_basilisk[3];
	  int	marauder[3];
	  int	adv_marauder[3];
	  int	goon[3];
	  int	adv_goon[3];
	  int	tyrant[3];
  } set;
  //FUNCTIONS: These functions are specific for each team
  struct {
	//Base functions (shared or common for both teams). (NOTE: Do not call team functions within base functions)
	struct {
		void (*move)( gentity_t *self, int msec );		
		void (*aim)( gentity_t *self );		
		void (*think)( gentity_t *self );		
		void (*spec)( gentity_t *self );
		void (*target)( gentity_t *self ); 	//target prioritization
		void (*status[IDLE + 1])( gentity_t *self ); //IDLE will always be the last element in enum
		void (*nav[LOST + 1])( gentity_t *self ); //Navigation state
	} base;
	//Function that are specific for each team (NOTE: Do not call base functions within team functions).
	struct {
		void (*think)( gentity_t *self );		
		void (*spec)( gentity_t *self );
		void (*target)( gentity_t *self ); 	//target prioritization
		void (*status[IDLE + 1])( gentity_t *self ); //IDLE will always be the last element in enum
		void (*nav[LOST + 1])( gentity_t *self ); //Navigation state
	} team;
  } funcs;
} bot_t;

// g_bot.c
void G_BotAdd( char *name, team_t team, int skill, int ignore );
void G_BotDelAll( void ); //Delete all
void G_BotDel( int clientNum );
void G_BotReload( gentity_t *ent, int clientNum );
void G_BotCmd( int clientNum, char *command, int value, int value2 );

// g_bot_nav.c
void BotTargetPath( gentity_t *self );
void BotFindNewPath( gentity_t *self );
void BotFindNextPath( gentity_t *self );
void BotBlocked( gentity_t *self );
void BotLost( gentity_t *self );
int distanceToTargetNode( gentity_t *self );
qboolean botAimAtPath( gentity_t *self );
void increasePathEssence( gentity_t *self );
void setCrumb( gentity_t *self, int closestpath );

// g_bot_util.c
int G_Rand( void ); //LEPE
int G_Rand_Range( int start, int end ); //LEPE
int botGetDistanceBetweenPlayer( gentity_t *self, gentity_t *player );
qboolean botTargetInRange( gentity_t *self, gentity_t *target );
qboolean botAimAtTarget( gentity_t *self, gentity_t *target );
qboolean botFindClosestEnemy( gentity_t *self );
qboolean botFindClosestFriend( gentity_t *self );
gentity_t *botFindClosestBuildable( gentity_t *self, float r, buildable_t buildable );

// g_bot_control.c
void BotControl( gentity_t *self, botMove move );
void BotDoMove( gentity_t *self, int msec ); 
void BotAddMove( gentity_t *self, botMove move, int time ); 
void BotCleanMove( gentity_t *self );
void BotRun( gentity_t *self );
void BotJump( gentity_t *self );
void BotStop( gentity_t *self );
void BotMoveRight( gentity_t *self );
void BotMoveLeft( gentity_t *self );
void BotMoveFwd( gentity_t *self );
void BotMoveBack( gentity_t *self );
void BotWallWalk( gentity_t *self );
void BotCrouch( gentity_t *self );
void BotStand ( gentity_t *self );
void BotGesture ( gentity_t *self );
void BotLookUp( gentity_t *self, int deg );
void BotLookDown( gentity_t *self, int deg );
void BotLookLeft( gentity_t *self, int deg );
void BotLookRight( gentity_t *self, int deg );
void BotTurn( gentity_t *self, int pitch, int yaw );
void BotPounce( gentity_t *self );
/*
void BotCharge( gentity_t *self );
void BotSprint( gentity_t *self );
void BotFlyUp( gentity_t *self );
void BotFlyDown( gentity_t *self );
 */
/* Combos */
void Bot_Strafe( gentity_t *self );

// g_bot_common.c
void BotExecState( gentity_t *self );
void BotInit( gentity_t *self );
void BotSpectator( gentity_t *self );
void BotThink( gentity_t *self );
void BotExplore( gentity_t *self );
void BotAttack( gentity_t *self );
void BotDefend( gentity_t *self );
void BotFollow( gentity_t *self );
void BotRetreat( gentity_t *self );
void BotEvade( gentity_t *self );
void BotHeal( gentity_t *self );
void BotBuild( gentity_t *self );
void BotRush( gentity_t *self );
void BotPatrol( gentity_t *self );
void BotImprove( gentity_t *self );
void BotIdle( gentity_t *self );
void G_BotGroupThink( void ); //called directly from g_main.c
void BotAim( gentity_t *self ); 
qboolean BotKeepThinking( gentity_t *self, botThinkLevel level);
void BotResetState( gentity_t *self, botState state );

// g_bot_alien.c
void BotInitAlien( gentity_t *self ); 
void BotAlienThink( gentity_t *self ); 
void BotBeforeSpawnAlien( gentity_t *self );
void BotEvolve( gentity_t *self ); 
void BotIdleAlien( gentity_t *self );
void BotBuildAlien( gentity_t *self );
void BotHealAlien( gentity_t *self );
void BotAttackAlien( gentity_t *self ); 
void BotTargetAlien( gentity_t *self ); 
void BotNavigateAlien( gentity_t *self ); 
void BotBlockedAlien( gentity_t *self ); 
gentity_t *botFindClosestBasilisk( gentity_t *self, float r );

// g_bot_human.c
void BotInitHuman( gentity_t *self ); 
void BotHumanThink( gentity_t *self ); 
void BotBeforeSpawnHuman( gentity_t *self );
void BotBuy( gentity_t *self ); 
void BotRepair( gentity_t *self );
void BotIdleHuman( gentity_t *self );
void BotBuildHuman( gentity_t *self );
void BotHealHuman( gentity_t *self );
void BotAttackHuman( gentity_t *self ); 
void BotTargetHuman( gentity_t *self ); 
void BotNavigateHuman( gentity_t *self ); 
void BotBlockedHuman( gentity_t *self ); 
void BotFollowHuman( gentity_t *self ); 
