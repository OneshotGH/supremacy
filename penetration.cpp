#include "includes.h"

float penetration::scale( Player* player, float damage, float armor_ratio, int hitgroup ) {
	bool  has_heavy_armor;
	int   armor;
	float heavy_ratio, bonus_ratio, ratio, new_damage;

	static auto is_armored = []( Player* player, int armor, int hitgroup ) {
		// the player has no armor.
		if( armor <= 0 )
			return false;

		// if the hitgroup is head and the player has a helment, return true.
		// otherwise only return true if the hitgroup is not generic / legs / gear.
		if( hitgroup == HITGROUP_HEAD && player->m_bHasHelmet( ) )
			return true;

		else if( hitgroup >= HITGROUP_CHEST && hitgroup <= HITGROUP_RIGHTARM )
			return true;

		return false;
	};

	// check if the player has heavy armor, this is only really used in operation stuff.
	has_heavy_armor = player->m_bHasHeavyArmor( );

	// scale damage based on hitgroup.
	switch( hitgroup ) {
	case HITGROUP_HEAD:
		if( has_heavy_armor )
			damage = ( damage * 4.f ) * 0.5f;
		else
			damage *= 4.f;
		break;

	case HITGROUP_STOMACH:
		damage *= 1.25f;
		break;

	case HITGROUP_LEFTLEG:
	case HITGROUP_RIGHTLEG:
		damage *= 0.75f;
		break;

	default:
		break;
	}

	// grab amount of player armor.
	armor = player->m_ArmorValue( );

	// check if the ent is armored and scale damage based on armor.
	if( is_armored( player, armor, hitgroup ) ) {
		heavy_ratio = 1.f;
		bonus_ratio = 0.5f;
		ratio       = armor_ratio * 0.5f;

		// player has heavy armor.
		if( has_heavy_armor ) {
			// calculate ratio values.
			bonus_ratio = 0.33f;
			ratio       = armor_ratio * 0.25f;
			heavy_ratio = 0.33f;

			// calculate new damage.
			new_damage = ( damage * ratio ) * 0.85f;
		}

		// no heavy armor, do normal damage calculation.
		else
			new_damage = damage * ratio;

		if( ( ( damage - new_damage ) * ( heavy_ratio * bonus_ratio ) ) > armor )
			new_damage = damage - ( armor / bonus_ratio );

		damage = new_damage;
	}

	return std::floor( damage );
}

bool penetration::TraceToExit( const vec3_t &start, const vec3_t& dir, vec3_t& out, CGameTrace* enter_trace, CGameTrace* exit_trace ) {
    static CTraceFilterSimple_game filter{};

	float  dist{};
	vec3_t new_end;
	int    contents, first_contents{};

	// max pen distance is 90 units.
	while( dist <= 90.f ) {
		// step forward a bit.
		dist += 4.f;

		// set out pos.
		out = start + ( dir * dist );

		if( !first_contents )
			first_contents = g_csgo.m_engine_trace->GetPointContents( out, MASK_SHOT, nullptr );

		contents = g_csgo.m_engine_trace->GetPointContents( out, MASK_SHOT, nullptr );

		if( ( contents & MASK_SHOT_HULL ) && ( !( contents & CONTENTS_HITBOX ) || ( contents == first_contents ) ) )
			continue;

		// move end pos a bit for tracing.
		new_end = out - ( dir * 4.f );

		// do first trace aHR0cHM6Ly9zdGVhbWNvbW11bml0eS5jb20vaWQvc2ltcGxlcmVhbGlzdGlj.
		g_csgo.m_engine_trace->TraceRay( Ray( out, new_end ), MASK_SHOT, nullptr, exit_trace );

        // note - dex; this is some new stuff added sometime around late 2017 ( 10.31.2017 update? ).
        if( g_csgo.sv_clip_penetration_traces_to_players->GetInt( ) )
            game::UTIL_ClipTraceToPlayers( out, new_end, MASK_SHOT, nullptr, exit_trace, -60.f );

        // we hit an ent's hitbox, do another trace.
        if( exit_trace->m_startsolid && ( exit_trace->m_surface.m_flags & SURF_HITBOX ) ) {
			filter.SetPassEntity( exit_trace->m_entity );
        
			g_csgo.m_engine_trace->TraceRay( Ray( out, start ), MASK_SHOT_HULL, (ITraceFilter *)&filter, exit_trace );
        
			if( exit_trace->hit( ) && !exit_trace->m_startsolid ) {
                out = exit_trace->m_endpos;
                return true;
            }

            continue;
		}

        if( !exit_trace->hit( ) || exit_trace->m_startsolid ) {
            if( game::IsBreakable( enter_trace->m_entity ) ) {
                *exit_trace          = *enter_trace;
                exit_trace->m_endpos = start + dir;
            	return true;
            }

            continue;
        }

        if( ( exit_trace->m_surface.m_flags & SURF_NODRAW ) ) {
            // note - dex; ok, when this happens the game seems to not ignore world?
            if( game::IsBreakable( exit_trace->m_entity ) && game::IsBreakable( enter_trace->m_entity ) ) {
                out = exit_trace->m_endpos;
                return true;
            } 

            if( !( enter_trace->m_surface.m_flags & SURF_NODRAW ) )
                continue;
        }

        if( exit_trace->m_plane.m_normal.dot( dir ) <= 1.f ) {
            out -= ( dir * ( exit_trace->m_fraction * 4.f ) );
            return true;
        }
	}

	return false;
}

void penetration::ClipTraceToPlayer( const vec3_t& start, const vec3_t& end, uint32_t mask, CGameTrace* tr, Player* player, float min ) {
	vec3_t     pos, to, dir, on_ray;
	float      len, range_along, range;
	Ray        ray;
	CGameTrace new_trace;

	// reference: https://github.com/alliedmodders/hl2sdk/blob/3957adff10fe20d38a62fa8c018340bf2618742b/game/shared/util_shared.h#L381

	// set some local vars.
	pos         = player->m_vecOrigin( ) + ( ( player->m_vecMins( ) + player->m_vecMaxs( ) ) * 0.5f );
	to          = pos - start;
	dir         = start - end;
	len         = dir.normalize( );
	range_along = dir.dot( to );

	// off start point.
	if( range_along < 0.f )	
		range = -( to ).length( );

	// off end point.
	else if( range_along > len ) 
		range = -( pos - end ).length( );

	// within ray bounds.
	else {
		on_ray = start + ( dir * range_along );
		range  = ( pos - on_ray ).length( );
	}

	if( /*min <= range &&*/ range <= 60.f ) {
		// clip to player.
		g_csgo.m_engine_trace->ClipRayToEntity( Ray( start, end ), mask, player, &new_trace );

		if( tr->m_fraction > new_trace.m_fraction )
			*tr = new_trace;
	}
}

bool penetration::run( PenetrationInput_t* in, PenetrationOutput_t* out ) {
    static CTraceFilterSkipTwoEntities_game filter{};

	int			  pen{ 4 }, enter_material, exit_material;
	float		  damage, penetration, penetration_mod, player_damage, remaining, trace_len{}, total_pen_mod, damage_mod, modifier, damage_lost;
	surfacedata_t *enter_surface, *exit_surface;
	bool		  nodraw, grate;
	vec3_t		  start, dir, end, pen_end;
	CGameTrace	  trace, exit_trace;
	Weapon		  *weapon;
	WeaponInfo    *weapon_info;

	// if we are tracing from our local player perspective.
	if( in->m_from->m_bIsLocalPlayer( ) ) {
		weapon      = g_cl.m_weapon;
		weapon_info = g_cl.m_weapon_info;
		start       = g_cl.m_shoot_pos;
	}

	// not local player.
	else {
		weapon = in->m_from->GetActiveWeapon( );
		if( !weapon )
			return false;

		// get weapon info.
		weapon_info = weapon->GetWpnData( );
		if( !weapon_info )
			return false;

		// set trace start.
		start = in->m_from->GetShootPosition( );
	}

	// get some weapon data.
	damage      = ( float )weapon_info->m_damage;
	penetration = weapon_info->m_penetration;

    // used later in calculations.
    penetration_mod = std::max( 0.f, ( 3.f / penetration ) * 1.25f );

	// get direction to end point.
	dir = ( in->m_pos - start ).normalized( );

    // setup trace filter for later.
    filter.SetPassEntity( in->m_from );
    filter.SetPassEntity2( nullptr );

    while( damage > 0.f ) {
		// calculating remaining len.
		remaining = weapon_info->m_range - trace_len;

		// set trace end.
		end = start + ( dir * remaining );

		// setup ray and trace.
		// TODO; use UTIL_TraceLineIgnoreTwoEntities?
		g_csgo.m_engine_trace->TraceRay( Ray( start, end ), MASK_SHOT, (ITraceFilter *)&filter, &trace );

		// check for player hitboxes extending outside their collision bounds.
		// if no target is passed we clip the trace to a specific player, otherwise we clip the trace to any player.
		if( in->m_target )
			ClipTraceToPlayer( start, end + ( dir * 40.f ), MASK_SHOT, &trace, in->m_target, -60.f );

		else
			game::UTIL_ClipTraceToPlayers( start, end + ( dir * 40.f ), MASK_SHOT, (ITraceFilter *)&filter, &trace, -60.f );

		// we didn't hit anything.
		if( trace.m_fraction == 1.f )
			return false;

		// calculate damage based on the distance the bullet traveled.
		trace_len += trace.m_fraction * remaining;
		damage    *= std::pow( weapon_info->m_range_modifier, trace_len / 500.f );

		// if a target was passed.
		if( in->m_target ) {

			// validate that we hit the target we aimed for.
			if( trace.m_entity && trace.m_entity == in->m_target && game::IsValidHitgroup( trace.m_hitgroup ) ) {
				int group = ( weapon->m_iItemDefinitionIndex( ) == ZEUS ) ? HITGROUP_GENERIC : trace.m_hitgroup;

				// scale damage based on the hitgroup we hit.
				player_damage = scale( in->m_target, damage, weapon_info->m_armor_ratio, group );

				// set result data for when we hit a player.
			    out->m_pen      = pen != 4;
			    out->m_hitgroup = group;
			    out->m_damage   = player_damage;
			    out->m_target   = in->m_target;

				// non-penetrate damage.
				if( pen == 4 )
					return player_damage >= in->m_damage;
					
				// penetration damage.
				return player_damage >= in->m_damage_pen;
			}
		}

		// no target was passed, check for any player hit or just get final damage done.
		else {
			out->m_pen = pen != 4;

			// todo - dex; team checks / other checks / etc.
			if( trace.m_entity && trace.m_entity->IsPlayer( ) && game::IsValidHitgroup( trace.m_hitgroup ) ) {
				int group = ( weapon->m_iItemDefinitionIndex( ) == ZEUS ) ? HITGROUP_GENERIC : trace.m_hitgroup;

				player_damage = scale( trace.m_entity->as< Player* >( ), damage, weapon_info->m_armor_ratio, group );

				// set result data for when we hit a player.
				out->m_hitgroup = group;
				out->m_damage   = player_damage;
				out->m_target   = trace.m_entity->as< Player* >( );

				// non-penetrate damage.
				if( pen == 4 )
					return player_damage >= in->m_damage;

				// penetration damage.
				return player_damage >= in->m_damage_pen;
			}

            // if we've reached here then we didn't hit a player yet, set damage and hitgroup.
            out->m_damage = damage;
		}

		// don't run pen code if it's not wanted.
		if( !in->m_can_pen )
			return false;

		// get surface at entry point.
		enter_surface = g_csgo.m_phys_props->GetSurfaceData( trace.m_surface.m_surface_props );

		// this happens when we're too far away from a surface and can penetrate walls or the surface's pen modifier is too low.
		if( ( trace_len > 3000.f && penetration ) || enter_surface->m_game.m_penetration_modifier < 0.1f )
			return false;

		// store data about surface flags / contents.
		nodraw = ( trace.m_surface.m_flags & SURF_NODRAW );
		grate  = ( trace.m_contents & CONTENTS_GRATE );

		// get material at entry point.
		enter_material = enter_surface->m_game.m_material;

		// note - dex; some extra stuff the game does.
		if( !pen && !nodraw && !grate && enter_material != CHAR_TEX_GRATE && enter_material != CHAR_TEX_GLASS )
			return false;

		// no more pen.
		if( penetration <= 0.f || pen <= 0 )
			return false;

		// try to penetrate object.
		if( !TraceToExit( trace.m_endpos, dir, pen_end, &trace, &exit_trace ) ) {
			if( !( g_csgo.m_engine_trace->GetPointContents( pen_end, MASK_SHOT_HULL ) & MASK_SHOT_HULL ) )
				return false;
		}

		// get surface / material at exit point.
		exit_surface  = g_csgo.m_phys_props->GetSurfaceData( exit_trace.m_surface.m_surface_props );
        exit_material = exit_surface->m_game.m_material;

        // todo - dex; check for CHAR_TEX_FLESH and ff_damage_bullet_penetration / ff_damage_reduction_bullets convars?
        //             also need to check !isbasecombatweapon too.
		if( enter_material == CHAR_TEX_GRATE || enter_material == CHAR_TEX_GLASS ) {
			total_pen_mod = 3.f;
			damage_mod    = 0.05f;
		}

		else if( nodraw || grate ) {
			total_pen_mod = 1.f;
			damage_mod    = 0.16f;
		}

		else {
			total_pen_mod = ( enter_surface->m_game.m_penetration_modifier + exit_surface->m_game.m_penetration_modifier ) * 0.5f;
			damage_mod    = 0.16f;
		}

		// thin metals, wood and plastic get a penetration bonus.
		if( enter_material == exit_material ) {
			if( exit_material == CHAR_TEX_CARDBOARD || exit_material == CHAR_TEX_WOOD )
				total_pen_mod = 3.f;

			else if( exit_material == CHAR_TEX_PLASTIC )
				total_pen_mod = 2.f;
		}

		// set some local vars.
		trace_len   = ( exit_trace.m_endpos - trace.m_endpos ).length( );
		modifier    = std::max( 0.f, 1.f / total_pen_mod );
		damage_lost = ( ( modifier * 3.f ) * penetration_mod + ( damage * damage_mod ) ) + ( ( ( trace_len * trace_len ) * modifier ) / 24.f );

		// subtract from damage.
		damage -= std::max( 0.f, damage_lost );
		if( damage < 1.f )
			return false;

		// set new start pos for successive trace.
		start = exit_trace.m_endpos;

		// decrement pen.
		--pen;
	}

	return false;
}