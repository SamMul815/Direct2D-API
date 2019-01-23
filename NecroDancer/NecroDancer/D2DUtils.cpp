#include "stdafx.h"
#include "D2DUtils.h"


HRESULT D2DInit(HWND hWnd, int width, int height, ID2D1Factory **factory, ID2D1HwndRenderTarget **Rt)
{
	HRESULT hr;
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, factory);		//팩토리 생성 싱글쓰레드, 

	if (FAILED(hr))
		return hr;
	//(*factory)->CreateWicBitmapRenderTarget
	return (*factory)->CreateHwndRenderTarget(
					D2D1::RenderTargetProperties(),										//렌더타겟의 정보
					D2D1::HwndRenderTargetProperties(hWnd, D2D1::SizeU(width, height)), //윈도우 렌더타겟의 정보, 윈도우 크기나 핸들등의 값이 들어간다.
					Rt);																//결과를 저장할 포인터
}

HRESULT WICInit(IWICImagingFactory **factory)
{
	CoInitialize(0);			//COM 초기화		정확히는 잘...
	
	return CoCreateInstance(	//넘어가자 ㅠ
		CLSID_WICImagingFactory,
		0, CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(factory)
		);
}

HRESULT DWInit(IDWriteFactory **factory)
{
	HRESULT hr;

	hr = DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(*factory),
		(IUnknown**)factory
		);

	if (FAILED(hr))
		return hr;

	return S_OK;
}