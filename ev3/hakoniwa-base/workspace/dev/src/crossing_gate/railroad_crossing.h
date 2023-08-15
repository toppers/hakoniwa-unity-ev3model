#ifndef RAILROAD_CROSSING_H_
#define RAILROAD_CROSSING_H_

#include "ev3api.h"
#include "stdbool.h"
#include "timer_ex.h"
#include "horn.h"
#include "util.h"
#include "manual_switch.h"
#include "train_detector.h"
#include "train_checker.h"
#include "gate_rotator.h"
#include "warning_light.h"

extern void railroad_crossing_init(void);
extern void railroad_crossing_run(void);

#endif // RAILROAD_CROSSING_H_
