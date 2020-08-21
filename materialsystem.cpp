#include "includes.h"

bool Hooks::OverrideConfig( MaterialSystem_Config_t* config, bool update ) {
	if( g_menu.main.visuals.world.get( ) == 2 )
		config->m_nFullbright = true;

	return g_hooks.m_material_system.GetOldMethod< OverrideConfig_t >( IMaterialSystem::OVERRIDECONFIG )( this, config, update );
}