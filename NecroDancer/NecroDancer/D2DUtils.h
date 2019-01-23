#pragma once
#pragma comment(lib, "d2d1")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "WindowsCodecs.lib")
#pragma comment(lib, "Comdlg32.lib")

#include<d2d1.h>
#include<d2d1helper.h>
#include<wincodec.h>
#include<dwrite.h>


HRESULT D2DInit(HWND hWnd, int width, int height, ID2D1Factory **factory, ID2D1HwndRenderTarget **Rt);
//HRESULT WICInit(IWICImagingFactory **factory);
HRESULT DWInit(IDWriteFactory **factory);