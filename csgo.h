#pragma once

// predeclares.
class CCSGOPlayerAnimState;
class C_CSGameRules;

class CSGO {
public:
	using MD5_PseudoRandom_t = uint32_t(__thiscall *)(uint32_t);
	using GetGlowObjectManager_t = CGlowObjectManager * (__cdecl *)();
	using RandomSeed_t = void(__cdecl *)(int);
	using RandomInt_t = int(__cdecl *)(int, int);
	using RandomFloat_t = float(__cdecl *)(float, float);
	using IsBreakableEntity_t = bool(__thiscall *)(Entity *);
	using AngleMatrix_t = void(__fastcall *)(const ang_t &, matrix3x4_t &);
	using LoadFromBuffer_t = bool(__thiscall *)(KeyValues *, const char *, const char *, void *, void *, void *);
	using ServerRankRevealAll_t = bool(__cdecl *)(CCSUsrMsg_ServerRankRevealAll *);
	using IsReady_t = void(__cdecl *)();
	using ShowAndUpdateSelection_t = void(__thiscall *)(CHudElement *, int, Weapon *, bool);
	using GetEconItemView_t = C_EconItemView * (__thiscall *)(Weapon *);
	using GetStaticData_t = CEconItemDefinition * (__thiscall *)(C_EconItemView *);
	using ConcatTransforms_t = void(__fastcall *)();
	using BeamAlloc_t = Beam_t * (__thiscall *)(IViewRenderBeams *, bool);
	using SetupBeam_t = void(__stdcall *)(Beam_t *, const BeamInfo_t &);
	using ClearNotices_t = void(__thiscall *)(KillFeed_t *);
	using AddListenerEntity_t = void(__stdcall *)(IEntityListener *);
	using GetShotgunSpread_t = void(__stdcall *)(int, int, int, float *, float *);

public:
	bool m_done;

	// module objects.
	PE::Module m_kernel32_dll;
	PE::Module m_user32_dll;
	PE::Module m_shell32_dll;
	PE::Module m_shlwapi_dll;
	PE::Module m_client_dll;
	PE::Module m_engine_dll;
	PE::Module m_vstdlib_dll;
	PE::Module m_tier0_dll;
	PE::Module m_serverbrowser_dll;

public:
	// interface ptrs.
	CHLClient *m_client;
	ICvar *m_cvar;
	IVEngineClient *m_engine;
	IClientEntityList *m_entlist;
	IInputSystem *m_input_system;
	ISurface *m_surface;
	IPanel *m_panel;
	IEngineVGui *m_engine_vgui;
	CPrediction *m_prediction;
	IEngineTrace *m_engine_trace;
	CGameMovement *m_game_movement;
	IVRenderView *m_render_view;
	CViewRender *m_view_render;
	IVModelRender *m_model_render;
	IMaterialSystem *m_material_system;
	CStudioRenderContext *m_studio_render;
	IVModelInfo *m_model_info;
	IVDebugOverlay *m_debug_overlay;
	IPhysicsSurfaceProps *m_phys_props;
	IGameEventManager2 *m_game_events;
	CMatchFramework *m_match_framework;
	ILocalize *m_localize;
	INetworkStringTableContainer *m_networkstringtable;
	IEngineSound *m_sound;

	IClientMode *m_client_mode;
	CGlobalVarsBase *m_globals;
	CInput *m_input;
	IMoveHelper *m_move_helper;
	INetChannel *m_net;

	CGlowObjectManager *m_glow;
	CClientState *m_cl;
	CGame *m_game;
	CRender *m_render;
	IMemAlloc *m_mem_alloc;
	IClientShadowMgr *m_shadow_mgr;
	// IClientEntityListener** m_entity_listeners;
	CHud *m_hud;
	C_CSGameRules *m_gamerules;
	IViewRenderBeams *m_beams;
	void *m_radar;
	void *m_hookable_cl;

public:
	// convars.
	ConVar *clear;
	ConVar *toggleconsole;
	ConVar *name;
	ConVar *sv_maxunlag;
	ConVar *sv_gravity;
	ConVar *sv_jump_impulse;
	ConVar *sv_enablebunnyhopping;
	ConVar *sv_airaccelerate;
	ConVar *sv_friction;
	ConVar *sv_stopspeed;
	ConVar *cl_interp;
	ConVar *cl_interp_ratio;
	ConVar *cl_updaterate;
	ConVar *cl_cmdrate;
	ConVar *cl_lagcompensation;
	ConVar *mp_teammates_are_enemies;
	ConVar *weapon_debug_spread_show;
	ConVar *net_showfragments;
	ConVar *molotov_throw_detonate_time;
	ConVar *weapon_molotov_maxdetonateslope;
	ConVar *weapon_recoil_scale;
	ConVar *view_recoil_tracking;
	ConVar *cl_fullupdate;
	ConVar *r_DrawSpecificStaticProp;
	ConVar *cl_crosshair_sniper_width;
	ConVar *hud_scaling;
	ConVar *sv_clip_penetration_traces_to_players;
	ConVar *weapon_accuracy_shotgun_spread_patterns;

public:
	// functions.
	GetGlowObjectManager_t   GetGlowObjectManager;
	MD5_PseudoRandom_t	     MD5_PseudoRandom;
	Address                  SetAbsAngles;
	Address				     SetAbsOrigin;
	Address                  InvalidateBoneCache;
	Address				     LockStudioHdr;
	RandomSeed_t             RandomSeed;
	RandomInt_t              RandomInt;
	RandomFloat_t            RandomFloat;
	IsBreakableEntity_t      IsBreakableEntity;
	Address	                 SetAbsVelocity;
	AngleMatrix_t            AngleMatrix;
	Address					 DoProceduralFootPlant;
	Address					 ComputeHitboxSurroundingBox;
	Address					 GetSequenceActivity;
	LoadFromBuffer_t		 LoadFromBuffer;
	ServerRankRevealAll_t    ServerRankRevealAll;
	Address					 HasC4;
	Address					 InvalidatePhysicsRecursive;
	IsReady_t				 IsReady;
	ShowAndUpdateSelection_t ShowAndUpdateSelection;
	GetEconItemView_t        GetEconItemView;
	GetStaticData_t          GetStaticData;
	Address					 TEFireBullets;
	BeamAlloc_t              BeamAlloc;
	SetupBeam_t              SetupBeam;
	ClearNotices_t           ClearNotices;
	AddListenerEntity_t      AddListenerEntity;
	GetShotgunSpread_t       GetShotgunSpread;

	size_t BoneAccessor;
	size_t AnimOverlay;
	size_t SpawnTime;
	size_t MostRecentModelBoneCounter;
	size_t LastBoneSetupTime;
	size_t IsLocalPlayer;
	size_t PlayerAnimState;
	size_t studioHdr;

	Address UTIL_TraceLine;
	Address CTraceFilterSimple_vmt;
	Address CTraceFilterSkipTwoEntities_vmt;

	int *m_nPredictionRandomSeed;
	Player *m_pPredictionPlayer;

public:
	// initialize class.
	bool init();
};

extern CSGO g_csgo;

namespace game {
	__forceinline float GetClientInterpAmount() {
		return std::max(g_csgo.cl_interp->GetFloat(), g_csgo.cl_interp_ratio->GetFloat() / g_csgo.cl_updaterate->GetFloat());
	}

	__forceinline int TIME_TO_TICKS(float time) {
		return (int)(0.5f + time / g_csgo.m_globals->m_interval);
	}

	__forceinline float TICKS_TO_TIME(int ticks) {
		return g_csgo.m_globals->m_interval * (float)(ticks);
	}

	__forceinline bool IsFakePlayer(int index) {
		player_info_t info;
		if (g_csgo.m_engine->GetPlayerInfo(index, &info))
			return info.m_fake_player;

		return false;
	}

	__forceinline bool IsValidHitgroup(int index) {
		if ((index >= HITGROUP_HEAD && index <= HITGROUP_RIGHTLEG) || index == HITGROUP_GEAR)
			return true;

		return false;
	}

	// note - dex; all of the static sigscans here should be moved to CSGO class... funcs that rely on these do 2 test statements to make sure the data is initialized
	//             also, nitro, is there a reason these are not __forceinline? i forget if you told me they must be inline.
	inline void CreateAnimationState(Player *holder, CCSGOPlayerAnimState *state) {
		using CreateAnimState_t = void(__thiscall *)(CCSGOPlayerAnimState *, Player *);

		static auto func = pattern::find(g_csgo.m_client_dll, XOR("55 8B EC 56 8B F1 B9 ? ? ? ? C7 46")).as< CreateAnimState_t >();
		if (!func)
			return;

		func(state, holder);
	}

	inline void UpdateAnimationState(CCSGOPlayerAnimState *state, ang_t ang) {
		static auto func = pattern::find(g_csgo.m_client_dll, XOR("E8 ? ? ? ? 0F 57 C0 0F 11 86")).rel32< uintptr_t >(0x1);
		if (!func)
			return;

		__asm {
			push  0
			mov	  ecx, state
			movss xmm1, dword ptr[ang + 4]
			movss xmm2, dword ptr[ang]
			call  func
		}
	}

	inline void ResetAnimationState(CCSGOPlayerAnimState *state) {
		using ResetAnimState_t = void(__thiscall *)(CCSGOPlayerAnimState *);

		static auto func = pattern::find(g_csgo.m_client_dll, XOR("56 6A 01 68 ? ? ? ? 8B F1")).as< ResetAnimState_t >();
		if (!func)
			return;

		func(state);
	}

	__forceinline void UTIL_ClipTraceToPlayers(const vec3_t &start, const vec3_t &end, uint32_t mask, ITraceFilter *filter, CGameTrace *tr, float range) {
		static auto func = pattern::find(g_csgo.m_client_dll, XOR("E8 ? ? ? ? 83 C4 14 8A 56 37")).rel32< uintptr_t >(0x1);
		if (!func)
			return;

		__asm {
			mov  ecx, start
			mov	 edx, end
			push range
			push tr
			push filter
			push mask
			call func
			add	 esp, 16
		}
	}

	__forceinline void ConcatTransforms(const matrix3x4_t &in1, const matrix3x4_t &in2, matrix3x4_t &output) {
		static auto func = pattern::find(g_csgo.m_client_dll, XOR("E8 ? ? ? ? 0F 28 44 24")).rel32< uintptr_t >(0x1);
		if (!func)
			return;

		__asm {
			push output
			lea  edx, in2
			lea  ecx, in1
			call func
			add  esp, 4
		}
	}

	bool   IsBreakable(Entity *ent);
	Beam_t *CreateGenericBeam(const BeamInfo_t &beam_info);
}