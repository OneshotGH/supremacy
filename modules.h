#pragma once

namespace PE {
    class Module {
    private:
        LDR_DATA_TABLE_ENTRY *m_ldr_entry;
        IMAGE_DOS_HEADER     *m_dos;
        IMAGE_NT_HEADERS     *m_nt;

    public:
        __forceinline Module( ) :
            m_ldr_entry{ nullptr }, m_dos{ nullptr }, m_nt{ nullptr } {}

        __forceinline Module( LDR_DATA_TABLE_ENTRY *ldr_entry, IMAGE_DOS_HEADER *dos, IMAGE_NT_HEADERS *nt ) :
            m_ldr_entry{ ldr_entry }, m_dos{ dos }, m_nt{ nt } {}

        __forceinline Address GetBase( ) const {
            return ( m_ldr_entry ) ? Address( m_ldr_entry->DllBase ) : Address{};
        }

        // valid check.
        __forceinline operator bool( ) const {
            return GetBase( );
        }

        // valid check.
        __forceinline bool operator !( ) const {
            return !GetBase( );
        }

        __forceinline operator Address( ) const {
            return ( m_ldr_entry ) ? Address( m_ldr_entry->DllBase ) : Address{};
        }

        __forceinline IMAGE_DOS_HEADER *GetDOS( ) const {
            return ( m_dos ) ? m_dos : nullptr;
        }

        __forceinline IMAGE_NT_HEADERS *GetNT( ) const {
            return ( m_nt ) ? m_nt : nullptr;
        }

        __forceinline size_t GetCodeSize( ) const {
            return ( m_nt ) ? (size_t)m_nt->OptionalHeader.SizeOfCode : 0u;
        }

        __forceinline size_t GetImageSize( ) const {
            return ( m_nt ) ? (size_t)m_nt->OptionalHeader.SizeOfImage : 0u;
        }

        __forceinline std::string GetName( ) const {
            std::string     out;
            std::wstring    wide_name;

            if( !m_ldr_entry )
                return {};

            // get wide name.
            wide_name = std::wstring( m_ldr_entry->BaseDllName.Buffer, m_ldr_entry->BaseDllName.Length >> 1 );

            // truncate from a unicode string to a multi-byte string.
            out = std::string( wide_name.begin( ), wide_name.end( ) );

            // convert out name to lowercase.
            std::transform( out.begin( ), out.end( ), out.begin( ), ::tolower );

            return out;
        }
    };

    // container type for all modules / export / exports.
    using modules_t = std::vector< Module >;
	using export_t  = std::pair< hash32_t, Address >;
	using exports_t = std::vector< export_t >;

    // get DOS / NT headers from file.
    __forceinline bool GetFileHeaders( Address base, PIMAGE_DOS_HEADER &out_dos, PIMAGE_NT_HEADERS &out_nt ) {
        auto dos = base.as< IMAGE_DOS_HEADER * >( );
        
        // check for invalid DOS / DOS signature.
        if( !dos || dos->e_magic != IMAGE_DOS_SIGNATURE /* 'MZ' */ )
            return false;
        
        // get NT headers.
        auto nt = (IMAGE_NT_HEADERS *)( (uintptr_t)dos + dos->e_lfanew );
        
        // check for invalid NT / NT signature.
        if( !nt || nt->Signature != IMAGE_NT_SIGNATURE /* 'PE\0\0' */ )
            return false;
        
        // set out dos and nt.
        out_dos = dos;
        out_nt  = nt;
        
        return true;
    }

    // get all modules from PEB ldr.
    static __declspec( noinline ) bool GetAllModules( modules_t &out ) {
        _PEB                 *peb;
        LIST_ENTRY           *list;
        LDR_DATA_TABLE_ENTRY *ldr_entry;
        IMAGE_DOS_HEADER     *dos{ nullptr };
        IMAGE_NT_HEADERS     *nt{ nullptr };

        // TEB->ProcessEnvironmentBlock.
        peb = (_PEB *)__readfsdword( 0x30 );
        if( !peb )
            return false;

        // get module linked list.
        list = &peb->Ldr->InMemoryOrderModuleList;

        // iterate linked list.
        for( auto it = list->Flink; it != list; it = it->Flink ) {
            // get current entry.
            ldr_entry = CONTAINING_RECORD( it, LDR_DATA_TABLE_ENTRY, InMemoryOrderLinks );
            if( !ldr_entry )
                continue;

            // get file headers and ensure it's a valid PE file.
            if( !GetFileHeaders( ldr_entry->DllBase, dos, nt ) )
                continue;
            
            // push module to out vector.
            out.push_back( { ldr_entry, dos, nt } );
        }

        return !out.empty( );
    }

    // gets a module from PEB ldr using a string.
    static __declspec( noinline ) Module GetModule( std::string name ) {
        modules_t modules;
    
        // get all modules.
        if( !GetAllModules( modules ) )
            return {};

        // convert name to lower-case.
        std::transform( name.begin( ), name.end( ), name.begin( ), ::tolower );
    
        // iterate all modules.
        for( const auto &m : modules ) {
            // compare name.
            if( m.GetName( ) == name )
                return m;
        }
    
        return {};
    }

    // gets a module from PEB ldr using a hash.
    static __declspec( noinline ) Module GetModule( const hash32_t name ) {
        modules_t modules;

        // get all modules.
        if( !GetAllModules( modules ) )
            return {};

        // iterate all modules.
        for( const auto &m : modules ) {
            // compare name hash.
            if( FNV1a::get( m.GetName( ) ) == name )
                return m;
        }

        return {};
    }

    // fwd declare GetExport ( by string )...
    static __declspec( noinline ) Address GetExport( const Module &module, const std::string &name );

    // gets the address of an exported function in a module by hash.
    static __declspec( noinline ) Address GetExport( const Module &module, const hash32_t name ) {
        Address     export_ptr, fwd_export_ptr;
        size_t      delim;
        std::string export_name, fwd_str, fwd_module, fwd_export;

        if( !module )
            return {};

        auto nt   = module.GetNT( );
        auto base = module.GetBase( );
    
        // get export data directory.
        auto data_dir = &nt->OptionalHeader.DataDirectory[ IMAGE_DIRECTORY_ENTRY_EXPORT ];
        if( !data_dir->VirtualAddress )
            return {};

        // get export dir.
        auto dir = Address::RVA< IMAGE_EXPORT_DIRECTORY * >( base, data_dir->VirtualAddress );
        if( !dir )
            return {};

        // names / funcs / ordinals ( all of these are RVAs ).
        auto names = Address::RVA< uint32_t * >( base, dir->AddressOfNames );
        auto funcs = Address::RVA< uint32_t * >( base, dir->AddressOfFunctions );
        auto ords  = Address::RVA< uint16_t * >( base, dir->AddressOfNameOrdinals );
        if( !names || !funcs || !ords )
            return {};

        // iterate names array.
        for( size_t i{ 0u }; i < dir->NumberOfNames; ++i ) {
            export_name = Address::RVA< const char * >( base, names[ i ] );
            if( export_name.empty( ) )
                continue;

            // compare hash.
            if( FNV1a::get( export_name ) == name ) {
                // get export ptr.
                export_ptr = Address::RVA( base, funcs[ ords[ i ] ] );

                // it's a forwarded export, we must resolve it.
                if( export_ptr >= (uintptr_t)dir && export_ptr < ( (uintptr_t)dir + data_dir->Size ) ) {
                    // get forwarder string.
                    fwd_str = export_ptr.as< const char * >( );

                    // forwarders have a period as the delimiter.
                    delim = fwd_str.find_last_of( '.' ) + 1;
                    if( delim == std::string::npos )
                        return {};

                    // get forwarder module name.
                    fwd_module = fwd_str.substr( 0, delim );
                    
                    // append "dll" to fwd_module.
                    fwd_module += 'd';
                    fwd_module += 'l';
                    fwd_module += 'l';

                    // get forwarder export name.
                    fwd_export = fwd_str.substr( delim );
                    
                    // get real export ptr ( recursively ).
                    fwd_export_ptr = GetExport( GetModule( fwd_module ), fwd_export );
                    if( !fwd_export_ptr )
                        return {};
                    
                    // return ptr to forwarded export.
                    return fwd_export_ptr;
                }

                // return ptr to normal export.
                return export_ptr;
            }
        }

        return {};
    }

	// returns an array containing all exports in the specified module.
	static __declspec( noinline ) exports_t GetAllExports( const Module &module ) {
		Address     export_ptr, fwd_export_ptr;
		size_t      delim;
		std::string export_name, fwd_str, fwd_module, fwd_export;
		exports_t   exports;

		if( !module )
			return{};

		auto nt   = module.GetNT( );
		auto base = module.GetBase( );

		// get export data directory.
		auto data_dir = &nt->OptionalHeader.DataDirectory[ IMAGE_DIRECTORY_ENTRY_EXPORT ];
		if( !data_dir->VirtualAddress )
			return{};

		// get export dir.
		auto dir = Address::RVA< IMAGE_EXPORT_DIRECTORY * >( base, data_dir->VirtualAddress );
		if( !dir )
			return{};

		// names / funcs / ordinals ( all of these are RVAs ).
		auto names = Address::RVA< uint32_t * >( base, dir->AddressOfNames );
		auto funcs = Address::RVA< uint32_t * >( base, dir->AddressOfFunctions );
		auto ords  = Address::RVA< uint16_t * >( base, dir->AddressOfNameOrdinals );
		if( !names || !funcs || !ords )
			return{};

		// iterate names array.
		for( size_t i{ 0u }; i < dir->NumberOfNames; ++i ) {
			export_name = Address::RVA< const char * >( base, names[ i ] );
			if( export_name.empty( ) )
				continue;

			// get export ptr.
			export_ptr = Address::RVA( base, funcs[ ords[ i ] ] );

			// it's a forwarded export, we must resolve it.
			if( export_ptr >= ( uintptr_t )dir && export_ptr < ( ( uintptr_t )dir + data_dir->Size ) ) {
				// get forwarder string.
				fwd_str = export_ptr.as< const char* >( );

				// forwarders have a period as the delimiter.
				delim = fwd_str.find_last_of( '.' ) + 1;
				if( delim == std::string::npos )
					continue;

				// get forwarder module name.
				fwd_module = fwd_str.substr( 0, delim );

				// append "dll" to fwd_module.
				fwd_module += 'd';
				fwd_module += 'l';
				fwd_module += 'l';

				// get forwarder export name.
				fwd_export = fwd_str.substr( delim );

				// get real export ptr ( recursively ).
				fwd_export_ptr = GetExport( GetModule( fwd_module ), fwd_export );
				if( !fwd_export_ptr )
					continue;

				exports.push_back( { FNV1a::get( export_name ), fwd_export_ptr } );
			}

			// return ptr to normal export.
			else
                exports.push_back( { FNV1a::get( export_name ), export_ptr } );
		}

		return exports;
	}

    // gets the address of an exported function in a module by string.
    static __declspec( noinline ) Address GetExport( const Module &module, const std::string &name ) {
        return GetExport( module, FNV1a::get( name ) );
    }
}