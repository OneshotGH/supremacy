#pragma once

enum {
	FCVAR_NONE                  = 0,
	FCVAR_UNREGISTERED          = ( 1 << 0 ),
	FCVAR_DEVELOPMENTONLY       = ( 1 << 1 ),
	FCVAR_GAMEDLL               = ( 1 << 2 ),
	FCVAR_CLIENTDLL             = ( 1 << 3 ),
	FCVAR_HIDDEN                = ( 1 << 4 ),
	FCVAR_PROTECTED             = ( 1 << 5 ),
	FCVAR_SPONLY                = ( 1 << 6 ),
	FCVAR_ARCHIVE               = ( 1 << 7 ),
	FCVAR_NOTIFY                = ( 1 << 8 ),
	FCVAR_USERINFO              = ( 1 << 9 ),
	FCVAR_CHEAT                 = ( 1 << 14 ),
	FCVAR_PRINTABLEONLY         = ( 1 << 10 ),
	FCVAR_UNLOGGED              = ( 1 << 11 ),
	FCVAR_NEVER_AS_STRING       = ( 1 << 12 ),
	FCVAR_REPLICATED            = ( 1 << 13 ),
	FCVAR_DEMO                  = ( 1 << 16 ),
	FCVAR_DONTRECORD            = ( 1 << 17 ),
	FCVAR_NOT_CONNECTED         = ( 1 << 22 ),
	FCVAR_ARCHIVE_XBOX          = ( 1 << 24 ),
	FCVAR_SERVER_CAN_EXECUTE    = ( 1 << 28 ),
	FCVAR_SERVER_CANNOT_QUERY   = ( 1 << 29 ),
	FCVAR_CLIENTCMD_CAN_EXECUTE = ( 1 << 30 )
};

// callback prototypes.
using ChangeCallbackV1_t = void( __cdecl* )( );
using ChangeCallback_t   = void( __cdecl* )( void* var, const char* old, float flold );

// do not use these, use the virtuals, please!
struct CVValue_t {
	char* m_string;
	int   m_str_len;
	float m_float;
	int   m_int;
};

class ConVar {
private:
	void* vtable; // 0x0000

public:
	ConVar*                          m_next; // 0x0004
	int                              m_registered; // 0x0008
	char*                            m_name;	// 0x000C
	char*                            m_help_string;// 0x0010
	int                              m_flags;// 0x0014
	ChangeCallbackV1_t				 m_callback;//0x0018
	ConVar*                          m_parent;
	char*                            m_default_value;
	CVValue_t                        m_value;
	int                              m_has_min;
	float                            m_min;
	int                              m_has_max;
	float                            m_max;
	CUtlVector< ChangeCallback_t >   m_callbacks;

public:
	enum indices : size_t {
		GETSTRING      = 11,
		GETFLOAT       = 12,
		GETINT         = 13,
		GETBOOL        = 13,
		SETVALUE_SZ    = 14,
		SETVALUE_FLOAT = 15,
		SETVALUE_INT   = 16,
	};

public:
	__forceinline const char* GetString( ) {
		return util::get_method< const char*( __thiscall* )( decltype( this ) ) >( this, GETSTRING )( this );
	}

	__forceinline float GetFloat( ) {
		return util::get_method< float( __thiscall* )( decltype( this ) ) >( this, GETFLOAT )( this );
	}

	__forceinline int GetInt( ) {
		return util::get_method< int( __thiscall* )( decltype( this ) ) >( this, GETINT )( this );
	}

	__forceinline void SetValue( const char* value ) {
		return util::get_method< void( __thiscall* )( decltype( this ), const char* ) >( this, SETVALUE_SZ )( this, value );
	}

	__forceinline void SetValue( float value ) {
		return util::get_method< void( __thiscall* )( decltype( this ), float ) >( this, SETVALUE_FLOAT )( this, value );
	}

	__forceinline void SetValue( int value ) {
		return util::get_method< void( __thiscall* )( decltype( this ), int ) >( this, SETVALUE_INT )( this, value );
	}
};

class ICvar {
public:
	enum indices {
		FINDVAR            = 14,
		CONSOLECOLORPRINTF = 25,
	};

	// note - dex; this used to be a virtual in old games but i can't find it anymore ( at least when i looked last time ).
	__forceinline ConVar* GetCommands( ) {
		return *( ConVar** )( ( uintptr_t )this + 0x30 );
	}

	// FindVar but iterates manually.
	__forceinline ConVar* FindVar( const hash32_t hash ) {
		ConVar *list;

		list = GetCommands( );
		if( !list )
			return nullptr;

		// iterate all convars.
		for( auto it = list; it != nullptr; it = it->m_next ) {
			// compare hash.
			if( FNV1a::get( it->m_name ) == hash ) 
                return it;
		}

		return nullptr;
	}

	template< typename... arguments >
	void ConsoleColorPrintf( const Color& color, const char* format, arguments ... args ) {
		return util::get_method< void( __cdecl* )( decltype( this ), const Color&, const char*, ... )>( this, CONSOLECOLORPRINTF )( this, color, format, args... );
	}
};