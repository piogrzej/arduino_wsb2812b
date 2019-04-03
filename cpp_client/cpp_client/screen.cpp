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
	HDC hScreen = GetDC(GetDesktopWindow());

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

//not used, in current method of screen capture apha chanel is always 255
inline uint8_t Screen::pixA(int x, int y) const
{
	return screenData[4 * ((y*screenX) + x) + 3];
}

inline bool isWhiteOrBlack(uint8_t r, uint8_t g, uint8_t b)
{
	return ((b - 20) < r) && (r < (b + 20)) && ((g - 20) < r) && (r < (g + 20));
}

void Screen::getAvgColor(BYTE rgb[3]) const
{
	uint8_t r, g, b, a;

	uint64_t r_sum = 0;
	uint64_t g_sum = 0;
	uint64_t b_sum = 0;

	//counter is equal to 1 avoid division by 0 when whole screen is black or white
	uint64_t counter = 1;

#ifdef ULTRAWIDE_MODE
	for (int x = 320; x < screenX - 320; ++x)
#else
	for (int x = 0; x < screenX; ++x)
#endif
		for (int y = 0; y < screenY; ++y)
		{
			r = pixR(x,y);
			g = pixG(x,y);
			b = pixB(x,y);

			//skip black/white(ish) colors
			if (isWhiteOrBlack(r,g,b)) continue;

			r_sum += r;
			g_sum += g;
			b_sum += b;

			counter++;
		}

	rgb[0] = static_cast<BYTE>(r_sum / counter) / COLOR_RAREFACTION;
	rgb[1] = static_cast<BYTE>(g_sum / counter) / COLOR_RAREFACTION;
	rgb[2] = static_cast<BYTE>(b_sum / counter) / COLOR_RAREFACTION;
}
