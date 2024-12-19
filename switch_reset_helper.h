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
