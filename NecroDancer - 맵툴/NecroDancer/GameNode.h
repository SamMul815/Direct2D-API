#pragma once
#include "ApiImage.h"
#include "D2DUtils.h"
class GameNode
{
private:
	//HDC _hdc;
	
public:

	virtual HRESULT Init(void);		//초기화 함수
	virtual void Release(void);		//메모리 해제 함수
	virtual void Update(void);		//연산 함수
	virtual void Render(void);	//그리기 함수


	//ApiImage* GetBackBuffer(void) { return backBuffer; }

	//HDC GetMemDC() { return backBuffer->GetMemDC(); }
	//HDC GetHDC() { return _hdc; }

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);


	GameNode();
	virtual ~GameNode();
};

