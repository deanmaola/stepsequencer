#include <MIDI.h>

int photoPin = 0;
int ledPin = 34;
int mappedPhotoPin = 0;
int brightValue = 860;
int darkValue = 20;
int brightVal = 0;
int lastBrightVal = 0;
int lightState = 0;
int midBright = 0;
int buttonPin = 32;
int buttonState = 0;
int lastButtonState = 0;
int extraPin = 22;
int extraPin2 = 23;
int superPin = 24;





void setup() {

  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  pinMode(extraPin, OUTPUT);
  pinMode(extraPin2, OUTPUT);

}

void loop() {
  Serial.begin(9600);
  delay(10);
  calibrateButton();
  checkLight();
  Serial.println(midBright);
  while (usbMIDI.read()) {}
}

void checkLight() {
  lastBrightVal = lightState;
  lightState = analogRead(A14);
  if (lightState < midBright && lastBrightVal > midBright) {
    usbMIDI.sendNoteOn(60, 127, 1);
    digitalWrite(ledPin, HIGH);
    delay(100);
  }
  if (lightState > midBright && lastBrightVal < midBright); {
    usbMIDI.sendNoteOff(60, 0, 1);
    digitalWrite(ledPin, LOW);
  }
}

void calibrateButton() {
  lastButtonState = buttonState;
  buttonState = digitalRead(buttonPin);
  if (lastButtonState == LOW && buttonState == HIGH) {
    midBright = analogRead(A14);

  }

}


//while (usbMIDI.read()) {}

//usbMIDI.sendNoteOn(midiNote[i], 127, 1);
//860
