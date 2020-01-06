/* $Id: main.cc 8485 2017-03-27 11:50:06Z friesel $ */

#include "thread/scheduler.h"
#include "user/appl.h"
#include "user/loop.h"
#include "util/print.h"
#include "machine/cpu.h"

CPU cpu;
Scheduler scheduler;
Loop loop1(1, 4);
Loop loop2(1, 6);

int main() {
    scheduler.ready(loop1);
    scheduler.ready(loop2);
    scheduler.schedule();
}
