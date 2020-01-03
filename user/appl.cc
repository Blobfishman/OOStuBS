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
#include "device/keyboard.h"
#include "guard/secure.h"
#include "machine/cpu.h"
#include "thread/dispatch.h"

CPU cpu;
extern Application app1;
extern Application app2;
int n =0;
int turn = 0;

Application::Application() : Coroutine(m_stack+ 1000) {
    keyboard.plugin();
    cpu.enable_int();
}

void Application::action() {
    int i = 0;
    int x,y;
    kout.getpos(x, y);
    while (true) {
        //Secure secure;
        kout.setpos(x, y);
        kout << i++ << endl;
        kout.flush();

        if(i == 999){
            if(dispatcher.active() == &app1) {
                y=y+1;
                dispatcher.dispatch(app2);
                i=0;
            }
            if(dispatcher.active() == &app2) {
                y=y+1;
                dispatcher.dispatch(app1);
                i=0;
            }
        }
    }
}
