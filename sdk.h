#pragma once

// padding macro, please use, counts pads in class automaticly
#define CONCAT_IMPL( x, y ) x##y
#define MACRO_CONCAT( x, y ) CONCAT_IMPL( x, y )
#define PAD( size ) uint8_t MACRO_CONCAT( _pad, __COUNTER__ )[ size ];

// pre-declares.
class Player;
class Weapon;
class Entity;
class WeaponInfo;
class matrix3x4_t;
class vec3_t;
class ang_t;

struct BoxTraceInfo_t;
struct CBaseTrace;

#include "game.h"
#include "math.h"
#include "vector2.h"
#include "vector3.h"
#include "angle.h"
#include "matrix.h"
#include "memalloc.h"
#include "basehandle.h"
#include "color.h"
#include "utlvector.h"
#include "clientclass.h"
#include "datamap.h"
#include "entlist.h"
#include "clientdll.h"
#include "clientmode.h"
#include "engineclient.h"
#include "cvar.h"
#include "globalvars.h"
#include "input.h"
#include "surface.h"
#include "glow.h"
#include "studio.h"
#include "prediction.h"
#include "trace.h"
#include "studiorender.h"
#include "gameevents.h"
#include "matchframework.h"
#include "hud.h"
#include "localize.h"
#include "beams.h"
#include "networkstringtable.h"
#include "sound.h"