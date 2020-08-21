#include "includes.h"

void Hooks::DrawModelExecute( uintptr_t ctx, const DrawModelState_t& state, const ModelRenderInfo_t& info, matrix3x4_t* bone ) {
	// do chams.
	if( g_chams.DrawModel( ctx, state, info, bone ) ) {
		g_hooks.m_model_render.GetOldMethod< Hooks::DrawModelExecute_t >( IVModelRender::DRAWMODELEXECUTE )( this, ctx, state, info, bone );
	}

	// disable material force for next call.
	//g_csgo.m_studio_render->ForcedMaterialOverride( nullptr );
}