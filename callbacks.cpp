#include "includes.h"

// execution callbacks..
void callbacks::SkinUpdate( ) {
	g_skins.m_update = true;
}

void callbacks::ForceFullUpdate( ) {
	//static DWORD tick{};
	//
	//if( tick != g_winapi.GetTickCount( ) ) {
	//	g_csgo.cl_fullupdate->m_callback( );
	//	tick = g_winapi.GetTickCount( );
	//

	g_csgo.m_cl->m_delta_tick = -1;
}

void callbacks::ToggleThirdPerson( ) {
	g_visuals.m_thirdperson = !g_visuals.m_thirdperson;
}

void callbacks::ToggleFakeLatency( ) {
	g_aimbot.m_fake_latency = !g_aimbot.m_fake_latency;
}

void callbacks::ToggleKillfeed( ) {
    KillFeed_t* feed = ( KillFeed_t* )g_csgo.m_hud->FindElement( HASH( "SFHudDeathNoticeAndBotStatus" ) );
    if( feed )
        g_csgo.ClearNotices( feed );
}

void callbacks::SaveHotkeys( ) {
	g_config.SaveHotkeys( );
}

void callbacks::ConfigLoad1( ) {
	g_config.load( &g_menu.main, XOR( "1.sup" ) );
	g_menu.main.config.config.select( 1 - 1 );

	g_notify.add( tfm::format( XOR( "loaded config 1\n" ) ) );
}

void callbacks::ConfigLoad2( ) {
	g_config.load( &g_menu.main, XOR( "2.sup" ) );
	g_menu.main.config.config.select( 2 - 1 );
	g_notify.add( tfm::format( XOR( "loaded config 2\n" ) ) );
}

void callbacks::ConfigLoad3( ) {
	g_config.load( &g_menu.main, XOR( "3.sup" ) );
	g_menu.main.config.config.select( 3 - 1 );
	g_notify.add( tfm::format( XOR( "loaded config 3\n" ) ) );
}

void callbacks::ConfigLoad4( ) {
	g_config.load( &g_menu.main, XOR( "4.sup" ) );
	g_menu.main.config.config.select( 4 - 1 );
	g_notify.add( tfm::format( XOR( "loaded config 4\n" ) ) );
}

void callbacks::ConfigLoad5( ) {
	g_config.load( &g_menu.main, XOR( "5.sup" ) );
	g_menu.main.config.config.select( 5 - 1 );
	g_notify.add( tfm::format( XOR( "loaded config 5\n" ) ) );
}

void callbacks::ConfigLoad6( ) {
	g_config.load( &g_menu.main, XOR( "6.sup" ) );
	g_menu.main.config.config.select( 6 - 1 );
	g_notify.add( tfm::format( XOR( "loaded config 6\n" ) ) );
}

void callbacks::ConfigLoad( ) {
	std::string config = g_menu.main.config.config.GetActiveItem( );
	std::string file   = tfm::format( XOR( "%s.sup" ), config.data( ) );

	g_config.load( &g_menu.main, file );
	g_notify.add( tfm::format( XOR( "loaded config %s\n" ), config.data( ) ) );
}

void callbacks::ConfigSave( ) {
	std::string config = g_menu.main.config.config.GetActiveItem( );
	std::string file   = tfm::format( XOR( "%s.sup" ), config.data( ) );

	g_config.save( &g_menu.main, file );
	g_notify.add( tfm::format( XOR( "saved config %s\n" ), config.data( ) ) );
}

bool callbacks::IsBaimHealth( ) {
	return g_menu.main.aimbot.baim2.get( 1 );
}

bool callbacks::IsFovOn( ) {
	return g_menu.main.aimbot.fov.get( );
}

bool callbacks::IsHitchanceOn( ) {
	return g_menu.main.aimbot.hitchance.get( );
}

bool callbacks::IsPenetrationOn( ) {
	return g_menu.main.aimbot.penetrate.get( );
}

bool callbacks::IsMultipointOn( ) {
	return !g_menu.main.aimbot.multipoint.GetActiveIndices( ).empty( );
}

bool callbacks::IsMultipointBodyOn( ) {
	return g_menu.main.aimbot.multipoint.get( 2 );
}

bool callbacks::IsAntiAimModeStand( ) {
	return g_menu.main.antiaim.mode.get( ) == 0;
}

bool callbacks::HasStandYaw( ) {
	return g_menu.main.antiaim.yaw_stand.get( ) > 0;
}

bool callbacks::IsStandYawJitter( ) {
	return g_menu.main.antiaim.yaw_stand.get( ) == 2;
}

bool callbacks::IsStandYawRotate( ) {
	return g_menu.main.antiaim.yaw_stand.get( ) == 3;
}

bool callbacks::IsStandYawRnadom( ) {
	return g_menu.main.antiaim.yaw_stand.get( ) == 4;
}

bool callbacks::IsStandDirAuto( ) {
	return g_menu.main.antiaim.dir_stand.get( ) == 0;
}

bool callbacks::IsStandDirCustom( ) {
	return g_menu.main.antiaim.dir_stand.get( ) == 4;
}

bool callbacks::IsAntiAimModeWalk( ) {
	return g_menu.main.antiaim.mode.get( ) == 1;
}

bool callbacks::WalkHasYaw( ) {
	return g_menu.main.antiaim.yaw_walk.get( ) > 0;
}

bool callbacks::IsWalkYawJitter( ) {
	return g_menu.main.antiaim.yaw_walk.get( ) == 2;
}

bool callbacks::IsWalkYawRotate( ) {
	return g_menu.main.antiaim.yaw_walk.get( ) == 3;
}

bool callbacks::IsWalkYawRandom( ) {
	return g_menu.main.antiaim.yaw_walk.get( ) == 4;
}

bool callbacks::IsWalkDirAuto( ) {
	return g_menu.main.antiaim.dir_walk.get( ) == 0;
}

bool callbacks::IsWalkDirCustom( ) {
	return g_menu.main.antiaim.dir_walk.get( ) == 4;
}

bool callbacks::IsAntiAimModeAir( ) {
	return g_menu.main.antiaim.mode.get( ) == 2;
}

bool callbacks::AirHasYaw( ) {
	return g_menu.main.antiaim.yaw_air.get( ) > 0;
}

bool callbacks::IsAirYawJitter( ) {
	return g_menu.main.antiaim.yaw_air.get( ) == 2;
}

bool callbacks::IsAirYawRotate( ) {
	return g_menu.main.antiaim.yaw_air.get( ) == 3;
}

bool callbacks::IsAirYawRandom( ) {
	return g_menu.main.antiaim.yaw_air.get( ) == 4;
}

bool callbacks::IsAirDirAuto( ) {
	return g_menu.main.antiaim.dir_air.get( ) == 0;
}

bool callbacks::IsAirDirCustom( ) {
	return g_menu.main.antiaim.dir_air.get( ) == 4;
}

bool callbacks::IsFakeAntiAimRelative( ) {
	return g_menu.main.antiaim.fake_yaw.get( ) == 2;
}

bool callbacks::IsFakeAntiAimJitter( ) {
	return g_menu.main.antiaim.fake_yaw.get( ) == 3;
}

bool callbacks::IsConfigMM( ) {
	return g_menu.main.config.mode.get( ) == 0;
}

bool callbacks::IsConfigNS( ) {
	return g_menu.main.config.mode.get( ) == 1;
}

bool callbacks::IsConfig1( ) {
	return g_menu.main.config.config.get( ) == 0;
}

bool callbacks::IsConfig2( ) {
	return g_menu.main.config.config.get( ) == 1;
}

bool callbacks::IsConfig3( ) {
	return g_menu.main.config.config.get( ) == 2;
}

bool callbacks::IsConfig4( ) {
	return g_menu.main.config.config.get( ) == 3;
}

bool callbacks::IsConfig5( ) {
	return g_menu.main.config.config.get( ) == 4;
}

bool callbacks::IsConfig6( ) {
	return g_menu.main.config.config.get( ) == 5;
}

// weaponcfgs callbacks.
bool callbacks::DEAGLE( ) {
	if( !g_csgo.m_engine->IsInGame( ) || !g_cl.m_processing )
		return false;

	return g_cl.m_weapon_id == Weapons_t::DEAGLE;
}

bool callbacks::ELITE( ) {
	if( !g_csgo.m_engine->IsInGame( ) || !g_cl.m_processing )
		return false;

	return g_cl.m_weapon_id == Weapons_t::ELITE;
}

bool callbacks::FIVESEVEN( ) {
	if( !g_csgo.m_engine->IsInGame( ) || !g_cl.m_processing )
		return false;

	return g_cl.m_weapon_id == Weapons_t::FIVESEVEN;
}

bool callbacks::GLOCK( ) {
	if( !g_csgo.m_engine->IsInGame( ) || !g_cl.m_processing )
		return false;

	return g_cl.m_weapon_id == Weapons_t::GLOCK;
}

bool callbacks::AK47( ) {
	if( !g_csgo.m_engine->IsInGame( ) || !g_cl.m_processing )
		return false;

	return g_cl.m_weapon_id == Weapons_t::AK47;
}

bool callbacks::AUG( ) {
	if( !g_csgo.m_engine->IsInGame( ) || !g_cl.m_processing )
		return false;

	return g_cl.m_weapon_id == Weapons_t::AUG;
}

bool callbacks::AWP( ) {
	if( !g_csgo.m_engine->IsInGame( ) || !g_cl.m_processing )
		return false;

	return g_cl.m_weapon_id == Weapons_t::AWP;
}

bool callbacks::FAMAS( ) {
	if( !g_csgo.m_engine->IsInGame( ) || !g_cl.m_processing )
		return false;

	return g_cl.m_weapon_id == Weapons_t::FAMAS;
}

bool callbacks::G3SG1( ) {
	if( !g_csgo.m_engine->IsInGame( ) || !g_cl.m_processing )
		return false;

	return g_cl.m_weapon_id == Weapons_t::G3SG1;
}

bool callbacks::GALIL( ) {
	if( !g_csgo.m_engine->IsInGame( ) || !g_cl.m_processing )
		return false;

	return g_cl.m_weapon_id == Weapons_t::GALIL;
}

bool callbacks::M249( ) {
	if( !g_csgo.m_engine->IsInGame( ) || !g_cl.m_processing )
		return false;

	return g_cl.m_weapon_id == Weapons_t::M249;
}

bool callbacks::M4A4( ) {
	if( !g_csgo.m_engine->IsInGame( ) || !g_cl.m_processing )
		return false;

	return g_cl.m_weapon_id == Weapons_t::M4A4;
}

bool callbacks::MAC10( ) {
	if( !g_csgo.m_engine->IsInGame( ) || !g_cl.m_processing )
		return false;

	return g_cl.m_weapon_id == Weapons_t::MAC10;
}

bool callbacks::P90( ) {
	if( !g_csgo.m_engine->IsInGame( ) || !g_cl.m_processing )
		return false;

	return g_cl.m_weapon_id == Weapons_t::P90;
}

bool callbacks::UMP45( ) {
	if( !g_csgo.m_engine->IsInGame( ) || !g_cl.m_processing )
		return false;

	return g_cl.m_weapon_id == Weapons_t::UMP45;
}

bool callbacks::XM1014( ) {
	if( !g_csgo.m_engine->IsInGame( ) || !g_cl.m_processing )
		return false;

	return g_cl.m_weapon_id == Weapons_t::XM1014;
}

bool callbacks::BIZON( ) {
	if( !g_csgo.m_engine->IsInGame( ) || !g_cl.m_processing )
		return false;

	return g_cl.m_weapon_id == Weapons_t::BIZON;
}

bool callbacks::MAG7( ) {
	if( !g_csgo.m_engine->IsInGame( ) || !g_cl.m_processing )
		return false;

	return g_cl.m_weapon_id == Weapons_t::MAG7;
}

bool callbacks::NEGEV( ) {
	if( !g_csgo.m_engine->IsInGame( ) || !g_cl.m_processing )
		return false;

	return g_cl.m_weapon_id == Weapons_t::NEGEV;
}

bool callbacks::SAWEDOFF( ) {
	if( !g_csgo.m_engine->IsInGame( ) || !g_cl.m_processing )
		return false;

	return g_cl.m_weapon_id == Weapons_t::SAWEDOFF;
}

bool callbacks::TEC9( ) {
	if( !g_csgo.m_engine->IsInGame( ) || !g_cl.m_processing )
		return false;

	return g_cl.m_weapon_id == Weapons_t::TEC9;
}

bool callbacks::P2000( ) {
	if( !g_csgo.m_engine->IsInGame( ) || !g_cl.m_processing )
		return false;

	return g_cl.m_weapon_id == Weapons_t::P2000;
}

bool callbacks::MP7( ) {
	if( !g_csgo.m_engine->IsInGame( ) || !g_cl.m_processing )
		return false;

	return g_cl.m_weapon_id == Weapons_t::MP7;
}

bool callbacks::MP9( ) {
	if( !g_csgo.m_engine->IsInGame( ) || !g_cl.m_processing )
		return false;

	return g_cl.m_weapon_id == Weapons_t::MP9;
}

bool callbacks::NOVA( ) {
	if( !g_csgo.m_engine->IsInGame( ) || !g_cl.m_processing )
		return false;

	return g_cl.m_weapon_id == Weapons_t::NOVA;
}

bool callbacks::P250( ) {
	if( !g_csgo.m_engine->IsInGame( ) || !g_cl.m_processing )
		return false;

	return g_cl.m_weapon_id == Weapons_t::P250;
}

bool callbacks::SCAR20( ) {
	if( !g_csgo.m_engine->IsInGame( ) || !g_cl.m_processing )
		return false;

	return g_cl.m_weapon_id == Weapons_t::SCAR20;
}

bool callbacks::SG553( ) {
	if( !g_csgo.m_engine->IsInGame( ) || !g_cl.m_processing )
		return false;

	return g_cl.m_weapon_id == Weapons_t::SG553;
}

bool callbacks::SSG08( ) {
	if( !g_csgo.m_engine->IsInGame( ) || !g_cl.m_processing )
		return false;

	return g_cl.m_weapon_id == Weapons_t::SSG08;
}

bool callbacks::M4A1S( ) {
	if( !g_csgo.m_engine->IsInGame( ) || !g_cl.m_processing )
		return false;

	return g_cl.m_weapon_id == Weapons_t::M4A1S;
}

bool callbacks::USPS( ) {
	if( !g_csgo.m_engine->IsInGame( ) || !g_cl.m_processing )
		return false;

	return g_cl.m_weapon_id == Weapons_t::USPS;
}

bool callbacks::CZ75A( ) {
	if( !g_csgo.m_engine->IsInGame( ) || !g_cl.m_processing )
		return false;

	return g_cl.m_weapon_id == Weapons_t::CZ75A;
}

bool callbacks::REVOLVER( ) {
	if( !g_csgo.m_engine->IsInGame( ) || !g_cl.m_processing )
		return false;

	return g_cl.m_weapon_id == Weapons_t::REVOLVER;
}

bool callbacks::KNIFE_BAYONET( ) {
	if( !g_csgo.m_engine->IsInGame( ) || !g_cl.m_processing )
		return false;

	return g_cl.m_weapon_id == Weapons_t::KNIFE_BAYONET;
}

bool callbacks::KNIFE_FLIP( ) {
	if( !g_csgo.m_engine->IsInGame( ) || !g_cl.m_processing )
		return false;

	return g_cl.m_weapon_id == Weapons_t::KNIFE_FLIP;
}

bool callbacks::KNIFE_GUT( ) {
	if( !g_csgo.m_engine->IsInGame( ) || !g_cl.m_processing )
		return false;

	return g_cl.m_weapon_id == Weapons_t::KNIFE_GUT;
}

bool callbacks::KNIFE_KARAMBIT( ) {
	if( !g_csgo.m_engine->IsInGame( ) || !g_cl.m_processing )
		return false;

	return g_cl.m_weapon_id == Weapons_t::KNIFE_KARAMBIT;
}

bool callbacks::KNIFE_M9_BAYONET( ) {
	if( !g_csgo.m_engine->IsInGame( ) || !g_cl.m_processing )
		return false;

	return g_cl.m_weapon_id == Weapons_t::KNIFE_M9_BAYONET;
}

bool callbacks::KNIFE_HUNTSMAN( ) {
	if( !g_csgo.m_engine->IsInGame( ) || !g_cl.m_processing )
		return false;

	return g_cl.m_weapon_id == Weapons_t::KNIFE_HUNTSMAN;
}

bool callbacks::KNIFE_FALCHION( ) {
	if( !g_csgo.m_engine->IsInGame( ) || !g_cl.m_processing )
		return false;

	return g_cl.m_weapon_id == Weapons_t::KNIFE_FALCHION;
}

bool callbacks::KNIFE_BOWIE( ) {
	if( !g_csgo.m_engine->IsInGame( ) || !g_cl.m_processing )
		return false;

	return g_cl.m_weapon_id == Weapons_t::KNIFE_BOWIE;
}

bool callbacks::KNIFE_BUTTERFLY( ) {
	if( !g_csgo.m_engine->IsInGame( ) || !g_cl.m_processing )
		return false;

	return g_cl.m_weapon_id == Weapons_t::KNIFE_BUTTERFLY;
}

bool callbacks::KNIFE_SHADOW_DAGGERS( ) {
	if( !g_csgo.m_engine->IsInGame( ) || !g_cl.m_processing )
		return false;

	return g_cl.m_weapon_id == Weapons_t::KNIFE_SHADOW_DAGGERS;
}

bool callbacks::AUTO_STOP( ) {
	return !g_menu.main.movement.autostop_always_on.get();
}