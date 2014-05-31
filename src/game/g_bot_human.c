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
 * Human bot code 
 */

#include "g_local.h"

void BotInitHuman( gentity_t *self ){
	//Initialization of TEAM funtions
	self->bot->funcs.team.spec				= BotBeforeSpawnHuman;
	//self->bot->funcs.team.target			= BotTargetHuman;
	self->bot->funcs.team.targetRank		= BotTargetRankHuman;
	self->bot->funcs.team.think				= BotHumanThink;
	self->bot->funcs.team.status[IDLE]		= BotIdleHuman;
	self->bot->funcs.team.status[ATTACK]	= BotAttackHuman;
	self->bot->funcs.team.status[HEAL]		= BotHealHuman;
	self->bot->funcs.team.status[BUILD]		= BotBuildHuman;
	self->bot->funcs.team.status[IMPROVE]	= BotBuy;
	self->bot->funcs.team.status[REPAIR]	= BotRepair;
	//--- nav state functions
	self->bot->funcs.team.nav[TARGETPATH]	= BotNavigateHuman;
	self->bot->funcs.team.nav[BLOCKED]		= BotBlockedHuman;
	//default % of buying //TODO: read it from file or vars
	//TODO: clear these values on load (or data may be corrupted)
	self->bot->set.lcannon[S3] 	= 50;
	self->bot->set.prifle[S3] 	= 40;
	self->bot->set.prifle[S2] 	= 50;
	self->bot->set.chaingun[S3] = 50;
	self->bot->set.chaingun[S2] = 40;
	self->bot->set.chaingun[S1] = 50;
	self->bot->set.flamer[S3] 	= 30;
	self->bot->set.flamer[S2] 	= 60;
	self->bot->set.mdriver[S3] 	= 20;
	self->bot->set.mdriver[S2] 	= 50;
	self->bot->set.mdriver[S1] 	= 80;
	self->bot->set.lasgun[S3] 	= 40;
	self->bot->set.lasgun[S2] 	= 50;
	self->bot->set.lasgun[S1] 	= 80;
	self->bot->set.shotgun[S3] 	= 10;
	self->bot->set.shotgun[S2] 	= 20;
	self->bot->set.shotgun[S1] 	= 80;
	self->bot->set.painsaw[S3] 	= 40;
	self->bot->set.painsaw[S2] 	= 40;
	self->bot->set.painsaw[S1] 	= 40;
	self->bot->set.nade[S3] 	= 80;
	self->bot->set.nade[S2] 	= 80;
	self->bot->set.battery[S3] 	= 50;
	self->bot->set.battery[S2] 	= 50;
	self->bot->set.armour[S3] 	= 100;
	self->bot->set.armour[S2] 	= 100;
	self->bot->set.armour[S1] 	= 100;
	self->bot->set.helmet[S2] 	= 100;
	self->bot->set.helmet[S3] 	= 100;
	self->bot->set.battlesuit[S3]= 100;
}
/**
 * Decide if spawn as ckit or mgun
 * @param self
 * //TODO: add decision
 */
void BotBeforeSpawnHuman( gentity_t *self )
{
	int clientNum;
    clientNum = self->client->ps.clientNum;
	//is enemy near node? YES -> mgun
	//are any building destroyed near node? (need to keep record of initial builds) NO -> mgun 
	//any ckit player near node? YES -> mgun
	//any building damaged? -do we have DC? YES -> mgun
	//several highly damaged buildings? NO -> mgun
    G_BotDebug(self, BOT_VERB_NORMAL, BOT_DEBUG_HUMAN + BOT_DEBUG_THINK, "Bot is about to spawn\n");
	self->client->pers.classSelection = PCL_HUMAN;
	self->client->ps.stats[ STAT_CLASS ] = PCL_HUMAN;
	//check in reference to RC or a node
	if(G_Rand() < 10) { //G_TimeTilSuddenDeath() > 0 && 
		self->client->pers.humanItemSelection = WP_HBUILD; 
	} else {
		self->client->pers.humanItemSelection = WP_MACHINEGUN;
	}
	G_PushSpawnQueue( &level.humanSpawnQueue, clientNum );
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
void BotHumanThink( gentity_t *self )
{
	//If we have an enemy and we are a builder, use blaster
	if(self->bot->Enemy) {
		//If we have an enemy, change the weapon
		if(BG_InventoryContainsWeapon( WP_HBUILD, self->client->ps.stats )) G_ForceWeaponChange( self, WP_BLASTER );
		self->bot->think.state[ THINK_LEVEL_2 ] = ATTACK;
	} 
	//If we are low in health and we are not healing and we have mkit, use it!
	//TODO: remove hard value and set it to a variable
	if((self->health < 40 || (self->health < 60 && (self->lastHealth > self->health))) 
				&& !(self->client->ps.stats[ STAT_STATE ] & SS_HEALING_2X) 
				&& BG_InventoryContainsUpgrade( UP_MEDKIT, self->client->ps.stats )) {
		BG_ActivateUpgrade( UP_MEDKIT, self->client->ps.stats );
		BotResetState( self, HEAL );
	} 
	
	//Repair if has a ckit
	if(BG_InventoryContainsWeapon( WP_HBUILD, self->client->ps.stats )) {
		self->bot->Struct = botFindDamagedStructure( self , 300, 100 );
		if(self->bot->Struct) {
			self->bot->think.state[ THINK_LEVEL_2 ] = REPAIR;
			G_BotDebug(self, BOT_VERB_DETAIL, BOT_DEBUG_HUMAN + BOT_DEBUG_STATE, "Suggesting Repair as LEVEL2 in HumanThink\n");
		} else {
			BotResetState( self, REPAIR );
			self->bot->Struct = botFindClosestBuildable( self, 300, BA_H_ARMOURY );
			if(self->bot->Struct) {
				self->bot->think.state[ THINK_LEVEL_1 ] = IMPROVE;
				G_BotDebug(self, BOT_VERB_DETAIL, BOT_DEBUG_HUMAN + BOT_DEBUG_STATE, "Suggesting Improve as LEVEL1 in HumanThink -> Repair\n");
			}
		}
	}
	//Buy stuff from arm if within range
	if(level.time - self->bot->timer.improve > 10000 && !(self->bot->Struct)) {
		self->bot->Struct = botFindClosestBuildable( self, 300, BA_H_ARMOURY );
		if(self->bot->Struct) {
			self->bot->think.state[ THINK_LEVEL_1 ] = IMPROVE;
			G_BotDebug(self, BOT_VERB_DETAIL, BOT_DEBUG_HUMAN + BOT_DEBUG_STATE, "Suggesting Improve as LEVEL1 in HumanThink\n");
		} else {
			BotResetState( self, IMPROVE );
		}
	}

	if(!self->bot->Enemy && self->bot->state != HEAL) { 
		if(G_Rand() < 30) {
			if(botFindClosestFriend( self )) {
			//self->bot->think.state[ THINK_LEVEL_1 ] = FOLLOW;
			}
		}
	}
	///////////////////////// LEVEL 1 /////////////////////////
	if(BotKeepThinking( self , THINK_LEVEL_1)) {
	}
	
	///////////////////////// LEVEL 2 /////////////////////////
	if(BotKeepThinking( self , THINK_LEVEL_2)) {
	}
	///////////////////////// LEVEL 3 /////////////////////////
	if(BotKeepThinking( self , THINK_LEVEL_3)) {
		if(self->client->pers.classSelection > PCL_HUMAN_BSUIT && botGetHealthPct( self ) < 30) {
			self->bot->think.state[ THINK_LEVEL_3 ] = RETREAT;
		}
		//TODO: if the target is not in our view range, set THINK_LEVEL_1 to UNDEFINED.
		if(!BG_InventoryContainsUpgrade( UP_MEDKIT, self->client->ps.stats )) {
			self->bot->Struct = botFindClosestBuildable( self, 200, BA_H_MEDISTAT );
			if(self->bot->Struct) {
				//Suggest Heal if low HP
				if(self->health <= 20) {
					self->bot->think.state[ THINK_LEVEL_3 ] = HEAL;
					G_BotDebug(self, BOT_VERB_DETAIL, BOT_DEBUG_HUMAN + BOT_DEBUG_STATE, "Suggesting Heal as LEVEL3 in HumanThink\n");
				} else if(self->health <= 50) {
					self->bot->think.state[ THINK_LEVEL_2 ] = HEAL;
					G_BotDebug(self, BOT_VERB_DETAIL, BOT_DEBUG_HUMAN + BOT_DEBUG_STATE, "Suggesting Heal as LEVEL2 in HumanThink\n");
				} else if(self->health < 90) {
					self->bot->think.state[ THINK_LEVEL_1 ] = HEAL;
					G_BotDebug(self, BOT_VERB_DETAIL, BOT_DEBUG_HUMAN + BOT_DEBUG_STATE, "Suggesting Heal as LEVEL1 in HumanThink\n");
				}
			}
		}
	}
	G_BotDebug(self, BOT_VERB_DETAIL, BOT_DEBUG_HUMAN + BOT_DEBUG_THINK,"HUMAN THINK: LVL1:%d, LVL2:%d, LVL3:%d, MAX:%d \n", 
			self->bot->think.state[ THINK_LEVEL_1 ],
			self->bot->think.state[ THINK_LEVEL_2 ],
			self->bot->think.state[ THINK_LEVEL_3 ],
			self->bot->think.state[ THINK_LEVEL_MAX ]
			);
	G_BotDebug(self, BOT_VERB_DETAIL, BOT_DEBUG_HUMAN + BOT_DEBUG_THINK,"Enemy:%p, Structure: %p\n", self->bot->Enemy, self->bot->Struct);
}

/**
 * Human navigation 
 * @param self
 */
void BotNavigateHuman( gentity_t *self ){
	//If we are tired, stop, crouch and wait...
	if(self->client->ps.stats[ STAT_STAMINA ] < 100)
	{
		BotStop( self );
		BotCrouch( self );
		self->bot->timer.foundPath += 3000;
	}
}
	
/**
 * If a human get blocked...
 * The bot will try to go either one way (left) or the other (right) with
 * some random behaviour.
 * Every 2 tries will jump.
 * @param self
 */
void BotBlockedHuman( gentity_t *self ){
	int try = self->bot->path.blocked_try;
	qboolean low_stamina = self->client->ps.stats[ STAT_STAMINA ] < 100;
	/* If we have low stamina, we can't keep jumping, so we reset it
	 * to help the bot to remove block */
	if(low_stamina) self->client->ps.stats[ STAT_STAMINA ] = 1000;

	G_BotDebug(self, BOT_VERB_DETAIL, BOT_DEBUG_HUMAN + BOT_DEBUG_NAVSTATE, "Trying to unblock. Try: %d\n", try);
	if(try <= 0) {
		BotMoveFwd( self );
		VectorCopy(self->r.currentOrigin, self->bot->path.blocked_origin);
		if(!low_stamina) BotJump( self );
	} else if(try == BOT_TIMER_NAV_SECOND) {
		BotControl( self, BOT_LOOK_RANDOM );
	} 
	if(try > BOT_TIMER_NAV_SECOND) {
		self->bot->path.blocked_try = 0; 
		G_BotDebug(self, BOT_VERB_DETAIL, BOT_DEBUG_HUMAN + BOT_DEBUG_NAVSTATE, "Reset blocked_try to 0\n", self->client->pers.netname );
		//If there is a friend nearby, try to follow him
		botFindClosestFriend( self );
	} else {
		//we set next try 
		self->bot->path.blocked_try++;
	}
}

/**
 * Human bots goes shopping
 * @param self [gentity_t] a BOT
 */
void BotBuy( gentity_t *self )
{
	qboolean boughtweap = qfalse;
	//qboolean boughtup = qfalse;
	qboolean buybatt = qfalse;
	qboolean energyweap = qfalse;
	weapon_t weapon;
	upgrade_t upgrade;
    vec3_t newOrigin;
	//int maxAmmo, maxClips;
    int prob = 0; //probability to buy item //LEPE
	int clientNum = self->client - level.clients;
	if(self->bot->Struct->s.modelindex != BA_H_ARMOURY || ! G_Visible(self, self->bot->Struct, CONTENTS_SOLID)) {
		self->bot->Struct = NULL;
		return;
	}
	//Do not buy if you are not close enough
	if(!G_BuildableRange( self->client->ps.origin, 100, BA_H_ARMOURY )){ return; }
	//Clear going to ARM
	self->bot->Struct = NULL;
    
    /************************ SELL WEAPONS *******************************/

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

	/******************************* CHECK FOR DAMAGED BUILDINGS **************************/
	self->bot->Struct = botFindDamagedStructure( self , 300, 50 );
	if(self->bot->Struct) {
		weapon = WP_HBUILD;
		boughtweap = qtrue;
		G_BotDebug(self, BOT_VERB_NORMAL, BOT_DEBUG_HUMAN + BOT_DEBUG_THINK, "Changed to CKIT\n");
	}
	//Remove CKIT
	if(BG_InventoryContainsWeapon( WP_HBUILD, self->client->ps.stats ))
	{
		self->client->ps.stats[ STAT_WEAPON ] = WP_NONE;
	}
    /****************************** BUY WEAPONS AND EQUIP *********************************/

	prob = self->bot->set.battlesuit[g_humanStage.integer];
	if(g_humanStage.integer == 2 && (G_Rand() < prob))
	{
		upgrade = UP_BATTLESUIT;
		if(!BG_InventoryContainsUpgrade( upgrade, self->client->ps.stats ) && 
			BG_Upgrade( upgrade )->price <= (short)self->client->ps.persistant[ PERS_CREDIT ] &&
			!(BG_Upgrade( upgrade )->slots & BG_SlotsForInventory( self->client->ps.stats )))
		{
			BG_AddUpgradeToInventory( upgrade, self->client->ps.stats );
			VectorCopy( newOrigin, self->s.pos.trBase );
			self->client->ps.stats[ STAT_CLASS ] = PCL_HUMAN_BSUIT;
			self->client->pers.classSelection = PCL_HUMAN_BSUIT;
			self->client->ps.eFlags ^= EF_TELEPORT_BIT;
			ClientUserinfoChanged( clientNum, qfalse );
			G_AddCreditToClient( self->client, -(short)BG_Upgrade( upgrade )->price, qfalse );
		}
	}
	upgrade = UP_LIGHTARMOUR;
	prob = self->bot->set.armour[g_humanStage.integer];
	if((G_Rand() < prob) &! BG_InventoryContainsUpgrade( upgrade, self->client->ps.stats ) && 
		BG_Upgrade( upgrade )->price <= (short)self->client->ps.persistant[ PERS_CREDIT ] &&
		!(BG_Upgrade( upgrade )->slots & BG_SlotsForInventory( self->client->ps.stats )) && 
		!BG_InventoryContainsUpgrade( UP_BATTLESUIT, self->client->ps.stats ))
	{
		BG_AddUpgradeToInventory( upgrade, self->client->ps.stats );
		G_AddCreditToClient( self->client, -(short)BG_Upgrade( upgrade )->price, qfalse );
	}
	prob = self->bot->set.helmet[g_humanStage.integer];
	if(g_humanStage.integer > 0 && (G_Rand() < prob))
	{
		upgrade = UP_HELMET;
		if(!BG_InventoryContainsUpgrade( upgrade, self->client->ps.stats ) && 
			BG_Upgrade( upgrade )->price <= (short)self->client->ps.persistant[ PERS_CREDIT ] &&
			!(BG_Upgrade( upgrade )->slots & BG_SlotsForInventory( self->client->ps.stats )) && 
			!BG_InventoryContainsUpgrade( UP_BATTLESUIT, self->client->ps.stats ))
		{
			BG_AddUpgradeToInventory( upgrade, self->client->ps.stats );
			G_AddCreditToClient( self->client, -(short)BG_Upgrade( upgrade )->price, qfalse );
		}
	}
	//LEPE: from here, we add some % of buying weapons
	prob = self->bot->set.lcannon[g_humanStage.integer];
	if((G_Rand() < prob) && g_humanStage.integer == 2 && g_bot_lcannon.integer > 0) 
	{
		weapon = WP_LUCIFER_CANNON;
		if( !BG_InventoryContainsWeapon( weapon, self->client->ps.stats ) &&
			BG_Weapon( weapon )->price <= (short)self->client->ps.persistant[ PERS_CREDIT ] &&
			!(BG_Weapon( weapon )->slots & BG_SlotsForInventory( self->client->ps.stats )))
		{
			boughtweap = qtrue;
			buybatt = qtrue;
			energyweap = qtrue;
			G_BotDebug(self, BOT_VERB_NORMAL, BOT_DEBUG_HUMAN + BOT_DEBUG_THINK, "Bought LUCIFER_CANNON\n");
		}
	}
	prob = self->bot->set.prifle[g_humanStage.integer];
	if((G_Rand() < prob) && g_humanStage.integer > 0 && boughtweap == qfalse && g_bot_prifle.integer > 0)
	{
		weapon = WP_PULSE_RIFLE;
		if( !BG_InventoryContainsWeapon( weapon, self->client->ps.stats ) &&
			BG_Weapon( weapon )->price <= (short)self->client->ps.persistant[ PERS_CREDIT ] &&
			!(BG_Weapon( weapon )->slots & BG_SlotsForInventory( self->client->ps.stats )))
		{
			boughtweap = qtrue;
			buybatt = qtrue;
			energyweap = qtrue;
			G_BotDebug(self, BOT_VERB_NORMAL, BOT_DEBUG_HUMAN + BOT_DEBUG_THINK, "Bought PULSE\n");
		}
	}
	prob = self->bot->set.chaingun[g_humanStage.integer];
	if((G_Rand() < prob) && boughtweap == qfalse && g_bot_chaingun.integer > 0)
	{
		weapon = WP_CHAINGUN;
		if( !BG_InventoryContainsWeapon( weapon, self->client->ps.stats ) &&
			BG_Weapon( weapon )->price <= (short)self->client->ps.persistant[ PERS_CREDIT ] &&
			!(BG_Weapon( weapon )->slots & BG_SlotsForInventory( self->client->ps.stats )))
		{
			boughtweap = qtrue;
			G_BotDebug(self, BOT_VERB_NORMAL, BOT_DEBUG_HUMAN + BOT_DEBUG_THINK,"Bought CHAINGUN\n");
		}
	}
	prob = self->bot->set.flamer[g_humanStage.integer];
	if((G_Rand() < prob) && g_humanStage.integer > 0 && boughtweap == qfalse && g_bot_flamer.integer > 0) 
	{
		weapon = WP_FLAMER;
		if( !BG_InventoryContainsWeapon( weapon, self->client->ps.stats ) &&
			BG_Weapon( weapon )->price <= (short)self->client->ps.persistant[ PERS_CREDIT ] &&
			!(BG_Weapon( weapon )->slots & BG_SlotsForInventory( self->client->ps.stats )))
		{
			boughtweap = qtrue;
			G_BotDebug(self, BOT_VERB_NORMAL, BOT_DEBUG_HUMAN + BOT_DEBUG_THINK,"Bought FLAMER\n");
		}
	}
	prob = self->bot->set.mdriver[g_humanStage.integer];
	if((G_Rand() < prob) && boughtweap == qfalse && g_bot_mdriver.integer > 0)
	{
		weapon = WP_MASS_DRIVER;
		if( !BG_InventoryContainsWeapon( weapon, self->client->ps.stats ) &&
			BG_Weapon( weapon )->price <= (short)self->client->ps.persistant[ PERS_CREDIT ] &&
			!(BG_Weapon( weapon )->slots & BG_SlotsForInventory( self->client->ps.stats )))
		{
			boughtweap = qtrue;
			buybatt = qtrue;
			energyweap = qtrue;
			G_BotDebug(self, BOT_VERB_NORMAL, BOT_DEBUG_HUMAN + BOT_DEBUG_THINK,"Bought MASS_DRIVER\n");
		}
	}
	prob = self->bot->set.lasgun[g_humanStage.integer];
	if((G_Rand() < prob) && boughtweap == qfalse && g_bot_lasgun.integer > 0)
	{
		weapon = WP_LAS_GUN;
		if( !BG_InventoryContainsWeapon( weapon, self->client->ps.stats ) &&
			BG_Weapon( weapon )->price <= (short)self->client->ps.persistant[ PERS_CREDIT ] &&
			!(BG_Weapon( weapon )->slots & BG_SlotsForInventory( self->client->ps.stats )))
		{
			boughtweap = qtrue;
			buybatt = qtrue;
			energyweap = qtrue;
			G_BotDebug(self, BOT_VERB_NORMAL, BOT_DEBUG_HUMAN + BOT_DEBUG_THINK,"Bought LAS_GUN\n");
		}
	}
	prob = self->bot->set.shotgun[g_humanStage.integer];
	if((G_Rand() < prob) && boughtweap == qfalse && g_bot_shotgun.integer > 0)
	{
		weapon = WP_SHOTGUN;
		if( !BG_InventoryContainsWeapon( weapon, self->client->ps.stats ) &&
			BG_Weapon( weapon )->price <= (short)self->client->ps.persistant[ PERS_CREDIT ] &&
			!(BG_Weapon( weapon )->slots & BG_SlotsForInventory( self->client->ps.stats )))
		{
			boughtweap = qtrue;
			G_BotDebug(self, BOT_VERB_NORMAL, BOT_DEBUG_HUMAN + BOT_DEBUG_THINK,"Bought SHOTGUN\n");
		}
	}
	prob = self->bot->set.painsaw[g_humanStage.integer];
	if((G_Rand() < prob) && boughtweap == qfalse && g_bot_painsaw.integer > 0)
	{
		weapon = WP_PAIN_SAW;
		if( !BG_InventoryContainsWeapon( weapon, self->client->ps.stats ) &&
			BG_Weapon( weapon )->price <= (short)self->client->ps.persistant[ PERS_CREDIT ] &&
			!(BG_Weapon( weapon )->slots & BG_SlotsForInventory( self->client->ps.stats )))
		{
			boughtweap = qtrue;
			G_BotDebug(self, BOT_VERB_NORMAL, BOT_DEBUG_HUMAN + BOT_DEBUG_THINK,"Bought PAIN_SAW\n");
		}
	}
	//100% prob if reached this point
	if(boughtweap == qfalse && g_bot_mgun.integer > 0)
	{
		weapon = WP_MACHINEGUN;
		if( !BG_InventoryContainsWeapon( weapon, self->client->ps.stats ) &&
			BG_Weapon( weapon )->price <= (short)self->client->ps.persistant[ PERS_CREDIT ] &&
			!(BG_Weapon( weapon )->slots & BG_SlotsForInventory( self->client->ps.stats )))
		{
			boughtweap = qtrue;
			G_BotDebug(self, BOT_VERB_NORMAL, BOT_DEBUG_HUMAN + BOT_DEBUG_THINK,"MACHINEGUN for FREE!\n");
		}
	}
	//Buy Nades
	upgrade = UP_GRENADE;
	prob = self->bot->set.nade[g_humanStage.integer];
	if((G_Rand() < prob) &! BG_InventoryContainsUpgrade( upgrade, self->client->ps.stats ) && g_humanStage.integer > 0 && 
			BG_Upgrade( upgrade )->price <= (short)self->client->ps.persistant[ PERS_CREDIT ]) {
		BG_AddUpgradeToInventory( upgrade, self->client->ps.stats );
		G_AddCreditToClient( self->client, -(short)BG_Upgrade( upgrade )->price, qfalse );
		G_BotDebug(self, BOT_VERB_NORMAL, BOT_DEBUG_HUMAN + BOT_DEBUG_THINK,"NADE Bought\n");
	}
	//Buy Selected Weapon
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
		G_BotDebug(self, BOT_VERB_NORMAL, BOT_DEBUG_HUMAN + BOT_DEBUG_THINK,"BLASTER?\n");
	}
	upgrade = UP_BATTPACK;
	prob = self->bot->set.battery[g_humanStage.integer];
	if((G_Rand() < prob) &! BG_InventoryContainsUpgrade( upgrade, self->client->ps.stats ) && 
		BG_Upgrade( upgrade )->price <= (short)self->client->ps.persistant[ PERS_CREDIT ] &&
		!(BG_Upgrade( upgrade )->slots & BG_SlotsForInventory( self->client->ps.stats )) && 
		!BG_InventoryContainsUpgrade( UP_BATTLESUIT, self->client->ps.stats ) && 
		buybatt == qtrue)
	{
		BG_AddUpgradeToInventory( upgrade, self->client->ps.stats );
		G_AddCreditToClient( self->client, -(short)BG_Upgrade( upgrade )->price, qfalse );
		G_BotDebug(self, BOT_VERB_NORMAL, BOT_DEBUG_HUMAN + BOT_DEBUG_THINK,"Bought BATTPACK\n");
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
	ClientUserinfoChanged( clientNum, qfalse );
	self->bot->timer.improve = level.time;
	//We reset current state
	BotResetState( self, IMPROVE );
	return;
}

/**
 * Attack to target if its in range (see: g_bot_alien.c botAttackIfTargetInRange)
 * @param self [gentity_t] a BOT
 * //TODO: if target is not visible, use pathfinding (when having helmet).
 */
void BotAttackHuman( gentity_t *self )
{
	int tooCloseDistance = 200; 
	int distance = botGetDistanceBetweenPlayer(self, self->bot->Enemy);
	
    G_BotDebug(self, BOT_VERB_DETAIL, BOT_DEBUG_UTIL + BOT_DEBUG_HUMAN, "Enemy: %p\n", self->bot->Enemy);
    G_BotDebug(self, BOT_VERB_DETAIL, BOT_DEBUG_UTIL + BOT_DEBUG_HUMAN, "Distance: %d\n", distance);
	//Use nades
	if(distance < tooCloseDistance && (self->bot->Enemy->s.eType == ET_BUILDABLE || self->bot->Enemy->s.eType == PCL_ALIEN_LEVEL4)) {	//LEPE: Nades on buildings or tyrants
	    if(BG_InventoryContainsUpgrade(UP_GRENADE,self->client->ps.stats)) {
            G_BotDebug(self, BOT_VERB_NORMAL, BOT_DEBUG_UTIL + BOT_DEBUG_HUMAN + BOT_DEBUG_THINK, "NADE ACTIVATED!\n");
            BG_ActivateUpgrade(UP_GRENADE,self->client->ps.stats);
	    }
	}
	
	if(distance < g_human_range.integer) 
	{
		//If its a player or bot
		if(self->bot->Enemy->s.eType == ET_PLAYER) {
			if(distance < 300 && 
				self->client->ps.weapon != WP_PAIN_SAW && 
				self->client->ps.weapon != WP_FLAMER)
			{
				BotAddMove( self, BOT_MOVE_BACK, BOT_TIMER_ACTION);
				BotStartMove( self, BOT_MOVE_FWD);
				Bot_Strafe( self );
			}
			else
			{
				BotRun( self );
				Bot_Strafe( self );
			}
		} 
		else if(self->bot->Enemy->s.eType == ET_BUILDABLE)  //If its a structure
		{
			if(self->client->ps.weapon == WP_PAIN_SAW || self->client->ps.weapon == WP_FLAMER)
			{
				BotStand( self );
				if(self->client->ps.weapon == WP_FLAMER && distance < FLAMER_RADIUS) {
					BotControl( self, BOT_RESET_FWD_BACK);
				} else {
					BotMoveFwd( self );
				}
				//Only if we are close enough that we should hit it 
				if(distance < FLAMER_RADIUS) {
					if(!BotHitTarget( self , 1000 )) {
						BotStand( self );
						BotAddMove( self, G_Rand() < 50 ? BOT_MOVE_LEFT : BOT_MOVE_RIGHT, BOT_TIMER_ACTION);
						BotStartMove( self, BOT_EMPTY_MOVE );
					}
				}
			}
			else
			{
				if(((self->bot->Enemy->s.modelindex == BA_A_ACIDTUBE && distance < ACIDTUBE_RANGE) ||
				   (self->bot->Enemy->s.modelindex == BA_A_HIVE && distance < HIVE_SENSE_RANGE) || 
					(distance < OVERMIND_ATTACK_RANGE)) && self->health < 50 && botGetHealthPct( self->bot->Enemy ) > 50) {
					BotStand( self );
					BotAddMove( self, BOT_MOVE_BACK, BOT_TIMER_ACTION);
					BotStartMove( self, BOT_MOVE_FWD);
				} else {
					BotStop( self );
					BotCrouch( self );
				}
				if(!BotHitTarget( self, 1000 )) {
					BotAddMove( self, G_Rand() < 50 ? BOT_MOVE_LEFT : BOT_MOVE_RIGHT, BOT_TIMER_ACTION);
					BotAddMove( self, G_Rand() < 50 ? BOT_MOVE_FWD: BOT_MOVE_BACK, BOT_TIMER_ACTION);
					BotStartMove( self, BOT_EMPTY_MOVE );
				}
			}
		}
		
		//Use blaster if weapon out of ammo. self->s.weapon is current weapon that might not be out.
		if(self->client->ps.weapon != WP_BLASTER && 
			self->client->ps.weapon != WP_PAIN_SAW && 
			self->client->ps.weapon != WP_GRENADE && 
			level.time - self->bot->timer.improve > 1000)
		{
			if(self->client->ps.ammo <= 0 && self->client->ps.clips <= 0)
			{
				G_ForceWeaponChange( self, WP_BLASTER );
			}
		}
		
		if(self->client->ps.weapon == WP_FLAMER)
		{
			if(distance < 200) {
				BotMainAttack( self );
			}
		}
		else if(self->client->ps.weapon == WP_LUCIFER_CANNON)
		{
			if(self->bot->Enemy->s.eType == ET_BUILDABLE || self->bot->Enemy->s.eType == PCL_ALIEN_LEVEL4) {
				Bot_FullLuci( self );
			} else {
				BotSecAttack( self );
			}
		}
		else
		{
			BotMainAttack( self );
		}
	} else {
		self->bot->Enemy = NULL;
		BotControl( self, BOT_RESET_BUTTONS );
	}
}

/**
 * 
 * @param self
 */
void BotIdleHuman( gentity_t *self ) {
	//Recharge energy weapons near RC or Repeater
	if((G_BuildableRange( self->client->ps.origin, 100, BA_H_REACTOR ) ||
		G_BuildableRange( self->client->ps.origin, 100, BA_H_REPEATER )) && 
		level.time - self->bot->timer.improve > 6000)
	{
		G_GiveClientMaxAmmo( self, qtrue );
		self->bot->timer.improve = level.time;
	}
	//If any weapon is being used and it is disabled by command, set it to blaster:
	if( (self->client->ps.weapon == WP_MACHINEGUN && g_bot_mgun.integer <= 0) ||
		(self->client->ps.weapon == WP_SHOTGUN && g_bot_shotgun.integer <= 0) ||
		(self->client->ps.weapon == WP_PAIN_SAW && g_bot_painsaw.integer <= 0) ||
		(self->client->ps.weapon == WP_LAS_GUN && g_bot_lasgun.integer <= 0) ||
		(self->client->ps.weapon == WP_MASS_DRIVER && g_bot_mdriver.integer <= 0) ||
		(self->client->ps.weapon == WP_PULSE_RIFLE && g_bot_prifle.integer <= 0) ||
		(self->client->ps.weapon == WP_FLAMER && g_bot_flamer.integer <= 0) ||
		(self->client->ps.weapon == WP_LUCIFER_CANNON && g_bot_lcannon.integer <= 0) ||
		(self->client->ps.weapon == WP_CHAINGUN && g_bot_chaingun.integer <= 0) ) {
			G_ForceWeaponChange( self, WP_BLASTER );
	}
}
/**
 * Think the best target to attack
 * @param self
 * //TODO: replace hardcoded values
 */
int BotTargetRankHuman( gentity_t *self, gentity_t *target, float rank ) {
	int sd;
	int distance;
	
	//If we can't see it and we don't have a helmet, forget it. 
	//TODO: record last known location, and if there is no other enemies around, go and explore it
	//if(!(BG_InventoryContainsUpgrade( UP_HELMET, self->client->ps.stats) || 
	if(!G_Visible(self, target, CONTENTS_SOLID)) {
		return 0;
	}
	distance = botGetDistanceBetweenPlayer(self, target);
	sd = G_TimeTilSuddenDeath() <= 0 ? 2 : 1;
	if(target->s.eType == ET_BUILDABLE) {
		if(self->health > 80) rank += 30;
		switch(target->s.modelindex) {
			case BA_A_SPAWN: 	rank += (50 * sd); break;
			case BA_A_OVERMIND: rank += (30 * sd); break;
			case BA_A_BOOSTER: 	rank += (25 * sd); break;
			case BA_A_ACIDTUBE: rank += (20 * sd); break;
			case BA_A_HIVE: 	rank += (20 * sd); break;
			default: 			rank += (10 * sd); break;
		}
		switch(self->client->ps.weapon) {
			case WP_PAIN_SAW:	rank += 50; break;
			case WP_FLAMER:		rank += 45; break;
			case WP_LUCIFER_CANNON: rank += 40; break;
			case WP_PULSE_RIFLE:rank += 30; break;
			case WP_LAS_GUN: 	rank += 20; break;
			default:			break;
		}
		//If we have a nade, aim the bushes!
		if(BG_InventoryContainsUpgrade(UP_GRENADE,self->client->ps.stats)) {
			rank += 20;
		}
	} else if(target->client) {
		switch(self->client->ps.weapon) {
			case WP_BLASTER:	
				switch(target->client->pers.classSelection) {
					case PCL_ALIEN_BUILDER0:
					case PCL_ALIEN_BUILDER0_UPG:
					case PCL_ALIEN_LEVEL0:
					case PCL_ALIEN_LEVEL1:
					case PCL_ALIEN_LEVEL1_UPG:
						rank += 30; break;
					case PCL_ALIEN_LEVEL2:
					case PCL_ALIEN_LEVEL2_UPG:
					case PCL_ALIEN_LEVEL3:
					case PCL_ALIEN_LEVEL3_UPG:
					case PCL_ALIEN_LEVEL4:
						rank -= 30; break; 
					default: break;
				}
			break;
			case WP_MACHINEGUN: 
				switch(target->client->pers.classSelection) {
					case PCL_ALIEN_BUILDER0:
					case PCL_ALIEN_BUILDER0_UPG:
					case PCL_ALIEN_LEVEL0:
					case PCL_ALIEN_LEVEL1:
					case PCL_ALIEN_LEVEL1_UPG:
						rank += 30; break;
					case PCL_ALIEN_LEVEL2:
					case PCL_ALIEN_LEVEL2_UPG:
						rank -= 10; break;
					case PCL_ALIEN_LEVEL3:
					case PCL_ALIEN_LEVEL3_UPG:
					case PCL_ALIEN_LEVEL4:
						rank += 10; break;
					default: break;
				}
			break;
			case WP_PAIN_SAW:
				if(distance > 200) rank -= 40;
				switch(target->client->pers.classSelection) {
					case PCL_ALIEN_BUILDER0:
					case PCL_ALIEN_BUILDER0_UPG:
						rank += 10; break;
					case PCL_ALIEN_LEVEL0:
					case PCL_ALIEN_LEVEL1:
					case PCL_ALIEN_LEVEL1_UPG:
						break;
					case PCL_ALIEN_LEVEL2:
					case PCL_ALIEN_LEVEL2_UPG:
						rank -= 30; break;
					case PCL_ALIEN_LEVEL3:
						break;
					case PCL_ALIEN_LEVEL3_UPG:
						rank -= 30; break;
					case PCL_ALIEN_LEVEL4:
					default: 
						break;
				}
			break;
			case WP_SHOTGUN:	
				if(distance > 300) rank -= 40;
				switch(target->client->pers.classSelection) {
					case PCL_ALIEN_BUILDER0:
					case PCL_ALIEN_BUILDER0_UPG:
					case PCL_ALIEN_LEVEL0:
					case PCL_ALIEN_LEVEL1:
					case PCL_ALIEN_LEVEL1_UPG:
						rank += 30; break;
					case PCL_ALIEN_LEVEL2:
					case PCL_ALIEN_LEVEL2_UPG:
						rank += 10; break;
					case PCL_ALIEN_LEVEL3:
					case PCL_ALIEN_LEVEL3_UPG:
					case PCL_ALIEN_LEVEL4:
					default: 
						break;
				}
			break;
			case WP_LAS_GUN: 	
				switch(target->client->pers.classSelection) {
					case PCL_ALIEN_BUILDER0:
					case PCL_ALIEN_BUILDER0_UPG:
					case PCL_ALIEN_LEVEL0:
					case PCL_ALIEN_LEVEL1:
					case PCL_ALIEN_LEVEL1_UPG:
						rank += 30; break;
					case PCL_ALIEN_LEVEL2:
					case PCL_ALIEN_LEVEL2_UPG:
						break;
					case PCL_ALIEN_LEVEL3:
					case PCL_ALIEN_LEVEL3_UPG:
					case PCL_ALIEN_LEVEL4:
						rank += 10; break;
					default: break;
				}
			break;
			case WP_MASS_DRIVER: 
				switch(target->client->pers.classSelection) {
					case PCL_ALIEN_BUILDER0:
					case PCL_ALIEN_BUILDER0_UPG:
					case PCL_ALIEN_LEVEL0:
					case PCL_ALIEN_LEVEL1:
					case PCL_ALIEN_LEVEL1_UPG:
						rank += 30; break;
					case PCL_ALIEN_LEVEL2:
					case PCL_ALIEN_LEVEL2_UPG:
						rank += 20; break;
					case PCL_ALIEN_LEVEL3:
					case PCL_ALIEN_LEVEL3_UPG:
					case PCL_ALIEN_LEVEL4:
						rank -= 10; break;
					default: break;
				}
			break;
			case WP_CHAINGUN: 	
				switch(target->client->pers.classSelection) {
					case PCL_ALIEN_BUILDER0:
					case PCL_ALIEN_BUILDER0_UPG:
					case PCL_ALIEN_LEVEL0:
					case PCL_ALIEN_LEVEL1:
					case PCL_ALIEN_LEVEL1_UPG:
						break;
					case PCL_ALIEN_LEVEL2:
					case PCL_ALIEN_LEVEL2_UPG:
					case PCL_ALIEN_LEVEL3:
					case PCL_ALIEN_LEVEL3_UPG:
					case PCL_ALIEN_LEVEL4:
						rank += 30; break;
					default: break;
				}
			break;
			case WP_FLAMER:		
				if(distance > 200) rank -= 40;
				switch(target->client->pers.classSelection) {
					case PCL_ALIEN_BUILDER0:
					case PCL_ALIEN_BUILDER0_UPG:
					case PCL_ALIEN_LEVEL0:
					case PCL_ALIEN_LEVEL1:
					case PCL_ALIEN_LEVEL1_UPG:
						rank += 30; break;
					case PCL_ALIEN_LEVEL2:
					case PCL_ALIEN_LEVEL2_UPG:
						rank += 10; break;
					case PCL_ALIEN_LEVEL3:
					case PCL_ALIEN_LEVEL3_UPG:
					case PCL_ALIEN_LEVEL4:
					default: 
						break;
				}
			break;
			case WP_PULSE_RIFLE:
				switch(target->client->pers.classSelection) {
					case PCL_ALIEN_BUILDER0:
					case PCL_ALIEN_BUILDER0_UPG:
					case PCL_ALIEN_LEVEL0:
					case PCL_ALIEN_LEVEL1:
					case PCL_ALIEN_LEVEL1_UPG:
						break;
					case PCL_ALIEN_LEVEL2:
					case PCL_ALIEN_LEVEL2_UPG:
						rank -= 10; break;
					case PCL_ALIEN_LEVEL3:
					case PCL_ALIEN_LEVEL3_UPG:
					case PCL_ALIEN_LEVEL4:
						rank += 30; break;
					default: break;
				}
			break;
			case WP_LUCIFER_CANNON: 
				switch(target->client->pers.classSelection) {
					case PCL_ALIEN_BUILDER0:
					case PCL_ALIEN_BUILDER0_UPG:
					case PCL_ALIEN_LEVEL0:
					case PCL_ALIEN_LEVEL1:
					case PCL_ALIEN_LEVEL1_UPG:
						rank += 30; break;
					case PCL_ALIEN_LEVEL2:
					case PCL_ALIEN_LEVEL2_UPG:
						rank -= 10; break;
					case PCL_ALIEN_LEVEL3:
					case PCL_ALIEN_LEVEL3_UPG:
					case PCL_ALIEN_LEVEL4:
						rank += 30; break;
					default: break;
				}
			break;
			default: break;
		}
	}
	return (int)rank;
}

/**
 * Repair close buildings
 * @param client
 */
void BotRepair( gentity_t *self ) {
	if(BG_InventoryContainsWeapon( WP_HBUILD, self->client->ps.stats ) && 
			self->client->ps.persistant[ PERS_NEWWEAPON ] != WP_HBUILD) {
		G_ForceWeaponChange( self, WP_HBUILD );
	}
}
/**
 * Use CKIT to build
 * @param client
 */
void BotBuildHuman( gentity_t *self ) {
}
/**
 * Locate medipad and heal
 * @param client
 */
void BotHealHuman( gentity_t *self ) {
	//TODO: if there is no a MEDIPAD nearby, search for it (pathfinding)
	//For now, just forget about it
}

/**
 * Perform group logic for Humans
 */
void G_BotGroupThinkHuman( void ) {

} 
