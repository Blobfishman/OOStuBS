/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                            K E Y B O A R D                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Tastaturtreiber.                                                          */
/*****************************************************************************/

#ifndef __Keyboard_include__
#define __Keyboard_include__

#include "guard/gate.h"
#include "machine/key.h"
#include "machine/keyctrl.h"
#include "meeting/semaphore.h"
#include "util/bounded_buffer.h"

class Keyboard : public Gate, public Keyboard_Controller {
   private:
    Keyboard(const Keyboard &copy);  // Verhindere Kopieren

   public:
    Keyboard();

    void plugin();

    bool prologue();

    void epilogue();

    Key getkey();

   private:
    BoundedBuffer<Key, 10> m_buffer;
    Semaphore m_semaphore;
};

#endif
