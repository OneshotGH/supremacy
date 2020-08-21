#pragma once

// pre-declares.
class Element;
class Tab;
class Form;

enum ElementFlags : size_t {
	NONE      = 0 << 0,
	DRAW      = 1 << 0,
	CLICK     = 1 << 1,
	ACTIVE    = 1 << 2,
	SAVE      = 1 << 3,
	DEACIVATE = 1 << 4,
};

enum ElementTypes : size_t {
	CHECKBOX = 1,
	SLIDER,
	KEYBIND,
	DROPDOWN,
	COLORPICKER,
	MULTI_DROPDOWN,
	EDIT,
	BUTTON,
	CUSTOM
};

using ToggleCallback_t = void( *)( );

#define LABEL_OFFSET 20

class Element {
	friend class GUI;
	friend class Tab;
	friend class Form;
	friend class Config;

protected:
	using ShowCallback_t = bool( *)( );
	using Callback_t = void( *)( );

protected:
	Point                         m_pos;
	int                           m_w;
	int                           m_h;
	int                           m_base_h;
	size_t                        m_col;
	Form*                         m_parent;
	std::string                   m_label;
	std::string                   m_file_id;
	size_t                        m_flags;
	size_t                        m_type;
	std::vector< ShowCallback_t > m_show_callbacks;
	Callback_t                    m_callback;
	bool			              m_show;
	bool                          m_use_label;

public:
	__forceinline Element( ) : m_pos{}, m_w{}, m_h{}, m_base_h{}, m_parent{ nullptr },
		m_label{}, m_file_id{}, m_flags{}, m_type{}, m_use_label{},
		m_show_callbacks{}, m_callback{}, m_show{} {}

	__forceinline void setup( const std::string &label, const std::string &file_id ) {
		m_label   = label;
		m_file_id = file_id;
	}

	__forceinline void AddFlags( size_t flags ) {
		m_flags |= flags;
	}

	__forceinline void RemoveFlags( size_t flags ) {
		m_flags &= ~flags;
	}

	__forceinline void AddShowCallback( ShowCallback_t scb ) {
		m_show_callbacks.push_back( scb );
	}

	__forceinline void SetCallback( Callback_t cb ) {
		m_callback = cb;
	}

	__forceinline void SetPosition( int x, int y ) {
		m_pos.x = x;
		m_pos.y = y;
	}

protected:
	virtual void draw( )  {};
	virtual void think( ) {};
	virtual void click( ) {};
};