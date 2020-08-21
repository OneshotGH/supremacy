#pragma once

#define EDIT_X_OFFSET	   20
#define EDIT_BOX_HEIGHT	   20
#define EDIT_ITEM_X_OFFSET 10

class Edit : public Element {
public:
	// ctor.
	__forceinline Edit( ) : m_text{}, m_limit{}, m_typing{ false }, m_old_typing{ false } {
		m_flags     = ElementFlags::CLICK | ElementFlags::DRAW | ElementFlags::SAVE | ElementFlags::ACTIVE;
		m_type      = ElementTypes::EDIT;
		m_use_label = true;
		m_show      = true;
	}

	__forceinline void setup( const std::string &label, const std::string &file_id, size_t limit = 3 ) {
		m_label   = label;
		m_file_id = file_id;
		m_limit   = limit;
		m_base_h  = m_h = 15 + EDIT_BOX_HEIGHT;
	}

	__forceinline int get( ) {
		if( m_text.empty( ) )
			return -1;

		return std::stoi( m_text );
	}

	__forceinline void set( int val ) {
		bool changed = val != get( );

		if( val == -1 )
			m_text.clear( );

		else
			m_text = std::to_string( val );

		if( changed && m_callback )
			m_callback( );
	}

protected:
	std::string m_text;
	size_t		m_limit;
	bool		m_typing;
	bool		m_old_typing;

protected:
	void draw( ) override;
	void think( ) override;
	void click( ) override;
};