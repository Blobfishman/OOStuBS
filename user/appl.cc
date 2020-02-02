/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                         A P P L I C A T I O N                             */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Die Klasse Application definiert die einzige Anwendung von OO-Stubs.      */
/*****************************************************************************/

/* INCLUDES */

#include "user/appl.h"

#include "device/cgastr.h"
#include "syscall/guarded_keyboard.h"
#include "syscall/guarded_organizer.h"

Application::Application(void* stack)
    : Thread(stack) {}

void Application::action() {
    kout << __PRETTY_FUNCTION__ << endl;
    kout.flush();
    while (true) {
        Key key = keyboard.getkey();
        kout << (char)key;
        kout.flush();
    }
}
