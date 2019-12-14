/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                  G A T E                                  */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Klasse von Objekten, die in der Lage sind, Unterbrechungen zu behandeln.  */
/*****************************************************************************/

#ifndef __Gate_include__
#define __Gate_include__

#include "object/chain.h"

class Gate : public Chain {
   private:
    Gate(const Gate& copy) = default;

   public:
    Gate() : m_queued(false) {}
    virtual bool prologue() = 0;
    virtual void epilogue() = 0;
    void queued(bool q) { m_queued = q; }
    bool queued() { return m_queued; }

   private:
    bool m_queued;
};

#endif
