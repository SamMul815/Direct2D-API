#pragma once
#include "Enemy.h"

class Enemy_Slime_Ice  : public Enemy
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

	Enemy_Slime_Ice();
	~Enemy_Slime_Ice();
};

