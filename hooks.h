#pragma once

class Hooks {
public:
	void init( );

public:
	// forward declarations
	class IRecipientFilter;

	// prototypes.
	using PaintTraverse_t              = void( __thiscall* )( void*, VPANEL, bool, bool );
	using DoPostScreenSpaceEffects_t   = bool( __thiscall* )( void*, CViewSetup* );
	using CreateMove_t                 = bool( __thiscall* )( void*, float, CUserCmd* );
	using LevelInitPostEntity_t        = void( __thiscall* )( void* );
	using LevelShutdown_t              = void( __thiscall* )( void* );
	using LevelInitPreEntity_t         = void( __thiscall* )( void*, const char* );
	using IN_KeyEvent_t                = int( __thiscall* )( void*, int, int, const char* );
	using FrameStageNotify_t           = void( __thiscall* )( void*, Stage_t );
	using UpdateClientSideAnimation_t  = void( __thiscall* )( void* );
    using GetActiveWeapon_t            = Weapon*( __thiscall * )( void* );
	using DoExtraBoneProcessing_t      = void( __thiscall* )( void*, int, int, int, int, int, int );
	using BuildTransformations_t       = void( __thiscall* )( void*, int, int, int, int, int, int );
	using CalcViewModelView_t          = void( __thiscall* )( void*, vec3_t&, ang_t& );
	using InPrediction_t               = bool( __thiscall* )( void* );
	using OverrideView_t               = void( __thiscall* )( void*, CViewSetup* );
	using LockCursor_t                 = void( __thiscall* )( void* );
	using RunCommand_t                 = void( __thiscall* )( void*, Entity*, CUserCmd*, IMoveHelper* );
	using ProcessPacket_t              = void( __thiscall* )( void*, void*, bool );
	using SendDatagram_t               = int( __thiscall* )( void*, void* );
	// using CanPacket_t                = bool( __thiscall* )( void* );
	using PlaySound_t                  = void( __thiscall* )( void*, const char* );
	using GetScreenSize_t              = void( __thiscall* )( void*, int&, int& );
	using Push3DView_t                 = void( __thiscall* )( void*, CViewSetup&, int, void*, void* );
	using SceneEnd_t                   = void( __thiscall* )( void* );
	using DrawModelExecute_t           = void( __thiscall* )( void*, uintptr_t, const DrawModelState_t&, const ModelRenderInfo_t&, matrix3x4_t* );
	using ComputeShadowDepthTextures_t = void( __thiscall* )( void*, const CViewSetup&, bool );
	using GetInt_t                     = int( __thiscall* )( void* );
	using GetBool_t                    = bool( __thiscall* )( void* );
	using IsConnected_t                = bool( __thiscall* )( void* );
	using IsHLTV_t                     = bool( __thiscall* )( void* );
	using OnEntityCreated_t            = void( __thiscall* )( void*, Entity* );
	using OnEntityDeleted_t            = void( __thiscall* )( void*, Entity* );
	using RenderSmokeOverlay_t         = void( __thiscall* )( void*, bool );
	using ShouldDrawFog_t              = bool( __thiscall* )( void* );
	using ShouldDrawParticles_t        = bool( __thiscall* )( void* );
	using Render2DEffectsPostHUD_t     = void( __thiscall* )( void*, const CViewSetup& );
	using OnRenderStart_t              = void( __thiscall* )( void* );
    using RenderView_t                 = void( __thiscall* )( void*, const CViewSetup &, const CViewSetup &, int, int );
	using GetMatchSession_t            = CMatchSessionOnlineHost*( __thiscall* )( void* );
	using OnScreenSizeChanged_t        = void( __thiscall* )( void*, int, int );
	using OverrideConfig_t             = bool( __thiscall* )( void*, MaterialSystem_Config_t*, bool );
	using PostDataUpdate_t             = void( __thiscall* )( void*, DataUpdateType_t );
	using TempEntities_t               = bool( __thiscall* )( void*, void * );
	using EmitSound_t                  = void( __thiscall* )( void*, IRecipientFilter&, int, int, const char*, unsigned int, const char*, float, float, int, int, int, const vec3_t*, const vec3_t*, void*, bool, float, int );
	// using PreDataUpdate_t            = void( __thiscall* )( void*, DataUpdateType_t );

public:
	bool                     TempEntities( void *msg );
	void                     PaintTraverse( VPANEL panel, bool repaint, bool force );
	bool                     DoPostScreenSpaceEffects( CViewSetup* setup );
	bool                     CreateMove( float input_sample_time, CUserCmd* cmd );
	void                     LevelInitPostEntity( );
	void                     LevelShutdown( );
	//int                      IN_KeyEvent( int event, int key, const char* bind );
	void                     LevelInitPreEntity( const char* map );
	void                     FrameStageNotify( Stage_t stage );
	void                     UpdateClientSideAnimation( );
    Weapon*                  GetActiveWeapon( );
	bool                     InPrediction( );
	bool                     ShouldDrawParticles( );
	bool                     ShouldDrawFog( );
	void                     OverrideView( CViewSetup* view );
	void                     LockCursor( );
	void                     PlaySound( const char* name );
	void                     OnScreenSizeChanged( int oldwidth, int oldheight );
	void                     RunCommand( Entity* ent, CUserCmd* cmd, IMoveHelper* movehelper );
	int                      SendDatagram( void* data );
	void                     ProcessPacket( void* packet, bool header );
	//void                     GetScreenSize( int& w, int& h );
	void                     SceneEnd( );
	void                     DrawModelExecute( uintptr_t ctx, const DrawModelState_t& state, const ModelRenderInfo_t& info, matrix3x4_t* bone );
	void                     ComputeShadowDepthTextures( const CViewSetup& view, bool unk );
	int                      DebugSpreadGetInt( );
	bool                     NetShowFragmentsGetBool( );
	void                     DoExtraBoneProcessing( int a2, int a3, int a4, int a5, int a6, int a7 );
	void                     BuildTransformations( int a2, int a3, int a4, int a5, int a6, int a7 );
	bool                     IsConnected( );
	bool                     IsHLTV( );
	void                     EmitSound( IRecipientFilter& filter, int iEntIndex, int iChannel, const char* pSoundEntry, unsigned int nSoundEntryHash, const char* pSample, float flVolume, float flAttenuation, int nSeed, int iFlags, int iPitch, const vec3_t* pOrigin, const vec3_t* pDirection, void* pUtlVecOrigins, bool bUpdatePositions, float soundtime, int speakerentity );
	void                     RenderSmokeOverlay( bool unk );
	void                     OnRenderStart( );
    void                     RenderView( const CViewSetup &view, const CViewSetup &hud_view, int clear_flags, int what_to_draw );
	void                     Render2DEffectsPostHUD( const CViewSetup& setup );
	CMatchSessionOnlineHost* GetMatchSession( );
	bool                     OverrideConfig( MaterialSystem_Config_t* config, bool update );
	void                     PostDataUpdate( DataUpdateType_t type );

	static LRESULT WINAPI WndProc( HWND wnd, uint32_t msg, WPARAM wp, LPARAM lp );

public:
	// vmts.
	VMT m_panel;
	VMT m_client_mode;
	VMT m_client;
	VMT m_client_state;
	VMT m_engine;
	VMT m_engine_sound;
	VMT m_prediction;
	VMT m_surface;
	VMT m_render;
	VMT m_net_channel;
	VMT m_render_view;
	VMT m_model_render;
	VMT m_shadow_mgr;
	VMT m_view_render;
	VMT m_match_framework;
	VMT m_material_system;
	VMT m_fire_bullets;
	VMT m_net_show_fragments;

	// player shit.
	std::array< VMT, 64 > m_player;

	// cvars
	VMT m_debug_spread;

	// wndproc old ptr.
	WNDPROC m_old_wndproc;

	// old player create fn.
	DoExtraBoneProcessing_t     m_DoExtraBoneProcessing;
	UpdateClientSideAnimation_t m_UpdateClientSideAnimation;
    GetActiveWeapon_t           m_GetActiveWeapon;
	BuildTransformations_t      m_BuildTransformations;

	// netvar proxies.
	RecvVarProxy_t m_Pitch_original;
	RecvVarProxy_t m_Body_original;
    RecvVarProxy_t m_Force_original;
	RecvVarProxy_t m_AbsYaw_original;
};

// note - dex; these are defined in player.cpp.
class CustomEntityListener : public IEntityListener {
public:
    virtual void OnEntityCreated( Entity *ent );
    virtual void OnEntityDeleted( Entity *ent );

    __forceinline void init( ) {
        g_csgo.AddListenerEntity( this );
    }
};

extern Hooks                g_hooks;
extern CustomEntityListener g_custom_entity_listener;