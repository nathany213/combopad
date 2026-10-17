#include <arduino.h>
#include <keyboard.h>

const byte rows = 3;
const byte cols = 3;

byte rowPins[rows] = {D9, D8, D7};
byte colPins[cols] = {D3, D10, D6};

char keys[rows][cols] = {
  {'1', '4', '7'},
  {'2', '5', '8'},
  {'3', '6', '9'}
};

void setup() {
    Serial.begin(9600);
    for (int i = 0; i < rows; i++) {
        //define the counter, 
        //conditions,
        //and then how the counter changes each iteration

        pinMode(rowPins[i], OUTPUT);
        digitalWrite(rowPins[i], HIGH);
        //set row pins high by default, only low when active
    }

    for (int i = 0; i < cols; i++) {
        pinMode(colPins[i], INPUT_PULLUP);
        //inputpullup better than input here
        //because it stops random interference affecting readings
    }
}

void loop() {
    for (int a = 0; a < rows; a++) {
        digitalWrite(rowPins[a], LOW); //start scanning this row

        for (int b = 0; b < cols; b++) {
            if (digitalRead(colPins[b]) == LOW) {
                //key at coords: row a, col b
                Keyboard.press(keys[a][b]);
                delay(50);
                Keyboard.releaseAll();
            }
        }

        digitalWrite(rowPins[a], HIGH);
    }
}