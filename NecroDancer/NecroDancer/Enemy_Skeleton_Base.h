#pragma once
#include "Enemy.h"
#include "Player.h"
//enum SKELETON_BASE_AI
//{
//	BASE_AI_STOP,
//	BASE_AI_MOVEUP,
//	BASE_AI_MOVEDOWN,
//	BASE_AI_MOVELEFT,
//	BASE_AI_MOVERIGHT
//};

class Enemy_Skeleton_Base : public Enemy
{
private:
	Player* _player;
	Animation* _ani;
	bool _moveCheck;
public:
	virtual HRESULT Init();
	virtual void Update();
	virtual void Render();
	virtual void Revision();
	virtual void Move();
	int AI();
	virtual void LinkPlayer(Player* player) { _player = player; }
	Enemy_Skeleton_Base();
	~Enemy_Skeleton_Base();
};

