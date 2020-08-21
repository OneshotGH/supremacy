#pragma once

class VMT {
private:
	Address                      m_base;
	Address*                     m_old_vmt;
	std::unique_ptr< Address[] > m_new_vmt;
	size_t                       m_size;
	bool                         m_rtti;

private:
	__forceinline size_t count_methods( ) {
		size_t i{ 0u };

		while( Address::valid( m_old_vmt[ i ] ) )
			++i;

		return i;
	}

public:
	// default ctor.
	__forceinline VMT( ) : m_base{}, m_old_vmt{}, m_new_vmt{}, m_size{}, m_rtti{} {}

	// ctor.
	__forceinline VMT( Address base, bool rtti = true ) : m_base{}, m_old_vmt{}, m_new_vmt{}, m_size{}, m_rtti{} {
		init( base, rtti );
	}

	// dtor.
	__forceinline ~VMT( ) {
		//reset( );
	}

	// reset entire class.
	__forceinline void reset( ) {
		m_new_vmt.reset( );

		if( m_base )
			m_base.set( m_old_vmt );

		m_base = Address{};
		m_old_vmt = nullptr;
		m_size = 0;
		m_rtti = false;
	}

	// setup and replace vmt.
	__forceinline void init( Address base, bool rtti = true ) {
		// save base class.
		m_base = base;

		// get ptr to old VMT.
		m_old_vmt = base.to< Address* >( );
		if( !m_old_vmt )
			return;

		// count number of methods in old VMT.
		m_size = count_methods( );
		if( !m_size )
			return;

		// allocate new VMT.
		m_new_vmt = std::make_unique< Address[] >( rtti ? m_size + 1 : m_size );
		if( !m_new_vmt )
			return;

		// get raw memory ptr.
		Address vmt = ( uintptr_t )m_new_vmt.get( );

		if( rtti ) {
			// copy VMT, starting from RTTI.
			std::memcpy( vmt, m_old_vmt - 1, ( m_size + 1 ) * sizeof( Address ) );

			// VMTs are ( usually ) stored in the .data section we should be able to just overwrite it, so let's do that here.
			// also, since we've copied RTTI ptr then point the new table at index 1 ( index 0 contains RTTI ptr ).
			base.set( vmt + sizeof( Address ) );

			// we've sucesfully copied the RTTI ptr.
			m_rtti = true;
		}

		else {
			// copy vmt.
			std::memcpy( vmt, m_old_vmt, m_size * sizeof( Address ) );

			// since VMTs are ( usually ) stored in the .data section we should be able to just overwrite it, so let's do that here.
			base.set( vmt );
		}
	}

	template< typename t = Address >
	__forceinline t add( size_t index, void* function_ptr ) {
		size_t vmt_index{ m_rtti ? index + 1 : index };

		// sanity check some stuff first.
		if( !m_old_vmt || !m_new_vmt || vmt_index > m_size )
            return t{};

		// redirect.
		m_new_vmt[ vmt_index ] = ( uintptr_t )function_ptr;

		return m_old_vmt[ index ].as< t >( );
	}

	__forceinline bool remove( size_t index ) {
		size_t vmt_index{ m_rtti ? index + 1 : index };

		// sanity check some stuff first.
		if( !m_old_vmt || !m_new_vmt || vmt_index > m_size )
			return false;

		// redirect.
		m_new_vmt[ vmt_index ] = m_old_vmt[ index ];

		return true;
	}

	template< typename t = Address >
	__forceinline t GetOldMethod( size_t index ) {
		return m_old_vmt[ index ].as< t >( );
	}
};