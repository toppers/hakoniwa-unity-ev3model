//
//  gate_rotator.c
//

#include "gate_rotator.h"

typedef enum _rotator_state {
    RS_INIT,
    RS_OPENED,         // 遮断桿が上がっている（遮断機が開いている）
    RS_CLOSING,        // 遮断桿を下ろしている（遮断機を閉じつつある）
    RS_CLOSED,         // 遮断桿が下がっている（遮断機が閉じている）
    RS_OPENING,        // 遮断桿を上げている（遮断機を開きつつある）
    TNUM_ROTATOR_STATE
} rotator_state;

static char* state_msg[TNUM_ROTATOR_STATE] = {
    "RS_INIT",
    "RS_OPEND", "RS_CLOSING",
    "RS_CLOSED", "RS_OPENING"
};

static rotator_state rs_state = RS_INIT;
static bool rs_is_entry = true;

#define ENTRY if(rs_is_entry){rs_is_entry=false;
#define DO }{
#define EVTCHK(f,s) if((f)){rs_state=(s);rs_is_entry=true;}
#define EXIT }if(rs_is_entry){
#define END }

static const motor_port_t gate1_port = EV3_PORT_A;
static const motor_port_t gate2_port = EV3_PORT_B;
static const motor_type_t motor_type = LARGE_MOTOR;

#define ROTATOR_POWER 8
static int16_t rotator_power = ROTATOR_POWER;

#define ROTATOR_COUNT 90
static int16_t gate1_count = 0;
static int16_t gate2_count = 0;

typedef enum _rotator_go_direction_type {
    RD_GO_CLOSING, RD_GO_OPENING
} rotator_go_direction_type;

static rotator_go_direction_type go_direction = RD_GO_CLOSING;

void gate_rotator_go_opening(void) {
    go_direction = RD_GO_OPENING;
}

void gate_rotator_go_closing(void) {
    go_direction = RD_GO_CLOSING;
}

static bool gate_rotator_got_open_request(void) {
    return go_direction == RD_GO_OPENING;
}

static bool gate_rotator_got_close_request(void) {
    return go_direction == RD_GO_CLOSING;
}

void gate_rotator_init(void) {
    ev3_motor_config(gate1_port, motor_type);
    ev3_motor_config(gate2_port, motor_type);
    ev3_motor_reset_counts(gate1_port);
    ev3_motor_reset_counts(gate1_port);
    gate1_count = 0;
    gate2_count = 0;
}

void gate_rotator_rotate_normal(void) {
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
    if(gate1_count >= ROTATOR_COUNT
       || gate2_count >= ROTATOR_COUNT) {
        return true;
    }
    return false;
}

bool gate_rotator_is_opened(void) {
    if(gate1_count <= 0 || gate2_count <= 0 ) {
        return true;
    }
    return false;
}

void gate_rotator_run(void) {
    if( rs_is_entry ) { msg_f(state_msg[rs_state], 5); }
    gate_rotator_update_counts();

    switch(rs_state ) {
    case RS_INIT:
        ENTRY
            gate_rotator_init();
        DO
        EVTCHK(true,RS_OPENED)
        EXIT
        END
        break;
    case RS_OPENED:
        ENTRY
        DO
        EVTCHK(gate_rotator_got_close_request(),RS_CLOSING)
        EXIT
        END
        break;
    case RS_CLOSING:
        ENTRY
            gate_rotator_rotate_normal();
        DO
        EVTCHK(gate_rotator_is_closed(),RS_CLOSED)
        EXIT
            gate_rotator_stop();
        END
        break;
    case RS_CLOSED:
        ENTRY
        DO
        EVTCHK(gate_rotator_got_open_request(),RS_OPENING)
        EXIT
        END
        break;
    case RS_OPENING:
        ENTRY
            gate_rotator_rotate_reverse();
        DO
        EVTCHK(gate_rotator_is_opened(),RS_OPENED)
        EXIT
            gate_rotator_stop();
        END
        break;
    default:
    case TNUM_ROTATOR_STATE:
        break;
    }
}
