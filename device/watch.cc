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
#include "meeting/bellringer.h"
#include "syscall/guarded_organizer.h"

void Watch::windup() {
    plugbox.assign(Plugbox::timer, *this);
    pic.allow(PIC::timer);
}

bool Watch::prologue() {
    ++m_current_time;
    return true;
}

void Watch::epilogue() {
    if (m_current_time >= INTERRUPT_COUNT_MAX) {
        m_current_time = 0;
        organizer.Scheduler::resume();
    }
    bellringer.check();
}
