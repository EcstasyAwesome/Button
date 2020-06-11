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
    bool _state;
    bool _digital;
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
    Button(const uint8_t pin, const uint16_t min, const uint16_t max, const uint16_t tm1, const uint16_t tm2, const uint16_t tm3, const uint8_t tm4);
	Button(const uint8_t pin, const bool state, const uint16_t tm1, const uint16_t tm2, const uint16_t tm3, const uint8_t tm4);
	Button(const uint8_t pin, const uint16_t tm1, const uint16_t tm2, const uint16_t tm3, const uint8_t tm4);
    BUTTON_STATUS getStatus();
};

#endif