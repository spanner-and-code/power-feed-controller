#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

#include <MotorController.h>
#include <Button.h>
#include <ButtonGroup.h>
#include <Display.h>
#include <RGBEncoder.h>

#include "Pins.h"

// Speed button PWM values
#define SPEED_1_PWM 50
#define SPEED_2_PWM 127
#define SPEED_3_PWM 255

#include <HTDual6A.h>
// Motor Controller
HTDual6A controller = HTDual6A(CONTROLLER_DIR, CONTROLLER_PWM);

// Direction buttons
Button btnLeft = Button(BTN_LEFT, LED_LEFT, Button::PULLUP);
Button btnRight = Button(BTN_RIGHT, LED_RIGHT, Button::PULLUP);
ButtonGroup btnGroupDirection = ButtonGroup(2, &btnLeft, &btnRight);

// Start & Stop button
Button btnMotor = Button(BTN_MOTOR, LED_MOTOR, Button::PULLUP | Button::TOGGLE);

// Speed buttons
Button btnSpeed1 = Button(BTN_SPEED_1, LED_SPEED_1, Button::PULLUP);
Button btnSpeed2 = Button(BTN_SPEED_2, LED_SPEED_2, Button::PULLUP);
Button btnSpeed3 = Button(BTN_SPEED_3, LED_SPEED_3, Button::PULLUP);
ButtonGroup btnGroupSpeed = ButtonGroup(3, &btnSpeed1, &btnSpeed2, &btnSpeed3);

// RGB Encoder
RGBEncoder encoder = RGBEncoder(ENCODER_PIN_A, ENCODER_PIN_B, ENCODER_RGB_R, ENCODER_RGB_G, ENCODER_RGB_B, ENCODER_BTN, Button::PULLDOWN);

// Display
Display display(0x20, 16, 2);

volatile bool running = false;
uint8_t pwm = 0;

/**
 * stop function for interrupts
 */
void stop() {
  controller.setPWM(0);
  btnMotor.off();
  running = false;
}

/**
 * Start the motor
 */
void start() {
  controller.setPWM(pwm);
  running = true;
}

/**
 * Update the display with the new speed and set the controller if already running 
 */
void update(uint8_t speed) {
  display.printSpeed(speed);
  display.printPwm(pwm);
  if (running) {
    controller.setPWM(pwm);
  }
}

/**
 * Set the direction and update the display
 */
void direction(uint8_t btn) {
  if (btn == BTN_LEFT) {
    controller.setDirection(MotorController::CCW);
    display.printDirection(Display::DIRECTION_LEFT);
  } else if (btn == BTN_RIGHT) {
    controller.setDirection(MotorController::CW);
    display.printDirection(Display::DIRECTION_RIGHT);
  }
}

/**
 * Set the new speed
 */
void speed(uint8_t btn) {
  uint8_t speed;

  switch (btn) {
    case BTN_SPEED_1:
      pwm = SPEED_1_PWM;
      speed = Display::SPEED_1;
      break;
    case BTN_SPEED_2:
      pwm = SPEED_2_PWM;
      speed = Display::SPEED_2;
      break;
    case BTN_SPEED_3:
      pwm = SPEED_3_PWM;
      speed = Display::SPEED_3;
      break;
  }

  encoder.setRGB(B111); // Off
  update(speed);
}

void setup() {
  Serial.begin(9600);

  // Emergency stop interrupts
  pinMode(BTN_EMERGENCY_STOP, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BTN_EMERGENCY_STOP), stop, CHANGE);
  pinMode(END_STOP_ONE, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(END_STOP_ONE), stop, CHANGE);
  pinMode(END_STOP_TWO, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(END_STOP_TWO), stop, CHANGE);

  // Start display
  display.init();

  // Default to right
  btnRight.on();
  direction(BTN_RIGHT);

  // Default to speed 1
  btnSpeed1.on();
  speed(BTN_SPEED_1);
}

void loop() {
  // Start & Stop button
  if (btnMotor.isPressed()) {
    if (running) {
      stop();
    } else {
      start();
    }
  }

  // Direction button group
  btnGroupDirection.onPress(direction);

  // Speed button group
  btnGroupSpeed.onPress(speed);

  // Encoder press
  encoder.onPress([]() {
    encoder.setRGB(B000); // White
    // Turn off any speed buttons that might be on
    btnGroupSpeed.off();
    update(Display::SPEED_ROTARY);
  });

  // Encoder rotate
  // Print the PWM when the encoder rotates, new value won't apply till encoder click
  encoder.onRotate([](bool dir) {
    if (dir == Encoder::ROTATE_CW && pwm < UINT8_MAX) {
      pwm++;
    } else if (dir == Encoder::ROTATE_CCW && pwm > 25) {
      pwm--;
    }
    display.printPwm(pwm);
  });

  // Print status
  if (running) {
    display.printStatus(Display::STATUS_RUNNING);
  } else {
    display.printStatus(Display::STATUS_STOPPED);
  }
}
