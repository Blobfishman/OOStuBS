#include "thread/idle_thread.h"
#include "machine/cpu.h"

#define IDLE_STACK_SIZE 1024

static char idle_stack[IDLE_STACK_SIZE];
Idle_Thread idle_thread(idle_stack + IDLE_STACK_SIZE);

Idle_Thread::Idle_Thread(void* stack) : Thread(stack) {}

void Idle_Thread::action() {
    while (true) {
        cpu.idle();
    }
}
