#pragma once

#define KEYBIND_X_OFFSET      20
#define KEYBIND_BOX_HEIGHT    20
#define KEYBIND_ITEM_X_OFFSET 10

class Keybind : public Element {
	friend class GUI;

	using ToggleCallback_t = void( *)( );

public:
	__forceinline Keybind( ) : m_key{ -1 }, m_label{}, m_set{}, m_old_set{}, m_toggle{} {
		m_flags  = ElementFlags::DRAW | ElementFlags::CLICK | ElementFlags::SAVE;
		m_type   = ElementTypes::KEYBIND;
		m_base_h = m_h = 15 + KEYBIND_BOX_HEIGHT;
	}

	__forceinline void setup( const std::string& label, const std::string& file_id, int key = -1 ) {
		m_label   = label;
		m_file_id = file_id;
		m_key     = key;
	}

	__forceinline void SetToggleCallback( ToggleCallback_t t ) {
		m_toggle = t;
	}

	__forceinline void set( int key ) {
		bool changed = m_key != key;

		m_key = key;

		if( changed && m_callback )
			m_callback( );
	}

	__forceinline int get( ) {
		return m_key;
	}

protected:
	int			     m_key;
	std::string      m_label;
	bool		     m_set;
	bool		     m_old_set;
	ToggleCallback_t m_toggle;

protected:
	void draw( ) override;
	void think( ) override;
	void click( ) override;
};