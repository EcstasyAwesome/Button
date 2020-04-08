#include "Button.h"

/*
 * @param pin
 *        pin number that a buttom is connected
 * @param value
 *        button value that a button is pressed
 * @param tm1
 *        long pushing time (ms), if 0 - disable (default is 0)
 * @param tm2
 *        auto pushing time (ms), if 0 - disable (default is 0)
 * @param tm3
 *        time (ms) between auto pushing (default is 0)
 * @param tm4
 *        debounce time (ms) (default is 100)
 */

Button::Button(const uint8_t pin, const uint16_t value, const uint16_t tm1, const uint16_t tm2, const uint16_t tm3, const uint8_t tm4) {
  _pin = pin;
  _min = (value <= 23) ? 0 : (value - 23);
  _max = (value >= 1000) ? 1023 : (value + 23);
  _long = tm1;
  _auto = tm2;
  _interval = tm3;
  _debounce = tm4;
}

/*
 * The method runs in the main loop()
 * @return event of pushing
 */

BUTTON_STATUS Button::getStatus() {
  uint16_t value = analogRead(_pin);
  if (value < _max && value >= _min) {
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