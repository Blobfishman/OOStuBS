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

PIC pic;

void PIC::allow(int interrupt_device) {
  if (interrupt_device < 8 && interrupt_device >= 0) {
    IO_Port imr(IMR1);
    int val = imr.inb();
    val ^= 0x01 << interrupt_device;
    imr.outb(val);

  } else if (interrupt_device > 7 && interrupt_device < 16) {
    IO_Port imr(IMR2);
    int val = imr.inb();
    val ^= 0x01 << interrupt_device;
    imr.outb(val);
  }
  // if interrupt_device out of range ignore it
}

void PIC::forbid(int interrupt_device) {
  if (interrupt_device < 8 && interrupt_device >= 0) {
    IO_Port imr(IMR1);
    int val = imr.inb();
    val |= 0x01 << interrupt_device;
    imr.outb(val);
  } else if (interrupt_device > 7 && interrupt_device < 16) {
    IO_Port imr(IMR2);
    int val = imr.inb();
    val |= 0x01 << interrupt_device;
    imr.outb(val);
  }
  // if interrupt_device out of range ignore it
}

bool PIC::is_masked(int interrupt_device) {
  if (interrupt_device < 8 && interrupt_device >= 0) {
    IO_Port imr(IMR1);
    int val = imr.inb();
    int bit = 0x01 << interrupt_device;
    val &= bit;
    return val != bit;
  } else if (interrupt_device > 7 && interrupt_device < 16) {
    IO_Port imr(IMR2);
    int val = imr.inb();
    int bit = 0x01 << interrupt_device;
    val &= bit;
    return val != bit;
  }
  return false;
}
