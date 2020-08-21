#pragma once

class IMemAlloc {
public:
	__forceinline void* Alloc( size_t size ) {
		return util::get_method< void*( __thiscall* )( void*, size_t ) >( this, 1 )( this, size );
	}

	__forceinline void* Realloc( void* region, size_t size ) {
		return util::get_method< void*( __thiscall* )( void*, void*, size_t ) >( this, 3 )( this, region, size );
	}

	__forceinline void Free( void* region ) {
		return util::get_method< void( __thiscall* )( void*, void* ) >( this, 5 )( this, region );
	}
};