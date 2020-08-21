#pragma once

namespace syscall {
	// i mean how big are the tables going to get?
	constexpr size_t MAX_TABLE_SIZE = 0x100000;

	__forceinline size_t GetWrapperSize( uint8_t* funptr ) {
		// scan function.
		for( size_t i{}; i < 0x30; ++i ) {
			// end of function found.
			if( funptr[ i ] == x86::instruction::retn || funptr[ i ] == x86::instruction::retn_imm16 )
				return i + 1;
		}

		return 0;
	}

	__forceinline bool IsValid( uint8_t* func, size_t size ) {
		const uint32_t mov_eax_imm32 = x86::encode_mov_imm32( x86::reg::eax );

		// ntdll syscall exports always have a certain prologue (checked win7/10)
		// x86: mov eax, imm32
		// x64: mov r10, rcx
		if( func[ 0 ] != mov_eax_imm32 )
			return false;

		for( size_t i{}; i < size; ++i ) {

			// win7/win8.1
			if( func[ i ] == x86::instruction::fs && func[ i + 1 ] == x86::instruction::call )
				return true;

			// win10
			else if( func[ i ] == x86::instruction::call && func[ i + 1 ] == x86::encode_call_reg( x86::reg::edx ) )
				return true;
		}

		return false;
	}

	__forceinline uint16_t GetIndex( Address func, std::ptrdiff_t* offset = nullptr ) {
		size_t size = GetWrapperSize( func.as< uint8_t* >( ) );

		size = size ? size : 16;

		if( IsValid( func.as< uint8_t* >( ), size ) ) {
			// mov eax, imm32
			const uint32_t mov_eax_imm32 = x86::encode_mov_imm32( x86::reg::eax );

			for( size_t i{}; i < size; ++i ) {
				if( func.at< uint8_t >( i ) == mov_eax_imm32 ) {
					if( offset )
						*offset = i;

					return func.at< uint16_t >( i + 1 );
				}
			}
		}

		return 0;
	}

	struct stub_t {
		uint8_t* stub;
		size_t   size;
	};

	class Table {
	private:
		std::unordered_map< hash32_t, // hash of export name
							uint16_t  // syscall index
		     > m_syscalls;
		stub_t m_shellcode;
		void*  m_table;

	private:

		// dtor.
		__forceinline ~Table( ) {
			// free table memory.
			if( m_table )
				VirtualFree( m_table, MAX_TABLE_SIZE, MEM_FREE );

			// delete shellcode stub.
			if( m_shellcode.stub )
				delete[] m_shellcode.stub;
		}

		__forceinline Table( ) : m_syscalls{}, m_shellcode{}, m_table{} {
			// grab ntdll.
			PE::Module nt = PE::GetModule( HASH( "ntdll.dll" ) );

			// iterate all exports from ntdll.
			for( const auto& exp : PE::GetAllExports( nt ) ) {
				// get syscall index from exported function index.
				uint32_t index = GetIndex( exp.second );
				if( !index )
					continue;

				// in our syscall container
				// store the syscall index with the hash
				// of the export name as key.
				m_syscalls[ exp.first ] = index;

				// we have not generated our shellcode yet.
				if( !m_shellcode.stub ) {

					// get the stub size.
					m_shellcode.size = GetWrapperSize( exp.second.as< uint8_t* >( ) );

					// allocate memory for the stub.
					m_shellcode.stub = new uint8_t[ m_shellcode.size ];

					// copy function export sycall prologue.
					std::memcpy( m_shellcode.stub, exp.second.as< void* >( ), m_shellcode.size );
				}
			}

			// allocate memory table.
			m_table = VirtualAlloc( 0, MAX_TABLE_SIZE, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE );

			// fill table with useless opcodes
			std::memset( m_table, x86::instruction::nop, MAX_TABLE_SIZE );

			for( const auto& s : m_syscalls ) {
				// get syscall index.
				int16_t index = s.second;

				// find the location for this syscall index to copy the shellcode stub into our table.
				Address stub = ( uintptr_t( m_table ) + ( index * m_shellcode.size ) );

				// move the default shellcode.
				std::memcpy( stub, m_shellcode.stub, m_shellcode.size );

				// retrive the offset to where the index is located in the shellcode.
				std::ptrdiff_t offset{};
				GetIndex( stub, &offset );

				// end the stub with a return opcode.
				stub.add( m_shellcode.size - 1 ).set< uint8_t >( x86::instruction::retn );

				// write the syscall index to the stub.
				stub.add( offset + 1 ) = index;
			}
		}

		// get by hash with prototype.
		template< typename t = void* >
		__forceinline t GetSyscallFn( hash32_t hash ) {
			return ( t )( ( uintptr_t( m_table ) + ( GetSyscall( hash ) * m_shellcode.size ) ) );
		}

		// get by hash.
		__forceinline uint16_t GetSyscall( hash32_t hash ) {
			return m_syscalls[ hash ];
		}
	};
}

extern syscall::Table g_syscalls;