/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                               B U Z Z E R                                 */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Mit Hilfe des "Weckers" koennen Prozesse eine bestimmte Zeit lang         */
/* schlafen und sich dann wecken lassen.                                     */
/*****************************************************************************/

#ifndef __Buzzer_include__
#define __Buzzer_include__

#include "meeting/bell.h"
#include "meeting/waitingroom.h"

class Buzzer : public Waitingroom, public Bell {
   private:
    Buzzer(const Buzzer &copy);  // Verhindere Kopieren

   public:
    Buzzer();
    virtual ~Buzzer();
    virtual void ring();
    void set(int ms);
    void sleep();
};

#endif
