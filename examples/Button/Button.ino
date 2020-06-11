#include <Button.h>

// analog button
Button button(A0, 0, 10, 1000, 2000, 500, 100);

// digital button
//Button button(2, HIGH, 1000, 2000, 500, 100);

// digital button with inner pull-up resistor
//Button button(2, 1000, 2000, 500, 100);

void setup() {
  Serial.begin(9600);
}

void loop() {
  switch (button.getStatus()) {
    case BUTTON_SHORT: Serial.println("short"); break;
    case BUTTON_AUTO: Serial.println("auto"); break;
    case BUTTON_LONG: Serial.println("long"); break;
    //case BUTTON_NONE: Serial.println("none"); break;
  }
}