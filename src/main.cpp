/**
 * @file main.cpp
 * @author Christoph B. Wurzinger (wu@htlweiz.at)
 * @brief 
 * @version 0.1
 * @date 2024-02-06
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <Arduino.h>

/**
 * @brief State of a blinking output
 * 
 */
typedef struct {
  long next_action_at;
  long half_period;
  uint8_t pin_number;
} blink_t;

/**
 * @brief Update function for blinking an output
 * Non-Blocking, call repeatedly!
 * 
 * @param state 
 */
void blink(blink_t* state){
  signed long now = millis();
  if((now - state->next_action_at) >= 0) {
    // BUGGY: PIND |= _BV(state->pin_number);
    PIND = _BV(state->pin_number);
    state->next_action_at += (*state).half_period;
  }
}

blink_t s1;
blink_t s2;

/**
 * @brief GPIO and state setup
 * 
 */
void setup() {
  unsigned long now = millis();
  s1.pin_number = 2;
  s1.half_period = 131;
  s1.next_action_at = now;

  s2.pin_number = 3;
  s2.half_period = 127;
  s2.next_action_at = now;

  DDRD = 0xff;
}

/**
 * @brief Loop: called periodically by the arduino framework
 * 
 */
void loop() {
  blink(&s1);
  blink(&s2);
}