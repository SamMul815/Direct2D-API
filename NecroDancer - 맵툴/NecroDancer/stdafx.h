// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//
#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <iostream>
#include <tchar.h>
#include "D2DUtils.h"
#include "MacroFunction.h"

using namespace std;

#include "KeyManager.h"
#include "TimeManager.h"
#include "D2DManager.h"

#ifdef FULLSCREEN
#define WINNAME (LPTSTR)(TEXT("Tango Team"))
#define WINSTARTX 0
#define WINSTARTY 0
#define WINSIZEX GetSystemMetrics(SM_CXSCREEN)
#define WINSIZEY GetSystemMetrics(SM_CYSCREEN)
#else
#define WINNAME (LPTSTR)(TEXT("Dancer"))
#define WINSTARTX 100
#define WINSTARTY 50
#define WINSIZEX 1250
#define WINSIZEY 800

#endif

#define WINSTYLE WS_CAPTION | WS_SYSMENU

#define SAFE_DELETE(p)		 {if(p) {delete(p); (p) = NULL;}}
#define SAFE_DELETE_ARRAY(p) {if(p) { delete[](p); (p)=NULL;}}
#define SAFE_RELEASE(p)		 {if(p) {(p)->Release(); (p) = NULL;}}

#define TIMEMANAGER TimeManager::GetSingleton()
#define D2DMANAGER D2DManager::GetSingleton()
#define KEYMANAGER KeyManager::GetSingleton()

extern HINSTANCE _hInstance;
extern HWND _hWnd;
extern POINT _ptMouse;

//extern ID2D1Factory			 *_factory;				//���
//extern ID2D1HwndRenderTarget *_Rt;					//Ÿ�� ����
//extern IDWriteFactory		 *_wFactory;				//�ؽ�Ʈ