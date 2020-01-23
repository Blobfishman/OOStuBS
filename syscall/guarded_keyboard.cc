/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                   G U A R D E D _ K E Y B O A R D                         */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Systemaufrufschnittstelle zur Tastatur.                                   */
/*****************************************************************************/

#include "syscall/guarded_keyboard.h"
#include "guard/secure.h"

Guarded_Keyboard keyboard;

Key Guarded_Keyboard::getkey() {
    Secure secure;
    return Keyboard::getkey();
}

