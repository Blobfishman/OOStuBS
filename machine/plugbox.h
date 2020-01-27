/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              P L U G B O X                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Abstraktion einer Interruptvektortabelle. Damit kann man die Adresse der  */
/* Behandlungsroutine fuer jeden Hardware-, Softwareinterrupt und jede       */
/* Prozessorexception festlegen.                                             */
/*****************************************************************************/

#ifndef __Plugbox_include__
#define __Plugbox_include__

#include "device/panic.h"
#include "guard/gate.h"

#define PLUGBOX_SLOT_COUNT 64

extern Panic panic;

class Plugbox {
   private:
    Plugbox(const Plugbox& copy);  // Verhindere Kopieren

    Gate* m_slots[PLUGBOX_SLOT_COUNT];

   public:
    Plugbox();

    enum { timer = 32, keyboard = 33 };

    void assign(unsigned int slot, Gate& gate);

    Gate& report(unsigned int slot);
};

extern Plugbox plugbox;

#endif
