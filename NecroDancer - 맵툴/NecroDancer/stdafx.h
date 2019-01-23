// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//
#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
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

//extern ID2D1Factory			 *_factory;				//출력
//extern ID2D1HwndRenderTarget *_Rt;					//타겟 설정
//extern IDWriteFactory		 *_wFactory;				//텍스트