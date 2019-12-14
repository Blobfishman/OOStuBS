/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                         A P P L I C A T I O N                             */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Die Klasse Application definiert die einzige Anwendung von OO-Stubs.      */
/*****************************************************************************/

/* INCLUDES */

#include "user/appl.h"
#include "device/cgastr.h"
#include "device/keyboard.h"
#include "machine/cpu.h"

bool flag = true;

CPU cpu;

Application::Application() {
    keyboard.plugin();
    cpu.enable_int();
}

void Application::action() {
    CPU cpu;
    int i;
    while (flag) {
        int x, y;
        ++i;
        kout.getpos(x, y);
        kout.setpos(5, 5);
        kout << i;
        kout.flush();
        kout.setpos(x, y);
    }
    while (1) {
        int x, y;
        --i;
        kout.getpos(x, y);
        kout.setpos(5, 5);
        kout << i;
        kout.flush();
    }
}
