/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                  P I C                                    */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Programmable Interrupt Controller.                                        */
/* Mit Hilfe des PICs koennen Hardware-Unterbrechungen einzeln zugelassen    */
/* oder unterdrueckt werden. Auf diese Weise wird also bestimmt, ob die      */
/* Unterbrechung eines Geraetes ueberhaupt an den Prozessor weitergegeben    */
/* wird. Selbst dann erfolgt eine Aktivierung der Unterbrechungsroutine nur, */
/* wenn der Prozessor bereit ist, auf Unterbrechungen zu reagieren. Dies     */
/* kann mit Hilfe der Klasse CPU festgelegt werden.                          */
/*****************************************************************************/

#include "pic.h"
#include "machine/io_port.h"

#define IMR1 0x21
#define IMR2 0xa1
const int PIC2_MAX_INDEX = 15;
const int PIC2_MIN_INDEX = 8;
const int PIC1_MAX_INDEX = 7;
const int PIC1_MIN_INDEX = 0;

PIC pic;

PIC::PIC() {
    for (int i = PIC1_MIN_INDEX; i <= PIC2_MAX_INDEX; i++) {
        forbid(i);
    }
}

void PIC::allow(int interrupt_device) {
    if (interrupt_device <= PIC1_MAX_INDEX &&
        interrupt_device >= PIC1_MIN_INDEX) {
        IO_Port imr(IMR1);
        int val = imr.inb();
        val ^= 0x01 << interrupt_device;
        imr.outb(val);

    } else if (interrupt_device >= PIC2_MIN_INDEX &&
               interrupt_device <= PIC2_MAX_INDEX) {
        IO_Port imr(IMR2);
        int val = imr.inb();
        val ^= 0x01 << (interrupt_device - PIC2_MIN_INDEX);
        imr.outb(val);
    }
    // if interrupt_device out of range ignore it
}

void PIC::forbid(int interrupt_device) {
    if (interrupt_device <= PIC1_MAX_INDEX &&
        interrupt_device >= PIC1_MIN_INDEX) {
        IO_Port imr(IMR1);
        int val = imr.inb();
        val |= 0x01 << interrupt_device;
        imr.outb(val);
    } else if (interrupt_device >= PIC2_MIN_INDEX &&
               interrupt_device <= PIC2_MAX_INDEX) {
        IO_Port imr(IMR2);
        int val = imr.inb();
        val |= 0x01 << (interrupt_device - PIC2_MIN_INDEX);
        imr.outb(val);
    }
    // if interrupt_device out of range ignore it
}

bool PIC::is_enabled(int interrupt_device) {
    if (interrupt_device <= PIC1_MAX_INDEX &&
        interrupt_device >= PIC1_MIN_INDEX) {
        IO_Port imr(IMR1);
        int val = imr.inb();
        int bit = 0x01 << interrupt_device;
        val &= bit;
        return val != bit;
    } else if (interrupt_device >= PIC2_MIN_INDEX &&
               interrupt_device <= PIC2_MAX_INDEX) {
        IO_Port imr(IMR2);
        int val = imr.inb();
        int bit = 0x01 << (interrupt_device - PIC2_MIN_INDEX);
        val &= bit;
        return val != bit;
    }
    return false;
}
