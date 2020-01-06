/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                 L O O P                                   */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Loop ist ein Thread, der nichts weiter tut als einen Zaehler hochzu-      */
/* zaehlen und dies auf dem Bildschirm anzuzeigen. Zwischendurch gibt er     */
/* den Prozessor ab. Der Scheduler bestimmt dann, welcher Thread als         */
/* naechstes laufen soll.                                                    */
/*****************************************************************************/

/* INCLUDES */

#include "user/loop.h"

#include "device/cgastr.h"
#include "device/keyboard.h"
#include "guard/secure.h"
#include "machine/cpu.h"
#include "thread/scheduler.h"

Loop::Loop(int x, int y) : Entrant(m_stack + 1000), m_x(x), m_y(y) {
    keyboard.plugin();
    cpu.enable_int();
}

void Loop::action() {
    int i = 0;
    while (true) {
        // Secure secure;
        kout.setpos(m_x, m_y);
        kout << i++;
        kout.flush();
        if (i % 9999 == 0) {
            scheduler.resume();
        }
    }
}
