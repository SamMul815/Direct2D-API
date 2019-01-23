#pragma once
class D2DText
{
private:
	IDWriteTextFormat		*_textFormat;	//텍스트설정
	ID2D1SolidColorBrush	*_brush;		//생상
public:
	HRESULT Init(LPCWSTR fontName, float size, D2D1::ColorF color);
	void Render(float messageBoxX, float messageBoxY, float messageBoxWidth, float messageBoxHeight, LPCWSTR string);

	D2DText();
	~D2DText();
};

