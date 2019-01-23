#include "stdafx.h"
#include "Enemy_Skeleton_Base.h"


Enemy_Skeleton_Base::Enemy_Skeleton_Base()
{
}

Enemy_Skeleton_Base::~Enemy_Skeleton_Base()
{
}
HRESULT Enemy_Skeleton_Base::Init()
{
	_move = new MoveHelper<Enemy>;
	_move->LinkObject(this);

	_image = IMAGEMANAGER->FindImage("SkeletonBase");

	int action[] = { 0,1,2,3 };

	_ani = new Animation;
	_ani->Init(192, 50, 24, 25);
	_ani->SetPlayFrame(action, 4, TRUE);
	_ani->SetFPS(8);
	_ani->Start();
	_currentHP = 1;
	_maxHP = 1;
	_atk = 1;

	_atkCheck = FALSE;
	_moveCheck = TRUE;

	return S_OK;
}
void Enemy_Skeleton_Base::Update()
{
	_ani->FrameUpdate(TIMEMANAGER->GetElapsedTime());
	_move->Update();
}

void Enemy_Skeleton_Base::Move()
{
	switch (AI())
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
			_tile[_y * MAPTILEX + _x].isEnemyUP = FALSE;
			_move->MoveUp();
			TrapCheck();
			_tile[_y * MAPTILEX + _x].isEnemyUP = TRUE;
		}
		else if (_tile[(_y - 1) * MAPTILEX + _x].isPlayerUP == TRUE)		//함정 있어여~
		{
			_atkCheck = TRUE;
			SOUNDMANAGER->Play("SlimeAttack");
		}
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
			_tile[_y * MAPTILEX + _x].isEnemyUP = FALSE;
			_move->MoveDown();
			TrapCheck();
			_tile[_y * MAPTILEX + _x].isEnemyUP = TRUE;
		}
		else if (_tile[(_y + 1) * MAPTILEX + _x].isPlayerUP == TRUE)		//함정 있어여~
		{
			_atkCheck = TRUE;
			SOUNDMANAGER->Play("SlimeAttack");
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
			_tile[_y * MAPTILEX + _x].isEnemyUP = FALSE;
			_move->MoveLeft();
			TrapCheck();
			_tile[_y * MAPTILEX + _x].isEnemyUP = TRUE;
		}
		else if (_tile[(_y)* MAPTILEX + _x - 1].isPlayerUP == TRUE)		//함정 있어여~
		{
			_atkCheck = TRUE;
			SOUNDMANAGER->Play("SlimeAttack");
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
			_tile[_y * MAPTILEX + _x].isEnemyUP = FALSE;
			_move->MoveRight();
			TrapCheck();
			_tile[_y * MAPTILEX + _x].isEnemyUP = TRUE;
		}
		else if (_tile[(_y)* MAPTILEX + _x + 1].isPlayerUP == TRUE)		//함정 있어여~
		{
			_atkCheck = TRUE;
			SOUNDMANAGER->Play("SlimeAttack");
		}
		break;
	default:
		break;
	}
}

void Enemy_Skeleton_Base::Revision()
{
	_posX = _x * TILESIZEX;
	_posY = _y * TILESIZEY - 6;
}

void Enemy_Skeleton_Base::Render()
{
	_image->AniRender(_posX, _posY, _ani);
	//_image->FrameRender(_posX, _posY, 0, 0);
	Enemy::UIRender();
}

int Enemy_Skeleton_Base::AI()
{
	int moveType = MOVE_NOT;
	int playerX = _player->GetX();
	int playerY = _player->GetY(); 

	int calcX = abs(_x - playerX);
	int calcY = abs(_y - playerY);
	
	if (_moveCheck == TRUE)
		_moveCheck = FALSE;
	else
		_moveCheck = TRUE;

	if ((calcX*calcX) + (calcY*calcY) < 25 && _moveCheck)
	{
		if ((calcX < calcY && calcX != 0 || calcY == 0))
		{
			if (_x < playerX)	//왼쪽일때
			{
				moveType = MOVE_RIGHT;
			}
			else if (_x > playerX)	//오른쪽일때
			{
				moveType = MOVE_LEFT;
			}
		}
		else
		{
			if (_y < playerY)	//위쪽일때
			{
				moveType = MOVE_DOWN;
			}
			else if (_y > playerY)	//오른쪽일때
			{
				moveType = MOVE_UP;
			}
		}
	}
	else
		moveType = MOVE_NOT;


	if (moveType == MOVE_NOT)
	{
		int action[] = { 0,1,2,3 };
		_ani->SetPlayFrame(action, 4, TRUE);
	}
	else
	{
		int action[] = { 4,5,6,7 };
		_ani->SetPlayFrame(action, 4, TRUE);
	}

	return moveType;
}