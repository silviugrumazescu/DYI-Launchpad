#include <MIDIUSB.h>
#include "PitchToNote.h"
#include <Wire.h>
#include <Adafruit_MPR121.h>

#ifndef _BV
#define _BV(bit) (1 << (bit)) 
#endif
#define NUM_BUTTONS 12
#define NUM_POTS 6

uint16_t buttonState;
uint16_t prevButtonState;
uint16_t analogValues[6];
uint16_t prevAnalogValues[6];
byte analogPins[] = {A0, A1, A2, A3, A4, A5};

Adafruit_MPR121 cap = Adafruit_MPR121();

void setup() 
{
  Serial.begin(9600);
  if(!cap.begin(0x5A))
  {
    Serial.println("MPR121 not found.");
    while(1);
  }

  Serial.println("MPR121 found!");
 
}

void loop() 
{
  readData();
  sendMidi();
  resetValues();
}

void readData()
{

  buttonState = cap.touched();

  for(uint8_t i = 0; i < NUM_POTS; i++)
    analogValues[i] = analogRead(analogPins[i]);
  
}

void sendMidi()
{
  for(uint8_t i = 0; i < NUM_BUTTONS; i++)
  {
    if(bitRead(buttonState, i) && !bitRead(prevButtonState, i))
    {
      noteOn(i, pitchC4, 100);
      MidiUSB.flush();
      Serial.print(i);
      Serial.println(" pressed");
    }

    if(!bitRead(buttonState, i) && bitRead(prevButtonState, i))
    {
      noteOff(i, pitchC4, 0);
      MidiUSB.flush();
      Serial.print(i);
      Serial.println(" unpressed");
    }
    
  }

  for(uint8_t i = 0; i < NUM_POTS; i++)
  {
    if(abs(analogValues[i] - prevAnalogValues[i]) > 5)
      controlChange(0, i, analogValues[i]/8); 
  }
  MidiUSB.flush();
}

void resetValues()
{
  prevButtonState = buttonState;
  for(uint8_t i = 0; i < NUM_POTS; i++)
    if(abs(analogValues[i] - prevAnalogValues[i]) > 5)
      prevAnalogValues[i] = analogValues[i];  
}

void noteOn(byte channel, byte pitch, byte velocity) 
{
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity) 
{
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}

void controlChange(byte channel, byte control, byte value) 
{
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
}
