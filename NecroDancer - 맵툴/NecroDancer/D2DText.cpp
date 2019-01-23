#include "stdafx.h"
#include "D2DText.h"


D2DText::D2DText()
{
}


D2DText::~D2DText()
{
}


HRESULT D2DText::Init(LPCWSTR fontName, float size, D2D1::ColorF color)
{
	HRESULT hr;

	hr = D2DMANAGER->GetD2DWFactory()->CreateTextFormat(
		fontName,						//폰트 이름
		0,								//폰트 컬렉션
		DWRITE_FONT_WEIGHT_NORMAL,		//폰트의 굵기
		DWRITE_FONT_STYLE_NORMAL,		//스타일 NOMAL,ITALIC, OBLIQUE
		DWRITE_FONT_STRETCH_NORMAL,		//
		size,							//크기
		L"ko",							//한국어 en-us ko-kr ja-jp
		&_textFormat
		);

	if (FAILED(hr))
		return hr;

	D2DMANAGER->GetD2DRenderTarget()->CreateSolidColorBrush(color, &_brush);


	return S_OK;
}

void D2DText::Render(float messageBoxX, float messageBoxY,float messageBoxWidth, float messageBoxHeight, LPCWSTR string)
{

	D2DMANAGER->GetD2DRenderTarget()->DrawTextA(
		string,
		wcslen(string),
		_textFormat,
		D2D1::RectF(
		messageBoxX,
		messageBoxY,
		messageBoxWidth,
		messageBoxHeight),
		_brush
		);
}