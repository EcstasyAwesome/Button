#include <Button.h>

Button button(A0, 0, 1000, 2000, 500);

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
