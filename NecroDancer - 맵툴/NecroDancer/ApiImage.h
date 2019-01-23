#pragma once
//#include "Animation.h"
//========================================================
// 2015. 12. 04 ## image Class ## - Tango Team -
//========================================================

class ApiImage
{
public:
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE,	//���ҽ� ���Ϸκ��� pk3. pak
		LOAD_FILE,		//���Ϸκ���
		LOAD_EMPTY,		//�� ��Ʈ�� ����
		LOAD_END
	};

	typedef struct tagImageInfo
	{
		DWORD	resID;
		HDC		hMemDC;
		HBITMAP hBit;
		HBITMAP hOBit;
		float	x;
		float	y;
		int		width;
		int		height;
		int		currentFrameX;	//���� ������X
		int		currentFrameY;	//���� ������Y
		int		maxFrameX;		//�ִ� ������
		int		maxFrameY;
		int		frameWidth;		//������ ���� ũ��
		int		frameHeight;	//������ ���� ũ��

		BYTE	loadType;
		tagImageInfo()
		{
			resID = 0;
			hMemDC = NULL;
			hBit = NULL;
			hOBit = NULL;
			x = 0;
			y = 0;
			width = 0;
			height = 0;
			currentFrameX = 0;
			currentFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			loadType = LOAD_RESOURCE;
		}

		//���� ����ü���� IMAGE_INFO, �� ����ü ������ �����ϱ� ���� ������ LPIMAGE_INFO
	}IMAGE_INFO, *LPIMAGE_INFO;

private:
	LPIMAGE_INFO	_imageInfo;		//�̹��� ����ü
	CHAR*			_fileName;		//���� �̸�
	BOOL			_trans;			//Ư�� �ȼ����� ��������?
	COLORREF		_transColor;	//�������� ��������?

	BOOL			_alpha;			//���İ��� ����Ҳ���?
	BLENDFUNCTION	_blendFunc;		//���ĺ��带 ����ϱ� ���� ����
	LPIMAGE_INFO	_blendImage;	//���ĺ��带 ����ϱ� ���� �̹��� ����

public:
	ApiImage();
	~ApiImage();

	//�� ��Ʈ�� �̹��� ���� ����� ���
	HRESULT Init(int width, int height, BOOL alpha = FALSE);

	//���ҽ����� �о�ͼ� ����� ���
	HRESULT Init(const DWORD resID, int width, int height,
		BOOL trans = FALSE, COLORREF transColor = FALSE, BOOL alpha = FALSE);

	//���Ϸκ��� �о�ͼ� ����� ���
	HRESULT Init(const char* fileName, int width, int height,
		BOOL trans = FALSE, COLORREF transColor = FALSE, BOOL alpha = FALSE);

	HRESULT Init(const char* fileName, float x, float y, int width, int height,
		BOOL trans = FALSE, COLORREF transColor = FALSE, BOOL alpha = FALSE);

	//������ �̹��� ���
	HRESULT Init(const char* fileName, float x, float y, int width, int height, int frameX, int frameY,
		BOOL trans = FALSE, COLORREF transColor = FALSE, BOOL alpha = FALSE);

	HRESULT Init(const char* fileName, int width, int height, int frameX, int frameY,
		BOOL trans = FALSE, COLORREF transColor = FALSE, BOOL alpha = FALSE);

	void Release(void);

	void SetTransColor(BOOL trans, COLORREF transColor);

	void Render(HDC hdc);

	//			HDC		�ѷ��� ��ǥX, �ѷ��� ��ǥY
	void Render(HDC hdc, int destX, int destY);

	//			HDC		�ѷ��� ��ǥX  �ѷ��� ��ǥY ������ X   ������ Y	 ������ �׸�width, ������ �׸� height
	void Render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	// �κ��丮�� ����
	void Render(HDC hdc, int destX, int destY, int sourX, int sourY, int destWidth, int destHeight, int sourWidth, int sourHeight);


	void FrameRender(HDC hdc, int destX, int destY);
	void FrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	void LoopRender(HDC hdc, const LPRECT drawArea, int offSetX, int offSetY);

	void AlphaRender(HDC hdc, BYTE alpha);
	void AlphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	void AlphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

	void FrameAlphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	void FrameAlphaRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha);
	void LoopAlphaRender(HDC hdc, const LPRECT drawArea, int offSetX, int offSetY, BYTE alpha);

	//�ִϸ��̼� ����
//	void AniRender(HDC hdc, int destX, int destY, Animation* ani);
//	void AniAlphaRender(HDC hdc, int destX, int destY, Animation* ani, BYTE alpha);

	inline HDC GetMemDC(void) { return _imageInfo->hMemDC; }

	//=============================
	// �̹��� ���� Getter, Setter //
	//=============================

	inline void SetX(float x) { _imageInfo->x = x; }
	inline float GetX() { return _imageInfo->x; }

	inline void SetY(float y) { _imageInfo->y = y; }
	inline float GetY() { return _imageInfo->y; }

	//�̹��� ������ǥ
	inline void SetCenter(float x, float y)
	{
		_imageInfo->x = x - (_imageInfo->width / 2);
		_imageInfo->y = y - (_imageInfo->height / 2);
	}

	//���� X
	inline float GetCenterX(void)
	{
		return _imageInfo->maxFrameX <= 0 ?
			_imageInfo->x + (_imageInfo->width / 2) :
			_imageInfo->x + (_imageInfo->frameWidth / 2);
	}

	//���� Y
	inline float GetCenterY(void)
	{
		return _imageInfo->maxFrameY <= 0 ?
			_imageInfo->y + (_imageInfo->height / 2) :
			_imageInfo->y + (_imageInfo->frameHeight / 2);
	}

	//���� �ػ�
	inline int GetWidth(void) { return _imageInfo->width; }

	//���� �ػ�
	inline int GetHeight(void) { return _imageInfo->height; }

	//������ ���� 
	inline void SetFrameX(int frameX)
	{
		_imageInfo->currentFrameX = frameX;
		if (frameX > _imageInfo->maxFrameX) _imageInfo->currentFrameX = _imageInfo->maxFrameX;
	}

	inline void SetFrameY(int frameY)
	{
		_imageInfo->currentFrameY = frameY;
		if (frameY > _imageInfo->maxFrameY) _imageInfo->currentFrameY = _imageInfo->maxFrameY;
	}

	inline int GetMaxFrameX(void) { return _imageInfo->maxFrameX; }
	inline int GetMaxFrameY(void) { return _imageInfo->maxFrameY; }

	inline int GetFrameX(void) { return _imageInfo->currentFrameX; }
	inline int GetFrameY(void) { return _imageInfo->currentFrameY; }

	inline int GetFrameWidth(void) { return _imageInfo->frameWidth; }
	inline int GetFrameHeight(void) { return _imageInfo->frameHeight; }

};

