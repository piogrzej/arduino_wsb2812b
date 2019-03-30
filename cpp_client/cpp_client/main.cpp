#include "serial.h"
#include "screen.h"

int main()
{
	char port_name[] = "COM4";

	Serial serial_port(port_name);
	if (!serial_port.isConnected()) return -1;

	Screen screen;

	char byteArray[4];

	while (true)
	{
		screen.capture();
		screen.getAvgColor(byteArray);

		//set color
		byteArray[0] = 254;
		//byteArray[1] = 0;
		//byteArray[2] = 128;
		//byteArray[3] = 64;

		serial_port.write(byteArray, 4);

		//aplay changes
		byteArray[0] = 255;
		byteArray[1] = 0;
		byteArray[2] = 0;
		byteArray[3] = 0;

		serial_port.write(byteArray, 4);

		Sleep(30);
	}

	return 0;
}