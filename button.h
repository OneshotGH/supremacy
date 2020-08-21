#pragma once

#define BUTTON_X_OFFSET      20
#define BUTTON_BOX_HEIGHT    20
#define BUTTON_ITEM_X_OFFSET 10

class Button : public Element {
	friend class GUI;

public:
	__forceinline Button( ) : m_label{} {
		m_flags     = ElementFlags::DRAW | ElementFlags::CLICK;
		m_type      = ElementTypes::BUTTON;
		m_base_h    = m_h = BUTTON_BOX_HEIGHT;
		m_use_label = false;
	}

	__forceinline void setup( const std::string& label ) {
		m_label = label;
	}

protected:
	std::string m_label;

protected:
	void draw( ) override;
	void think( ) override;
	void click( ) override;
};