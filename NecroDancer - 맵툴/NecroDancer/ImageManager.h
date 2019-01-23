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

	//�⺻ �̹���
	D2DImage* AddImage(string strKey, LPCWSTR fileName, float width, float height);

	//������ �̹���
	D2DImage* AddImage(string strKey, LPCWSTR fileName, float width, float height, int frameX, int frameY);

	//�̹��� Ű ������ ã�� �Լ�
	D2DImage* FindImage(string strKey);

	BOOL DeleteImage(string strKey);

	BOOL DeleteAll(void);

	//���� �Լ�
	void Render(string strKey, float alpha =1.0f);
	void Render(string strKey, float destX, float destY, float alpha = 1.0f);
	void Render(string strKey, float destX, float destY, float width, float height, float alpha = 1.0f);
	void Render(string strKey, float destX, float destY, float sourX, float sourY, float sourWidth, float sourHeight, float alpha = 1.0f);
	

	//������ ����
	void FrameRender(string strKey, float destX, float destY, float alpha = 1.0f);
	void FrameRender(string strKey, float destX, float destY, int frameCount, float alpha = 1.0f);
	void FrameRender(string strKey, float destX, float destY, int currentFrameX, int currentFrameY, float alpha = 1.0f);


	//�ִ� ����
	void AniRender(string strKey, float destX, float destY, Animation* ani,float alpha = 1.0f);

	//���� ����
	ImageManager();
	~ImageManager();
};

