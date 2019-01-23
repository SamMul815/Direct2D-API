#include "stdafx.h"
#include "Camera.h"


Camera::Camera()
{
}


Camera::~Camera()
{
}

HRESULT Camera::Init()
{
	_x = 0;
	_y = 0;
	_StrongShake = FALSE;
	_StrongTime = 0;

	_WeakShake = FALSE;
	_WeakTime = 0;

	return S_OK;
}

void Camera::Update()
{
	if (_StrongShake)
	{
		int shakeX = RND->GetInt(8) - 4;
		int shakeY = RND->GetInt(8) - 4;

		_x += shakeX;
		_y += shakeY;
		_StrongTime++;

		if (_StrongTime > 10)
		{
			_StrongShake = FALSE;
			_StrongTime = 0;
		}
	}
	if (_WeakShake)
	{
		int shakeX = RND->GetInt(4) - 2;
		int shakeY = RND->GetInt(4) - 2;

		_x += shakeX;
		_y += shakeY;
		_WeakTime++;

		if (_WeakTime > 10)
		{
			_WeakShake = FALSE;
			_WeakTime = 0;
		}
	}

	_cameraRC = RectMake(_x, _y, WINSIZEX, WINSIZEY);
}
void Camera::SetCenterXY(int x, int y)
{
	_x = x -( WINSIZEX / 2);
	_y = y -( WINSIZEY / 2);
}
void Camera::SetXY(int x, int y)
{
	_x = x;
	_y = y;
}