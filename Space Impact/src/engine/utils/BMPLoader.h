#pragma once

#include <d2d1.h>
#pragma comment(lib, "d2d1")

class BMPLoader
{
public:
	static ID2D1Bitmap* Load(const wchar_t* filepath);

private:
	BMPLoader() = default;
	~BMPLoader() = default;
};