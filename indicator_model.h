#ifndef INDICATOR_MODEL_H_
#define INDICATOR_MODEL_H_

#include <stdbool.h>

void indicator_model_initialize(void);
void indicator_model_step(bool leftButton, bool rightButton, bool *leftLED, bool *rightLED);

#endif
