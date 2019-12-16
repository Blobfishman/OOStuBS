/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              G U A R D I A N                              */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Zentrale Unterbrechungsbehandlungsroutine des Systems.                    */
/* Der Parameter gibt die Nummer des aufgetretenen Interrupts an.            */
/*****************************************************************************/

/* INCLUDES */
#include "machine/plugbox.h"
#include "guard/guard.h"
#include "machine/cpu.h"
/* FUNKTIONEN */

extern "C" void guardian(unsigned int slot);

/* GUARDIAN: Low-Level Interrupt-Behandlung. */

void guardian(unsigned int slot) { 
    Gate &gate = plugbox.report(slot);
    if (gate.prologue()) {
       guard.relay(&gate); 
    }
}
