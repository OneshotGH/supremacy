#pragma once

// pre-declare.
class Entity;

class IEntityListener {
public:
	virtual void OnEntityCreated( Entity *ent ) = 0;
    // virtual void OnEntitySpawned( Entity *ent ) = 0; // note - dex; doesn't seem used on the client?
    virtual void OnEntityDeleted( Entity *ent ) = 0;
};

class CEntInfo {
public:
	Entity*		m_pEntity;
	int			m_SerialNumber;
	CEntInfo*	m_pPrev;
	CEntInfo*	m_pNext;
};

class IClientEntityList {
public:
	enum indices : size_t {
		GETCLIENTENTITY = 3,
		GETCLIENTENTITYFROMHANDLE = 4,
		GETHIGHESTENTITYINDEX = 6,
	};

public:
	template< typename t = Entity* >
	__forceinline t GetClientEntity( int index ) {
		return util::get_method< t( __thiscall* )( decltype( this ), int ) >( this, GETCLIENTENTITY )( this, index );
	}

	template< typename t = Entity* >
	__forceinline t GetClientEntityFromHandle( EHANDLE handle ) {
		return util::get_method< t( __thiscall* )( decltype( this ), EHANDLE ) >( this, GETCLIENTENTITYFROMHANDLE )( this, handle );
	}

	template< typename t = Entity* >
	__forceinline t GetClientEntityFromHandle( ulong_t handle ) {
		return util::get_method< t( __thiscall* )( decltype( this ), ulong_t ) >( this, GETCLIENTENTITYFROMHANDLE )( this, handle );
	}

	__forceinline int GetHighestEntityIndex( ) {
		return util::get_method< int( __thiscall* )( decltype( this ) ) >( this, GETHIGHESTENTITYINDEX )( this );
	}
};