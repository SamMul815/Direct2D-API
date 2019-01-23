#include "stdafx.h"
#include "Dragon_Green.h"

Dragon_Green::Dragon_Green()
{
}

Dragon_Green::~Dragon_Green()
{
}
HRESULT Dragon_Green::Init()			
{
	_move = new MoveHelper<Enemy>;
	_move->LinkObject(this);

	_image = IMAGEMANAGER->FindImage("DragonGreen");

	int action[] = { 0,1 };

	_ani = new Animation;
	_ani->Init(108, 102, 54, 51);
	_ani->SetPlayFrame(action, 2, TRUE);
	_ani->SetFPS(4);
	_ani->Start();
	_currentHP = 10;
	_maxHP = 10;
	_atk = 3;
	_atkCheck = FALSE;
	_moveCheck = FALSE;
	_isRight = FALSE;
	_isCry = FALSE;
	_lookPlayer = FALSE;
	return S_OK;
}
void Dragon_Green::Update()			
{	 
	_ani->FrameUpdate(TIMEMANAGER->GetElapsedTime());
	_move->Update();
}	 
void Dragon_Green::Render()			
{	 
	if (_isRight)
		_image->FlipAniRender(_posX, _posY, _ani);
	else
		_image->AniRender(_posX, _posY, _ani);

	Enemy::UIRender();
}	 
void Dragon_Green::Revision()		
{	 
	_posX = _x * TILESIZEX - 15;
	_posY = _y * TILESIZEY - 30;
}	 
void Dragon_Green::Move()			
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
			SOUNDMANAGER->Play("Dragon_Attack");
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
			SOUNDMANAGER->Play("Dragon_Attack");
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
			SOUNDMANAGER->Play("Dragon_Attack");
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
			SOUNDMANAGER->Play("Dragon_Attack");
		}
		break;
	default:
		break;
	}
}	 
int	Dragon_Green::AI()				
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

	if (((calcX*calcX) + (calcY*calcY) < 36 || _lookPlayer ) && _moveCheck)
	{
		_lookPlayer = TRUE;
		if ((calcX < calcY && calcX != 0 || calcY == 0))
		{
			if (_x < playerX)	//왼쪽일때
			{
				moveType = MOVE_RIGHT;
				_isRight = TRUE;
			}
			else if (_x > playerX)	//오른쪽일때
			{
				moveType = MOVE_LEFT;
				_isRight = FALSE;
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
	{
		moveType = MOVE_NOT;
	}

	if ((calcX*calcX) + (calcY*calcY) > 64)
	{
		_lookPlayer = FALSE;
		_isCry = FALSE;
	}

	if (moveType != MOVE_NOT)
	{
		if (_isCry == FALSE)
		{
			_isCry = TRUE;
			SOUNDMANAGER->Play("Dragon_Cry");
		}
		CAMERA->WeakShake();
		SOUNDMANAGER->Play("Dragon_Walk");
	}

	return moveType;
}	 

void Dragon_Green::Hit(int damage)
{
	_currentHP -= damage;
	SOUNDMANAGER->Play("Dragon_Hit");
}
void Dragon_Green::DyingMessage()	
{
	_enemyManager->StageClear();
}