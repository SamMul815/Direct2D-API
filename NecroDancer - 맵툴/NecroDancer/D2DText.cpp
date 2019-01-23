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
		fontName,						//��Ʈ �̸�
		0,								//��Ʈ �÷���
		DWRITE_FONT_WEIGHT_NORMAL,		//��Ʈ�� ����
		DWRITE_FONT_STYLE_NORMAL,		//��Ÿ�� NOMAL,ITALIC, OBLIQUE
		DWRITE_FONT_STRETCH_NORMAL,		//
		size,							//ũ��
		L"ko",							//�ѱ��� en-us ko-kr ja-jp
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