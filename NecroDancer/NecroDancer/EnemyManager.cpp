#include "stdafx.h"
#include "Player.h"
#include "EnemyManager.h"


EnemyManager::EnemyManager()
{

}


EnemyManager::~EnemyManager()
{

}


HRESULT EnemyManager::Init()
{
	for (int i = 0; i < MAPTILEX * MAPTILEY; i++)
	{
		_enemyPosition[i] = NULL;
	}

	_stageClear = FALSE;
	_beatCheck = FALSE;

	return S_OK;
}

void EnemyManager::Update()
{
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); _viEnemy++)
	{
		(*_viEnemy)->Update();
	}
}
void EnemyManager::Move()
{
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); _viEnemy++)
	{
		_enemyPosition[(*_viEnemy)->GetY() * MAPTILEX + (*_viEnemy)->GetX()] = NULL;
		(*_viEnemy)->Move();
		_enemyPosition[ (*_viEnemy)->GetY() * MAPTILEX + (*_viEnemy)->GetX()] = *_viEnemy;

		if ((*_viEnemy)->GetAttackCheck())		//적이 공격했다는 표시
		{
			_player->Hit((*_viEnemy)->GetAtk());	//적의 공격력에 따른 플레이어 힛트
			(*_viEnemy)->StopAttack();
		}
	}

	if (_beatCheck == TRUE)
		_beatCheck = FALSE;
	else
		_beatCheck = TRUE;

}
void EnemyManager::Render(int x, int y)
{
	if (_enemyPosition[y*MAPTILEX + x] != NULL)
	{
		_enemyPosition[y*MAPTILEX + x]->Render();
	}

}
void EnemyManager::AttackEnemy(int x, int y,int damage)
{
	_enemyPosition[y * MAPTILEX + x]->Hit(damage);
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end();)
	{
		if ((*_viEnemy)->GetHP() <= 0)
		{
			_tile[(*_viEnemy)->GetY() * MAPTILEX + (*_viEnemy)->GetX()].isEnemyUP = FALSE;
			_enemyPosition[(*_viEnemy)->GetY() * MAPTILEX + (*_viEnemy)->GetX()] = NULL;
			(*_viEnemy)->DyingMessage();
			_viEnemy = _vEnemy.erase(_viEnemy);
			_player->Kill();
		}
		else
			_viEnemy++;
	}
}
void EnemyManager::MakeSlimeGreen(int x, int y)
{
	Enemy* enemy;
	enemy = new Enemy_Slime_Green;
	enemy->Init();
	enemy->SetX(x);
	enemy->SetY(y);
	enemy->Revision();
	enemy->LinkTile(_tile);
	_vEnemy.push_back(enemy);

	_enemyPosition[x * MAPTILEX + y] = enemy;

}
void EnemyManager::MakeSlimeIce(int x, int y)
{
	Enemy* enemy;
	enemy = new Enemy_Slime_Ice;
	enemy->Init();
	enemy->SetX(x);
	enemy->SetY(y);
	enemy->Revision();
	enemy->LinkTile(_tile);
	_vEnemy.push_back(enemy);
	_enemyPosition[x * MAPTILEX + y] = enemy;
}
void EnemyManager::MakeSlimeFire(int x, int y)
{
	Enemy* enemy;
	enemy = new Enemy_Slime_Fire;
	enemy->Init();
	enemy->SetX(x);
	enemy->SetY(y);
	enemy->Revision();
	enemy->LinkTile(_tile);
	_vEnemy.push_back(enemy);
	_enemyPosition[x * MAPTILEX + y] = enemy;
}
void EnemyManager::MakeSkeletonBase(int x, int y)
{
	Enemy* enemy;
	enemy = new Enemy_Skeleton_Base;
	enemy->Init();
	enemy->SetX(x);
	enemy->SetY(y);
	enemy->Revision();
	enemy->LinkTile(_tile);
	enemy->LinkPlayer(_player);
	_vEnemy.push_back(enemy);
	_enemyPosition[x * MAPTILEX + y] = enemy;
}
void EnemyManager::MakeSkeletonArmored(int x, int y)
{
	Enemy* enemy;
	enemy = new Enemy_Skeleton_Armored;
	enemy->Init();
	enemy->SetX(x);
	enemy->SetY(y);
	enemy->Revision();
	enemy->LinkTile(_tile);
	enemy->LinkPlayer(_player);
	enemy->LinkEnemyManager(this);
	_vEnemy.push_back(enemy);
	_enemyPosition[x * MAPTILEX + y] = enemy;
}
void EnemyManager::MakeGreenDragon(int x, int y)
{
	Enemy* enemy;
	enemy = new Dragon_Green;
	enemy->Init();
	enemy->SetX(x);
	enemy->SetY(y);
	enemy->Revision();
	enemy->LinkTile(_tile);
	enemy->LinkPlayer(_player);
	enemy->LinkEnemyManager(this);
	_vEnemy.push_back(enemy);
	_enemyPosition[x * MAPTILEX + y] = enemy;
}
void EnemyManager::MakeShopKeeper(int x, int y, int Stage)
{
	Enemy* enemy;
	enemy = new NPC_ShopKeeper;
	enemy->Init(Stage);
	enemy->SetX(x);
	enemy->SetY(y);
	enemy->Revision();
	enemy->LinkTile(_tile);
	enemy->LinkPlayer(_player);
	_vEnemy.push_back(enemy);
	_enemyPosition[x * MAPTILEX + y] = enemy;
}
void EnemyManager::MakeChest(int x, int y)
{
	Enemy* enemy;
	enemy = new NPC_Chest;
	enemy->Init();
	enemy->SetX(x);
	enemy->SetY(y);
	enemy->Revision();
	enemy->LinkTile(_tile);
	enemy->LinkPlayer(_player);
	_vEnemy.push_back(enemy);
	_enemyPosition[x * MAPTILEX + y] = enemy;
}