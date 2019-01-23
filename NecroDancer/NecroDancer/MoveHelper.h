#pragma once
#include "EnumStruct.h"

#include <vector>

enum MOVEARROW
{
	MOVE_NOT,
	MOVE_UP,
	MOVE_DOWN,
	MOVE_LEFT,
	MOVE_RIGHT
};
template <typename T>
class MoveHelper
{
private:
	T* _object;
	vector<int> _vMoveArrow;

	int _check;
	int _startX;
	int _startY;

public:
	void MoveUp()
	{
		int arrow;
		arrow = ((T*)_object)->GetY();
		((T*)_object)->SetY(arrow - 1);
		_check = 0;
		_vMoveArrow.push_back(MOVE_UP);
	}
	void MoveDown()
	{
		int arrow;
		arrow = ((T*)_object)->GetY();
		((T*)_object)->SetY(arrow + 1);
		_check = 0;
		_vMoveArrow.push_back(MOVE_DOWN);
	}
	void MoveLeft()
	{
		int arrow;
		arrow = ((T*)_object)->GetX();
		((T*)_object)->SetX(arrow - 1);
		_check = 0;
		_vMoveArrow.push_back(MOVE_LEFT);
	}
	void MoveRight()
	{
		int arrow;
		arrow = ((T*)_object)->GetX();
		((T*)_object)->SetX(arrow + 1);
		_check = 0;
		_vMoveArrow.push_back(MOVE_RIGHT);
	}
	void Update()
	{
		int posX;
		int posY;
		
		if (_vMoveArrow.size() == 0) return;

		switch (*_vMoveArrow.begin())
		{
		case MOVE_NOT:
		
		break;
		case MOVE_UP:
			_check++;
			posX = ((T*)_object)->GetPosX();
			posY = ((T*)_object)->GetPosY();
			((T*)_object)->SetPosY(posY - TILESIZEY / 8);
			if(_check == 1)
				((T*)_object)->SetPosY(posY + 2);
			if(_check == 8)
				((T*)_object)->SetPosY(posY - 2);
		break;
		case MOVE_DOWN:
			_check++;
			posX = ((T*)_object)->GetPosX();
			posY = ((T*)_object)->GetPosY();
			((T*)_object)->SetPosY(posY + TILESIZEY / 8);

			if (_check == 1)
				((T*)_object)->SetPosY(posY - 2);
			if (_check == 8)
				((T*)_object)->SetPosY(posY + 2);
			
		break;
		case MOVE_LEFT:
			_check++;
			posX = ((T*)_object)->GetPosX();
			posY = ((T*)_object)->GetPosY();
			((T*)_object)->SetPosX(posX - TILESIZEX / 8);
			((T*)_object)->SetPosY(posY - (4 -_check));
			
		break;
		case MOVE_RIGHT:
			_check++;
			posX = ((T*)_object)->GetPosX();
			posY = ((T*)_object)->GetPosY();
			((T*)_object)->SetPosX(posX + TILESIZEX / 8);
			((T*)_object)->SetPosY(posY - (4 - _check));
			
		break;
		default:
		break;
		}

		if (_check >= 8)
		{
			_check = 0;
			((T*)_object)->Revision();
			_vMoveArrow.erase(_vMoveArrow.begin());
		}
	}
	void Init()
	{
		//_moveArrow = MOVE_NOT;
		_check  = 0;
		_startX = 0;
		_startY = 0;
	}
	void LinkObject(T* object) { _object = object; }
	MoveHelper() {};
	~MoveHelper() {};
};

