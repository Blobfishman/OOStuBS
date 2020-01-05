/* $Id: main.cc 8485 2017-03-27 11:50:06Z friesel $ */

#include "thread/scheduler.h"
#include "user/appl.h"
#include "util/print.h"
Scheduler scheduler;
Application app1;
Application app2;

int main() {
    scheduler.ready(app1);
    scheduler.ready(app2);
    scheduler.schedule();
}
