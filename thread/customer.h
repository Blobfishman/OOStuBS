/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                         C U S T O M E R                                   */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Ein Thread, der auf ein Ereignis warten kann.                             */
/*****************************************************************************/

#ifndef __customer_include__
#define __customer_include__

#include "meeting/waitingroom.h"
#include "thread/entrant.h"

class Customer : public Entrant {
   private:
    Customer(const Customer& copy);  // Verhindere Kopieren

    Waitingroom* m_waitingroom;

   public:
    Customer(void* tos) : Entrant(tos), m_waitingroom(nullptr) {}

    void waiting_in(Waitingroom* w) { m_waitingroom = w; }

    Waitingroom* waiting_in() { return m_waitingroom; }
};

#endif
