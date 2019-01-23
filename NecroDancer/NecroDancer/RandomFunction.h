#pragma once
#include "SingletonBase.h"
#include <time.h>

class RandomFunction : public SingletonBase < RandomFunction >
{
public:
	RandomFunction()
	{
		srand(GetTickCount());
	}
	~RandomFunction()
	{

	}

	//int�� ������ �̾ƺ���!
	inline int GetInt(int num) { return rand() % num; }
	inline int GetFromIntTo(int fromNum, int toNum) { return rand() % (toNum - fromNum + 1) + fromNum; }

	//float�� ������
	float GetFloat() { return (float)rand() / (float)RAND_MAX; }
	float GetFloat(float num) { return ((float)rand() / (float)RAND_MAX) * num; }
	float GetFromFloatTo(float fromFloat, float toFloat)
	{
		float rnd = (float)rand() / (float)RAND_MAX;

		return (rnd * (toFloat - fromFloat) + fromFloat);
	}

};
