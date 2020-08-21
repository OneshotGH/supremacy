#pragma once

enum LightType_t {
	MATERIAL_LIGHT_DISABLE = 0,
	MATERIAL_LIGHT_POINT,
	MATERIAL_LIGHT_DIRECTIONAL,
	MATERIAL_LIGHT_SPOT,
};

enum {
	STUDIORENDER_DRAW_ENTIRE_MODEL     = 0,
	STUDIORENDER_DRAW_OPAQUE_ONLY      = 0x01,
	STUDIORENDER_DRAW_TRANSLUCENT_ONLY = 0x02,
	STUDIORENDER_DRAW_GROUP_MASK       = 0x03,
	STUDIORENDER_DRAW_NO_FLEXES        = 0x04,
	STUDIORENDER_DRAW_STATIC_LIGHTING  = 0x08,
	STUDIORENDER_DRAW_ACCURATETIME     = 0x10,		// Use accurate timing when drawing the model.
	STUDIORENDER_DRAW_NO_SHADOWS       = 0x20,
	STUDIORENDER_DRAW_GET_PERF_STATS   = 0x40,
	STUDIORENDER_DRAW_WIREFRAME        = 0x80,
	STUDIORENDER_DRAW_ITEM_BLINK       = 0x100,
	STUDIORENDER_SHADOWDEPTHTEXTURE    = 0x200
};

enum {
	MATERIAL_VAR_DEBUG                    = 1,
	MATERIAL_VAR_NO_DEBUG_OVERRIDE        = 2,
	MATERIAL_VAR_NO_DRAW                  = 4,
	MATERIAL_VAR_USE_IN_FILLRATE_MODE     = 8,
	MATERIAL_VAR_VERTEXCOLOR              = 16,
	MATERIAL_VAR_VERTEXALPHA              = 32,
	MATERIAL_VAR_SELFILLUM                = 64,
	MATERIAL_VAR_ADDITIVE                 = 128,
	MATERIAL_VAR_ALPHATEST                = 256,
	MATERIAL_VAR_ZNEARER                  = 1024,
	MATERIAL_VAR_MODEL                    = 2048,
	MATERIAL_VAR_FLAT                     = 4096,
	MATERIAL_VAR_NOCULL                   = 8192,
	MATERIAL_VAR_NOFOG                    = 16384,
	MATERIAL_VAR_IGNOREZ                  = 32768,
	MATERIAL_VAR_DECAL                    = 65536,
	MATERIAL_VAR_ENVMAPSPHERE             = 131072,
	MATERIAL_VAR_ENVMAPCAMERASPACE        = 524288,
	MATERIAL_VAR_BASEALPHAENVMAPMASK      = 1048576,
	MATERIAL_VAR_TRANSLUCENT              = 2097152,
	MATERIAL_VAR_NORMALMAPALPHAENVMAPMASK = 4194304,
	MATERIAL_VAR_NEEDS_SOFTWARE_SKINNING  = 8388608,
	MATERIAL_VAR_OPAQUETEXTURE            = 16777216,
	MATERIAL_VAR_ENVMAPMODE               = 33554432,
	MATERIAL_VAR_SUPPRESS_DECALS          = 67108864,
	MATERIAL_VAR_HALFLAMBERT              = 134217728,
	MATERIAL_VAR_WIREFRAME                = 268435456,
	MATERIAL_VAR_ALLOWALPHATOCOVERAGE     = 536870912,
	MATERIAL_VAR_ALPHA_MODIFIED_BY_PROXY  = 1073741824,
};

struct LightDesc_t {
	LightType_t  m_Type;										//< MATERIAL_LIGHT_xxx
	vec3_t       m_Color;											//< color+intensity 
	vec3_t       m_Position;										//< light source center position
	vec3_t       m_Direction;										//< for SPOT, direction it is pointing
	float        m_Range;											//< distance range for light.0=infinite
	float        m_Falloff;										//< angular falloff exponent for spot lights
	float        m_Attenuation0;									//< constant distance falloff term
	float        m_Attenuation1;									//< linear term of falloff
	float        m_Attenuation2;									//< quadatic term of falloff
	float        m_Theta;											//< inner cone angle. no angular falloff 
	float        m_Phi;											//< outer cone angle
	float        m_ThetaDot;
	float        m_PhiDot;
	float        m_OneOverThetaDotMinusPhiDot;
	unsigned int m_Flags;
protected:
	float        m_RangeSquared;
};

struct studiomeshgroup_t {
	void			*m_pMesh;
	int				 m_NumStrips;
	int				 m_Flags;
	void	        *m_pStripData;
	unsigned short	*m_pGroupIndexToMeshIndex;
	int				 m_NumVertices;
	int				*m_pUniqueTris;
	unsigned short	*m_pIndices;
	bool			 m_MeshNeedsRestore;
	short			 m_ColorMeshID;
	void			*m_pMorph;
};

struct studiomeshdata_t {
	int					m_NumGroup;
	studiomeshgroup_t*	m_pMeshGroup;
};

class IMaterial;

struct studioloddata_t {
	studiomeshdata_t	*m_pMeshData;
	float				 m_SwitchPoint;
	int					 numMaterials;
	IMaterial			**ppMaterials;
	int					*pMaterialFlags;
	int					*m_pHWMorphDecalBoneRemap;
	int					 m_nDecalBoneCount;
};

struct studiohwdata_t {
	int					 m_RootLOD;
	int					 m_NumLODs;
	studioloddata_t		*m_pLODs;
	int					 m_NumStudioMeshes;
};

struct DrawModelInfo_t {
	studiohdr_t		*m_pStudioHdr;
	PAD( 0x8 );
	int				 m_Skin;
	int				 m_Body;
	int				 m_HitboxSet;
	void			*m_pClientEntity;
	int				 m_Lod;
	void        	*m_pColorMeshes;
	bool			 m_bStaticLighting;
	vec3_t			 m_vecAmbientCube[ 6 ];
	int				 m_nLocalLightCount;
	LightDesc_t		 m_LocalLightDescs[ 4 ];
};

struct DrawModelState_t {
	studiohdr_t*		 m_pStudioHdr;
	studiohwdata_t*		 m_pStudioHWData;
	void*		         m_pRenderable;
	const matrix3x4_t	*m_pModelToWorld;
	PAD( 0x4 );
	int					 m_drawFlags;
	int					 m_lod;
};

struct ModelRenderInfo_t {
	vec3_t				m_origin;			// 0
	ang_t				m_angles;			// 12
	void*				m_renderable;		// 24
	const model_t*		m_model;			// 28
	const matrix3x4_t*	m_model_to_world;	// 32
	const matrix3x4_t*	m_lighting_offset;	// 36
	const vec3_t*		m_lighting_origin;	// 40
	int					m_flags;			// 44
	int					m_index;			// 48
	int					m_skin;				// 52
	int					m_body;				// 56
	int					m_hitboxset;		// 60
	uint16_t			m_instance;			// 64

	__forceinline ModelRenderInfo_t( ) : m_model_to_world{}, m_lighting_offset{}, m_lighting_origin{} {}
};

class IClientShadowMgr {
public:
	enum indices : size_t {
		UNLOCKALLSHADOWDEPTHTEXTURES = 30,
		COMPUTESHADOWDEPTHTEXTURES   = 43,
	};
};

class IMaterial {
public:
	enum indices : size_t {
		GETNAME                 = 0,
		GETTEXTUREGROUPNAME     = 1,
		INCREMENTREFERENCECOUNT = 12,
		ALPHAMODULATE           = 27,
		COLORMODULATE           = 28,
		SETFLAG                 = 29,
		GETFLAG                 = 30
	};

	__forceinline const char* GetName( ) {
		return util::get_method< const char* ( __thiscall* )( void* ) >( this, GETNAME )( this );
	}

	__forceinline const char* GetTextureGroupName( ) {
		return util::get_method< const char* ( __thiscall* )( void* ) >( this, GETTEXTUREGROUPNAME )( this );
	}

	__forceinline void IncrementReferenceCount( ) {
		return util::get_method< void( __thiscall* )( void* ) >( this, INCREMENTREFERENCECOUNT )( this );
	}

	__forceinline void AlphaModulate( float alpha ) {
		return util::get_method< void( __thiscall* )( void*, float ) >( this, ALPHAMODULATE )( this, alpha );
	}

	__forceinline void ColorModulate( float r, float g, float b ) {
		return util::get_method< void( __thiscall* )( void*, float, float, float ) >( this, COLORMODULATE )( this, r, g, b );
	}

	__forceinline void ColorModulate( Color col ) {
		ColorModulate( col.r( ) / 255.f, col.g( ) / 255.f, col.b( ) / 255.f );
	}

	__forceinline void SetFlag( int fl, bool set ) {
		return util::get_method< void( __thiscall* )( void*, int, bool ) >( this, SETFLAG )( this, fl, set );
	}

	__forceinline bool GetFlag( int fl ) {
		return util::get_method< bool( __thiscall* )( void*, int ) >( this, GETFLAG )( this, fl );
	}
};

class IMaterialSystem {
public:
	enum indices : size_t {
		OVERRIDECONFIG  = 21,
		CREATEMATERIAL  = 83,
		FINDMATERIAL    = 84,
		FIRSTMATERIAL   = 86,
		NEXTMATERIAL    = 87,
		INVALIDMATERIAL = 88,
		GETMATERIAL     = 89
	};

	//__forceinline IMaterial* CreateMaterial( const char* name, KeyValues* kv ) {
	//	return util::get_method< IMaterial*( __thiscall* )( void*, const char*, KeyValues* ) >( this, CREATEMATERIAL )( this, name, kv );
	//}

	__forceinline IMaterial* FindMaterial( const char* name, char *type ) {
		return  util::get_method< IMaterial*( __thiscall* )( void *, const char*, char*, bool, void* ) >( this, FINDMATERIAL )( this, name, type, 1, 0 );
	}

	__forceinline uint16_t FirstMaterial( ) {
		return util::get_method< uint16_t( __thiscall* )( void* ) >( this, FIRSTMATERIAL )( this );
	}

	__forceinline uint16_t NextMaterial( uint16_t handle ) {
		return util::get_method< uint16_t( __thiscall* )( void*, uint16_t ) >( this, NEXTMATERIAL )( this, handle );
	}

	__forceinline uint16_t InvalidMaterial( ) {
		return util::get_method< uint16_t( __thiscall* )( void* ) >( this, INVALIDMATERIAL )( this );
	}

	__forceinline IMaterial* GetMaterial( uint16_t handle ) {
		return util::get_method< IMaterial*( __thiscall* )( void*, uint16_t ) >( this, GETMATERIAL )( this, handle );
	}

	// find material by hash.
	__forceinline IMaterial* FindMaterial( hash32_t hash ) {
		for( uint16_t h = FirstMaterial( ); h != InvalidMaterial( ); h = NextMaterial( h ) ) {
			IMaterial* mat = GetMaterial( h );
			if( !mat )
				continue;

			if( FNV1a::get( mat->GetName( ) ) == hash )
				return mat;
		}

		return nullptr;
	}
};

class CStudioRenderContext {
public:
	enum indices : size_t {
		DRAWMODEL              = 29,
		FORCEDMATERIALOVERRIDE = 33
	};

public:
	PAD( 0x250 );
	IMaterial* m_pForcedMaterial;

public:
	__forceinline void ForcedMaterialOverride( IMaterial* mat ) {
		return util::get_method< void( __thiscall* )( void *, IMaterial *, int, int ) >( this, FORCEDMATERIALOVERRIDE )( this, mat, 0, 0 );
	}
};

class IVModelRender {
public:
	enum indices : size_t {
		FORCEDMATERIALOVERRIDE = 1,
		ISFORCEDMATERIALOVERRIDE = 2,
		DRAWMODELEXECUTE       = 21
	};

	// dont use this, just a wrapper.
	// use the one from studiorender.
	//__forceinline void ForcedMaterialOverride( IMaterial* mat ) {
	//	return util::get_method< void( __thiscall* )( void *, IMaterial *, int, int ) >( this, FORCEDMATERIALOVERRIDE )( this, mat, 0, 0 );
	//}

	__forceinline bool IsForcedMaterialOverride( ) {
		return util::get_method< bool( __thiscall* )( void * ) >( this, ISFORCEDMATERIALOVERRIDE )( this );
	}
};

class IVRenderView {
public:
	enum indices : size_t {
		SETBLEND           = 4,
		SETCOLORMODULATION = 6,
		GETCOLORMODULATION = 7,
		SCENEEND           = 9,
		DRAWWORLDLISTS     = 14,
	};

	__forceinline void SetBlend( float blend ) {
		return util::get_method< void( __thiscall* )( void *, float )>( this, SETBLEND )( this, blend );
	}

	__forceinline void SetColorModulation( Color col ) {
		float color[] = { ( float )col.r( ) / 255,  ( float )col.g( ) / 255, ( float )col.b( ) / 255,  1.f };
		return util::get_method< void( __thiscall* )( void*, float* ) >( this, SETCOLORMODULATION )( this, color );
	}

	__forceinline Color GetColorModulation( ) {
		float color[ 4 ]{};
		util::get_method< void( __thiscall* )( void*, float* ) >( this, GETCOLORMODULATION )( this, color );

		return Color(
			( uint8_t )color[ 0 ] * 255,
			( uint8_t )color[ 1 ] * 255,
			( uint8_t )color[ 2 ] * 255,
			( uint8_t )color[ 3 ] * 255
		);
	}
};

class CViewRender {
public:
	enum indices : size_t {
		ONRENDERSTART          = 4,
		RENDERVIEW             = 6,
        GETPLAYERVIEWSETUP     = 12,
		RENDER2DEFFECTSPOSTHUD = 39,
		RENDERSMOKEOVERLAY     = 40,
	};

public:
    // virtuals.
    __forceinline const CViewSetup *GetPlayerViewSetup( int slot = -1 ) {
        return util::get_method< const CViewSetup *(__thiscall *)( decltype( this ), int ) >( this, GETPLAYERVIEWSETUP )( this, slot );
    }

public:
    // members.
	PAD( 0x4 );
	CViewSetup m_view;
};

struct MaterialVideoMode_t {
	int m_Width;
	int m_Height;
	int m_Format;
	int m_RefreshRate;
};

struct MaterialSystem_Config_t {
	MaterialVideoMode_t m_VideoMode;
	float               m_fMonitorGamma;
	float               m_fGammaTVRangeMin;
	float               m_fGammaTVRangeMax;
	float               m_fGammaTVExponent;
	bool                m_bGammaTVEnabled;
	bool                m_bTripleBuffered;
	int                 m_nAASamples;
	int                 m_nForceAnisotropicLevel;
	int                 m_nSkipMipLevels;
	int                 m_nDxSupportLevel;
	int                 m_nFlags;
	bool                m_bEditMode;
	char                m_nProxiesTestMode;
	bool                m_bCompressedTextures;
	bool                m_bFilterLightmaps;
	bool                m_bFilterTextures;
	bool                m_bReverseDepth;
	bool                m_bBufferPrimitives;
	bool                m_bDrawFlat;
	bool                m_bMeasureFillRate;
	bool                m_bVisualizeFillRate;
	bool                m_bNoTransparency;
	bool                m_bSoftwareLighting;
	bool                m_bAllowCheats;
	char                m_nShowMipLevels;
	bool                m_bShowLowResImage;
	bool                m_bShowNormalMap;
	bool                m_bMipMapTextures;
	char                m_nFullbright;
	bool                m_bFastNoBump;
	bool                m_bSuppressRendering;
	bool                m_bDrawGray;
	bool                m_bShowSpecular;
	bool                m_bShowDiffuse;
	int                 m_nWindowedSizeLimitWidth;
	int                 m_nWindowedSizeLimitHeight;
	int                 m_nAAQuality;
	bool                m_bShadowDepthTexture;
	bool                m_bMotionBlur;
	bool                m_bSupportFlashlight;
	bool                m_bPaintEnabled;
	PAD( 0xC );
};