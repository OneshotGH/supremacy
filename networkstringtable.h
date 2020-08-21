#pragma once

class INetworkStringTable {
public:
    enum indices : size_t {
        FINDTABLE = 3        
	};

    __forceinline int AddString( bool is_server, const char *value, int len = -1, const void *userdata = nullptr ) {
        return util::get_method< int (__thiscall *)( void *, bool, const char *, int, const void * ) >( this, 8 )( this, is_server, value, len, userdata );
    }
};

class INetworkStringTableContainer {
public:
    enum indices : size_t {
        FINDTABLE = 3        
	};

    __forceinline INetworkStringTable *FindTable( const char *table_name ) {
        return util::get_method< INetworkStringTable *(__thiscall *)( void *, const char * ) >( this, FINDTABLE )( this, table_name );
    }
};