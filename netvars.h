#pragma once

class Netvars {
private:
	struct NetvarData {
		bool        m_datamap_var; // we can't do proxies on stuff from datamaps :).
		RecvProp    *m_prop_ptr;
		size_t      m_offset;

		__forceinline NetvarData( ) : m_datamap_var{}, m_prop_ptr{}, m_offset{} { }
	};

	std::unordered_map< hash32_t, int > m_client_ids;

	// netvar container.
	std::unordered_map< hash32_t,		// hash key + tables
		std::unordered_map< hash32_t,	// hash key + props
		NetvarData						// prop offset / prop ptr
		> > m_offsets;

public:
	// ctor.
    Netvars( ) : m_offsets{} {}

    void init( ) {
		ClientClass *list;

		// sanity check on client.
		if( !g_csgo.m_client )
			return;

		// grab linked list.
		list = g_csgo.m_client->GetAllClasses( );
		if( !list )
			return;

		// iterate list of netvars.
		for( ; list != nullptr; list = list->m_pNext )
			StoreDataTable( list->m_pRecvTable->m_pNetTableName, list->m_pRecvTable );

		// find all datamaps
		FindAndStoreDataMaps( );
	}

	// dtor.
    ~Netvars( ) {
		m_offsets.clear( );
	}

	// gather all classids dynamically on runtime.
    void SetupClassData( ) {
		ClientClass *list;

		// clear old shit.
		m_client_ids.clear( );

		// sanity check on client.
		if( !g_csgo.m_client )
			return;

		// grab linked list.
		list = g_csgo.m_client->GetAllClasses( );
		if( !list )
			return;

		// iterate list.
		for( ; list != nullptr; list = list->m_pNext )
			m_client_ids[ FNV1a::get( list->m_pNetworkName ) ] = list->m_ClassID;
	}

	void StoreDataTable( const std::string& name, RecvTable* table, size_t offset = 0 ) {
		hash32_t	var, base{ FNV1a::get( name ) };
		RecvProp*   prop;
		RecvTable*  child;

		// iterate props
		for( int i{}; i < table->m_nProps; ++i ) {
			prop = &table->m_pProps[ i ];
			child = prop->m_pDataTable;

			// we have a child table, that contains props.
			if( child && child->m_nProps > 0 )
				StoreDataTable( name, child, prop->m_Offset + offset );

			// hash var name.
			var = FNV1a::get( prop->m_pVarName );

			// insert if not present.
			if( !m_offsets[ base ][ var ].m_offset ) {
				m_offsets[ base ][ var ].m_datamap_var = false;
				m_offsets[ base ][ var ].m_prop_ptr    = prop;
				m_offsets[ base ][ var ].m_offset      = ( size_t )( prop->m_Offset + offset );
			}
		}
	}

	// iterate client module and find all datamaps.
	void FindAndStoreDataMaps( ) {
		pattern::patterns_t matches{};

		// sanity.
		if( !g_csgo.m_client_dll )
			return;

		matches = pattern::FindAll( g_csgo.m_client_dll, XOR( "C7 05 ? ? ? ? ? ? ? ? C7 05 ? ? ? ? ? ? ? ? C3 CC" ) );
		if( matches.empty( ) )
			return;

		for( auto& m : matches )
			StoreDataMap( m );
	}

	void StoreDataMap( Address ptr ) {
		datamap_t*          map;
		hash32_t            base, var;
		typedescription_t*  entry;

		// get datamap and verify.
		map = ptr.at( 2 ).sub( 4 ).as< datamap_t* >( );

		if( !map || !map->m_size || map->m_size > 200 || !map->m_desc || !map->m_name )
			return;

		// hash table name.
		base = FNV1a::get( map->m_name );

		for( int i{}; i < map->m_size; ++i ) {
			entry = &map->m_desc[ i ];
			if( !entry->m_name )
				continue;

			// hash var name.
			var = FNV1a::get( entry->m_name );

			// if we dont have this var stored yet.
			if( !m_offsets[ base ][ var ].m_offset ) {
				m_offsets[ base ][ var ].m_datamap_var = true;
				m_offsets[ base ][ var ].m_offset      = ( size_t )entry->m_offset[ TD_OFFSET_NORMAL ];
				m_offsets[ base ][ var ].m_prop_ptr    = nullptr;
			}
		}
	}

    // get client id.
	__forceinline int GetClientID( hash32_t network_name ) {
		return m_client_ids[ network_name ];
	}

	// get netvar offset.
	__forceinline size_t get( hash32_t table, hash32_t prop ) {
		return m_offsets[ table ][ prop ].m_offset;
	}

	// get netvar proxy.
	__forceinline RecvVarProxy_t GetProxy( hash32_t table, hash32_t prop, RecvVarProxy_t proxy ) {
		// todo - dex; should we return null here if m_is_valid_netvar is false? probably doesn't matter anyway.
		return m_offsets[ table ][ prop ].m_prop_ptr->m_ProxyFn;
	}

	// set netvar proxy.
	__forceinline void SetProxy( hash32_t table, hash32_t prop, void* proxy, RecvVarProxy_t &original ) {
		auto netvar_entry = m_offsets[ table ][ prop ];

		// we can't set a proxy on a datamap.
		if( netvar_entry.m_datamap_var )
			return;

        // save original.
		original = netvar_entry.m_prop_ptr->m_ProxyFn;

        // redirect.
		netvar_entry.m_prop_ptr->m_ProxyFn = ( RecvVarProxy_t )proxy;
	}
};

extern Netvars g_netvars;