#ifndef WARNING_LIGHT_H_
#define WARNING_LIGHT_H_
//
//  warning_light.h
//

#include "ev3api.h"
#include "stdbool.h"
#include "util.h"
#include "timer_ex.h"

extern void warning_light_init(void);
extern void warning_light_flashing(void);
extern void warning_light_off(void);

#endif // WARNING_LIGHT_H_
