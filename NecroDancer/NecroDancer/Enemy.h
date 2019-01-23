#pragma once
#include "EnumStruct.h"
#include "MoveHelper.h"

class Player;
class EnemyManager;
class Enemy
{
protected:
	int		_x; 	//Å¸ÀÏ ÁÂÇ¥
	int		_y;
	int		_posX;	//È­¸é ÁÂÇ¥
	int		_posY;
	int		_atk;
	int		_currentHP;
	int		_maxHP;
	D2DImage*	_image;
	InGameTileData* _tile;
	MoveHelper<Enemy>* _move;

	bool	_atkCheck;
public:

	Enemy();
	~Enemy();
	int GetX() { return _x; }
	int GetY() { return _y; }
	void SetX(int x) { _x = x; }
	void SetY(int y) { _y = y; }
	int GetPosX() { return _posX; }
	int GetPosY() { return _posY; }
	void SetPosX(int x) { _posX = x; }
	void SetPosY(int y) { _posY = y; }
	int GetHP() { return _currentHP; }
	int GetAtk() { return _atk; }
	void LinkTile(InGameTileData* tile) { _tile = tile; }
	virtual void Hit(int damage) { _currentHP -= damage; }
	
	virtual HRESULT Init();
	virtual HRESULT Init(int stage) { return S_OK; };
	virtual void Move();
	virtual void Update();
	virtual void Render();
	virtual void Revision();
	virtual void UIRender();
	virtual void LinkPlayer(Player* player) {}
	virtual void LinkEnemyManager(EnemyManager* enemyManager) {}
	virtual void DyingMessage() {};
	virtual void Release();
	void TrapCheck();

	bool GetAttackCheck() { return _atkCheck; }
	void StopAttack() { _atkCheck = FALSE; }
};

