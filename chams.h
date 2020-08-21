#pragma once

class Chams {
public:
	enum model_type_t : uint32_t {
		invalid = 0,
		player,
		weapon,
		arms,
		view_weapon
	};

public:
	model_type_t GetModelType( const ModelRenderInfo_t& info );
	bool IsInViewPlane( const vec3_t& world );

	void SetColor( Color col, IMaterial* mat = nullptr );
	void SetAlpha( float alpha, IMaterial* mat = nullptr );
	void SetupMaterial( IMaterial* mat, Color col, bool z_flag );

	void init( );

	bool OverridePlayer( int index );
	bool GenerateLerpedMatrix( int index, BoneArray* out );
	void RenderHistoryChams( int index );
	bool DrawModel( uintptr_t ctx, const DrawModelState_t& state, const ModelRenderInfo_t& info, matrix3x4_t* bone );
	void SceneEnd( );

	void RenderPlayer( Player* player );
	bool SortPlayers( );

public:
	std::vector< Player* > m_players;
	bool m_running;
	IMaterial* debugambientcube;
	IMaterial* debugdrawflat;
};

extern Chams g_chams;