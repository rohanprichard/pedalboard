#include "MIDIUSB.h"

// Upper Pedalboard  11 keys, F#1 to E2

#define NUM_KEYS 11
const int keyPins[NUM_KEYS] = {
    2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12
};

const int midiNotes[NUM_KEYS] = {
    42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52
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
