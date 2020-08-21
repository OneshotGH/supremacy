#pragma once

class Grenades {
private:
	enum GrenadeFlags : size_t {
		NONE = 0,
		DETONATE,
		BOUNCE,
	};

	struct bounce_t {
		vec3_t point;
		Color  color;
	};

	using path_t    = std::vector< vec3_t >;
	using bounces_t = std::vector< bounce_t >;

private:
	int       m_id;
	path_t    m_path;
	bounces_t m_bounces;
	float     m_vel, m_power;
	vec3_t    m_start, m_velocity, m_move;

public:
	void   reset( );
	void   paint( );
	void   think( );
	void   simulate( );
	void   setup( );
	size_t advance( size_t tick );
	bool   detonate( size_t tick, CGameTrace& trace );
	void   ResolveFlyCollisionBounce( CGameTrace& trace );
	void   PhysicsPushEntity( vec3_t& start, const vec3_t& move, CGameTrace& trace, Entity* ent );
	void   TraceHull( const vec3_t& start, const vec3_t& end, CGameTrace& trace, Entity* ent );
	void   PhysicsAddGravityMove( vec3_t& move );
	void   PhysicsClipVelocity( const vec3_t& in, const vec3_t& normal, vec3_t& out, float overbounce );
};

extern Grenades g_grenades;