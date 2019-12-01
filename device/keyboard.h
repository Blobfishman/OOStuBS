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

class Keyboard : public Gate, public Keyboard_Controller {
 private:
  Keyboard(const Keyboard &copy);  // Verhindere Kopieren

 public:
  Keyboard();
  // PLUGIN: 'Anstoepseln' der Tastatur. Ab sofort werden Tasten erkannt.
  void plugin();

  void trigger();
};

extern Keyboard keyboard;

#endif
