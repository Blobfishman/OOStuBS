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
#include "user/appl.h"

Keyboard keyboard;

Keyboard::Keyboard() {}

void Keyboard::plugin() {
	plugbox.assign(Plugbox::keyboard, *this);

	pic.allow(PIC::keyboard);
}

void Keyboard::trigger() {
	Key key = this->key_hit();
	if (key.valid()) {
		if (key.ctrl() & key.alt() &
		    (key.scancode() == Key::scan::del)) {
			keyboard.reboot();
		} else {
			if(key.ascii() == '1'){
				flag = false;	
			}
			int x, y;
			kout.getpos(x, y);
			kout.setpos(5, 10);
			kout << key.ascii();
			kout.flush();
			kout.setpos(x, y);
		}
	}
}
