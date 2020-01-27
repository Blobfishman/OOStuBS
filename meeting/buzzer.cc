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
#include "syscall/guarded_organizer.h"
#include "meeting/bellringer.h"

Buzzer::~Buzzer() { bellringer.cancel(this); }

void Buzzer::ring() {
    Customer* customer = nullptr;
    while ((customer = (Customer*)dequeue()) != nullptr) {
        organizer.wakeup(*customer);
    }
}

void Buzzer::set(int ms) {
    m_ticks = ms;  // Muss möglicherweise noch umgerechnet werden
}

void Buzzer::sleep() { bellringer.job(this, m_ticks); }
