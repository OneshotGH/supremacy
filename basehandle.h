#pragma once

class Entity;

#define NUM_ENT_ENTRY_BITS			(11 + 2)
#define NUM_ENT_ENTRIES				(1 << NUM_ENT_ENTRY_BITS)
#define INVALID_EHANDLE_INDEX		0xFFFFFFFF
#define NUM_SERIAL_NUM_BITS			16
#define NUM_SERIAL_NUM_SHIFT_BITS	(32 - NUM_SERIAL_NUM_BITS)
#define ENT_ENTRY_MASK				(( 1 << NUM_SERIAL_NUM_BITS) - 1)

class CBaseHandle {
public:
	__forceinline CBaseHandle( ) {
		m_Index = INVALID_EHANDLE_INDEX;
	}

	__forceinline CBaseHandle( const CBaseHandle& other ) {
		m_Index = other.m_Index;
	}

	__forceinline CBaseHandle( ulong_t value ) {
		m_Index = value;
	}

	__forceinline CBaseHandle( int iEntry, int iSerialNumber ) {
		Init( iEntry, iSerialNumber );
	}

	__forceinline void Init( int iEntry, int iSerialNumber ) {
		m_Index = iEntry | ( iSerialNumber << NUM_SERIAL_NUM_SHIFT_BITS );
	}

	__forceinline void Term( ) {
		m_Index = INVALID_EHANDLE_INDEX;
	}

	__forceinline bool IsValid( ) const {
		return m_Index != INVALID_EHANDLE_INDEX;
	}

	__forceinline int GetEntryIndex( ) const {
		if( !IsValid( ) )
			return NUM_ENT_ENTRIES - 1;

		return m_Index & ENT_ENTRY_MASK;
	}

	__forceinline int GetSerialNumber( ) const {
		return m_Index >> NUM_SERIAL_NUM_SHIFT_BITS;
	}

	__forceinline int ToInt( ) const {
		return ( int )( m_Index );
	}

	__forceinline bool operator !=( const CBaseHandle& other ) const {
		return m_Index != other.m_Index;
	}

	__forceinline bool operator ==( const CBaseHandle& other ) const {
		return m_Index == other.m_Index;
	}

	__forceinline bool operator ==( const void* pEnt ) const {
		return Get( ) == pEnt;
	}

	__forceinline bool operator !=( const void* pEnt ) const {
		return Get( ) != pEnt;
	}

	__forceinline const CBaseHandle& operator=( const void* pEntity ) {
		return Set( pEntity );
	}

	__forceinline const CBaseHandle& Set( const void* pEntity ) {
		if( !pEntity )
			m_Index = INVALID_EHANDLE_INDEX;

		return *this;
	}

	__forceinline void* CBaseHandle::Get( ) const {
		return nullptr;
	}

	ulong_t m_Index;
};

template< class t > class CHandle : public CBaseHandle {
public:
	__forceinline CHandle( ) {}

	__forceinline CHandle( int iEntry, int iSerialNumber ) {
		Init( iEntry, iSerialNumber );
	}

	__forceinline CHandle( const CBaseHandle& handle ) : CBaseHandle( handle ) {}

	__forceinline CHandle( t* pObj ) {
		Term( );
		Set( pObj );
	}

	__forceinline CHandle< t > FromIndex( int index ) {
		CHandle< t > ret;
		ret.m_Index = index;
		return ret;
	}

	__forceinline t* Get( ) const {
		return ( t * )( CBaseHandle::Get( ) );
	}

	__forceinline operator t*( ) {
		return Get( );
	}

	__forceinline operator t*( ) const {
		return Get( );
	}

	__forceinline bool operator !( ) const {
		return !Get( );
	}

	__forceinline bool operator==( t* val ) const {
		return Get( ) == val;
	}

	__forceinline bool operator!=( t* val ) const {
		return Get( ) != val;
	}

	__forceinline void Set( const t* pVal ) {
		CBaseHandle::Set( ( const void * )( pVal ) );
	}

	__forceinline const CBaseHandle& operator=( const t* val ) {
		Set( val );
		return *this;
	}

	__forceinline t* operator->( ) const {
		return Get( );
	}
};

using EHANDLE = CHandle< Entity >;