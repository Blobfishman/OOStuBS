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

void Panic::epilogue() {}

bool Panic::prologue() {
    kout << "PANIC: Unexpected Interrupt!";
    cpu.halt();
    return false;
}
