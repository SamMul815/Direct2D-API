#pragma once
class D2DText
{
private:
	IDWriteTextFormat		*_textFormat;	//�ؽ�Ʈ����
	ID2D1SolidColorBrush	*_brush;		//����
public:
	HRESULT Init(LPCWSTR fontName, float size, D2D1::ColorF color);
	void Render(float messageBoxX, float messageBoxY, float messageBoxWidth, float messageBoxHeight, LPCWSTR string);

	D2DText();
	~D2DText();
};

