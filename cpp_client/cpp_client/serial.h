// based on "Serial Communication with an Arduino using C++ on Windows"
// by Manash Kumar Mandal
#ifndef SERIAL_H
#define SERIAL_H

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define SERIAL_TIMEOUT 2000

class Serial
{
private:
	HANDLE handler;
	bool connected;
	COMSTAT status;
	DWORD errors;
public:
	Serial(char* port_name);
	~Serial();
	int read(BYTE* buffer, uint32_t buf_size);
	bool write(BYTE* buffer, uint32_t buf_size);
	bool isConnected();
};

#endif