#include <Adafruit_NeoPixel.h>

#define NUM_LEDS 144
#define DATA_PIN 5
#define SWITCH_PIN 2
#define BRIGHTNESS 255

Adafruit_NeoPixel strip(NUM_LEDS, DATA_PIN, NEO_GRB + NEO_KHZ800);

bool switchState = HIGH;
bool lastSwitchState = HIGH;

int colorIndex = 0;

uint32_t colors[] = {
  strip.Color(255, 0, 0),      // Red
  strip.Color(0, 255, 0),      // Green
  strip.Color(0, 0, 255),      // Blue
  strip.Color(255, 255, 0),    // Yellow
  strip.Color(255, 0, 255),    // Magenta
  strip.Color(0, 255, 255),    // Cyan
  strip.Color(255, 255, 255),  // White
};

int numColors = sizeof(colors) / sizeof(colors[0]);

void setup() {
  strip.begin();
  strip.setBrightness(BRIGHTNESS);
  strip.show();

  pinMode(SWITCH_PIN, INPUT_PULLUP);
}

void loop() {
  switchState = digitalRead(SWITCH_PIN);

  if (switchState == LOW && lastSwitchState == HIGH) {
    colorIndex = (colorIndex + 1) % numColors;

    runningAnimation(colors[colorIndex]);
  }

  if (switchState == HIGH) {
    strip.clear();
    strip.show();
  }

  lastSwitchState = switchState;

  delay(50);
}

void runningAnimation(uint32_t color) {
  strip.clear();

  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, color);
    strip.show();
    delay(1);
  }
}
