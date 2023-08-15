#include "app.h"

#include "railroad_crossing.h"

typedef enum _railroad_crossing_state {
    RC_INIT,
    RC_OPEN,  RC_OPEN2, RC_TO_OPEN,
    RC_CLOSE, RC_CLOSE2, RC_CLOSE3,
    RC_TO_CLOSE, TNUM_RC_STATE
} railroad_crossing_state;

static char* rc_state_msg[TNUM_RC_STATE] = {
    "RC_INIT",
    "RC_OPEN",  "RC_OPEN2", "RC_TO_OPEN",
    "RC_CLOSE", "RC_CLOSE2", "RC_CLOSE3",
    "RC_TO_CLOSE"
};

static railroad_crossing_state rc_state = RC_INIT;
static bool rc_is_entry = true;

#define ENTRY if(rc_is_entry){rc_is_entry=false;
#define DO }{
#define EVTCHK(f,s) if((f)){rc_state=(s);rc_is_entry=true;}
#define EXIT }if(rc_is_entry){
#define END }

void railroad_crossing_init(void) {
    gate_rotator_init();
    manual_switch_init();
    train_checker_init();
    train_detector_init();
    warning_light_init();
}

#define MY_TIMER_ID 0

void railroad_crossing_run(void) {
    if(rc_is_entry) { msg_f(rc_state_msg[rc_state], 2); }

    switch(rc_state) {
    case RC_INIT:
        ENTRY
            ev3_led_set_color(LED_ORANGE);
            railroad_crossing_init();
            timer_start(MY_TIMER_ID, 3000U*1000U);
        DO
        EVTCHK(timer_is_timedout(MY_TIMER_ID),RC_OPEN)
        EXIT
            timer_stop(MY_TIMER_ID);
            train_checker_caribrate();
        END
        break;
    case RC_OPEN:
        ENTRY
            ev3_led_set_color(LED_GREEN);
            horn_confirmation();
        DO
        EVTCHK(manual_switch_is_pushed(),RC_OPEN2)
        EVTCHK(train_checker_is_detected_A(),RC_TO_CLOSE)
        EXIT
            horn_at_A();
        END
        // if(train_checker_is_detected_B()) {
        //    horn_at_B();
        //    t_is_entry = true;
        //    rc_state = RC_TO_CLOSE;
        // }
        break;
    case RC_OPEN2:
        ENTRY
            ev3_led_set_color(LED_ORANGE);
        DO
        EVTCHK((!manual_switch_is_pushed()),RC_TO_CLOSE)
        EXIT
        END
        break;
    case RC_TO_CLOSE:
        ENTRY
            ev3_led_set_color(LED_ORANGE);
            gate_rotator_go_opening();
            // horn_warning();
            timer_start(MY_TIMER_ID,300U*1000U);
        DO
        EVTCHK(timer_is_timedout(MY_TIMER_ID),RC_CLOSE)
        EXIT
            timer_stop(MY_TIMER_ID);
        END
        break;
    case RC_CLOSE:
        ENTRY
            ev3_led_set_color(LED_RED);
            horn_warning();
        DO
        EVTCHK(manual_switch_is_pushed(),RC_CLOSE3)
        EVTCHK(train_detector_is_detected(),RC_CLOSE2)
        EXIT
        END
        break;
    case RC_CLOSE3:
        ENTRY
            ev3_led_set_color(LED_ORANGE);
        DO
        EVTCHK((!manual_switch_is_pushed()),RC_TO_OPEN)
        EXIT
        END
        break;
    case RC_CLOSE2:
        ENTRY
            ev3_led_set_color(LED_ORANGE);
        DO
        EVTCHK((!train_detector_is_detected()),RC_TO_OPEN)
        EXIT
        END
        break;
    case RC_TO_OPEN:
        ENTRY
            ev3_led_set_color(LED_ORANGE);
            gate_rotator_go_closing();
            // horn_warning();
            timer_start(MY_TIMER_ID, 2000U*1000U);
        DO
        // if(train_checker_is_detected_B()
        //   || timer_is_timedout(MY_TIMER_ID)) {
        EVTCHK(timer_is_timedout(MY_TIMER_ID),RC_OPEN)
        EXIT
            timer_stop(MY_TIMER_ID);
            horn_at_B();
        END
        break;
    case TNUM_RC_STATE:
    default:
        break;
    }

    ext_tsk();
}
