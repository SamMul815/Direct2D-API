#include "stdafx.h"
#include "ApiImage.h"
//8��Ʈ? 16��Ʈ? 24��Ʈ? 32��Ʈ?
#pragma comment (lib, "msimg32.lib")

ApiImage::ApiImage()
	: _imageInfo(NULL),
	_fileName(NULL),
	_trans(false),
	_transColor(RGB(0, 0, 0))
{
}


ApiImage::~ApiImage()
{
}

//�� ��Ʈ�� �̹��� ���� ����� ���
HRESULT ApiImage::Init(int width, int height, BOOL alpha)
{

	if (_imageInfo != NULL) Release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_EMPTY;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = 0;
	_imageInfo->y = 0;
	_imageInfo->width = width;
	_imageInfo->height = height;

	_fileName = NULL;

	//����Į�� �ʱ�ȭ
	_trans = FALSE;
	_transColor = RGB(0, 0, 0);

	if (_imageInfo->hBit == 0)
	{
		Release();

		return E_FAIL;
	}

	if (alpha)
	{
		_blendFunc.BlendFlags = 0;
		_blendFunc.AlphaFormat = 0;
		_blendFunc.BlendOp = AC_SRC_OVER;
		_blendImage = new IMAGE_INFO;
		_blendImage->loadType = LOAD_EMPTY;
		_blendImage->resID = 0;
		_blendImage->hMemDC = CreateCompatibleDC(hdc);
		_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
		_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
		_blendImage->width = width;
		_blendImage->height = height;
		_alpha = TRUE;
	}
	else
		_alpha = FALSE;

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

//���ҽ����� �о�ͼ� ����� ���
HRESULT ApiImage::Init(const DWORD resID, int width, int height,
	BOOL trans, COLORREF transColor, BOOL alpha)
{
	if (_imageInfo != NULL) Release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_RESOURCE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = 0;
	_imageInfo->y = 0;
	_imageInfo->width = width;
	_imageInfo->height = height;

	_fileName = NULL;

	//����Į�� �ʱ�ȭ
	_trans = FALSE;
	_transColor = RGB(0, 0, 0);

	if (_imageInfo->hBit == 0)
	{
		Release();

		return E_FAIL;
	}

	if (alpha)
	{
		_blendFunc.BlendFlags = 0;
		_blendFunc.AlphaFormat = 0;
		_blendFunc.BlendOp = AC_SRC_OVER;

		_blendImage = new IMAGE_INFO;
		_blendImage->loadType = LOAD_EMPTY;
		_blendImage->resID = 0;
		_blendImage->hMemDC = CreateCompatibleDC(hdc);
		_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
		_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
		_blendImage->width = WINSIZEX;
		_blendImage->height = WINSIZEY;
		_alpha = TRUE;
	}
	else
		_alpha = FALSE;

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

//���Ϸκ��� �о�ͼ� ����� ���
HRESULT ApiImage::Init(const char* fileName, int width, int height,
	BOOL trans, COLORREF transColor, BOOL alpha)
{
	if (fileName == NULL) return E_FAIL;

	if (_imageInfo != NULL) Release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = 0;
	_imageInfo->y = 0;
	_imageInfo->width = width;
	_imageInfo->height = height;

	//���ϰ�� �̸� �����ؼ� ������
	int len = strlen(fileName);

	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//����Į�� �ʱ�ȭ
	_trans = trans;
	_transColor = transColor;

	if (_imageInfo->hBit == 0)
	{
		Release();

		return E_FAIL;
	}

	if (alpha)
	{

		_blendFunc.BlendFlags = 0;
		_blendFunc.AlphaFormat = 0;
		_blendFunc.BlendOp = AC_SRC_OVER;
		_blendImage = new IMAGE_INFO;
		_blendImage->loadType = LOAD_EMPTY;
		_blendImage->resID = 0;
		_blendImage->hMemDC = CreateCompatibleDC(hdc);
		_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
		_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
		_blendImage->width = WINSIZEX;
		_blendImage->height = WINSIZEY;
		_alpha = TRUE;

	}
	else
		_alpha = false;
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT ApiImage::Init(const char* fileName, float x, float y, int width, int height,
	BOOL trans, COLORREF transColor, BOOL alpha)
{
	if (fileName == NULL) return E_FAIL;

	if (_imageInfo != NULL) Release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x - (width / 2);
	_imageInfo->y = y - (height / 2);
	_imageInfo->width = width;
	_imageInfo->height = height;

	//���ϰ�� �̸� �����ؼ� ������
	int len = strlen(fileName);

	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//����Į�� �ʱ�ȭ
	_trans = trans;
	_transColor = transColor;

	if (_imageInfo->hBit == 0)
	{
		Release();

		return E_FAIL;
	}

	if (alpha)
	{
		_blendFunc.BlendFlags = 0;
		_blendFunc.AlphaFormat = 0;
		_blendFunc.BlendOp = AC_SRC_OVER;
		_blendImage = new IMAGE_INFO;
		_blendImage->loadType = LOAD_EMPTY;
		_blendImage->resID = 0;
		_blendImage->hMemDC = CreateCompatibleDC(hdc);
		_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
		_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
		_blendImage->width = WINSIZEX;
		_blendImage->height = WINSIZEY;
		_alpha = TRUE;
	}
	else
		_alpha = FALSE;

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

//������ �̹��� ���
HRESULT ApiImage::Init(const char* fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor, BOOL alpha)
{
	if (fileName == NULL) return E_FAIL;

	if (_imageInfo != NULL) Release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x - (width / 2);
	_imageInfo->y = y - (height / 2);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;

	//���ϰ�� �̸� �����ؼ� ������
	int len = strlen(fileName);

	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//����Į�� �ʱ�ȭ
	_trans = trans;
	_transColor = transColor;

	if (_imageInfo->hBit == 0)
	{
		Release();

		return E_FAIL;
	}

	if (alpha)
	{
		_blendFunc.BlendFlags = 0;
		_blendFunc.AlphaFormat = 0;
		_blendFunc.BlendOp = AC_SRC_OVER;

		_blendImage = new IMAGE_INFO;
		_blendImage->loadType = LOAD_EMPTY;
		_blendImage->resID = 0;
		_blendImage->hMemDC = CreateCompatibleDC(hdc);
		_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
		_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
		_blendImage->width = WINSIZEX;
		_blendImage->height = WINSIZEY;
		_alpha = TRUE;
	}
	else
		_alpha = FALSE;

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT ApiImage::Init(const char* fileName, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor, BOOL alpha)
{
	if (fileName == NULL) return E_FAIL;

	if (_imageInfo != NULL) Release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;

	//���ϰ�� �̸� �����ؼ� ������
	int len = strlen(fileName);

	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//����Į�� �ʱ�ȭ
	_trans = trans;
	_transColor = transColor;

	if (_imageInfo->hBit == 0)
	{
		Release();

		return E_FAIL;
	}

	if (alpha)
	{
		_blendFunc.BlendFlags = 0;
		_blendFunc.AlphaFormat = 0;
		_blendFunc.BlendOp = AC_SRC_OVER;

		_blendImage = new IMAGE_INFO;
		_blendImage->loadType = LOAD_EMPTY;
		_blendImage->resID = 0;
		_blendImage->hMemDC = CreateCompatibleDC(hdc);
		_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
		_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
		_blendImage->width = WINSIZEX;
		_blendImage->height = WINSIZEY;
		_alpha = TRUE;
	}
	else
		_alpha = FALSE;

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

void ApiImage::Release(void)
{
	if (_imageInfo)
	{
		//�̹��� ����
		SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);

		//�����͵� ����
		SAFE_DELETE(_imageInfo);
		SAFE_DELETE(_fileName);

		//���� �ʱ�ȭ
		_trans = false;
		_transColor = RGB(0, 0, 0);
	}

	if (_alpha)
	{
		SelectObject(_blendImage->hMemDC, _blendImage->hOBit);
		DeleteObject(_blendImage->hBit);
		DeleteDC(_blendImage->hMemDC);

		//�����͵� ����
		SAFE_DELETE(_blendImage);
		//SAFE_DELETE(_blendFunc);
		_alpha = FALSE;

	}
}

void ApiImage::SetTransColor(BOOL trans, COLORREF transColor)
{
	_trans = trans;
	_transColor = transColor;
}



//���� �̹��� ����

void ApiImage::Render(HDC hdc)
{
	if (_trans)
	{
		GdiTransparentBlt(hdc,	//����� ��� DC
			_imageInfo->x,		//����� ��ǥ ������ X
			_imageInfo->y,		//����� ��ǥ ������ Y
			_imageInfo->width,	//����� ũ�� width
			_imageInfo->height,	//����� ũ�� height
			_imageInfo->hMemDC,	//������ DC
			0, 0,				//����� ��������
			_imageInfo->width,	//����� �������� width
			_imageInfo->height,	//����� �������� height
			_transColor);		//���翡�� ���ܵ� ����
	}
	else
	{
		//DC �������� ��Ӻ��� ���
		BitBlt(hdc, _imageInfo->x, _imageInfo->y,
			_imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}
void ApiImage::Render(HDC hdc, int destX, int destY)
{
	if (_trans)
	{
		GdiTransparentBlt(hdc,	//����� ��� DC
			destX,				//����� ��ǥ ������ X
			destY,				//����� ��ǥ ������ Y
			_imageInfo->width,	//����� ũ�� width
			_imageInfo->height,	//����� ũ�� height
			_imageInfo->hMemDC,	//������ DC
			0, 0,				//����� ��������
			_imageInfo->width,	//����� �������� width
			_imageInfo->height,	//����� �������� height
			_transColor);		//���翡�� ���ܵ� ����
	}
	else
	{
		//DC �������� ��Ӻ��� ���
		BitBlt(hdc, destX, destY,
			_imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}
void ApiImage::Render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	if (_trans)
	{
		GdiTransparentBlt(hdc,	//����� ��� DC
			destX,				//����� ��ǥ ������ X
			destY,				//����� ��ǥ ������ Y
			sourWidth,			//����� ũ�� width
			sourHeight,			//����� ũ�� height
			_imageInfo->hMemDC,	//������ DC
			sourX, sourY,		//����� ��������
			sourWidth,			//����� �������� width
			sourHeight,			//����� �������� height
			_transColor);		//���翡�� ���ܵ� ����
	}
	else
	{
		//DC �������� ��Ӻ��� ���
		BitBlt(hdc, destX, destY,
			sourWidth, sourHeight,
			_imageInfo->hMemDC, sourX, sourY, SRCCOPY);
	}
}

void ApiImage::Render(HDC hdc, int destX, int destY, int sourX, int sourY, int destWidth, int destHeight, int sourWidth, int sourHeight)
{
	if (_trans)
	{
		GdiTransparentBlt(hdc,
			destX,
			destY,
			destWidth,
			destHeight,
			_imageInfo->hMemDC,
			sourX, sourY,
			sourWidth,
			sourHeight,
			_transColor);
	}
	else
	{
		//DC �������� ��Ӻ��� ���
		BitBlt(hdc, destX, destY,
			destWidth, destHeight,
			_imageInfo->hMemDC, sourX, sourY, SRCCOPY);
	}
}


void ApiImage::FrameRender(HDC hdc, int destX, int destY)
{
	if (_trans)
	{
		GdiTransparentBlt(hdc,				//����� ��� DC
			destX,							//����� ��ǥ ������ X
			destY,							//����� ��ǥ ������ Y
			_imageInfo->frameWidth,			//����� ũ�� width
			_imageInfo->frameHeight,		//����� ũ�� height
			_imageInfo->hMemDC,				//������ DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,		//����� ��������
			_imageInfo->frameWidth,			//����� �������� width
			_imageInfo->frameHeight,		//����� �������� height
			_transColor);					//���翡�� ���ܵ� ����


	}
	else
	{
		//DC �������� ��Ӻ��� ���
		BitBlt(hdc, destX, destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			SRCCOPY);
	}
}
void ApiImage::FrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;


	if (_trans)
	{
		GdiTransparentBlt(hdc,				//����� ��� DC
			destX,							//����� ��ǥ ������ X
			destY,							//����� ��ǥ ������ Y
			_imageInfo->frameWidth,			//����� ũ�� width
			_imageInfo->frameHeight,		//����� ũ�� height
			_imageInfo->hMemDC,				//������ DC
			currentFrameX * _imageInfo->frameWidth,
			currentFrameY * _imageInfo->frameHeight,		//����� ��������
			_imageInfo->frameWidth,			//����� �������� width
			_imageInfo->frameHeight,		//����� �������� height
			_transColor);					//���翡�� ���ܵ� ����
	}
	else
	{
		//DC �������� ��Ӻ��� ���
		BitBlt(hdc, destX, destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			currentFrameX * _imageInfo->frameWidth,
			currentFrameY * _imageInfo->frameHeight,
			SRCCOPY);
	}
}
void ApiImage::LoopRender(HDC hdc, const LPRECT drawArea, int offSetX, int offSetY)
{
	if (offSetX < 0) offSetX = _imageInfo->width + (offSetX % _imageInfo->width);
	if (offSetY < 0) offSetY = _imageInfo->height + (offSetY % _imageInfo->height);

	//�׷����� �ҽ��� ����(�̹���) ����
	RECT rcSour;
	int sourWidth;
	int sourHeight;

	//�׷����� ����
	RECT rcDest;

	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;

	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		//�̹����� ���� ���
		rcSour.top = (y + offSetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;
		sourHeight = rcSour.bottom - rcSour.top;

		//�ҽ��� ������ ��ο� ����(�׷��ִ� ����) ������ ������!
		if (y + sourHeight > drawAreaH)
		{
			//�Ѿ �κ��� �ٽ� �׷��ش�
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		//x������!
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			//�ҽ��� ���� ���� ���
			rcSour.left = (x + offSetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;
			sourWidth = rcSour.right - rcSour.left;

			if (x + sourWidth > drawAreaW)
			{
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			Render(hdc, rcDest.left, rcDest.top,
				rcSour.left, rcSour.top,
				rcSour.right - rcSour.left,
				rcSour.bottom - rcSour.top);
		}


	}
}

// Alpha ���� ������

void ApiImage::AlphaRender(HDC hdc, BYTE alpha)
{
	if (!_alpha) return;
	_blendFunc.SourceConstantAlpha = alpha;

	if (_trans)
	{
		BitBlt(_blendImage->hMemDC, 0, 0,
			_imageInfo->width, _imageInfo->height,
			hdc,
			(int)_imageInfo->x, (int)_imageInfo->y, SRCCOPY);

		GdiTransparentBlt(_blendImage->hMemDC,
			0,
			0,
			_imageInfo->width,
			_imageInfo->height,
			_imageInfo->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_transColor);

		AlphaBlend(hdc, (int)_imageInfo->x, (int)_imageInfo->y,
			_imageInfo->width, _imageInfo->height,
			_blendImage->hMemDC,
			0, 0,
			_imageInfo->width, _imageInfo->height, _blendFunc);
	}
	else
	{
		AlphaBlend(hdc, (int)_imageInfo->x, (int)_imageInfo->y,
			_imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC,
			0, 0,
			_imageInfo->width, _imageInfo->height, _blendFunc);
	}
}
void ApiImage::AlphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	if (!_alpha) return;
	_blendFunc.SourceConstantAlpha = alpha;

	if (_trans)
	{
		BitBlt(_blendImage->hMemDC, 0, 0,
			_imageInfo->width,
			_imageInfo->height,
			hdc,
			destX,
			destY, SRCCOPY);

		GdiTransparentBlt(
			_blendImage->hMemDC,
			0,
			0,
			_imageInfo->width,
			_imageInfo->height,
			_imageInfo->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_transColor);

		AlphaBlend(hdc, destX, destY,
			_imageInfo->width, _imageInfo->height,
			_blendImage->hMemDC,
			0, 0,
			_imageInfo->width, _imageInfo->height, _blendFunc);
	}
	else
	{
		AlphaBlend(hdc, destX, destY,
			_imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC,
			0, 0,
			_imageInfo->width, _imageInfo->height, _blendFunc);
	}
}
void ApiImage::AlphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	if (!_alpha) return;
	_blendFunc.SourceConstantAlpha = alpha;
	if (_trans)
	{
		BitBlt(_blendImage->hMemDC, 0, 0,
			_imageInfo->width, _imageInfo->height,
			hdc,
			destX, destY, SRCCOPY);

		GdiTransparentBlt(_blendImage->hMemDC,
			0,
			0,
			sourWidth,
			sourHeight,
			_imageInfo->hMemDC,
			sourX, sourY,
			sourWidth,
			sourHeight,
			_transColor);

		AlphaBlend(hdc, destX, destY,
			sourWidth,
			sourHeight,
			_blendImage->hMemDC,
			0, 0,
			sourWidth,
			sourHeight, _blendFunc);
	}
	else
	{
		AlphaBlend(hdc, destX, destY,
			sourWidth,
			sourHeight,
			_imageInfo->hMemDC,
			0, 0,
			sourWidth,
			sourHeight, _blendFunc);
	}
}
void ApiImage::FrameAlphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	if (!_alpha) return;
	_blendFunc.SourceConstantAlpha = alpha;


	if (_trans)
	{
		BitBlt(
			_blendImage->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			hdc,
			destX, destY, SRCCOPY);

		GdiTransparentBlt(
			_blendImage->hMemDC,//����� ��� DC
			0,							//����� ��ǥ ������ X
			0,							//����� ��ǥ ������ Y
			_imageInfo->frameWidth,			//����� ũ�� width
			_imageInfo->frameHeight,		//����� ũ�� height
			_imageInfo->hMemDC,				//������ DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,		//����� ��������
			_imageInfo->frameWidth,			//����� �������� width
			_imageInfo->frameHeight,		//����� �������� height
			_transColor);					//���翡�� ���ܵ� ����

		AlphaBlend(hdc,
			destX, destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_blendImage->hMemDC,
			0, 0,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_blendFunc);
	}
	else
	{
		AlphaBlend(hdc,
			destX, destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			0, 0,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_blendFunc);
	}
}
void ApiImage::FrameAlphaRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha)
{
	if (!_alpha) return;
	_blendFunc.SourceConstantAlpha = alpha;

	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	if (_trans)
	{
		BitBlt(
			_blendImage->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			hdc,
			destX, destY, SRCCOPY);

		GdiTransparentBlt(
			_blendImage->hMemDC,			//����� ��� DC
			0,								//����� ��ǥ ������ X
			0,								//����� ��ǥ ������ Y
			_imageInfo->frameWidth,			//����� ũ�� width
			_imageInfo->frameHeight,		//����� ũ�� height
			_imageInfo->hMemDC,				//������ DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,		//����� ��������
			_imageInfo->frameWidth,			//����� �������� width
			_imageInfo->frameHeight,		//����� �������� height
			_transColor);					//���翡�� ���ܵ� ����


		AlphaBlend(hdc,
			destX, destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_blendImage->hMemDC,
			0, 0,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_blendFunc);
	}
	else
	{
		AlphaBlend(hdc,
			destX, destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_blendImage->hMemDC,
			0, 0,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_blendFunc);
	}
}
void ApiImage::LoopAlphaRender(HDC hdc, const LPRECT drawArea, int offSetX, int offSetY, BYTE alpha)
{
	if (!_alpha) return;
	if (offSetX < 0) offSetX = _imageInfo->width + (offSetX % _imageInfo->width);
	if (offSetY < 0) offSetY = _imageInfo->height + (offSetY % _imageInfo->height);

	//�׷����� �ҽ��� ����(�̹���) ����
	RECT rcSour;
	int sourWidth;
	int sourHeight;

	//�׷����� ����
	RECT rcDest;

	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;

	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		//�̹����� ���� ���
		rcSour.top = (y + offSetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;
		sourHeight = rcSour.bottom - rcSour.top;

		//�ҽ��� ������ ��ο� ����(�׷��ִ� ����) ������ ������!
		if (y + sourHeight > drawAreaH)
		{
			//�Ѿ �κ��� �ٽ� �׷��ش�
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		//x������!
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			//�ҽ��� ���� ���� ���
			rcSour.left = (x + offSetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;
			sourWidth = rcSour.right - rcSour.left;

			if (x + sourWidth > drawAreaW)
			{
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			AlphaRender(hdc, rcDest.left, rcDest.top,
				rcSour.left, rcSour.top,
				rcSour.right - rcSour.left,
				rcSour.bottom - rcSour.top, alpha);
		}
	}
}

//void ApiImage::AniRender(HDC hdc, int destX, int destY, Animation* ani)
//{
//	Render(hdc, destX, destY, ani->GetFramePos().x, ani->GetFramePos().y, ani->GetFrameWidth(), ani->GetFrameHeight());
//}
//
//void ApiImage::AniAlphaRender(HDC hdc, int destX, int destY, Animation* ani, BYTE alpha)
//{
//	AlphaRender(hdc, destX, destY, ani->GetFramePos().x, ani->GetFramePos().y, ani->GetFrameWidth(), ani->GetFrameHeight(), alpha);
//}
//
