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

Loop::Loop(void* stack, int x, bool ex) : Thread(stack), m_x(x), m_exit(ex) {}

void Loop::action() {
    int i = 0;
    kout << __PRETTY_FUNCTION__ << endl;
    kout.flush();
    while (true) {
        kout.show(8, 8, m_x + '0', m_x);
    }
}
