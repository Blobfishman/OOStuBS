/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                  P I T                                    */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Programmable Interval Timer.                                              */
/*****************************************************************************/

#include "machine/pit.h"
#include "machine/io_port.h"

#define PIT1_COUNTER_0 0x40
#define PIT1_CONTROL 0x43

void PIT::interval(int us) {
    m_time = us;
    int value = (us * 1000) / 838;

    IO_Port pit_counter(PIT1_COUNTER_0);
    IO_Port pit_control(PIT1_CONTROL);

    pit_control.outb(0b00110100);

    pit_counter.outb(value);
    pit_counter.outb(value >> 8);
}
