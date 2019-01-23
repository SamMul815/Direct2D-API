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

//�⺻ �̹��� �߰�
D2DImage* ImageManager::AddImage(string strKey, LPCWSTR fileName, float width, float height)
{
	//������ Ű ���� �ִ°�? ������ �װ� �׳� �������ش�
	D2DImage* img = FindImage(strKey);

	if (img) return img;

	//������� ������ �Դٸ� Ű ���� ����
	img = new D2DImage;

	//�̹��� �ʱ�ȭ�� �����ϸ� NULL������ �ʱ�ȭ
	if (FAILED(img->Init(fileName,width, height)))
	{
		SAFE_DELETE(img);

		return NULL;
	}

	//������� ������ �Դٸ� �ʱ�ȭ�� �� �� ��Ȳ
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

//������ �̹��� �߰�
D2DImage* ImageManager::AddImage(string strKey, LPCWSTR fileName, float width, float height, int frameX, int frameY)
{
	//������ Ű ���� �ִ°�? ������ �װ� �׳� �������ش�
	D2DImage* img = FindImage(strKey);

	if (img) return img;

	//������� ������ �Դٸ� Ű ���� ����
	img = new D2DImage;

	//�̹��� �ʱ�ȭ�� �����ϸ� NULL������ �ʱ�ȭ
	if (FAILED(img->Init(fileName, width, height,frameX,frameY)))
	{
		SAFE_DELETE(img);

		return NULL;
	}

	//������� ������ �Դٸ� �ʱ�ȭ�� �� �� ��Ȳ
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

//���� �Լ�
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

//������ ����
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


//�ִ� ����
void ImageManager::AniRender(string strKey, float destX, float destY, Animation* ani,float alpha)
{
	D2DImage* img = FindImage(strKey);

	if (img) img->AniRender(destX, destY,ani,alpha);
}

//�̹��� Ű ������ ã�� �Լ�
D2DImage* ImageManager::FindImage(string strKey)
{
	mapImageIter key = _mImageList.find(strKey);

	//�̹����� ������
	if (key != _mImageList.end())
	{
		return key->second;
	}

	return NULL;
}