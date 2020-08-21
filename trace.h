#pragma once

using ShouldHitFunc_t = bool (__cdecl *)( Entity *, int );

enum {
	CHAR_TEX_ANTLION     = 'A',
	CHAR_TEX_BLOODYFLESH = 'B',
	CHAR_TEX_CONCRETE    = 'C',
	CHAR_TEX_DIRT        = 'D',
	CHAR_TEX_EGGSHELL    = 'E',
	CHAR_TEX_FLESH       = 'F',
	CHAR_TEX_GRATE       = 'G',
	CHAR_TEX_ALIENFLESH  = 'H',
	CHAR_TEX_CLIP        = 'I',
	CHAR_TEX_PLASTIC     = 'L',
	CHAR_TEX_METAL       = 'M',
	CHAR_TEX_SAND        = 'N',
	CHAR_TEX_FOLIAGE     = 'O',
	CHAR_TEX_COMPUTER    = 'P',
	CHAR_TEX_SLOSH       = 'S',
	CHAR_TEX_TILE        = 'T',
	CHAR_TEX_CARDBOARD   = 'U',
	CHAR_TEX_VENT        = 'V',
	CHAR_TEX_WOOD        = 'W',
	CHAR_TEX_GLASS       = 'Y',
	CHAR_TEX_WARPSHIELD  = 'Z',
};

// m_takeDamage
enum {
	DAMAGE_NO          = 0,
	DAMAGE_EVENTS_ONLY = 1,
	DAMAGE_YES         = 2,
	DAMAGE_AIM         = 3,
};

enum Collision_Group_t {
	COLLISION_GROUP_NONE = 0,
	COLLISION_GROUP_DEBRIS,
	COLLISION_GROUP_DEBRIS_TRIGGER,
	COLLISION_GROUP_INTERACTIVE_DEBRIS,
	COLLISION_GROUP_INTERACTIVE,
	COLLISION_GROUP_PLAYER,
	COLLISION_GROUP_BREAKABLE_GLASS,
	COLLISION_GROUP_VEHICLE,
	COLLISION_GROUP_PLAYER_MOVEMENT,
	COLLISION_GROUP_NPC,
	COLLISION_GROUP_IN_VEHICLE,
	COLLISION_GROUP_WEAPON,
	COLLISION_GROUP_VEHICLE_CLIP,
	COLLISION_GROUP_PROJECTILE,
	COLLISION_GROUP_DOOR_BLOCKER,
	COLLISION_GROUP_PASSABLE_DOOR,
	COLLISION_GROUP_DISSOLVING,
	COLLISION_GROUP_PUSHAWAY,
	COLLISION_GROUP_NPC_ACTOR,
	COLLISION_GROUP_NPC_SCRIPTED,
	COLLISION_GROUP_PZ_CLIP,
	COLLISION_GROUP_DEBRIS_BLOCK_PROJECTILE,
	LAST_SHARED_COLLISION_GROUP
};

enum TraceType_t {
	TRACE_EVERYTHING = 0,
	TRACE_WORLD_ONLY,
	TRACE_ENTITIES_ONLY,
	TRACE_EVERYTHING_FILTER_PROPS
};

enum Contents_t {
	CONTENTS_EMPTY                = 0,
	CONTENTS_SOLID                = 0x1,
	CONTENTS_WINDOW               = 0x2,
	CONTENTS_AUX                  = 0x4,
	CONTENTS_GRATE                = 0x8,
	CONTENTS_SLIME                = 0x10,
	CONTENTS_WATER                = 0x20,
	CONTENTS_BLOCKLOS             = 0x40,
	CONTENTS_OPAQUE               = 0x80,
	CONTENTS_TESTFOGVOLUME        = 0x100,
	CONTENTS_UNUSED               = 0x200,
	CONTENTS_BLOCKLIGHT           = 0x400,
	CONTENTS_TEAM1                = 0x800,
	CONTENTS_TEAM2                = 0x1000,
	CONTENTS_IGNORE_NODRAW_OPAQUE = 0x2000,
	CONTENTS_MOVEABLE             = 0x4000,
	CONTENTS_AREAPORTAL           = 0x8000,
	CONTENTS_PLAYERCLIP           = 0x10000,
	CONTENTS_MONSTERCLIP          = 0x20000,
	CONTENTS_CURRENT_0            = 0x40000,
	CONTENTS_CURRENT_90           = 0x80000,
	CONTENTS_CURRENT_180          = 0x100000,
	CONTENTS_CURRENT_270          = 0x200000,
	CONTENTS_CURRENT_UP           = 0x400000,
	CONTENTS_CURRENT_DOWN         = 0x800000,
	CONTENTS_ORIGIN               = 0x1000000,
	CONTENTS_MONSTER              = 0x2000000,
	CONTENTS_DEBRIS               = 0x4000000,
	CONTENTS_DETAIL               = 0x8000000,
	CONTENTS_TRANSLUCENT          = 0x10000000,
	CONTENTS_LADDER               = 0x20000000,
	CONTENTS_HITBOX               = 0x40000000,
};

enum Masks_t {
	MASK_ALL                   = 0xFFFFFFFF,
	MASK_SOLID                 = CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_WINDOW | CONTENTS_MONSTER | CONTENTS_GRATE,
	MASK_PLAYERSOLID           = CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_PLAYERCLIP | CONTENTS_WINDOW | CONTENTS_MONSTER | CONTENTS_GRATE,
	MASK_NPCSOLID              = CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_MONSTERCLIP | CONTENTS_WINDOW | CONTENTS_MONSTER | CONTENTS_GRATE,
	MASK_NPCFLUID              = CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_MONSTERCLIP | CONTENTS_WINDOW | CONTENTS_MONSTER | CONTENTS_GRATE,
	MASK_WATER                 = CONTENTS_WATER | CONTENTS_MOVEABLE | CONTENTS_SLIME,
	MASK_OPAQUE                = CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_OPAQUE,
	MASK_OPAQUE_AND_NPCS       = MASK_OPAQUE | CONTENTS_MONSTER,
	MASK_BLOCKLOS              = CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_BLOCKLOS,
	MASK_BLOCKLOS_AND_NPCS     = MASK_BLOCKLOS | CONTENTS_MONSTER,
	MASK_VISIBLE               = MASK_OPAQUE | CONTENTS_IGNORE_NODRAW_OPAQUE,
	MASK_VISIBLE_AND_NPCS      = MASK_OPAQUE_AND_NPCS | CONTENTS_IGNORE_NODRAW_OPAQUE,
	MASK_SHOT                  = CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_MONSTER | CONTENTS_WINDOW | CONTENTS_DEBRIS | CONTENTS_GRATE | CONTENTS_HITBOX,
	MASK_SHOT_BRUSHONLY        = CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_WINDOW | CONTENTS_DEBRIS,
	MASK_SHOT_HULL             = CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_MONSTER | CONTENTS_WINDOW | CONTENTS_DEBRIS | CONTENTS_GRATE,
	MASK_SHOT_PORTAL           = CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_WINDOW | CONTENTS_MONSTER,
	MASK_SOLID_BRUSHONLY       = CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_WINDOW | CONTENTS_GRATE,
	MASK_PLAYERSOLID_BRUSHONLY = CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_WINDOW | CONTENTS_PLAYERCLIP | CONTENTS_GRATE,
	MASK_NPCSOLID_BRUSHONLY    = CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_WINDOW | CONTENTS_MONSTERCLIP | CONTENTS_GRATE,
	MASK_NPCWORLDSTATIC        = CONTENTS_SOLID | CONTENTS_WINDOW | CONTENTS_MONSTERCLIP | CONTENTS_GRATE,
	MASK_NPCWORLDSTATIC_FLUID  = CONTENTS_SOLID | CONTENTS_WINDOW | CONTENTS_MONSTERCLIP,
	MASK_SPLITAREPORTAL        = CONTENTS_WATER | CONTENTS_SLIME,
	MASK_CURRENT               = CONTENTS_CURRENT_0 | CONTENTS_CURRENT_90 | CONTENTS_CURRENT_180 | CONTENTS_CURRENT_270 | CONTENTS_CURRENT_UP | CONTENTS_CURRENT_DOWN,
	MASK_DEADSOLID             = CONTENTS_SOLID | CONTENTS_PLAYERCLIP | CONTENTS_WINDOW | CONTENTS_GRATE,
};

enum {
	SURF_LIGHT     = 0x0001,
	SURF_SKY2D     = 0x0002,
	SURF_SKY       = 0x0004,
	SURF_WARP      = 0x0008,
	SURF_TRANS     = 0x0010,
	SURF_NOPORTAL  = 0x0020,
	SURF_TRIGGER   = 0x0040,
	SURF_NODRAW    = 0x0080,
	SURF_HINT      = 0x0100,
	SURF_SKIP      = 0x0200,
	SURF_NOLIGHT   = 0x0400,
	SURF_BUMPLIGHT = 0x0800,
	SURF_NOSHADOWS = 0x1000,
	SURF_NODECALS  = 0x2000,
	SURF_NOPAINT   = SURF_NODECALS,
	SURF_NOCHOP    = 0x4000,
	SURF_HITBOX    = 0x8000
};

enum SurfaceFlags_t {
	DISPSURF_FLAG_SURFACE   = ( 1 << 0 ),
	DISPSURF_FLAG_WALKABLE  = ( 1 << 1 ),
	DISPSURF_FLAG_BUILDABLE = ( 1 << 2 ),
	DISPSURF_FLAG_SURFPROP1 = ( 1 << 3 ),
	DISPSURF_FLAG_SURFPROP2 = ( 1 << 4 ),
};

struct BoxTraceInfo_t {
    float m_t1;
    float m_t2;
    int   m_hitside;
    bool  m_startsolid;

    __forceinline BoxTraceInfo_t( ) : m_t1{ -1.f }, m_t2{ 1.f }, m_hitside{ -1 }, m_startsolid{ true } {}
};

struct cplane_t {
	vec3_t       m_normal;
	float       m_dist;
	uint8_t     m_type;
	uint8_t     m_sign_bits;
	PAD( 0x2 );
};

struct csurface_t {
	const char* m_name;
	short       m_surface_props;
	uint16_t    m_flags;
};

struct CBaseTrace {
	vec3_t   m_startpos;
	vec3_t   m_endpos;
	cplane_t m_plane;
	float    m_fraction;
	int      m_contents;
	uint16_t m_displacement_flags;
	bool     m_allsolid;
	bool     m_startsolid;
};

class CGameTrace : public CBaseTrace {
public:
	float      m_fraction_left_solid;
	csurface_t m_surface;
	int        m_hitgroup;
	short      m_physicsbone;
	uint16_t   m_wold_surface_index;
	Entity*    m_entity;
	int        m_hitbox;

	__forceinline bool hit( ) const {
		return m_fraction < 1.f || m_allsolid || m_startsolid;
	}
};

class Ray {
public:
	__forceinline Ray( ) : m_world_axis_transform{}, m_is_ray{}, m_is_swept{} {}

	__forceinline Ray( const vec3_t &start, const vec3_t &end ) {
		m_delta                = vec_aligned_t{ end - start };
		m_is_swept             = m_delta.length_sqr( ) != 0.f;
		m_world_axis_transform = nullptr;
		m_is_ray               = true;
		m_start                = start;
		m_start_offset.clear( );
		m_extents.clear( );
	}

	__forceinline Ray( const vec3_t& start, const vec3_t& end, const vec3_t& mins, const vec3_t& maxs ) {
		m_delta                = vec_aligned_t{ end - start };
		m_world_axis_transform = nullptr;
		m_is_swept             = m_delta.length_sqr( ) != 0.f;
		m_extents              = vec_aligned_t{ maxs - mins };
		m_extents              *= 0.5f;
		m_is_ray               = m_extents.length_sqr( ) < 1e-6;
		m_start_offset         = vec_aligned_t{ mins + maxs };
		m_start_offset         *= 0.5f;
		m_start                = vec_aligned_t{ start + m_start_offset };
		m_start_offset         *= -1.f;
	}

public:
	vec_aligned_t      m_start;
	vec_aligned_t      m_delta;
	vec_aligned_t	   m_start_offset;
	vec_aligned_t	   m_extents;
	const matrix3x4_t* m_world_axis_transform;
	bool               m_is_ray;
	bool               m_is_swept;
};

class ITraceFilter {
public:
	virtual bool        ShouldHitEntity( Entity *pEntity, int contents_mask ) = 0;
	virtual TraceType_t	GetTraceType( ) const = 0;
};

class CTraceFilter : public ITraceFilter {
public:
	virtual TraceType_t	GetTraceType( ) const {
        return TRACE_EVERYTHING;
	}
};

class CTraceFilterSimple : public CTraceFilter {
public:
	const Entity*   m_pass_ent1;
	int             m_collision_group;
	ShouldHitFunc_t m_shouldhit_check_fn;

public:
    __forceinline CTraceFilterSimple() {}

	__forceinline CTraceFilterSimple( const Entity* pass_ent1, int collision_group = COLLISION_GROUP_NONE, ShouldHitFunc_t shouldhit_check_fn = nullptr ) :
        m_pass_ent1{ pass_ent1 },
        m_collision_group{ collision_group },
        m_shouldhit_check_fn{ shouldhit_check_fn } {}
    
	virtual bool ShouldHitEntity( Entity* entity, int contents_mask ) {
        return entity != m_pass_ent1;
	}

    virtual void SetPassEntity( Entity *pass_ent1 ) { 
        m_pass_ent1 = pass_ent1; 
    }

	virtual void SetCollisionGroup( int collision_group ) { 
        m_collision_group = collision_group; 
    }
};

class CTraceFilterSkipTwoEntities : public CTraceFilterSimple {
public:
    const Entity* m_pass_ent2;

public:
    __forceinline CTraceFilterSkipTwoEntities( const Entity* pass_ent1, const Entity* pass_ent2, int collision_group = COLLISION_GROUP_NONE, ShouldHitFunc_t shouldhit_check_fn = nullptr ) :
        m_pass_ent2{ pass_ent2 },
        CTraceFilterSimple( pass_ent1, collision_group, shouldhit_check_fn ) {}
    
	virtual bool ShouldHitEntity( Entity* entity, int contents_mask ) {
        return entity != m_pass_ent1;
	}

    virtual void SetPassEntity2( Entity *pass_ent2 ) { 
        m_pass_ent2 = pass_ent2; 
    }
};

class CTraceFilterWorldOnly : public ITraceFilter {
public:
    virtual bool ShouldHitEntity( Entity* entity, int contents_mask ) {
        return false;
	}

    virtual TraceType_t	GetTraceType( ) const {
		return TRACE_WORLD_ONLY;
	}
};

//// trace filter with lambda callback, allows for custom 'ShouldHit' implementations
//class CallbackTraceFilter : public CTraceFilter {
//	using Callback_t = std::function< bool( Entity*, int ) >;
//
//public:
//	__forceinline CallbackTraceFilter( TraceType_t type, Callback_t callback ) : m_callback{ callback } {
//		m_type = type;
//	}
//
//	__forceinline bool ShouldHitEntity( Entity* entity, int mask ) override {
//		return m_callback( entity, mask );
//	}
//
//private:
//	Callback_t m_callback;
//};

struct surfacephysicsparams_t {
	float m_friction;
	float m_elasticity;
	float m_density;
	float m_thickness;
	float m_dampening;
};

struct surfaceaudioparams_t {
	float m_audio_reflectivity;
	float m_audio_hardness_factor;
	float m_audio_roughness_factor;
	float m_scrape_rough_threshold;
	float m_impact_hard_threshold;
	float m_audio_hard_min_velocity;
	float m_high_pitch_occlusion;
	float m_mid_pitch_occlusion;
	float m_low_pitch_occlusion;
};

struct surfacegameprops_t {
	float    m_max_speed_factor;
	float    m_jump_factor;
	float    m_penetration_modifier;
	float    m_damage_modifier;
	uint16_t m_material;
	uint8_t  m_climbable;
};

struct surfacesoundnames_t {
	short m_walk_left;
	short m_walk_right;
	short m_run_left;
	short m_run_right;
	short m_impact_soft;
	short m_impact_hard;
	short m_scrape_smooth;
	short m_scrape_rough;
	short m_bullet_impact;
	short m_rolling;
	short m_break_sound;
	short m_strain;
};

struct surfacedata_t {
	surfacephysicsparams_t m_physics;
	surfaceaudioparams_t   m_audio;
	surfacesoundnames_t    m_sounds;
	surfacegameprops_t     m_game;
	PAD( 48 );
}; // size = 0x94

class IPhysicsSurfaceProps {
public:
	__forceinline surfacedata_t* GetSurfaceData( int surfaceDataIndex ) {
		return util::get_method< surfacedata_t*( __thiscall* )( decltype( this ), int ) >( this, 5 )( this, surfaceDataIndex );
	}
};

class IEngineTrace {
	enum indices : size_t {
		GETPOINTCONTENTS = 0,
		CLIPRAYTOENTITY  = 3,
		TRACERAY         = 5,
	};

public:
	__forceinline int GetPointContents( const vec3_t& position, int mask = MASK_ALL, void** entity = nullptr ) {
		return util::get_method< int( __thiscall* )( decltype( this ), const vec3_t&, int, void** ) >( this, GETPOINTCONTENTS )( this, position, mask, entity );
	}

	__forceinline void ClipRayToEntity( const Ray& ray, uint32_t mask, Entity* entity, CGameTrace* trace ) {
		return util::get_method< void( __thiscall* )( decltype( this ), const Ray&, uint32_t, Entity*, CGameTrace* ) >( this, CLIPRAYTOENTITY )( this, ray, mask, entity, trace );
	}

	__forceinline void TraceRay( const Ray& ray, uint32_t mask, ITraceFilter* filter, CGameTrace* trace ) {
		return util::get_method< void( __thiscall* )( decltype( this ), const Ray&, uint32_t, ITraceFilter*, CGameTrace* ) >( this, TRACERAY )( this, ray, mask, filter, trace );
	}
};