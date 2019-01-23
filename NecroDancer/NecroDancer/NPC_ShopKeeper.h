#pragma once
#include "Enemy.h"
#include "Player.h"

class NPC_ShopKeeper : public Enemy
{
private:
	Player* _player;
	int _stage;
	int _distance;
	float _songPower;

public:

	virtual HRESULT Init(int stage);
	virtual void Update();
	virtual void Render();
	virtual void Revision();
	virtual void Move();
	virtual void LinkPlayer(Player* player) { _player = player; }
	virtual void DyingMessage();
	NPC_ShopKeeper();
	~NPC_ShopKeeper();
};

