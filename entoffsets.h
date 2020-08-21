#pragma once

class EntOffsets {
public:
    // holds a xored netvar... should be in the data section.
    template< const uint32_t key, const uint32_t xor_extra > class XoredNetvar {
    public:
        uint32_t m_xored_offset;

        // default ctor.
        __forceinline XoredNetvar() : m_xored_offset{ 0u } {}

        // xor our netvar and add the extra offset for xor.
        __forceinline void init( const size_t offset ) {
            m_xored_offset = ( offset ^ key ) + xor_extra;
        }

        // returns the real netvar offset at runtime.
        __forceinline size_t get( ) const {
            return ( m_xored_offset - xor_extra ) ^ key;
        }

        __forceinline operator size_t( ) const {
            return get( );
        }
    };

    // note - dex; key and counter must be here for true compile-time.
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_vecOrigin;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_vecOldOrigin;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_vecVelocity;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_vecMins;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_vecMaxs;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_iTeamNum;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_nSequence;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_flCycle;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_flC4Blow;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_bBombTicking;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_hPlayer;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_fEffects;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_nModelIndex;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_bReadyToDraw;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_vecAbsVelocity;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_lifeState;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_fFlags;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_MoveType;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_iHealth;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_iAccount;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_bHasDefuser;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_nHitboxSet;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_angAbsRotation;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_angRotation;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_angNetworkAngles;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_nTickBase;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_flNextAttack;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_flDuckAmount;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_flSimulationTime;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_flOldSimulationTime;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_flLowerBodyYawTarget;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_fImmuneToGunGameDamageTime;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_bHasHelmet;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_bClientSideAnimation;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_bHasHeavyArmor;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_bIsScoped;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_bDucking;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_bSpotted;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_iObserverMode;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_ArmorValue;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_flMaxspeed;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_surfaceFriction;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_flFlashBangTime;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_angEyeAngles;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_aimPunchAngle;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_viewPunchAngle;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_aimPunchAngleVel;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_vecViewOffset;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_PlayerCommand;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_pCurrentCommand;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_iEFlags;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_flPoseParameter;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_hMyWearables;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_BoneCache;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_hObserverTarget;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_hActiveWeapon;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_hGroundEntity;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_CustomMaterials;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_CustomMaterials2;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_VisualsDataProcessors;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_bCustomMaterialInitialized;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_iItemDefinitionIndex;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_iClip1;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_iPrimaryReserveAmmoCount;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_Activity;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_fFireDuration;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_iBurstShotsRemaining;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_flNextPrimaryAttack;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_flNextSecondaryAttack;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_flThrowStrength;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_fNextBurstShot;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_zoomLevel;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_flRecoilIndex;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_weaponMode;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_nFallbackPaintKit;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_nFallbackStatTrak;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_nFallbackSeed;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_flFallbackWear;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_iViewModelIndex;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_iWorldModelIndex;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_iAccountID;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_iItemIDHigh;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_iEntityQuality;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_OriginalOwnerXuidLow;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_OriginalOwnerXuidHigh;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_bPinPulled;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_fThrowTime;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_hWeapon;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_hWeaponWorldModel;
	XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_fLastShotTime;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_hOwnerEntity;
	XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_flDeathYaw;
	XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_flAbsYaw;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_flConstraintRadius;
    XoredNetvar< GET_XOR_KEYUI32, __COUNTER__ > m_hMyWeapons;

    void init( ) {
        // initialize a xored netvar.
        #define INIT_XOREDNETVAR( member_var, table_hash, prop_hash ) \
            member_var.init( g_netvars.get( table_hash, prop_hash ) );

        // same as above, but you must manually input the offset.
        // good for if you need something near a netvar.
        #define INIT_XOREDNETVAR_SPECIFIC( member_var, offset ) \
            member_var.init( offset );

        INIT_XOREDNETVAR( m_vecOrigin,                  HASH( "DT_BasePlayer" ),           HASH( "m_vecOrigin" ) );
        INIT_XOREDNETVAR( m_vecVelocity,                HASH( "DT_CSPlayer" ),             HASH( "m_vecVelocity[0]" ) );
        INIT_XOREDNETVAR( m_vecMins,                    HASH( "DT_BaseEntity" ),           HASH( "m_vecMins" ) );
        INIT_XOREDNETVAR( m_vecMaxs,                    HASH( "DT_BaseEntity" ),           HASH( "m_vecMaxs" ) );
        INIT_XOREDNETVAR( m_iTeamNum,                   HASH( "DT_BaseEntity" ),           HASH( "m_iTeamNum" ) );
        INIT_XOREDNETVAR( m_nSequence,                  HASH( "DT_PredictedViewModel" ),   HASH( "m_nSequence" ) );
        INIT_XOREDNETVAR( m_flCycle,                    HASH( "DT_CSPlayer" ),             HASH( "m_flCycle" ) );
        INIT_XOREDNETVAR( m_flC4Blow,                   HASH( "DT_PlantedC4" ),            HASH( "m_flC4Blow" ) );
        INIT_XOREDNETVAR( m_bBombTicking,               HASH( "DT_PlantedC4" ),            HASH( "m_bBombTicking" ) );
        INIT_XOREDNETVAR( m_nModelIndex,                HASH( "DT_BasePlayer" ),           HASH( "m_nModelIndex" ) );
        INIT_XOREDNETVAR( m_lifeState,                  HASH( "DT_BasePlayer" ),           HASH( "m_lifeState" ) );
        INIT_XOREDNETVAR( m_fFlags,                     HASH( "DT_BasePlayer" ),           HASH( "m_fFlags" ) );
        INIT_XOREDNETVAR( m_MoveType,                   HASH( "C_BaseEntity" ),            HASH( "m_MoveType" ) );
        INIT_XOREDNETVAR( m_iHealth,                    HASH( "DT_CSPlayer" ),             HASH( "m_iHealth" ) );
        INIT_XOREDNETVAR( m_iAccount,                   HASH( "DT_CSPlayer" ),             HASH( "m_iAccount" ) );
        INIT_XOREDNETVAR( m_bHasDefuser,                HASH( "DT_CSPlayer" ),             HASH( "m_bHasDefuser" ) );
        INIT_XOREDNETVAR( m_nHitboxSet,                 HASH( "DT_BaseAnimating" ),        HASH( "m_nHitboxSet" ) );
        INIT_XOREDNETVAR( m_angAbsRotation,             HASH( "C_BaseEntity" ),            HASH( "m_angAbsRotation" ) );
        INIT_XOREDNETVAR( m_angRotation,                HASH( "C_BaseEntity" ),            HASH( "m_angRotation" ) );
        INIT_XOREDNETVAR( m_angNetworkAngles,           HASH( "C_BaseEntity" ),            HASH( "m_angNetworkAngles" ) );
        INIT_XOREDNETVAR( m_nTickBase,                  HASH( "DT_CSPlayer" ),             HASH( "m_nTickBase" ) );
        INIT_XOREDNETVAR( m_flNextAttack,               HASH( "DT_CSPlayer" ),             HASH( "m_flNextAttack" ) );
        INIT_XOREDNETVAR( m_flDuckAmount,               HASH( "DT_BasePlayer" ),           HASH( "m_flDuckAmount" ) );
        INIT_XOREDNETVAR( m_flSimulationTime,           HASH( "DT_BaseEntity" ),           HASH( "m_flSimulationTime" ) );
        INIT_XOREDNETVAR( m_flLowerBodyYawTarget,       HASH( "DT_CSPlayer" ),             HASH( "m_flLowerBodyYawTarget" ) );
        INIT_XOREDNETVAR( m_fImmuneToGunGameDamageTime, HASH( "DT_CSPlayer" ),             HASH( "m_fImmuneToGunGameDamageTime" ) );
        INIT_XOREDNETVAR( m_bHasHelmet,                 HASH( "DT_CSPlayer" ),             HASH( "m_bHasHelmet" ) );
        INIT_XOREDNETVAR( m_bClientSideAnimation,       HASH( "DT_CSPlayer" ),             HASH( "m_bClientSideAnimation" ) );
        INIT_XOREDNETVAR( m_bHasHeavyArmor,             HASH( "DT_CSPlayer" ),             HASH( "m_bHasHeavyArmor" ) );
        INIT_XOREDNETVAR( m_bIsScoped,                  HASH( "DT_CSPlayer" ),             HASH( "m_bIsScoped" ) );
        INIT_XOREDNETVAR( m_bDucking,                   HASH( "DT_CSPlayer" ),             HASH( "m_bDucking" ) );
        INIT_XOREDNETVAR( m_bSpotted,                   HASH( "DT_BaseEntity" ),           HASH( "m_bSpotted" ) );
        INIT_XOREDNETVAR( m_iObserverMode,              HASH( "DT_BasePlayer" ),           HASH( "m_iObserverMode" ) );
        INIT_XOREDNETVAR( m_ArmorValue,                 HASH( "DT_BasePlayer" ),           HASH( "m_ArmorValue" ) );
        INIT_XOREDNETVAR( m_flMaxspeed,                 HASH( "DT_BasePlayer" ),           HASH( "m_flMaxspeed" ) );
        INIT_XOREDNETVAR( m_surfaceFriction,            HASH( "C_BasePlayer" ),            HASH( "m_surfaceFriction" ) );
        INIT_XOREDNETVAR( m_angEyeAngles,               HASH( "DT_CSPlayer" ),             HASH( "m_angEyeAngles" ) );
        INIT_XOREDNETVAR( m_aimPunchAngle,              HASH( "DT_CSPlayer" ),             HASH( "m_aimPunchAngle" ) );
        INIT_XOREDNETVAR( m_viewPunchAngle,             HASH( "DT_CSPlayer" ),             HASH( "m_viewPunchAngle" ) );
        INIT_XOREDNETVAR( m_aimPunchAngleVel,           HASH( "DT_CSPlayer" ),             HASH( "m_aimPunchAngleVel" ) );
        INIT_XOREDNETVAR( m_vecViewOffset,              HASH( "DT_CSPlayer" ),             HASH( "m_vecViewOffset[0]" ) );
        INIT_XOREDNETVAR( m_flPoseParameter,            HASH( "DT_CSPlayer" ),             HASH( "m_flPoseParameter" ) );
        INIT_XOREDNETVAR( m_hMyWearables,               HASH( "DT_BaseCombatCharacter" ),  HASH( "m_hMyWearables" ) );
        INIT_XOREDNETVAR( m_hObserverTarget,            HASH( "DT_CSPlayer" ),             HASH( "m_hObserverTarget" ) );
        INIT_XOREDNETVAR( m_hActiveWeapon,              HASH( "DT_BaseCombatCharacter" ),  HASH( "m_hActiveWeapon" ) );
        INIT_XOREDNETVAR( m_hGroundEntity,              HASH( "DT_CSPlayer" ),             HASH( "m_hGroundEntity" ) );
        INIT_XOREDNETVAR( m_iItemDefinitionIndex,       HASH( "DT_BaseAttributableItem" ), HASH( "m_iItemDefinitionIndex" ) );
        INIT_XOREDNETVAR( m_iClip1,                     HASH( "DT_BaseCombatWeapon" ),     HASH( "m_iClip1" ) );
        INIT_XOREDNETVAR( m_iPrimaryReserveAmmoCount,   HASH( "DT_BaseCombatWeapon" ),     HASH( "m_iPrimaryReserveAmmoCount" ) );
        INIT_XOREDNETVAR( m_Activity,                   HASH( "CBaseCombatWeapon" ),       HASH( "m_Activity" ) );
        INIT_XOREDNETVAR( m_fFireDuration,              HASH( "CBaseCombatWeapon" ),       HASH( "m_fFireDuration" ) );
        INIT_XOREDNETVAR( m_iBurstShotsRemaining,       HASH( "CWeaponCSBaseGun" ),        HASH( "m_iBurstShotsRemaining" ) );
        INIT_XOREDNETVAR( m_flNextPrimaryAttack,        HASH( "DT_BaseCombatWeapon" ),     HASH( "m_flNextPrimaryAttack" ) );
        INIT_XOREDNETVAR( m_flNextSecondaryAttack,      HASH( "DT_BaseCombatWeapon" ),     HASH( "m_flNextSecondaryAttack" ) );
        INIT_XOREDNETVAR( m_flThrowStrength,            HASH( "DT_BaseCSGrenade" ),        HASH( "m_flThrowStrength" ) );
        INIT_XOREDNETVAR( m_fNextBurstShot,             HASH( "CWeaponCSBaseGun" ),        HASH( "m_fNextBurstShot" ) );
        INIT_XOREDNETVAR( m_zoomLevel,                  HASH( "CWeaponCSBaseGun" ),        HASH( "m_zoomLevel" ) );
        INIT_XOREDNETVAR( m_flRecoilIndex,              HASH( "DT_WeaponNegev" ),          HASH( "m_flRecoilIndex" ) );
        INIT_XOREDNETVAR( m_weaponMode,                 HASH( "CWeaponCSBase" ),           HASH( "m_weaponMode" ) );
        INIT_XOREDNETVAR( m_nFallbackPaintKit,          HASH( "DT_BaseAttributableItem" ), HASH( "m_nFallbackPaintKit" ) );
        INIT_XOREDNETVAR( m_nFallbackStatTrak,          HASH( "DT_BaseAttributableItem" ), HASH( "m_nFallbackStatTrak" ) );
        INIT_XOREDNETVAR( m_nFallbackSeed,              HASH( "DT_BaseAttributableItem" ), HASH( "m_nFallbackSeed" ) );
        INIT_XOREDNETVAR( m_flFallbackWear,             HASH( "DT_BaseAttributableItem" ), HASH( "m_flFallbackWear" ) );
        INIT_XOREDNETVAR( m_iViewModelIndex,            HASH( "DT_BaseCombatWeapon" ),     HASH( "m_iViewModelIndex" ) );
        INIT_XOREDNETVAR( m_iWorldModelIndex,           HASH( "DT_BaseCombatWeapon" ),     HASH( "m_iWorldModelIndex" ) );
        INIT_XOREDNETVAR( m_iAccountID,                 HASH( "DT_BaseCombatWeapon" ),     HASH( "m_iAccountID" ) );
        INIT_XOREDNETVAR( m_iItemIDHigh,                HASH( "DT_BaseCombatWeapon" ),     HASH( "m_iItemIDHigh" ) );
        INIT_XOREDNETVAR( m_iEntityQuality,             HASH( "DT_BaseCombatWeapon" ),     HASH( "m_iEntityQuality" ) );
        INIT_XOREDNETVAR( m_OriginalOwnerXuidLow,       HASH( "DT_BaseAttributableItem" ), HASH( "m_OriginalOwnerXuidLow" ) );
        INIT_XOREDNETVAR( m_OriginalOwnerXuidHigh,      HASH( "DT_BaseAttributableItem" ), HASH( "m_OriginalOwnerXuidHigh" ) );
        INIT_XOREDNETVAR( m_bPinPulled,                 HASH( "DT_BaseCSGrenade" ),        HASH( "m_bPinPulled" ) );
        INIT_XOREDNETVAR( m_fThrowTime,                 HASH( "DT_BaseCSGrenade" ),        HASH( "m_fThrowTime" ) );
        INIT_XOREDNETVAR( m_hWeapon,                    HASH( "DT_PredictedViewModel" ),   HASH( "m_hWeapon" ) );
        INIT_XOREDNETVAR( m_hWeaponWorldModel,          HASH( "DT_BaseCombatWeapon" ),     HASH( "m_hWeaponWorldModel" ) );
        INIT_XOREDNETVAR( m_hOwnerEntity,               HASH( "DT_CSPlayer" ),             HASH( "m_hOwnerEntity" ) );
		INIT_XOREDNETVAR( m_fLastShotTime,				HASH( "DT_WeaponCSBase" ),		   HASH( "m_fLastShotTime" ) );
		INIT_XOREDNETVAR( m_hPlayer,					HASH( "DT_CSRagdoll" ),			   HASH( "m_hPlayer" ) );
		INIT_XOREDNETVAR( m_flDeathYaw,					HASH( "DT_CSRagdoll" ),			   HASH( "m_flDeathYaw" ) );
		INIT_XOREDNETVAR( m_flAbsYaw,					HASH( "DT_CSRagdoll" ),			   HASH( "m_flAbsYaw" ) );
        INIT_XOREDNETVAR( m_flConstraintRadius,			HASH( "DT_CSPlayer" ),             HASH( "m_flConstraintRadius" ) );
        INIT_XOREDNETVAR( m_hMyWeapons,			        HASH( "DT_CSPlayer" ),             HASH( "m_hMyWeapons" ) );

        INIT_XOREDNETVAR_SPECIFIC( m_flOldSimulationTime,        g_netvars.get( HASH( "DT_BaseEntity" ),       HASH( "m_flSimulationTime" ) ) + sizeof( float ) );
        INIT_XOREDNETVAR_SPECIFIC( m_CustomMaterials,            g_netvars.get( HASH( "DT_BaseCombatWeapon" ), HASH( "m_Item" ) ) + 0x14 );
        INIT_XOREDNETVAR_SPECIFIC( m_VisualsDataProcessors,      g_netvars.get( HASH( "DT_BaseCombatWeapon" ), HASH( "m_Item" ) ) + 0x220 );
        INIT_XOREDNETVAR_SPECIFIC( m_vecOldOrigin,               0x3A8 );
        INIT_XOREDNETVAR_SPECIFIC( m_fEffects,                   0xEC );
        INIT_XOREDNETVAR_SPECIFIC( m_bReadyToDraw,               0x270 );
        INIT_XOREDNETVAR_SPECIFIC( m_vecAbsVelocity,             0x94 );
        INIT_XOREDNETVAR_SPECIFIC( m_flFlashBangTime,            0xA2E8 );
        INIT_XOREDNETVAR_SPECIFIC( m_PlayerCommand,              0x326C );
        INIT_XOREDNETVAR_SPECIFIC( m_pCurrentCommand,            0x3314 );
        INIT_XOREDNETVAR_SPECIFIC( m_iEFlags,                    0xE4 );
        INIT_XOREDNETVAR_SPECIFIC( m_BoneCache,                  0x2900 );
        INIT_XOREDNETVAR_SPECIFIC( m_CustomMaterials2,           0x9DC );
        INIT_XOREDNETVAR_SPECIFIC( m_bCustomMaterialInitialized, 0x32DD );

        // don't want these macros outside of this file.
        #undef INIT_XOREDNETVAR
        #undef INIT_XOREDNETVAR_SPECIFIC
    }
};

extern EntOffsets g_entoffsets;
