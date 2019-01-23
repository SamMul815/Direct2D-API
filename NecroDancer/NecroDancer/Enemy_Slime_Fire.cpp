#include "stdafx.h"
#include "Enemy_Slime_Fire.h"


Enemy_Slime_Fire::Enemy_Slime_Fire()
{
}


Enemy_Slime_Fire::~Enemy_Slime_Fire()
{
}

HRESULT Enemy_Slime_Fire::Init()
{

	_move = new MoveHelper<Enemy>;
	_move->LinkObject(this);

	_vPattern.push_back(MOVE_UP);
	_vPattern.push_back(MOVE_DOWN);
	_vPattern.push_back(MOVE_LEFT);
	_vPattern.push_back(MOVE_RIGHT);
	_vPattern.push_back(MOVE_DOWN);
	_vPattern.push_back(MOVE_UP);
	_vPattern.push_back(MOVE_RIGHT);
	_vPattern.push_back(MOVE_LEFT);

	_image = IMAGEMANAGER->FindImage("SlimeFire");

	int aniFrame[4] = { 0,1,2,3 };

	_ani = new Animation;
	_ani->Init(104, 52, 26, 26);
	_ani->SetPlayFrame(aniFrame, 4, TRUE);
	//_ani->SetDefPlayFrame(FALSE, TRUE);
	_ani->SetFPS(8);
	_ani->Start();
	//104, 52, 4, 2

	_currentHP = 3;
	_maxHP = 3;
	_atk = 2;
	_atkCheck = FALSE;
	return S_OK;
}

void Enemy_Slime_Fire::Update()
{
	_ani->FrameUpdate(TIMEMANAGER->GetElapsedTime());
	_move->Update();
}

void Enemy_Slime_Fire::Render()
{
	_image->AniRender(_posX, _posY, _ani);
	Enemy::UIRender();
}

void Enemy_Slime_Fire::Revision()
{
	_posX = _x * TILESIZEX;
	_posY = _y * TILESIZEY - 6;
}

void Enemy_Slime_Fire::Move()
{
	bool moveCheck;
	switch (*_vPattern.begin())
	{
	case MOVE_NOT:
		break;
	case MOVE_UP:
		if (_tile[(_y - 1) * MAPTILEX + _x].objectType == OBJECT_NONE &&		//아무런 오브젝트도 없는상황
			_tile[(_y - 1) * MAPTILEX + _x].isEnemyUP == FALSE &&
			_tile[(_y - 1) * MAPTILEX + _x].isPlayerUP == FALSE)
		{
			_tile[_y * MAPTILEX + _x].isEnemyUP = FALSE;
			_move->MoveUp();
			_tile[_y * MAPTILEX + _x].isEnemyUP = TRUE;
		}
		else if (_tile[(_y - 1) * MAPTILEX + _x].objectType == OBJECT_TRAP)		//함정 있어여~
		{
			_move->MoveUp();
			TrapCheck();
		}
		else if (_tile[(_y - 1) * MAPTILEX + _x].isPlayerUP == TRUE)		//함정 있어여~
		{
			_atkCheck = TRUE;
		}
		//_move->MoveUp();
		break;
	case MOVE_DOWN:
		if (_tile[(_y + 1) * MAPTILEX + _x].objectType == OBJECT_NONE &&		//아무런 오브젝트도 없는상황
			_tile[(_y + 1) * MAPTILEX + _x].isEnemyUP == FALSE &&
			_tile[(_y + 1) * MAPTILEX + _x].isPlayerUP == FALSE)
		{
			_tile[_y * MAPTILEX + _x].isEnemyUP = FALSE;
			_move->MoveDown();
			_tile[_y * MAPTILEX + _x].isEnemyUP = TRUE;
		}
		else if (_tile[(_y + 1) * MAPTILEX + _x].objectType == OBJECT_TRAP)		//함정 있어여~
		{
			_move->MoveDown();
			TrapCheck();
		}
		else if (_tile[(_y + 1) * MAPTILEX + _x].isPlayerUP == TRUE)		//함정 있어여~
		{
			_atkCheck = TRUE;
		}
		break;
	case MOVE_LEFT:
		if (_tile[(_y)* MAPTILEX + _x - 1].objectType == OBJECT_NONE &&		//아무런 오브젝트도 없는상황
			_tile[(_y)* MAPTILEX + _x - 1].isEnemyUP == FALSE &&
			_tile[(_y)* MAPTILEX + _x - 1].isPlayerUP == FALSE)
		{
			_tile[_y * MAPTILEX + _x].isEnemyUP = FALSE;
			_move->MoveLeft();
			_tile[_y * MAPTILEX + _x].isEnemyUP = TRUE;
		}
		else if (_tile[(_y)* MAPTILEX + _x - 1].objectType == OBJECT_TRAP)		//함정 있어여~
		{
			_move->MoveLeft();
			TrapCheck();
		}
		else if (_tile[_y * MAPTILEX + _x-1].isPlayerUP == TRUE)		//함정 있어여~
		{
			_atkCheck = TRUE;
		}
		break;
	case MOVE_RIGHT:
		if (_tile[(_y)* MAPTILEX + _x + 1].objectType == OBJECT_NONE &&		//아무런 오브젝트도 없는상황
			_tile[(_y)* MAPTILEX + _x + 1].isEnemyUP == FALSE &&
			_tile[(_y)* MAPTILEX + _x + 1].isPlayerUP == FALSE)
		{
			_tile[_y * MAPTILEX + _x].isEnemyUP = FALSE;
			_move->MoveRight();
			_tile[_y * MAPTILEX + _x].isEnemyUP = TRUE;
		}
		else if (_tile[(_y)* MAPTILEX + _x + 1].objectType == OBJECT_TRAP)		//함정 있어여~
		{
			_move->MoveRight();
			TrapCheck();
		}
		else if (_tile[_y * MAPTILEX + _x + 1].isPlayerUP == TRUE)		//함정 있어여~
		{
			_atkCheck = TRUE;
		}
		break;
	default:
		break;
	}

	_vPattern.push_back(*_vPattern.begin());
	_vPattern.erase(_vPattern.begin());

}