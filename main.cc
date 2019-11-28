/* $Id: main.cc 8485 2017-03-27 11:50:06Z friesel $ */

#include "device/cgastr.h"
#include "machine/cpu.h"
#include "machine/keyctrl.h"
#include "machine/pic.h"

int main() {
  PIC p;
  p.allow(PIC::timer);
  CPU cpu;
  cpu.enable_int();
  while (true) {
  }
}
