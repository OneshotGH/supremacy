#include "includes.h"
#include "edit.h"

void Edit::draw( ) {
	Rect  area{ m_parent->GetElementsRect( ) };
	Point p{ area.x + m_pos.x, area.y + m_pos.y };

	// draw label.
	render::menu.string( p.x + EDIT_X_OFFSET, p.y - 2, { 205, 205, 205, m_parent->m_alpha }, m_label );

	// box outline.
	render::rect( p.x + EDIT_X_OFFSET, p.y + 15, m_w - EDIT_X_OFFSET, EDIT_BOX_HEIGHT, { 0, 0, 0, m_parent->m_alpha } );

	// inner blob
	// todo; gradient?
	render::rect_filled( p.x + EDIT_X_OFFSET + 1, p.y + 15 + 1, m_w - EDIT_X_OFFSET - 2, EDIT_BOX_HEIGHT - 2, { 41, 41, 41, m_parent->m_alpha } );

	render::menu.string( p.x + EDIT_X_OFFSET + EDIT_ITEM_X_OFFSET, p.y + 15 + 4, { 152, 152, 152, m_parent->m_alpha }, m_text );

	render::FontSize_t size = render::menu.size( m_text );

	if( m_typing && ( g_winapi.GetTickCount( ) / 500 ) % 2 )
		render::rect_filled( p.x + EDIT_X_OFFSET + EDIT_ITEM_X_OFFSET + size.m_width + 1, p.y + 15 + 13, 6, 2, { 152, 152, 152, m_parent->m_alpha } );
}

void Edit::think( ) {
	if( m_typing ) {
		// if we want to exit typing? user presses escape or enter. he is likely done
		if( g_input.GetKeyPress( VK_RETURN ) || g_input.GetKeyPress( VK_ESCAPE ) ) {
			m_typing = false;

			if( m_callback )
				m_callback( );

			return;
		}
		
		// same applies here.
		if( m_parent->m_active_element != this || !m_parent->m_open ) {
			m_typing = false;

			if( m_callback )
				m_callback( );

			return;
		}

		if( !m_old_typing )
			g_input.m_buffer = m_text;

		else
			m_text = g_input.m_buffer;

		if( m_text.size( ) >= m_limit )
			m_text = m_text.substr( 0, m_limit );
			
		m_old_typing = true;
	}

	else m_old_typing = false;
}

void Edit::click( ) {
	if( !m_typing ) {
		Rect  area{ m_parent->GetElementsRect( ) };
		Point p{ area.x + m_pos.x, area.y + m_pos.y };

		// area where user has to click.
		Rect edit = { p.x + EDIT_X_OFFSET, p.y + 15, m_w - EDIT_X_OFFSET, EDIT_BOX_HEIGHT };

		if( g_input.IsCursorInRect( edit ) )
			m_typing = true;
	}
}