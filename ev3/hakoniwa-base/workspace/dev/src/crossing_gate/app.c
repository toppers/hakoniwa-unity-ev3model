/**
 * This sample program balances a two-wheeled Segway type robot such as Gyroboy in EV3 core set.
 *
 * References:
 * http://www.hitechnic.com/blog/gyro-sensor/htway/
 * http://www.cs.bgu.ac.il/~ami/teaching/Lejos-2013/classes/src/lejos/robotics/navigation/Segoway.java
 */

#include "ev3api.h"
#include "app.h"

//#define DEBUG

#ifdef DEBUG
#define _debug(x) (x)
#else
#define _debug(x)
#endif

static const int left_motor = EV3_PORT_A;
static const int right_motor = EV3_PORT_B;

static const int touch_sensor0 = EV3_PORT_1;
static const int color_sensor_a = EV3_PORT_2;
static const int color_sensor_b = EV3_PORT_3;
static const int ultrasonic_sensor = EV3_PORT_4;

#define ERR_CHECK(err)  \
do {    \
    if ((err) != 0) {   \
        syslog(LOG_NOTICE, "ERROR: %s %d err=%d", __FUNCTION__, __LINE__, (err));   \
    }   \
} while (0)

colorid_t color = COLOR_NONE;
static void check_color_sensor(int id)
{
    color = ev3_color_sensor_get_color(id);
    uint8_t value = ev3_color_sensor_get_reflect(id);
    char *color_str = "NULL";
    switch (color) {
        case COLOR_NONE:
            color_str = "NONE";
            break;
        case COLOR_BLACK:
            color_str = "BLACK";
            break;
        case COLOR_BLUE:
            color_str = "BLUE";
            break;
        case COLOR_GREEN:
            color_str = "GREEN";
            break;
        case COLOR_YELLOW:
            color_str = "YELLOW";
            break;
        case COLOR_RED:
            color_str = "RED";
            break;
        case COLOR_WHITE:
            color_str = "WHITE";
            break;
        case COLOR_BROWN:
            color_str = "BROWN";
            break;
        default:
            break;
    }
    syslog(LOG_NOTICE, "id=%d color=%s reflect_value=%d", id, color_str, value);
    return;
}

int16_t ultrasonic_value = 0;
static void check_ultrasonic_sensor(void)
{
    ultrasonic_value = ev3_ultrasonic_sensor_get_distance(ultrasonic_sensor);
    syslog(LOG_NOTICE, "ultrasonic_value=%d", ultrasonic_value);
    return;
}
/*
 * 1.7 タッチセンサの値を見る
 */
bool_t is_pressed[2] = { false, false };
static void check_touch_sensor(int id)
{
    int inx = (id == touch_sensor0) ? 0 : 1;
    is_pressed[inx] = ev3_touch_sensor_is_pressed(id);
    if (is_pressed[inx]) {
        syslog(LOG_NOTICE, "is_pressed[%d]=%d", inx, is_pressed[inx]);
    }
    return;
}

static void do_stop(void)
{
    ER err = ev3_motor_stop(left_motor, true);
    ERR_CHECK(err);
    err = ev3_motor_stop(right_motor, true);
    ERR_CHECK(err);
}

static void check_angle(int id)
{
    int32_t counts = ev3_motor_get_counts(id);
    syslog(LOG_NOTICE, "motor_id=%d count=%d", id, counts);
}

static void do_arm_move(int id, bool_t normal_rotate)
{
    if (normal_rotate) {
        ER err = ev3_motor_set_power(id, 2);
        ERR_CHECK(err);
        check_angle(id);
    }
    else {
        ER err = ev3_motor_set_power(id, -2);
        ERR_CHECK(err);
    }
    return;
}



void main_task(intptr_t unused) {
    ev3_sensor_config(color_sensor_a, COLOR_SENSOR);
    ev3_sensor_config(color_sensor_b, COLOR_SENSOR);
    ev3_sensor_config(ultrasonic_sensor, ULTRASONIC_SENSOR);
    ev3_sensor_config(touch_sensor0, TOUCH_SENSOR);
    ev3_motor_config(left_motor, LARGE_MOTOR);
    ev3_motor_config(right_motor, LARGE_MOTOR);
  
    syslog(LOG_NOTICE, "#### motor control start");

    ev3_motor_stop(left_motor, true);
    ev3_motor_stop(right_motor, true);
    while(1) {
        check_touch_sensor(touch_sensor0);
        if (is_pressed[0]) {
            do_arm_move(left_motor, true);
            do_arm_move(right_motor, true);
        }
        else {
            do_arm_move(left_motor, false);
            do_arm_move(right_motor, false);
        }
        tslp_tsk(100000); /* 100msec */
    }
}
