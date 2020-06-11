#include "Button.h"

/*
 * Use this constructor if a button is connected to an analog pin
 * Using min/max values can be useful because sometimes the real button value can be different than value was declared by the user
 *
 * @param pin
 *        pin number that a buttom is connected
 * @param min
 *        button min value that a button is pressed
 * @param max
 *        button max value that a button is pressed
 * @param tm1
 *        long pushing time (ms), if 0 - disable
 * @param tm2
 *        auto pushing time (ms), if 0 - disable
 * @param tm3
 *        time (ms) between auto pushing, if tm2 is disabled tm3 is ignored
 * @param tm4
 *        debounce time (ms)
 */

Button::Button(const uint8_t pin, const uint16_t min, const uint16_t max, const uint16_t tm1, const uint16_t tm2, const uint16_t tm3, const uint8_t tm4) {
  _pin = pin;
  _min = min;
  _max = max;
  _long = tm1;
  _auto = tm2;
  _interval = tm3;
  _debounce = tm4;
  _digital = false;
}

/*
 * Use this constructor if a button is connected to a digital pin
 *
 * @param pin
 *        pin number that a buttom is connected
 * @param state
 *        pin state when the button is pressed (HIGH/true or LOW/false)
 * @param tm1
 *        long pushing time (ms), if 0 - disable
 * @param tm2
 *        auto pushing time (ms), if 0 - disable
 * @param tm3
 *        time (ms) between auto pushing, if tm2 is disabled tm3 is ignored
 * @param tm4
 *        debounce time (ms)
 */

Button::Button(const uint8_t pin, const bool state, const uint16_t tm1, const uint16_t tm2, const uint16_t tm3, const uint8_t tm4) {
  _pin = pin;
  _long = tm1;
  _auto = tm2;
  _interval = tm3;
  _debounce = tm4;
  _digital = true;
  _state = state;
  pinMode(_pin, INPUT);
}

/*
 * Use this constructor if a button is connected to a digital pin, using an inner pull-up resistor
 *
 * @param pin
 *        pin number that a buttom is connected
 * @param tm1
 *        long pushing time (ms), if 0 - disable
 * @param tm2
 *        auto pushing time (ms), if 0 - disable
 * @param tm3
 *        time (ms) between auto pushing, if tm2 is disabled tm3 is ignored
 * @param tm4
 *        debounce time (ms)
 */

Button::Button(const uint8_t pin, const uint16_t tm1, const uint16_t tm2, const uint16_t tm3, const uint8_t tm4) {
  _pin = pin;
  _long = tm1;
  _auto = tm2;
  _interval = tm3;
  _debounce = tm4;
  _digital = true;
  _state = false;
  pinMode(_pin, INPUT_PULLUP);
}

/*
 * The method runs in the main loop()
 * @return event of pushing
 */

BUTTON_STATUS Button::getStatus() {
  bool physicallyPressed;
  if (_digital) physicallyPressed = _state ? digitalRead(_pin) : !digitalRead(_pin);
  else {
  	uint16_t value = analogRead(_pin);
	physicallyPressed = value <= _max && value >= _min;
  }
  if (physicallyPressed) {
    if (!_pressed) {
      if (millis() - _time >= _debounce) {
        _pressed = true;
        _time = millis();
        if (_long == 0 && _auto == 0) return BUTTON_SHORT;
      }
    }
    else if (_long != 0 && !_longPressed && (millis() - _time) >= _long) {
      _longPressed = true;
      if (_auto == 0) return BUTTON_LONG;
    }
    else if (_auto != 0) {
      if (!_autoPressed) {
        if (millis() - _time >= _auto) {
          _autoPressed = true;
          _time = millis();
          return BUTTON_AUTO;
        }
      }
      else if (millis() - _time >= _interval) {
        _time = millis();
        return BUTTON_AUTO;
      }
    }
  }
  else if (_pressed && (millis() - _time) >= _debounce) {
    BUTTON_STATUS status = BUTTON_NONE;
    if (!_autoPressed) {
      if (_longPressed) {
        if (_auto != 0) status = BUTTON_LONG;
      }
      else if (_long != 0 || _auto != 0) status = BUTTON_SHORT;
    }
    _pressed = false;
    _longPressed = false;
    _autoPressed = false;
    _time = millis();
    return status;
  }
  return BUTTON_NONE;
}