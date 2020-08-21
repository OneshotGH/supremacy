#pragma once

class Interfaces {
private:
	// used internally to register classes.
	class InterfaceReg {
	private:
		using create_t = void*( __cdecl * )( );

	public:
		create_t        m_create_fn;
		const char      *m_name;
		InterfaceReg    *m_next;
	};

	struct interface_t {
		std::string m_name;
		Address     m_ptr;
	};

	// holds every interface used by the game.
	std::vector< interface_t > m_interfaces;

public:
	// ctor.
    __forceinline Interfaces( ) : m_interfaces{} {
		PE::modules_t modules;
		Address       ci;
		InterfaceReg  *reg;

		if( !PE::GetAllModules( modules ) )
			return;

		for( const auto &m : modules ) {
			// get CreateInterface export.
			ci = PE::GetExport( m, HASH( "CreateInterface" ) );
			if( !Address::valid( ci ) )
				continue;

			// there is a jump to the real CreateInterface function.
			if( ci.at< uint8_t >( 0x4 ) == 0xe9 ) {
				// displaced jump - take it
				ci = ci.rel32( 0x5 );

				// we are now in the true CreateInterface function.

				// check for ESI register at 5th instruction
				// ptr to linked list is after the MOV ESI instruction.
				if( ci.at< uint8_t >( 0x5 ) == 0x35 ) {

					// get ptr to linked list.
					reg = ci.add( 0x6 ).get< InterfaceReg* >( 2 );

					// iterate list.
					CreateEntries( reg );
				}
			}

			// check for ESI register at 2nd instruction
			// ptr to linked list is after the MOV ESI instruction.
			else if( ci.at< uint8_t >( 0x2 ) == 0x35 ) {

				// get ptr to linked list.
				reg = ci.add( 0x3 ).get< InterfaceReg* >( 2 );

				// iterate list.
				CreateEntries( reg );
			}
		}
	}

	__forceinline void CreateEntries( InterfaceReg* list ) {
		// iterate single linked list.
		for( list; list != nullptr; list = list->m_next ) {
			// invalid name.
			if( !list->m_name )
				continue;

			// add to vector.
			m_interfaces.push_back( { list->m_name, ( uintptr_t )list->m_create_fn( ) } );
		}
	}

	// get interface.
	template< typename t = Address > 
	__declspec( noinline ) t get( const hash32_t name, size_t skip = 0, bool truncate = true ) {
		std::string interface_name;

		for( const auto &i : m_interfaces ) {
			// make a copy of the interface's name.
			interface_name = i.m_name;

			// truncate version number.
			if( truncate )
				interface_name.resize( interface_name.size( ) - 3 );

			// compare hash.
			if( FNV1a::get( interface_name ) == name ) {
				// skip this interface if a newer one is available.
				if( skip > 0 ) {
					--skip;
					continue;
				}

				return i.m_ptr.as< t >( );
			}
		}

		return t{};
	}
};