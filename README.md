# ARAP Robot Controller

Firmware for the ARAP differential-drive robot platform. Runs on an Arduino Mega 2560 and provides motor control, encoder feedback, GPS positioning, ultrasonic obstacle detection, and LED status indication. Communicates with the ROS navigation stack over serial UART at 57600 baud.

---

## Hardware

| Component | Model | Interface |
|---|---|---|
| Microcontroller | Arduino Mega 2560 | USB Serial |
| Motor Drivers (x2) | BTS7960 H-Bridge | PWM + Digital |
| Drive Motors (x2) | goBILDA 12V DC with built-in encoder | Via BTS7960 |
| GPS Module | u-blox NEO-M9N | I2C |
| Ultrasonic Sensors (x2) | A0221AU | UART 9600 baud |
| LED Strip | WS2812B (16 LEDs) | Single-wire data |

---

## Pin Assignments

### Motors (BTS7960)

| Function | Left Motor | Right Motor |
|---|---|---|
| RPWM | 7 | 11 |
| LPWM | 6 | 10 |
| R_EN | 22 | 24 |
| L_EN | 23 | 25 |

Power the BTS7960 motor input from a 12V supply. Do not power the motor side from the Arduino.

### Encoders (Built-in Hall Effect, Quadrature A+B)

| Channel | Left Motor | Right Motor |
|---|---|---|
| A | Pin 2 (INT0) | Pin 18 (INT5) |
| B | Pin 3 (INT1) | Pin 19 (INT4) |
| VCC | 5V | 5V |
| GND | GND | GND |

These are the encoders built into the goBILDA motors. Connect the encoder header wires to the pins above. Refer to the goBILDA motor datasheet for the encoder connector pinout on your specific model.

### GPS (NEO-M9N)

| GPS Pin | Mega Pin |
|---|---|
| SDA | 20 |
| SCL | 21 |
| VCC | 3.3V or 5V |
| GND | GND |

### Ultrasonic Sensors (A0221AU)

Wire colors:

| Color | Function |
|---|---|
| Red | VCC — connect to 5V |
| Black | GND — connect to GND |
| Yellow | TX (data out) — connect to Arduino RX pin |
| White | RX — leave unconnected |

Sensor connections:

| Sensor | Yellow wire to |
|---|---|
| Left | Pin 17 (RX2) |
| Right | Pin 15 (RX3) |

### LED Strip (WS2812B)

| Wire | Mega Pin |
|---|---|
| Data | 12 |
| VCC | 5V |
| GND | GND |

Add a 330Ω resistor on the data line and a 470µF capacitor across VCC/GND at the strip.

---

## Dependencies

Install both libraries before compiling.

| Library | Install via Library Manager |
|---|---|
| FastLED | Search "FastLED" by Daniel Garcia |
| SparkFun u-blox GNSS Arduino Library | Search "SparkFun u-blox GNSS" |

### Arduino IDE

Sketch → Include Library → Manage Libraries → search and install each library listed above.

### PlatformIO

```ini
[env:megaatmega2560]
platform = atmelavr
board = megaatmega2560
framework = arduino
monitor_speed = 57600
lib_deps =
    fastled/FastLED@^3.6.0
    sparkfun/SparkFun u-blox GNSS Arduino Library@^2.2.0
```

---

## Project Structure

All files go in a folder named `Arap`:

```
Arap/
├── Arap.ino          Main sketch
├── motorParams.h     Pin config and tuning parameters
├── commands.h        Command definitions and enums
├── led.h             LED function declarations
└── led.cpp           LED animation implementations
```

---

## Upload

1. Connect the Arduino Mega via USB.
2. Open `Arap.ino` in Arduino IDE.
3. Board: **Arduino Mega or Mega 2560**
4. Select the correct port.
5. Click Upload.
6. Open Serial Monitor at **57600 baud**.
7. Confirm startup message: `=== ARAP Ready ===`

---

## Serial Commands

All commands are single-character followed by optional parameters, terminated by newline.

### Motor

| Command | Description |
|---|---|
| `m L R` | Set motor speeds, -255 to 255 |
| `k` | Emergency stop |
| `b` | Active brake |

### Sensors (ROS Integration)

| Command | Response format |
|---|---|
| `e` | `e <left_ticks> <right_ticks>` |
| `r` | Resets encoder counts to zero |
| `g` | `g <lat> <lon> <alt> <fix> <sats> <hAcc>` |
| `u` | `u <left_mm> <right_mm>` |

### LED

| Command | Description |
|---|---|
| `l N` | Set LED mode (0–12) |
| `c R G B` | Set custom color |
| `d N` | Set brightness (0–255) |

### System

| Command | Description |
|---|---|
| `s` | Full status dump |
| `p` | Ping (returns PONG) |
| `h` | Help |

### Examples

```
m 100 100       Slow forward
m 200 200       Medium forward
m -150 -150     Reverse
m -150 150      Spin left
m 150 -150      Spin right
k               Stop
```

---

## LED Behavior

| State | Effect |
|---|---|
| Idle | Blue breathing pulse |
| Moving | Rainbow cycle |
| Braking | Color pulse |
| Error | Solid white |

---

## Configuration

Key parameters in `motorParams.h`:

| Parameter | Default | Notes |
|---|---|---|
| `INVERT_LEFT_MOTOR` | true | Flip if left motor runs backwards |
| `INVERT_RIGHT_MOTOR` | true | Flip if right motor runs backwards |
| `MOTOR_DEADBAND` | 35 | Minimum PWM to start rotation. Increase if motors stall at low speed |
| `ACCEL_RATE` | 8 | PWM units per update cycle. Decrease for smoother ramp-up |
| `DECEL_RATE` | 15 | PWM units per update cycle for slowing down |
| `NUM_LEDS` | 16 | Adjust to match your LED strip |
| `SERIAL_BAUD` | 57600 | Must match ROS serial node and Serial Monitor |

---

## Troubleshooting

**Motors do not spin** — Check 12V supply to BTS7960. Verify R_EN and L_EN wiring. Try increasing `MOTOR_DEADBAND`.

**Wrong direction** — Toggle `INVERT_LEFT_MOTOR` or `INVERT_RIGHT_MOTOR` in `motorParams.h`, or swap M+/M- at the driver.

**GPS not found** — Check SDA/SCL wiring. The system continues without GPS if the module is absent.

**Ultrasonic returns -1** — Verify yellow wire on correct RX pin (17 left, 15 right). Ensure 5V power. Min range is 30mm.

**LEDs not working** — Confirm data pin 12, 5V power, GND, and that FastLED is installed.

**Garbled serial output** — Set baud to 57600.
