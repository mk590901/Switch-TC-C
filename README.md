# SWITCH-TC-C

The application tests threaded code generated by the editor of hierarchical state machines. The original scheme can be seen in the attached movie. It's another model of a switch affected by two events: __TURN__ and __RESET__. The first switches two states __ON__ and __OFF__, the second resets the state machine to the __OFF__ state regardless of what state it was in before.

## Precondition

The editor's __Planner__ module was supplemented with __C__ code generator, which automatically generates the __switch_reset_helper.h__ and __switch_reset_helper.c__ files. A core has also been added to the application, which services the launch of threaded code and the impact of events on it. This is a set of next files: __core.h__ and _core.c__.

## Code modification

The generated __switch_reset_helper.c__ file is a skeleton for the logical part of the application, namely the list and bodies of empty transfer functions that can and should be filled with some content. For example, with trace elements in the simplest case. Some functions may not be used and should be deleted or commented out:

```c
#ifndef _Switch_ResetHelper_H
#define _Switch_ResetHelper_H

#include "core.h"

// Transfer functions

// void switch_entry(void* data);
// void switch_init(void* data);
void off_entry  (void* data);
void off_reset  (void* data);
// void off_exit(void* data);
void off_turn   (void* data);
void on_entry   (void* data);
// void on_exit(void* data);
void on_turn    (void* data);

void create_helper(QHsmHelper* helper);

#endif
```

```c
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
```
## Description of the application

The application is created as a __ubuntu__ __console application__ and can be launched in terminal mode:

```c
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

```
## Compilation and build
```
micrcx@micrcx-desktop:~/vs_cpp/tc_c$ make
cc    -c -o core.o core.c
cc    -c -o switch_reset_helper.o switch_reset_helper.c
cc    -c -o main.o main.c
g++ core.o switch_reset_helper.o main.o -o switch
```

## Run
```
micrcx@micrcx-desktop:~/vs_cpp/tc_c$ ./switch
OFF
OFF: TURN
ON
@RESET
OFF
OFF: TURN
ON
ON: TURN
OFF
@RESET
OFF
micrcx@micrcx-desktop:~/vs_cpp/tc_c$ 
```

## Movie

[c_sample.webm](https://github.com/user-attachments/assets/fa6ce062-e931-4059-9d1d-28c09f1f9b9f)



