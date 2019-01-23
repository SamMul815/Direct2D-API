// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//
#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN          // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <iostream>
#include <tchar.h>
#include "D2DUtils.h"
#include "MacroFunction.h"

using namespace std;

#include "ImageManager.h"
#include "KeyManager.h"
#include "TimeManager.h"
#include "SoundManager.h"
#include "D2DManager.h"
#include "SceneManager.h"
#include "RandomFunction.h"
#include "TxtData.h"
#include "Camera.h"


#ifdef FULLSCREEN
#define WINNAME (LPTSTR)(TEXT("Tango Team"))
#define WINSTARTX 0
#define WINSTARTY 0
#define WINSIZEX GetSystemMetrics(SM_CXSCREEN)
#define WINSIZEY GetSystemMetrics(SM_CYSCREEN)
#else
#define WINNAME (LPTSTR)(TEXT("Dancer"))
#define WINSTARTX 100
#define WINSTARTY 100
#define WINSIZEX 1200
#define WINSIZEY 800

#endif

#define WINSTYLE WS_CAPTION | WS_SYSMENU

#define SAFE_DELETE(p)		 {if(p) {delete(p); (p) = NULL;}}
#define SAFE_DELETE_ARRAY(p) {if(p) { delete[](p); (p)=NULL;}}
#define SAFE_RELEASE(p)		 {if(p) {(p)->Release(); (p) = NULL;}}

#define TIMEMANAGER  TimeManager::GetSingleton()
#define D2DMANAGER	 D2DManager::GetSingleton()
#define KEYMANAGER	 KeyManager::GetSingleton()
#define SCENEMANAGER SceneManager::GetSingleton()
#define IMAGEMANAGER ImageManager::GetSingleton()
#define SOUNDMANAGER SoundManager::GetSingleton()
#define RND			 RandomFunction::GetSingleton() 
#define TXTDATA		 TxtData::GetSingleton()
#define CAMERA		 Camera::GetSingleton()

extern HINSTANCE _hInstance;
extern HWND _hWnd;
extern POINT _ptMouse;

extern IWICImagingFactory*		_pWICImagingFactory;		//입력
extern IWICFormatConverter*		_pWICConverter;				//컨버터
extern IWICBitmapDecoder*		_pWICDecoder;				//디코더
extern IWICBitmapFrameDecode*	_pWICFrameDecoder;			//프레임 디코더

#define RADTODEG 57.2957795f
#define DEGTORAD 0.017453f	//1도에 대한 라디안 값


//extern ID2D1Factory			 *_factory;				//출력
//extern ID2D1HwndRenderTarget *_Rt;					//타겟 설정
//extern IDWriteFactory		 *_wFactory;				//텍스트