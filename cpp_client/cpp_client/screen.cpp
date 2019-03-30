#include "screen.h"

Screen::Screen()
{
	HDC hScreen = GetDC(NULL);
	screenX = GetDeviceCaps(hScreen, HORZRES);
	screenY = GetDeviceCaps(hScreen, VERTRES);

	screenData = (BYTE*)malloc(4 * screenX * screenY);
}


Screen::~Screen()
{
	free(screenData);
}

void Screen::capture()
{
	HDC hScreen = GetDC(NULL);

	HDC hdcMem = CreateCompatibleDC(hScreen);
	HBITMAP hBitmap = CreateCompatibleBitmap(hScreen, screenX, screenY);
	HGDIOBJ hOld = SelectObject(hdcMem, hBitmap);
	BitBlt(hdcMem, 0, 0, screenX, screenY, hScreen, 0, 0, SRCCOPY);
	SelectObject(hdcMem, hOld);

	BITMAPINFOHEADER bmi = { 0 };
	bmi.biSize = sizeof(BITMAPINFOHEADER);
	bmi.biPlanes = 1;
	bmi.biBitCount = 32;
	bmi.biWidth = screenX;
	bmi.biHeight = -screenY;
	bmi.biCompression = BI_RGB;
	bmi.biSizeImage = 0;

	GetDIBits(hdcMem, hBitmap, 0, screenY, screenData, (BITMAPINFO*)&bmi, DIB_RGB_COLORS);

	ReleaseDC(GetDesktopWindow(), hScreen);
	DeleteDC(hdcMem);
	DeleteObject(hBitmap);
}

inline uint8_t Screen::pixB(int x, int y) const
{
	return screenData[4 * ((y*screenX) + x)];
}

inline uint8_t Screen::pixG(int x, int y) const
{
	return screenData[4 * ((y*screenX) + x) + 1];
}

inline uint8_t Screen::pixR(int x, int y) const
{
	return screenData[4 * ((y*screenX) + x) + 2];
}

void Screen::getAvgColor(char byteArray[4]) const
{
	uint8_t r, g, b;

	uint64_t r_sum = 0;
	uint64_t g_sum = 0;
	uint64_t b_sum = 0;

	uint64_t counter = 0;

	for (int x = 0; x < screenX; ++x)
		for (int y = 0; y < screenY; ++y)
		{
			r = pixR(x, y);
			g =	pixG(x, y);
			b = pixB(x, y);

			//skip black color
			if (r < 10 && g < 10 && b < 10) continue;
			//skip white color
			if (r > 240 && g > 240 && b > 240) continue;

			r_sum += r;
			g_sum += g;
			b_sum += b;

			counter++;
		}

	byteArray[1] = static_cast<char>(r_sum / (counter)) / 2;
	byteArray[2] = static_cast<char>(g_sum / (counter)) / 2;
	byteArray[3] = static_cast<char>(b_sum / (counter)) / 2;
}