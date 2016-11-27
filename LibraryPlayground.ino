#include <RotaryEncoder.h>
#include <LED.h>
#include <Button.h>
#include <FiniteStateMachine.h>

#define PIN_A 2
#define PIN_B 3
#define HOLD_STATES 2

RotaryEncoder encoder = RotaryEncoder(PIN_A, PIN_B);
Button button = Button(12);
LED led = LED(13);

byte buttonHolds = 0;

void ledOn() {
  led.on();
}

void ledOff() {
  led.off();
}

State ledOnState = State(ledOn);
State ledOffState = State(ledOff);

FSM buttonHoldStateMachine = FSM(ledOffState);

void setup() {
  button.clickHandler(ledCallback);
  button.holdHandler(ledCallback);
  encoder.incrementHandler(onIncrement);
  encoder.decrementHandler(onDecrement);
  encoder.begin();
  Serial.begin(9600);
}

void loop() {
  button.read();
  encoder.read();
}

void onIncrement(RotaryEncoder &source){
  Serial.println("Increment");
}

void onDecrement(RotaryEncoder &source){
  Serial.println("Decrement");
}

void onClick(Button &btn) {
  led.toggle();
}

void ledCallback(Button &btn) {
  buttonHolds = ++buttonHolds % HOLD_STATES;
  switch (buttonHolds){
    case 0: buttonHoldStateMachine.transitionTo(ledOnState); break;
    case 1: buttonHoldStateMachine.transitionTo(ledOffState); break;
  }

  buttonHoldStateMachine.update();
}
