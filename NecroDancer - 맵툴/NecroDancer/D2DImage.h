#pragma once
#include "D2DUtils.h"
#include "Animation.h"
class D2DImage
{
public:
	typedef struct tagImageInfo
	{
		DWORD resID;
		IWICImagingFactory*		 pWICImagingFactory;		//�Է�
		IWICFormatConverter*	 pWICConverter;				//������
		IWICBitmapDecoder*		 pWICDecoder;				//���ڴ�
		IWICBitmapFrameDecode*	 pWICFrameDecoder;			//������ ���ڴ�

		ID2D1Bitmap*			 pBitmap;

		float width;
		float height;
		int currentFrameX;
		int currentFrameY;
		int maxFrameX;
		int maxFrameY;
		float frameWidth;
		float frameHeight;
		tagImageInfo()
		{
			resID			 = 0;
			pWICImagingFactory = nullptr;
			pWICConverter 	 = nullptr;
			pWICDecoder		 = nullptr;
			pWICFrameDecoder = nullptr;
			pBitmap			 = nullptr;
			width			 = 0;
			height			 = 0;
			currentFrameX	 = 0;
			currentFrameY	 = 0;
			maxFrameX		 = 0;
			maxFrameY		 = 0;
			frameWidth		 = 0;
			frameHeight		 = 0;
		}
	}IMAGE_INFO, *LPIMAGE_INFO;

private:
	LPIMAGE_INFO	_imageInfo;
	LPWSTR			_fileName;
	
public:
	D2DImage();
	~D2DImage();
	
	HRESULT D2DSetting(LPCWSTR fileName);

	HRESULT Init(LPCWSTR fileName, float width, float height);
	HRESULT Init(LPCWSTR fileName, float width, float height, int frameX, int frameY);

	//�׳� ����
	void Render(float alpha = 1.0f);
	void Render(float destX, float destY, float alpha = 1.0f);
	void Render(float destX, float destY, float width, float height, float alpha = 1.0f);
	void Render(float destX, float destY, float sourX, float sourY, float sourWidth, float sourHeight, float alpha = 1.0f);
	
	void RenderTest(float destX, float destY, float alpha = 1.0f);

	//������ ����
	void FrameRender(float destX, float destY, float alpha = 1.0f);
	void FrameRender(float destX, float destY, int frameCount, float alpha = 1.0f);
	void FrameRender(float destX, float destY, int currentFrameX, int currentFrameY, float alpha = 1.0f);
	
	//�ִϸ޴ϼ� ����
	void AniRender(float destX, float destY,Animation* ani,float alpha = 1.0f);


	//�¿� ���� ����
	void FlipRender(float destX, float destY, float alpha = 1.0f);
	void FlipRender(float destX, float destY, float width, float height, float alpha = 1.0f);
	void FlipFrameRender(float destX, float destY, float alpha = 1.0f);
	void FlipFrameRender(float destX, float destY, int frameCount, float alpha = 1.0f);
	void FlipFrameRender(float destX, float destY, int currentFrameX, int currentFrameY, float alpha = 1.0f);

	void Release();


	float GetWidth()		{ return _imageInfo->width; } 
	float GetHeight()		{ return _imageInfo->height; }

	float GetFrameWidth()	{ return _imageInfo->frameWidth; }
	float GetFrameHeight()	{ return _imageInfo->frameHeight; }

	int GetMaxFrameX()		{ return _imageInfo->maxFrameX; }
	int GetMaxFrameY()		{ return _imageInfo->maxFrameY; }

};

