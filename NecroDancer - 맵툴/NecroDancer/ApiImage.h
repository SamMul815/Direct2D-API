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
		LOAD_RESOURCE,	//리소스 파일로부터 pk3. pak
		LOAD_FILE,		//파일로부터
		LOAD_EMPTY,		//빈 비트맵 파일
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
		int		currentFrameX;	//현재 프레임X
		int		currentFrameY;	//현재 프레임Y
		int		maxFrameX;		//최대 프레임
		int		maxFrameY;
		int		frameWidth;		//프레임 가로 크기
		int		frameHeight;	//프레임 세로 크기

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

		//같은 구조체지만 IMAGE_INFO, 그 구조체 변수에 접근하기 위한 포인터 LPIMAGE_INFO
	}IMAGE_INFO, *LPIMAGE_INFO;

private:
	LPIMAGE_INFO	_imageInfo;		//이미지 구조체
	CHAR*			_fileName;		//뽜일 이름
	BOOL			_trans;			//특정 픽셀값을 날릴꺼니?
	COLORREF		_transColor;	//날릴꺼면 뭘날릴래?

	BOOL			_alpha;			//알파값을 사용할꺼니?
	BLENDFUNCTION	_blendFunc;		//알파블렌드를 사용하기 위한 정보
	LPIMAGE_INFO	_blendImage;	//알파블렌드를 사용하기 위한 이미지 정보

public:
	ApiImage();
	~ApiImage();

	//빈 비트맵 이미지 만들어서 사용할 경우
	HRESULT Init(int width, int height, BOOL alpha = FALSE);

	//리소스부터 읽어와서 사용할 경우
	HRESULT Init(const DWORD resID, int width, int height,
		BOOL trans = FALSE, COLORREF transColor = FALSE, BOOL alpha = FALSE);

	//파일로부터 읽어와서 사용할 경우
	HRESULT Init(const char* fileName, int width, int height,
		BOOL trans = FALSE, COLORREF transColor = FALSE, BOOL alpha = FALSE);

	HRESULT Init(const char* fileName, float x, float y, int width, int height,
		BOOL trans = FALSE, COLORREF transColor = FALSE, BOOL alpha = FALSE);

	//프레임 이미지 등록
	HRESULT Init(const char* fileName, float x, float y, int width, int height, int frameX, int frameY,
		BOOL trans = FALSE, COLORREF transColor = FALSE, BOOL alpha = FALSE);

	HRESULT Init(const char* fileName, int width, int height, int frameX, int frameY,
		BOOL trans = FALSE, COLORREF transColor = FALSE, BOOL alpha = FALSE);

	void Release(void);

	void SetTransColor(BOOL trans, COLORREF transColor);

	void Render(HDC hdc);

	//			HDC		뿌려줄 좌표X, 뿌려줄 좌표Y
	void Render(HDC hdc, int destX, int destY);

	//			HDC		뿌려줄 좌표X  뿌려줄 좌표Y 가져올 X   가져올 Y	 가져올 그림width, 가져올 그림 height
	void Render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	// 인벤토리용 렌더
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

	//애니메이션 렌더
//	void AniRender(HDC hdc, int destX, int destY, Animation* ani);
//	void AniAlphaRender(HDC hdc, int destX, int destY, Animation* ani, BYTE alpha);

	inline HDC GetMemDC(void) { return _imageInfo->hMemDC; }

	//=============================
	// 이미지 관련 Getter, Setter //
	//=============================

	inline void SetX(float x) { _imageInfo->x = x; }
	inline float GetX() { return _imageInfo->x; }

	inline void SetY(float y) { _imageInfo->y = y; }
	inline float GetY() { return _imageInfo->y; }

	//이미지 중점좌표
	inline void SetCenter(float x, float y)
	{
		_imageInfo->x = x - (_imageInfo->width / 2);
		_imageInfo->y = y - (_imageInfo->height / 2);
	}

	//중점 X
	inline float GetCenterX(void)
	{
		return _imageInfo->maxFrameX <= 0 ?
			_imageInfo->x + (_imageInfo->width / 2) :
			_imageInfo->x + (_imageInfo->frameWidth / 2);
	}

	//중점 Y
	inline float GetCenterY(void)
	{
		return _imageInfo->maxFrameY <= 0 ?
			_imageInfo->y + (_imageInfo->height / 2) :
			_imageInfo->y + (_imageInfo->frameHeight / 2);
	}

	//가로 해상도
	inline int GetWidth(void) { return _imageInfo->width; }

	//세로 해상도
	inline int GetHeight(void) { return _imageInfo->height; }

	//프레임 관련 
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

