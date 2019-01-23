#pragma once
class D2DManager : public SingletonBase<D2DManager>
{
private:
	ID2D1Factory			*_factory;					//이미지 공장
	IDWriteFactory			*_wFactory;					//텍스트 공장
	ID2D1HwndRenderTarget	*_Rt;						//타겟 설정

public:
	HRESULT Init();
	void Release();
	void BeginDraw();
	void EndDraw();

	ID2D1Factory* GetD2DFactory() { return _factory; }
	IDWriteFactory* GetD2DWFactory() { return _wFactory; }
	ID2D1HwndRenderTarget* GetD2DRenderTarget() { return _Rt; }
	
	void DrawRectangle(ID2D1SolidColorBrush* brush, RECT *rc,float strokeWidth = 1.0f);
	ID2D1SolidColorBrush* MakeBrush(D2D1::ColorF color);

	D2DManager();
	~D2DManager();
};

