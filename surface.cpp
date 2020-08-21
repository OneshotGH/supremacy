#include "includes.h"

/*void Hooks::GetScreenSize( int& w, int& h ) {
	//Stack stack;

	//static Address DrawCrosshairW{ pattern::find( g_csgo.m_client_dll, XOR( "99 2B C2 D1 F8 89 44 24 18" ) ) };
	//static Address DrawCrosshairH{ pattern::find( g_csgo.m_client_dll, XOR( "8B 0D ? ? ? ? 99 2B C2 D1 F8 89" ) ) };

	// run the original method first.
	g_hooks.m_surface.GetOldMethod< Hooks::GetScreenSize_t >( ISurface::GETSCREENSIZE )( this, w, h );

	//if( stack.next( ).return_address( ) == DrawCrosshairW )
	//	w = 50;

	//if( stack.next( ).return_address( ) == DrawCrosshairH )
	//	h = 50;
}*/

void Hooks::LockCursor( ) {
	if( g_gui.m_open ) {

		// un-lock the cursor.
		g_csgo.m_surface->UnlockCursor( );

		// disable input.
		g_csgo.m_input_system->EnableInput( false );
	}

	else {
		// call the original.
		g_hooks.m_surface.GetOldMethod< LockCursor_t >( ISurface::LOCKCURSOR )( this );

		// enable input.
		g_csgo.m_input_system->EnableInput( true );
	}
}

void Hooks::PlaySound( const char* name ) {
	g_hooks.m_surface.GetOldMethod< PlaySound_t >( ISurface::PLAYSOUND )( this, name );

	if( g_menu.main.misc.autoaccept.get( ) ) {

		// auto accept.
		if( FNV1a::get( name ) == HASH( "!UI/competitive_accept_beep.wav" ) && !g_csgo.m_engine->IsInGame( ) ) {
			// accept match.
			g_csgo.IsReady( );

			// notify user.
			g_csgo.m_surface->PlaySound( XOR( "ui/xp_levelup.wav" ) );
		}
	}
}

void Hooks::OnScreenSizeChanged( int oldwidth, int oldheight ) {
	g_hooks.m_surface.GetOldMethod< OnScreenSizeChanged_t >( ISurface::ONSCREENSIZECHANGED )( this, oldwidth, oldheight );

	render::init( );

	Visuals::ModulateWorld( );
}