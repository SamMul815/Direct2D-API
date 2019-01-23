#include "stdafx.h"
#include "D2DUtils.h"


HRESULT D2DInit(HWND hWnd, int width, int height, ID2D1Factory **factory, ID2D1HwndRenderTarget **Rt)
{
	HRESULT hr;
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, factory);		//���丮 ���� �̱۾�����, 

	if (FAILED(hr))
		return hr;
	//(*factory)->CreateWicBitmapRenderTarget
	return (*factory)->CreateHwndRenderTarget(
					D2D1::RenderTargetProperties(),										//����Ÿ���� ����
					D2D1::HwndRenderTargetProperties(hWnd, D2D1::SizeU(width, height)), //������ ����Ÿ���� ����, ������ ũ�⳪ �ڵ���� ���� ����.
					Rt);																//����� ������ ������
}

HRESULT WICInit(IWICImagingFactory **factory)
{
	CoInitialize(0);			//COM �ʱ�ȭ		��Ȯ���� ��...
	
	return CoCreateInstance(	//�Ѿ�� ��
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