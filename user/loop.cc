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

Loop::Loop(int x, int y, bool ex)
    : Entrant(m_stack + 1000), m_x(x), m_y(y), m_exit(ex) {}

void Loop::action() {
    int i = 0;
    while (true) {
        if (i == 100000 && m_exit) {
            scheduler.exit();
        }
        kout.setpos(m_x, m_y);
        kout << "Loop" << i++;
        kout.flush();
        if (i % 9999 == 0) {
            scheduler.resume();
        }
    }
}
