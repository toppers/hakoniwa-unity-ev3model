//
//  warning_light.c
//

#include "warning_light.h"

static const motor_port_t light_port = EV3_PORT_C;
static const motor_type_t motor_type = UNREGULATED_MOTOR;

#define LIGHT_POWER 80
static int16_t light_power = LIGHT_POWER;

typedef enum _light_state {
    WL_INIT,
    WL_OFF,
    WL_FLASHING,
    TNUM_LIGHT_STATE
} light_state;

static light_state wl_state = WL_OFF;

void warning_light_init(void) {
    ev3_motor_config(light_port, motor_type);
    wl_state = WL_OFF;
}

void warning_light_flashing(void) {
    wl_state = WL_FLASHING;
}

void warning_light_off(void) {
    wl_state = WL_OFF;
}

static const int WL_TIMER_ID = 1;

void warning_light_run(void) {
    static bool is_light_on = true;

    switch(wl_state) {
    case WL_FLASHING:
        if(!timer_is_started(WL_TIMER_ID)) {
            timer_start(WL_TIMER_ID, 500U * 1000U);
            if(is_light_on) {
                ev3_motor_stop(light_port, false);
            } else {
                ev3_motor_set_power(light_port, light_power);
            }
        }
        if(timer_is_timedout(WL_TIMER_ID)) {
            timer_stop(WL_TIMER_ID);
            is_light_on = !is_light_on;
        }
        break;
    case WL_OFF:
    default:
        ev3_motor_stop(light_port, false);
        break;
    }
}
