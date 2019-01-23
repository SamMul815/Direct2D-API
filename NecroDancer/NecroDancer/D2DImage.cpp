#include "stdafx.h"
#include "D2DImage.h"

D2DImage::D2DImage()
{
}


D2DImage::~D2DImage()
{
}

HRESULT D2DImage::Init(LPCWSTR fileName, float width, float height)
{
	HRESULT hr;

	if (fileName == NULL) return E_FAIL;
	if (_imageInfo != NULL) Release();

	_imageInfo = new IMAGE_INFO;
	_imageInfo->width  = width;
	_imageInfo->height = height;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->maxFrameX = 0;
	_imageInfo->maxFrameY = 0;
	_imageInfo->frameWidth = width;
	_imageInfo->frameHeight = height;

	hr = D2DSetting(fileName);
	
	if (FAILED(hr))
		return hr;

	return S_OK;
}

HRESULT D2DImage::Init(LPCWSTR fileName, float width, float height, int frameX, int frameY)
{
	HRESULT hr;
	if (fileName == NULL) return E_FAIL;
	if (_imageInfo != NULL) Release();

	_imageInfo = nullptr;
	_imageInfo = new IMAGE_INFO;
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;

	hr = D2DSetting(fileName);

	if (FAILED(hr))
		return hr;

	return S_OK;
}

void D2DImage::Release()
{
	_imageInfo = nullptr;
}

HRESULT D2DImage::D2DSetting(LPCWSTR fileName)
{
	HRESULT hr;

	CoInitialize(0);			//COM 초기화		정확히는 잘...

	hr =  CoCreateInstance(	//넘어가자 ㅠ
		CLSID_WICImagingFactory,
		0, CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(&_pWICImagingFactory)
		);

	if (FAILED(hr)) return hr;

	hr = _pWICImagingFactory->CreateDecoderFromFilename(		//디코더 생성
		fileName,
		0,
		GENERIC_READ,					//읽기전용
		WICDecodeMetadataCacheOnDemand,
		&_pWICDecoder
		);

	if (FAILED(hr)) return hr;								//안전성

	hr = _pWICDecoder->GetFrame(0, &_pWICFrameDecoder);		//0번째 프레임을 가져옴

	if (FAILED(hr))
	{
		_pWICDecoder->Release();
		return hr;
	}

	hr = _pWICImagingFactory->CreateFormatConverter(&_pWICConverter);

	if (FAILED(hr))
	{
		_pWICConverter->Release();
		return hr;
	}

	hr = _pWICConverter->Initialize(
		 _pWICFrameDecoder,
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		0, 0.0f, WICBitmapPaletteTypeCustom
		);
	if (FAILED(hr))
	{
		_pWICConverter->Release();
		_pWICDecoder->Release();
		_pWICFrameDecoder->Release();
		return hr;
	}

	//hr = D2DMANAGER->GetD2DRenderTarget()-(_imageInfo->pWICConverter, nullptr, &_imageInfo->pBitmap);
	hr = D2DMANAGER->GetD2DRenderTarget()->CreateBitmapFromWicBitmap(_pWICConverter, nullptr, &_imageInfo->pBitmap);

	_pWICConverter->Release();
	_pWICDecoder->Release();
	_pWICFrameDecoder->Release();

	return S_OK;
}

void D2DImage::Render(float alpha)
{

	if (_imageInfo->pBitmap == NULL) return;

	float drawX = 0 - CAMERA->GetX();
	float drawY = 0 - CAMERA->GetY();

	if (drawX + _imageInfo->width < 0) return;
	if (drawY + _imageInfo->height< 0) return;
	if (drawX > WINSIZEX) return;
	if (drawY > WINSIZEY) return;


	D2D1_RECT_F dxArea1 = D2D1::RectF(drawX, drawY, drawX+ _imageInfo->width, drawY+_imageInfo->height);
	D2D1_RECT_F dxArea2 = D2D1::RectF(0, 0, _imageInfo->width, _imageInfo->height);
	D2DMANAGER->GetD2DRenderTarget()->DrawBitmap(_imageInfo->pBitmap, dxArea1, alpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, dxArea2);
}

void D2DImage::Render(float destX, float destY, float alpha)
{
	if (_imageInfo->pBitmap == NULL) return;

	float drawX = destX - CAMERA->GetX();
	float drawY = destY - CAMERA->GetY();

	if (drawX + _imageInfo->width < 0) return;
	if (drawY + _imageInfo->height< 0) return;
	if (drawX > WINSIZEX) return;
	if (drawY > WINSIZEY) return;

	D2D1_RECT_F dxArea1 = D2D1::RectF(drawX, drawY, drawX + _imageInfo->width, drawY + _imageInfo->height);
	D2D1_RECT_F dxArea2 = D2D1::RectF(0, 0, _imageInfo->width, _imageInfo->height);
	D2DMANAGER->GetD2DRenderTarget()->DrawBitmap(_imageInfo->pBitmap, dxArea1, alpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, dxArea2);
}

void D2DImage::Render(float destX, float destY,float width, float height, float alpha)
{
	if (_imageInfo->pBitmap == NULL) return;

	float drawX = destX - CAMERA->GetX();
	float drawY = destY - CAMERA->GetY();

	if (drawX + _imageInfo->width < 0) return;
	if (drawY + _imageInfo->height< 0) return;
	if (drawX > WINSIZEX) return;
	if (drawY > WINSIZEY) return;

	D2D1_RECT_F dxArea1 = D2D1::RectF(drawX, drawY, drawX + width, drawY + height);
	D2D1_RECT_F dxArea2 = D2D1::RectF(0, 0, _imageInfo->width, _imageInfo->height);
	D2DMANAGER->GetD2DRenderTarget()->DrawBitmap(_imageInfo->pBitmap, dxArea1, alpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, dxArea2);
}

void D2DImage::Render(float destX, float destY, float sourX, float sourY, float sourWidth, float sourHeight, float alpha)
{
	if (_imageInfo->pBitmap == NULL) return;

	float drawX = destX - CAMERA->GetX();
	float drawY = destY - CAMERA->GetY();

	if (drawX + _imageInfo->width < 0) return;
	if (drawY + _imageInfo->height< 0) return;
	if (drawX > WINSIZEX) return;
	if (drawY > WINSIZEY) return;

	D2D1_RECT_F dxArea1 = D2D1::RectF(drawX, drawY, drawX + sourWidth, drawY + sourHeight);
	D2D1_RECT_F dxArea2 = D2D1::RectF(sourX, sourY, sourX + sourWidth, sourY + sourHeight);

	D2DMANAGER->GetD2DRenderTarget()->DrawBitmap(_imageInfo->pBitmap, dxArea1, alpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, dxArea2);
}


void D2DImage::FrameRender(float destX, float destY, float alpha)
{
	if (_imageInfo->pBitmap == NULL) return;

	float drawX = destX - CAMERA->GetX();
	float drawY = destY - CAMERA->GetY();

	if (drawX + _imageInfo->width < 0) return;
	if (drawY + _imageInfo->height< 0) return;
	if (drawX > WINSIZEX) return;
	if (drawY > WINSIZEY) return;

	D2D1_RECT_F dxArea1 = D2D1::RectF(drawX, drawY, drawX + _imageInfo->frameWidth, drawY + _imageInfo->frameHeight);
	D2D1_RECT_F dxArea2 = D2D1::RectF(
		_imageInfo->currentFrameX * _imageInfo->frameWidth,
		_imageInfo->currentFrameY * _imageInfo->frameHeight,
		_imageInfo->currentFrameX * _imageInfo->frameWidth + _imageInfo->frameWidth,
		_imageInfo->currentFrameY * _imageInfo->frameHeight + _imageInfo->frameHeight);
	D2DMANAGER->GetD2DRenderTarget()->DrawBitmap(_imageInfo->pBitmap, dxArea1, alpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, dxArea2);
}

void D2DImage::FrameRender(float destX, float destY, int frameCount, float alpha)
{
	if (_imageInfo->pBitmap == NULL) return;

	float drawX = destX - CAMERA->GetX();
	float drawY = destY - CAMERA->GetY();

	if (drawX + _imageInfo->width < 0) return;
	if (drawY + _imageInfo->height< 0) return;
	if (drawX > WINSIZEX) return;
	if (drawY > WINSIZEY) return;

	_imageInfo->currentFrameX = frameCount % (_imageInfo->maxFrameX+1);
	_imageInfo->currentFrameY = frameCount / (_imageInfo->maxFrameX+1);

	D2D1_RECT_F dxArea1 = D2D1::RectF(drawX, drawY, drawX + _imageInfo->frameWidth, drawY + _imageInfo->frameHeight);
	D2D1_RECT_F dxArea2 = D2D1::RectF(
		_imageInfo->currentFrameX * _imageInfo->frameWidth,
		_imageInfo->currentFrameY * _imageInfo->frameHeight,
		_imageInfo->currentFrameX * _imageInfo->frameWidth + _imageInfo->frameWidth,
		_imageInfo->currentFrameY * _imageInfo->frameHeight + _imageInfo->frameHeight);
	D2DMANAGER->GetD2DRenderTarget()->DrawBitmap(_imageInfo->pBitmap, dxArea1, alpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, dxArea2);
}

void D2DImage::FrameRender(float destX, float destY, int currentFrameX, int currentFrameY, float alpha)
{
	if (_imageInfo->pBitmap == NULL) return;

	float drawX = destX - CAMERA->GetX();
	float drawY = destY - CAMERA->GetY();

	if (drawX + _imageInfo->width < 0) return;
	if (drawY + _imageInfo->height< 0) return;
	if (drawX > WINSIZEX) return;
	if (drawY > WINSIZEY) return;

	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	D2D1_RECT_F dxArea1 = D2D1::RectF(drawX, drawY, drawX + _imageInfo->frameWidth, drawY + _imageInfo->frameHeight);
	D2D1_RECT_F dxArea2 = D2D1::RectF(
		_imageInfo->currentFrameX * _imageInfo->frameWidth,
		_imageInfo->currentFrameY * _imageInfo->frameHeight,
		_imageInfo->currentFrameX * _imageInfo->frameWidth +_imageInfo->frameWidth,
		_imageInfo->currentFrameY * _imageInfo->frameHeight+_imageInfo->frameHeight);
	D2DMANAGER->GetD2DRenderTarget()->DrawBitmap(_imageInfo->pBitmap, dxArea1, alpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, dxArea2);
}


void D2DImage::AniRender(float destX, float destY, Animation* ani,float alpha)
{
	Render(destX, destY, ani->GetFramePos().x, ani->GetFramePos().y, ani->GetFrameWidth(), ani->GetFrameHeight(),alpha);
}

void D2DImage::FlipAniRender(float destX, float destY, Animation* ani, float alpha)
{
	FlipRender(destX, destY, ani->GetFramePos().x, ani->GetFramePos().y,ani->GetFrameWidth(),ani->GetFrameHeight(), alpha);
}

void D2DImage::FlipRender(float destX, float destY, float alpha)
{
	if (_imageInfo->pBitmap == NULL) return;

	float drawX = destX - CAMERA->GetX();
	float drawY = destY - CAMERA->GetY();

	if (drawX + _imageInfo->width < 0) return;
	if (drawY + _imageInfo->height< 0) return;
	if (drawX > WINSIZEX) return;
	if (drawY > WINSIZEY) return;

	drawX = drawX * -1 - _imageInfo->width;		
	D2D1_RECT_F dxArea1 = D2D1::RectF(drawX, drawY, drawX + _imageInfo->width, drawY + _imageInfo->height);
	D2D1_RECT_F dxArea2 = D2D1::RectF(0, 0, _imageInfo->width, _imageInfo->height);

	D2D1::Matrix3x2F matrix;
	D2DMANAGER->GetD2DRenderTarget()->GetTransform(&matrix);
	matrix._11 = matrix._11 * -1;
	D2DMANAGER->GetD2DRenderTarget()->SetTransform(matrix);
	D2DMANAGER->GetD2DRenderTarget()->DrawBitmap(_imageInfo->pBitmap, dxArea1, alpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, dxArea2);
	matrix._11 = matrix._11 * -1;
	D2DMANAGER->GetD2DRenderTarget()->SetTransform(matrix);

}
void D2DImage::FlipRender(float destX, float destY, float width, float height, float alpha )
{
	if (_imageInfo->pBitmap == NULL) return;

	float drawX = destX - CAMERA->GetX();
	float drawY = destY - CAMERA->GetY();

	if (drawX + _imageInfo->width < 0) return;
	if (drawY + _imageInfo->height< 0) return;
	if (drawX > WINSIZEX) return;
	if (drawY > WINSIZEY) return;

	drawX = drawX * -1 - width;
	D2D1_RECT_F dxArea1 = D2D1::RectF(drawX, drawY, drawX + width, drawY + height);
	D2D1_RECT_F dxArea2 = D2D1::RectF(0, 0, _imageInfo->width, _imageInfo->height);

	D2D1::Matrix3x2F matrix;
	D2DMANAGER->GetD2DRenderTarget()->GetTransform(&matrix);
	matrix._11 = matrix._11 * -1;
	D2DMANAGER->GetD2DRenderTarget()->SetTransform(matrix);
	D2DMANAGER->GetD2DRenderTarget()->SetTransform(matrix);	D2DMANAGER->GetD2DRenderTarget()->DrawBitmap(_imageInfo->pBitmap, dxArea1, alpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, dxArea2);
	matrix._11 = matrix._11 * -1;
	D2DMANAGER->GetD2DRenderTarget()->SetTransform(matrix);										//변경했던 렌더타겟 매트릭스 초기화
}
void D2DImage::FlipRender(float destX, float destY, float sourX, float sourY, float sourWidth, float sourHeight, float alpha)
{
	if (_imageInfo->pBitmap == NULL) return;

	float drawX = destX - CAMERA->GetX();
	float drawY = destY - CAMERA->GetY();

	if (drawX + _imageInfo->width < 0) return;
	if (drawY + _imageInfo->height< 0) return;
	if (drawX > WINSIZEX) return;
	if (drawY > WINSIZEY) return;

	drawX = drawX * -1 - sourWidth;
	D2D1::Matrix3x2F matrix;
	D2DMANAGER->GetD2DRenderTarget()->GetTransform(&matrix);
	matrix._11 = matrix._11 * -1;
	D2DMANAGER->GetD2DRenderTarget()->SetTransform(matrix);

	D2D1_RECT_F dxArea1 = D2D1::RectF(drawX, drawY, drawX + sourWidth, drawY + sourHeight);
	D2D1_RECT_F dxArea2 = D2D1::RectF(sourX, sourY, sourX + sourWidth, sourY + sourHeight);
	D2DMANAGER->GetD2DRenderTarget()->DrawBitmap(_imageInfo->pBitmap, dxArea1, alpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, dxArea2);
	matrix._11 = matrix._11 * -1;
	D2DMANAGER->GetD2DRenderTarget()->SetTransform(matrix);

}

void D2DImage::FlipFrameRender(float destX, float destY, float alpha )
{

	if (_imageInfo->pBitmap == NULL) return;

	float drawX = destX - CAMERA->GetX();
	float drawY = destY - CAMERA->GetY();

	if (drawX + _imageInfo->width < 0) return;
	if (drawY + _imageInfo->height< 0) return;
	if (drawX > WINSIZEX) return;
	if (drawY > WINSIZEY) return;

	drawX = drawX * -1 - _imageInfo->frameWidth;

	D2D1_RECT_F dxArea1 = D2D1::RectF(drawX, drawY, drawX + _imageInfo->frameWidth, drawY + _imageInfo->frameHeight);
	D2D1_RECT_F dxArea2 = D2D1::RectF(
		_imageInfo->currentFrameX * _imageInfo->frameWidth,
		_imageInfo->currentFrameY * _imageInfo->frameHeight,
		_imageInfo->currentFrameX * _imageInfo->frameWidth + _imageInfo->frameWidth,
		_imageInfo->currentFrameY * _imageInfo->frameHeight + _imageInfo->frameHeight);

	D2D1::Matrix3x2F matrix;
	D2DMANAGER->GetD2DRenderTarget()->GetTransform(&matrix);
	matrix._11 = matrix._11 * -1;
	D2DMANAGER->GetD2DRenderTarget()->SetTransform(matrix);

	D2DMANAGER->GetD2DRenderTarget()->DrawBitmap(_imageInfo->pBitmap, dxArea1, alpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, dxArea2);
	
	matrix._11 = matrix._11 * -1;
	D2DMANAGER->GetD2DRenderTarget()->SetTransform(matrix);
}
void D2DImage::FlipFrameRender(float destX, float destY, int frameCount, float alpha )
{
	if (_imageInfo->pBitmap == NULL) return;

	float drawX = destX - CAMERA->GetX();
	float drawY = destY - CAMERA->GetY();

	if (drawX + _imageInfo->width < 0) return;
	if (drawY + _imageInfo->height< 0) return;
	if (drawX > WINSIZEX) return;
	if (drawY > WINSIZEY) return;

	drawX = drawX * -1 - _imageInfo->frameWidth;

	_imageInfo->currentFrameX = frameCount % (_imageInfo->maxFrameX + 1);
	_imageInfo->currentFrameY = frameCount / (_imageInfo->maxFrameX + 1);

	D2D1_RECT_F dxArea1 = D2D1::RectF(drawX, drawY, drawX + _imageInfo->frameWidth, drawY + _imageInfo->frameHeight);
	D2D1_RECT_F dxArea2 = D2D1::RectF(
		_imageInfo->currentFrameX * _imageInfo->frameWidth,
		_imageInfo->currentFrameY * _imageInfo->frameHeight,
		_imageInfo->currentFrameX * _imageInfo->frameWidth + _imageInfo->frameWidth,
		_imageInfo->currentFrameY * _imageInfo->frameHeight + _imageInfo->frameHeight);

	D2D1::Matrix3x2F matrix;
	D2DMANAGER->GetD2DRenderTarget()->GetTransform(&matrix);
	matrix._11 = matrix._11 * -1;
	D2DMANAGER->GetD2DRenderTarget()->SetTransform(matrix);

	D2DMANAGER->GetD2DRenderTarget()->DrawBitmap(_imageInfo->pBitmap, dxArea1, alpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, dxArea2);
	
	matrix._11 = matrix._11 * -1;
	D2DMANAGER->GetD2DRenderTarget()->SetTransform(matrix);
}
void D2DImage::FlipFrameRender(float destX, float destY, int currentFrameX, int currentFrameY, float alpha )
{
	if (_imageInfo->pBitmap == NULL) return;

	float drawX = destX - CAMERA->GetX();
	float drawY = destY - CAMERA->GetY();

	if (drawX + _imageInfo->width < 0) return;
	if (drawY + _imageInfo->height< 0) return;
	if (drawX > WINSIZEX) return;
	if (drawY > WINSIZEY) return;

	drawX = drawX * -1 - _imageInfo->frameWidth;

	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	D2D1_RECT_F dxArea1 = D2D1::RectF(drawX, drawY, drawX + _imageInfo->frameWidth, drawY + _imageInfo->frameHeight);
	D2D1_RECT_F dxArea2 = D2D1::RectF(
		_imageInfo->currentFrameX * _imageInfo->frameWidth,
		_imageInfo->currentFrameY * _imageInfo->frameHeight,
		_imageInfo->currentFrameX * _imageInfo->frameWidth + _imageInfo->frameWidth,
		_imageInfo->currentFrameY * _imageInfo->frameHeight + _imageInfo->frameHeight);


	D2D1::Matrix3x2F matrix;
	D2DMANAGER->GetD2DRenderTarget()->GetTransform(&matrix);
	matrix._11 = matrix._11 * -1;
	D2DMANAGER->GetD2DRenderTarget()->SetTransform(matrix);

	D2DMANAGER->GetD2DRenderTarget()->DrawBitmap(_imageInfo->pBitmap, dxArea1, alpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, dxArea2);
	matrix._11 = matrix._11 * -1;
	D2DMANAGER->GetD2DRenderTarget()->SetTransform(matrix);
}

void D2DImage::ReverseFrameRender(float destX, float destY, int frameCount, float alpha)
{
	if (_imageInfo->pBitmap == NULL) return;

	float drawX = destX - CAMERA->GetX();
	float drawY = destY - CAMERA->GetY();

	if (drawX + _imageInfo->width < 0) return;
	if (drawY + _imageInfo->height< 0) return;
	if (drawX > WINSIZEX) return;
	if (drawY > WINSIZEY) return;

	drawY = drawY * -1 - _imageInfo->frameHeight;

	_imageInfo->currentFrameX = frameCount % (_imageInfo->maxFrameX + 1);
	_imageInfo->currentFrameY = frameCount / (_imageInfo->maxFrameX + 1);

	D2D1_RECT_F dxArea1 = D2D1::RectF(drawX, drawY, drawX + _imageInfo->frameWidth, drawY + _imageInfo->frameHeight);
	D2D1_RECT_F dxArea2 = D2D1::RectF(
		_imageInfo->currentFrameX * _imageInfo->frameWidth,
		_imageInfo->currentFrameY * _imageInfo->frameHeight,
		_imageInfo->currentFrameX * _imageInfo->frameWidth + _imageInfo->frameWidth,
		_imageInfo->currentFrameY * _imageInfo->frameHeight + _imageInfo->frameHeight);

	D2D1::Matrix3x2F matrix;
	D2DMANAGER->GetD2DRenderTarget()->GetTransform(&matrix);
	matrix._22 = matrix._22 * -1;
	D2DMANAGER->GetD2DRenderTarget()->SetTransform(matrix);

	D2DMANAGER->GetD2DRenderTarget()->DrawBitmap(_imageInfo->pBitmap, dxArea1, alpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, dxArea2);

	matrix._22 = matrix._22 * -1;
	D2DMANAGER->GetD2DRenderTarget()->SetTransform(matrix);
}

void D2DImage::UIRender(float destX, float destY, float alpha)
{
	if (_imageInfo->pBitmap == NULL) return;

	D2D1_RECT_F dxArea1 = D2D1::RectF(destX, destY, destX + _imageInfo->width, destY + _imageInfo->height);
	D2D1_RECT_F dxArea2 = D2D1::RectF(0, 0, _imageInfo->width, _imageInfo->height);
	D2DMANAGER->GetD2DRenderTarget()->DrawBitmap(_imageInfo->pBitmap, dxArea1, alpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, dxArea2);

}

void D2DImage::UIFrameRender(float destX, float destY, int currentFrameX, int currentFrameY, float alpha)
{
	if (_imageInfo->pBitmap == NULL) return;

	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	D2D1_RECT_F dxArea1 = D2D1::RectF(destX, destY, destX+ _imageInfo->frameWidth, destY + _imageInfo->frameHeight);
	D2D1_RECT_F dxArea2 = D2D1::RectF(
		_imageInfo->currentFrameX * _imageInfo->frameWidth,
		_imageInfo->currentFrameY * _imageInfo->frameHeight,
		_imageInfo->currentFrameX * _imageInfo->frameWidth + _imageInfo->frameWidth,
		_imageInfo->currentFrameY * _imageInfo->frameHeight + _imageInfo->frameHeight);
	D2DMANAGER->GetD2DRenderTarget()->DrawBitmap(_imageInfo->pBitmap, dxArea1, alpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, dxArea2);

}