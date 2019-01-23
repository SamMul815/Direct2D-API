//������� ���
#include "stdafx.h"
#include "Club.h"
#include "D2DUtils.h"

//��������
HINSTANCE _hInstance;
HWND	  _hWnd;

LPTSTR _lpszClass = TEXT("Dancer");
POINT  _ptMouse;
Club   _club;

IWICImagingFactory*		_pWICImagingFactory;		//�Է�
IWICFormatConverter*	_pWICConverter;				//������
IWICBitmapDecoder*		_pWICDecoder;				//���ڴ�
IWICBitmapFrameDecode*	_pWICFrameDecoder;			//������ ���ڴ�



//�Լ� ������Ÿ��(����)
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void setWindowsSize(int x, int y, int width, int height);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int cmdShow)
{
	MSG message;
	WNDCLASS wndClass;

	_hInstance = hInstance;

	wndClass.cbClsExtra = 0;										//Ŭ���� ���� �޸�
	wndClass.cbWndExtra = 0;										//������ ���� �޸�
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	//������ ��׶��� ����
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);					//������ Ŀ��
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);				//������ ������
	wndClass.hInstance = hInstance;									//������ �ν��Ͻ�
	wndClass.lpfnWndProc = (WNDPROC)WndProc;						//���ν���
	wndClass.lpszClassName = WINNAME;								//Ŭ���� �̸�
	wndClass.lpszMenuName = NULL;									//�޴� �̸�	
	wndClass.style = CS_HREDRAW | CS_VREDRAW;						//������ ������~

																	//������ ���� ���
	RegisterClass(&wndClass);

	//������ â ����
	_hWnd = CreateWindow(
		WINNAME,			//������ Ŭ���� �̸�
		WINNAME,			//������ Ÿ��Ʋ �ٿ� ��Ÿ�� ���ڿ�
		WS_OVERLAPPEDWINDOW,//������ ������
		WINSTARTX,			//������ â ���� X��ǥ
		WINSTARTY,			//������ â ���� Y��ǥ
		WINSIZEX,			//������ â ����ũ��
		WINSIZEY,			//������ â ����ũ��
		NULL,				//�θ� ������ ����
		(HMENU)NULL,		//�޴� �ڵ�
		hInstance,			//�ν��Ͻ� ������ ����
		NULL);

	//if (FAILED(D2DInit(_hWnd, WINSIZEX, WINSIZEY, &_factory, &_Rt)))				//D2D �ʱ�ȭ
	//{
	//	MessageBox(_hWnd, TEXT("D2D �ʱ�ȭ ����"), TEXT("����"), MB_ICONERROR);		//�ʱ�ȭ ���н� �޼����ڽ�
	//	return 0;
	//}

	//if (FAILED(WICInit(&_imagingFactory)))		//�̹��� �ҷ��ö� ����� ���丮 ����
	//{
	//	MessageBox(0, TEXT("WIC ����"),0,0);
	//	return 0;
	//	
	//}

	//if (FAILED(DWInit(&_wFactory)))		//�̹��� �ҷ��ö� ����� ���丮 ����
	//{
	//	MessageBox(0, TEXT("DWI ����"), 0, 0);
	//	return 0;

	//}

	setWindowsSize(WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY);

	//������ â�� ������ ���Բ� ��Ÿ���ش�
	ShowWindow(_hWnd, cmdShow);
	if (FAILED(_club.Init()))
	{
		//���� ���н� �ΰ��ְ� ����

		return 0;
	}

	//���ӿ� ��а� ����
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
	//	TranslateMessage(&message);	//Ű���� �Է� �޽��� ó�� ���
	//	DispatchMessage(&message);	//������ ������� �޽��� ����
	//}

	//�޽��� �� ��������
	_club.Release();

	UnregisterClass(WINNAME, hInstance);

	return message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	return _club.MainProc(hWnd, iMessage, wParam, lParam);
}

//===============================================
// - 2015. 11. 17 ## Ŭ���̾�Ʈ ���� ������ ##
//===============================================


void setWindowsSize(int x, int y, int width, int height)
{
	RECT winRect;

	winRect.left = 0;
	winRect.top = 0;
	winRect.right = width;
	winRect.bottom = height;

	//���۾� ������ ������ �۾� �������� ũ�⸸ ������
	AdjustWindowRect(&winRect, WINSTYLE, false);

	SetWindowPos(_hWnd, NULL, x, y, (winRect.right - winRect.left),
		(winRect.bottom - winRect.top), SWP_NOZORDER | SWP_NOMOVE);


}