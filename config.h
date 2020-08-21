#pragma once

class Config {
public:
	void init( );
	void LoadHotkeys( );
	void SaveHotkeys( );
	void load( const Form* form, const std::string& name );
	void save( const Form* form, const std::string& name );

private:
	bool m_init;
	std::string m_path;
};

extern Config g_config;