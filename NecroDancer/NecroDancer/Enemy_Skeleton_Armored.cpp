#include "stdafx.h"
#include "Enemy_Skeleton_Armored.h"


Enemy_Skeleton_Armored::Enemy_Skeleton_Armored()
{
}


Enemy_Skeleton_Armored::~Enemy_Skeleton_Armored()
{
}

HRESULT Enemy_Skeleton_Armored::Init()
{
	_move = new	MoveHelper<Enemy>;
	_move->LinkObject(this);

	_image = IMAGEMANAGER->FindImage("SkeletonArmored");

	int action[] = { 0,1 };

	_ani = new Animation;
	_ani->Init(144, 48, 24, 24);
	_ani->SetPlayFrame(action, 2, TRUE);
	_ani->SetFPS(4);
	_ani->Start();
	_currentHP = 1;
	_maxHP = 1;
	_atk = 1;
	_atkCheck = FALSE;
	_moveCheck = FALSE;
	_isRight = FALSE;
	return S_OK;
}
void Enemy_Skeleton_Armored::Update()						
{
	_ani->FrameUpdate(TIMEMANAGER->GetElapsedTime());
	_move->Update();
}
void Enemy_Skeleton_Armored::Render()						
{
	if(_isRight)
		_image->FlipAniRender(_posX, _posY, _ani);
	else
		_image->AniRender(_posX, _posY, _ani);

	Enemy::UIRender();
}
void Enemy_Skeleton_Armored::Revision()						
{
	_posX = _x * TILESIZEX;
	_posY = _y * TILESIZEY - 6;
}
void Enemy_Skeleton_Armored::Move()							
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
int Enemy_Skeleton_Armored::AI()	
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
				int action[] = { 2,3 };
				_ani->SetPlayFrame(action, 2, TRUE);
				moveType = MOVE_RIGHT;
				_isRight = TRUE;
			}
			else if (_x > playerX)	//오른쪽일때
			{
				int action[] = { 2,3 };
				_ani->SetPlayFrame(action, 2, TRUE);
				moveType = MOVE_LEFT;
				_isRight = FALSE;
			}
		}
		else
		{
			if (_y < playerY)	//위쪽일때
			{
				int action[] = { 4,5 };
				_ani->SetPlayFrame(action, 2, TRUE);
				moveType = MOVE_DOWN;
				_isRight = FALSE;
			}
			else if (_y > playerY)	//오른쪽일때
			{
				int action[] = { 0,1 };
				_ani->SetPlayFrame(action, 2, TRUE);
				moveType = MOVE_UP;
				_isRight = FALSE;
			}
		}
	}
	else
		moveType = MOVE_NOT;


	return moveType;
}

void Enemy_Skeleton_Armored::DyingMessage()
{
	_enemyManager->MakeSkeletonBase(_x, _y);
	_tile[_y * MAPTILEX + _x].isEnemyUP = TRUE;
}