#ifndef Button_h
#define Button_h
#include "Arduino.h"

typedef enum {
  BUTTON_NONE = 0,
  BUTTON_SHORT,
  BUTTON_LONG,
  BUTTON_AUTO,
} BUTTON_STATUS;

class Button {
  private:
    bool _pressed;
    bool _longPressed;
    bool _autoPressed;
    uint8_t _pin;
	uint8_t _debounce;
    uint16_t _min;
    uint16_t _max;
    uint16_t _long;
    uint16_t _auto;
    uint16_t _interval;
    uint32_t _time;
  public:
    Button(const uint8_t pin, const uint16_t value, const uint16_t tm1 = 0, const uint16_t tm2 = 0, const uint16_t tm3 = 0, const uint8_t tm4 = 100);
    BUTTON_STATUS getStatus();
};

#endif