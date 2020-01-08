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

Application::Application(Entrant* kill_target)
    : Entrant(m_stack + 1000), m_kill_target(kill_target) {}

void Application::action() {
    int i = 0;
    int x = 1;
    int y = 1;
    while (true) {
        // Secure secure;
        kout.setpos(x, y);
        kout << "A" << i++;
        kout.flush();
        if (i == 300000 && m_kill_target != nullptr) {
            scheduler.kill(*m_kill_target);
            m_kill_target = nullptr;
        }
        if (i % 9999 == 0) {
            scheduler.resume();
        }
    }
}
