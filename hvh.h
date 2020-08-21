#pragma once

class AdaptiveAngle {
public:
	float m_yaw;
	float m_dist;

public:
	// ctor.
	__forceinline AdaptiveAngle( float yaw, float penalty = 0.f ) {
		// set yaw.
		m_yaw = math::NormalizedAngle( yaw );

		// init distance.
		m_dist = 0.f;

		// remove penalty.
		m_dist -= penalty;
	}
};

enum AntiAimMode : size_t {
	STAND = 0,
	WALK,
	AIR,
};

class HVH {
public:
	size_t m_mode;
	int    m_pitch;
	int    m_yaw;
	float  m_jitter_range;
	float  m_rot_range;
	float  m_rot_speed;
	float  m_rand_update;
	int    m_dir;
	float  m_dir_custom;
	size_t m_base_angle;
	float  m_auto_time;

	bool   m_step_switch;
	int    m_random_lag;
	float  m_next_random_update;
	float  m_random_angle;
	float  m_direction;
	float  m_auto;
	float  m_auto_dist;
	float  m_auto_last;
	float  m_view;

public:
	void IdealPitch( );
	void AntiAimPitch( );
	void AutoDirection( );
	void GetAntiAimDirection( );
    bool DoEdgeAntiAim( Player *player, ang_t &out );
	void DoRealAntiAim( );
	void DoFakeAntiAim( );
	void AntiAim( );
	void SendPacket( );
};

extern HVH g_hvh;