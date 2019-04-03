#include "serial.h"
#include "screen.h"

#define NEW_CAPTURE_DELAY 30//ms
#define SET_SINGLE_COLOR_TO_ALL_LEDS 254
#define APPLY_LED_CHANGES 255

int main()
{
	char port_name[] = "COM4";

	Serial serial_port(port_name);
	if (!serial_port.isConnected()) return -1;

	Screen screen;

	BYTE byteArray[4];

	printf("Program started, close this window to exit.\n");

	while (true)
	{
		screen.capture();

		//set color
		byteArray[0] = SET_SINGLE_COLOR_TO_ALL_LEDS;
		screen.getAvgColor(byteArray+sizeof(BYTE));
		serial_port.write(byteArray, 4);

		//apply changes
		byteArray[0] = APPLY_LED_CHANGES;
		byteArray[1] = 0;
		byteArray[2] = 0;
		byteArray[3] = 0;

		serial_port.write(byteArray, 4);

		Sleep(NEW_CAPTURE_DELAY);
	}

	return 0;
}