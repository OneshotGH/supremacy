#pragma once

namespace stdpp {
	// unique_vector
	// goal; only unique elements in a vector while preserving original order
	// aka, no sort (looking at you std::set and std::unique)
	template< typename t >
	class unique_vector {
		using vec_type_t       = std::vector< t >;
		using const_iterator_t = typename vec_type_t::const_iterator;

	private:
		vec_type_t m_vector;

	public:
		// ctor.
		__forceinline unique_vector( ) : m_vector{} {}

		// hood boss ctor.
		__forceinline unique_vector( std::initializer_list< t > l ) : m_vector{} {
			// for all elements in the list, add them to our container.
			for( const auto& e : l )
				push_back( e );
		}

		// returns true if container contains element.
		__forceinline bool contains( const t& elem ) const {
			if( std::find( begin( ), end( ), elem ) != end( ) )
				return true;

			return false;
		}

		// adds element to tail of container, if not present yet.
		__forceinline void push_back( const t& elem ) {
			// check if element does not exist
			if( !contains( elem ) )
				m_vector.push_back( elem );
		}

		// wrappers.
		__forceinline const_iterator_t begin( ) const {
			return m_vector.begin( );
		}

		__forceinline const_iterator_t end( ) const {
			return m_vector.end( );
		}

		__forceinline void clear( ) {
			m_vector.clear( );
		}

		__forceinline bool empty( ) {
			return m_vector.empty( );
		}
	};
}