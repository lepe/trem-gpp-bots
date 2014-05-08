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
	self->bot->funcs.team.target			= BotTargetHuman;
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
	self->bot->set.helmet[S1] 	= 100;
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
    G_BotDebug(BOT_VERB_DETAIL, BOT_DEBUG_HUMAN + BOT_DEBUG_THINK, "Bot is about to spawn\n");
	self->client->pers.classSelection = PCL_HUMAN;
	self->client->ps.stats[ STAT_CLASS ] = PCL_HUMAN;
	self->client->pers.humanItemSelection = WP_MACHINEGUN;
	//self->client->pers.humanItemSelection = WP_HBUILD; //LEPE (for future reference when builders become a reality)
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
	//Buy stuff from arm if within range
	if(G_BuildableRange( self->client->ps.origin, 100, BA_H_ARMOURY ) && 
			level.time - self->bot->timer.improve > 5000) 
	{
		self->bot->think.state[ THINK_LEVEL_1 ] = IMPROVE;
	}

	//Suggest Heal if low HP
	if(self->health <= 20) {
		self->bot->think.state[ THINK_LEVEL_3 ] = HEAL;
	} if(self->health <= 50) {
		self->bot->think.state[ THINK_LEVEL_2 ] = HEAL;
	} else if(self->health < 100) {
		self->bot->think.state[ THINK_LEVEL_1 ] = HEAL;
	}
	
	if(!self->bot->Enemy && self->bot->state != HEAL) { 
		if(botFindClosestFriend( self )) {
			//self->bot->think.state[ THINK_LEVEL_1 ] = FOLLOW;
		}
	}
	///////////////////////// LEVEL 1 /////////////////////////
	if(BotKeepThinking( self , THINK_LEVEL_1)) {
		//TODO: if the target is not in our view range, set THINK_LEVEL_1 to UNDEFINED.
	}
	
	///////////////////////// LEVEL 2 /////////////////////////
	if(BotKeepThinking( self , THINK_LEVEL_2)) {

	}
}

/**
 * Human navigation 
 * @param self
 */
void BotNavigateHuman( gentity_t *self ){
	/*
	if(self->client->ps.stats[ STAT_STAMINA ] < 100)
	{
		BotStop( self );
		BotCrouch( self );
		self->bot->timer.foundPath += 100;
	}
	 */
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
	qboolean rand = G_Rand() < 50;
	/* If we have low stamina, we can't keep jumping, so we reset it
	 * to help the bot to remove block */
	if(low_stamina) self->client->ps.stats[ STAT_STAMINA ] = 1000;

	G_BotDebug(BOT_VERB_DETAIL, BOT_DEBUG_HUMAN + BOT_DEBUG_NAVSTATE, "[ %d ] Trying to unblock. Rand: %d\n", try, rand );
	if(try <= 0) {
		BotMoveFwd( self );
		VectorCopy(self->r.currentOrigin, self->bot->path.blocked_origin);
		if(!low_stamina) BotJump( self );
	} else if(try < BOT_TIMER_NAV_SECOND) {
		if(rand) BotControl( self, BOT_LOOK_RIGHT );
	} else if(try == BOT_TIMER_NAV_SECOND) {
		if(!low_stamina) BotJump( self );
	} else if(try > BOT_TIMER_NAV_SECOND * 2) {
		if(rand) BotControl( self, BOT_LOOK_LEFT );
	}
	if(try >= BOT_TIMER_NAV_SECOND * 4) {
		self->bot->path.blocked_try = 0; 
		G_BotDebug(BOT_VERB_DETAIL, BOT_DEBUG_HUMAN + BOT_DEBUG_NAVSTATE, "Reset blocked_try to 0\n" );
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
	if(self->client->ps.stats[ STAT_TEAM ] != TEAM_HUMANS){return;}
    
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
	if(g_humanStage.integer == 1 && (G_Rand() < prob))
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
    		G_BotDebug(BOT_VERB_NORMAL, BOT_DEBUG_HUMAN + BOT_DEBUG_THINK, "Bought LUCIFER_CANNON\n");
		}
	}
    prob = self->bot->set.prifle[g_humanStage.integer];
	if((G_Rand() < prob) && g_humanStage.integer == 1 && boughtweap == qfalse && g_bot_prifle.integer > 0)
	{
		weapon = WP_PULSE_RIFLE;
		if( !BG_InventoryContainsWeapon( weapon, self->client->ps.stats ) &&
			BG_Weapon( weapon )->price <= (short)self->client->ps.persistant[ PERS_CREDIT ] &&
			!(BG_Weapon( weapon )->slots & BG_SlotsForInventory( self->client->ps.stats )))
		{
			boughtweap = qtrue;
			buybatt = qtrue;
			energyweap = qtrue;
    		G_BotDebug(BOT_VERB_NORMAL, BOT_DEBUG_HUMAN + BOT_DEBUG_THINK, "Bought PULSE\n");
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
            G_BotDebug(BOT_VERB_NORMAL, BOT_DEBUG_HUMAN + BOT_DEBUG_THINK,"Bought CHAINGUN\n");
		}
	}
    prob = self->bot->set.flamer[g_humanStage.integer];
	if((G_Rand() < prob) && g_humanStage.integer == 1 && boughtweap == qfalse && g_bot_flamer.integer > 0) 
	{
		weapon = WP_FLAMER;
		if( !BG_InventoryContainsWeapon( weapon, self->client->ps.stats ) &&
			BG_Weapon( weapon )->price <= (short)self->client->ps.persistant[ PERS_CREDIT ] &&
			!(BG_Weapon( weapon )->slots & BG_SlotsForInventory( self->client->ps.stats )))
		{
			boughtweap = qtrue;
            G_BotDebug(BOT_VERB_NORMAL, BOT_DEBUG_HUMAN + BOT_DEBUG_THINK,"Bought FLAMER\n");
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
            G_BotDebug(BOT_VERB_NORMAL, BOT_DEBUG_HUMAN + BOT_DEBUG_THINK,"Bought MASS_DRIVER\n");
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
            G_BotDebug(BOT_VERB_NORMAL, BOT_DEBUG_HUMAN + BOT_DEBUG_THINK,"Bought LAS_GUN\n");
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
            G_BotDebug(BOT_VERB_NORMAL, BOT_DEBUG_HUMAN + BOT_DEBUG_THINK,"Bought SHOTGUN\n");
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
            G_BotDebug(BOT_VERB_NORMAL, BOT_DEBUG_HUMAN + BOT_DEBUG_THINK,"Bought PAIN_SAW\n");
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
            G_BotDebug(BOT_VERB_NORMAL, BOT_DEBUG_HUMAN + BOT_DEBUG_THINK,"MACHINEGUN for FREE!\n");
		}
	}
	//Buy Nades
	upgrade = UP_GRENADE;
    prob = self->bot->set.nade[g_humanStage.integer];
	if((G_Rand() < prob) &! BG_InventoryContainsUpgrade( upgrade, self->client->ps.stats ) && g_humanStage.integer > 0 && 
			BG_Upgrade( upgrade )->price <= (short)self->client->ps.persistant[ PERS_CREDIT ]) {
		BG_AddUpgradeToInventory( upgrade, self->client->ps.stats );
		G_AddCreditToClient( self->client, -(short)BG_Upgrade( upgrade )->price, qfalse );
		G_BotDebug(BOT_VERB_NORMAL, BOT_DEBUG_HUMAN + BOT_DEBUG_THINK,"NADE Bought\n");
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
		G_BotDebug(BOT_VERB_NORMAL, BOT_DEBUG_HUMAN + BOT_DEBUG_THINK,"BLASTER?\n");
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
		G_BotDebug(BOT_VERB_NORMAL, BOT_DEBUG_HUMAN + BOT_DEBUG_THINK,"Bought BATTPACK\n");
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
	self->bot->timer.improve = level.time;
	//We reset current state
	BotResetState( self, IMPROVE );
	return;
}

/**
 * Attack to target if its in range (see: g_bot_alien.c botAttackIfTargetInRange)
 * @param self [gentity_t] a BOT
 */
void BotAttackHuman( gentity_t *self )
{
	int tooCloseDistance = 200; 
	int tempEntityIndex = -1;
	int distance = botGetDistanceBetweenPlayer(self, self->bot->Enemy);
	//TODO: move this code to target prioritization
	if(G_Rand() < 10 && distance > tooCloseDistance) { //LEPE: change target 10% of times. 
		// try to find closest enemy
		tempEntityIndex = botFindClosestEnemy(self);
		if(tempEntityIndex >= 0) {
			self->bot->Enemy = &g_entities[tempEntityIndex];
			distance = botGetDistanceBetweenPlayer(self, self->bot->Enemy);
		}
	}
	//Use nades
	if(distance < tooCloseDistance && (self->bot->Enemy->s.eType == ET_BUILDABLE || self->bot->Enemy->s.eType == PCL_ALIEN_LEVEL4)) {	//LEPE: Nades on buildings or tyrants
	    if(BG_InventoryContainsUpgrade(UP_GRENADE,self->client->ps.stats)) {
            G_BotDebug(BOT_VERB_DETAIL, BOT_DEBUG_UTIL + BOT_DEBUG_HUMAN + BOT_DEBUG_THINK, "NADE ACTIVATED!\n");
            BG_ActivateUpgrade(UP_GRENADE,self->client->ps.stats);
	    }
	}
	
	if(distance < g_human_range.integer) 
	{
	  //ROTAX
		int rand = 0;
		rand = G_Rand();

		//If its a player or bot
		if(self->bot->Enemy->s.eType == ET_PLAYER) {
			if(distance < 300 && 
				self->client->ps.weapon != WP_PAIN_SAW && 
				self->client->ps.weapon != WP_FLAMER)
			{
				BotMoveBack( self );
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
				BotMoveFwd( self );
			}
			else
			{
				if(distance < 200) {
					BotStand( self );
					BotAddMove( self, BOT_MOVE_BACK, 500);
				} else {
					BotStop( self );
					BotCrouch( self );
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
 * this function may change the bot->Enemy
 * @param self
 */
void BotTargetHuman( gentity_t *self ) {

}

/**
 * Repair close buildings
 * @param client
 */
void BotRepair( gentity_t *self ) {
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
	//Use medkit if low hp
	if(BG_InventoryContainsUpgrade( UP_MEDKIT, self->client->ps.stats ))
	{
		if(self->health <= 40) { //TODO: remove hardcoded value
			BG_ActivateUpgrade( UP_MEDKIT, self->client->ps.stats );
			BotResetState( self, HEAL );
		}
	} else {
		if(!self->bot->Struct) {
			self->bot->Struct = botFindClosestBuildable( self, 200, BA_H_MEDISTAT );
		}
		//TODO: if there is no a MEDIPAD nearby, search for it (pathfinding)
		//For now, just forget about it
		if(!self->bot->Struct) {
			BotResetState( self, HEAL );
		}
	}
}

/**
 * Perform group logic for Humans
 */
void G_BotGroupThinkHuman( void ) {

} 
