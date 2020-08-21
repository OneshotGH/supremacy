#pragma once

enum CSRoundEndReason {
	UNKNOWN1 = 0,
	BOMB_DETONATED,			// terrorists planted bomb and it detonated.
	UNKNOWN2,
	UNKNOWN3,
	T_ESCAPED,				// dunno if used.
	CT_STOPPED_ESCAPE,		// dunno if used.
	T_STOPPED,				// dunno if used
	BOMB_DEFUSED,			// counter-terrorists defused the bomb.
	CT_WIN,					// counter-terrorists killed all terrorists.
	T_WIN,					// terrorists killed all counter-terrorists.
	ROUND_DRAW,				// draw ( likely due to time ).
	HOSTAGE_RESCUED,		// counter-terrorists rescued a hostage.
	CT_WIN_TIME,
	T_WIN_TIME,
	T_NOT_ESACPED,
	UNKNOWN4,
	GAME_START,
	T_SURRENDER,
	CT_SURRENDER,
};


class CKeyValuesSystem {
public:
	virtual void		RegisterSizeofKeyValues( int size ) = 0;
	virtual void*		AllocKeyValuesMemory( int size ) = 0;
	virtual void		FreeKeyValuesMemory( void *pMem ) = 0;
	virtual int			GetSymbolForString( const char *name, bool bCreate = true ) = 0;
	virtual const char*	GetStringForSymbol( int symbol ) = 0;
	virtual void		AddKeyValuesToMemoryLeakList( void *pMem, int name ) = 0;
	virtual void		RemoveKeyValuesFromMemoryLeakList( void *pMem ) = 0;

	template< typename T = CKeyValuesSystem* >
	static __forceinline T KeyValuesSystem( ) {
		static auto KeyValuesFactory = PE::GetExport( PE::GetModule( HASH( "vstdlib.dll" ) ), HASH( "KeyValuesSystem" ) );
		return KeyValuesFactory.as< T( *)( ) >( )( );
	}
};

class KeyValues {
protected:
	enum types_t {
		TYPE_NONE = 0,
		TYPE_STRING,
		TYPE_INT,
		TYPE_FLOAT,
		TYPE_PTR,
		TYPE_WSTRING,
		TYPE_COLOR,
		TYPE_UINT64,
		TYPE_NUMTYPES,
	};

public:
	__forceinline KeyValues* FindKey( hash32_t hash ) {
		KeyValues        *dat;
		CKeyValuesSystem *system;
		const char       *string;

		system = CKeyValuesSystem::KeyValuesSystem( );

		if( !this || !hash || !system )
			return nullptr;

		for( dat = this->m_sub; dat != nullptr; dat = dat->m_peer ) {
			string = system->GetStringForSymbol( dat->m_key_name_id );

			if( string && FNV1a::get( string ) == hash )
				return dat;
		}

		return nullptr;
	}

	int __forceinline GetInt( int default_value = 0 ) {
		int result{};

		switch( this->m_data_type ) {
		case TYPE_STRING:
			result = atoi( this->m_string );
			break;
		case TYPE_WSTRING:
			result = _wtoi( this->m_wide_string );
			break;
		case TYPE_FLOAT:
			result = ( signed int )floor( this->m_float_value );
			break;
		case TYPE_UINT64:
			result = 0;
			break;
		default:
			result = this->m_int_value;
			break;
		}

		return( result ? result : default_value );
	}

	bool __forceinline GetBool( ) {
		return !!GetInt( );
	}

	float __forceinline GetFloat( float default_value = 0.f ) {
		switch( this->m_data_type ) {
		case TYPE_STRING:
			return ( float )atof( this->m_string );
		case TYPE_WSTRING:
			return ( float )_wtof( this->m_wide_string );
		case TYPE_FLOAT:
			return this->m_float_value;
		case TYPE_INT:
			return ( float )this->m_int_value;
		case TYPE_UINT64:
			return ( float )( *( ( uint64_t * )this->m_string ) );
		case TYPE_PTR:
		default:
			return 0.0f;
		};
	}

	uint32_t m_key_name_id : 24;
	uint32_t m_key_name_case_sensitive : 8;

	char    *m_string;
	wchar_t *m_wide_string;

	union {
		int           m_int_value;
		float         m_float_value;
		void         *m_ptr_value;
		unsigned char m_color_value[ 4 ];
	};

	char m_data_type;
	char m_has_escape_sequences;

	PAD( 0x2 );

	KeyValues *m_peer;
	KeyValues *m_sub;
	KeyValues *m_chain;
};

class CGameEventCallback {
public:
	void *m_callback;
	int   m_listener_type;
};

class CGameEventDescriptor {
public:
	char							  m_name[ 32 ];
	int								  m_id;
	KeyValues						 *m_keys;
	bool							  m_is_local;
	bool							  m_is_reliable;
	CUtlVector< CGameEventCallback* > m_listeners;
};

class IGameEvent {
public:
	CGameEventDescriptor *m_descriptor;
	KeyValues			 *m_keys;

	virtual ~IGameEvent( ) {};
	virtual const char *GetName( ) const = 0;
	virtual bool IsReliable( ) const = 0;
	virtual bool IsLocal( ) const = 0;
	virtual bool IsEmpty( const char *keyName = nullptr ) = 0;
	virtual bool GetBool( const char *keyName = nullptr, bool defaultValue = false ) = 0;
	virtual int GetInt( const char *keyName = nullptr, int defaultValue = 0 ) = 0;
	virtual unsigned long long GetUint64( char const *keyName = nullptr, unsigned long long defaultValue = 0 ) = 0;
	virtual float GetFloat( const char *keyName = nullptr, float defaultValue = 0.0f ) = 0;
	virtual const char *GetString( const char *keyName = nullptr, const char *defaultValue = "" ) = 0;
	virtual const wchar_t *GetWString( char const *keyName = nullptr, const wchar_t *defaultValue = L"" ) = 0;
	virtual void SetBool( const char *keyName, bool value ) = 0;
	virtual void SetInt( const char *keyName, int value ) = 0;
	virtual void SetUInt64( const char *keyName, unsigned long long value ) = 0;
	virtual void SetFloat( const char *keyName, float value ) = 0;
	virtual void SetString( const char *keyName, const char *value ) = 0;
	virtual void SetWString( const char *keyName, const wchar_t *value ) = 0;
};

class IGameEventListener2 {
public:
	virtual	~IGameEventListener2( void ) {};
	virtual void FireGameEvent( IGameEvent *event ) = 0;
	virtual int GetEventDebugID( void ) {
		return m_debug_id;
	}
public:
	int	m_debug_id;
};

class IGameEventManager2 {
public:
	CUtlVector< CGameEventDescriptor > m_events;
	CUtlVector< CGameEventCallback* >  m_listeners;

	virtual	~IGameEventManager2( void ) {};
	virtual int LoadEventsFromFile( const char *filename ) = 0;
	virtual void Reset( ) = 0;
	virtual bool AddListener( IGameEventListener2 *listener, const char *name, bool bServerSide ) = 0;
	virtual bool FindListener( IGameEventListener2 *listener, const char *name ) = 0;
	virtual void RemoveListener( IGameEventListener2 *listener ) = 0;

	/*bool __forceinline add_listener_internal( IGameEventListener2 *listener, CGameEventDescriptor *descriptor, bool serverside ) {
		// char __thiscall CGameEventManager::AddListener_Internal( void *this, int listener, int a3, bool serverside )
		// 55 8B EC 83 EC 08 8B C1 56 57

		// return GameEventManager::AddListener_Internal( this, listener, descriptor, serverside == false );
	}

	bool __forceinline add_listener_by_hash( IGameEventListener2 *listener, hash_t hash, bool serverside ) {
		CGameEventDescriptor *descriptor;

		for( int i{}; i < m_events.count( ); i++ ) {
			descriptor = &m_events.element( i );

			if( !descriptor )
				continue;

			if( hash::fnv1a( descriptor->m_name ) == hash )
				break;

			else
				descriptor = nullptr;
		}

		if( !descriptor )
			return false;

		return add_listener_internal( listener, descriptor, serverside );
	}*/
};