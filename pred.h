#pragma once

class InputPrediction {
public:
	float m_curtime;
	float m_frametime;

public:
	void update( );
	void run( );
	void restore( );
};

extern InputPrediction g_inputpred;