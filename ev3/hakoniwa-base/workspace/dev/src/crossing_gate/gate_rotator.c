//
//  gate_rotator.c
//

#include "gate_rotator.h"

typedef enum _gate_rotator_state {
    GRS_INIT,
    GRS_OPENED,         // 遮断桿が上がっている（遮断機が開いている）
    GRS_CLOSING,        // 遮断桿を下ろしている（遮断機を閉じつつある）
    GRS_CLOSED,         // 遮断桿が下がっている（遮断機が閉じている）
    GRS_OPENING,        // 遮断桿を上げている（遮断機を開きつつある）
    TNUM_ROTATOR_STATE
} gate_rotator_state;

static char* state_msg[TNUM_ROTATOR_STATE] = {
    "GRS_INIT",
    "GRS_OPENED", "GRS_CLOSING",
    "GRS_CLOSED", "GRS_OPENING"
};

static gate_rotator_state gr_state = GRS_INIT;
static bool grs_is_entry = true;

#define ENTRY if(grs_is_entry){grs_is_entry=false;
#define DO }{
#define EVTCHK(f,s) if((f)){gr_state=(s);grs_is_entry=true;}
#define EXIT }if(grs_is_entry){
#define END }

static const motor_port_t gate1_port = EV3_PORT_A;
static const motor_port_t gate2_port = EV3_PORT_B;
static const motor_type_t motor_type = LARGE_MOTOR;

#define ROTATOR_POWER 8
static int16_t rotator_power = ROTATOR_POWER;

#define ROTATOR_COUNT 90
static int16_t gate1_count = 0;
static int16_t gate2_count = 0;

typedef enum _gate_rotator_direction_type {
    GR_DIR_CLOSING, GR_DIR_OPENING
} gate_rotator_direction_type;

static gate_rotator_direction_type gr_direction = GR_DIR_OPENING;

void gate_rotator_go_opening(void) {
    gr_direction = GR_DIR_OPENING;
}

void gate_rotator_go_closing(void) {
    gr_direction = GR_DIR_CLOSING;
}

static bool gate_rotator_got_open_request(void) {
    return gr_direction == GR_DIR_OPENING;
}

static bool gate_rotator_got_close_request(void) {
    return gr_direction == GR_DIR_CLOSING;
}

void gate_rotator_init(void) {
    ev3_motor_config(gate1_port, motor_type);
    ev3_motor_config(gate2_port, motor_type);
    ev3_motor_reset_counts(gate1_port);
    ev3_motor_reset_counts(gate1_port);
    gate1_count = 0;
    gate2_count = 0;
    gr_state = GRS_INIT;
    gr_direction = GR_DIR_OPENING;
}

void gate_rotator_rotate_normal(void) {
    syslog(LOG_NOTICE, "rotator_power=%d", rotator_power);
    ev3_motor_set_power(gate1_port, rotator_power);
    ev3_motor_set_power(gate2_port, rotator_power);

    /* ev3_motor_rotate(motor_port1, rotator_degree, rotator_speed, false); */
    /* ev3_motor_rotate(motor_port2, rotator_degree, rotator_speed, false); */
}

void gate_rotator_rotate_reverse(void) {
    ev3_motor_set_power(gate1_port, -rotator_power);
    ev3_motor_set_power(gate2_port, -rotator_power);

    /* ev3_motor_rotate(motor_port1, -rotator_degree, rotator_speed, false); */
    /* ev3_motor_rotate(motor_port2, -rotator_degree, rotator_speed, false); */
}

void gate_rotator_stop(void) {
    ev3_motor_stop(gate1_port, true);
    ev3_motor_stop(gate2_port, true);
}

void gate_rotator_update_counts(void) {
    gate1_count = ev3_motor_get_counts(gate1_port);
    gate2_count = ev3_motor_get_counts(gate2_port);
}

bool gate_rotator_is_closed(void) {
    /* if(gate1_count >= ROTATOR_COUNT  */
    /*    || gate2_count >= ROTATOR_COUNT) { */
    if(gate1_count >= ROTATOR_COUNT) {
        return true;
    }
    return false;
}

bool gate_rotator_is_opened(void) {
    /* if(gate1_count <= 0 || gate2_count <= 0 ) { */
    if(gate1_count <= 0) {
        return true;
    }
    return false;
}

void gate_rotator_run(void) {
    gate_rotator_update_counts();
    if( grs_is_entry ) {
        fmt_f2("%s, %d", state_msg[gr_state], gate1_count, 2);
    }

    switch(gr_state) {
    case GRS_INIT:
        ENTRY
            gate_rotator_init();
        DO
        EVTCHK(true,GRS_OPENED)
        EXIT
        END
        break;
    case GRS_OPENED:
        ENTRY
        DO
        EVTCHK(gate_rotator_got_close_request(),GRS_CLOSING)
        EXIT
        END
        break;
    case GRS_CLOSING:
        ENTRY
            gate_rotator_rotate_normal();
        DO
        EVTCHK(gate_rotator_is_closed(),GRS_CLOSED)
        EXIT
            gate_rotator_stop();
        END
        break;
    case GRS_CLOSED:
        ENTRY
        DO
        EVTCHK(gate_rotator_got_open_request(),GRS_OPENING)
        EXIT
        END
        break;
    case GRS_OPENING:
        ENTRY
            gate_rotator_rotate_reverse();
        DO
        EVTCHK(gate_rotator_is_opened(),GRS_OPENED)
        EXIT
            gate_rotator_stop();
        END
        break;
    default:
    case TNUM_ROTATOR_STATE:
        break;
    }
}
