#pragma once
#include "singletonBase.h"
#include "D2DImage.h"
#include <map>

class ImageManager : public SingletonBase<ImageManager>
{
private:
	typedef map<string, D2DImage*> mapImageList;
	typedef map<string, D2DImage*>::iterator mapImageIter;

private:
	mapImageList    _mImageList;

public:
	HRESULT Init(void);
	void Release(void);

	//기본 이미지
	D2DImage* AddImage(string strKey, LPCWSTR fileName, float width, float height);

	//프레임 이미지
	D2DImage* AddImage(string strKey, LPCWSTR fileName, float width, float height, int frameX, int frameY);

	//이미지 키 값으로 찾는 함수
	D2DImage* FindImage(string strKey);

	BOOL DeleteImage(string strKey);

	BOOL DeleteAll(void);

	//렌더 함수
	void Render(string strKey, float alpha =1.0f);
	void Render(string strKey, float destX, float destY, float alpha = 1.0f);
	void Render(string strKey, float destX, float destY, float width, float height, float alpha = 1.0f);
	void Render(string strKey, float destX, float destY, float sourX, float sourY, float sourWidth, float sourHeight, float alpha = 1.0f);
	

	//프레임 렌더
	void FrameRender(string strKey, float destX, float destY, float alpha = 1.0f);
	void FrameRender(string strKey, float destX, float destY, int frameCount, float alpha = 1.0f);
	void FrameRender(string strKey, float destX, float destY, int currentFrameX, int currentFrameY, float alpha = 1.0f);


	//애니 렌더
	void AniRender(string strKey, float destX, float destY, Animation* ani,float alpha = 1.0f);

	//알파 렌더
	ImageManager();
	~ImageManager();
};

