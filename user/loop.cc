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

Loop::Loop(void* stack, int x, bool ex) : Thread(stack), m_x(x), m_exit(ex) {}

void Loop::action() {
}
