/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              P L U G B O X                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Abstraktion einer Interruptvektortabelle. Damit kann man die Behandlungs- */
/* routine fuer jeden Hardware-, Softwareinterrupt und jede Prozessor-       */
/* exception festlegen.                                                      */
/*****************************************************************************/

#include "machine/plugbox.h"

Plugbox plugbox;

Plugbox::Plugbox() : m_slots{&panic} {}

void Plugbox::assign(unsigned int slot, Gate& gate) {
  if (slot < PLUGBOX_SLOT_COUNT && slot > 0) {
    m_slots[slot] = &gate;
  }
}

Gate& Plugbox::report(unsigned int slot) {
  if (slot < PLUGBOX_SLOT_COUNT && slot > 0) {
    return *m_slots[slot];
  }
  return panic;
}
