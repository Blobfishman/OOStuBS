/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              W A T C H                                    */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/*****************************************************************************/

#include "device/watch.h"

#include "machine/cgascr.h"
#include "machine/pic.h"
#include "machine/plugbox.h"
#include "syscall/guarded_organizer.h"

void Watch::windup() {
    plugbox.assign(Plugbox::timer, *this);
    pic.allow(PIC::timer);
}

bool Watch::prologue() {
    if (++m_current_time >= INTERRUPT_COUNT_MAX) {
        m_current_time = 0;
        return true;
    } else {
        return false;
    }
}

void Watch::epilogue() { 
    organizer.Scheduler::resume(); 
}
