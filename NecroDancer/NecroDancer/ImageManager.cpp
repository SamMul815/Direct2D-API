#include "stdafx.h"
#include "ImageManager.h"

ImageManager::ImageManager()
{

}
ImageManager::~ImageManager()
{

}


HRESULT ImageManager::Init(void)
{
	return S_OK;
}
void ImageManager::Release(void)
{
	DeleteAll();
}

//기본 이미지 추가
D2DImage* ImageManager::AddImage(string strKey, LPCWSTR fileName, float width, float height)
{
	//동일한 키 값이 있는가? 있으면 그걸 그냥 대입해준다
	D2DImage* img = FindImage(strKey);

	if (img) return img;

	//여기까지 연산이 왔다면 키 값이 없다
	img = new D2DImage;

	//이미지 초기화가 실패하면 NULL값으로 초기화
	if (FAILED(img->Init(fileName,width, height)))
	{
		SAFE_DELETE(img);

		return NULL;
	}

	//여기까지 연산이 왔다면 초기화가 잘 된 상황
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

//프레임 이미지 추가
D2DImage* ImageManager::AddImage(string strKey, LPCWSTR fileName, float width, float height, int frameX, int frameY)
{
	//동일한 키 값이 있는가? 있으면 그걸 그냥 대입해준다
	D2DImage* img = FindImage(strKey);

	if (img) return img;

	//여기까지 연산이 왔다면 키 값이 없다
	img = new D2DImage;

	//이미지 초기화가 실패하면 NULL값으로 초기화
	if (FAILED(img->Init(fileName, width, height,frameX,frameY)))
	{
		SAFE_DELETE(img);

		return NULL;
	}

	//여기까지 연산이 왔다면 초기화가 잘 된 상황
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

BOOL ImageManager::DeleteImage(string strKey)
{
	mapImageIter key = _mImageList.find(strKey);

	if (key != _mImageList.end())
	{
		key->second->Release();
		SAFE_DELETE(key->second);
		_mImageList.erase(key);

		return true;
	}

	return false;
}

BOOL ImageManager::DeleteAll(void)
{
	mapImageIter iter = _mImageList.begin();

	for (; iter != _mImageList.end();)
	{
		if (iter->second != NULL)
		{
			SAFE_DELETE(iter->second);
			iter = _mImageList.erase(iter);
		}
		else
		{
			++iter;
		}
	}

	_mImageList.clear();

	return TRUE;
}

//렌더 함수
void ImageManager::Render(string strKey, float alpha )
{
	D2DImage* img = FindImage(strKey);

	if (img) img->Render(alpha);
}
void ImageManager::Render(string strKey, float destX, float destY, float alpha)
{
	D2DImage* img = FindImage(strKey);

	if (img) img->Render(destX,destY,alpha);
}
void ImageManager::Render(string strKey, float destX, float destY, float width, float height, float alpha)
{
	D2DImage* img = FindImage(strKey);

	if (img) img->Render(destX, destY,width,height, alpha);
}
void ImageManager::Render(string strKey, float destX, float destY, float sourX, float sourY, float sourWidth, float sourHeight, float alpha)
{
	D2DImage* img = FindImage(strKey);

	if (img) img->Render(destX, destY,sourX,sourY,sourWidth,sourHeight, alpha);
}

//프레임 렌더
void ImageManager::FrameRender(string strKey, float destX, float destY, float alpha)
{
	D2DImage* img = FindImage(strKey);

	if (img) img->FrameRender(destX, destY, alpha);
}
void ImageManager::FrameRender(string strKey, float destX, float destY,int frameCount, float alpha)
{
	D2DImage* img = FindImage(strKey);

	if (img) img->FrameRender(destX, destY, frameCount, alpha);
}
void ImageManager::FrameRender(string strKey, float destX, float destY, int currentFrameX, int currentFrameY, float alpha)
{
	D2DImage* img = FindImage(strKey);

	if (img) img->FrameRender(destX, destY,currentFrameX,currentFrameY, alpha);
}


//애니 렌더
void ImageManager::AniRender(string strKey, float destX, float destY, Animation* ani,float alpha)
{
	D2DImage* img = FindImage(strKey);

	if (img) img->AniRender(destX, destY,ani,alpha);
}

//이미지 키 값으로 찾는 함수
D2DImage* ImageManager::FindImage(string strKey)
{
	mapImageIter key = _mImageList.find(strKey);

	//이미지가 있으면
	if (key != _mImageList.end())
	{
		return key->second;
	}

	return NULL;
}