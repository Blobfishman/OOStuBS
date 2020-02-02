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

#include "device/cgastr.h"
#include "machine/cpu.h"
#include "syscall/guarded_organizer.h"

Semaphore::Semaphore(int c) : m_count(c) {}

void Semaphore::p() {
    if (m_count > 0) {
        m_count--;
    } else {
        Customer* customer = (Customer*)organizer.active();
        if (customer == nullptr) {
            kout << "PANIC: Unexpected nullptr object of Customer in "
                 << __PRETTY_FUNCTION__;
            kout.flush();
            cpu.halt();
        }
        organizer.block(*customer, *this);
    }
}

void Semaphore::v() {
    Chain* item;
    if ((item = this->dequeue())) {
        if (item == nullptr) {
            kout << "PANIC: Unexpected nullptr object of Customer in "
                 << __PRETTY_FUNCTION__;
            kout.flush();
            cpu.halt();
        }
        organizer.wakeup(*(Customer*)item);
    } else {
        m_count++;
    }
}
