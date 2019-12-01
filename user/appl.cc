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

Application::Application() {
    keyboard.plugin();
    CPU cpu;
    cpu.enable_int();
}

void Application::action() {
    while(1) {
        int x,y;
        kout.getpos(x,y);
        kout << "xxxxxxxxxxXXXXXXXXXXXXxxxxxxxxxxx";
        kout.flush();
        kout.setpos(x, y);
    }
}
