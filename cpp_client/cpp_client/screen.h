#ifndef SCREEN_H
#define SCREEN_H

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

class Screen
{
private:
	int screenX = 0;
	int screenY = 0;
	BYTE* screenData = 0;

	inline uint8_t pixR(int x, int y) const;
	inline uint8_t pixG(int x, int y) const;
	inline uint8_t pixB(int x, int y) const;
public:
	Screen();
	~Screen();
	void capture();
	void getAvgColor(char byteArray[4]) const;
};

#endif

