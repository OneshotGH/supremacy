#include "includes.h"

Config g_config{};

void Config::init( ) {
	// reset.
	m_init = false;

	// alloc.
	m_path.resize( MAX_PATH + 1 );

	// get the path to mydocuments.
	if( !SUCCEEDED( g_winapi.SHGetFolderPathA( 0, CSIDL_PERSONAL, 0, SHGFP_TYPE_CURRENT, ( char* )m_path.data( ) ) ) )
		return;

	// append our subdir.
	g_winapi.PathAppendA( ( char* )m_path.c_str( ), g_cl.m_user.c_str( ) );

	// create folder if not present.
	g_winapi.CreateDirectoryA( m_path.c_str( ), 0 );

	// we found the path.
	// and we managed to create our subdir.
	m_init = true;
}

void Config::LoadHotkeys( ) {
	if( !m_init )
		return;

	// make copy of parent dir.
	std::string file{ m_path };

	// append filename.
	g_winapi.PathAppendA( ( char* )file.c_str( ), XOR( "keys.sup" ) );

	// construct incoming file stream.
	std::ifstream in{ file };
	if( !in.is_open( ) || in.fail( ) ) {
		in.close( );
		return;
	}

	// read file into string.
	std::string data;
	in.seekg( 0, std::ios::end );
	data.resize( in.tellg( ) );
	in.seekg( 0, std::ios::beg );
	in.read( &data[ 0 ], data.size( ) );
	in.close( );

	// decrypt config and convert to json obj.
	nlohmann::json config{ nlohmann::json::parse( crypto::base64_decode( data ) ) };

	// load all keys from the json.
	g_menu.main.config.key1.set( config[ g_menu.main.config.key1.m_file_id ] );
	g_menu.main.config.key2.set( config[ g_menu.main.config.key2.m_file_id ] );
	g_menu.main.config.key3.set( config[ g_menu.main.config.key3.m_file_id ] );
	g_menu.main.config.key4.set( config[ g_menu.main.config.key4.m_file_id ] );
	g_menu.main.config.key5.set( config[ g_menu.main.config.key5.m_file_id ] );
	g_menu.main.config.key6.set( config[ g_menu.main.config.key6.m_file_id ] );
}

void Config::SaveHotkeys( ) {
	if( !m_init )
		return;

	nlohmann::json config{};

	// make copy of parent dir.
	std::string file{ m_path };

	// append filename.
	g_winapi.PathAppendA( ( char* )file.c_str( ), XOR( "keys.sup" ) );

	// construct outgoing file stream.
	std::ofstream stream{ file };
	if( !stream.is_open( ) || stream.fail( ) ) {
		stream.close( );
		return;
	}

	// save all keys to the json.
	config[ g_menu.main.config.key1.m_file_id ] = g_menu.main.config.key1.get( );
	config[ g_menu.main.config.key2.m_file_id ] = g_menu.main.config.key2.get( );
	config[ g_menu.main.config.key3.m_file_id ] = g_menu.main.config.key3.get( );
	config[ g_menu.main.config.key4.m_file_id ] = g_menu.main.config.key4.get( );
	config[ g_menu.main.config.key5.m_file_id ] = g_menu.main.config.key5.get( );
	config[ g_menu.main.config.key6.m_file_id ] = g_menu.main.config.key6.get( );

	// write to file.
	stream << crypto::base64_encode( config.dump( ) );
	stream.close( );
}

void Config::load( const Form* form, const std::string& name ) {
	if( !m_init )
		return;

	// nothing to load.
	if( form->m_tabs.empty( ) )
		return;

	// make copy of parent dir.
	std::string file{ m_path };

	// append filename.
	g_winapi.PathAppendA( ( char* )file.c_str( ), name.c_str( ) );

	// construct incoming file stream.
	std::ifstream in{ file };
	if( !in.is_open( ) || in.fail( ) ) {
		in.close( );
		return;
	}

	// read file.
	std::string data;
	in.seekg( 0, std::ios::end );
	data.resize( in.tellg( ) );
	in.seekg( 0, std::ios::beg );
	in.read( &data[ 0 ], data.size( ) );
	in.close( );

	// decrypt config and convert to json obj.
	nlohmann::json config{ nlohmann::json::parse( crypto::base64_decode( data ) ) };
			
	// iterate all stored tabs.
	for( nlohmann::json::iterator t = config.begin( ); t != config.end( ); t++ ) {
		// get tab title.
		std::string title = t.key( );

		// get containing elements.
		nlohmann::json elements = t.value( );

		// get the tab by name.
		// ignore if tab is not present.
		Tab* tab = form->GetTabByName( title );
		if( !tab )
			continue;

		// iterate all stored elements.
		for( nlohmann::json::iterator e = elements.begin( ); e != elements.end( ); e++ ) {
			// get element identifier.
			std::string id = e.key( );

			// get element by name.
			// ignore if element is not present.
			Element* element = tab->GetElementByName( id );
			if( !element )
				continue;

			switch( element->m_type ) {

			case ElementTypes::CHECKBOX:
				static_cast< Checkbox* >( element )->set( e.value( ) );
				break;

			case ElementTypes::SLIDER:
				static_cast< Slider* >( element )->set( e.value( ) );
				break;

			case ElementTypes::KEYBIND:
				static_cast< Keybind* >( element )->set( e.value( ) );
				break;

			case ElementTypes::DROPDOWN:
				static_cast< Dropdown* >( element )->set( e.value( ) );
				break;

			case ElementTypes::COLORPICKER:
			{
				if( !e.value( ).is_array( ) )
					continue;

				std::vector< int > color = e.value( );

				// tf happened here. colors should be sets of 4.
				if( color.size( ) != 4 )
					continue;
			
				// set color.
				static_cast< Colorpicker* >( element )->set( { color[ 0 ], color[ 1 ], color[ 2 ], color[ 3 ] } );
				break;
			}

			case ElementTypes::MULTI_DROPDOWN:
			{
				if( !e.value( ).is_array( ) )
					continue;

				MultiDropdown* mdd = ( MultiDropdown* )element;

				std::vector< int > selection = e.value( );

				mdd->clear( );

				for( auto idx : selection )
					mdd->select( idx );
		
				break;
			}
				
			case ElementTypes::EDIT:
				static_cast< Edit* >( element )->set( e.value( ) );
				break;

			default:
				break;
			}
		}
	}
}

void Config::save( const Form* form, const std::string& name ) {
	nlohmann::json config{};

	if( !m_init )
		return;

	// nothing to save.
	if( form->m_tabs.empty( ) )
		return;

	// make copy of parent dir.
	std::string file{ m_path };

	// append filename.
	g_winapi.PathAppendA( ( char* )file.c_str( ), name.c_str( ) );

	// construct outgoing file stream.
	std::ofstream stream{ file };
	if( !stream.is_open( ) || stream.fail( ) ) {
		stream.close( );
		return;
	}
		
	// iterate tabs.
	for( const auto t : form->m_tabs ) {
		// this tab has no elements.
		if( t->m_elements.empty( ) )
			continue;

		// get tab title.
		std::string title = t->m_title;

		// iterate tab elements.
		for( const auto e : t->m_elements ) {
			if( !( e->m_flags & ElementFlags::SAVE ) )
				continue;

			// get element type.
			size_t type = e->m_type;

			// get file identifier.
			std::string name = e->m_file_id;

			// NOTE; gross C++ casts ahead.
			// pls dont kill me its the best way.

			switch( type ) {

			case ElementTypes::CHECKBOX:
				config[ title ][ name ] = static_cast< Checkbox* >( e )->get( );
				break;

			case ElementTypes::SLIDER:
				config[ title ][ name ] = static_cast< Slider* >( e )->get( );
				break;

			case ElementTypes::KEYBIND:
				config[ title ][ name ] = static_cast< Keybind* >( e )->get( );
				break;

			case ElementTypes::DROPDOWN:
				config[ title ][ name ] = static_cast< Dropdown* >( e )->get( );
				break;

			case ElementTypes::COLORPICKER:
			{
				// get color
				Color color = static_cast< Colorpicker* >( e )->get( );

				// construct small array with color.
				std::array< int, 4 > arr = { color.r( ), color.g( ), color.b( ), color.a( ) };

				// write array to config.
				config[ title ][ name ] = arr;
				break;
			}

			case ElementTypes::MULTI_DROPDOWN:
				config[ title ][ name ] = static_cast< MultiDropdown* >( e )->GetActiveIndices( );
				break;

			case ElementTypes::EDIT:
				config[ title ][ name ] = static_cast< Edit* >( e )->get( );
				break;

			default:
				break;
			}
		}
	}

	stream << crypto::base64_encode( config.dump( ) );
	stream.close( );
}