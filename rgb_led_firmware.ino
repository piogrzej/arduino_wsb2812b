#include <NeoPixelBus.h>

#define SERIAL_RX_BUFFER_SIZE 512 // incrase size of serial buffer

const uint16_t LED_COUNT = 60;
const uint8_t LED_PIN = 13;  // make sure to set this to the correct pin
const uint8_t RAZER_GREEN_COLOR_SATURATION = 128;

NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(LED_COUNT, LED_PIN);
RgbColor razerGreen(0, RAZER_GREEN_COLOR_SATURATION, 0);

// LRGB - led, red, green, blue
// led means index of led,
// led can store special values:
//    255 - show changes,
//    254 - set R,G,B color to all leds
uint8_t     LRGB[4];
uint16_t    counter=0;

void setup()
{
    Serial.begin(115200);
    while (!Serial); // wait for serial attach

    // this resets all the neopixels to an off state
    strip.Begin();
    strip.Show();

    for(int i=0; i<LED_COUNT; ++i)
    {
        strip.SetPixelColor(i, razerGreen);   
    }
    strip.Show();
}

void setAllLedsToColor(const uint8_t R, const uint8_t G, const uint8_t B)
{
  RgbColor color(R,G,B);

  for(uint8_t i = 0; i < LED_COUNT; ++i)
  {
    strip.SetPixelColor(i, color);
  }
}

void loop()
{
  if (Serial.available() > 0)
  {
    
    LRGB[counter] = Serial.read();

    counter++;

    if(counter>3)
    {
        counter=0;

        switch(LRGB[0]) {
          case 255://show changes
            strip.Show();
            break;
          case 254://set all leds to one color
            setAllLedsToColor(LRGB[1],LRGB[2],LRGB[3]);
            break;
          default:
            RgbColor color(LRGB[1],LRGB[2],LRGB[3]);
            strip.SetPixelColor(LRGB[0], color);
        }

    }

  }
}
