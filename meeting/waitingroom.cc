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

#include "device/cgastr.h"
#include "machine/cpu.h"
#include "syscall/guarded_organizer.h"

Waitingroom::Waitingroom() {}

Waitingroom::~Waitingroom() {
    Customer* customer = (Customer*)dequeue();
    while (customer != nullptr) {
        organizer.wakeup(*customer);
        customer = (Customer*)dequeue();
    }
}

void Waitingroom::remove(Customer* customer) {
    if (customer == nullptr) {
        kout << "PANIC: Unexpected nullptr object of Customer in "
             << __PRETTY_FUNCTION__;
        kout.flush();
        cpu.halt();
    }
    Queue::remove((Chain*)customer);
}
