#pragma once
#include "Enemy.h"
#include "Player.h"
#include "EnemyManager.h"
class Enemy_Skeleton_Armored : public Enemy
{
private:
	Player* _player;
	EnemyManager* _enemyManager;
	Animation* _ani;

	bool _moveCheck;
	bool _isRight;
public:
	virtual HRESULT Init();
	virtual void Update();
	virtual void Render();
	virtual void Revision();
	virtual void Move();
	int AI();
	virtual void LinkPlayer(Player* player) { _player = player; }
	virtual void LinkEnemyManager(EnemyManager* enemyManager) { _enemyManager = enemyManager; }
	virtual void DyingMessage();
	Enemy_Skeleton_Armored();
	~Enemy_Skeleton_Armored();
};

