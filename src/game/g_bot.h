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
#define BOT_MOVE_QUEUE		10
#define BOT_FIND_PATH_MAX	20
#define BOT_TURN_VAL		45.0f
#define BOT_TURN_SHORT		ANGLE2SHORT( BOT_TURN_VAL )
#define BOT_TURN_ANGLE_DIV	(360.0f / (float)BOT_TURN_VAL)
#define BOT_MOVE_PACE		100.0f
#define BOT_DEBUG_ALL		-1
#define BOT_NO_ENEMY		-1
#define BOT_WOBBLE			50

//timers
#define BOT_TIMER_AIM		50	//Just aim
#define BOT_TIMER_NAV		100	//Aim to path, find next path, etc.
#define BOT_TIMER_ACTION	500 //Perform states
#define BOT_TIMER_NAV_SECOND	1000 / BOT_TIMER_NAV	//used in Blocked code
#define BOT_TIMER_THINK_LEVEL_3_START_AT	3000  //this shift timer ahead so it won't overlap MAX
#define BOT_TIMER_THINK_LEVEL_MAX_START_AT	1000  //this shift timer ahead so it won't overlap LVL3
extern const int BOT_TIMER[];

/*
 * Bot's general headers
 */
typedef struct
{
	vec3_t coord;
	int	nextid[5];
	int	random;
	int	timeout;
	int	action;
    int essence[ NUM_TEAMS ]; //LEPE: used for ant colony algorithm
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
 * Example: G_BotDebug(self, BOT_VERB_DETAIL, BOT_DEBUG_MAIN + BOT_DEBUG_THINK + BOT_DEBUG_ALIEN, "This is test # %d\n", 1);
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
	BOT_DEBUG_TARGET	= 1 << 5,	//Debug how profile affected the outcome of something
		//<-------- new "debug by functions" should be inserted here
	//By files
	BOT_DEBUG_GENERAL	= 1 << 6,	//Debug g_bot.c
	BOT_DEBUG_MAIN		= 1 << 7,	//Debug g_main.c (bot related)
	BOT_DEBUG_ADMIN		= 1 << 8,	//Debug g_admin.c (bot related)
	BOT_DEBUG_ACTIVE	= 1 << 9,	//Debug g_active.c (bot related)
	BOT_DEBUG_ALIEN		= 1 << 10,	//Debug g_bot_alien.c
	BOT_DEBUG_HUMAN		= 1 << 11,	//Debug g_bot_human.c
	BOT_DEBUG_CONTROL	= 1 << 12,	//Debug g_bot_control.c
	BOT_DEBUG_UTIL		= 1 << 13,	//Debug g_bot_util.c
	BOT_DEBUG_COMMON	= 1 << 14,	//Debug g_bot_common.c
	BOT_DEBUG_SAY		= 1 << 15,	//Debug g_bot_say.c
	BOT_DEBUG_NAV		= 1 << 16, 	//Debug g_bot_nav.c
		//<-------- new "debug by file" should be inserted here. (No more than 30 or we are hitting the INT limit!)
} botDebugType;

typedef enum
{
	BOT_EMPTY_MOVE, 		//0
	BOT_WAIT,				//1
	BOT_RUN,				//2
	BOT_WALK,				//3
	BOT_JUMP,				//4
	BOT_CROUCH,				//5
	BOT_WALLWALK,			//6
	BOT_STAND,				//7
	BOT_MOVE_LEFT,			//8
	BOT_MOVE_RIGHT,			//9
	BOT_MOVE_FWD,			//10
	BOT_MOVE_BACK,			//11
	BOT_LOOK_CENTER,		//12
	BOT_LOOK_RANDOM,		//13
	BOT_LOOK_UP,			//14
	BOT_LOOK_DOWN,			//15
	BOT_LOOK_LEFT,			//16
	BOT_LOOK_RIGHT,			//17
	BOT_RESET_BUTTONS,		//18
	BOT_RESET_LEFT_RIGHT,	//19
	BOT_RESET_FWD_BACK,		//20
	BOT_MAIN_ATTACK,		//21
	BOT_SEC_ATTACK,			//22
	BOT_MID_ATTACK,			//23
	BOT_GESTURE,			//24
		//<-- add movements here
	BOT_STOP				//25
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
	UNDEFINED,		//0 used to automatically change states
	// Valid States:
	EXPLORE,		//1 explore the map: this will become one of the following:
	ATTACK,			//2 engage in combat
	DEFEND,			//3 stay in an area for some time (camp)
	FOLLOW, 		//4 following another player
	RETREAT, 		//5 go back to base
	EVADE, 			//6 perform evasive technique
	HEAL,			//7 heal itself
	REPAIR,			//8 repair building
	BUILD,			//9 build something
	RUSH,			//10 rushing into the enemy
	PATROL,			//11 patrol the area
	IMPROVE,		//12 improve: buy for humans, evolve for aliens
		//<-- add new states here	(add to: g_bot_common, g_bot_alien.c and g_bot_human.c)
	IDLE			//13 just think. it is also used as enum count
} botState;

typedef enum
{
	IDLENAV,		//0 don't do anything
	TARGETPATH,		//1 walk to a node 
	FINDNEXTPATH,	//2 looking for the next node //TODO: this and targetpath are not the same?
	FINDNEWPATH,	//3 looking for any close node
	BLOCKED, 		//4 blocked, trying to get out of there... 
		//<-- add new states here (add to: g_bot_common, g_bot_alien.c and g_bot_human.c)
	LOST			//5 lost... doing random stuff (like crying) //used also for enum count
} botNavState;

typedef struct
{
  //GENERAL
  gentity_t		*Enemy;
  gentity_t		*Friend;
  gentity_t		*Struct; //used for repairing or healing
  botState		state;
  qboolean		debug; 	//debug this bot
  //THINK: variables used to decide per thinking level
  struct {
	  botState 		state[THINK_LEVEL_MAX + 1];
  } think;
  struct {
  	  int		targetHits; //used in hit detection to check if we were able to hit the target
	  int 		angleToTarget; //simulate wobbling
  } var;
  //PATH: variables and properties related to Navigation
  struct {
	  botNavState	state;
	  qboolean		nextNode;
	  qboolean		pathChosen;
	  int			targetNode;
	  int			lastpathid;
	  int		    crumb[1000]; //path node history
	  //int		    *crumb; //path node history
	  int           numCrumb; //counter of max path length
	  int           lastJoint; //keep id of last junction
	  int 			blocked_try; //We increase this value each time we try to unblock the bot
	  vec3_t		blocked_origin; //keep where we got stucked
  } path;
  //MOVE: variables and properties related to Advanced Movements (combinations)
  struct {
	  struct {
		  botMove action;
		  int time; // time to wait until next action (in ms)
	  } queue[BOT_MOVE_QUEUE];
	  botMove blockedAction;
	  int read; //index used to know which queue slot to read from 
	  int write; //index used to know which queue slot to write into
	  qboolean exec; //used to start performing a movement
	  vec3_t topoint; //move to that coordinate without aiming
	  vec3_t lookat; //move aim to that point : disabled until we find a way to make it smooth (requires g_bot_step_aim = 1)
  } move;
  //TIMER: used to time actions (variables).
  struct {
	  int	think[THINK_LEVEL_MAX + 1]; //think timer per level
	  int	improve; 	//buytime for humans, evolvetime for aliens
	  int	aim; 		//variable used to time every aim loop (see BOT_TIMER_AIM)
	  int	nav; 		//variable used to time every nav loop (see BOT_TIMER_NAV)
	  int	action; 	//variable used to time every action loop (see BOT_TIMER_ACTION)
	  int 	move; 		//used in g_bot_control.c for the movement queue
	  int	foundPath; 	//on BotFindN***Path(): if a new/next path is found, we reset this timer
	  int	hit;		//time to identify if we hit some target
  } timer;
  //PROFILE: bot personality
  /*
  struct {
	  int	obedient; //follows esssence or it goes to explore often
	  int	aggressive; //try to attack more often or stays at base (camp) and repairs/build more
	  int	cooperative; //try to keep close to other bots
	  int	bold; //(daring). Will keep attacking even low HP or will try to pursue more.
	  int	greedy; //will try to save creds/evos as much as possible. On the other hand: will spent everything as it gain it
	  int	evasive; //The more, it will try not to go straight to the target but will be slower. 
	  int	talkative; //How much it talks
	  int	impulsive; //How much it takes to take decisions
  } profile;
   */
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
		int  (*targetRank)( gentity_t *self, gentity_t *target ); 	//target prioritization
		void (*status[IDLE + 1])( gentity_t *self ); //IDLE will always be the last element in enum
		void (*nav[LOST + 1])( gentity_t *self ); //Navigation state
	} base;
	//Function that are specific for each team (NOTE: Do not call base functions within team functions).
	struct {
		void (*think)( gentity_t *self );		
		void (*spec)( gentity_t *self );
		int  (*targetRank)( gentity_t *self, gentity_t *target, float rank ); 	//target prioritization
		void (*status[IDLE + 1])( gentity_t *self ); //IDLE will always be the last element in enum
		void (*nav[LOST + 1])( gentity_t *self ); //Navigation state
	} team;
  } funcs;
} bot_t;

// g_bot.c
void G_BotAdd( char *name, team_t team );
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
void increasePathEssence( gentity_t *self, gentity_t *target, int essence );
void setCrumb( gentity_t *self, int closestpath );

// g_bot_util.c
int G_Rand( void ); //LEPE
int G_Rand_Range( int start, int end ); //LEPE
int botGetDistanceBetweenPlayer( gentity_t *self, gentity_t *player );
int botGetAngleBetweenPlayersView( gentity_t *self, gentity_t *player );
int botGetAngleToPoint( gentity_t *self, vec3_t point );
int botGetAngleToTarget( gentity_t *self, gentity_t *target );
int botGetHealthPct( gentity_t *self );
int botFindClosestNode( gentity_t *self );
int botFindEnemy( gentity_t *self, int maxRange );
qboolean botFindPath( int *path , int goal, int start );
qboolean botAimAtTarget( gentity_t *self, gentity_t *target, qboolean pitch);
qboolean botFindClosestFriend( gentity_t *self );
qboolean botSameTeam( gentity_t *ent1, gentity_t *ent2 );
qboolean botHitTarget( gentity_t *self, int time );
void botResetHitTarget( gentity_t *self );
gentity_t *botFindClosestBuildable( gentity_t *self, float r, buildable_t buildable );
gentity_t *botFindDamagedStructure( gentity_t *self, float r, int damage );

// g_bot_control.c
void BotControl( gentity_t *self, botMove move );
void BotStartMove( gentity_t *self, botMove block );
void BotDoMove( gentity_t *self, int msec ); 
void BotAddMove( gentity_t *self, botMove move, int time ); 
void BotCleanMove( gentity_t *self );
void BotClearQueue( gentity_t *self );
void BotRun( gentity_t *self );
void BotWalk( gentity_t *self );
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
void BotMainAttack ( gentity_t *self );
void BotSecAttack ( gentity_t *self );
void BotMidAttack ( gentity_t *self );
void BotLookUp( gentity_t *self, int degrees );
void BotLookDown( gentity_t *self, int degrees ); 
void BotLookLeft( gentity_t *self, int degrees ); 
void BotLookRight( gentity_t *self, int degrees ); 
void BotMoveToPoint( gentity_t *self, vec3_t point ); 
void BotMoveToPointClear( gentity_t *self ); 
void BotMoveToPointExec( gentity_t *self );//used in g_active.c
void BotAimToPoint( gentity_t *self, vec3_t point ); //used in g_active.c
void BotAimToPointClear( gentity_t *self );
void BotAimToPointExec( gentity_t *self ); //used in g_active.c
qboolean BotIsMoving( gentity_t *self, botMove move );

/*
void BotLookUp( gentity_t *self, int deg );
void BotLookDown( gentity_t *self, int deg );
void BotLookLeft( gentity_t *self, int deg );
void BotLookRight( gentity_t *self, int deg );
void BotTurn( gentity_t *self, int pitch, int yaw );
 */
/* Combos */
void Bot_Strafe( gentity_t *self );
void Bot_Pounce( gentity_t *self, int angle );
void Bot_FullLuci( gentity_t *self );
/*
void Bot_Charge( gentity_t *self );
void Bot_Sprint( gentity_t *self );
void Bot_FlyUp( gentity_t *self );
void Bot_FlyDown( gentity_t *self );
 */

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
void BotFindTarget( gentity_t *self );
void BotResetState( gentity_t *self, botState state );
int BotTargetRank( gentity_t *self, gentity_t *target );
qboolean BotKeepThinking( gentity_t *self, botThinkLevel level);

// g_bot_alien.c
void BotInitAlien( gentity_t *self ); 
void BotAlienThink( gentity_t *self ); 
void BotBeforeSpawnAlien( gentity_t *self );
void BotEvolve( gentity_t *self ); 
void BotIdleAlien( gentity_t *self );
void BotBuildAlien( gentity_t *self );
void BotHealAlien( gentity_t *self );
void BotRetreatAlien( gentity_t *self );
void BotAttackAlien( gentity_t *self ); 
void BotNavigateAlien( gentity_t *self ); 
void BotBlockedAlien( gentity_t *self ); 
int BotTargetRankAlien(gentity_t *self, gentity_t *target, float rank );
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
void BotNavigateHuman( gentity_t *self ); 
void BotBlockedHuman( gentity_t *self ); 
void BotFollowHuman( gentity_t *self ); 
int BotTargetRankHuman(gentity_t *self, gentity_t *target, float rank );
