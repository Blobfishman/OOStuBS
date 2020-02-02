/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                 B E L L                                   */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Eine "Glocke" ist eine abstrakte Basisklasse, die das Ausloesen einer     */
/* Aktivitaet nach einer bestimmten Wartezeit erlaubt.                       */
/* Dazu besitzt sie einen Zaehler, der vom "Gloeckner" (Bellringer) ver-     */
/* waltet wird.                                                              */
/*****************************************************************************/

#ifndef __Bell_include__
#define __Bell_include__

#include "object/chain.h"

class Bell : public Chain {
   private:
    Bell(const Bell &copy);  // Verhindere Kopieren

    int m_count{0};

   public:
    Bell() {}

    void wait(int value) { m_count = value; }
    int wait() { return m_count; }
    void tick() { m_count--; }
    bool run_down() { return m_count <= 0; }
    virtual void ring() = 0;
};

#endif
