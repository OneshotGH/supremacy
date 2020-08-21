#pragma once

enum HitscanMode : int {
	NORMAL  = 0,
	LETHAL  = 1,
	LETHAL2 = 3,
	PREFER  = 4
};

struct AnimationBackup_t {
	vec3_t           m_origin, m_abs_origin;
	vec3_t           m_velocity, m_abs_velocity;
	int              m_flags, m_eflags;
	float            m_duck, m_body;
	C_AnimationLayer m_layers[ 13 ];
};

struct HitscanData_t {
	float  m_damage;
	vec3_t m_pos;

	__forceinline HitscanData_t( ) : m_damage{ 0.f }, m_pos{} {}
};

struct HitscanBox_t {
	int         m_index;
	HitscanMode m_mode;

	__forceinline bool operator==( const HitscanBox_t& c ) const {
		return m_index == c.m_index && m_mode == c.m_mode;
	}
};

class AimPlayer {
public:
	using records_t   = std::deque< std::shared_ptr< LagRecord > >;
	using hitboxcan_t = stdpp::unique_vector< HitscanBox_t >;

public:
	// essential data.
	Player*   m_player;
	float	  m_spawn;
	records_t m_records;

	// aimbot data.
	hitboxcan_t m_hitboxes;
	
	// resolve data.
	int       m_shots;
	int       m_missed_shots;
	LagRecord m_walk_record;

	float     m_body_update;
	bool      m_moved;

	int m_stand_index;
	int m_stand_index2;
	int m_body_index;


	// data about the LBY proxy.
	float m_body;
	float m_old_body;

	//std::deque< float >            m_lbyt_update;
	//std::deque< float >			   m_prefer_stand;
	//std::deque< float >            m_prefer_air;

public:
	void UpdateAnimations( LagRecord* record );
	void OnNetUpdate( Player* player );
	void OnRoundStart( Player* player );
	void SetupHitboxes( LagRecord* record, bool history );
	bool SetupHitboxPoints( LagRecord* record, BoneArray* bones, int index, std::vector< vec3_t >& points );
	bool GetBestAimPosition( vec3_t& aim, float& damage, LagRecord* record );

public:
	void reset( ) {
		m_player       = nullptr;
		m_spawn        = 0.f;
		m_walk_record  = LagRecord{};
		m_shots        = 0;
		m_missed_shots = 0;

		m_records.clear( );
		m_hitboxes.clear( );
	}
};

class Aimbot {
private:
	struct target_t {
		Player*    m_player;
		AimPlayer* m_data;
	};

	struct knife_target_t {
		target_t  m_target;
		LagRecord m_record;
	};

	struct table_t {
		uint8_t swing[ 2 ][ 2 ][ 2 ]; // [ first ][ armor ][ back ]
		uint8_t stab[ 2 ][ 2 ];		  // [ armor ][ back ]
	};

	const table_t m_knife_dmg{ { { { 25, 90 }, { 21, 76 } }, { { 40, 90 }, { 34, 76 } } }, { { 65, 180 }, { 55, 153 } } };

	std::array< ang_t, 12 > m_knife_ang{
		ang_t{ 0.f, 0.f, 0.f }, ang_t{ 0.f, -90.f, 0.f }, ang_t{ 0.f, 90.f, 0.f }, ang_t{ 0.f, 180.f, 0.f },
		ang_t{ -80.f, 0.f, 0.f }, ang_t{ -80.f, -90.f, 0.f }, ang_t{ -80.f, 90.f, 0.f }, ang_t{ -80.f, 180.f, 0.f },
		ang_t{ 80.f, 0.f, 0.f }, ang_t{ 80.f, -90.f, 0.f }, ang_t{ 80.f, 90.f, 0.f }, ang_t{ 80.f, 180.f, 0.f }
	};

public:
	std::array< AimPlayer, 64 > m_players;
	std::vector< AimPlayer* >   m_targets;

	BackupRecord m_backup[ 64 ];

	// target selection stuff.
	float m_best_dist;
	float m_best_fov;
	float m_best_damage;
	int   m_best_hp;
	float m_best_lag;
	float m_best_height;
	
	// found target stuff.
	Player*    m_target;
	ang_t      m_angle;
	vec3_t     m_aim;
	float      m_damage;
	LagRecord* m_record;

	// fake latency stuff.
	bool       m_fake_latency;

	bool m_stop;

public:
	__forceinline void reset( ) {
		// reset aimbot data.
		init( );

		// reset all players data.
		for( auto& p : m_players )
			p.reset( );
	}

	__forceinline bool IsValidTarget( Player* player ) {
		if( !player )
			return false;

		if( !player->IsPlayer( ) )
			return false;

		if( !player->alive( ) )
			return false;

		if( player->m_bIsLocalPlayer( ) )
			return false;

		if( !player->enemy( g_cl.m_local ) )
			return false;

		return true;
	}

public:
	// aimbot.
	void init( );
	void StripAttack( );
	void think( );
	void find( );
	bool CheckHitchance( Player* player, const ang_t& angle );
	bool SelectTarget( LagRecord* record, const vec3_t& aim, float damage );
	void apply( );
	void NoSpread( );

	// knifebot.
	void knife( );
	bool CanKnife( LagRecord* record, ang_t angle, bool& stab );
	bool KnifeTrace( vec3_t dir, bool stab, CGameTrace* trace );
	bool KnifeIsBehind( LagRecord* record );
};

extern Aimbot g_aimbot;