#include "includes.h"

void Hooks::ComputeShadowDepthTextures( const CViewSetup &view, bool unk ) {
	if( !unk )
		return g_hooks.m_shadow_mgr.GetOldMethod< ComputeShadowDepthTextures_t >( IClientShadowMgr::COMPUTESHADOWDEPTHTEXTURES )( this, view, unk );

	if( g_menu.main.visuals.disableteam.get( ) ) {
		for( int i{ 1 }; i <= g_csgo.m_globals->m_max_clients; ++i ) {
			Player* player = g_csgo.m_entlist->GetClientEntity< Player* >( i );

			if( !player )
				continue;

			if( player->m_bIsLocalPlayer( ) )
				continue;

			if( !player->enemy( g_cl.m_local ) ) {
				// disable all rendering at the root.
				player->m_bReadyToDraw( ) = false;

				// now stop rendering their weapon.
				Weapon* weapon = player->GetActiveWeapon( );
				if( weapon )
					weapon->m_bReadyToDraw( ) = false;
			}
		}
	}

	g_hooks.m_shadow_mgr.GetOldMethod< ComputeShadowDepthTextures_t >( IClientShadowMgr::COMPUTESHADOWDEPTHTEXTURES )( this, view, unk );
}