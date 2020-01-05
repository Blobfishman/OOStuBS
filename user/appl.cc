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
#include "guard/secure.h"
#include "machine/cpu.h"
#include "thread/scheduler.h"

CPU cpu;

Application::Application() : Entrant(m_stack + 1000) {
    keyboard.plugin();
    cpu.enable_int();
}

void Application::action() {
    int i = 0;
    int x, y;
    kout.getpos(x, y);
    while (true) {
        // Secure secure;
        kout.setpos(x, y);
        kout << i++;
        kout.flush();
        if(i == 9999) {
            scheduler.resume();
            i=0;
        }
    }
}
