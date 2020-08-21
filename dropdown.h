#pragma once

#define DROPDOWN_X_OFFSET		20
#define DROPDOWN_ITEM_X_OFFSET	10
#define DROPDOWN_ITEM_Y_OFFSET	5
#define DROPDOWN_BOX_HEIGHT		20
#define DROPDOWN_ITEM_HEIGHT	16
#define DROPDOWN_SEPARATOR		2

class Dropdown : public Element {
public:
	__forceinline Dropdown( ) : m_open{ false }, m_label{}, m_items{}, m_anim_height{}, m_active_item{}, m_offset{} {
		m_flags = ElementFlags::DRAW | ElementFlags::CLICK | ElementFlags::ACTIVE | ElementFlags::SAVE | ElementFlags::DEACIVATE;
		m_type  = ElementTypes::DROPDOWN;
		m_show  = true;
	}

	__forceinline void setup( const std::string &label, const std::string &file_id, const std::vector< std::string > &items, bool use_label = true, size_t active = 0 ) {
		m_file_id   = file_id;
		m_use_label = use_label;

		if( m_use_label )
			m_label = label;

		m_offset = m_use_label ? 15 : 0;
		m_base_h = m_h = m_offset + DROPDOWN_BOX_HEIGHT;

		for( const auto& i : items )
			m_items.push_back( i );

		select( active );
	}

	// get index of active item.
	__forceinline size_t get( ) {
		return m_active_item;
	}

	__forceinline void select( size_t idx ) {
		if( idx < m_items.size( ) )
			m_active_item = idx;
	}

	__forceinline void set( size_t idx ) {
		bool changed = m_active_item != idx;

		m_active_item = idx;

		if( changed && m_callback )
			m_callback( );
	}

	// get name of active item.
	__forceinline std::string GetActiveItem( ) {
		// check bounds
		if( m_active_item < m_items.size( ) )
			return m_items[ m_active_item ];

		// happens sometimes with outdated configs
		// i.e items removed.
		return XOR( "error" );
	}

protected:
	bool					   m_open;
	std::string				   m_label;
	std::vector< std::string > m_items;
	float					   m_anim_height;
	size_t					   m_active_item;
	int						   m_offset;

private:
	__forceinline void arrow1( Point p );
	__forceinline void arrow2( Point p );

protected:
	void draw( ) override;
	void think( ) override;
	void click( ) override;
};