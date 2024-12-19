#include "core.h"

// Hash function
unsigned int hash(const char* key) {
    unsigned int hash = 0;
    while (*key) {
        hash = (hash << 5) + *key++;
    }
    return hash % HASH_TABLE_SIZE;
}

// Function to create a key from state and event
char* create_key(const char* state, const char* event) {
    char* key = (char*)malloc(strlen(state) + strlen(event) + 2);
    sprintf(key, "%s.%s", state, event);
    return key;
}

// Function to insert a state and event into the container
void insert(QHsmHelper* helper, const char* state, const char* event, ThreadedCodeExecutor* executor) {
    char* key = create_key(state, event);
    unsigned int index = hash(key);
    while (helper->container[index] != NULL) {
        index = (index + 1) % HASH_TABLE_SIZE;
    }
    helper->container[index] = (HashTableEntry*)malloc(sizeof(HashTableEntry));
    helper->container[index]->key = key;
    helper->container[index]->executor = executor;
}

// Function to get an executor from the container
ThreadedCodeExecutor* get_executor(QHsmHelper* helper, const char* key) {
    unsigned int index = hash(key);
    while (helper->container[index] != NULL) {
        if (strcmp(helper->container[index]->key, key) == 0) {
            return helper->container[index]->executor;
        }
        index = (index + 1) % HASH_TABLE_SIZE;
    }
    return NULL;
}

// Function to post an event
void post(Runner* runner, const char* event, void* data) {
    EventWrapper event_wrapper = {data, strdup(event)};
    runner->events_queue[runner->queue_size++] = event_wrapper;
    while (runner->queue_size > 0) {
        EventWrapper current_event = runner->events_queue[0];
        memmove(runner->events_queue, runner->events_queue + 1, (runner->queue_size - 1) * sizeof(EventWrapper));
        runner->queue_size--;

        char* key = create_key(runner->helper->state, current_event.event);
        ThreadedCodeExecutor* executor = get_executor(runner->helper, key);
        free(key);

        if (executor) {
            free(runner->helper->state);
            runner->helper->state = strdup(executor->target_state);
            for (int i = 0; i < executor->function_count; i++) {
                executor->functions[i](current_event.data);
            }
        } else {
            printf("runSync.error: %s->%s\n", runner->helper->state, current_event.event);
        }
    }
}

// Wrapper function with default argument
void post_(Runner* runner, const char* event) {
    post(runner, event, NULL);
}

// Function to set the state
void set_state(QHsmHelper* helper, const char* state) {
    free(helper->state);
    helper->state = strdup(state);
}

// Function to get the state
char* get_state(QHsmHelper* helper) {
    return helper->state;
}

// Function to initialize the QHsmHelper
QHsmHelper* compose_qhsm_helper(const char* initial_state) {
    QHsmHelper* helper = (QHsmHelper*)malloc(sizeof(QHsmHelper));
    helper->state = strdup(initial_state);
    memset(helper->container, 0, sizeof(helper->container));
    return helper;
}

// Function to initialize the Runner
Runner* compose_runner(QHsmHelper* helper) {
    Runner* runner = (Runner*)malloc(sizeof(Runner));
    runner->helper = helper;
    runner->queue_size = 0;
    return runner;
}

// Function to initialize the ThreadedCodeExecutor
ThreadedCodeExecutor* compose_threaded_code_executor(const char* target_state, void (*functions[])(void*), int function_count) {
    ThreadedCodeExecutor* executor = (ThreadedCodeExecutor*)malloc(sizeof(ThreadedCodeExecutor));
    executor->target_state = strdup(target_state);
    executor->function_count = function_count;
    for (int i = 0; i < function_count; i++) {
        executor->functions[i] = functions[i];
    }
    return executor;
}

void freeAllAllocatedMemory(QHsmHelper *helper, Runner *runner) {
    // Free allocated memory
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        if (helper->container[i] != NULL) {
            free(helper->container[i]->key);
            free(helper->container[i]->executor->target_state);
            free(helper->container[i]->executor);
            free(helper->container[i]);
        }
    }
    free(helper->state);
    free(helper);
    free(runner);
}

