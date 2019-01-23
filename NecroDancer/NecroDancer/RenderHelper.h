#pragma once
#include "D2DImage.h"
#include "EnumStruct.h"
#include "Player.h"
#include "EnemyManager.h"
#include "D2DText.h"
class RenderHelper
{
private:

	D2DImage*	_blockImage;
	D2DImage*	_tileImage;
	D2DImage*	_tileStair;
	D2DImage*	_altarImage[ALTAR_END];
	D2DImage*	_enemyImage[ENEMY_END];
	D2DImage*	_ItemImage[ITEM_STATE_END];

	D2DImage*	_trapMoveImage;
	D2DImage*	_trapBombImage;
	D2DImage*	_trapNeedleImage;
	D2DImage*	_trapTeleportImage;

	InGameTileData* _tile;
	Player*			_player;
	EnemyManager*	_enemyManager;
	D2DText*		_text;
public:
	HRESULT Init();
	void LinkeTileData(InGameTileData* tiledata) { _tile = tiledata; }
	void LinkePlayer(Player* player) { _player = player; }
	void LinkEnemyManager(EnemyManager* enemyManager) { _enemyManager = enemyManager; }

	void Render();

	RenderHelper();
	~RenderHelper();

};

