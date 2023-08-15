#ifndef TRAIN_CHECKER_H_
#define TRAIN_CHECKER_H_

#include "ev3api.h"
#include "stdbool.h"
#include "util.h"

extern void train_checker_init(void);
extern void train_checker_caribrate(void);
extern bool train_checker_is_detected_A(void);
extern bool train_checker_is_detected_B(void);

#endif // TRAIN_CHECKER_H_
