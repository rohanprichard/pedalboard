#include <Arduino.h>
#include <usb_midi.h>

#define NUM_KEYS 29

// Example pin list — adjust based on your actual wiring
const int keyPins[NUM_KEYS] = {
    2, 3, 4, 5, 6, 7, 8, 9, 10, 11,
    12, 13, 14, 15, 16, 17, 18, 19, 20, 21,
    22, 23, 24, 25, 26, 27, 28, 29, 30
};

// MIDI notes from C0 (12) to E2 (40)
const int midiNotes[NUM_KEYS] = {
    12, 13, 14, 15, 16, 17, 18, 19, 20, 21,
    22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
    32, 33, 34, 35, 36, 37, 38, 39, 40
};

bool keyState[NUM_KEYS] = {false};

void setup() {
    for (int i = 0; i < NUM_KEYS; i++) {
        pinMode(keyPins[i], INPUT_PULLUP);
    }
}

void loop() {
    for (int i = 0; i < NUM_KEYS; i++) {
        bool currentState = digitalRead(keyPins[i]) == LOW;

        if (currentState && !keyState[i]) {
            usbMIDI.sendNoteOn(midiNotes[i], 127, 1);
            keyState[i] = true;
        } 
        else if (!currentState && keyState[i]) {
            usbMIDI.sendNoteOff(midiNotes[i], 0, 1);
            keyState[i] = false;
        }
    }

    usbMIDI.read(); // Always good practice
}
