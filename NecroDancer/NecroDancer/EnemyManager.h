#pragma once
#include "Enemy.h"
#include "Enemy_Slime_Green.h"
#include "Enemy_Slime_Ice.h"
#include "Enemy_Slime_Fire.h"
#include "Enemy_Skeleton_Base.h"
#include "Enemy_Skeleton_Armored.h"
#include "Dragon_Green.h"
#include "NPC_ShopKeeper.h"
#include "NPC_Chest.h"
#include "GameNode.h"
#include <vector>

class Player;

class EnemyManager
{
private:
	vector<Enemy*> _vEnemy;
	vector<Enemy*>::iterator _viEnemy;
	Enemy* _enemyPosition[MAPTILEX * MAPTILEY];
	InGameTileData*	_tile;
	Player*	_player;
	bool _stageClear;
	bool	_beatCheck;			//비트 박자 확인
public:
	HRESULT Init();
	void Render(int x, int y);
	void Update();
	void Move();
	void LinkEnemyTileData(InGameTileData* tile) {_tile = tile;	}
	void LinkPlayer(Player* player) { _player = player; }

	void MakeSlimeGreen(int x, int y);
	void MakeSlimeIce(int x, int y);
	void MakeSlimeFire(int x, int y);
	void MakeSkeletonBase(int x, int y);
	void MakeSkeletonArmored(int x, int y);
	void MakeGreenDragon(int x, int y);
	void MakeShopKeeper(int x, int y, int Stage);
	void MakeChest(int x, int y);
	void AttackEnemy(int x, int y,int damage);

	bool GetStageClear() {return  _stageClear; }
	bool GetBeatCheck() { return _beatCheck; }

	void StageClear() { _stageClear = TRUE; }
	EnemyManager();
	~EnemyManager();

};

