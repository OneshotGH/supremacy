#pragma once

class AimPlayer;

class LagCompensation {
public:
	enum LagType : size_t {
		INVALID = 0,
		CONSTANT,
		ADAPTIVE,
		RANDOM,
	};

public:
	bool StartPrediction( AimPlayer* player );
	void PlayerMove( LagRecord* record );
	void AirAccelerate( LagRecord* record, ang_t angle, float fmove, float smove );
	void PredictAnimations( CCSGOPlayerAnimState* state, LagRecord* record );
};

extern LagCompensation g_lagcomp;