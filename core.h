#ifndef _Core_H
#define _Core_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_TABLE_SIZE 128
#define FUNC_TABLE_SIZE 16
#define QUEUE_SIZE      128

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))


// Define a structure for the event wrapper
typedef struct {
    void* data;
    char* event;
} EventWrapper;

// Define a structure for the threaded code executor
typedef struct {
    void (*functions[FUNC_TABLE_SIZE])(void*); // Assuming a maximum of 10 functions
    int function_count;
    char* target_state;
} ThreadedCodeExecutor;

// Define a structure for the hash table entry
typedef struct {
    char* key;
    ThreadedCodeExecutor* executor;
} HashTableEntry;

// Define a structure for the QHsmHelper
typedef struct {
    char* state;
    HashTableEntry* container[HASH_TABLE_SIZE];
} QHsmHelper;

// Define a structure for the runner
typedef struct {
    EventWrapper events_queue[QUEUE_SIZE]; // Assuming a maximum of 100 events
    int queue_size;
    QHsmHelper* helper;
} Runner;


// Function declarations
unsigned int hash(const char* key);
char*       create_key(const char* state, const char* event);
void        insert(QHsmHelper* helper, const char* state, const char* event, ThreadedCodeExecutor* executor);
ThreadedCodeExecutor*
            get_executor(QHsmHelper* helper, const char* key);
void        post(Runner* runner, const char* event, void* data);
void        post_(Runner* runner, const char* event);
void        set_state(QHsmHelper* helper, const char* state);
char*       get_state(QHsmHelper* helper);
QHsmHelper* compose_qhsm_helper(const char* initial_state);
Runner*     compose_runner(QHsmHelper* helper);
ThreadedCodeExecutor*
            compose_threaded_code_executor(const char* target_state, void (*functions[])(void*), int function_count);
void        freeAllAllocatedMemory(QHsmHelper *helper, Runner *runner);

#endif
