/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                          O R G A N I Z E R                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Ein Organizer ist ein spezieller Scheduler, der zusaetzlich das Warten    */
/* von Threads (Customer) auf Ereignisse erlaubt.                            */
/*****************************************************************************/

#include "thread/organizer.h"

void Organizer::block(Customer& customer, Waitingroom& waitingroom) {
    waitingroom.enqueue(&customer);
    customer.waiting_in(&waitingroom);
    exit();
}

void Organizer::wakeup(Customer& customer) {
    ready(customer);
    Waitingroom* room = customer.waiting_in();
    room->remove(&customer);
    customer.waiting_in(nullptr);
}

void Organizer::kill(Customer& that) {
    if (that.waiting_in() == nullptr) {
        Scheduler::kill(that);
    } else {
        Waitingroom* room = that.waiting_in();
        room->remove(&that);
        that.waiting_in(nullptr);
    }
}
