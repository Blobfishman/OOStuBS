/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                 P A N I C                                 */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Standard Unterbrechungsbehandlung.                                        */
/*****************************************************************************/

#include "device/panic.h"
#include "device/cgastr.h"
#include "machine/cpu.h"

Panic panic;

void Panic::trigger() {
  cga_stream << "PANIC: Unexpected Interrupt!";
  CPU cpu;
  cpu.halt();
}
