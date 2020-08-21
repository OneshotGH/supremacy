#include "includes.h"

void Dropdown::arrow1( Point p ) {
	render::rect_filled( p.x + m_w - 11, p.y + m_offset + 9 + 2, 1, 1, { 152, 152, 152, m_parent->m_alpha } );
	render::rect_filled( p.x + m_w - 10, p.y + m_offset + 9 + 2, 1, 1, { 152, 152, 152, m_parent->m_alpha } );
	render::rect_filled( p.x + m_w - 9, p.y + m_offset + 9 + 2, 1, 1, { 152, 152, 152, m_parent->m_alpha } );
	render::rect_filled( p.x + m_w - 8, p.y + m_offset + 9 + 2, 1, 1, { 152, 152, 152, m_parent->m_alpha } );
	render::rect_filled( p.x + m_w - 7, p.y + m_offset + 9 + 2, 1, 1, { 152, 152, 152, m_parent->m_alpha } );

	render::rect_filled( p.x + m_w - 10, p.y + m_offset + 9 + 1, 1, 1, { 152, 152, 152, m_parent->m_alpha } );
	render::rect_filled( p.x + m_w - 9, p.y + m_offset + 9 + 1, 1, 1, { 152, 152, 152, m_parent->m_alpha } );
	render::rect_filled( p.x + m_w - 8, p.y + m_offset + 9 + 1, 1, 1, { 152, 152, 152, m_parent->m_alpha } );

	render::rect_filled( p.x + m_w - 9, p.y + m_offset + 9, 1, 1, { 152, 152, 152, m_parent->m_alpha } );
}

void Dropdown::arrow2( Point l ) {
	render::rect_filled( l.x + m_w - 11, l.y + m_offset + 9, 1, 1, { 152, 152, 152, m_parent->m_alpha } );
	render::rect_filled( l.x + m_w - 10, l.y + m_offset + 9, 1, 1, { 152, 152, 152, m_parent->m_alpha } );
	render::rect_filled( l.x + m_w - 9, l.y + m_offset + 9, 1, 1, { 152, 152, 152, m_parent->m_alpha } );
	render::rect_filled( l.x + m_w - 8, l.y + m_offset + 9, 1, 1, { 152, 152, 152, m_parent->m_alpha } );
	render::rect_filled( l.x + m_w - 7, l.y + m_offset + 9, 1, 1, { 152, 152, 152, m_parent->m_alpha } );

	render::rect_filled( l.x + m_w - 10, l.y + m_offset + 9 + 1, 1, 1, { 152, 152, 152, m_parent->m_alpha } );
	render::rect_filled( l.x + m_w - 9, l.y + m_offset + 9 + 1, 1, 1, { 152, 152, 152, m_parent->m_alpha } );
	render::rect_filled( l.x + m_w - 8, l.y + m_offset + 9 + 1, 1, 1, { 152, 152, 152, m_parent->m_alpha } );

	render::rect_filled( l.x + m_w - 9, l.y + m_offset + 9 + 2, 1, 1, { 152, 152, 152, m_parent->m_alpha } );
}

void Dropdown::draw( ) {
	Rect	area{ m_parent->GetElementsRect( ) };
	Point	p{ area.x + m_pos.x, area.y + m_pos.y };

	// get gui color.
	Color color = g_gui.m_color;
	color.a( ) = m_parent->m_alpha;

	// draw label.
	if( m_use_label )
		render::menu_shade.string( p.x + LABEL_OFFSET, p.y - 2, { 205, 205, 205, m_parent->m_alpha }, m_label );

	// draw border.
	render::rect( p.x + DROPDOWN_X_OFFSET, p.y + m_offset, m_w - DROPDOWN_X_OFFSET, DROPDOWN_BOX_HEIGHT, { 0, 0, 0, m_parent->m_alpha } );

	// draw inside.
	render::rect_filled( p.x + DROPDOWN_X_OFFSET + 1, p.y + m_offset + 1, m_w - DROPDOWN_X_OFFSET - 2, DROPDOWN_BOX_HEIGHT - 2, { 41, 41, 41, m_parent->m_alpha } );

	// arrow.
	m_open ? arrow1( p ) : arrow2( p );

	// does this dropdown have any items?
	if( !m_items.empty( ) ) {

		// is this dropdown open?
		if( m_open ) {

			// draw items outline.
			render::rect( p.x + DROPDOWN_X_OFFSET, p.y + m_offset + DROPDOWN_BOX_HEIGHT + DROPDOWN_SEPARATOR, m_w - DROPDOWN_X_OFFSET, m_anim_height + 1, { 0, 0, 0, m_parent->m_alpha } );

			// draw items inside.
			render::rect_filled( p.x + DROPDOWN_X_OFFSET + 1, p.y + m_offset + DROPDOWN_BOX_HEIGHT + DROPDOWN_SEPARATOR + 1, m_w - DROPDOWN_X_OFFSET - 2, m_anim_height - 1, { 41, 41, 41, m_parent->m_alpha } );

			// iterate items.
			for( size_t i{}; i < m_items.size( ); ++i ) {

				// get offset to current item.
				int item_offset = ( i * DROPDOWN_ITEM_HEIGHT );

				// has this item been animated yet?
				if( m_anim_height > item_offset ) {

					// yet again, it won't use list init inside the ternary conditional.
					render::menu.string( p.x + DROPDOWN_X_OFFSET + DROPDOWN_ITEM_X_OFFSET, p.y + m_offset + DROPDOWN_BOX_HEIGHT + DROPDOWN_ITEM_Y_OFFSET + item_offset,
						( i == m_active_item ) ? color : Color{ 152, 152, 152, m_parent->m_alpha },
									 m_items[ i ] );
				}
			}
		}

		render::menu.string( p.x + DROPDOWN_X_OFFSET + DROPDOWN_ITEM_X_OFFSET, p.y + m_offset + 4, { 152, 152, 152, m_parent->m_alpha }, GetActiveItem( ) );
	}

	//render::rect( p.x, p.y, m_w, m_pos.h, { 255, 0, 0 } );
}

void Dropdown::think( ) {
	// fucker can be opened.
	if( !m_items.empty( ) ) {
		int total_size = DROPDOWN_ITEM_HEIGHT * m_items.size( );

		// we need to travel 'total_size' in 300 ms.
		float frequency = total_size / 0.3f;

		// the increment / decrement per frame.
		float step = frequency * g_csgo.m_globals->m_frametime;

		// if open		-> increment
		// if closed	-> decrement
		m_open ? m_anim_height += step : m_anim_height -= step;

		// clamp the size.
		math::clamp< float >( m_anim_height, 0, total_size );

		// open
		if( m_open ) {
			// clicky height.
			m_h = m_offset + DROPDOWN_BOX_HEIGHT + DROPDOWN_SEPARATOR + total_size;

			// another element is in focus.
			if( m_parent->m_active_element != this )
				m_open = false;
		}

		// closed.
		else
			m_h = m_offset + DROPDOWN_BOX_HEIGHT;
	}

	// no items, no open.
	else
		m_h = m_offset + DROPDOWN_BOX_HEIGHT;
}

void Dropdown::click( ) {
	Rect  area{ m_parent->GetElementsRect( ) };
	Point p{ area.x + m_pos.x, area.y + m_pos.y };

	// bar.
	Rect bar{ p.x + DROPDOWN_X_OFFSET, p.y + m_offset, m_w - DROPDOWN_X_OFFSET, DROPDOWN_BOX_HEIGHT };

	// pop open if bar pressed
	if( g_input.IsCursorInRect( bar ) )
		m_open = true;

	// check item clicks.
	if( m_open ) {
		if( !g_input.IsCursorInRect( bar ) ) {
			// iterate items.
			for( size_t i{}; i < m_items.size( ); ++i ) {
				Rect item{ p.x + DROPDOWN_X_OFFSET, p.y + m_offset + DROPDOWN_BOX_HEIGHT + DROPDOWN_SEPARATOR + ( i * DROPDOWN_ITEM_HEIGHT ), m_w - DROPDOWN_X_OFFSET, DROPDOWN_ITEM_HEIGHT };

				// click was in context of current item.
				if( g_input.IsCursorInRect( item ) ) {
					m_active_item = i;

					if( m_callback )
						m_callback( );
				}
			}
		}
	}
}