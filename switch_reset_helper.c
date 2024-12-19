#include "switch_reset_helper.h"

// Transfer functions

// void switch_entry(void* data) {
// }

// void switch_init(void* data) {    
// }

void off_entry(void* data) {
    printf("OFF\n");
}

void off_reset(void* data) {
    printf("@RESET\n");
}

// void off_exit(void* data) {
// }

void off_turn(void* data) {
    printf("OFF: TURN\n");
}

void on_entry(void* data) {
    printf("ON\n");
}

// void on_exit(void* data) {
// }

void on_turn(void* data) {
    printf("ON: TURN\n");
}

// Function to create the helper
void create_helper(QHsmHelper* helper) {
    void (*off_entry_functions[])(void*) = {
        // switch_entry,
        // switch_init,
        off_entry
    };
    insert(helper, "switch", "init", compose_threaded_code_executor("off", off_entry_functions, ARRAY_SIZE(off_entry_functions)));

    void (*off_reset_functions[])(void*) = {
        off_reset,
        // off_exit,
        // switch_init,
        off_entry
    };
    insert(helper, "off", "RESET", compose_threaded_code_executor("off", off_reset_functions, ARRAY_SIZE(off_reset_functions)));

    void (*off_turn_functions[])(void*) = {
        off_turn,
        on_entry
    };
    insert(helper, "off", "TURN", compose_threaded_code_executor("on", off_turn_functions, ARRAY_SIZE(off_turn_functions)));

    void (*on_reset_functions[])(void*) = {
        off_reset,
        // on_exit,
        // switch_init,
        off_entry
    };
    insert(helper, "on", "RESET", compose_threaded_code_executor("off", on_reset_functions, ARRAY_SIZE(on_reset_functions)));

    void (*on_turn_functions[])(void*) = {
        on_turn,
        // on_exit,
        // off_exit,
        // switch_init,
        off_entry
    };
    insert(helper, "on", "TURN", compose_threaded_code_executor("off", on_turn_functions, ARRAY_SIZE(on_turn_functions)));
}
