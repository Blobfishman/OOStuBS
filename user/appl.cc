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

CPU cpu;

Application::Application() : Coroutine(m_stack) {
    keyboard.plugin();
    cpu.enable_int();
}

void Application::action() {
    int i = 0;
    int x,y;
    kout.getpos(x, y);
    while (true) {
        Secure secure;
        kout.setpos(x, y);
        kout << i++;
        kout.flush();
    }
}
