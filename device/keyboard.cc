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
#include "machine/pic.h"
#include "machine/plugbox.h"
#include "device/cgastr.h"

Keyboard keyboard;

Keyboard::Keyboard() {

}

void Keyboard::plugin() {
  plugbox.assign(Plugbox::keyboard, *this);

  pic.allow(PIC::keyboard);
}

void Keyboard::trigger() {
  Key key = this->key_hit();
  if (key.valid()) {
    kout.show(4, 4, key.ascii(), 7);
  }
  // TODO: Bei Ctrl-Alt-Del ein Reboot auslösen
}
