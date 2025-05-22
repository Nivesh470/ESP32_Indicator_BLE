#include "indicator_model.h"

static bool leftMode = false;
static bool rightMode = false;
static bool hazardMode = false;
static int leftHoldCount = 0;
static int rightHoldCount = 0;
static int blinkCounter = 0;
static bool ledToggle = false;

void indicator_model_initialize(void) {
    leftMode = rightMode = hazardMode = false;
    leftHoldCount = rightHoldCount = blinkCounter = 0;
    ledToggle = false;
}

void indicator_model_step(bool leftButton, bool rightButton, bool *leftLED, bool *rightLED) {
    // Handle 1s button hold (assuming 100ms step)
    if (leftButton) {
        if (leftHoldCount < 10) leftHoldCount++;
    } else {
        if (leftHoldCount >= 10) {
            if (hazardMode) { hazardMode = false; leftMode = true; rightMode = false; }
            else if (rightMode) { rightMode = false; leftMode = true; }
            else if (leftMode) { leftMode = false; }
            else { leftMode = true; }
        }
        leftHoldCount = 0;
    }

    if (rightButton) {
        if (rightHoldCount < 10) rightHoldCount++;
    } else {
        if (rightHoldCount >= 10) {
            if (hazardMode) { hazardMode = false; rightMode = true; leftMode = false; }
            else if (leftMode) { leftMode = false; rightMode = true; }
            else if (rightMode) { rightMode = false; }
            else { rightMode = true; }
        }
        rightHoldCount = 0;
    }

    // Hazard activation
    if (leftButton && rightButton) {
        if (leftHoldCount >= 10 && rightHoldCount >= 10) {
            hazardMode = true;
            leftMode = false;
            rightMode = false;
        }
    }

    // Blinking every 300ms (3 x 100ms steps)
    blinkCounter++;
    if (blinkCounter >= 3) {
        ledToggle = !ledToggle;
        blinkCounter = 0;
    }

    // Output logic
    *leftLED = (leftMode || hazardMode) ? ledToggle : false;
    *rightLED = (rightMode || hazardMode) ? ledToggle : false;
}
