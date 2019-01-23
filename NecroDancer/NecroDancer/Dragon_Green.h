#pragma once
#include "Enemy.h"
#include "Player.h"
#include "EnemyManager.h"
class Dragon_Green : public Enemy
{
private:
	Player* _player;
	Animation* _ani;
	EnemyManager* _enemyManager;

	bool _moveCheck;
	bool _isRight;
	bool _isCry;
	bool _lookPlayer;

public:
	Dragon_Green();
	~Dragon_Green();
	virtual HRESULT Init();
	virtual void Update();
	virtual void Render();
	virtual void Revision();
	virtual void Move();
	int AI();
	virtual void DyingMessage();
	virtual void LinkPlayer(Player* player) { _player = player; }
	virtual void LinkEnemyManager(EnemyManager* enemyManager) { _enemyManager = enemyManager; }
	virtual void Hit(int damage);

};

