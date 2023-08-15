#include "app.h"

#include "railroad_crossing.h"

void main_task(intptr_t unused) {
    static bool is_initialized = false;
    if(! is_initialized ) {
        init_f("railroad crossing");
        is_initialized = true;
    }

    railroad_crossing_run();

    ext_tsk();
}
