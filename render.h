#pragma once

struct Point {
	int x;
	int y;
};

struct Rect {
	int x;
	int y;
	int w;
	int h;
};

namespace render {
	struct FontSize_t {
		int m_width;
		int m_height;
	};

	enum StringFlags_t {
		ALIGN_LEFT = 0,
		ALIGN_RIGHT,
		ALIGN_CENTER
	};

	class Font {
	public:
		HFont      m_handle;
		FontSize_t m_size;

	public:
		__forceinline Font( ) : m_handle{}, m_size{} {};

		// ctor.
		__forceinline Font( const std::string& name, int s, int w, int flags ) {
			m_handle = g_csgo.m_surface->CreateFont( );
			g_csgo.m_surface->SetFontGlyphSet( m_handle, name.data( ), s, w, 0, 0, flags );
			m_size = size( XOR( "A" ) );
		}

		// ctor.
		__forceinline Font( HFont font ) {
			m_handle = font;
			m_size = size( XOR( "A" ) );
		}

		void string( int x, int y, Color color, const std::string& text, StringFlags_t flags = ALIGN_LEFT );
		void string( int x, int y, Color color, const std::stringstream& text, StringFlags_t flags = ALIGN_LEFT );
		void wstring( int x, int y, Color color, const std::wstring& text, StringFlags_t flags = ALIGN_LEFT );
		render::FontSize_t size( const std::string& text );
		FontSize_t wsize( const std::wstring& text );
	};

	extern Font menu;
	extern Font menu_shade;
	extern Font esp;
	extern Font esp_small;
	extern Font hud;
	extern Font cs;
	extern Font indicator;

	void init( );
	bool WorldToScreen( const vec3_t& world, vec2_t& screen );
	void line( vec2_t v0, vec2_t v1, Color color );
	void line( int x0, int y0, int x1, int y1, Color color );
	void rect( int x, int y, int w, int h, Color color );
	void rect_filled( int x, int y, int w, int h, Color color );
	void rect_filled_fade( int x, int y, int w, int h, Color color, int a1, int a2 );
	void rect_outlined( int x, int y, int w, int h, Color color, Color color2 );
	void circle( int x, int y, int radius, int segments, Color color );
	void gradient( int x, int y, int w, int h, Color color1, Color color2 );
	void sphere( vec3_t origin, float radius, float angle, float scale, Color color );
	Vertex RotateVertex( const vec2_t& p, const Vertex& v, float angle );
}

// nitro du hurensohn