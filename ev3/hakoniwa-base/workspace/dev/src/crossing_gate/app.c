#include "app.h"

#include "railroad_crossing.h"

static bool is_initialized = false;

void main_task(intptr_t unused) {
    if(! is_initialized ) {
        init_f("railroad crossing");
        is_initialized = true;
    }

    railroad_crossing_run();

    ext_tsk();
}

void sub_task(intptr_t unused) {
    if( is_initialized ) {
        train_detector_run();
    }
    ext_tsk();
}
