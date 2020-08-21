#pragma once

// warning C4172: returning address of local variable or temporary
// potential pointer dangling? seems fine for now.
#pragma warning( disable : 4172 )  

// generate 'pseudo-random' xor key based on file, date and line.
#define GET_XOR_KEYUI8  ( ( CONST_HASH( __FILE__ __TIMESTAMP__ ) + __LINE__ ) % UINT8_MAX )
#define GET_XOR_KEYUI16 ( ( CONST_HASH( __FILE__ __TIMESTAMP__ ) + __LINE__ ) % UINT16_MAX )
#define GET_XOR_KEYUI32 ( ( CONST_HASH( __FILE__ __TIMESTAMP__ ) + __LINE__ ) % UINT32_MAX )

namespace xor{
	// actual xor implementation.
	template< class t, const size_t len, const t key >
	class Gen {
	private:
		std::array< t, len > m_buffer;

	private:
		// encrypt single character.
		constexpr t enc(const t c) const noexcept {
			return c ^ key;
		}

		// decrypt single character.
		__forceinline t dec(const t c) const noexcept {
			return c ^ key;
		}

	public:
		// iterate each byte and decrypt.
		__forceinline auto data() noexcept {
			for (size_t i{ 0u }; i < len; ++i)
				m_buffer[i] = dec(m_buffer[i]);

			return m_buffer.data();
		}

		// ctor.
		template< size_t... seq >
		constexpr __forceinline Gen(const t(&s)[len], std::index_sequence< seq... >) noexcept : m_buffer{ enc(s[seq])... } {}
	};
}

// todo - dex;  the issue with this code is that the xor key will be static since it's in the actual function call
//              the macro needs to pass a key instead using __COUNTER__ or __LINE__ as the first template arg, the rest will be handled by the compiler (like size).
//              sadly, this increasess compile time by a fuck ton.

template< class t, const size_t len >
constexpr __forceinline auto XorStr(const t(&s)[len]) {
	return xor ::Gen< t, len, GET_XOR_KEYUI8 >(s, std::make_index_sequence< len >()).data();
}

#ifdef _DEBUG
#define XOR( s ) ( s )
#else
#define XOR( s ) ( XorStr( s ) )
#endif