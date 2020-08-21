#include "includes.h"

Grenades g_grenades{};;

void Grenades::reset( ) {
	m_start    = vec3_t{};
	m_move     = vec3_t{};
	m_velocity = vec3_t{};
	m_vel      = 0.f;
	m_power    = 0.f;

	m_path.clear( );
	m_bounces.clear( );
}

void Grenades::paint( ) {
    static CTraceFilterSimple_game filter{};
	CGameTrace	                   trace;
	std::pair< float, Player* >    target{ 0.f, nullptr };

	if( !g_menu.main.visuals.tracers.get( ) )
		return;

	// we dont want to do this if dead.
	if( !g_cl.m_processing )
		return;

	// aww man...
	// we need some points at least.
	if( m_path.size( ) < 2 )
		return;

    // setup trace filter for later.
    filter.SetPassEntity( g_cl.m_local );

	// previous point, set to last point.
	// or actually.. the first point, we are drawing in reverse.
	vec3_t prev = m_path.front( );

	// iterate and draw path.
	for( const auto& cur : m_path ) {
		vec2_t screen0, screen1;

		if( render::WorldToScreen( prev, screen0 ) && render::WorldToScreen( cur, screen1 ) )
			render::line( screen0, screen1, { 60, 180, 225 } );

		// store point for next iteration.
		prev = cur;
	}

	// iterate all players.
	for( int i{ 1 }; i <= g_csgo.m_globals->m_max_clients; ++i ) {
		Player* player = g_csgo.m_entlist->GetClientEntity< Player* >( i );
		if( !g_aimbot.IsValidTarget( player ) )
			continue;

		// get center of mass for player.
		vec3_t center = player->WorldSpaceCenter( );

		// get delta between center of mass and final nade pos.
		vec3_t delta = center - prev;

		if( m_id == HEGRENADE ) {
			// pGrenade->m_flDamage = 100;
			// pGrenade->m_DmgRadius = pGrenade->m_flDamage * 3.5f;

			// is within damage radius?
			if( delta.length( ) > 350.f )
				continue;

			// check if our path was obstructed by anything using a trace.
			g_csgo.m_engine_trace->TraceRay( Ray( prev, center ), MASK_SHOT, (ITraceFilter *)&filter, &trace );

			// something went wrong here.
			if( !trace.m_entity || trace.m_entity != player )
				continue;

			// rather 'interesting' formula by valve to compute damage.
			float d      = ( delta.length( ) - 25.f ) / 140.f;
			float damage = 105.f * std::exp( -d * d );

			// scale damage.
			damage = penetration::scale( player, damage, 1.f, HITGROUP_CHEST );

			// clip max damage.
			damage = std::min( damage, ( player->m_ArmorValue( ) > 0 ) ? 57.f : 98.f );

			// better target?
			if( damage > target.first ) {
				target.first  = damage;
				target.second = player;
			}
		}
	}

	// we have a target for damage.
	if( target.second ) {
		vec2_t screen;

		// replace the last bounce with green.
		if( !m_bounces.empty( ) )
			m_bounces.back( ).color = { 0, 255, 0, 255 };

		if( render::WorldToScreen( prev, screen ) )
			render::esp_small.string( screen.x, screen.y + 5, { 255, 255, 255, 0xb4 }, tfm::format( XOR( "%i" ), ( int )target.first ), render::ALIGN_CENTER );
	}

	// render bounces.
	for( const auto& b : m_bounces ) {
		vec2_t screen;

		if( render::WorldToScreen( b.point, screen ) )
			render::rect( screen.x - 2, screen.y - 2, 4, 4, b.color );
	}
}

void Grenades::think( ) {
	bool attack, attack2;

	// reset some data.
	reset( );

	if( !g_menu.main.visuals.tracers.get( ) )
		return;

	if( !g_cl.m_processing )
		return;

	// validate nade.
	if( g_cl.m_weapon_type != WEAPONTYPE_GRENADE )
		return;

	attack  = ( g_cl.m_cmd->m_buttons & IN_ATTACK );
	attack2 = ( g_cl.m_cmd->m_buttons & IN_ATTACK2 );

	if( !attack && !attack2 )
		return;

	m_id    = g_cl.m_weapon_id;
	m_power = g_cl.m_weapon->m_flThrowStrength( );
	m_vel   = g_cl.m_weapon_info->m_throw_velocity;

	simulate( );
}

void Grenades::simulate( ) {
	// init member variables
	// that will be used during the simulation.
	setup( );

	// log positions 20 times per second.
	size_t step = ( size_t )game::TIME_TO_TICKS( 0.05f ), timer{ 0u };

	// iterate until the container is full, should never happen.
	for( size_t i{ 0u }; i < 4096u; ++i ) {

		// the timer was reset, insert new point.
		if( !timer )
			m_path.push_back( m_start );

		// advance object to this frame.
		size_t flags = advance( i );

		// if we detonated, we are done.
		// our path is complete.
		if( ( flags & DETONATE ) )
			break;

		// reset or bounced.
		// add a new point when bounced, and one every step.
		if( ( flags & BOUNCE ) || timer >= step )
			timer = 0;

		// increment timer.
		else 
            ++timer;

		if( m_velocity == vec3_t{} )
			break;
	}

	// fire grenades can extend to the ground.
	// this happens if their endpoint is within range of the floor.
	// 131 units to be exact.
	if( m_id == MOLOTOV || m_id == FIREBOMB ) {
		CGameTrace trace;
		PhysicsPushEntity( m_start, { 0.f, 0.f, -131.f }, trace, g_cl.m_local );

		if( trace.m_fraction < 0.9f )
			m_start = trace.m_endpos;
	}

	// store final point.
	// likely the point of detonation.
	m_path.push_back( m_start );
	m_bounces.push_back( { m_start, colors::red } );
}

void Grenades::setup( ) {
	// get the last CreateMove angles.
	ang_t angle = g_cl.m_view_angles;

	// grab the pitch from these angles.
	float pitch = angle.x;

	// correct the pitch.
	if( pitch < -90.f ) 
		pitch += 360.f;

	else if( pitch > 90.f )
		pitch -= 360.f;

	// a rather 'interesting' approach at the approximation of some angle.
	// lets keep it on a pitch 'correction'.
	angle.x = pitch - ( 90.f - std::abs( pitch ) ) * 10.f / 90.f;

	// get ThrowVelocity from weapon files.
	float vel = m_vel * 0.9f;

	// clipped to [ 15, 750 ]
	math::clamp( vel, 15.f, 750.f );

	// apply throw power to velocity.
	// this is set depending on mouse states:
	// m1=1  m1+m2=0.5  m2=0
	vel *= ( ( m_power * 0.7f ) + 0.3f );

	// convert throw angle into forward direction.
	vec3_t forward;
	math::AngleVectors( angle, &forward );

	// set start point to our shoot position.
	m_start = g_cl.m_shoot_pos;

	// adjust starting point based on throw power.
	m_start.z += ( m_power * 12.f ) - 12.f;

	// create end point from start point.
	// and move it 22 units along the forward axis.
	vec3_t end = m_start + ( forward * 22.f );

	CGameTrace trace;
	TraceHull( m_start, end, trace, g_cl.m_local );

	// we now have 'endpoint', set in our gametrace object.

	// move back start point 6 units along forward axis.
	m_start = trace.m_endpos - ( forward * 6.f );

	// finally, calculate the velocity where we will start off with.
	// weird formula, valve..
	m_velocity = g_cl.m_local->m_vecVelocity( ) ;
	m_velocity *= 1.25f;
	m_velocity += ( forward * vel );
}

size_t Grenades::advance( size_t tick ) {
	size_t     flags{ NONE };
	CGameTrace trace;

	// apply gravity.
	PhysicsAddGravityMove( m_move );

	// move object.
	PhysicsPushEntity( m_start, m_move, trace, g_cl.m_local );

	// check if the object would detonate at this point.
	// if so stop simulating further and endthe path here.
	if( detonate( tick, trace ) )
		flags |= DETONATE;

	// fix collisions/bounces.
	if( trace.m_fraction != 1.f ) {
		// mark as bounced.
		flags |= BOUNCE;

		// adjust velocity.
		ResolveFlyCollisionBounce( trace );
	}

	// take new start point.
	m_start = trace.m_endpos;

	return flags;
}

bool Grenades::detonate( size_t tick, CGameTrace& trace ) {
	// convert current simulation tick to time.
	float time = game::TICKS_TO_TIME( tick );

	// CSmokeGrenadeProjectile::Think_Detonate
	// speed <= 0.1
	// checked every 0.2s

	// CDecoyProjectile::Think_Detonate
	// speed <= 0.2
	// checked every 0.2s

	// CBaseCSGrenadeProjectile::SetDetonateTimerLength
	// auto detonate at 1.5s
	// checked every 0.2s

	switch( m_id ) {
	case FLASHBANG:
	case HEGRENADE:
		return time >= 1.5f && !( tick % game::TIME_TO_TICKS( 0.2f ) ); 

	case SMOKE:
		return m_velocity.length( ) <= 0.1f && !( tick % game::TIME_TO_TICKS( 0.2f ) );

	case DECOY:
		return m_velocity.length( ) <= 0.2f && !( tick % game::TIME_TO_TICKS( 0.2f ) );

	case MOLOTOV:
	case FIREBOMB:
		// detonate when hitting the floor.
		if( trace.m_fraction != 1.f && ( std::cos( math::deg_to_rad( g_csgo.weapon_molotov_maxdetonateslope->GetFloat( ) ) ) <= trace.m_plane.m_normal.z ) )
			return true;

		// detonate if we have traveled for too long.
		// checked every 0.1s
		return time >= g_csgo.molotov_throw_detonate_time->GetFloat( ) && !( tick % game::TIME_TO_TICKS( 0.1f ) );

	default:
		return false;
	}

	return false;
}

void Grenades::ResolveFlyCollisionBounce( CGameTrace& trace ) {
	// https://github.com/VSES/SourceEngine2007/blob/master/se2007/game/shared/physics_main_shared.cpp#L1341

	// assume all surfaces have the same elasticity
	float surface = 1.f;

    if( trace.m_entity ) {
    	if( game::IsBreakable( trace.m_entity ) ) {
    		if( !trace.m_entity->is( HASH( "CFuncBrush" ) ) &&
    			!trace.m_entity->is( HASH( "CBaseDoor" ) ) &&
    			!trace.m_entity->is( HASH( "CCSPlayer" ) ) &&
    			!trace.m_entity->is( HASH( "CBaseEntity" ) ) ) {
    
    			// move object.
    			PhysicsPushEntity( m_start, m_move, trace, trace.m_entity );
    
    			// deduct velocity penalty.
    			m_velocity *= 0.4f;
    			return;
    		}
    	}
    }

	// combine elasticities together.
	float elasticity = 0.45f * surface;

	// clipped to [ 0, 0.9 ]
	math::clamp( elasticity, 0.f, 0.9f );

	vec3_t velocity;
	PhysicsClipVelocity( m_velocity, trace.m_plane.m_normal, velocity, 2.f );
	velocity *= elasticity;

	if( trace.m_plane.m_normal.z > 0.7f ) {
		float speed = velocity.length_sqr( );

		// hit surface with insane speed.
		if( speed > 96000.f ) {

			// weird formula to slow down by normal angle?
			float len = velocity.normalized( ).dot( trace.m_plane.m_normal );
			if( len > 0.5f )
				velocity *= 1.5f - len;
		}

		// are we going too slow?
		// just stop completely.
		if( speed < 400.f )
			m_velocity = vec3_t{};

		else {
			// set velocity.
			m_velocity = velocity;

			// compute friction left.
			float left = 1.f - trace.m_fraction;

			// advance forward.
			PhysicsPushEntity( trace.m_endpos, velocity * ( left * g_csgo.m_globals->m_interval ), trace, g_cl.m_local );
		}
	}

	else {
		// set velocity.
		m_velocity = velocity;

		// compute friction left.
		float left = 1.f - trace.m_fraction;

		// advance forward.
		PhysicsPushEntity( trace.m_endpos, velocity * ( left * g_csgo.m_globals->m_interval ), trace, g_cl.m_local );
	}

	m_bounces.push_back( { trace.m_endpos, colors::white } );
}

void Grenades::PhysicsPushEntity( vec3_t& start, const vec3_t& move, CGameTrace& trace, Entity* ent ) {
	// compute end point.
	vec3_t end = start + move;

	// trace through world.
	TraceHull( start, end, trace, ent );
}

void Grenades::TraceHull( const vec3_t& start, const vec3_t& end, CGameTrace& trace, Entity* ent ) {
	// create trace filter.
    static CTraceFilterSimple_game filter{};

    filter.SetPassEntity( ent );

	g_csgo.m_engine_trace->TraceRay( Ray( start, end, { -2.f, -2.f, -2.f }, { 2.f, 2.f, 2.f } ), MASK_SOLID, (ITraceFilter *)&filter, &trace );
}

void Grenades::PhysicsAddGravityMove( vec3_t& move ) {
	// https://github.com/VSES/SourceEngine2007/blob/master/se2007/game/shared/physics_main_shared.cpp#L1264

	// gravity for grenades.
	float gravity = 800.f * 0.4f;

	// move one tick using current velocity.
	move.x = m_velocity.x * g_csgo.m_globals->m_interval;
	move.y = m_velocity.y * g_csgo.m_globals->m_interval;

	// apply linear acceleration due to gravity.
	// calculate new z velocity.
	float z = m_velocity.z - ( gravity * g_csgo.m_globals->m_interval );

	// apply velocity to move, the average of the new and the old.
	move.z = ( ( m_velocity.z + z ) / 2.f ) * g_csgo.m_globals->m_interval;

	// write back new gravity corrected z-velocity.
	m_velocity.z = z;
}

void Grenades::PhysicsClipVelocity( const vec3_t& in, const vec3_t& normal, vec3_t& out, float overbounce ) {
	// https://github.com/VSES/SourceEngine2007/blob/master/se2007/game/shared/physics_main_shared.cpp#L1294
	constexpr float STOP_EPSILON = 0.1f;

	// https://github.com/VSES/SourceEngine2007/blob/master/se2007/game/shared/physics_main_shared.cpp#L1303

	float backoff = in.dot( normal ) * overbounce;

	for( int i{}; i < 3; ++i ) {
		out[ i ] = in[ i ] - ( normal[ i ] * backoff );

		if( out[ i ] > -STOP_EPSILON && out[ i ] < STOP_EPSILON )
			out[ i ] = 0.f;
	}
}