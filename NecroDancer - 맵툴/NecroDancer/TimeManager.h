#pragma once
#include "SingletonBase.h"
#include "Timer.h"
#include "D2DText.h"

class TimeManager : public SingletonBase < TimeManager >
{
private:
	Timer*	_timer;
	D2DText* _text;
public:
	HRESULT Init(void);
	void Release(void);
	void Update(float lock = 0.0f);
	void Render();

	//������ ȭ�鿡 ���! �� ���� ������ ��������
	inline float GetElapsedTime(void) const { return _timer->GetElapsedTime(); }
	inline float GetWorldTime(void) const { return _timer->GetWorldTime(); }

	TimeManager();
	~TimeManager();
};