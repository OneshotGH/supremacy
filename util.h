#pragma once

namespace util {
	__forceinline Address copy( Address dst, Address src, size_t size ) {
		__movsb(
			dst.as<uint8_t*>( ),
			src.as<uint8_t*>( ),
			size
		);

		return dst;
	}

	// memset
	__forceinline Address set( Address dst, uint8_t val, size_t size ) {
		__stosb(
			dst.as<uint8_t*>( ),
			val,
			size
		);

		return dst;
	}

	template< typename o = void*, typename i = void* >
	__forceinline o force_cast( i in ) {
		union { i in; o out; }
		u = { in };
		return u.out;
	};

	template < typename t = Address >
	__forceinline static t get_method( Address this_ptr, size_t index ) {
		return ( t )this_ptr.to< t* >( )[ index ];
	}

	// get base ptr ( EBP (x86_32) / RBP (x86_64) ).
	__forceinline uintptr_t GetBasePointer( ) {
		return ( uintptr_t )_AddressOfReturnAddress( ) - sizeof( uintptr_t );
	}

	// wide -> multi-byte
	__forceinline std::string WideToMultiByte( const std::wstring &str ) {
		std::string ret;
		int         str_len;

		// check if not empty str
		if( str.empty( ) )
			return {};

		// count size
		str_len = g_winapi.WideCharToMultiByte( CP_UTF8, 0, str.data( ), ( int )str.size( ), 0, 0, 0, 0 );

		// setup return value
		ret = std::string( str_len, 0 );

		// final conversion
		g_winapi.WideCharToMultiByte( CP_UTF8, 0, str.data( ), ( int )str.size( ), &ret[ 0 ], str_len, 0, 0 );

		return ret;
	}

	// multi-byte -> wide
	__forceinline std::wstring MultiByteToWide( const std::string &str ) {
		std::wstring    ret;
		int		        str_len;

		// check if not empty str
		if( str.empty( ) )
			return {};

		// count size
		str_len = g_winapi.MultiByteToWideChar( CP_UTF8, 0, str.data( ), ( int )str.size( ), nullptr, 0 );

		// setup return value
		ret = std::wstring( str_len, 0 );

		// final conversion
		g_winapi.MultiByteToWideChar( CP_UTF8, 0, str.data( ), ( int )str.size( ), &ret[ 0 ], str_len );

		return ret;
	}
};