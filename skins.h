#pragma once

constexpr int sequence_default_draw = 0;
constexpr int sequence_default_idle1 = 1;
constexpr int sequence_default_idle2 = 2;
constexpr int sequence_default_heavy_miss1 = 9;
constexpr int sequence_default_heavy_hit1 = 10;
constexpr int sequence_default_heavy_backstab = 11;
constexpr int sequence_default_lookat01 = 12;

constexpr int sequence_butterfly_draw = 0;
constexpr int sequence_butterfly_draw2 = 1;
constexpr int sequence_butterfly_lookat01 = 13;
constexpr int sequence_butterfly_lookat03 = 15;

constexpr int sequence_falchion_idle1 = 1;
constexpr int sequence_falchion_heavy_miss1 = 8;
constexpr int sequence_falchion_heavy_miss1_noflip = 9;
constexpr int sequence_falchion_lookat01 = 12;
constexpr int sequence_falchion_lookat02 = 13;

constexpr int sequence_push_idle1 = 1;
constexpr int sequence_push_heavy_miss2 = 11;

struct KnifeData {
	int         m_id;
	std::string m_model, m_world_model, m_name;
	int         m_model_index, m_world_model_index;

	__forceinline KnifeData( ) : m_id{}, m_model{}, m_world_model{}, m_name {}, m_model_index{}, m_world_model_index{} {}

	__forceinline void setup( int id, const std::string& model, const std::string& world_model, const std::string& name ) {
		m_id                = id;
		m_model             = model;
		m_name              = name;
		m_model_index       = g_csgo.m_model_info->GetModelIndex( model.data( ) );
		m_world_model_index = g_csgo.m_model_info->GetModelIndex( world_model.data( ) );
	}
};

struct GloveData {
	int         m_id;
	std::string m_model, m_world_model;
	int         m_model_index, m_world_model_index;

	__forceinline GloveData( ) : m_id{}, m_model{}, m_model_index{} {}

	__forceinline void setup( int id, const std::string& model, const std::string& world_model ) {
		m_id                = id;
		m_model             = model;
		m_world_model       = world_model;
		m_model_index       = g_csgo.m_model_info->GetModelIndex( model.data( ) );
		m_world_model_index = g_csgo.m_model_info->GetModelIndex( world_model.data( ) );
	}
};

class Skins {
public:
	enum knives_t {
		BAYONET = 1,
		BOWIE,
		BUTTERFLY,
		FALCHION ,
		FLIP,
		GUT,
		HUNTSMAN,
		KARAMBIT,
		M9,
		DAGGER,
		KNIFE_MAX
	};

	enum gloves_t {
		BLOODHOUND = 1,
		SPORTY,
		DRIVER,
		HANDWRAP,
		MOTO,
		SPECIALIST,
		GLOVE_MAX
	};

public:
	KnifeData   m_knife_data[ knives_t::KNIFE_MAX ];
	GloveData   m_glove_data[ gloves_t::GLOVE_MAX ];
	int         m_last_seq;
	CBaseHandle m_glove_handle;
	bool        m_update;
	float       m_update_time;

public:
	void load( );
	void think( );
	void UpdateItem( Weapon* item );
	void UpdateAnimations( Entity* ent );
};

extern Skins g_skins;