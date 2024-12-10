#include <avr/pgmspace.h> // Required for PROGMEM
#include "music_data.h"   // Include the header file
#include "TMRpcm.h"
#include "SPI.h"
#include <Arduino.h>
#include <RotaryEncoder.h>
TMRpcm tmrpcm;

#define PIN_IN1 A2
#define PIN_IN2 A3
#define BUTTON_PIN 7

RotaryEncoder encoder(PIN_IN1, PIN_IN2, RotaryEncoder::LatchMode::TWO03);


 
// Helper function to read a string from PROGMEM
void getStringFromProgmem(const char* progmemStr, char* buffer, size_t bufferSize) {
    strncpy_P(buffer, progmemStr, bufferSize);
    buffer[bufferSize - 1] = '\0'; // Null-terminate the string
}
 
// Helper function to print song information
String getFileName(uint8_t songIndex) {
    Song song;
    memcpy_P(&song, &musicLibrary[songIndex], sizeof(Song));
 
    // Buffers to hold strings
    char nameBuffer[50];
    char albumBuffer[50];
    char artistBuffer[50];
 
    // Retrieve strings from PROGMEM
    getStringFromProgmem(song.name, nameBuffer, sizeof(nameBuffer));
    getStringFromProgmem(song.album, albumBuffer, sizeof(albumBuffer));
    getStringFromProgmem(song.artist, artistBuffer, sizeof(artistBuffer));
    String songDetails = String(nameBuffer) + "--" + String(albumBuffer) + "--" + String(artistBuffer) + "--" + String(song.year) + ".wav";

    return songDetails;
}
void playMusic(String fileName)
{
  if(!tmrpcm.isPlaying())
  {
    tmrpcm.play(fileName.c_str());
  }
}

void setup() {
    Serial.begin(9600); // Initialize serial communication
    Serial.println("Hello");
    //tmrpcm.speakerPin=9;
    //tmrpcm.setVolume(4);
    pinMode(BUTTON_PIN, INPUT_PULLUP); // Use internal pull-up resistor

}
 
void loop() {
  if(!tmrpcm.isPlaying()){
  static int pos = 0;
  static bool lastButtonState = HIGH; // Initial button state (not pressed)

  encoder.tick();

  // Read and process rotary encoder position
  int newPos = encoder.getPosition();
  if (newPos > 80) {
    newPos = 80;
  }
  if (newPos < 0) {
    newPos = 0;
  }

  // Adjust position to make it even if necessary
  if (newPos % 2 != 0) {
    newPos++;
  }
  if (pos != newPos) {
    // Calculate the index as position divided by 2
    int index = newPos / 2;

    // Print the index
    Serial.print("index: ");
    Serial.println(index);
    //add the code to print the stuff about the song here 
    String songDetails = getFileName(index);

    int firstDelimiter = songDetails.indexOf("--");
    int secondDelimiter = songDetails.indexOf("--", firstDelimiter + 2);
    int thirdDelimiter = songDetails.indexOf("--", secondDelimiter + 2);

    String name = songDetails.substring(0, firstDelimiter); // Song name
    String album = songDetails.substring(firstDelimiter + 2, secondDelimiter); // Album name
    String artist = songDetails.substring(secondDelimiter + 2, thirdDelimiter); // Artist name
    String yearWithExtension = songDetails.substring(thirdDelimiter + 2); // Year with file extension (e.g., "2024.wav")

    // To remove the file extension (".wav") from the year part
    int fileExtensionIndex = yearWithExtension.indexOf(".wav");
    String year = yearWithExtension.substring(0, fileExtensionIndex);
    Serial.println("Song: " + name);
    Serial.println("Album: " + album);
    Serial.println("Artist: " + artist);
    Serial.println("Year: " + year);
    
    pos = newPos;
  }
  bool currentButtonState = digitalRead(BUTTON_PIN);
  if (lastButtonState == HIGH && currentButtonState == LOW) { // Button press detected
    String fileName = getFileName(pos/2);
    playMusic(fileName);
    Serial.print("Button pressed at position!!!: ");
    Serial.println(pos / 2); // Print the position when the button was pressed
    Serial.println("Playing song : " + fileName);
    delay(50); // Debounce delay

  }
  lastButtonState = currentButtonState;

  }

}
