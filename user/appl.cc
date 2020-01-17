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
#include "syscall/guarded_scheduler.h"

Application::Application(void* stack, Thread* kill_target)
    : Thread(stack), m_kill_target(kill_target) {}

void Application::action() {
    int i = 0;
    while (true) {
        kout.show(4,4, 'A', 3);
        i++;
        if (i == 30000000 && m_kill_target != nullptr) {
            scheduler.kill(*m_kill_target);
            m_kill_target = nullptr;
        }
    }
}
