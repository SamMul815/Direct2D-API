// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//
#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN          // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
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

extern IWICImagingFactory*		_pWICImagingFactory;		//�Է�
extern IWICFormatConverter*		_pWICConverter;				//������
extern IWICBitmapDecoder*		_pWICDecoder;				//���ڴ�
extern IWICBitmapFrameDecode*	_pWICFrameDecoder;			//������ ���ڴ�

#define RADTODEG 57.2957795f
#define DEGTORAD 0.017453f	//1���� ���� ���� ��


//extern ID2D1Factory			 *_factory;				//���
//extern ID2D1HwndRenderTarget *_Rt;					//Ÿ�� ����
//extern IDWriteFactory		 *_wFactory;				//�ؽ�Ʈ