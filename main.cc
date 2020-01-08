/* $Id: main.cc 8485 2017-03-27 11:50:06Z friesel $ */

#include "thread/scheduler.h"
#include "user/appl.h"
#include "user/loop.h"
#include "util/print.h"
#include "machine/cpu.h"
#include "device/keyboard.h"

CPU cpu;
Scheduler scheduler;
Loop loop1(1, 4);
Loop loop2(1, 6, true);
Application app(&loop1);

int main() {
    keyboard.plugin();
    cpu.enable_int();
    scheduler.ready(loop1);
    scheduler.ready(loop2);
    scheduler.ready(app);
    scheduler.schedule();
}
