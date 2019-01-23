#pragma once
#include "GameNode.h"
#include "Player.h"
#include "Stage2Beat.h"
#include "EnumStruct.h"
#include "RenderHelper.h"
#include "EnemyManager.h"

class Stage2 : public GameNode
{
private:
	HeartBeat* _beat;
	EnemyManager* _enemyManager;
	Player*	   _player;
	RenderHelper*  _renderHelper;
	InGameTileData _tile[MAPTILEX][MAPTILEY];
public:
	Stage2();
	~Stage2();

	virtual HRESULT Init(void);
	virtual void Release(void);
	virtual void Update(void);
	virtual void Render(void);

	void LinkPlayer(Player* player) { _player = player; }
	void LoadMapData();
};

