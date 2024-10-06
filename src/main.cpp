#include <FastLED.h>

#define LED_PIN 6        // Define the GPIO pin where the data line is connected
#define NUM_LEDS 60      // Number of LEDs in the strip
#define BRIGHTNESS 100   // Brightness level (0-255)
#define LED_TYPE WS2812B // Type of LED strip
#define COLOR_ORDER GRB  // Color order for WS2812B

CRGB leds[NUM_LEDS];
String msg;
int currentAnimation = 0; // Variable to store the selected animation

// Animation 1: Rainbow
void rainbowAnimation()
{
  for (int hue = 0; hue < 255; hue++)
  {
    for (int i = 0; i < NUM_LEDS; i++)
    {
      leds[i] = CHSV((hue + (i * 10)) % 255, 255, 255); // Set each LED to a different color
    }
    FastLED.show(); // Update the strip with new colors
    delay(50);
  }
}

// Animation 2: Blink
void blinkAnimation()
{
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CRGB::Red; // Set all LEDs to red
  }
  FastLED.show();                          // Turn LEDs on
  delay(500);                              // Wait
  fill_solid(leds, NUM_LEDS, CRGB::Black); // Turn LEDs off
  FastLED.show();                          // Update strip
  delay(500);                              // Wait
}

// Animation 3: Theater Chase
void theaterChaseAnimation()
{
  for (int cycle = 0; cycle < 10; cycle++)
  {
    for (int offset = 0; offset < 3; offset++)
    {
      for (int i = 0; i < NUM_LEDS; i++)
      {
        if ((i + offset) % 3 == 0)
        {
          leds[i] = CRGB::Blue; // Blue LEDs chase
        }
        else
        {
          leds[i] = CRGB::Black; // Turn others off
        }
      }
      FastLED.show(); // Update the strip
      delay(100);     // Short delay between updates
    }
  }
}

void setup()
{
  // Initialize the serial communication
  Serial.begin(9600); // Use 9600 baud rate for Arduino Uno

  // Initialize the FastLED library
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);

  // Set all LEDs to off initially
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  FastLED.show();

  // Print "begin" after setup
  Serial.println("begin");
  Serial.println("Enter 1 for Rainbow, 2 for Blink, 3 for Theater Chase:");
}

void loop()
{
  // Check if there's any serial input
  if (Serial.available())
  {
    msg = Serial.readStringUntil('\n');
    msg.trim(); // Remove any extra spaces or line endings
    int option = msg.toInt();

    // Store the animation option
    if (option >= 1 && option <= 3)
    {
      currentAnimation = option;
      Serial.println("Animation Selected: " + String(option));
    }
    else
    {
      Serial.println("Invalid input. Please enter 1, 2, or 3.");
    }
  }

  // Run the selected animation based on the stored option
  switch (currentAnimation)
  {
  case 1:
    rainbowAnimation();
    break;
  case 2:
    blinkAnimation();
    break;
  case 3:
    theaterChaseAnimation();
    break;
  default:
    // No valid animation selected, do nothing
    break;
  }
}
