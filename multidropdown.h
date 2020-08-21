#pragma once

class MultiDropdown : public Element {
public:
	__forceinline MultiDropdown( ) : m_open{ false }, m_label{}, m_anim_height{}, m_active_items{}, m_offset{} {
		m_flags = ElementFlags::DRAW | ElementFlags::CLICK | ElementFlags::ACTIVE | ElementFlags::SAVE;
		m_type  = ElementTypes::MULTI_DROPDOWN;
		m_show  = true;
	}

	__forceinline void setup( const std::string &label, const std::string &file_id, const std::vector< std::string > &items, bool use_label = true, std::vector< size_t > active = {} ) {
		m_file_id = file_id;
		m_use_label = use_label;

		if( m_use_label )
			m_label = label;

		m_offset = m_use_label ? 15 : 0;
		m_base_h = m_h = m_offset + DROPDOWN_BOX_HEIGHT;

		for( const auto& i : items )
			m_items.push_back( i );

		for( const auto& a : active )
			select( a );
	}

	__forceinline bool get( size_t index ) {
		return std::find( m_active_items.begin( ), m_active_items.end( ), index ) != m_active_items.end( );
	}

	__forceinline std::vector< std::string > GetActiveItems( ) {
		std::vector< std::string > out{};
	
		// iterate active items and store in
		for( const auto& i : m_active_items )
			out.push_back( m_items[ i ] );
	
		return out;
	}

	__forceinline void select( size_t idx ) {
		bool changed = std::find( m_active_items.begin( ), m_active_items.end( ), idx ) == m_active_items.end( );

		if( idx < m_items.size( ) )
			m_active_items.push_back( idx );

		if( changed && m_callback )
			m_callback( );
	}

	__forceinline void clear( ) {
		m_active_items.clear( );
	}

	__forceinline bool empty( ) {
		return m_active_items.empty( );
	}

	__forceinline std::vector< size_t > GetActiveIndices( ) const {
		return m_active_items;
	}

protected:
	bool				       m_open;
	std::string				   m_label;
	std::vector< std::string > m_items;
	float					   m_anim_height;
	std::vector< size_t >	   m_active_items;
	int						   m_offset;

private:
	__forceinline void arrow1( Point p );
	__forceinline void arrow2( Point p );

protected:
	void draw( ) override;
	void think( ) override;
	void click( ) override;
};