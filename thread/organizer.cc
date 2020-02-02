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

#include "device/cgastr.h"
#include "machine/cpu.h"

void Organizer::block(Customer& customer, Waitingroom& waitingroom) {
    waitingroom.enqueue(&customer);
    customer.waiting_in(&waitingroom);
    Scheduler::exit();
}

void Organizer::wakeup(Customer& customer) {
    Waitingroom* room = customer.waiting_in();
    if (room == nullptr) {
        // Unerwarteter nullptr
        kout << "PANIC: Unexpected nullptr object of waitingroom in "
             << __PRETTY_FUNCTION__;
        kout.flush();
        cpu.halt();
    }
    room->remove(&customer);
    customer.waiting_in(nullptr);
    ready(customer);
}

void Organizer::kill(Customer& that) {
    if (that.waiting_in() == nullptr) {
        Scheduler::kill(that);
    } else {
        Waitingroom* room = that.waiting_in();
        if (room == nullptr) {
            // Unerwarteter nullptr
            kout << "PANIC: Unexpected nullptr object of waitingroom in "
                 << __PRETTY_FUNCTION__;
            kout.flush();
            cpu.halt();
        }
        room->remove(&that);
        that.waiting_in(nullptr);
    }
}
