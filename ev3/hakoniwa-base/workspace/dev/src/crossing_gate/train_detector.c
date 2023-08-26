//
// train_detector.c
//

#include "train_detector.h"

static const sensor_port_t train_detector_sensor_port = EV3_PORT_4;
static const sensor_type_t train_detector_sensor_type = ULTRASONIC_SENSOR;

#define TD_THRESHOLD 10
static int train_detector_threshold = TD_THRESHOLD;

void train_detector_set_threshold(int threshold) {
  train_detector_threshold = threshold;
}

static int8_t distance = 255;
static int8_t saved_distance = 255;
static bool detected = false;

void train_detector_init(void) {
    ev3_sensor_config(train_detector_sensor_port, train_detector_sensor_type);
    distance = 255;
    saved_distance = 255;
    dly_tsk(500U * 1000U);
}

// 通過していないときは13, 14 など、通過中は4,5,,,8 などとなる
// 背が低い車両や、車両間の隙間の対策（一定時間の経過を判定する等）が必要
// 周期ハンドラの周期が100ms以上ないときは、呼び出しを間欠的にする
bool train_detector_is_detected(void) {

    return detected;
}

void train_detector_run(void) {
    distance
        = ev3_ultrasonic_sensor_get_distance(train_detector_sensor_port);

    detected = distance < train_detector_threshold;
    if( saved_distance != distance ) {
        if( detected ) {
            fmt_f("dist= %d (d)", distance, 5);
        } else {
            fmt_f("dist= %d (n)", distance, 5);
        }
    }
    saved_distance = distance;
}

