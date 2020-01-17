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
#include "machine/cpu.h"
#include "syscall/guarded_scheduler.h"

Loop::Loop(void* stack, int x, bool ex) : Thread(stack), m_x(x), m_exit(ex) {}

void Loop::action() {
    int i = 0;
    while (true) {
        if (i == 10000000 && m_exit) {
            scheduler.exit();
        }
        kout.show(4,4, m_x + '0', 6);
        i++;
        if (i % 100000 == 0 && m_exit) {
            scheduler.resume();
        }
    }
}
