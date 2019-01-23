#include "stdafx.h"
#include "timeManager.h"
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console" )

TimeManager::TimeManager()
	: _timer(NULL)
{
}


TimeManager::~TimeManager()
{
}

HRESULT TimeManager::Init(void)
{
	_timer = new Timer;
	_timer->Init();

	_text = new D2DText;
	_text->Init(L"돋움", 15, D2D1::ColorF(0, 0, 0));
	return S_OK;
}

void TimeManager::Release(void)
{
	if (_timer != NULL)
	{
		SAFE_DELETE(_timer);
		_timer = NULL;
	}
}

void TimeManager::Update(float lock)
{
	if (_timer != NULL)
	{
		_timer->Tick(lock);
	}
}

void TimeManager::Render()
{
	WCHAR str[256];
	
	//HDC hdc = GetDC(_Rt->GetHwnd());
	string strFrame;
	//SetTextColor(hdc, RGB(255, 255, 255));
	//SetBkMode(hdc, TRANSPARENT);

#ifdef _DEBUG
	if (_timer != NULL)
	{
		//FPS
		wsprintfW(str, L"framePerSec(FPS) : %d", _timer->GetFrameRate());
		_text->Render(10,10, 300, 300, str);
		//TextOut(hdc, 0, 0, str, strlen(str));
		//_timer->GetFrameRate(str);
		//cout << "FPS: " << str << endl;
		//월드타임
		//sprintf_s(str, "worldTime : %f", _timer->GetWorldTime());
		//TextOut(hdc, 0, 20, str, strlen(str));

		////갱신 Tick
		//sprintf_s(str, "elapsedTime : %f", _timer->GetElapsedTime());
		//TextOut(hdc, 0, 40, str, strlen(str));
	}
#else
	{
		//FPS
		wsprintf(str, "framePerSec(FPS) : %d", _timer->getFrameRate());
		TextOut(hdc, 0, 0, str, strlen(str));
	}
#endif
}