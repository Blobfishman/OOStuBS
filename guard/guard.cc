/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                G U A R D                                  */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Mit Hilfe dieser Klasse koennen Aktivitaeten, die einen kritischen        */
/* Abschnitt betreffen, der mit einem Guard-Objekt geschuetzt ist, mit       */
/* Unterbrechungsbehandlungsroutinen synchronisiert werden, die ebenfalls    */
/* auf den kritischen Abschnitt zugreifen.                                   */
/*****************************************************************************/

#include "guard.h"

Guard guard;

void Guard::leave() {
    while (m_epiqueue.is_empty()) {
        cpu.disable_int();
        Gate* gate = m_epiqueue.dequeue();
        gate->queued(false);
        cpu.enable_int();
        gate->epilogue();
        cpu.disable_int();
    }
    retne();
    cpu.enable_int();
}

void Guard::relay(Gate* item) {
    if (item->queued()) {
        // Item mehrfach hinzugefuegt
        return;
    }
    if (m_locked) {
        cpu.enable_int(); 
        m_epiqueue.enqueue(item);
        item->queued(true);
        cpu.disable_int(); 
    } else {
        cpu.enable_int();
        item->epilogue();
    }
}
