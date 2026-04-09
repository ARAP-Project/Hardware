#ifndef MOTOR_PARAMS_H
#define MOTOR_PARAMS_H

#include <Arduino.h>

// =============================================================================
//                          MOTOR PIN CONFIGURATION
// =============================================================================

// LEFT MOTOR - BTS7960 Driver
constexpr uint8_t RPWM_L = 7;
constexpr uint8_t LPWM_L = 6;
constexpr uint8_t REN_L  = 22;
constexpr uint8_t LEN_L  = 23;

// RIGHT MOTOR - BTS7960 Driver
constexpr uint8_t RPWM_R = 11;
constexpr uint8_t LPWM_R = 10;
constexpr uint8_t REN_R  = 24;
constexpr uint8_t LEN_R  = 25;

// =============================================================================
//                       ENCODER PIN CONFIGURATION
//              Interrupt-capable pins on Arduino Mega 2560
// =============================================================================

// LEFT ENCODER
constexpr uint8_t ENC_L_A = 2;   // INT0
constexpr uint8_t ENC_L_B = 3;   // INT1

// RIGHT ENCODER
constexpr uint8_t ENC_R_A = 18;  // INT5
constexpr uint8_t ENC_R_B = 19;  // INT4

// =============================================================================
//                          MOTOR BEHAVIOR SETTINGS
// =============================================================================

// Direction inversion (set true if motor spins opposite to expected)
constexpr bool INVERT_LEFT_MOTOR  = true;
constexpr bool INVERT_RIGHT_MOTOR = true;

// PWM limits
constexpr int16_t PWM_MAX = 255;
constexpr int16_t PWM_MIN = -255;

// Minimum PWM to overcome motor stiction (wiper motors need higher value)
constexpr uint8_t MOTOR_DEADBAND = 35;

// Acceleration rate (PWM units per update)
constexpr uint8_t ACCEL_RATE = 8;

// Deceleration rate (faster than accel for safety)
constexpr uint8_t DECEL_RATE = 15;

// Motor update interval (milliseconds)
constexpr uint8_t MOTOR_UPDATE_MS = 25;

// =============================================================================
//                      ULTRASONIC SENSOR CONFIGURATION
//               A0221AU / A02YYUW via UART (9600 baud)
// =============================================================================

// Left sensor on Serial2 (RX2 = pin 17)
// Right sensor on Serial3 (RX3 = pin 15)
constexpr uint32_t ULTRA_BAUD = 9600;

// =============================================================================
//                          LED CONFIGURATION
// =============================================================================

// LED strip data pin
constexpr uint8_t LED_PIN = 12;

// Number of LEDs on the strip
constexpr uint8_t NUM_LEDS = 16;

// LED brightness (0-255)
constexpr uint8_t LED_BRIGHTNESS = 150;

// LED update interval (milliseconds)
constexpr uint8_t LED_UPDATE_MS = 30;

// =============================================================================
//                          SERIAL CONFIGURATION
// =============================================================================

constexpr uint32_t SERIAL_BAUD = 57600;
constexpr uint8_t  CMD_BUFFER_SIZE = 48;

#endif
