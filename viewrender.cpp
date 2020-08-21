#include "includes.h"

void Hooks::OnRenderStart( ) {
	// call og.
	g_hooks.m_view_render.GetOldMethod< OnRenderStart_t >( CViewRender::ONRENDERSTART )( this );

	if( g_menu.main.visuals.fov.get( ) ) {
		if( g_cl.m_local && g_cl.m_local->m_bIsScoped( ) ) {
			if( g_menu.main.visuals.fov_scoped.get( ) ) {
				if( g_cl.m_local->GetActiveWeapon( )->m_zoomLevel( ) != 2 ) {
					g_csgo.m_view_render->m_view.m_fov = g_menu.main.visuals.fov_amt.get( );
				}
				else {
					g_csgo.m_view_render->m_view.m_fov += 45.f;
				}
			}
		}

		else g_csgo.m_view_render->m_view.m_fov = g_menu.main.visuals.fov_amt.get( );
	}

	if( g_menu.main.visuals.viewmodel_fov.get( ) )
		g_csgo.m_view_render->m_view.m_viewmodel_fov = g_menu.main.visuals.viewmodel_fov_amt.get( );
}

void Hooks::RenderView( const CViewSetup &view, const CViewSetup &hud_view, int clear_flags, int what_to_draw ) {
	// ...

	g_hooks.m_view_render.GetOldMethod< RenderView_t >( CViewRender::RENDERVIEW )( this, view, hud_view, clear_flags, what_to_draw );
}

void Hooks::Render2DEffectsPostHUD( const CViewSetup &setup ) {
	if( !g_menu.main.visuals.noflash.get( ) )
		g_hooks.m_view_render.GetOldMethod< Render2DEffectsPostHUD_t >( CViewRender::RENDER2DEFFECTSPOSTHUD )( this, setup );
}

void Hooks::RenderSmokeOverlay( bool unk ) {
	// do not render smoke overlay.
	if( !g_menu.main.visuals.nosmoke.get( ) )
		g_hooks.m_view_render.GetOldMethod< RenderSmokeOverlay_t >( CViewRender::RENDERSMOKEOVERLAY )( this, unk );
}
