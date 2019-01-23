#pragma once
#include "GameNode.h"
#include "HeartBeat.h"
#include "Animation.h"
#include "MoveHelper.h"
#include "EnemyManager.h"
#include "EnumStruct.h"
#include "Sight.h"


struct tagInventory
{
	int head;
	int body;
	int weapon;
	int shovel;
	int torch;
	int potion;
	int spell1;
	int spell2;
	int bomb;
};

struct tagStat
{
	int	maxHP;
	int	currentHP;
	int	atk;
	int	def;
	int shv;
};

class Player : public GameNode
{
private:
	bitset<4> _keyBit;
	int		  _keyStack;
	int		  _keycheck;

	int		_x; 	//플레이어 타일 좌표
	int		_y;
	int		_posX;	//플레이어 화면 좌표
	int		_posY;	
	int		_killStack;
	bool	_isLeft;
	bool	_attackEffect;
	bool	_digEffect;
	bool	_fireEffect;
	bool	_upStair;
	bool	_live;
	int		_stage;
	int		_fireEffectFrame;
	int		_digEffectFrame;
	int		_EffectFrameCount;
	int		_EffectArrow;
	int		_attackCheck;

	tagStat		 _playerStat;	//플레이어 스텟
	tagInventory _playerInven;  //플레이어 인벤 
	MoveHelper<Player>*	_move;
	Sight*		_sight;

	D2DImage*	_effectImage1[6];
	D2DImage*	_effectImage2[6];
	D2DImage*	_head;
	D2DImage*	_body;
	HeartBeat*	_beat;
	Animation*	_playerHeadAni;
	Animation*	_playerBodyAni;
	InGameTileData* _tile;
	EnemyManager*	_enemyManager;
public:
	int GetX() { return _x; }
	int GetY() { return _y; }
	void SetX(int x) { _x = x;}
	void SetY(int y) { _y = y;}
	int GetPosX() { return _posX; }
	int GetPosY() { return _posY; }
	void SetPosX(int x) { _posX = x; }
	void SetPosY(int y) { _posY = y; }
	void Revision();

	virtual HRESULT Init();
	virtual void Render();
	virtual void Update();
	virtual void Release();

	void UIRender();
	void PlayerEffectRender();
	void SightRender();
	int KeyCheck();
	void LinkBeat(HeartBeat* beat) { _beat = beat; }
	void LinkTile(InGameTileData* tile) { _tile = tile;}
	void LinkEnemyManager(EnemyManager* enemyManager) { _enemyManager = enemyManager; }

	void ImageInput();
	void TrapCheck();
	void ItemCheck(int x, int y);
	void BlockCheck(int tileNum);
	bool AttackCheck(int arrow);
	void Attack(int arrow);
	void Hit(int damage);
	void Kill() { _killStack++; }
	void SpellHeal();
	void SpellFire();

	Player();
	~Player();
};

