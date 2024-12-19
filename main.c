//#include "core.h"
#include "switch_reset_helper.h"

// Function to test the switch
void test_switch() {
    QHsmHelper* helper = compose_qhsm_helper("switch");
    Runner* runner = compose_runner(helper);
    create_helper(helper);

    post_(runner, "init");
    post_(runner, "TURN");
    post_(runner, "RESET");
    post_(runner, "TURN");
    post_(runner, "TURN");
    post_(runner, "RESET");

    freeAllAllocatedMemory(helper, runner);
}

int main() {
    test_switch();
    return 0;
}

