//헤더파일 등록
#include "stdafx.h"
#include "Club.h"
#include "D2DUtils.h"

//전역변수
HINSTANCE _hInstance;
HWND	  _hWnd;

LPTSTR _lpszClass = TEXT("Dancer");
POINT  _ptMouse;
Club   _club;

IWICImagingFactory*		_pWICImagingFactory;		//입력
IWICFormatConverter*	_pWICConverter;				//컨버터
IWICBitmapDecoder*		_pWICDecoder;				//디코더
IWICBitmapFrameDecode*	_pWICFrameDecoder;			//프레임 디코더



//함수 프로토타입(원형)
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void setWindowsSize(int x, int y, int width, int height);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int cmdShow)
{
	MSG message;
	WNDCLASS wndClass;

	_hInstance = hInstance;

	wndClass.cbClsExtra = 0;										//클래스 여분 메모리
	wndClass.cbWndExtra = 0;										//윈도우 여분 메모리
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	//윈도우 백그라운드 색상
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);					//윈도우 커서
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);				//윈도우 아이콘
	wndClass.hInstance = hInstance;									//윈도우 인스턴스
	wndClass.lpfnWndProc = (WNDPROC)WndProc;						//프로시져
	wndClass.lpszClassName = WINNAME;								//클래스 이름
	wndClass.lpszMenuName = NULL;									//메뉴 이름	
	wndClass.style = CS_HREDRAW | CS_VREDRAW;						//윈도우 스따일~

																	//윈도우 셋팅 등록
	RegisterClass(&wndClass);

	//윈도우 창 생성
	_hWnd = CreateWindow(
		WINNAME,			//윈도우 클래스 이름
		WINNAME,			//윈도우 타이틀 바에 나타낼 문자열
		WS_OVERLAPPEDWINDOW,//윈도우 스따일
		WINSTARTX,			//윈도우 창 시작 X좌표
		WINSTARTY,			//윈도우 창 시작 Y좌표
		WINSIZEX,			//윈도우 창 가로크기
		WINSIZEY,			//윈도우 창 세로크기
		NULL,				//부모 윈도우 유무
		(HMENU)NULL,		//메뉴 핸들
		hInstance,			//인스턴스 윈도우 지정
		NULL);

	//if (FAILED(D2DInit(_hWnd, WINSIZEX, WINSIZEY, &_factory, &_Rt)))				//D2D 초기화
	//{
	//	MessageBox(_hWnd, TEXT("D2D 초기화 실패"), TEXT("에러"), MB_ICONERROR);		//초기화 실패시 메세지박스
	//	return 0;
	//}

	//if (FAILED(WICInit(&_imagingFactory)))		//이미지 불러올때 사용팔 팩토리 생성
	//{
	//	MessageBox(0, TEXT("WIC 실패"),0,0);
	//	return 0;
	//	
	//}

	//if (FAILED(DWInit(&_wFactory)))		//이미지 불러올때 사용팔 팩토리 생성
	//{
	//	MessageBox(0, TEXT("DWI 실패"), 0, 0);
	//	return 0;

	//}

	setWindowsSize(WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY);

	//윈도우 창을 눈으로 보게끔 나타내준다
	ShowWindow(_hWnd, cmdShow);
	if (FAILED(_club.Init()))
	{
		//헬존 실패시 널값넣고 종료

		return 0;
	}

	//게임용 당분간 봉인
	while (true)
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			if (message.message == WM_QUIT) break;
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else
		{
			TIMEMANAGER->Update(60.0f);
			_club.Update();
			_club.Render();
		}
	}


	//while (GetMessage(&message, 0, 0, 0))
	//{
	//	TranslateMessage(&message);	//키보드 입력 메시지 처리 담당
	//	DispatchMessage(&message);	//실제로 윈도우로 메시지 전달
	//}

	//메시지 다 돌았으면
	_club.Release();

	UnregisterClass(WINNAME, hInstance);

	return message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	return _club.MainProc(hWnd, iMessage, wParam, lParam);
}

//===============================================
// - 2015. 11. 17 ## 클라이언트 영역 재조정 ##
//===============================================


void setWindowsSize(int x, int y, int width, int height)
{
	RECT winRect;

	winRect.left = 0;
	winRect.top = 0;
	winRect.right = width;
	winRect.bottom = height;

	//비작업 영역을 제외한 작업 영역안의 크기만 맞춰줌
	AdjustWindowRect(&winRect, WINSTYLE, false);

	SetWindowPos(_hWnd, NULL, x, y, (winRect.right - winRect.left),
		(winRect.bottom - winRect.top), SWP_NOZORDER | SWP_NOMOVE);


}