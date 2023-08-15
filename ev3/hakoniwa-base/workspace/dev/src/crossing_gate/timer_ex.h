#ifndef TIMER_EX_H_
#define _TIMER_EX_H_

#include "ev3api.h"
#include "stdbool.h"

extern void timer_start(int id, int delay_ms);
extern void timer_stop(int id);
extern int timer_is_started(int id);
extern bool timer_is_timedout(int id);

#endif  // MY_TIMER_EX_H_
