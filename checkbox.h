#pragma once

#define CHECKBOX_SIZE 8

class Checkbox : public Element {
public:
	// ctor.
	__forceinline Checkbox( ) : m_checked{ false }, m_label{} {
		m_flags     = ElementFlags::CLICK | ElementFlags::DRAW | ElementFlags::SAVE;
		m_w         = m_h = m_base_h = CHECKBOX_SIZE;
		m_type      = ElementTypes::CHECKBOX;
		m_use_label = true;
		m_show      = true;
	}

	__forceinline void setup( const std::string &label, const std::string &file_id, bool use_label = true, bool default = false ) {
		m_file_id   = file_id;
		m_use_label = use_label;

		if( m_use_label )
			m_label = label;

		m_checked = default;
	}

	__forceinline void set( bool checked ) {
		bool changed = m_checked != checked;

		m_checked = checked;

		if( changed && m_callback )
			m_callback( );
	}

	__forceinline bool get( ) {
		return m_checked;
	}

protected:
	bool		m_checked;
	std::string m_label;

protected:
	void draw( ) override;
	void think( ) override;
	void click( ) override;
};