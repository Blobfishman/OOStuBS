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

Keyboard::Keyboard() : m_semaphore(0) {}

void Keyboard::plugin() {
    plugbox.assign(Plugbox::keyboard, *this);

    pic.allow(PIC::keyboard);
}

void Keyboard::epilogue() {
    if (m_buffer.peek() != Key()) {
        m_semaphore.signal();
    }
}

bool Keyboard::prologue() {
    Key key = this->key_hit();
    if (key.valid()) {
        if (key.ctrl() & key.alt() & (key.scancode() == Key::scan::del)) {
            reboot();
        }
        m_buffer.produce(key);
        return true;
    }
    return false;
}

Key Keyboard::getkey() {
    m_semaphore.wait();
    return m_buffer.consume();
}
