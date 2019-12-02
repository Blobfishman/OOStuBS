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
#include "device/cgastr.h"
#include "machine/pic.h"
#include "machine/plugbox.h"

Keyboard keyboard;

Keyboard::Keyboard() {}

void Keyboard::plugin() {
	plugbox.assign(Plugbox::keyboard, *this);

	pic.allow(PIC::keyboard);
}

void Keyboard::trigger() {
	Key key = this->key_hit();
	if (key.valid()) {
			if (key.ctrl() & key.alt() & (key.scancode() == Key::scan::del)) {
			keyboard.reboot();
		} else {
			kout.show(4, 4, key.ascii(), 7);
		}
	}
}
