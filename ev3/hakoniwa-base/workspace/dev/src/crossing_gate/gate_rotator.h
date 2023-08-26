#ifndef ROTATOR_H_
#define ROTATOR_H_
//
//  gate_rotator.h
//

#include "ev3api.h"
#include "stdbool.h"
#include "util.h"

extern void gate_rotator_go_opening(void);
extern void gate_rotator_go_closing(void);
extern bool gate_rotator_is_closed(void);
extern bool gate_rotator_is_opened(void);
extern void gate_rotator_init(void);
extern void gate_rotator_stop(void);
extern void gate_rotator_run(void);

#endif // ROTATOR_H_
