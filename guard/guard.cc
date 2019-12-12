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
    retne();

    while(m_epiqueue.is_empty()) {
        cpu.disable_int();
        Gate* gate = (Gate*)m_epiqueue.dequeue();
        cpu.enable_int(); 
        gate->epilogue();
        gate->queued(false);
    }
}

void Guard::relay(Gate* item) {
    if (item->queued()) {
        // Item mehrfach hinzugefuegt
        return;
    }
    if (m_locked) {
        m_epiqueue.enqueue(item);
        item->queued(true);
    } else {
        cpu.enable_int();
        item->epilogue();
    }
}
