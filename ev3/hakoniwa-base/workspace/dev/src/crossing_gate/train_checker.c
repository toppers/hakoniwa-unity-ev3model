//
// train_checker.c
//

#include "train_checker.h"

static const sensor_port_t train_checker_sensor_A = EV3_PORT_3;
static const sensor_port_t train_checker_sensor_B = EV3_PORT_2;
static const sensor_type_t train_checker_sensor_type = COLOR_SENSOR;

#define TC_THRESHOLD 0
static uint8_t train_checker_threshold_A = TC_THRESHOLD;
static uint8_t train_checker_threshold_B = TC_THRESHOLD;

void train_checker_set_threshold(sensor_port_t port, int threshold) {
    if(port == train_checker_sensor_A) {
        train_checker_threshold_A = threshold;
    }
    if(port == train_checker_sensor_B) {
        train_checker_threshold_B = threshold;
    }
}

void train_checker_caribrate(void) {
    train_checker_set_threshold
        ( train_checker_sensor_A,
          ev3_color_sensor_get_reflect(train_checker_sensor_A));
    train_checker_set_threshold
        ( train_checker_sensor_B,
          ev3_color_sensor_get_reflect(train_checker_sensor_B));
}

void train_checker_init(void) {
    ev3_sensor_config(train_checker_sensor_A, train_checker_sensor_type);
    ev3_sensor_config(train_checker_sensor_B, train_checker_sensor_type);
}

// しきい値と比較して、通過中はそれより大きい値か調べる
bool train_checker_is_detected(sensor_port_t port) {
    static uint8_t chk_old_A = 255;
    static uint8_t chk_old_B = 255;
    uint8_t chk = ev3_color_sensor_get_reflect(port);

    if(port == train_checker_sensor_A) {
        if( chk_old_A != chk ) {
            fmt_f("chk_A = %d", chk, 3);
            chk_old_A = chk;
#ifdef TARGET_REAL
            return chk > train_checker_threshold_A;
#else
            return chk < train_checker_threshold_A;
#endif
        }
    } else if(port == train_checker_sensor_B) {
        if( chk_old_B != chk ) {
            fmt_f("chk_B = %d", chk, 4);
            chk_old_B = chk;
#ifdef TARGET_REAL
            return chk > train_checker_threshold_B;
#else
            return chk < train_checker_threshold_B;
#endif
        }
    }

    return false;
}

bool train_checker_is_detected_A(void) {
    return train_checker_is_detected(train_checker_sensor_A);
}
bool train_checker_is_detected_B(void) {
    return train_checker_is_detected(train_checker_sensor_B);
}
