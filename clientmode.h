#pragma once

class CViewSetup {
public:
	int         m_x;					// 0x0000
	int         m_old_x;				// 0x0004
	int         m_y;					// 0x0008
	int	        m_old_y;				// 0x000C
	int         m_width;				// 0x0010
	int         m_old_width;			// 0x0014
	int         m_height;				// 0x0018
	int         m_old_height;			// 0x001C
	bool        m_ortho;				// 0x0020
	float       m_ortho_left;			// 0x0024
	float       m_ortho_top;			// 0x0028
	float       m_ortho_right;			// 0x002C
	float       m_ortho_bottom;			// 0x0030
	bool        m_custom_view_matrix;	// 0x0034
	matrix3x4_t m_custom_matrix;		// 0x0038
private:
	PAD( 0x48 );						// 0x0068
public:
	float       m_fov;                  // 0x00B0
	float       m_viewmodel_fov;		// 0x00B4
	vec3_t      m_origin;
	ang_t       m_angles;
	float       m_znear;
	float       m_zfar;
	float       m_znear_viewmodel;
	float       m_zfar_viewmodel;
	float       m_aspect_ratio;
	float       m_near_blur_depth;
	float       m_near_focus_depth;
	float       m_far_focus_depth;
	float       m_far_blur_depth;
	float       m_near_blur_radius;
	float       m_far_blur_radius;
	int         m_quality;
	int         m_motionblur_mode;
	float       m_shutter_time;
	vec3_t      m_shutter_open_pos;
	ang_t       m_shutter_open_angles;
	vec3_t      m_shutter_close_pos;
	ang_t       m_shutter_close_angles;
	float       m_offcenter_top;
	float       m_offcenter_bottom;
	float       m_offcenter_left;
	float       m_offcenter_right;
	int         m_edge_blur;
};

class IClientMode {
public:
	enum indices : size_t {
		SHOULDDRAWPARTICLES      = 16,
		SHOULDDRAWFOG            = 17,
		OVERRIDEVIEW             = 18,
		CREATEMOVE               = 24,
		DOPOSTSPACESCREENEFFECTS = 44,
	};
};