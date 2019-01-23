#pragma once
#include "Enemy.h"
#include "Player.h"
#include "EnumStruct.h"
class NPC_Chest : public Enemy
{
private:

public:
	NPC_Chest();
	~NPC_Chest();

	virtual HRESULT Init();
	virtual void Update();
	virtual void Render();
	virtual void Revision();
	virtual void Move();
	virtual void DyingMessage();
};

