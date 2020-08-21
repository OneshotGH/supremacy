#include "includes.h"

void math::AngleMatrix( const ang_t& ang, const vec3_t& pos, matrix3x4_t& out ) {
    g_csgo.AngleMatrix( ang, out );
    out.SetOrigin( pos );
}

void math::NormalizeAngle( float &angle ) {
    float rot;

    // bad number.
    if( !std::isfinite( angle ) ) {
        angle = 0.f;
        return;
    }

    // no need to normalize this angle.
    if( angle >= -180.f && angle <= 180.f )
        return;

    // get amount of rotations needed.
    rot = std::round( std::abs( angle / 360.f ) );

    // normalize.
    angle = ( angle < 0.f ) ? angle + ( 360.f * rot ) : angle - ( 360.f * rot );
}

float math::ApproachAngle( float target, float value, float speed ) {
    float delta;

    target = AngleMod( target );
    value  = AngleMod( value );
    delta  = target - value;

    // speed is assumed to be positive.
    speed = std::abs( speed );

    math::NormalizeAngle( delta );

    if( delta > speed )
        value += speed;

    else if( delta < -speed )
        value -= speed;

    else
        value = target;

    return value;
}

void math::VectorAngles( const vec3_t& forward, ang_t& angles, vec3_t *up ) {
    vec3_t  left;
    float   len, up_z, pitch, yaw, roll;

    // get 2d length.
    len = forward.length_2d( );

    if( up && len > 0.001f ) {
        pitch = rad_to_deg( std::atan2( -forward.z, len ) );
        yaw   = rad_to_deg( std::atan2( forward.y, forward.x ) );

        // get left direction vector using cross product.
        left = ( *up ).cross( forward ).normalized( );

        // calculate up_z.
        up_z = ( left.y * forward.x ) - ( left.x * forward.y );

        // calculate roll.
        roll = rad_to_deg( std::atan2( left.z, up_z ) );
    }

    else {
        if( len > 0.f ) {
            // calculate pitch and yaw.
            pitch = rad_to_deg( std::atan2( -forward.z, len ) );
            yaw   = rad_to_deg( std::atan2( forward.y, forward.x ) );
            roll  = 0.f;
        }

        else {
            pitch = ( forward.z > 0.f ) ? -90.f : 90.f;
            yaw   = 0.f;
            roll  = 0.f;
        }
    }

    // set out angles.
    angles = { pitch, yaw, roll };
}

void math::AngleVectors( const ang_t& angles, vec3_t* forward, vec3_t* right, vec3_t* up ) {
    float cp = std::cos( deg_to_rad( angles.x ) ), sp = std::sin( deg_to_rad( angles.x ) );
    float cy = std::cos( deg_to_rad( angles.y ) ), sy = std::sin( deg_to_rad( angles.y ) );
    float cr = std::cos( deg_to_rad( angles.z ) ), sr = std::sin( deg_to_rad( angles.z ) );

	if( forward ) {
		forward->x = cp * cy;
		forward->y = cp * sy;
		forward->z = -sp;
	}

    if( right ) {
        right->x = -1.f * sr * sp * cy + -1.f * cr * -sy;
        right->y = -1.f * sr * sp * sy + -1.f * cr * cy;
        right->z = -1.f * sr * cp;
    }

    if( up ) {
        up->x = cr * sp * cy + -sr * -sy;
        up->y = cr * sp * sy + -sr * cy;
        up->z = cr * cp;
    }
}

float math::GetFOV( const ang_t &view_angles, const vec3_t &start, const vec3_t &end ) {
    vec3_t dir, fw;

    // get direction and normalize.
    dir = ( end - start ).normalized( );

    // get the forward direction vector of the view angles.
    AngleVectors( view_angles, &fw );

    // get the angle between the view angles forward directional vector and the target location.
    return std::max( rad_to_deg( std::acos( fw.dot( dir ) ) ), 0.f );
}

void math::VectorTransform( const vec3_t& in, const matrix3x4_t& matrix, vec3_t& out ) {
    out = {
        in.dot( vec3_t( matrix[ 0 ][ 0 ], matrix[ 0 ][ 1 ], matrix[ 0 ][ 2 ] ) ) + matrix[ 0 ][ 3 ],
        in.dot( vec3_t( matrix[ 1 ][ 0 ], matrix[ 1 ][ 1 ], matrix[ 1 ][ 2 ] ) ) + matrix[ 1 ][ 3 ],
        in.dot( vec3_t( matrix[ 2 ][ 0 ], matrix[ 2 ][ 1 ], matrix[ 2 ][ 2 ] ) ) + matrix[ 2 ][ 3 ]
    };
}

void math::VectorITransform( const vec3_t &in, const matrix3x4_t &matrix, vec3_t &out ) {
    vec3_t diff;

    diff = { 
        in.x - matrix[ 0 ][ 3 ], 
        in.y - matrix[ 1 ][ 3 ], 
        in.z - matrix[ 2 ][ 3 ] 
    };

    out = {
        diff.x * matrix[ 0 ][ 0 ] + diff.y * matrix[ 1 ][ 0 ] + diff.z * matrix[ 2 ][ 0 ],
        diff.x * matrix[ 0 ][ 1 ] + diff.y * matrix[ 1 ][ 1 ] + diff.z * matrix[ 2 ][ 1 ],
        diff.x * matrix[ 0 ][ 2 ] + diff.y * matrix[ 1 ][ 2 ] + diff.z * matrix[ 2 ][ 2 ]
    };
}

void math::MatrixAngles( const matrix3x4_t& matrix, ang_t& angles ) {
    vec3_t forward, left, up;

    // extract the basis vectors from the matrix. since we only need the z
    // component of the up vector, we don't get x and y.
    forward = { matrix[ 0 ][ 0 ], matrix[ 1 ][ 0 ], matrix[ 2 ][ 0 ] };
    left    = { matrix[ 0 ][ 1 ], matrix[ 1 ][ 1 ], matrix[ 2 ][ 1 ] };
    up      = { 0.f, 0.f, matrix[ 2 ][ 2 ] };

    float len = forward.length_2d( );

    // enough here to get angles?
    if( len > 0.001f ) {
        angles.x = rad_to_deg( std::atan2( -forward.z, len ) );
        angles.y = rad_to_deg( std::atan2( forward.y, forward.x ) );
        angles.z = rad_to_deg( std::atan2( left.z, up.z ) );
    }

    else {
        angles.x = rad_to_deg( std::atan2( -forward.z, len ) );
        angles.y = rad_to_deg( std::atan2( -left.x, left.y ) );
        angles.z = 0.f;
    }
}

void math::MatrixCopy( const matrix3x4_t &in, matrix3x4_t &out ) {
    std::memcpy( out.Base( ), in.Base( ), sizeof( matrix3x4_t ) );
}

void math::ConcatTransforms( const matrix3x4_t &in1, const matrix3x4_t &in2, matrix3x4_t &out ) {
    if( &in1 == &out ) {
        matrix3x4_t in1b;
        MatrixCopy( in1, in1b );
        ConcatTransforms( in1b, in2, out );
        return;
    }

    if( &in2 == &out ) {
        matrix3x4_t in2b;
        MatrixCopy( in2, in2b );
        ConcatTransforms( in1, in2b, out );
        return;
    }

    out[ 0 ][ 0 ] = in1[ 0 ][ 0 ] * in2[ 0 ][ 0 ] + in1[ 0 ][ 1 ] * in2[ 1 ][ 0 ] + in1[ 0 ][ 2 ] * in2[ 2 ][ 0 ];
    out[ 0 ][ 1 ] = in1[ 0 ][ 0 ] * in2[ 0 ][ 1 ] + in1[ 0 ][ 1 ] * in2[ 1 ][ 1 ] + in1[ 0 ][ 2 ] * in2[ 2 ][ 1 ];
    out[ 0 ][ 2 ] = in1[ 0 ][ 0 ] * in2[ 0 ][ 2 ] + in1[ 0 ][ 1 ] * in2[ 1 ][ 2 ] + in1[ 0 ][ 2 ] * in2[ 2 ][ 2 ];
    out[ 0 ][ 3 ] = in1[ 0 ][ 0 ] * in2[ 0 ][ 3 ] + in1[ 0 ][ 1 ] * in2[ 1 ][ 3 ] + in1[ 0 ][ 2 ] * in2[ 2 ][ 3 ] + in1[ 0 ][ 3 ];

    out[ 1 ][ 0 ] = in1[ 1 ][ 0 ] * in2[ 0 ][ 0 ] + in1[ 1 ][ 1 ] * in2[ 1 ][ 0 ] + in1[ 1 ][ 2 ] * in2[ 2 ][ 0 ];
    out[ 1 ][ 1 ] = in1[ 1 ][ 0 ] * in2[ 0 ][ 1 ] + in1[ 1 ][ 1 ] * in2[ 1 ][ 1 ] + in1[ 1 ][ 2 ] * in2[ 2 ][ 1 ];
    out[ 1 ][ 2 ] = in1[ 1 ][ 0 ] * in2[ 0 ][ 2 ] + in1[ 1 ][ 1 ] * in2[ 1 ][ 2 ] + in1[ 1 ][ 2 ] * in2[ 2 ][ 2 ];
    out[ 1 ][ 3 ] = in1[ 1 ][ 0 ] * in2[ 0 ][ 3 ] + in1[ 1 ][ 1 ] * in2[ 1 ][ 3 ] + in1[ 1 ][ 2 ] * in2[ 2 ][ 3 ] + in1[ 1 ][ 3 ];

    out[ 2 ][ 0 ] = in1[ 2 ][ 0 ] * in2[ 0 ][ 0 ] + in1[ 2 ][ 1 ] * in2[ 1 ][ 0 ] + in1[ 2 ][ 2 ] * in2[ 2 ][ 0 ];
    out[ 2 ][ 1 ] = in1[ 2 ][ 0 ] * in2[ 0 ][ 1 ] + in1[ 2 ][ 1 ] * in2[ 1 ][ 1 ] + in1[ 2 ][ 2 ] * in2[ 2 ][ 1 ];
    out[ 2 ][ 2 ] = in1[ 2 ][ 0 ] * in2[ 0 ][ 2 ] + in1[ 2 ][ 1 ] * in2[ 1 ][ 2 ] + in1[ 2 ][ 2 ] * in2[ 2 ][ 2 ];
    out[ 2 ][ 3 ] = in1[ 2 ][ 0 ] * in2[ 0 ][ 3 ] + in1[ 2 ][ 1 ] * in2[ 1 ][ 3 ] + in1[ 2 ][ 2 ] * in2[ 2 ][ 3 ] + in1[ 2 ][ 3 ];
}

bool math::IntersectRayWithBox( const vec3_t &start, const vec3_t &delta, const vec3_t &mins, const vec3_t &maxs, float tolerance, BoxTraceInfo_t *out_info ) {
    int   i;
    float d1, d2, f;

    for( i = 0; i < 6; ++i ) {
        if( i >= 3 ) {
            d1 = start[ i - 3 ] - maxs[ i - 3 ];
            d2 = d1 + delta[ i - 3 ];
        }
        
        else {
            d1 = -start[ i ] + mins[ i ];
            d2 = d1 - delta[ i ];
        }
        
        // if completely in front of face, no intersection.
        if( d1 > 0.f && d2 > 0.f ){
            out_info->m_startsolid = false;

            return false;
        }
        
        // completely inside, check next face.
        if( d1 <= 0.f && d2 <= 0.f )
            continue;
        
        if( d1 > 0.f )
            out_info->m_startsolid = false;
        
        // crosses face.
        if( d1 > d2 ) {
            f = std::max( 0.f, d1 - tolerance );

            f = f / ( d1 - d2 );
            if( f > out_info->m_t1 ) {
                out_info->m_t1      = f;
                out_info->m_hitside = i;
            }
        }
        
        // leave.
        else {
            f = ( d1 + tolerance ) / ( d1 - d2 );
            if( f < out_info->m_t2 )
                out_info->m_t2 = f;
        }
    }

    return out_info->m_startsolid || ( out_info->m_t1 < out_info->m_t2 && out_info->m_t1 >= 0.f );
}

bool math::IntersectRayWithBox( const vec3_t &start, const vec3_t &delta, const vec3_t &mins, const vec3_t &maxs, float tolerance, CBaseTrace *out_tr, float *fraction_left_solid ) {
    BoxTraceInfo_t box_tr;
    
    // note - dex; this is Collision_ClearTrace.
    out_tr->m_startpos   = start;
	out_tr->m_endpos     = start;
	out_tr->m_endpos    += delta;
	out_tr->m_startsolid = false;
	out_tr->m_allsolid   = false;
	out_tr->m_fraction   = 1.f;
	out_tr->m_contents   = 0;

    if( IntersectRayWithBox( start, delta, mins, maxs, tolerance, &box_tr ) ) {
        out_tr->m_startsolid = box_tr.m_startsolid;
        
        if( box_tr.m_t1 < box_tr.m_t2 && box_tr.m_t1 >= 0.f ){
        	out_tr->m_fraction = box_tr.m_t1;
        
        	// VectorMA( pTrace->startpos, trace.t1, vecRayDelta, pTrace->endpos );
        
        	out_tr->m_contents       = CONTENTS_SOLID;
            out_tr->m_plane.m_normal = vec3_t{};
        
        	if( box_tr.m_hitside >= 3 ) {
        		box_tr.m_hitside -= 3;
        
        		out_tr->m_plane.m_dist                       = maxs[ box_tr.m_hitside ];
        		out_tr->m_plane.m_normal[ box_tr.m_hitside ] = 1.f;
        		out_tr->m_plane.m_type                       = box_tr.m_hitside;
        	}
        	
            else {
        		out_tr->m_plane.m_dist                       = -mins[ box_tr.m_hitside ];
        		out_tr->m_plane.m_normal[ box_tr.m_hitside ] = -1.f;
        		out_tr->m_plane.m_type                       = box_tr.m_hitside;
        	}
        
        	return true;
        }
        
        if( out_tr->m_startsolid ) {
        	out_tr->m_allsolid = ( box_tr.m_t2 <= 0.f ) || ( box_tr.m_t2 >= 1.f );
        	out_tr->m_fraction = 0.f;
        
        	if( fraction_left_solid )
                *fraction_left_solid = box_tr.m_t2;
        
        	out_tr->m_endpos         = out_tr->m_startpos;
        	out_tr->m_contents       = CONTENTS_SOLID;
        	out_tr->m_plane.m_dist   = out_tr->m_startpos.x;
        	out_tr->m_plane.m_normal = { 1.f, 0.f, 0.f };
        	out_tr->m_plane.m_type   = 0;
        	out_tr->m_startpos       = start + ( box_tr.m_t2 * delta );
        
        	return true;
        }
    }

    return false;
}

bool math::IntersectRayWithOBB( const vec3_t &start, const vec3_t &delta, const matrix3x4_t &obb_to_world, const vec3_t &mins, const vec3_t &maxs, float tolerance, CBaseTrace *out_tr ) {
    vec3_t box_extents, box_center, extent{}, uextent, segment_center, cross, new_start, tmp_end;
    float  coord, tmp, cextent, sign;

    // note - dex; this is Collision_ClearTrace.
    out_tr->m_startpos   = start;
	out_tr->m_endpos     = start;
	out_tr->m_endpos    += delta;
	out_tr->m_startsolid = false;
	out_tr->m_allsolid   = false;
	out_tr->m_fraction   = 1.f;
	out_tr->m_contents   = 0;

    // compute center in local space and transform to world space.
    box_extents = ( mins + maxs ) / 2.f;
    VectorTransform( box_extents, obb_to_world, box_center );

    // calculate extents from local center.
    box_extents = maxs - box_extents;

    // save the extents of the ray.
    segment_center = start + delta - box_center;

    // check box axes for separation.
	for( int i = 0; i < 3; ++i ){
		extent[ i ]  = delta.x * obb_to_world[ 0 ][ i ] + delta.y * obb_to_world[ 1 ][ i ] + delta.z * obb_to_world[ 2 ][ i ];
		uextent[ i ] = std::abs( extent[ i ] );

		coord = segment_center.x * obb_to_world[ 0 ][ i ] + segment_center.y * obb_to_world[ 1 ][ i ] + segment_center.z * obb_to_world[ 2 ][ i ];
		coord = std::abs( coord );
		if( coord > ( box_extents[ i ] + uextent[ i ] ) )
			return false;
	}

    // now check cross axes for separation.
    cross = delta.cross( segment_center );

    cextent = cross.x * obb_to_world[ 0 ][ 0 ] + cross.y * obb_to_world[ 1 ][ 0 ] + cross.z * obb_to_world[ 2 ][ 0 ];
    cextent = std::abs( cextent );
    tmp     = box_extents.y * uextent.z + box_extents.z * uextent.y;
    if( cextent > tmp )
    	return false;
    
    cextent = cross.x * obb_to_world[ 0 ][ 1 ] + cross.y * obb_to_world[ 1 ][ 1 ] + cross.z * obb_to_world[ 2 ][ 1 ];
    cextent = std::abs( cextent );
    tmp     = box_extents.x * uextent.z + box_extents.z * uextent.x;
    if( cextent > tmp )
    	return false;
    
    cextent = cross.x * obb_to_world[ 0 ][ 2 ] + cross.y * obb_to_world[ 1 ][ 2 ] + cross.z * obb_to_world[ 2 ][ 2 ];
    cextent = std::abs( cextent );
    tmp     = box_extents.x * uextent.y + box_extents.y * uextent.x;
    if( cextent > tmp )
    	return false;

    // we hit this box, compute intersection point and return.
    // compute ray start in bone space.
	VectorITransform( start, obb_to_world, new_start );

    // extent is ray.m_Delta in bone space, recompute delta in bone space.
    extent *= 2.f;

    // delta was prescaled by the current t, so no need to see if this intersection is closer.
    if( !IntersectRayWithBox( start, extent, mins, maxs, tolerance, out_tr ) )
        return false;

    // fix up the start/end pos and fraction
    VectorTransform( out_tr->m_endpos, obb_to_world, tmp_end );

    out_tr->m_endpos    = tmp_end;
    out_tr->m_startpos  = start;
    out_tr->m_fraction *= 2.f;
    
    // fix up the plane information
    sign = out_tr->m_plane.m_normal[ out_tr->m_plane.m_type ];

    out_tr->m_plane.m_normal.x = sign * obb_to_world[ 0 ][ out_tr->m_plane.m_type ];
    out_tr->m_plane.m_normal.y = sign * obb_to_world[ 1 ][ out_tr->m_plane.m_type ];
    out_tr->m_plane.m_normal.z = sign * obb_to_world[ 2 ][ out_tr->m_plane.m_type ];
    out_tr->m_plane.m_dist     = out_tr->m_endpos.dot( out_tr->m_plane.m_normal );
    out_tr->m_plane.m_type     = 3;

    return true;
}

bool math::IntersectRayWithOBB( const vec3_t &start, const vec3_t &delta, const vec3_t &box_origin, const ang_t &box_rotation, const vec3_t &mins, const vec3_t &maxs, float tolerance, CBaseTrace *out_tr ) {
    // todo - dex; https://github.com/pmrowla/hl2sdk-csgo/blob/master/public/collisionutils.cpp#L1400
    return false;
}

bool math::IntersectInfiniteRayWithSphere( const vec3_t &start, const vec3_t &delta, const vec3_t &sphere_center, float radius, float *out_t1, float *out_t2 ) {
    vec3_t sphere_to_ray;
    float  a, b, c, discrim, oo2a;

    sphere_to_ray = start - sphere_center;
    a             = delta.dot( delta ); 
    
    // this would occur in the case of a zero-length ray.
    if( !a ) {
        *out_t1 = 0.f;
        *out_t2 = 0.f;

        return sphere_to_ray.length_sqr( ) <= ( radius * radius );
    }

    b = 2.f * sphere_to_ray.dot( delta );
    c = sphere_to_ray.dot( sphere_to_ray ) - ( radius * radius );

    discrim = b * b - 4.f * a * c;
    if( discrim < 0.f )
        return false;

    discrim = std::sqrt( discrim );
    oo2a    = 0.5f / a;

    *out_t1 = ( -b - discrim ) * oo2a;
    *out_t2 = ( -b + discrim ) * oo2a;

    return true;
}

bool math::IntersectRayWithSphere( const vec3_t &start, const vec3_t &delta, const vec3_t &sphere_center, float radius, float *out_t1, float *out_t2 ) {
    if( !IntersectInfiniteRayWithSphere( start, delta, sphere_center, radius, out_t1, out_t2 ) )
        return false;

    if( *out_t1 > 1.0f || *out_t2 < 0.0f )
        return false;

    // clamp intersection points.
    *out_t1 = std::max( 0.f, *out_t1 );
    *out_t2 = std::min( 1.f, *out_t2 );

    return true;
}

vec3_t math::Interpolate( const vec3_t from, const vec3_t to, const float percent ) {
    return to * percent + from * ( 1.f - percent );
}