#pragma once

class quaternion_t {
public:
	float x, y, z, w;
};

class vec3_t {
public:
	// data member variables
	float x, y, z;

public:
	// ctors.
	__forceinline vec3_t( ) : x{}, y{}, z{} {}
	__forceinline vec3_t( float x, float y, float z ) : x{ x }, y{ y }, z{ z } {}

	// at-accesors.
	__forceinline float& at( const size_t index ) {
		return ( ( float* )this )[ index ];
	}
	__forceinline float& at( const size_t index ) const {
		return ( ( float* )this )[ index ];
	}

	// index operators.
	__forceinline float& operator( )( const size_t index ) {
		return at( index );
	}
	__forceinline const float& operator( )( const size_t index ) const {
		return at( index );
	}
	__forceinline float& operator[ ]( const size_t index ) {
		return at( index );
	}
	__forceinline const float& operator[ ]( const size_t index ) const {
		return at( index );
	}

	// equality operators.
	__forceinline bool operator==( const vec3_t& v ) const {
		return v.x == x && v.y == y && v.z == z;
	}
	__forceinline bool operator!=( const vec3_t& v ) const {
		return v.x != x || v.y != y || v.z != z;
	}

	// copy assignment.
	__forceinline vec3_t& operator=( const vec3_t& v ) {
		x = v.x;
		y = v.y;
		z = v.z;
		return *this;
	}

	// negation-operator.
	__forceinline vec3_t operator-( ) const {
		return vec3_t{ -x, -y, -z };
	}

	// arithmetic operators.
	__forceinline vec3_t operator+( const vec3_t& v ) const {
		return {
			x + v.x,
			y + v.y,
			z + v.z
		};
	}

	__forceinline vec3_t operator-( const vec3_t& v ) const {
		return {
			x - v.x,
			y - v.y,
			z - v.z
		};
	}

	__forceinline vec3_t operator*( const vec3_t& v ) const {
		return {
			x * v.x,
			y * v.y,
			z * v.z
		};
	}

	__forceinline vec3_t operator/( const vec3_t& v ) const {
		return {
			x / v.x,
			y / v.y,
			z / v.z
		};
	}

	// compound assignment operators.
	__forceinline vec3_t& operator+=( const vec3_t& v ) {
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	__forceinline vec3_t& operator-=( const vec3_t& v ) {
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	__forceinline vec3_t& operator*=( const vec3_t& v ) {
		x *= v.x;
		y *= v.y;
		z *= v.z;
		return *this;
	}

	__forceinline vec3_t& operator/=( const vec3_t& v ) {
		x /= v.x;
		y /= v.y;
		z /= v.z;
		return *this;
	}

	// arithmetic operators w/ float.
	__forceinline vec3_t operator+( float f ) const {
		return {
			x + f,
			y + f,
			z + f
		};
	}

	__forceinline vec3_t operator-( float f ) const {
		return {
			x - f,
			y - f,
			z - f
		};
	}

	__forceinline vec3_t operator*( float f ) const {
		return {
			x * f,
			y * f,
			z * f
		};
	}

	__forceinline vec3_t operator/( float f ) const {
		return {
			x / f,
			y / f,
			z / f
		};
	}

	// compound assignment operators w/ float.
	__forceinline vec3_t& operator+=( float f ) {
		x += f;
		y += f;
		z += f;
		return *this;
	}

	__forceinline vec3_t& operator-=( float f ) {
		x -= f;
		y -= f;
		z -= f;
		return *this;
	}

	__forceinline vec3_t& operator*=( float f ) {
		x *= f;
		y *= f;
		z *= f;
		return *this;
	}

	__forceinline vec3_t& operator/=( float f ) {
		x /= f;
		y /= f;
		z /= f;
		return *this;
	}

	// methods.
	__forceinline void clear( ) {
		x = y = z = 0.f;
	}

	__forceinline float length_sqr( ) const {
		return ( ( x * x ) + ( y * y ) + ( z * z ) );
	}

	__forceinline float length_2d_sqr( ) const {
		return ( ( x * x ) + ( y * y ) );
	}

	__forceinline float length( ) const {
		return std::sqrt( length_sqr( ) );
	}

	__forceinline float length_2d( ) const {
		return std::sqrt( length_2d_sqr( ) );
	}

	__forceinline float dot( const vec3_t& v ) const {
		return ( x * v.x + y * v.y + z * v.z );
	}

	__forceinline float dot( float* v ) const {
		return ( x * v[ 0 ] + y * v[ 1 ] + z * v[ 2 ] );
	}

	__forceinline vec3_t cross( const vec3_t &v ) const {
		return {
			( y * v.z ) - ( z * v.y ),
			( z * v.x ) - ( x * v.z ),
			( x * v.y ) - ( y * v.x )
		};
	}

	__forceinline float dist_to( const vec3_t &vOther ) const {
		vec3_t delta;

		delta.x = x - vOther.x;
		delta.y = y - vOther.y;
		delta.z = z - vOther.z;

		return delta.length_2d( );
	}

	__forceinline float normalize( ) {
		float len = length( );

		( *this ) /= ( length( ) + std::numeric_limits< float >::epsilon( ) );

		return len;
	}

	__forceinline vec3_t normalized( ) const {
		auto vec = *this;

		vec.normalize( );

		return vec;
	}
};

__forceinline vec3_t operator*( float f, const vec3_t& v ) {
	return v * f;
}

class __declspec( align( 16 ) ) vec_aligned_t : public vec3_t {
public:
	__forceinline vec_aligned_t( ) {}

	__forceinline vec_aligned_t( const vec3_t& vec ) {
		x = vec.x;
		y = vec.y;
		z = vec.z;
		w = 0.f;
	}

	float w;
};