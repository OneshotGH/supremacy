#pragma once

#define SLIDER_X_OFFSET 20
#define SLIDER_HEIGHT	8

class Slider : public Element {
public:
	__forceinline Slider( ) : m_drag{ false }, m_value{}, m_min{}, m_max{}, m_step{}, m_fill{}, m_precision{}, m_label{}, m_suffix{}, m_offset{} {
		m_flags = ElementFlags::DRAW | ElementFlags::CLICK | ElementFlags::SAVE;
		m_type  = ElementTypes::SLIDER;
		m_show  = true;
	}

	__forceinline void setup( const std::string &label, const std::string &file_id, float min, float max, 
							  bool use_label = true, int precision = 0, float value = 0.f, float step = 1.f, const std::wstring &suffix = L"" ) {
		m_file_id   = file_id;
		m_use_label = use_label;

		if( m_use_label )
			m_label = label;

		m_offset    = m_use_label ? 15 : 0;
		m_h         = m_offset + SLIDER_HEIGHT;
		m_base_h    = m_h;
		m_min       = min;
		m_max       = max;
		m_value     = value;
		m_precision = precision;
		m_step      = step;
		m_suffix    = suffix;
	}

	__forceinline void set( float value ) {
		bool changed = value != m_value;

		// set new value
		m_value = value;

		// clamp the value.
		math::clamp( m_value, m_min, m_max );

		if( changed && m_callback )
			m_callback( );
	}

	__forceinline float get( ) {
		return m_value;
	}

protected:
	bool	     m_drag;
	float	     m_value;
	float	     m_min;
	float	     m_max;
	float	     m_step;
	int		     m_fill;
	int		     m_precision;
	std::string  m_label;
	std::wstring m_suffix;
	int          m_offset;

protected:
	void draw( ) override;
	void think( ) override;
	void click( ) override;
};