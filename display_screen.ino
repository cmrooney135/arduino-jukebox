#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED display dimensions
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// Create an instance of the SSD1306 display object
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  // Initialize the OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  // 0x3C is the I2C address of the OLED
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);  // Stop if initialization fails
  }

  // Clear the display buffer
  display.clearDisplay();

  // Set text size (1 is the smallest, 2 is a bit larger, 3 is larger)
  display.setTextSize(1);

  // Set text color (WHITE for visible text)
  display.setTextColor(SSD1306_WHITE);

  // Set the cursor position (x, y)
  display.setCursor(0, 0);

  // Print text to the display
  display.print(F("Title of Song"));
  display.setCursor(0, 20);
  display.print(F("Album"));
  display.setCursor(0, 40);
  display.print(F("Artist"));

  // Display the text on the OLED
  display.display();
}

void loop() {
  // Nothing to do here, text is displayed once
}
