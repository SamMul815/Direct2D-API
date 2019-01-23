#pragma once
#include "Enemy.h"
#include <vector>


class Enemy_Slime_Green : public Enemy
{
private:
	vector<int> _vPattern;
	Animation*	_ani;
public:
	virtual HRESULT Init();
	virtual void Update();
	virtual void Render();
	virtual void Revision();
	virtual void Move();

	Enemy_Slime_Green();
	~Enemy_Slime_Green();
};

