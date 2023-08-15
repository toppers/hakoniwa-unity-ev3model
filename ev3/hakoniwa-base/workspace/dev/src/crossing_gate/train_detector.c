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

static int8_t dist_old = 255;

void train_detector_init(void) {
  ev3_sensor_config(train_detector_sensor_port, train_detector_sensor_type);
  dist_old = 0;
  dly_tsk(1000U * 1000U);
}

// 通過していないときは13, 14 など、通過中は4,5,,,8 などとなる
// 背が低い車両や、車両間の隙間の対策（一定時間の経過を判定する等）が必要
// このdetectorを使うには cyc0 の周期は100ms以上にする
bool train_detector_is_detected(void) {
    int8_t distance
      = ev3_ultrasonic_sensor_get_distance(train_detector_sensor_port);

    if( dist_old != distance ) {
        fmt_f("dist= %d", distance, 5);
    }
    dist_old = distance;
    return distance < train_detector_threshold;
}
