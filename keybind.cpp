#include "includes.h"

const std::string keynames[] = {
	"", XOR( "mouse1" ), XOR( "mouse2" ), XOR( "cancel" ), XOR( "mouse3" ), XOR( "mouse4" ), XOR( "mouse5" ), XOR( "[7]" ),
	XOR( "backspace" ), XOR( "tab" ), XOR( "[10]" ), XOR( "[11]" ), XOR( "num 5" ), XOR( "enter" ), XOR( "[14]" ), XOR( "[15]" ), XOR( "shift" ),
	XOR( "ctrl" ), XOR( "alt" ), XOR( "[19]" ), XOR( "capslock" ), XOR( "[21]" ), XOR( "[22]" ), XOR( "[23]" ), XOR( "[24]" ), XOR( "[25]" ),
	XOR( "[26]" ), XOR( "esc" ), XOR( "[28]" ), XOR( "[29]" ), XOR( "[30]" ), XOR( "[31]" ), XOR( "space" ), XOR( "pgup" ), XOR( "pgdown" ), XOR( "end" ),
	XOR( "home" ), XOR( "left" ), XOR( "up" ), XOR( "right" ), XOR( "down" ), XOR( "[41]" ), XOR( "[42]" ), XOR( "[43]" ), XOR( "[44]" ), XOR( "insert" ),
	XOR( "delete" ), XOR( "[47]" ), XOR( "0" ), XOR( "1" ), XOR( "2" ), XOR( "3" ), XOR( "4" ), XOR( "5" ), XOR( "6" ), XOR( "7" ), XOR( "8" ), XOR( "9" ),
	XOR( "[58]" ),  XOR( "[59]" ), XOR( "[60]" ), XOR( "[61]" ), XOR( "[62]" ), XOR( "[63]" ), XOR( "[64]" ), XOR( "a" ), XOR( "b" ), XOR( "c" ), XOR( "d" ),
	XOR( "e" ),  XOR( "f" ), XOR( "g" ), XOR( "h" ), XOR( "i" ), XOR( "j" ), XOR( "k" ), XOR( "l" ), XOR( "m" ), XOR( "n" ), XOR( "o" ), XOR( "p" ), XOR( "q" ),
	XOR( "r" ), XOR( "s" ), XOR( "t" ), XOR( "u" ), XOR( "v" ), XOR( "w" ), XOR( "x" ), XOR( "y" ), XOR( "z" ),	XOR( "left win" ), XOR( "right win" ),
	XOR( "application" ), XOR( "[94]" ),  XOR( "[95]" ), XOR( "num 0" ), XOR( "num 1" ), XOR( "num 2" ), XOR( "num 3" ), XOR( "num 4" ), XOR( "num 5" ),
	XOR( "num 6" ), XOR( "num 7" ), XOR( "num 8" ),  XOR( "num 9" ), XOR( "num mult" ), XOR( "num plus" ), XOR( "[108]" ), XOR( "num sub" ), XOR( "num decimal" ),
	XOR( "num divide" ), XOR( "f1" ), XOR( "f2" ),  XOR( "f3" ), XOR( "f4" ), XOR( "f5" ), XOR( "f6" ), XOR( "f7" ), XOR( "f8" ), XOR( "f9" ), XOR( "f10" ),
	XOR( "f11" ), XOR( "f12" ), XOR( "f13" ), XOR( "f14" ), XOR( "f15" ), XOR( "f16" ), XOR( "f17" ),  XOR( "f18" ), XOR( "f19" ), XOR( "f20" ), XOR( "f21" ),
	XOR( "f22" ), XOR( "f23" ), XOR( "f24" ), XOR( "[136]" ), XOR( "[137]" ), XOR( "[138]" ), XOR( "[139]" ), XOR( "[140]" ), XOR( "[141]" ), XOR( "[142]" ),
	XOR( "[143]" ), XOR( "num lock" ), XOR( "break" ), XOR( "[146]" ), XOR( "[147]" ), XOR( "[148]" ), XOR( "[149]" ), XOR( "[150]" ), XOR( "[151]" ), XOR( "[152]" ),
	XOR( "[153]" ), XOR( "[154]" ), XOR( "[155]" ), XOR( "[156]" ),  XOR( "[157]" ), XOR( "[158]" ), XOR( "[159]" ), XOR( "[160]" ), XOR( "[161]" ), XOR( "ctrl" ),
	XOR( "ctrl" ), XOR( "alt" ), XOR( "alt" ), XOR( "[166]" ), XOR( "[167]" ), XOR( "[168]" ), XOR( "[169]" ), XOR( "[170]" ), XOR( "[171]" ), XOR( "m" ), XOR( "d" ),
	XOR( "c" ), XOR( "b" ),  XOR( "p" ), XOR( "q" ), XOR( "j" ), XOR( "g" ), XOR( "[180]" ), XOR( "[181]" ), XOR( "[182]" ), XOR( "f" ), XOR( "[184]" ), XOR( "[185]" ),
	XOR( ";" ), XOR( "=" ), XOR( " )," ), XOR( "-" ), XOR( "." ), XOR( "/" ), XOR( "grave" ), XOR( "[193]" ), XOR( "[194]" ), XOR( "[195]" ), XOR( "[196]" ),
	XOR( "[197]" ), XOR( "[198]" ),  XOR( "[199]" ), XOR( "[200]" ), XOR( "[201]" ), XOR( "[202]" ), XOR( "[203]" ), XOR( "[204]" ), XOR( "[205]" ), XOR( "[206]" ),
	XOR( "[207]" ), XOR( "[208]" ), XOR( "[209]" ), XOR( "[210]" ), XOR( "[211]" ), XOR( "[212]" ), XOR( "[213]" ), XOR( "[214]" ), XOR( "[215]" ), XOR( "[216]" ),
	XOR( "[217]" ),  XOR( "[218]" ), XOR( "[" ), XOR( "\\" ), XOR( "]" ), XOR( "[222]" ), XOR( "[223]" ), XOR( "[224]" ), XOR( "[225]" ), XOR( "\\" ), XOR( "[227]" ),
	XOR( "[228]" ), XOR( "[229]" ), XOR( "[230]" ), XOR( "[231]" ), XOR( "[232]" ), XOR( "[233]" ), XOR( "right win" ), XOR( "[235]" ), XOR( "[236]" ), XOR( "[237]" ),
	XOR( "[238]" ), XOR( "[239]" ), XOR( "[240]" ), XOR( "left win" ), XOR( "[242]" ), XOR( "[243]" ), XOR( "[244]" ), XOR( "[245]" ), XOR( "[246]" ), XOR( "[247]" ),
	XOR( "[248]" ), XOR( "application" ), XOR( "[250]" ), XOR( "[251]" ), XOR( "[252]" ), XOR( "[253]" )
};;

void Keybind::draw( ) {
	Rect  area{ m_parent->GetElementsRect( ) };
	Point p{ area.x + m_pos.x, area.y + m_pos.y };

	// get gui color.
	Color color = g_gui.m_color;
	color.a( ) = m_parent->m_alpha;

	// draw label.
	render::menu.string( p.x + KEYBIND_X_OFFSET, p.y - 2, { 205, 205, 205, m_parent->m_alpha }, m_label );

	// box outline.
	render::rect( p.x + KEYBIND_X_OFFSET, p.y + 15, m_w - KEYBIND_X_OFFSET, KEYBIND_BOX_HEIGHT, { 0, 0, 0, m_parent->m_alpha } );

	// inner blob
	// todo; gradient?
	render::rect_filled( p.x + KEYBIND_X_OFFSET + 1, p.y + 15 + 1, m_w - KEYBIND_X_OFFSET - 2, KEYBIND_BOX_HEIGHT - 2, { 41, 41, 41, m_parent->m_alpha } );

	// todo; animate with '...'
	if( m_set )
		render::menu.string( p.x + KEYBIND_X_OFFSET + KEYBIND_ITEM_X_OFFSET, p.y + 15 + 4, color, XOR( "press key" ) );

	// we have a key assigned.
	else if( m_key >= 0 && m_key <= 0xFE )
		render::menu.string( p.x + KEYBIND_X_OFFSET + KEYBIND_ITEM_X_OFFSET, p.y + 15 + 4, { 152, 152, 152, m_parent->m_alpha }, keynames[ m_key ] );
}

void Keybind::think( ) {
	// we want to set a key.
	if( m_set ) {

		// iterate all keystates.
		for( int i{}; i <= 0xFE; ++i ) {

			// find pressed key.
			if( g_input.GetKeyPress( i ) ) {
				// escape is our wildcard.
				if( i == VK_ESCAPE ) {
					m_key = -1;
					m_set = false;

					if( m_callback )
						m_callback( );

					return;
				}

				m_key     = i;
				m_set     = false;
				m_old_set = true;

				if( m_callback )
					m_callback( );

				return;
			}
		}
	}

	else m_old_set = false;
}

void Keybind::click( ) {
	Rect  area{ m_parent->GetElementsRect( ) };
	Point p{ area.x + m_pos.x, area.y + m_pos.y };

	// area where user has to click.
	Rect bind = { p.x + KEYBIND_X_OFFSET, p.y + 15, m_w - KEYBIND_X_OFFSET, KEYBIND_BOX_HEIGHT };

	if( !m_set && !m_old_set && g_input.IsCursorInRect( bind ) )
		m_set = true;
}