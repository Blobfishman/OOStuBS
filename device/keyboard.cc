/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                            K E Y B O A R D                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Tastaturtreiber.                                                          */
/*****************************************************************************/

#include "device/keyboard.h"
#include "machine/cgascr.h"
#include "machine/pic.h"
#include "machine/plugbox.h"

void Keyboard::plugin() {
  plugbox.assign(Plugbox::keyboard, *this);

  pic.allow(PIC::keyboard);
}

void Keyboard::trigger() {
  Key key = this->key_hit();
  if (key.valid()) {
    CGA_Screen screen;
    screen.show(0, 0, key.ascii(), 3);
  }
  // TODO: Bei Ctrl-Alt-Del ein Reboot auslösen
}
