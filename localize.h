#pragma once

class C_EconItemView {
public:
};

class CEconItemSchema {
public:
};

class CEconItemDefinition {
public:
	__forceinline const char* GetItemBaseName( ) {
		return util::get_method< const char*( __thiscall* )( void* ) >( this, 2 )( this );
	}
};

class ILocalize {
public:
	__forceinline const wchar_t* Find( const char* token ) {
		return util::get_method< const wchar_t*( __thiscall* )( void*, const char* ) >( this, 12 )( this, token );
	}
};