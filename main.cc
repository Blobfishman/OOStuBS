/* $Id: main.cc 8485 2017-03-27 11:50:06Z friesel $ */

#include "device/keyboard.h"
#include "device/watch.h"
#include "machine/cpu.h"
#include "syscall/guarded_scheduler.h"
#include "user/appl.h"
#include "user/loop.h"
#include "util/print.h"

#define STACK_SIZE 4096

CPU cpu;
Watch watch(1000);
static char stack_loop1[STACK_SIZE];
static char stack_loop2[STACK_SIZE];
static char stack_loop3[STACK_SIZE];
static char stack_app[STACK_SIZE];
Loop loop1(stack_loop1 + STACK_SIZE, 1);
Loop loop2(stack_loop2 + STACK_SIZE, 2, true);
Loop loop3(stack_loop3 + STACK_SIZE, 3);
Application app(&stack_app + STACK_SIZE, &loop1);

int main() {
    guard.enter();
    scheduler.Scheduler::ready(loop1);
    scheduler.Scheduler::ready(loop2);
    scheduler.Scheduler::ready(loop3);
    scheduler.Scheduler::ready(app);
    keyboard.plugin();
    watch.windup();
    cpu.enable_int();
    scheduler.schedule();
}
