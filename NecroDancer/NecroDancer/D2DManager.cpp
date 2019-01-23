#include "stdafx.h"
#include "D2DManager.h"


D2DManager::D2DManager()
	:_factory(nullptr),	
	 _wFactory (nullptr),
	 _Rt(nullptr)		
{

}


D2DManager::~D2DManager()
{

}

HRESULT D2DManager::Init()
{
	HRESULT hr;

	//蒲配府 积己
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &_factory);	
	if (FAILED(hr)) return hr;

	//坊歹 鸥百 积己
	hr = _factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(_hWnd, D2D1::SizeU(WINSIZEX, WINSIZEY)),
		&_Rt);
	if (FAILED(hr)) return hr;
	//咆胶飘 蒲配府 积己
	hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(_wFactory),
		reinterpret_cast<IUnknown **>(&_wFactory));
	if (FAILED(hr)) return hr;

	CoInitialize(NULL);

	return S_OK;
}
void D2DManager::Release()
{

}
void D2DManager::BeginDraw()
{
	_Rt->BeginDraw();
	_Rt->Clear(D2D1::ColorF(0, 0, 0));
}
void D2DManager::EndDraw()
{
	_Rt->EndDraw();
}

ID2D1SolidColorBrush*D2DManager:: MakeBrush(D2D1::ColorF color)
{
	HRESULT hr;
	ID2D1SolidColorBrush* brush;
	brush = nullptr;

	hr = _Rt->CreateSolidColorBrush(color, &brush);

	return brush;
}

void D2DManager::DrawRectangle(ID2D1SolidColorBrush* brush,RECT *rc, float strokeWidth)
{
	_Rt->DrawRectangle(D2D1::RectF(rc->left, rc->top, rc->right, rc->bottom), brush,strokeWidth);
}
