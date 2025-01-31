#include "MIDIUSB.h"

// Lower Pedalboard  20 keys, C0 to E2

#define NUM_KEYS 20 
const int keyPins[NUM_KEYS] = {
    2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 
    A0, A1, A2, A3, A4, A5
};

const int midiNotes[NUM_KEYS] = {
    24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 
    36, 37, 38, 39, 40, 41, 42, 43
};
// Modify the prev 3 statements to match the number of keys on your pedalboard

bool keyState[NUM_KEYS] = {false}; 

void noteOn(byte channel, byte pitch, byte velocity) {
    midiEventPacket_t noteOnPacket = {0x09, 0x90 | channel, pitch, velocity};
    MidiUSB.sendMIDI(noteOnPacket);
}

void noteOff(byte channel, byte pitch, byte velocity) {
    midiEventPacket_t noteOffPacket = {0x08, 0x80 | channel, pitch, velocity};
    MidiUSB.sendMIDI(noteOffPacket);
}

void setup() {
    for (int i = 0; i < NUM_KEYS; i++) {
        pinMode(keyPins[i], INPUT_PULLUP); // Disable if you are using external pull-up resistors
    }
}

void loop() {
    for (int i = 0; i < NUM_KEYS; i++) {
        bool currentState = digitalRead(keyPins[i]) == LOW; 
        
        if (currentState && !keyState[i]) {
            noteOn(0, midiNotes[i], 127);
            MidiUSB.flush();
            keyState[i] = true;
        } 
        else if (!currentState && keyState[i]) {
            noteOff(0, midiNotes[i], 127);
            MidiUSB.flush();
            keyState[i] = false;
        }
    }
}