#pragma once

#define END_OF_FREE_LIST	-1
#define ENTRY_IN_USE		-2

struct GlowObjectDefinition_t {
	Entity *m_entity;
	vec3_t m_color;
	float  m_alpha;
	PAD( 0x8 );
	float  m_bloom_amount;
	PAD( 0x4 );
	bool   m_render_occluded;
	bool   m_render_unoccluded;
	bool   m_render_full_bloom;
	PAD( 0x1 );
	int    m_full_bloom_stencil;
	PAD( 0x4 );
	int    m_slot;
	int    m_next_free_slot;
};

class CGlowObjectManager {
public:
	CUtlVector< GlowObjectDefinition_t >	m_object_definitions;
	int										m_first_free_slot;
};