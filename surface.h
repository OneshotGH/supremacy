#pragma once
#undef CreateFont

using HFont  = ulong_t;
using VPANEL = ulong_t;

enum FontDrawType_t {
	FONT_DRAW_DEFAULT = 0,
	FONT_DRAW_NONADDITIVE,
	FONT_DRAW_ADDITIVE
};

enum EFontFlags : int {
	FONTFLAG_NONE         = 0,
	FONTFLAG_ITALIC       = ( 1 << 0 ),
	FONTFLAG_UNDERLINE    = ( 1 << 1 ),
	FONTFLAG_STRIKEOUT    = ( 1 << 2 ),
	FONTFLAG_SYMBOL       = ( 1 << 3 ),
	FONTFLAG_ANTIALIAS    = ( 1 << 4 ),
	FONTFLAG_GAUSSIANBLUR = ( 1 << 5 ),
	FONTFLAG_ROTARY       = ( 1 << 6 ),
	FONTFLAG_DROPSHADOW   = ( 1 << 7 ),
	FONTFLAG_ADDITIVE     = ( 1 << 8 ),
	FONTFLAG_OUTLINE      = ( 1 << 9 ),
	FONTFLAG_CUSTOM       = ( 1 << 10 ),
	FONTFLAG_BITMAP       = ( 1 << 11 )
};

enum VGuiPanel_t {
	PANEL_ROOT = 0, // buy menu problems
	PANEL_GAMEUIDLL, // only called in main menu
	PANEL_CLIENTDLL, // only called ingame
	PANEL_TOOLS, // perfect
	PANEL_INGAMESCREENS,
	PANEL_GAMEDLL,
	PANEL_CLIENTDLL_TOOLS
};

class IEngineVGui {
public:
	virtual	~IEngineVGui( void ) {}
	virtual uint32_t GetPanel( VGuiPanel_t type ) = 0;
	virtual bool IsGameUIVisible( ) = 0;
};

class IPanel {
public:
	enum indices : size_t {
		GETNAME       = 36,
		PAINTTRAVERSE = 41,
	};

public:
	__forceinline const char* GetName( VPANEL vgui_panel ) {
		return util::get_method< const char*( __thiscall* )( decltype( this ), uint32_t ) >( this, GETNAME )( this, vgui_panel );
	}
};

class Vertex {
public:
	vec2_t m_pos;
	vec2_t m_coord;

public:
	__forceinline Vertex( ) {}

    __forceinline Vertex( float x, float y ) : m_pos{ x, y }, m_coord{ 0.f, 0.f } {}
    __forceinline Vertex( const vec2_t& pos ) : m_pos{ pos }, m_coord{ 0.f, 0.f } {}
    __forceinline Vertex( const vec2_t& pos, const vec2_t& coord ) : m_pos{ pos }, m_coord{ coord } {}

	__forceinline void init( const vec2_t& pos, const vec2_t &coord = { 0, 0 } ) {
        m_pos   = pos;
        m_coord = coord;
	}
};

class CRender {
public:
};

class ISurface {
public:
	enum indices : size_t {
		DRAWSETCOLOR        = 14,
		DRAWFILLEDRECT      = 16,
		DRAWOUTLINEDRECT    = 18,
		DRAWLINE            = 19,
		DRAWSETTEXTFONT     = 23,
		DRAWSETTEXTCOLOR    = 24,
		DRAWSETTEXTPOS      = 26,
		DRAWPRINTTEXT       = 28,
		DRAWUNICODECHAR     = 29,
		DRAWSETTEXTURERGBA  = 37,
		DRAWSETTEXTURE      = 38,
		DRAWTEXTUREDRECT    = 41,
		CREATENEWTEXTUREID  = 43,
		GETSCREENSIZE		= 44,
		UNLOCKCURSOR		= 66,
		LOCKCURSOR			= 67,
		CREATEFONT          = 71,
		SETFONTGLYPHSET     = 72,
		GETTEXTSIZE         = 79,
		PLAYSOUND           = 82,
		DRAWOUTLINEDCIRCLE  = 103,
		DRAWTEXTURDPOLYLINE = 104,
		DRAWTEXTUREDPOLYGON = 106,
		ONSCREENSIZECHANGED = 116,
		DRAWFILLEDRECTFADE  = 123,
		DRAWCOLOREDCIRCLE	= 162,
	};
public:

	__forceinline void DrawSetColor( Color col ) {
		return util::get_method< void( __thiscall* )( decltype( this ), Color ) >( this, DRAWSETCOLOR )( this, col );
	}

	__forceinline void DrawFilledRect( int x0, int y0, int x1, int y1 ) {
		return util::get_method< void( __thiscall* )( decltype( this ), int, int, int, int ) >( this, DRAWFILLEDRECT )( this, x0, y0, x1, y1 );
	}

	__forceinline void DrawOutlinedRect( int x, int y, int w, int h ) {
		return util::get_method< void( __thiscall* )( decltype( this ), int, int, int, int ) >( this, DRAWOUTLINEDRECT )( this, x, y, w, h );
	}

	__forceinline void DrawLine( int x0, int y0, int x1, int y1 ) {
		return util::get_method< void( __thiscall* )( decltype( this ), int, int, int, int ) >( this, DRAWLINE )( this, x0, y0, x1, y1 );
	}

	__forceinline void DrawSetTextFont( HFont font ) {
		return util::get_method< void( __thiscall* )( decltype( this ), HFont ) >( this, DRAWSETTEXTFONT )( this, font );
	}

	__forceinline void DrawSetTextColor( Color col ) {
		return util::get_method< void( __thiscall* )( decltype( this ), Color ) >( this, DRAWSETTEXTCOLOR )( this, col );
	}

	__forceinline void DrawSetTextPos( int x, int y ) {
		return util::get_method< void( __thiscall* )( decltype( this ), int, int ) >( this, DRAWSETTEXTPOS )( this, x, y );
	}

	__forceinline  void DrawPrintText( const wchar_t* text, int length, FontDrawType_t type = FONT_DRAW_DEFAULT ) {
		return util::get_method< void( __thiscall* )( decltype( this ), const wchar_t*, int, FontDrawType_t ) >( this, DRAWPRINTTEXT )( this, text, length, type );
	}

	__forceinline void DrawUnicodeChar( wchar_t wchar, FontDrawType_t type = FONT_DRAW_DEFAULT ) {
		return util::get_method< void( __thiscall* )( decltype( this ), wchar_t, FontDrawType_t ) >( this, DRAWUNICODECHAR )( this, wchar, type );
	}

	__forceinline void DrawSetTextureRGBA( int id, Color* rgba, int wide, int tall ) {
		return util::get_method< void( __thiscall* )( decltype( this ), int, Color*, int, int ) >( this, DRAWSETTEXTURERGBA )( this, id, rgba, wide, tall );
	}

	__forceinline void DrawSetTextureRGBA( int id, const uint8_t* rgba, int wide, int tall ) {
		return util::get_method< void( __thiscall* )( decltype( this ), int, const uint8_t*, int, int ) >( this, DRAWSETTEXTURERGBA )( this, id, rgba, wide, tall );
	}

	__forceinline void DrawSetTexture( int id ) {
		return util::get_method< void( __thiscall* )( decltype( this ), int ) >( this, DRAWSETTEXTURE )( this, id );
	}

	__forceinline void DrawTexturedRect( int x0, int y0, int x1, int y1 ) {
		return util::get_method< void( __thiscall * )( void*, int, int, int, int ) >( this, DRAWTEXTUREDRECT )( this, x0, y0, x1, y1 );
	}

	__forceinline int CreateNewTextureID( bool procedural = false ) {
		return util::get_method< int( __thiscall* )( decltype( this ), bool ) >( this, CREATENEWTEXTUREID )( this, procedural );
	}

	__forceinline void UnlockCursor( ) {
		return util::get_method< void( __thiscall* )( decltype( this ) )>( this, UNLOCKCURSOR )( this );
	}

	__forceinline HFont CreateFont( ) {
		return util::get_method< HFont( __thiscall* )( decltype( this ) )>( this, CREATEFONT )( this );
	}

	__forceinline  bool SetFontGlyphSet( HFont font, const char* windowsFontName, int tall, int weight, int blur, int scanlines, int flags, int range_min = 0, int range_max = 0 ) {
		return util::get_method< bool( __thiscall* )( decltype( this ), HFont, const char*, int, int, int, int, int, int, int ) >( this, SETFONTGLYPHSET )( this, font, windowsFontName, tall, weight, blur, scanlines, flags, range_min, range_max );
	}

	__forceinline void GetTextSize( HFont font, const wchar_t* text, int& wide, int& tall ) {
		return util::get_method < void( __thiscall* )( decltype( this ), HFont, const wchar_t*, int&, int& ) >( this, GETTEXTSIZE )( this, font, text, wide, tall );
	}

	__forceinline void PlaySound( const char* sample ) {
		return util::get_method<void( __thiscall* )( decltype( this ), const char* )>( this, PLAYSOUND )( this, sample );
	}

	__forceinline void DrawOutlinedCircle( int x, int y, int radius, int segments ) {
		return util::get_method< void( __thiscall* )( decltype( this ), int, int, int, int ) >( this, DRAWOUTLINEDCIRCLE )( this, x, y, radius, segments );
	}

	__forceinline void DrawFilledRectFade( int x0, int y0, int x1, int y1, uint32_t alpha0, uint32_t alpha1, bool bHorizontal ) {
		return util::get_method< void( __thiscall* )( decltype( this ), int, int, int, int, uint32_t, uint32_t, bool ) >( this, DRAWFILLEDRECTFADE )( this, x0, y0, x1, y1, alpha0, alpha1, bHorizontal );
	}

	__forceinline void DrawTexturedPolyLine( int count, Vertex* verts ) {
		return util::get_method< void( __thiscall* )( decltype( this ), Vertex*, int ) >( this, DRAWTEXTURDPOLYLINE )( this, verts, count );
	}

	__forceinline void DrawTexturedPolygon( int count, Vertex* verts, bool unk = false ) {
		return util::get_method< void( __thiscall* )( decltype( this ), int, Vertex*, bool ) >( this, DRAWTEXTUREDPOLYGON )( this, count, verts, unk );
	}

	__forceinline void DrawColoredCircle( int x, int y, float radius, int r, int g, int b, int a ) {
		return util::get_method< void( __thiscall* )( decltype( this ), int, int, float, int, int, int, int ) >( this, DRAWCOLOREDCIRCLE )( this, x, y, radius, r, g, b, a );
	}
};

class IVDebugOverlay {
public:
	// indexes for virtuals.
	enum indices : size_t {
		ADDBOXOVERLAY = 1,
		ADDLINEOVERLAY = 5,
		ADDTEXTOVERLAY = 7,
		ADDCAPSULEOVERLAY = 23
	};

	__forceinline void AddBoxOverlay( const vec3_t &origin, const vec3_t &mins, const vec3_t &maxs, const ang_t &angles, int r, int g, int b, int a, float duration ) {
		using AddBoxOverlay_t = void( __thiscall* )( void*, const vec3_t&, const vec3_t&, const vec3_t&, const ang_t&, int, int, int, int, float );
		util::get_method< AddBoxOverlay_t >( this, ADDBOXOVERLAY )( this, origin, mins, maxs, angles, r, g, b, a, duration );
	}

	__forceinline void AddLineOverlay( const vec3_t& origin, const vec3_t& dest, int r, int g, int b, bool noDepthTest, float duration ) {
		using AddLineOverlay_t = void( __thiscall* )( void*, const vec3_t&, const vec3_t&, int, int, int, bool, float );
		util::get_method< AddLineOverlay_t >( this, ADDLINEOVERLAY )( this, origin, dest, r, g, b, noDepthTest, duration );
	}

	__forceinline void AddTextOverlay( const vec3_t &origin, float duration, const char *fmt, ... ) {
		util::get_method< void( __thiscall* )( void*, const vec3_t&, float, const char* ) >( this, ADDTEXTOVERLAY )( this, origin, duration, fmt );
	}

	__forceinline void AddCapsuleOverlay( const vec3_t &mins, const vec3_t &maxs, float pillradius, int r, int g, int b, int a, float duration, int unk, int occlude ) {
		using AddCapsuleOverlay_t = void( __thiscall* )( void*, const vec3_t&, const vec3_t&, float &, int, int, int, int, float, int, int );
		util::get_method< AddCapsuleOverlay_t >( this, ADDCAPSULEOVERLAY )( this, mins, maxs, pillradius, r, g, b, a, duration, unk, occlude );
	}
};