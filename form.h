#pragma once

class Form {
	friend class GUI;
	friend class Element;
	friend class Dropdown;
	friend class MultiDropdown;
	friend class Colorpicker;
	friend class Edit;
	friend class Config;

public:
	bool                m_open;
	float               m_opacity;
	int                 m_alpha;
private:
	int                 m_key;
	int	                m_x;
	int	                m_y;
	int                 m_width;
	int                 m_height;
	int                 m_tick;
	std::vector< Tab* >	m_tabs;
	Tab*				m_active_tab;
	Element*			m_active_element;

public:
	__forceinline Form( ) : m_open{ true }, m_opacity{}, m_alpha{}, m_key{ -1 }, m_x{}, m_y{}, m_width{}, m_height{}, m_tick{}, m_tabs{}, m_active_tab{}, m_active_element{} {}

	__forceinline void SetPosition( int x, int y ) {
		m_x = x;
		m_y = y;
	}

	__forceinline void SetSize( int w, int h ) {
		m_width  = w;
		m_height = h;
	}

	__forceinline void SetToggle( int key ) {
		m_key = key;
	}

	// adds a new tab.
	__forceinline void RegisterTab( Tab* tab ) {
		// if this is the first tab, set the active tab.
		if( !m_tabs.size( ) )
			m_active_tab = tab;

		// this form is the owner of the tab.
		tab->m_parent = this;

		// add the tab to our container.
		m_tabs.push_back( tab );
	}

	// get specific tab based off name.
	__forceinline Tab* GetTabByName( const std::string& name ) const {
		auto it = std::find_if( m_tabs.begin( ), m_tabs.end( ),
		[ &name ]( Tab* tab ) {
			return !tab->m_title.compare( name );
		} );

		if( it != m_tabs.end( ) )
			return *it;

		return nullptr;
	}

	// toggles the form.
	__forceinline void toggle( ) {
		m_open = !m_open;
	}

	// get the click-able area.
	__forceinline Rect GetClientRect( ) const {
		return { m_x + 6, m_y + 6, m_width - 12, m_height - 12 };
	}

	__forceinline Rect GetFormRect( ) const {
		return { m_x, m_y, m_width, m_height };
	}

	__forceinline Rect GetTabsRect( ) const {
		return { m_x + 20, m_y + 20, 100, m_height - 40 };
	}

	__forceinline Rect GetElementsRect( ) const {
		Rect tabs_area = GetTabsRect( );
		return { tabs_area.x + tabs_area.w + 20, m_y + 20, m_width - tabs_area.w - 60, m_height - 40 };
	}

public:
	void draw( );
};