/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                    G U A R D E D _ O R G A N I Z E R                      */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Systemaufrufschnittstelle zum Organizer.                                  */
/*****************************************************************************/

#include "syscall/guarded_organizer.h"

#include "guard/secure.h"

Guarded_Organizer organizer;

void Guarded_Organizer::ready(Thread& that) {
    Secure secure;
    Scheduler::ready(that);
}

void Guarded_Organizer::exit() {
    Secure secure;
    Scheduler::exit();
}

void Guarded_Organizer::kill(Thread& that) {
    Secure secure;
    Scheduler::kill(that);
}

void Guarded_Organizer::resume() {
    Secure secure;
    Scheduler::resume();
}
