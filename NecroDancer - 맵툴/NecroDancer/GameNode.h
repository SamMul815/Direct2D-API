#pragma once
#include "ApiImage.h"
#include "D2DUtils.h"
class GameNode
{
private:
	//HDC _hdc;
	
public:

	virtual HRESULT Init(void);		//�ʱ�ȭ �Լ�
	virtual void Release(void);		//�޸� ���� �Լ�
	virtual void Update(void);		//���� �Լ�
	virtual void Render(void);	//�׸��� �Լ�


	//ApiImage* GetBackBuffer(void) { return backBuffer; }

	//HDC GetMemDC() { return backBuffer->GetMemDC(); }
	//HDC GetHDC() { return _hdc; }

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);


	GameNode();
	virtual ~GameNode();
};

