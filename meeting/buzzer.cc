/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                               B U Z Z E R                                 */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Mit Hilfe des "Weckers" koennen Prozesse eine bestimmte Zeit lang         */
/* schlafen und sich dann wecken lassen.                                     */
/*****************************************************************************/

/* INCLUDES */

#include "meeting/buzzer.h"

#include "device/cgastr.h"
#include "meeting/bellringer.h"
#include "syscall/guarded_organizer.h"

Buzzer::Buzzer() {}

Buzzer::~Buzzer() { bellringer.cancel(this); }

void Buzzer::ring() {
    Customer* customer = (Customer*)dequeue();
    while (customer != nullptr) {
        organizer.wakeup(*customer);
        customer = (Customer*)dequeue();
    }
}

void Buzzer::set(int ms) { bellringer.job(this, ms); }

void Buzzer::sleep() {
    organizer.block(*((Customer*)(organizer.active())), *this);
}
