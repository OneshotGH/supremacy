#include "includes.h"

Skins g_skins{};;

void Skins::load( ) {
	// update model indexes on mapload.
	m_knife_data[ knives_t::BAYONET ].setup( KNIFE_BAYONET, 
											 XOR( "models/weapons/v_knife_bayonet.mdl" ), 
											 XOR( "models/weapons/w_knife_bayonet.mdl" ),
											 XOR( "bayonet" ) );

	m_knife_data[ knives_t::BOWIE ].setup( KNIFE_BOWIE, 
										   XOR( "models/weapons/v_knife_survival_bowie.mdl" ), 
										   XOR( "models/weapons/w_knife_survival_bowie.mdl" ),
										   XOR( "knife_survival_bowie" ) );


	m_knife_data[ knives_t::BUTTERFLY ].setup( KNIFE_BUTTERFLY, 
											   XOR( "models/weapons/v_knife_butterfly.mdl" ),
											   XOR( "models/weapons/w_knife_butterfly.mdl" ),
											   XOR( "knife_butterfly" ) );

	m_knife_data[ knives_t::FALCHION ].setup( KNIFE_FALCHION, 
											  XOR( "models/weapons/v_knife_falchion_advanced.mdl" ), 
											  XOR( "models/weapons/w_knife_falchion_advanced.mdl" ),
											  XOR( "knife_falchion" ) );

	m_knife_data[ knives_t::FLIP ].setup( KNIFE_FLIP, 
										  XOR( "models/weapons/v_knife_flip.mdl" ), 
										  XOR( "models/weapons/w_knife_flip.mdl" ),
										  XOR( "knife_flip" ) );

	m_knife_data[ knives_t::GUT ].setup( KNIFE_GUT, 
										 XOR( "models/weapons/v_knife_gut.mdl" ), 
										 XOR( "models/weapons/w_knife_gut.mdl" ),
										 XOR( "knife_gut" ) );

	m_knife_data[ knives_t::HUNTSMAN ].setup( KNIFE_HUNTSMAN, 
											  XOR( "models/weapons/v_knife_tactical.mdl" ), 
											  XOR( "models/weapons/w_knife_tactical.mdl" ),
											  XOR( "knife_tactical" ) );

	m_knife_data[ knives_t::KARAMBIT ].setup( KNIFE_KARAMBIT, 
											  XOR( "models/weapons/v_knife_karam.mdl" ), 
											  XOR( "models/weapons/w_knife_karam.mdl" ),
											  XOR( "knife_karambit" ) );

	m_knife_data[ knives_t::M9 ].setup( KNIFE_M9_BAYONET, 
										XOR( "models/weapons/v_knife_m9_bay.mdl" ), 
										XOR( "models/weapons/w_knife_m9_bay.mdl" ),
										XOR( "knife_m9_bayonet" ) );

	m_knife_data[ knives_t::DAGGER ].setup( KNIFE_SHADOW_DAGGERS, 
											XOR( "models/weapons/v_knife_push.mdl" ), 
											XOR( "models/weapons/w_knife_push.mdl" ),
											XOR( "knife_push" ) );

	// update glove model indexes on mapload.
	m_glove_data[ gloves_t::BLOODHOUND ].setup( 5027,
												XOR( "models/weapons/v_models/arms/glove_bloodhound/v_glove_bloodhound.mdl" ),
												XOR( "models/weapons/w_models/arms/glove_bloodhound/w_glove_bloodhound.mdl" ) );

	m_glove_data[ gloves_t::SPORTY ].setup( 5030,
											XOR( "models/weapons/v_models/arms/glove_sporty/v_glove_sporty.mdl" ),
											XOR( "models/weapons/w_models/arms/glove_sporty/w_glove_sporty.mdl" ) );

	m_glove_data[ gloves_t::DRIVER ].setup( 5031,
											XOR( "models/weapons/v_models/arms/glove_slick/v_glove_slick.mdl" ),
											XOR( "models/weapons/w_models/arms/glove_slick/w_glove_slick.mdl" ) );

	m_glove_data[ gloves_t::HANDWRAP ].setup( 5032,
											  XOR( "models/weapons/v_models/arms/glove_handwrap_leathery/v_glove_handwrap_leathery.mdl" ),
											  XOR( "models/weapons/w_models/arms/glove_handwrap_leathery/w_glove_handwrap_leathery.mdl" ) );

	m_glove_data[ gloves_t::MOTO ].setup( 5033,
										  XOR( "models/weapons/v_models/arms/glove_motorcycle/v_glove_motorcycle.mdl" ),
										  XOR( "models/weapons/w_models/arms/glove_motorcycle/w_glove_motorcycle.mdl" ) );

	m_glove_data[ gloves_t::SPECIALIST ].setup( 5034,
												XOR( "models/weapons/v_models/arms/glove_specialist/v_glove_specialist.mdl" ),
												XOR( "models/weapons/w_models/arms/glove_specialist/w_glove_specialist.mdl" ) );

	m_update_time = 0.f;
}

void Skins::think( ) {
	std::vector< Weapon* > weapons{};

	if( !g_menu.main.skins.enable.get( ) )
		return;

	if( !g_csgo.m_engine->IsInGame( ) )
		return;

	if( !g_cl.m_local || !g_cl.m_local->alive( ) )
		return;

	player_info_t info;
	if( !g_csgo.m_engine->GetPlayerInfo( g_cl.m_local->index( ), &info ) )
		return;

	// store knife index.
	KnifeData* knife = &m_knife_data[ g_menu.main.skins.knife.get( ) ];

	for( int i{ 1 }; i <= g_csgo.m_entlist->GetHighestEntityIndex( ); ++i ) {
		Entity* ent = g_csgo.m_entlist->GetClientEntity( i );
		if( !ent )
			continue;

		// run knifechanger.
		if( g_menu.main.skins.knife.get( ) > 0 && ent->is( HASH( "CPredictedViewModel" ) ) ) {
			// get weapon entity from predicted viewmodel.
			Weapon* weapon = ent->as< Weapon* >( )->GetWeapon( );

			// no need to be here anymore.
			if( !weapon || !weapon->IsKnife( ) )
				continue;

			// this weapon does not belong to us, we are done here.
			// should barely happen unless you pick up someones knife.
			// possible on servers with 'mp_drop_knife_enable 1'.
			if( info.m_xuid_low != weapon->m_OriginalOwnerXuidLow( ) || info.m_xuid_high != weapon->m_OriginalOwnerXuidHigh( ) )
				continue;

			// get and validate world model handle from the weapon
			Weapon* weapon_world_model = weapon->GetWeaponWorldModel( );
			if( !weapon_world_model )
				continue;

			// set model index of the predicted viewmodel.
			ent->m_nModelIndex( ) = knife->m_model_index;

			// set the world model index.
			// do this to have knifechanger in third person. verry p.
			weapon_world_model->m_nModelIndex( ) = knife->m_world_model_index;

			// correct m_nSequence and m_flCycle.
			UpdateAnimations( ent );
		}

		else if( ent->IsBaseCombatWeapon( ) ) {
			// cast to weapon class.
			Weapon* weapon = ent->as< Weapon* >( );

			// this is not our gun.
			if( info.m_xuid_low != weapon->m_OriginalOwnerXuidLow( ) || info.m_xuid_high != weapon->m_OriginalOwnerXuidHigh( ) )
				continue;

			// we found a weapon that we own.
			weapons.push_back( weapon );

			if( weapon->IsKnife( ) ) {
				// if this weapon is a knife, set some additional stuff.
				if( g_menu.main.skins.knife.get( ) > 0 ) {
					// set the item id, this is for the hud.
					weapon->m_iItemDefinitionIndex( ) = knife->m_id;

					// not needed. but everyone does this, try without.
					weapon->m_nModelIndex( ) = knife->m_model_index;

					// not needed. but everyone does this, try without.
					weapon->m_iViewModelIndex( ) = knife->m_model_index;

					// not needed. but everyone does this, try without.
					weapon->m_iWorldModelIndex( ) = knife->m_world_model_index;

					// set the little star thing.
					weapon->m_iEntityQuality( ) = 3;
				}

				else if( g_menu.main.skins.knife.get( ) == 0 ) {
					// fix definition.
					if( g_cl.m_local->m_iTeamNum( ) == TEAM_TERRORISTS )
						weapon->m_iItemDefinitionIndex( ) = KNIFE_T;

					else if( g_cl.m_local->m_iTeamNum( ) == TEAM_COUNTERTERRORISTS )
						weapon->m_iItemDefinitionIndex( ) = KNIFE_CT;

					// reset.
					weapon->m_iEntityQuality( )    = 0;
					weapon->m_nFallbackPaintKit( ) = -1;
					weapon->m_nFallbackStatTrak( ) = -1;
				}
			}

			switch( weapon->m_iItemDefinitionIndex( ) ) {
			case DEAGLE:
				weapon->m_nFallbackPaintKit( ) = g_menu.main.skins.id_deagle.get( );
				weapon->m_nFallbackStatTrak( ) = g_menu.main.skins.stattrak_deagle.get( ) ? 1337 : -1;
				weapon->m_nFallbackSeed( )     = g_menu.main.skins.seed_deagle.get( );
				weapon->m_flFallbackWear( )    = ( ( 100.f - g_menu.main.skins.quality_deagle.get( ) ) / 100.f ) + FLT_EPSILON;
				break;
			case ELITE:
				weapon->m_nFallbackPaintKit( ) = g_menu.main.skins.id_elite.get( );
				weapon->m_nFallbackStatTrak( ) = g_menu.main.skins.stattrak_elite.get( ) ? 1337 : -1;
				weapon->m_nFallbackSeed( )     = g_menu.main.skins.seed_elite.get( );
				weapon->m_flFallbackWear( )    = ( ( 100.f - g_menu.main.skins.quality_elite.get( ) ) / 100.f ) + FLT_EPSILON;
				break;
			case FIVESEVEN:
				weapon->m_nFallbackPaintKit( ) = g_menu.main.skins.id_fiveseven.get( );
				weapon->m_nFallbackStatTrak( ) = g_menu.main.skins.stattrak_fiveseven.get( ) ? 1337 : -1;
				weapon->m_nFallbackSeed( )     = g_menu.main.skins.seed_fiveseven.get( );
				weapon->m_flFallbackWear( )    = ( ( 100.f - g_menu.main.skins.quality_fiveseven.get( ) ) / 100.f ) + FLT_EPSILON;
				break;
			case GLOCK:
				weapon->m_nFallbackPaintKit( ) = g_menu.main.skins.id_glock.get( );
				weapon->m_nFallbackStatTrak( ) = g_menu.main.skins.stattrak_glock.get( ) ? 1337 : -1;
				weapon->m_nFallbackSeed( )     = g_menu.main.skins.seed_glock.get( );
				weapon->m_flFallbackWear( )    = ( ( 100.f - g_menu.main.skins.quality_glock.get( ) ) / 100.f ) + FLT_EPSILON;
				break;
			case AK47:
				weapon->m_nFallbackPaintKit( ) = g_menu.main.skins.id_ak47.get( );
				weapon->m_nFallbackStatTrak( ) = g_menu.main.skins.stattrak_ak47.get( ) ? 1337 : -1;
				weapon->m_nFallbackSeed( )     = g_menu.main.skins.seed_ak47.get( );
				weapon->m_flFallbackWear( )    = ( ( 100.f - g_menu.main.skins.quality_ak47.get( ) ) / 100.f ) + FLT_EPSILON;
				break;
			case AUG:
				weapon->m_nFallbackPaintKit( ) = g_menu.main.skins.id_aug.get( );
				weapon->m_nFallbackStatTrak( ) = g_menu.main.skins.stattrak_aug.get( ) ? 1337 : -1;
				weapon->m_nFallbackSeed( )     = g_menu.main.skins.seed_aug.get( );
				weapon->m_flFallbackWear( )    = ( ( 100.f - g_menu.main.skins.quality_aug.get( ) ) / 100.f ) + FLT_EPSILON;
				break;
			case AWP:
				weapon->m_nFallbackPaintKit( ) = g_menu.main.skins.id_awp.get( );
				weapon->m_nFallbackStatTrak( ) = g_menu.main.skins.stattrak_awp.get( ) ? 1337 : -1;
				weapon->m_nFallbackSeed( )     = g_menu.main.skins.seed_awp.get( );
				weapon->m_flFallbackWear( )    = ( ( 100.f - g_menu.main.skins.quality_awp.get( ) ) / 100.f ) + FLT_EPSILON;
				break;
			case FAMAS:
				weapon->m_nFallbackPaintKit( ) = g_menu.main.skins.id_famas.get( );
				weapon->m_nFallbackStatTrak( ) = g_menu.main.skins.stattrak_famas.get( ) ? 1337 : -1;
				weapon->m_nFallbackSeed( )     = g_menu.main.skins.seed_famas.get( );
				weapon->m_flFallbackWear( )    = ( ( 100.f - g_menu.main.skins.quality_famas.get( ) ) / 100.f ) + FLT_EPSILON;
				break;
			case G3SG1:
				weapon->m_nFallbackPaintKit( ) = g_menu.main.skins.id_g3sg1.get( );
				weapon->m_nFallbackStatTrak( ) = g_menu.main.skins.stattrak_g3sg1.get( ) ? 1337 : -1;
				weapon->m_nFallbackSeed( )     = g_menu.main.skins.seed_g3sg1.get( );
				weapon->m_flFallbackWear( )    = ( ( 100.f - g_menu.main.skins.quality_g3sg1.get( ) ) / 100.f ) + FLT_EPSILON;
				break;
			case GALIL:
				weapon->m_nFallbackPaintKit( ) = g_menu.main.skins.id_galil.get( );
				weapon->m_nFallbackStatTrak( ) = g_menu.main.skins.stattrak_galil.get( ) ? 1337 : -1;
				weapon->m_nFallbackSeed( )     = g_menu.main.skins.seed_galil.get( );
				weapon->m_flFallbackWear( )    = ( ( 100.f - g_menu.main.skins.quality_galil.get( ) ) / 100.f ) + FLT_EPSILON;
				break;
			case M249:
				weapon->m_nFallbackPaintKit( ) = g_menu.main.skins.id_m249.get( );
				weapon->m_nFallbackStatTrak( ) = g_menu.main.skins.stattrak_m249.get( ) ? 1337 : -1;
				weapon->m_nFallbackSeed( )     = g_menu.main.skins.seed_m249.get( );
				weapon->m_flFallbackWear( )    = ( ( 100.f - g_menu.main.skins.quality_m249.get( ) ) / 100.f ) + FLT_EPSILON;
				break;
			case M4A4:
				weapon->m_nFallbackPaintKit( ) = g_menu.main.skins.id_m4a4.get( );
				weapon->m_nFallbackStatTrak( ) = g_menu.main.skins.stattrak_m4a4.get( ) ? 1337 : -1;
				weapon->m_nFallbackSeed( )     = g_menu.main.skins.seed_m4a4.get( );
				weapon->m_flFallbackWear( )    = ( ( 100.f - g_menu.main.skins.quality_m4a4.get( ) ) / 100.f ) + FLT_EPSILON;
				break;
			case MAC10:
				weapon->m_nFallbackPaintKit( ) = g_menu.main.skins.id_mac10.get( );
				weapon->m_nFallbackStatTrak( ) = g_menu.main.skins.stattrak_mac10.get( ) ? 1337 : -1;
				weapon->m_nFallbackSeed( )     = g_menu.main.skins.seed_mac10.get( );
				weapon->m_flFallbackWear( )    = ( ( 100.f - g_menu.main.skins.quality_mac10.get( ) ) / 100.f ) + FLT_EPSILON;
				break;
			case P90:
				weapon->m_nFallbackPaintKit( ) = g_menu.main.skins.id_p90.get( );
				weapon->m_nFallbackStatTrak( ) = g_menu.main.skins.stattrak_p90.get( ) ? 1337 : -1;
				weapon->m_nFallbackSeed( )     = g_menu.main.skins.seed_p90.get( );
				weapon->m_flFallbackWear( )    = ( ( 100.f - g_menu.main.skins.quality_p90.get( ) ) / 100.f ) + FLT_EPSILON;
				break;
			case UMP45:
				weapon->m_nFallbackPaintKit( ) = g_menu.main.skins.id_ump45.get( );
				weapon->m_nFallbackStatTrak( ) = g_menu.main.skins.stattrak_ump45.get( ) ? 1337 : -1;
				weapon->m_nFallbackSeed( )     = g_menu.main.skins.seed_ump45.get( );
				weapon->m_flFallbackWear( )    = ( ( 100.f - g_menu.main.skins.quality_ump45.get( ) ) / 100.f ) + FLT_EPSILON;
				break;
			case XM1014:
				weapon->m_nFallbackPaintKit( ) = g_menu.main.skins.id_xm1014.get( );
				weapon->m_nFallbackStatTrak( ) = g_menu.main.skins.stattrak_xm1014.get( ) ? 1337 : -1;
				weapon->m_nFallbackSeed( )     = g_menu.main.skins.seed_xm1014.get( );
				weapon->m_flFallbackWear( )    = ( ( 100.f - g_menu.main.skins.quality_xm1014.get( ) ) / 100.f ) + FLT_EPSILON;
				break;
			case BIZON:
				weapon->m_nFallbackPaintKit( ) = g_menu.main.skins.id_bizon.get( );
				weapon->m_nFallbackStatTrak( ) = g_menu.main.skins.stattrak_bizon.get( ) ? 1337 : -1;
				weapon->m_nFallbackSeed( )     = g_menu.main.skins.seed_bizon.get( );
				weapon->m_flFallbackWear( )    = ( ( 100.f - g_menu.main.skins.quality_bizon.get( ) ) / 100.f ) + FLT_EPSILON;
				break;
			case MAG7:
				weapon->m_nFallbackPaintKit( ) = g_menu.main.skins.id_mag7.get( );
				weapon->m_nFallbackStatTrak( ) = g_menu.main.skins.stattrak_mag7.get( ) ? 1337 : -1;
				weapon->m_nFallbackSeed( )     = g_menu.main.skins.seed_mag7.get( );
				weapon->m_flFallbackWear( )    = ( ( 100.f - g_menu.main.skins.quality_mag7.get( ) ) / 100.f ) + FLT_EPSILON;
				break;
			case NEGEV:
				weapon->m_nFallbackPaintKit( ) = g_menu.main.skins.id_negev.get( );
				weapon->m_nFallbackStatTrak( ) = g_menu.main.skins.stattrak_negev.get( ) ? 1337 : -1;
				weapon->m_nFallbackSeed( )     = g_menu.main.skins.seed_negev.get( );
				weapon->m_flFallbackWear( )    = ( ( 100.f - g_menu.main.skins.quality_negev.get( ) ) / 100.f ) + FLT_EPSILON;
				break;
			case SAWEDOFF:
				weapon->m_nFallbackPaintKit( ) = g_menu.main.skins.id_sawedoff.get( );
				weapon->m_nFallbackStatTrak( ) = g_menu.main.skins.stattrak_sawedoff.get( ) ? 1337 : -1;
				weapon->m_nFallbackSeed( )     = g_menu.main.skins.seed_sawedoff.get( );
				weapon->m_flFallbackWear( )    = ( ( 100.f - g_menu.main.skins.quality_sawedoff.get( ) ) / 100.f ) + FLT_EPSILON;
				break;
			case TEC9:
				weapon->m_nFallbackPaintKit( ) = g_menu.main.skins.id_tec9.get( );
				weapon->m_nFallbackStatTrak( ) = g_menu.main.skins.stattrak_tec9.get( ) ? 1337 : -1;
				weapon->m_nFallbackSeed( )     = g_menu.main.skins.seed_tec9.get( );
				weapon->m_flFallbackWear( )    = ( ( 100.f - g_menu.main.skins.quality_tec9.get( ) ) / 100.f ) + FLT_EPSILON;
				break;
			case P2000:
				weapon->m_nFallbackPaintKit( ) = g_menu.main.skins.id_p2000.get( );
				weapon->m_nFallbackStatTrak( ) = g_menu.main.skins.stattrak_p2000.get( ) ? 1337 : -1;
				weapon->m_nFallbackSeed( )     = g_menu.main.skins.seed_p2000.get( );
				weapon->m_flFallbackWear( )    = ( ( 100.f - g_menu.main.skins.quality_p2000.get( ) ) / 100.f ) + FLT_EPSILON;
				break;
			case MP7:
				weapon->m_nFallbackPaintKit( ) = g_menu.main.skins.id_mp7.get( );
				weapon->m_nFallbackStatTrak( ) = g_menu.main.skins.stattrak_mp7.get( ) ? 1337 : -1;
				weapon->m_nFallbackSeed( )     = g_menu.main.skins.seed_mp7.get( );
				weapon->m_flFallbackWear( )    = ( ( 100.f - g_menu.main.skins.quality_mp7.get( ) ) / 100.f ) + FLT_EPSILON;
				break;
			case MP9:
				weapon->m_nFallbackPaintKit( ) = g_menu.main.skins.id_mp9.get( );
				weapon->m_nFallbackStatTrak( ) = g_menu.main.skins.stattrak_mp9.get( ) ? 1337 : -1;
				weapon->m_nFallbackSeed( )     = g_menu.main.skins.seed_mp9.get( );
				weapon->m_flFallbackWear( )    = ( ( 100.f - g_menu.main.skins.quality_mp9.get( ) ) / 100.f ) + FLT_EPSILON;
				break;
			case NOVA:
				weapon->m_nFallbackPaintKit( ) = g_menu.main.skins.id_nova.get( );
				weapon->m_nFallbackStatTrak( ) = g_menu.main.skins.stattrak_nova.get( ) ? 1337 : -1;
				weapon->m_nFallbackSeed( )     = g_menu.main.skins.seed_nova.get( );
				weapon->m_flFallbackWear( )    = ( ( 100.f - g_menu.main.skins.quality_nova.get( ) ) / 100.f ) + FLT_EPSILON;
				break;
			case P250:
				weapon->m_nFallbackPaintKit( ) = g_menu.main.skins.id_p250.get( );
				weapon->m_nFallbackStatTrak( ) = g_menu.main.skins.stattrak_p250.get( ) ? 1337 : -1;
				weapon->m_nFallbackSeed( )     = g_menu.main.skins.seed_p250.get( );
				weapon->m_flFallbackWear( )    = ( ( 100.f - g_menu.main.skins.quality_p250.get( ) ) / 100.f ) + FLT_EPSILON;
				break;
			case SCAR20:
				weapon->m_nFallbackPaintKit( ) = g_menu.main.skins.id_scar20.get( );
				weapon->m_nFallbackStatTrak( ) = g_menu.main.skins.stattrak_scar20.get( ) ? 1337 : -1;
				weapon->m_nFallbackSeed( )     = g_menu.main.skins.seed_scar20.get( );
				weapon->m_flFallbackWear( )    = ( ( 100.f - g_menu.main.skins.quality_scar20.get( ) ) / 100.f ) + FLT_EPSILON;
				break;
			case SG553:
				weapon->m_nFallbackPaintKit( ) = g_menu.main.skins.id_sg553.get( );
				weapon->m_nFallbackStatTrak( ) = g_menu.main.skins.stattrak_sg553.get( ) ? 1337 : -1;
				weapon->m_nFallbackSeed( )     = g_menu.main.skins.seed_sg553.get( );
				weapon->m_flFallbackWear( )    = ( ( 100.f - g_menu.main.skins.quality_sg553.get( ) ) / 100.f ) + FLT_EPSILON;
				break;
			case SSG08:
				weapon->m_nFallbackPaintKit( ) = g_menu.main.skins.id_ssg08.get( );
				weapon->m_nFallbackStatTrak( ) = g_menu.main.skins.stattrak_ssg08.get( ) ? 1337 : -1;
				weapon->m_nFallbackSeed( )     = g_menu.main.skins.seed_ssg08.get( );
				weapon->m_flFallbackWear( )    = ( ( 100.f - g_menu.main.skins.quality_ssg08.get( ) ) / 100.f ) + FLT_EPSILON;
				break;
			case M4A1S:
				weapon->m_nFallbackPaintKit( ) = g_menu.main.skins.id_m4a1s.get( );
				weapon->m_nFallbackStatTrak( ) = g_menu.main.skins.stattrak_m4a1s.get( ) ? 1337 : -1;
				weapon->m_nFallbackSeed( )     = g_menu.main.skins.seed_m4a1s.get( );
				weapon->m_flFallbackWear( )    = ( ( 100.f - g_menu.main.skins.quality_m4a1s.get( ) ) / 100.f ) + FLT_EPSILON;
				break;
			case USPS:
				weapon->m_nFallbackPaintKit( ) = g_menu.main.skins.id_usps.get( );
				weapon->m_nFallbackStatTrak( ) = g_menu.main.skins.stattrak_usps.get( ) ? 1337 : -1;
				weapon->m_nFallbackSeed( )     = g_menu.main.skins.seed_usps.get( );
				weapon->m_flFallbackWear( )    = ( ( 100.f - g_menu.main.skins.quality_usps.get( ) ) / 100.f ) + FLT_EPSILON;
				break;
			case CZ75A:
				weapon->m_nFallbackPaintKit( ) = g_menu.main.skins.id_cz75a.get( );
				weapon->m_nFallbackStatTrak( ) = g_menu.main.skins.stattrak_cz75a.get( ) ? 1337 : -1;
				weapon->m_nFallbackSeed( )     = g_menu.main.skins.seed_cz75a.get( );
				weapon->m_flFallbackWear( )    = ( ( 100.f - g_menu.main.skins.quality_cz75a.get( ) ) / 100.f ) + FLT_EPSILON;
				break;
			case REVOLVER:
				weapon->m_nFallbackPaintKit( ) = g_menu.main.skins.id_revolver.get( );
				weapon->m_nFallbackStatTrak( ) = g_menu.main.skins.stattrak_revolver.get( ) ? 1337 : -1;
				weapon->m_nFallbackSeed( )     = g_menu.main.skins.seed_revolver.get( );
				weapon->m_flFallbackWear( )    = ( ( 100.f - g_menu.main.skins.quality_revolver.get( ) ) / 100.f ) + FLT_EPSILON;
				break;
			case KNIFE_BAYONET:
				weapon->m_nFallbackPaintKit( ) = g_menu.main.skins.id_bayonet.get( );
				weapon->m_nFallbackStatTrak( ) = g_menu.main.skins.stattrak_bayonet.get( ) ? 1337 : -1;
				weapon->m_nFallbackSeed( )     = g_menu.main.skins.seed_bayonet.get( );
				weapon->m_flFallbackWear( )    = ( ( 100.f - g_menu.main.skins.quality_bayonet.get( ) ) / 100.f ) + FLT_EPSILON;
				break;
			case KNIFE_FLIP:
				weapon->m_nFallbackPaintKit( ) = g_menu.main.skins.id_flip.get( );
				weapon->m_nFallbackStatTrak( ) = g_menu.main.skins.stattrak_flip.get( ) ? 1337 : -1;
				weapon->m_nFallbackSeed( )     = g_menu.main.skins.seed_flip.get( );
				weapon->m_flFallbackWear( )    = ( ( 100.f - g_menu.main.skins.quality_flip.get( ) ) / 100.f ) + FLT_EPSILON;
				break;
			case KNIFE_GUT:
				weapon->m_nFallbackPaintKit( ) = g_menu.main.skins.id_gut.get( );
				weapon->m_nFallbackStatTrak( ) = g_menu.main.skins.stattrak_gut.get( ) ? 1337 : -1;
				weapon->m_nFallbackSeed( )     = g_menu.main.skins.seed_gut.get( );
				weapon->m_flFallbackWear( )    = ( ( 100.f - g_menu.main.skins.quality_gut.get( ) ) / 100.f ) + FLT_EPSILON;
				break;
			case KNIFE_KARAMBIT:
				weapon->m_nFallbackPaintKit( ) = g_menu.main.skins.id_karambit.get( );
				weapon->m_nFallbackStatTrak( ) = g_menu.main.skins.stattrak_karambit.get( ) ? 1337 : -1;
				weapon->m_nFallbackSeed( )     = g_menu.main.skins.seed_karambit.get( );
				weapon->m_flFallbackWear( )    = ( ( 100.f - g_menu.main.skins.quality_karambit.get( ) ) / 100.f ) + FLT_EPSILON;
				break;
			case KNIFE_M9_BAYONET:
				weapon->m_nFallbackPaintKit( ) = g_menu.main.skins.id_m9.get( );
				weapon->m_nFallbackStatTrak( ) = g_menu.main.skins.stattrak_m9.get( ) ? 1337 : -1;
				weapon->m_nFallbackSeed( )     = g_menu.main.skins.seed_m9.get( );
				weapon->m_flFallbackWear( )    = ( ( 100.f - g_menu.main.skins.quality_m9.get( ) ) / 100.f ) + FLT_EPSILON;
				break;
			case KNIFE_HUNTSMAN:
				weapon->m_nFallbackPaintKit( ) = g_menu.main.skins.id_huntsman.get( );
				weapon->m_nFallbackStatTrak( ) = g_menu.main.skins.stattrak_huntsman.get( ) ? 1337 : -1;
				weapon->m_nFallbackSeed( )     = g_menu.main.skins.seed_huntsman.get( );
				weapon->m_flFallbackWear( )    = ( ( 100.f - g_menu.main.skins.quality_huntsman.get( ) ) / 100.f ) + FLT_EPSILON;
				break;
			case KNIFE_FALCHION:
				weapon->m_nFallbackPaintKit( ) = g_menu.main.skins.id_falchion.get( );
				weapon->m_nFallbackStatTrak( ) = g_menu.main.skins.stattrak_falchion.get( ) ? 1337 : -1;
				weapon->m_nFallbackSeed( )     = g_menu.main.skins.seed_falchion.get( );
				weapon->m_flFallbackWear( )    = ( ( 100.f - g_menu.main.skins.quality_falchion.get( ) ) / 100.f ) + FLT_EPSILON;
				break;
			case KNIFE_BOWIE:
				weapon->m_nFallbackPaintKit( ) = g_menu.main.skins.id_bowie.get( );
				weapon->m_nFallbackStatTrak( ) = g_menu.main.skins.stattrak_bowie.get( ) ? 1337 : -1;
				weapon->m_nFallbackSeed( )     = g_menu.main.skins.seed_bowie.get( );
				weapon->m_flFallbackWear( )    = ( ( 100.f - g_menu.main.skins.quality_bowie.get( ) ) / 100.f ) + FLT_EPSILON;
				break;
			case KNIFE_BUTTERFLY:
				weapon->m_nFallbackPaintKit( ) = g_menu.main.skins.id_butterfly.get( );
				weapon->m_nFallbackStatTrak( ) = g_menu.main.skins.stattrak_butterfly.get( ) ? 1337 : -1;
				weapon->m_nFallbackSeed( )     = g_menu.main.skins.seed_butterfly.get( );
				weapon->m_flFallbackWear( )    = ( ( 100.f - g_menu.main.skins.quality_butterfly.get( ) ) / 100.f ) + FLT_EPSILON;
				break;
			case KNIFE_SHADOW_DAGGERS:
				weapon->m_nFallbackPaintKit( ) = g_menu.main.skins.id_daggers.get( );
				weapon->m_nFallbackStatTrak( ) = g_menu.main.skins.stattrak_daggers.get( ) ? 1337 : -1;
				weapon->m_nFallbackSeed( )     = g_menu.main.skins.seed_daggers.get( );
				weapon->m_flFallbackWear( )    = ( ( 100.f - g_menu.main.skins.quality_daggers.get( ) ) / 100.f ) + FLT_EPSILON;
				break;

			default:
				break;
			}

			// fix stattrak ownership.
			weapon->m_iAccountID( ) = info.m_xuid_low;

			// fix stattrak in hud.
			if( weapon->m_nFallbackStatTrak( ) >= 0 )
				weapon->m_iEntityQuality( ) = 9;

			// force use fallback values.
			weapon->m_iItemIDHigh( ) = -1;
		}
	}

	if( g_menu.main.skins.glove.get( ) > 0 ) {
		CBaseHandle* wearables = g_cl.m_local->m_hMyWearables( );

		// get pointer to entity from wearable handle 0.
		// glove is at wearable 0, valve will likely add more wearables like hats and boots. thats why.
		Weapon* glove = g_csgo.m_entlist->GetClientEntityFromHandle< Weapon* >( wearables[ 0 ] );

		// there is no glove entity yet.
		if( !glove ) {
			// attempt to get our old glove.
			Weapon* old = g_csgo.m_entlist->GetClientEntityFromHandle< Weapon* >( m_glove_handle );

			// this glove is still valid.
			if( old ) {

				// write back handle to wearables.
				wearables[ 0 ] = m_glove_handle;

				// set glove pointer.
				glove = old;
			}
		}

		// if we at this point still not have a glove entity.
		// we should create one.
		if( !glove ) {
			ClientClass* list{ g_csgo.m_client->GetAllClasses( ) };

			// iterate list.
			for( ; list != nullptr; list = list->m_pNext ) {

				// break if we found wearable
				if( list->m_ClassID == g_netvars.GetClientID( HASH( "CEconWearable" ) ) )
					break;
			}

			// create an ent index and serial no for the new glove entity.
			int index  = g_csgo.m_entlist->GetHighestEntityIndex( ) + 1;
			int serial = g_csgo.RandomInt( 0xA00, 0xFFF );

			// call ctor on CEconWearable entity.
			Address networkable = list->m_pCreate( index, serial );

			// get entity ptr via index.
			glove = g_csgo.m_entlist->GetClientEntity< Weapon* >( index );

			static Address offset = g_netvars.get( HASH( "DT_EconEntity" ), HASH( "m_iItemIDLow" ) );

			// m_bInitialized?
			networkable.add( offset.add( 0x8 ) ).set< bool >( true );

			// no idea what this is.
			networkable.add( offset.sub( 0xC ) ).set< bool >( true );

			// set the wearable handle.
			wearables[ 0 ] = index | ( serial << 16 );

			// use this for later on.
			m_glove_handle = wearables[ 0 ];
		}

		// store glove data.
		GloveData* data = &m_glove_data[ g_menu.main.skins.glove.get( ) ];

		// set default data,
		glove->m_nFallbackSeed( )     = 0;
		glove->m_nFallbackStatTrak( ) = -1;
		glove->m_iItemIDHigh( )       = -1;
		glove->m_iEntityQuality( )    = 4;
		glove->m_iAccountID( )        = info.m_xuid_low;

		// set custom data.
		glove->m_nFallbackPaintKit( ) = 10000 + g_menu.main.skins.glove_id.get( );
		glove->m_iItemDefinitionIndex( ) = data->m_id;
		glove->SetGloveModelIndex( data->m_model_index );

		// update the glove.
		glove->PreDataUpdate( DATA_UPDATE_CREATED );
	}

	// only force update every 1s.
	if( m_update && g_csgo.m_globals->m_curtime >= m_update_time ) {
		for( auto& w : weapons )
			UpdateItem( w );

		m_update      = false;
		m_update_time = g_csgo.m_globals->m_curtime + 1.f;
	}
}

void Skins::UpdateItem( Weapon* item ) {
	if( !item || !item->IsBaseCombatWeapon( ) )
		return;

	if( g_csgo.m_cl->m_delta_tick == -1 )
		return;

	//  if ( sub_106E32D0(v4, "round_start") )
	//		SFWeaponSelection::ShowAndUpdateSelection( v2, 2, 0, v10 );

	// v1 = CHud::FindElement(&g_HUD, "SFWeaponSelection");
	// if( v1 )
	//		SFWeaponSelection::ShowAndUpdateSelection( ( int * )v1, 2, 0, this );
	
	item->m_bCustomMaterialInitialized( ) = item->m_nFallbackPaintKit( ) <= 0;

	item->m_CustomMaterials( ).RemoveAll( );
	item->m_CustomMaterials2( ).RemoveAll( );

	size_t count = item->m_VisualsDataProcessors( ).Count( );
	for( size_t i{}; i < count; ++i ) {
		auto& elem = item->m_VisualsDataProcessors( )[ i ];
		if( elem ) {
			elem->unreference( );
			elem = nullptr;
		}
	}

	item->m_VisualsDataProcessors( ).RemoveAll( );

	item->PostDataUpdate( DATA_UPDATE_CREATED );
	item->OnDataChanged( DATA_UPDATE_CREATED );

	CHudElement* SFWeaponSelection = g_csgo.m_hud->FindElement( HASH( "SFWeaponSelection" ) );
	g_csgo.ShowAndUpdateSelection( SFWeaponSelection, 0, item, false );
}

void Skins::UpdateAnimations( Entity* ent ) {
	int knife = g_menu.main.skins.knife.get( );

	int seq = ent->m_nSequence( );

	// check if this knife needs extra fixing.
	if( knife == knives_t::BUTTERFLY || knife == knives_t::FALCHION || knife == knives_t::DAGGER || knife == knives_t::BOWIE ) {

		// fix the idle sequences.
		if( seq == sequence_default_idle1 || seq == sequence_default_idle2 ) {
			// set the animation to be completed.
			ent->m_flCycle( ) = 0.999f;

			// cycle change, re-render.
			ent->InvalidatePhysicsRecursive( ANIMATION_CHANGED );
		}
	}

	// fix sequences.
	if( m_last_seq != seq ) {
		if( knife == knives_t::BUTTERFLY ) {
			switch( seq ) {
			case sequence_default_draw:
				seq = g_csgo.RandomInt( sequence_butterfly_draw, sequence_butterfly_draw2 );
				break;

			case sequence_default_lookat01:
				seq = g_csgo.RandomInt( sequence_butterfly_lookat01, sequence_butterfly_lookat03 );
				break;

			default:
				seq++;
				break;
			}
		}

		else if( knife == knives_t::FALCHION ) {
			switch( seq ) {
			case sequence_default_draw:
			case sequence_default_idle1:
				break;

			case sequence_default_idle2:
				seq = sequence_falchion_idle1;
				break;

			case sequence_default_heavy_miss1:
				seq = g_csgo.RandomInt( sequence_falchion_heavy_miss1, sequence_falchion_heavy_miss1_noflip );
				break;

			case sequence_default_lookat01:
				seq = g_csgo.RandomInt( sequence_falchion_lookat01, sequence_falchion_lookat02 );
				break;
			}
		}

		else if( knife == knives_t::DAGGER ) {
			switch( seq ) {
			case sequence_default_idle2:
				seq = sequence_push_idle1;
				break;

			case sequence_default_heavy_hit1:
			case sequence_default_heavy_backstab:
			case sequence_default_lookat01:
				seq += 3;
				break;

			case sequence_default_heavy_miss1:
				seq = sequence_push_heavy_miss2;
				break;
			}

		}

		else if( knife == knives_t::BOWIE ) {
			if( seq > sequence_default_idle1 )
				seq--;
		}

		m_last_seq = seq;
	}

	// write back fixed sequence.
	ent->m_nSequence( ) = seq;
}