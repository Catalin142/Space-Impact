#pragma once
#include <wincodec.h>

#include "BMPLoader.h"
#include "../GraphicsContext.h"

#include <cassert>

#pragma comment(lib, "windowscodecs.lib")

#include "Macros.h"

ID2D1Bitmap* BMPLoader::Load(const wchar_t* filepath)
{
	IWICBitmapDecoder* Decoder = nullptr;
	IWICBitmapFrameDecode* Source = nullptr;
	IWICFormatConverter* Converter = nullptr;
	IWICImagingFactory* wicFactory = nullptr;
	ID2D1Bitmap* BitMap = nullptr;


	HRESULT hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, (LPVOID*)&wicFactory);

	if (SUCCEEDED(hr))
		hr = wicFactory->CreateDecoderFromFilename(filepath, NULL, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &Decoder);

	if (SUCCEEDED(hr))
	{
		hr = Decoder->GetFrame(0, &Source);
	}

	if (SUCCEEDED(hr))
	{
		hr = wicFactory->CreateFormatConverter(&Converter);
	}

	if (SUCCEEDED(hr))
	{
		hr = Converter->Initialize(Source, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0.0f, WICBitmapPaletteTypeMedianCut);
	}

	if (SUCCEEDED(hr))
	{
		hr = GraphicsContext::Get()->getRenderTarget()->CreateBitmapFromWicBitmap(Converter, NULL, &BitMap);
	}

	SAFE_RELEASE(wicFactory);
	SAFE_RELEASE(Decoder);
	SAFE_RELEASE(Converter);
	SAFE_RELEASE(Source);

	return BitMap;
}
