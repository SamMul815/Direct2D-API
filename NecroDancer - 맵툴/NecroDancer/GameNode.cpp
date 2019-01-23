#include "stdafx.h"
#include "GameNode.h"


GameNode::GameNode()
{
}


GameNode::~GameNode()
{
}

HRESULT GameNode::Init(void)
{
	//_hdc = GetDC(_hWnd);

	D2DMANAGER->Init();
	//KEYMANAGER->Init();
	//IMAGEMANAGER->Init();
	//SOUNDMANAGER->Init();
	TIMEMANAGER->Init();
	//// EFFECTMANAGER->Init();
	//SCENEMANAGER->Init();
	//ACTIONMANAGER->Init();

	return S_OK;
}

void GameNode::Release(void)
{

	//KEYMANAGER->ReleaseSingleton();
	//IMAGEMANAGER->ReleaseSingleton();
	//SOUNDMANAGER->ReleaseSingleton();
	TIMEMANAGER->ReleaseSingleton();
	//EFFECTMANAGER->ReleaseSingleton();
	//SCENEMANAGER->ReleaseSingleton();
	//ACTIONMANAGER->ReleaseSingleton();
	////TXTDATA->ReleaseSingleton();
	////DATABASE->ReleaseSingleton();
	//ReleaseDC(_hWnd, _hdc);
}

void GameNode::Update(void)
{

}

void GameNode::Render(void)
{

}



LRESULT GameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;


	switch (iMessage)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostMessage(hWnd, WM_DESTROY, 0, 0);
			break;
		}
		break;
	case WM_MOUSEMOVE:
		_ptMouse.x = static_cast<float>LOWORD(lParam);
		_ptMouse.y = static_cast<float>HIWORD(lParam);

		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}