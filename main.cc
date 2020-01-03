/* $Id: main.cc 8485 2017-03-27 11:50:06Z friesel $ */

#include "user/appl.h"
#include "util/print.h"
#include "thread/dispatch.h"
Dispatcher dispatcher;
Application app1;
Application app2;

int main() {
    dispatcher.go(app1);
}
