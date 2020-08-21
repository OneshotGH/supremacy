#pragma once

#define MAX_WEAPONS	48

enum Hitboxes_t : int {
	HITBOX_HEAD = 0,
	HITBOX_NECK,
	HITBOX_LOWER_NECK,
	HITBOX_PELVIS,
	HITBOX_BODY,
	HITBOX_THORAX,
	HITBOX_CHEST,
	HITBOX_UPPER_CHEST,
	HITBOX_R_THIGH,
	HITBOX_L_THIGH,
	HITBOX_R_CALF,
	HITBOX_L_CALF,
	HITBOX_R_FOOT,
	HITBOX_L_FOOT,
	HITBOX_R_HAND,
	HITBOX_L_HAND,
	HITBOX_R_UPPER_ARM,
	HITBOX_R_FOREARM,
	HITBOX_L_UPPER_ARM,
	HITBOX_L_FOREARM,
	HITBOX_MAX
};

enum RenderFlags_t : uint32_t {
	STUDIO_NONE = 0x00000000,
	STUDIO_RENDER = 0x00000001,
	STUDIO_VIEWXFORMATTACHMENTS = 0x00000002,
	STUDIO_DRAWTRANSLUCENTSUBMODELS = 0x00000004,
	STUDIO_TWOPASS = 0x00000008,
	STUDIO_STATIC_LIGHTING = 0x00000010,
	STUDIO_WIREFRAME = 0x00000020,
	STUDIO_ITEM_BLINK = 0x00000040,
	STUDIO_NOSHADOWS = 0x00000080,
	STUDIO_WIREFRAME_VCOLLIDE = 0x00000100,
	STUDIO_NOLIGHTING_OR_CUBEMAP = 0x00000200,
	STUDIO_SKIP_FLEXES = 0x00000400,
	STUDIO_DONOTMODIFYSTENCILSTATE = 0x00000800,
	STUDIO_TRANSPARENCY = 0x80000000,
	STUDIO_SHADOWDEPTHTEXTURE = 0x40000000,
	STUDIO_SHADOWTEXTURE = 0x20000000,
	STUDIO_SKIP_DECALS = 0x10000000
};

enum BoneFlags_t : int {
	BONE_USED_BY_ANYTHING = 0x0007FF00,
	BONE_USED_BY_HITBOX = 0x00000100, // bone (or child) is used by a hit box
	BONE_USED_BY_ATTACHMENT = 0x00000200, // bone (or child) is used by an attachment point
	BONE_USED_BY_VERTEX_MASK = 0x0003FC00,
	BONE_USED_BY_VERTEX_LOD0 = 0x00000400, // bone (or child) is used by the toplevel model via skinned vertex
	BONE_USED_BY_VERTEX_LOD1 = 0x00000800,
	BONE_USED_BY_VERTEX_LOD2 = 0x00001000,
	BONE_USED_BY_VERTEX_LOD3 = 0x00002000,
	BONE_USED_BY_VERTEX_LOD4 = 0x00004000,
	BONE_USED_BY_VERTEX_LOD5 = 0x00008000,
	BONE_USED_BY_VERTEX_LOD6 = 0x00010000,
	BONE_USED_BY_VERTEX_LOD7 = 0x00020000,
	BONE_USED_BY_BONE_MERGE = 0x00040000
};

enum CSWeaponType : int {
	WEAPONTYPE_UNKNOWN = -1,
	WEAPONTYPE_KNIFE,
	WEAPONTYPE_PISTOL,
	WEAPONTYPE_SUBMACHINEGUN,
	WEAPONTYPE_RIFLE,
	WEAPONTYPE_SHOTGUN,
	WEAPONTYPE_SNIPER_RIFLE,
	WEAPONTYPE_MACHINEGUN,
	WEAPONTYPE_C4,
	WEAPONTYPE_TASER,
	WEAPONTYPE_GRENADE,
	WEAPONTYPE_HEALTHSHOT = 11
};

enum teams_t : int {
	TEAM_NOTEAM = 0,
	TEAM_SPECTATOR,
	TEAM_TERRORISTS,
	TEAM_COUNTERTERRORISTS
};

enum effects_t : int {
	EF_BONEMERGE = 0x001,	// Performs bone merge on client side
	EF_BRIGHTLIGHT = 0x002,	// DLIGHT centered at entity origin
	EF_DIMLIGHT = 0x004,	// player flashlight
	EF_NOINTERP = 0x008,	// don't interpolate the next frame
	EF_NOSHADOW = 0x010,	// Don't cast no shadow
	EF_NODRAW = 0x020,	// don't draw entity
	EF_NORECEIVESHADOW = 0x040,	// Don't receive no shadow
	EF_BONEMERGE_FASTCULL = 0x080,	// For use with EF_BONEMERGE. If this is set, then it places this ent's origin at its
	EF_ITEM_BLINK = 0x100,	// blink an item so that the user notices it.
	EF_PARENT_ANIMATES = 0x200,	// always assume that the parent entity is animating
	EF_MAX_BITS = 10
};

enum InvalidatePhysicsBits_t : int {
	POSITION_CHANGED = 0x1,
	ANGLES_CHANGED = 0x2,
	VELOCITY_CHANGED = 0x4,
	ANIMATION_CHANGED = 0x8,
};

enum DataUpdateType_t : int {
	DATA_UPDATE_CREATED = 0,
	DATA_UPDATE_DATATABLE_CHANGED,
};

enum LifeStates_t : int {
	LIFE_ALIVE = 0,
	LIFE_DYING,
	LIFE_DEAD,
	LIFE_RESPAWNABLE,
	LIFE_DISCARDBODY,
};

enum PlayerFlags_t : int {
	FL_ONGROUND = (1 << 0),
	FL_DUCKING = (1 << 1),
	FL_WATERJUMP = (1 << 3),
	FL_ONTRAIN = (1 << 4),
	FL_INRAIN = (1 << 5),
	FL_FROZEN = (1 << 6),
	FL_ATCONTROLS = (1 << 7),
	FL_CLIENT = (1 << 8),
	FL_FAKECLIENT = (1 << 9),
	FL_INWATER = (1 << 10),
};

enum MoveType_t : int {
	MOVETYPE_NONE = 0,
	MOVETYPE_ISOMETRIC,
	MOVETYPE_WALK,
	MOVETYPE_STEP,
	MOVETYPE_FLY,
	MOVETYPE_FLYGRAVITY,
	MOVETYPE_VPHYSICS,
	MOVETYPE_PUSH,
	MOVETYPE_NOCLIP,
	MOVETYPE_LADDER,
	MOVETYPE_OBSERVER,
	MOVETYPE_CUSTOM,
	MOVETYPE_LAST = MOVETYPE_CUSTOM,
	MOVETYPE_MAX_BITS = 4,
};

enum Weapons_t : int {
	DEAGLE = 1,
	ELITE = 2,
	FIVESEVEN = 3,
	GLOCK = 4,
	AK47 = 7,
	AUG = 8,
	AWP = 9,
	FAMAS = 10,
	G3SG1 = 11,
	GALIL = 13,
	M249 = 14,
	M4A4 = 16,
	MAC10 = 17,
	P90 = 19,
	UMP45 = 24,
	XM1014 = 25,
	BIZON = 26,
	MAG7 = 27,
	NEGEV = 28,
	SAWEDOFF = 29,
	TEC9 = 30,
	ZEUS = 31,
	P2000 = 32,
	MP7 = 33,
	MP9 = 34,
	NOVA = 35,
	P250 = 36,
	SCAR20 = 38,
	SG553 = 39,
	SSG08 = 40,
	KNIFE_T = 42,
	FLASHBANG = 43,
	HEGRENADE = 44,
	SMOKE = 45,
	MOLOTOV = 46,
	DECOY = 47,
	FIREBOMB = 48,
	C4 = 49,
	MUSICKIT = 58,
	KNIFE_CT = 59,
	M4A1S = 60,
	USPS = 61,
	TRADEUPCONTRACT = 62,
	CZ75A = 63,
	REVOLVER = 64,
	KNIFE_BAYONET = 500,
	KNIFE_FLIP = 505,
	KNIFE_GUT = 506,
	KNIFE_KARAMBIT = 507,
	KNIFE_M9_BAYONET = 508,
	KNIFE_HUNTSMAN = 509,
	KNIFE_FALCHION = 512,
	KNIFE_BOWIE = 514,
	KNIFE_BUTTERFLY = 515,
	KNIFE_SHADOW_DAGGERS = 516,
};

struct RenderableInstance_t {
	uint8_t m_alpha;
	__forceinline RenderableInstance_t() : m_alpha{ 255ui8 } {}
};

class Entity {
public:
	// helper methods.
	template< typename t >
	__forceinline t &get(size_t offset) {
		return *(t *)((uintptr_t)this + offset);
	}

	template< typename t >
	__forceinline void set(size_t offset, const t &val) {
		*(t *)((uintptr_t)this + offset) = val;
	}

	template< typename t >
	__forceinline t as() {
		return (t)this;
	}

public:
	// netvars / etc.
	__forceinline vec3_t &m_vecOrigin() {
		return get< vec3_t >(g_entoffsets.m_vecOrigin);
	}

	__forceinline vec3_t &m_vecOldOrigin() {
		return get< vec3_t >(g_entoffsets.m_vecOldOrigin);
	}

	__forceinline vec3_t &m_vecVelocity() {
		return get< vec3_t >(g_entoffsets.m_vecVelocity);
	}

	__forceinline vec3_t &m_vecMins() {
		return get< vec3_t >(g_entoffsets.m_vecMins);
	}

	__forceinline vec3_t &m_vecMaxs() {
		return get< vec3_t >(g_entoffsets.m_vecMaxs);
	}

	__forceinline int &m_iTeamNum() {
		return get< int >(g_entoffsets.m_iTeamNum);
	}

	__forceinline int &m_nSequence() {
		return get< int >(g_entoffsets.m_nSequence);
	}

	__forceinline float &m_flCycle() {
		return get< float >(g_entoffsets.m_flCycle);
	}

	__forceinline float &m_flC4Blow() {
		return get< float >(g_entoffsets.m_flC4Blow);
	}

	__forceinline bool &m_bBombTicking() {
		return get< bool >(g_entoffsets.m_bBombTicking);
	}

	__forceinline int &m_fEffects() {
		// todo; netvar.
		return get< int >(g_entoffsets.m_fEffects);
	}

	__forceinline int &m_nModelIndex() {
		return get< int >(g_entoffsets.m_nModelIndex);
	}

	__forceinline bool &m_bReadyToDraw() {
		return get< bool >(g_entoffsets.m_bReadyToDraw);
	}

public:
	// virtual indices
	enum indices : size_t {
		WORLDSPACECENTER = 78,
		GETMAXHEALTH = 122,
		ISPLAYER = 152,
		ISBASECOMBATWEAPON = 160,
	};

public:
	// virtuals.
	// renderable table.
	__forceinline void *renderable() {
		return (void *)((uintptr_t)this + 0x4);
	}

	__forceinline vec3_t &GetRenderOrigin() {
		return util::get_method< vec3_t &(__thiscall *)(void *) >(renderable(), 1)(renderable());
	}

	__forceinline ang_t &GetRenderAngles() {
		return util::get_method< ang_t &(__thiscall *)(void *) >(renderable(), 2)(renderable());
	}

	__forceinline const model_t *GetModel() {
		return util::get_method< const model_t *(__thiscall *)(void *) >(renderable(), 8)(renderable());
	}

	__forceinline void DrawModel(int flags = STUDIO_RENDER, const RenderableInstance_t &instance = {}) {
		return util::get_method< void(__thiscall *)(void *, int, const RenderableInstance_t &)>(renderable(), 9)(renderable(), flags, instance);
	}

	__forceinline bool SetupBones(matrix3x4_t *out, int max, int mask, float time) {
		return util::get_method< bool(__thiscall *)(void *, matrix3x4_t *, int, int, float)>(renderable(), 13)(renderable(), out, max, mask, time);
	}

	// networkable table.
	__forceinline void *networkable() {
		return (void *)((uintptr_t)this + 0x8);
	}

	__forceinline void Release() {
		return util::get_method< void(__thiscall *)(void *) >(networkable(), 1)(networkable());
	}

	__forceinline ClientClass *GetClientClass() {
		return util::get_method< ClientClass *(__thiscall *)(void *) >(networkable(), 2)(networkable());
	}

	__forceinline void OnDataChanged(DataUpdateType_t type) {
		return util::get_method< void(__thiscall *)(void *, DataUpdateType_t) >(networkable(), 5)(networkable(), type);
	}

	__forceinline void PreDataUpdate(DataUpdateType_t type) {
		return util::get_method< void(__thiscall *)(void *, DataUpdateType_t) >(networkable(), 6)(networkable(), type);
	}

	__forceinline void PostDataUpdate(DataUpdateType_t type) {
		return util::get_method< void(__thiscall *)(void *, DataUpdateType_t) >(networkable(), 7)(networkable(), type);
	}

	__forceinline bool dormant() {
		return util::get_method< bool(__thiscall *)(void *) >(networkable(), 9)(networkable());
	}

	__forceinline int index() {
		return util::get_method< int(__thiscall *)(void *) >(networkable(), 10)(networkable());
	}

	__forceinline void SetDestroyedOnRecreateEntities() {
		return util::get_method< void(__thiscall *)(void *) >(networkable(), 13)(networkable());
	}

	// normal table.
	__forceinline const vec3_t &GetAbsOrigin() {
		return util::get_method< const vec3_t &(__thiscall *)(void *) >(this, 10)(this);
	}

	__forceinline const ang_t &GetAbsAngles() {
		return util::get_method< const ang_t &(__thiscall *)(void *) >(this, 11)(this);
	}

	__forceinline bool IsPlayer() {
		return util::get_method< bool(__thiscall *)(void *) >(this, ISPLAYER)(this);
	}

	__forceinline bool IsBaseCombatWeapon() {
		return util::get_method< bool(__thiscall *)(void *) >(this, ISBASECOMBATWEAPON)(this);
	}

	__forceinline std::string GetBombsiteName() {
		std::string out;

		// note - dex; bomb_target + 0x150 has a char array for site name... not sure how much memory gets allocated for it.
		out.resize(32u);

		std::memcpy(&out[0], (const void *)((uintptr_t)this + 0x150), 32u);

		return out;
	}

	__forceinline void InvalidatePhysicsRecursive(InvalidatePhysicsBits_t bits) {
		using InvalidatePhysicsRecursive_t = void(__thiscall *)(decltype(this), InvalidatePhysicsBits_t);
		g_csgo.InvalidatePhysicsRecursive.as< InvalidatePhysicsRecursive_t >()(this, bits);
	}

	__forceinline void SetAbsAngles(const ang_t &angles) {
		using SetAbsAngles_t = void(__thiscall *)(decltype(this), const ang_t &);
		g_csgo.SetAbsAngles.as< SetAbsAngles_t >()(this, angles);
	}

	__forceinline void SetAbsOrigin(const vec3_t &origin) {
		using SetAbsOrigin_t = void(__thiscall *)(decltype(this), const vec3_t &);
		g_csgo.SetAbsOrigin.as< SetAbsOrigin_t >()(this, origin);
	}

	__forceinline void SetAbsVelocity(const vec3_t &velocity) {
		using SetAbsVelocity_t = void(__thiscall *)(decltype(this), const vec3_t &);
		g_csgo.SetAbsVelocity.as< SetAbsVelocity_t >()(this, velocity);
	}

	__forceinline void AddEffect(int effects) {
		m_fEffects() |= effects;
	}

	__forceinline int get_class_id() {
		ClientClass *cc{ GetClientClass() };

		return (cc) ? cc->m_ClassID : -1;
	}

	__forceinline bool is(hash32_t hash) {
		return g_netvars.GetClientID(hash) == get_class_id();
	}
};

class CCSGOPlayerAnimState {
public:
	PAD(0x1C);				// 0x0000
	Player *m_outer;			// 0x001C
	PAD(0x40);				// 0x0020
	Player *m_player;			// 0x0060
	PAD(0x8);					// 0x0064
	float   m_time;				// 0x006C
	int     m_frame;			// 0x0070
	float   m_update_delta;		// 0x0074
	float   m_eye_yaw;			// 0x0078
	float   m_eye_pitch;		// 0x007C
	float   m_goal_feet_yaw;	// 0x0080
	float   m_cur_feet_yaw;		// 0x0084
	PAD(0x1C);				// 0x0088
	float   m_dip_cycle;        // 0x00A4
	float   m_dip_adj;          // 0x00A8
	PAD(0x40);				// 0x00A8
	float   m_speed;			// 0x00EC
	float   m_fall_velocity;    // 0x00F0
	PAD(0x14);				// 0x00F0
	bool    m_ground;			// 0x0108
	bool    m_land;             // 0x0109
	PAD(0x2);					// 0x010A 
	PAD(0x21C);				// 0x010C
	bool    m_dip_air;			// 0x0328
	PAD(0x12);				// 0x0329
	float   m_min_pitch;        // 0x033C
	PAD(0x4);					// 0x0340
}; // size: 0x344

class CStudioHdr {
public:
	class mstudioposeparamdesc_t {
	public:
		int					sznameindex;
		__forceinline char *const name(void) const { return ((char *)this) + sznameindex; }
		int					flags;	// ????
		float				start;	// starting value
		float				end;	// ending value
		float				loop;	// looping range, 0 for no looping, 360 for rotations, etc.
	};

	studiohdr_t *m_pStudioHdr;
	void *m_pVModel;
};

class C_AnimationLayer {
public:
	float   m_anim_time;			// 0x0000
	float   m_fade_out_time;		// 0x0004
	int     m_flags;				// 0x0008
	int     m_activty;				// 0x000C
	int     m_priority;				// 0x0010
	int     m_order;				// 0x0014
	int     m_sequence;				// 0x0018
	float   m_prev_cycle;			// 0x001C
	float   m_weight;				// 0x0020
	float   m_weight_delta_rate;	// 0x0024
	float   m_playback_rate;		// 0x0028
	float   m_cycle;				// 0x002C
	Entity *m_owner;				// 0x0030
	int     m_bits;					// 0x0034
}; // size: 0x0038

class CBoneAccessor {
public:
	void *m_pAnimating;
	BoneArray *m_pBones;
	int        m_ReadableBones;
	int        m_WritableBones;
};

class CBoneCache {
public:
	BoneArray *m_pCachedBones;
	PAD(0x8);
	int        m_CachedBoneCount;
};

class Ragdoll : public Entity {
public:
	__forceinline Player *GetPlayer() {
		return g_csgo.m_entlist->GetClientEntityFromHandle< Player * >(m_hPlayer());
	}

	__forceinline EHANDLE &m_hPlayer() {
		return get< EHANDLE >(g_entoffsets.m_hPlayer);
	}

	__forceinline float &m_flDeathYaw() {
		return get< float >(g_entoffsets.m_flDeathYaw);
	}

	__forceinline float &m_flAbsYaw() {
		return get< float >(g_entoffsets.m_flAbsYaw);
	}
};

class Player : public Entity {
public:
	// netvars / etc.
	__forceinline vec3_t &m_vecAbsVelocity() {
		return get< vec3_t >(g_entoffsets.m_vecAbsVelocity);
	}

	__forceinline int &m_lifeState() {
		return get< int >(g_entoffsets.m_lifeState);
	}

	__forceinline int &m_fFlags() {
		return get< int >(g_entoffsets.m_fFlags);
	}

	__forceinline int &m_MoveType() {
		return get< int >(g_entoffsets.m_MoveType);
	}

	__forceinline int &m_iHealth() {
		return get< int >(g_entoffsets.m_iHealth);
	}

	__forceinline int &m_iAccount() {
		return get< int >(g_entoffsets.m_iAccount);
	}

	__forceinline bool &m_bHasDefuser() {
		return get< bool >(g_entoffsets.m_bHasDefuser);
	}

	__forceinline int &m_nHitboxSet() {
		return get< int >(g_entoffsets.m_nHitboxSet);
	}

	__forceinline ang_t &m_angAbsRotation() {
		return get< ang_t >(g_entoffsets.m_angAbsRotation);
	}

	__forceinline ang_t &m_angRotation() {
		return get< ang_t >(g_entoffsets.m_angRotation);
	}

	__forceinline ang_t &m_angNetworkAngles() {
		return get< ang_t >(g_entoffsets.m_angNetworkAngles);
	}

	__forceinline bool m_bIsLocalPlayer() {
		// .text:101E0078 674     84 C0				   test    al, al          ; Logical Compare
		// .text:101E007A 674     74 17				   jz      short loc_101E0093; Jump if Zero( ZF = 1 )
		// .text:101E007C 674     8A 83 F8 35 00 00	   mov     al, [ ebx + 35F8h ]
		return get< bool >(g_csgo.IsLocalPlayer);
	}

	__forceinline CCSGOPlayerAnimState *m_PlayerAnimState() {
		// .text:1037A5B8 00C     E8 E3 40 E6 FF         call    C_BasePlayer__Spawn ; Call Procedure
		// .text:1037A5BD 00C     80 BE E1 39 00 00 00   cmp     byte ptr[ esi + 39E1h ], 0; Compare Two Operands
		// .text:1037A5C4 00C     74 48                  jz      short loc_1037A60E; Jump if Zero( ZF = 1 )
		// .text:1037A5C6 00C     8B 8E 74 38 00 00      mov     ecx, [ esi + 3874h ]; this
		// .text:1037A5CC 00C     85 C9                  test    ecx, ecx; Logical Compare
		// .text:1037A5CE 00C     74 3E                  jz      short loc_1037A60E; Jump if Zero( ZF = 1 )
		return get< CCSGOPlayerAnimState * >(g_csgo.PlayerAnimState);
	}

	__forceinline CStudioHdr *m_studioHdr() {
		// .text:1017E902 08C    8B 86 3C 29 00 00    mov     eax, [ esi + 293Ch ]
		// .text:1017E908 08C    89 44 24 10          mov[ esp + 88h + var_78 ], eax
		return get< CStudioHdr * >(g_csgo.studioHdr);
	}

	__forceinline ulong_t &m_iMostRecentModelBoneCounter() {
		// .text:101AC9A9 000    89 81 80 26 00 00    mov[ ecx + 2680h ], eax
		return get< ulong_t >(g_csgo.MostRecentModelBoneCounter);
	}

	__forceinline float &m_flLastBoneSetupTime() {
		// .text:101AC99F 000    C7 81 14 29 00 00 FF FF+    mov     dword ptr [ecx+2914h], 0FF7FFFFFh;
		return get< float >(g_csgo.LastBoneSetupTime);
	}

	__forceinline int &m_nTickBase() {
		return get< int >(g_entoffsets.m_nTickBase);
	}

	__forceinline float &m_flNextAttack() {
		return get< float >(g_entoffsets.m_flNextAttack);
	}

	__forceinline float &m_flDuckAmount() {
		return get< float >(g_entoffsets.m_flDuckAmount);
	}

	__forceinline float &m_flSimulationTime() {
		return get< float >(g_entoffsets.m_flSimulationTime);
	}

	__forceinline float &m_flOldSimulationTime() {
		return get< float >(g_entoffsets.m_flOldSimulationTime);
	}

	__forceinline float &m_flLowerBodyYawTarget() {
		return get< float >(g_entoffsets.m_flLowerBodyYawTarget);
	}

	__forceinline float &m_fImmuneToGunGameDamageTime() {
		return get< float >(g_entoffsets.m_fImmuneToGunGameDamageTime);
	}

	__forceinline bool &m_bHasHelmet() {
		return get< bool >(g_entoffsets.m_bHasHelmet);
	}

	__forceinline bool &m_bClientSideAnimation() {
		return get< bool >(g_entoffsets.m_bClientSideAnimation);
	}

	__forceinline bool &m_bHasHeavyArmor() {
		return get< bool >(g_entoffsets.m_bHasHeavyArmor);
	}

	__forceinline bool &m_bIsScoped() {
		return get< bool >(g_entoffsets.m_bIsScoped);
	}

	__forceinline bool &m_bDucking() {
		return get< bool >(g_entoffsets.m_bDucking);
	}

	__forceinline bool &m_bSpotted() {
		return get< bool >(g_entoffsets.m_bSpotted);
	}

	__forceinline int &m_iObserverMode() {
		return get< int >(g_entoffsets.m_iObserverMode);
	}

	__forceinline int &m_ArmorValue() {
		return get< int >(g_entoffsets.m_ArmorValue);
	}

	__forceinline float &m_flMaxspeed() {
		return get< float >(g_entoffsets.m_flMaxspeed);
	}

	__forceinline float &m_surfaceFriction() {
		return get< float >(g_entoffsets.m_surfaceFriction);
	}

	__forceinline float &m_flFlashBangTime() {
		return get< float >(g_entoffsets.m_flFlashBangTime);
	}

	__forceinline ang_t &m_angEyeAngles() {
		return get< ang_t >(g_entoffsets.m_angEyeAngles);
	}

	__forceinline ang_t &m_aimPunchAngle() {
		return get< ang_t >(g_entoffsets.m_aimPunchAngle);
	}

	__forceinline ang_t &m_viewPunchAngle() {
		return get< ang_t >(g_entoffsets.m_viewPunchAngle);
	}

	__forceinline ang_t &m_aimPunchAngleVel() {
		return get< ang_t >(g_entoffsets.m_aimPunchAngleVel);
	}

	__forceinline vec3_t &m_vecViewOffset() {
		return get< vec3_t >(g_entoffsets.m_vecViewOffset);
	}

	__forceinline CUserCmd &m_PlayerCommand() {
		return get< CUserCmd >(g_entoffsets.m_PlayerCommand);
	}

	__forceinline CUserCmd *&m_pCurrentCommand() {
		return get< CUserCmd * >(g_entoffsets.m_pCurrentCommand);
	}

	__forceinline int &m_iEFlags() {
		return get< int >(g_entoffsets.m_iEFlags);
	}

	__forceinline float *m_flPoseParameter() {
		return (float *)((uintptr_t)this + g_entoffsets.m_flPoseParameter);
	}

	__forceinline CBaseHandle *m_hMyWearables() {
		return (CBaseHandle *)((uintptr_t)this + g_entoffsets.m_hMyWearables);
	}

	__forceinline CBoneCache &m_BoneCache() {
		// TODO; sig
		return get< CBoneCache >(g_entoffsets.m_BoneCache);
	}

	__forceinline EHANDLE &m_hObserverTarget() {
		return get< EHANDLE >(g_entoffsets.m_hObserverTarget);
	}

	__forceinline EHANDLE &m_hActiveWeapon() {
		return get< EHANDLE >(g_entoffsets.m_hActiveWeapon);
	}

	__forceinline EHANDLE &m_hGroundEntity() {
		return get< EHANDLE >(g_entoffsets.m_hGroundEntity);
	}

	__forceinline CBaseHandle *m_hMyWeapons() {
		return (CBaseHandle *)((uintptr_t)this + g_entoffsets.m_hMyWeapons);
	}

	__forceinline C_AnimationLayer *m_AnimOverlay() {
		// .text:1017EAB1 08C    8B 47 1C                mov     eax, [edi+1Ch]
		// .text:1017EAB4 08C    8D 0C D5 00 00 00 00    lea     ecx, ds:0[ edx * 8 ]; Load Effective Address
		// .text:1017EABB 08C    2B CA                   sub     ecx, edx; Integer Subtraction
		// .text:1017EABD 08C    8B 80 70 29 00 00       mov     eax, [ eax + 2970h ]
		// .text:1017EAC3 08C    8D 34 C8                lea     esi, [ eax + ecx * 8 ]; Load Effective Address
		// .text:1017EAC6
		return get< C_AnimationLayer * >(g_csgo.AnimOverlay);
	}

	__forceinline float &m_flSpawnTime() {
		// .text:10381AB3 00C    F3 0F 10 49 10             movss   xmm1, dword ptr [ecx+10h] ; Move Scalar Single-FP
		// .text:10381AB8 00C    F3 0F 5C 88 90 A2 00 00    subss   xmm1, dword ptr[ eax + 0A290h ]; Scalar Single - FP Subtract
		return get< float >(g_csgo.SpawnTime);
	}

	__forceinline CBoneAccessor &m_BoneAccessor() {
		// .text:101A9253 1C4    C7 81 A0 26 00 00 00 FF 0F 00    mov     dword ptr[ ecx + 26A0h ], 0FFF00h
		// .text:101A925D 1C4    C7 81 9C 26 00 00 00 FF 0F 00    mov     dword ptr[ ecx + 269Ch ], 0FFF00h
		// .text:101A9267 1C4    8B 10                            mov     edx, [ eax ]
		// .text:101A9269 1C4    8D 81 94 26 00 00                lea     eax, [ ecx + 2694h ]; Load Effective Address
		// .text:101A926F 1C4    50                               push    eax
		return get< CBoneAccessor >(g_csgo.BoneAccessor);
	}

public:
	enum indices : size_t {
		GETREFEHANDLE = 2,
		TESTHITBOXES = 52,
		BUILDTRANSFORMATIONS = 184,
		DOEXTRABONEPROCESSING = 192,
		STANDARDBLENDINGRULES = 200,
		UPDATECLIENTSIDEANIMATION = 218, // 55 8B EC 51 56 8B F1 80 BE ? ? ? ? ? 74 36
		GETACTIVEWEAPON = 262,
		GETEYEPOS = 163,
		GETFOV = 321,
		UPDATECOLLISIONBOUNDS = 329 // 56 57 8B F9 8B 0D ? ? ? ? F6 87 ? ? ? ? ?
	};

public:
	// virtuals.
	__forceinline ulong_t GetRefEHandle() {
		using GetRefEHandle_t = ulong_t(__thiscall *)(decltype(this));
		return util::get_method< GetRefEHandle_t >(this, GETREFEHANDLE)(this);
	}

	__forceinline void BuildTransformations(CStudioHdr *hdr, vec3_t *pos, quaternion_t *q, const matrix3x4_t &transform, int mask, uint8_t *computed) {
		using BuildTransformations_t = void(__thiscall *)(decltype(this), CStudioHdr *, vec3_t *, quaternion_t *, matrix3x4_t const &, int, uint8_t *);
		return util::get_method< BuildTransformations_t >(this, BUILDTRANSFORMATIONS)(this, hdr, pos, q, transform, mask, computed);
	}

	__forceinline void StandardBlendingRules(CStudioHdr *hdr, vec3_t *pos, quaternion_t *q, float time, int mask) {
		using StandardBlendingRules_t = void(__thiscall *)(decltype(this), CStudioHdr *, vec3_t *, quaternion_t *, float, int);
		return util::get_method< StandardBlendingRules_t >(this, STANDARDBLENDINGRULES)(this, hdr, pos, q, time, mask);
	}

	__forceinline float GetFOV() {
		return util::get_method< float(__thiscall *)(decltype(this)) >(this, GETFOV)(this);
	}

	__forceinline const vec3_t &WorldSpaceCenter() {
		return util::get_method< const vec3_t &(__thiscall *)(void *) >(this, WORLDSPACECENTER)(this);
	}

	__forceinline void GetEyePos(vec3_t *pos) {
		util::get_method< void(__thiscall *)(decltype(this), vec3_t *) >(this, GETEYEPOS)(this, pos);
	}

	__forceinline void ModifyEyePosition(CCSGOPlayerAnimState *state, vec3_t *pos) {
		if (!state) {
			return;
		}

		//  if ( *(this + 0x50) && (*(this + 0x100) || *(this + 0x94) != 0.0 || !sub_102C9480(*(this + 0x50))) )
		if (state->m_player &&
			(state->m_land || state->m_player->m_flDuckAmount() != 0.f || !state->m_player->GetGroundEntity())) {
			auto v5 = 8;

			if (v5 != -1 && state->m_player->m_BoneCache().m_pCachedBones) {
				vec3_t head_pos(
					state->m_player->m_BoneCache().m_pCachedBones[8][0][3],
					state->m_player->m_BoneCache().m_pCachedBones[8][1][3],
					state->m_player->m_BoneCache().m_pCachedBones[8][2][3]);

				auto v12 = head_pos;
				auto v7 = v12.z + 1.7;

				auto v8 = pos->z;
				if (v8 > v7) // if (v8 > (v12 + 1.7))
				{
					float v13 = 0.f;
					float v3 = (*pos).z - v7;

					float v4 = (v3 - 4.f) * 0.16666667;
					if (v4 >= 0.f)
						v13 = std::fminf(v4, 1.f);

					(*pos).z = (((v7 - (*pos).z)) * (((v13 * v13) * 3.0) - (((v13 * v13) * 2.0) * v13))) + (*pos).z;
				}
			}
		}
	}

	__forceinline vec3_t GetShootPosition() {
		/*
		float *__thiscall sub_103A4A60(_DWORD *this, float *a2)
		{
			int v2; // edi
			_DWORD *v3; // ecx

			v2 = this;
			(*(*this + 652))(a2);
			if ( *(v2 + 0x39E1) )
			{
				v3 = *(v2 + 0x3874);
				if ( v3 )
					sub_103B4130(v3, a2);
				}
				return a2;
			}
		*/

		vec3_t pos;

		GetEyePos(&pos);

		if (*reinterpret_cast <int32_t *> (uintptr_t(this) + 0x39E1)) {
			auto v3 = m_PlayerAnimState();
			if (v3) {
				ModifyEyePosition(v3, &pos);
			}
		}

		return pos;
	}

	__forceinline void UpdateClientSideAnimation() {
		return util::get_method< void(__thiscall *)(decltype(this)) >(this, UPDATECLIENTSIDEANIMATION)(this);
	}

	__forceinline void UpdateCollisionBounds() {
		return util::get_method< void(__thiscall *)(decltype(this)) >(this, UPDATECOLLISIONBOUNDS)(this);
	}

	// misc funcs.
	__forceinline CStudioHdr *GetModelPtr() {
		using LockStudioHdr_t = void(__thiscall *)(decltype(this));

		if (!m_studioHdr())
			g_csgo.LockStudioHdr.as< LockStudioHdr_t >()(this);

		return m_studioHdr();
	}

	__forceinline Weapon *GetActiveWeapon() {
		return g_csgo.m_entlist->GetClientEntityFromHandle< Weapon * >(m_hActiveWeapon());
	}

	__forceinline Entity *GetObserverTarget() {
		return g_csgo.m_entlist->GetClientEntityFromHandle(m_hObserverTarget());
	}

	__forceinline Entity *GetGroundEntity() {
		return g_csgo.m_entlist->GetClientEntityFromHandle(m_hGroundEntity());
	}

	__forceinline void SetAnimLayers(C_AnimationLayer *layers) {
		std::memcpy(m_AnimOverlay(), layers, sizeof(C_AnimationLayer) * 13);
	}

	__forceinline void GetAnimLayers(C_AnimationLayer *layers) {
		std::memcpy(layers, m_AnimOverlay(), sizeof(C_AnimationLayer) * 13);
	}

	__forceinline void SetPoseParameters(float *poses) {
		std::memcpy(m_flPoseParameter(), poses, sizeof(float) * 24);
	}

	__forceinline void GetPoseParameters(float *poses) {
		std::memcpy(poses, m_flPoseParameter(), sizeof(float) * 24);
	}

	__forceinline bool ComputeHitboxSurroundingBox(vec3_t *mins, vec3_t *maxs) {
		using ComputeHitboxSurroundingBox_t = bool(__thiscall *)(void *, vec3_t *, vec3_t *);

		return g_csgo.ComputeHitboxSurroundingBox.as< ComputeHitboxSurroundingBox_t >()(this, mins, maxs);
	}

	__forceinline int GetSequenceActivity(int sequence) {
		using GetSequenceActivity_t = int(__fastcall *)(CStudioHdr *, int);

		return g_csgo.GetSequenceActivity.as< GetSequenceActivity_t >()(GetModelPtr(), sequence);
	}

	__forceinline bool HasC4() {
		using HasC4_t = bool(__thiscall *)(decltype(this));
		return g_csgo.HasC4.as< HasC4_t >()(this);
	}

	__forceinline void InvalidateBoneCache() {
		CBoneAccessor *accessor = &m_BoneAccessor();
		if (!accessor)
			return;

		accessor->m_WritableBones = 0;
		accessor->m_ReadableBones = 0;

		m_iMostRecentModelBoneCounter() = 0;
		m_flLastBoneSetupTime() = std::numeric_limits< float >::lowest();
	}

	__forceinline bool alive() {
		return m_lifeState() == LIFE_ALIVE;
	}

	__forceinline bool enemy(Player *from) {
		if (m_iTeamNum() != from->m_iTeamNum())
			return true;

		else if (g_csgo.mp_teammates_are_enemies->GetInt())
			return true;

		return false;
	}
};

class WeaponInfo {
private:
	PAD(0x4);											// 0x0000

public:
	const char *m_weapon_name;						// 0x0004 -- actual weapon name, even for usp-s and revolver. ex: "weapon_revolver"
	PAD(0xC);												// 0x0008
	int               m_max_clip1;							// 0x0014
	int				  m_max_clip2;							// 0x0018
	int				  m_default_clip1;						// 0x001C
	int		          m_default_clip2;						// 0x0020
	int               m_max_reserve;						// 0x0024
	PAD(0x4);												// 0x0028
	const char *m_world_model;						// 0x002C
	const char *m_view_model;							// 0x0030
	const char *m_world_dropped_model;				// 0x0034
	PAD(0x48);											// 0x0038
	const char *m_ammo_type;							// 0x0080
	uint8_t           pad_0084[4];						// 0x0084
	const char *m_sfui_name;							// 0x0088
	const char *m_deprecated_weapon_name;				// 0x008C -- shitty weapon name, shows "weapon_deagle" for revolver / etc.
	uint8_t           pad_0090[56];						// 0x0090
	CSWeaponType      m_weapon_type;						// 0x00C8
	int			      m_in_game_price;						// 0x00CC
	int               m_kill_award;							// 0x00D0
	const char *m_animation_prefix;					// 0x00D4
	float			  m_cycletime;							// 0x00D8
	float			  m_cycletime_alt;						// 0x00DC
	float			  m_time_to_idle;						// 0x00E0
	float			  m_idle_interval;						// 0x00E4
	bool			  m_is_full_auto;						// 0x00E5
	PAD(0x3);												// 0x00E8
	int               m_damage;								// 0x00EC
	float             m_armor_ratio;						// 0x00F0
	int               m_bullets;							// 0x00F4
	float             m_penetration;						// 0x00F8
	float             m_flinch_velocity_modifier_large;		// 0x00FC
	float             m_flinch_velocity_modifier_small;		// 0x0100
	float             m_range;								// 0x0104
	float             m_range_modifier;						// 0x0108
	float			  m_throw_velocity;						// 0x010C
	PAD(0xC);												// 0x0118
	bool			  m_has_silencer;						// 0x0119
	PAD(0x3);												// 0x011C
	const char *m_silencer_model;						// 0x0120
	int				  m_crosshair_min_distance;				// 0x0124
	int				  m_crosshair_delta_distance;			// 0x0128
	float             m_max_player_speed;					// 0x012C
	float             m_max_player_speed_alt;				// 0x0130
	float			  m_spread;								// 0x0134
	float			  m_spread_alt;							// 0x0138
	float             m_inaccuracy_crouch;					// 0x013C
	float             m_inaccuracy_crouch_alt;				// 0x0140
	float             m_inaccuracy_stand;					// 0x0144
	float             m_inaccuracy_stand_alt;				// 0x0148
	float             m_inaccuracy_jump_initial;			// 0x014C
	float             m_inaccuracy_jump;					// 0x0150
	float             m_inaccuracy_jump_alt;				// 0x0154
	float             m_inaccuracy_land;					// 0x0158
	float             m_inaccuracy_land_alt;				// 0x015C
	float             m_inaccuracy_ladder;					// 0x0160
	float             m_inaccuracy_ladder_alt;				// 0x0164
	float             m_inaccuracy_fire;					// 0x0168
	float             m_inaccuracy_fire_alt;				// 0x016C
	float             m_inaccuracy_move;					// 0x0170
	float             m_inaccuracy_move_alt;				// 0x0174
	float             m_inaccuracy_reload;					// 0x0178
	int               m_recoil_seed;						// 0x017C
	float			  m_recoil_angle;						// 0x0180
	float             m_recoil_angle_alt;					// 0x0184
	float             m_recoil_angle_variance;				// 0x0188
	float             m_recoil_angle_variance_alt;			// 0x018C
	float             m_recoil_magnitude;					// 0x0190
	float             m_recoil_magnitude_alt;				// 0x0194
	float             m_recoil_magnitude_variance;			// 0x0198
	float             m_recoil_magnitude_variance_alt;		// 0x019C
	float             m_recovery_time_crouch;				// 0x01A0
	float             m_recovery_time_stand;				// 0x01A4
	float             m_recovery_time_crouch_final;			// 0x01A8
	float             m_recovery_time_stand_final;			// 0x01AC
	float             m_recovery_transition_start_bullet;	// 0x01B0
	float             m_recovery_transition_end_bullet;		// 0x01B4
	bool			  m_unzoom_after_shot;					// 0x01B5
	PAD(0x3);												// 0x01B8
	bool		      m_hide_view_model_zoomed;				// 0x01B9
	bool			  m_zoom_levels;						// 0x01BA
	PAD(0x2);												// 0x01BC
	int				  m_zoom_fov[2];						// 0x01C4
	float			  m_zoom_time[3];						// 0x01D0
	PAD(0x8);												// 0x01D8
	float             m_addon_scale;						// 0x01DC
	PAD(0x8);												// 0x01E4
	int				  m_tracer_frequency;					// 0x01E8
	int				  m_tracer_frequency_alt;				// 0x01EC
	PAD(0x18);											// 0x0200
	int				  m_health_per_shot;					// 0x0204
	PAD(0x8);												// 0x020C
	float			  m_inaccuracy_pitch_shift;				// 0x0210
	float			  m_inaccuracy_alt_sound_threshold;		// 0x0214
	float			  m_bot_audible_range;					// 0x0218
	PAD(0x8);												// 0x0220
	const char *m_wrong_team_msg;						// 0x0224
	bool			  m_has_burst_mode;						// 0x0225
	PAD(0x3);												// 0x0228
	bool			  m_is_revolver;						// 0x0229
	bool			  m_can_shoot_underwater;				// 0x022A
	PAD(0x2);												// 0x022C			
};

class IRefCounted {
private:
	volatile long refCount;

public:
	virtual void destructor(char bDelete) = 0;
	virtual bool OnFinalRelease() = 0;

	void unreference() {
		if (InterlockedDecrement(&refCount) == 0 && OnFinalRelease()) {
			destructor(1);
		}
	}
};

class Weapon : public Entity {
public:
	using ref_vec_t = CUtlVector< IRefCounted * >;

	// netvars / etc.
	__forceinline ref_vec_t &m_CustomMaterials() {
		return get< ref_vec_t >(g_entoffsets.m_CustomMaterials);
	}

	__forceinline ref_vec_t &m_CustomMaterials2() {
		return get< ref_vec_t >(g_entoffsets.m_CustomMaterials2);
	}

	__forceinline ref_vec_t &m_VisualsDataProcessors() {
		return get< ref_vec_t >(g_entoffsets.m_VisualsDataProcessors);
	}

	__forceinline bool &m_bCustomMaterialInitialized() {
		return get< bool >(g_entoffsets.m_bCustomMaterialInitialized);
	}

	__forceinline int &m_iItemDefinitionIndex() {
		return get< int >(g_entoffsets.m_iItemDefinitionIndex);
	}

	__forceinline int &m_iClip1() {
		return get< int >(g_entoffsets.m_iClip1);
	}

	__forceinline int &m_iPrimaryReserveAmmoCount() {
		return get< int >(g_entoffsets.m_iPrimaryReserveAmmoCount);
	}

	__forceinline int &m_Activity() {
		return get< int >(g_entoffsets.m_Activity);
	}

	__forceinline float &m_fFireDuration() {
		return get< float >(g_entoffsets.m_fFireDuration);
	}

	__forceinline int &m_iBurstShotsRemaining() {
		return get< int >(g_entoffsets.m_iBurstShotsRemaining);
	}

	__forceinline float &m_flNextPrimaryAttack() {
		return get< float >(g_entoffsets.m_flNextPrimaryAttack);
	}

	__forceinline float &m_flNextSecondaryAttack() {
		return get< float >(g_entoffsets.m_flNextSecondaryAttack);
	}

	__forceinline float &m_flThrowStrength() {
		return get< float >(g_entoffsets.m_flThrowStrength);
	}

	__forceinline float &m_fNextBurstShot() {
		return get< float >(g_entoffsets.m_fNextBurstShot);
	}

	__forceinline int &m_zoomLevel() {
		return get< int >(g_entoffsets.m_zoomLevel);
	}

	__forceinline float &m_flRecoilIndex() {
		return get< float >(g_entoffsets.m_flRecoilIndex);
	}

	__forceinline int &m_weaponMode() {
		return get< int >(g_entoffsets.m_weaponMode);
	}

	__forceinline int &m_nFallbackPaintKit() {
		return get< int >(g_entoffsets.m_nFallbackPaintKit);
	}

	__forceinline int &m_nFallbackStatTrak() {
		return get< int >(g_entoffsets.m_nFallbackStatTrak);
	}

	__forceinline int &m_nFallbackSeed() {
		return get< int >(g_entoffsets.m_nFallbackSeed);
	}

	__forceinline float &m_flFallbackWear() {
		return get< float >(g_entoffsets.m_flFallbackWear);
	}

	__forceinline int &m_iViewModelIndex() {
		return get< int >(g_entoffsets.m_iViewModelIndex);
	}

	__forceinline int &m_iWorldModelIndex() {
		return get< int >(g_entoffsets.m_iWorldModelIndex);
	}

	__forceinline int &m_iAccountID() {
		return get< int >(g_entoffsets.m_iAccountID);
	}

	__forceinline int &m_iItemIDHigh() {
		return get< int >(g_entoffsets.m_iItemIDHigh);
	}

	__forceinline int &m_iEntityQuality() {
		return get< int >(g_entoffsets.m_iEntityQuality);
	}

	__forceinline int &m_OriginalOwnerXuidLow() {
		return get< int >(g_entoffsets.m_OriginalOwnerXuidLow);
	}

	__forceinline int &m_OriginalOwnerXuidHigh() {
		return get< int >(g_entoffsets.m_OriginalOwnerXuidHigh);
	}

	__forceinline bool &m_bPinPulled() {
		return get< bool >(g_entoffsets.m_bPinPulled);
	}

	__forceinline float &m_fThrowTime() {
		return get< float >(g_entoffsets.m_fThrowTime);
	}

	__forceinline EHANDLE &m_hWeapon() {
		return get< EHANDLE >(g_entoffsets.m_hWeapon);
	}

	__forceinline EHANDLE &m_hWeaponWorldModel() {
		return get< EHANDLE >(g_entoffsets.m_hWeaponWorldModel);
	}

	__forceinline EHANDLE &m_hOwnerEntity() {
		return get< EHANDLE >(g_entoffsets.m_hOwnerEntity);
	}

	__forceinline float &m_flConstraintRadius() {
		return get< float >(g_entoffsets.m_flConstraintRadius);
	}

	__forceinline float &m_fLastShotTime() {
		return get< float >(g_entoffsets.m_fLastShotTime);
	}

public:
	enum indices : size_t {
		SETMODELINDEX = 75,
		GETMAXCLIP1 = 367,
		GETSPREAD = 439,
		GETWPNDATA = 446, // C_WeaponCSBaseGun::GetCSWpnData
		GETINACCURACY = 469,
		UPDATEACCURACYPENALTY = 471,
	};

public:
	// virtuals.
	__forceinline int GetMaxClip1() {
		return util::get_method< int(__thiscall *)(void *) >(this, GETMAXCLIP1)(this);
	}

	__forceinline void SetGloveModelIndex(int index) {
		return util::get_method< void(__thiscall *)(void *, int) >(this, SETMODELINDEX)(this, index);
	}

	__forceinline WeaponInfo *GetWpnData() {
		return util::get_method< WeaponInfo *(__thiscall *)(void *) >(this, GETWPNDATA)(this);
	}

	__forceinline float GetInaccuracy() {
		return util::get_method< float(__thiscall *)(void *) >(this, GETINACCURACY)(this);
	}

	__forceinline float GetSpread() {
		return util::get_method< float(__thiscall *)(void *) >(this, GETSPREAD)(this);
	}

	__forceinline void UpdateAccuracyPenalty() {
		return util::get_method< void(__thiscall *)(void *) >(this, UPDATEACCURACYPENALTY)(this);
	}

	// misc funcs.
	__forceinline Weapon *GetWeapon() {
		return g_csgo.m_entlist->GetClientEntityFromHandle< Weapon * >(m_hWeapon());
	}

	__forceinline Weapon *GetWeaponWorldModel() {
		return g_csgo.m_entlist->GetClientEntityFromHandle< Weapon * >(m_hWeaponWorldModel());
	}

	__forceinline bool IsKnife() {
		return (GetWpnData()->m_weapon_type == WEAPONTYPE_KNIFE && m_iItemDefinitionIndex() != ZEUS);
	}

	__forceinline vec3_t CalculateSpread(int seed, float inaccuracy, float spread, bool revolver2 = false) {
		WeaponInfo *wep_info;
		int        item_def_index;
		float      recoil_index, r1, r2, r3, r4, s1, c1, s2, c2;

		// if we have no bullets, we have no spread.
		wep_info = GetWpnData();
		if (!wep_info || !wep_info->m_bullets)
			return {};

		// get some data for later.
		item_def_index = m_iItemDefinitionIndex();
		recoil_index = m_flRecoilIndex();

		// seed randomseed.
		g_csgo.RandomSeed((seed & 0xff) + 1);

		// generate needed floats.
		r1 = g_csgo.RandomFloat(0.f, 1.f);
		r2 = g_csgo.RandomFloat(0.f, math::pi_2);

		// todo - dex; need to make sure this is right for shotguns still.
		//             the 3rd arg to get_shotgun_spread is actually using the bullet iterator
		//             should also probably check for if the weapon is a shotgun, but it seems like GetShotgunSpread modifies some the r1 - r4 vars...
		// for( int i{}; i < wep_info->m_bullets; ++i )
		/*
			// shotgun shit, or first bullet
			if ( !bullet_i
			  || ((int (__thiscall *)(void ***))weapon_accuracy_shotgun_spread_patterns[13])(&weapon_accuracy_shotgun_spread_patterns) )
			{
			  r1 = RandomFloat(0, 0x3F800000);// rand 0.f, 1.f
			  r2 = RandomFloat(0, 0x40C90FDB);// rand 0.f, pi * 2.f
			  v47 = *(_DWORD *)v45;
			  r2_ = r2;
			  v48 = (*(int (__thiscall **)(int))(v47 + 48))(v45);

			  // not revolver?
			  if ( v48 != sub_101D9B10(&dword_14FA0DE0) || a7 != 1 )
			  {

				// not negev?
				v50 = (*(int (__thiscall **)(int))(*(_DWORD *)v45 + 48))(v45);
				if ( v50 != sub_101D9B10(&dword_14FA0DEC) || recoil_index >= 3.0 )
				{
				  r1_ = r1;
				}
				else
				{
				  r1__ = r1;
				  recoil_index_it1 = 3;
				  do
				  {
					--recoil_index_it1;
					r1__ = r1__ * r1__;
				  }
				  while ( (float)recoil_index_it1 > recoil_index );
				  r1_ = 1.0 - r1__;
				}
			  }
			  else
			  {
				r1_ = 1.0 - (float)(r1 * r1);
			  }

			  // some convar stuff / etc
			  if ( max_inaccuracy )
				r1_ = 1.0;

			  bullet_i = v87;
			  bullet_i1 = r1_ * v104;

			  if ( only_up_is_not_0 )
				v53 = 1.5707964;
			  else
				v53 = r2_;

			  r2_ = v53;
			}

			if ( ((int (__thiscall *)(void ***))weapon_accuracy_shotgun_spread_patterns[13])(&weapon_accuracy_shotgun_spread_patterns) )
			{
			  null0 = v54;
			  m_iItemDefinitionIndex = (**(int (***)(void))LODWORD(v88))();
			  get_shotgun_spread(
				m_iItemDefinitionIndex,
				null0,
				bullet_i + m_BulletsPerShot * (signed int)recoil_index,
				&r4,
				&r3);
			}
			else
			{
			  r3 = RandomFloat(0, 0x3F800000);// rand 0.f, 1.f
			  r4 = RandomFloat(0, 0x40C90FDB);// rand 0.f, pi * 2.f
			}
		*/

		if ( /*wep_info->m_weapon_type == WEAPONTYPE_SHOTGUN &&*/ g_csgo.weapon_accuracy_shotgun_spread_patterns->GetInt() > 0)
			g_csgo.GetShotgunSpread(item_def_index, 0, 0 /*bullet_i*/ + wep_info->m_bullets * recoil_index, &r4, &r3);

		else {
			r3 = g_csgo.RandomFloat(0.f, 1.f);
			r4 = g_csgo.RandomFloat(0.f, math::pi_2);
		}

		// revolver secondary spread.
		if (item_def_index == REVOLVER && revolver2) {
			r1 = 1.f - (r1 * r1);
			r3 = 1.f - (r3 * r3);
		}

		// negev spread.
		else if (item_def_index == NEGEV && recoil_index < 3.f) {
			for (int i{ 3 }; i > recoil_index; --i) {
				r1 *= r1;
				r3 *= r3;
			}

			r1 = 1.f - r1;
			r3 = 1.f - r3;
		}

		// get needed sine / cosine values.
		c1 = std::cos(r2);
		c2 = std::cos(r4);
		s1 = std::sin(r2);
		s2 = std::sin(r4);

		// calculate spread vector.
		return {
			(c1 * (r1 * inaccuracy)) + (c2 * (r3 * spread)),
			(s1 * (r1 * inaccuracy)) + (s2 * (r3 * spread)),
			0.f
		};
	}

	__forceinline vec3_t CalculateSpread(int seed, bool revolver2 = false) {
		return CalculateSpread(seed, GetInaccuracy(), GetSpread(), revolver2);
	}

	__forceinline std::string GetLocalizedName() {
		C_EconItemView *item_view;
		CEconItemDefinition *item_def;

		item_view = g_csgo.GetEconItemView(this);
		if (!item_view)
			return XOR("error");

		item_def = g_csgo.GetStaticData(item_view);
		if (!item_def)
			return XOR("error");

		return util::WideToMultiByte(g_csgo.m_localize->Find(item_def->GetItemBaseName()));
	}
};

class CTraceFilterSimple_game {
public:
	void *m_vmt;
	const Entity *m_pass_ent1;
	int             m_collision_group;
	ShouldHitFunc_t m_shouldhit_check_fn;

public:
	__forceinline CTraceFilterSimple_game() :
		m_vmt{ g_csgo.CTraceFilterSimple_vmt.as< void * >() },
		m_pass_ent1{},
		m_collision_group{},
		m_shouldhit_check_fn{} {}

	__forceinline CTraceFilterSimple_game(const Entity *pass_ent1, int collision_group = COLLISION_GROUP_NONE, ShouldHitFunc_t shouldhit_check_fn = nullptr) :
		m_vmt{ g_csgo.CTraceFilterSimple_vmt.as< void * >() },
		m_pass_ent1{ pass_ent1 },
		m_collision_group{ collision_group },
		m_shouldhit_check_fn{ shouldhit_check_fn } {}

	__forceinline bool ShouldHitEntity(Entity *entity, int contents_mask) {
		// note - dex; game is dumb, this gets the real vmt.
		void *real_vmt = *(void **)m_vmt;

		return util::get_method< bool(__thiscall *)(void *, Entity *, int) >(real_vmt, 0)(real_vmt, entity, contents_mask);
	}

	// note - dex; don't really care about calling the virtuals for these two functions, they only set members in the class for us.
	__forceinline void SetPassEntity(Entity *pass_ent1) {
		m_pass_ent1 = pass_ent1;

		// util::get_method< void (__thiscall *)( void *, Entity* ) >( m_vmt, 2 )( m_vmt, pass_ent1 );
	}

	__forceinline void SetCollisionGroup(int collision_group) {
		m_collision_group = collision_group;

		// util::get_method< void (__thiscall *)( void *, int ) >( m_vmt, 3 )( m_vmt, collision_group );
	}
};

class CTraceFilterSkipTwoEntities_game {
public:
	void *m_vmt;
	const Entity *m_pass_ent1;
	int             m_collision_group;
	ShouldHitFunc_t m_shouldhit_check_fn;
	const Entity *m_pass_ent2;

public:
	__forceinline CTraceFilterSkipTwoEntities_game() :
		m_vmt{ g_csgo.CTraceFilterSkipTwoEntities_vmt.as< void * >() },
		m_pass_ent1{},
		m_collision_group{},
		m_shouldhit_check_fn{},
		m_pass_ent2{} {}

	__forceinline CTraceFilterSkipTwoEntities_game(const Entity *pass_ent1, const Entity *pass_ent2, int collision_group = COLLISION_GROUP_NONE, ShouldHitFunc_t shouldhit_check_fn = nullptr) :
		m_vmt{ g_csgo.CTraceFilterSimple_vmt.as< void * >() },
		m_pass_ent1{ pass_ent1 },
		m_collision_group{ collision_group },
		m_shouldhit_check_fn{ shouldhit_check_fn },
		m_pass_ent2{ pass_ent2 } {}

	__forceinline bool ShouldHitEntity(Entity *entity, int contents_mask) {
		// note - dex; game is dumb, this gets the real vmt.
		void *real_vmt = *(void **)m_vmt;

		return util::get_method< bool(__thiscall *)(void *, Entity *, int) >(m_vmt, 0)(m_vmt, entity, contents_mask);
	}

	// note - dex; don't really care about calling the virtuals for these two functions, they only set members in the class for us.
	__forceinline void SetPassEntity(Entity *pass_ent1) {
		m_pass_ent1 = pass_ent1;

		// util::get_method< void (__thiscall *)( void *, Entity* ) >( m_vmt, 2 )( m_vmt, pass_ent1 );
	}

	__forceinline void SetCollisionGroup(int collision_group) {
		m_collision_group = collision_group;

		// util::get_method< void (__thiscall *)( void *, int ) >( m_vmt, 3 )( m_vmt, collision_group );
	}

	__forceinline void SetPassEntity2(Entity *pass_ent2) {
		m_pass_ent2 = pass_ent2;
		// util::get_method< void (__thiscall *)( void *, Entity* ) >( m_vmt, 4 )( m_vmt, pass_ent2 );
	}
};