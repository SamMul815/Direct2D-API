#pragma once

class Timer
{
private:
	bool _isHardware;				//하드웨어 종류 타이머를 돌리기에 적합한가?
	float _timeScale;
	float _timeElapsed;
	__int64 _curTime;
	__int64 _lastTime;
	__int64 _periodFrequency;

	unsigned long _frameRate;
	unsigned long _FPSFrameCount;
	float _FPSTimeElapsed;
	float _worldTime;

public:
	HRESULT Init(void);
	void Tick(float lockFPS = 0.0f);
	unsigned long GetFrameRate(char* str = NULL) const;
	inline float GetElapsedTime(void) const { return _timeElapsed; }
	inline float GetWorldTime(void) const { return _worldTime; }


	Timer();
	~Timer();
};

