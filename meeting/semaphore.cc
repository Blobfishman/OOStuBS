/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                           S E M A P H O R E                               */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Semaphore werden zur Synchronisation von Threads verwendet.               */
/*****************************************************************************/

#include "meeting/semaphore.h"

#include "syscall/guarded_organizer.h"

Semaphore::Semaphore(int c) : m_count(c) {}

void Semaphore::p() {
    if (m_count > 0) {
        m_count--;
    } else {
        Customer* customer = (Customer*)organizer.active();
        enqueue(customer);
        organizer.block(*customer, *this);
    }
}

void Semaphore::v() {
    Chain* item;
    if ((item = this->dequeue())) {
        organizer.wakeup(*(Customer*)item);
    } else {
        m_count++;
    }
}
