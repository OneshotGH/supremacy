#pragma once

class Movement {
public:
	float  m_speed;
	float  m_ideal;
	float  m_ideal2;
	vec3_t m_mins;
	vec3_t m_maxs;
	vec3_t m_origin;
	float  m_switch_value = 1.f;
	int    m_strafe_index;
	float  m_old_yaw;
	float  m_circle_yaw;
	bool   m_invert;

public:
	void JumpRelated( );
	void Strafe( );
	void DoPrespeed( );
	bool GetClosestPlane( vec3_t& plane );
	bool WillCollide( float time, float step );
	void FixMove( CUserCmd* cmd, const ang_t& old_angles );
	void AutoPeek( );
	void QuickStop( );
	void FakeWalk( );
};

extern Movement g_movement;