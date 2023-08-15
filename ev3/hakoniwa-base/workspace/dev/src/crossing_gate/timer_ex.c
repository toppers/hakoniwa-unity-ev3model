// Extended SimpleTimer

#include "timer_ex.h"

typedef struct _timer_counters_type {
    SYSTIM timer_start_count;
    SYSTIM timer_timedout_count;
    SYSTIM timer_current_count;
} timer_counters_type;

#define NUM_OF_TIMERS 5
static timer_counters_type timers[NUM_OF_TIMERS];

void timer_start(int id, int delay) {
    get_tim(&timers[id].timer_start_count);
    timers[id].timer_timedout_count
        = timers[id].timer_start_count + (SYSTIM)delay;
}

void timer_stop(int id) {
    timers[id].timer_start_count = (SYSTIM)0;
}

int timer_is_started(int id) {
    return (timers[id].timer_start_count > (SYSTIM)0);
}

bool timer_is_timedout(int id) {
    if(timers[id].timer_start_count <= 0 ) {
        return false;
    }

    get_tim(&timers[id].timer_current_count);
    if(timers[id].timer_current_count
        >= timers[id].timer_timedout_count ) {
        return true;
    } else {
        return false;
    }
}
