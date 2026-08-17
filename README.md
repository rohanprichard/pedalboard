# 29-Note MIDI Organ Pedalboard

A DIY 29-note MIDI pedalboard for organ software, built with two Arduino Leonardo boards and 3D-printed pedals. Each board appears as a native USB-MIDI device, so the pedalboard connects directly to a computer without custom drivers.

## Demo and build assets

- [Watch the build/demo on YouTube](https://www.youtube.com/watch?v=D_P4T568hAM)
- [Circuit diagram](assets/Pedalboard.png)
- [Schematic PDF](assets/Pedalboard-Schematic.pdf)

## What it does

- maps pedals from C0 to E2 to MIDI note messages
- splits the wiring across two Arduino Leonardo boards
- works with Hauptwerk, GrandOrgue, DAWs, and other USB-MIDI-capable software

## Hardware

| Part | Quantity |
| --- | ---: |
| Arduino Leonardo | 2 |
| Momentary push buttons | 29 |
| Jumper wires | 50+ |
| USB cables | 2 |
| Breadboard | Optional |
| 3D-printed pedal components | As required |

## Wiring

- **Board 1:** the first 14 notes, C0–F1; uses pins 2–13 and A0.
- **Board 2:** the remaining notes, F#1–E2; uses pins 2–12.
- Connect each switch between its assigned input and ground; the sketches use internal pull-up resistors.

Refer to the [schematic](assets/Pedalboard-Schematic.pdf) before powering the boards.

## Upload and use

1. Open `sketches/lower_pedalboard.ino` and `sketches/upper_pedalboard.ino` in the Arduino IDE.
2. Select the correct Arduino Leonardo board and upload each sketch.
3. Connect both boards over USB.
4. Open MIDI-capable software and select the two MIDI inputs.
5. Verify each pedal sends the intended note before performance use.

`sketches/teensy_pedalboard.ino` is an alternative implementation for compatible Teensy hardware.

## Troubleshooting

- Missing notes: verify the pin map and ground connection for that switch.
- No MIDI device: confirm the board supports native USB MIDI and try a data-capable USB cable.
- Duplicate notes: inspect the wiring and the use of `INPUT_PULLUP`.

## License

MIT
