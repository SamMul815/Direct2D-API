#include "stdafx.h"
#include "Enemy.h"


Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}

HRESULT Enemy::Init()
{
	return S_OK;
}

void Enemy::Update()
{

}

void Enemy::Render()
{

}
void Enemy::Revision()
{

}
void Enemy::Move()
{

}

void Enemy::TrapCheck()
{
		switch (_tile[(_y)* MAPTILEX + _x].objectKind)
		{
		case TRAP_MOVEUP:
			_tile[_y * MAPTILEX + _x].isEnemyUP = FALSE;
			_move->MoveUp();
			_tile[_y * MAPTILEX + _x].isEnemyUP = TRUE;
			break;
		case TRAP_MOVERIGHT:
			_tile[_y * MAPTILEX + _x].isEnemyUP = FALSE;
			_move->MoveRight();
			_tile[_y * MAPTILEX + _x].isEnemyUP = TRUE;
			break;
		case TRAP_MOVEDOWN:
			_tile[_y * MAPTILEX + _x].isEnemyUP = FALSE;
			_move->MoveDown();
			_tile[_y * MAPTILEX + _x].isEnemyUP = TRUE;
			break;
		case TRAP_MOVELEFT:
			_tile[_y * MAPTILEX + _x].isEnemyUP = FALSE;
			_move->MoveLeft();
			_tile[_y * MAPTILEX + _x].isEnemyUP = TRUE;
			break;
		case TRAP_BOOM:
			break;
		case TRAP_TELEPORT:
			break;
		case TRAP_NEEDLE:
			break;
		default:
			break;
		}
}
void Enemy::UIRender()
{

	if (_currentHP != _maxHP)
	{
		for (int i = 0; i < _maxHP; i++)
		{
			if (_maxHP > 5)
			{
				if (i < _currentHP)
					IMAGEMANAGER->FindImage("Enemy_Heart")->Render((_posX + i * 12) - ((_maxHP / 2) * 6), _posY - 5);
				else
					IMAGEMANAGER->FindImage("Enemy_Heart_Empty")->Render((_posX + i * 12) - ((_maxHP / 2) * 6), _posY - 5);
			}
			else
			{
				if (i < _currentHP)
					IMAGEMANAGER->FindImage("Enemy_Heart")->Render(_posX + i * 12, _posY - 5);
				else
					IMAGEMANAGER->FindImage("Enemy_Heart_Empty")->Render(_posX + i * 12, _posY - 5);
			}
		}
	}
}

void Enemy::Release()
{

	SAFE_DELETE(_move);
}