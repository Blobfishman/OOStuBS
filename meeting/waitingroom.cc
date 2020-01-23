/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                        W A I T I N G R O O M                              */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Liste von Threads, die auf ein Ereignis warten.                           */
/*****************************************************************************/

#include "meeting/waitingroom.h"

#include "syscall/guarded_organizer.h"

Waitingroom::Waitingroom() {}

Waitingroom::~Waitingroom() {
    while ((Customer* customer = (Customer*)Queue::dequeue()) != nullptr) {
        organizer.wakeup(customer);
    }
}

void Waitingroom::remove(Customer* customer) {
    Queue::remove((Chain*)customer);
}
