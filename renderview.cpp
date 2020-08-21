#include "includes.h"

void Hooks::SceneEnd( ) {
	g_hooks.m_render_view.GetOldMethod< Hooks::SceneEnd_t >( IVRenderView::SCENEEND )( this );

	g_chams.SceneEnd( );
}