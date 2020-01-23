/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                           S E M A P H O R E                               */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Semaphore werden zur Synchronisation von Threads verwendet.               */
/*****************************************************************************/

#include "syscall/guarded_organizer.h"
#include "thread/dispatch.h"

Semaphore::Semaphore(int c) : m_count(c) {}

void Semaphore::p() {
    if (m_count > 0) {
        m_count--;
    } else {
        Customer* customer = (Customer*)dispatcher.active();
        enqueue(customer);
        organizer.block(*customer, *this);
    }
}

void Semaphore::v() {
    if (is_empty()) {
        Customer* customer = (Customer*)dequeue();
        organizer.wakeup(*customer);

    } else {
        m_count++;
    }
}

void Semaphore::wait() { p(); }

void Semaphore::signal() { v(); }
