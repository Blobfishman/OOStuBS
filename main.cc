/* $Id: main.cc 8485 2017-03-27 11:50:06Z friesel $ */

#include "device/cgastr.h"
#include "machine/keyctrl.h"

int main() {
    CGA_Stream kout;
    CGA_Screen osstream;

    int neg_number = -3;
    int number = 3;

    kout << endl;
    kout.flush();
    kout << "| sys/zahl |     " << number << "          |     " << neg_number
         << "          |" << endl;
    kout.flush();
    kout << "| dec      |     " << dec << number << "          |     "
         << neg_number << "          |" << endl;
    kout.flush();
    kout << "| hex      |   " << hex << number << "   |     " << neg_number
         << "  |" << endl;
    kout.flush();
    kout << "| oct      |  " << oct << number << " |   " << neg_number << " |"
         << endl;
    kout.flush();
    kout << "| Bin+     | " << bin << number << "  |" << endl;
    kout.flush();
    kout << "| Bin-     | " << neg_number << "  |" << endl;
    kout.flush();

    Keyboard_Controller controller;
    Key key_pressed;

    controller.set_repeat_rate(30, 3);
    bool flag = true;
    bool repeat = true;

    kout << "Nur noch Keyboard-Eingabe ohne Buffer direkt zu flushen" << endl;
    kout.flush();
    while (flag) {
        key_pressed = controller.key_hit();
        if (key_pressed.valid()) {
            kout << key_pressed.ascii();
            if (key_pressed.ascii() == 49) {
                flag = false;
            }
        }
    }
    kout << endl;
    kout.flush();

    flag = true;
    while (flag) {
        key_pressed = controller.key_hit();
        if (key_pressed.valid()) {
            // mit taste 2 die repeat rate aendern
            if (key_pressed.ascii() == 50) {
                if (repeat) {
                    controller.set_repeat_rate(0, 0);
                    repeat = false;

                } else {
                    controller.set_repeat_rate(30, 3);
                    repeat = true;
                }
            } else {
                kout << key_pressed.ascii();
                kout.flush();
            }

            if (key_pressed.ascii() == 49) {
                flag = false;
            }
        }
    }
    kout << endl;
    kout.flush();

    kout << "Ende der Eingabe bitte rebooten" << endl;
    kout.flush();

    return 0;
}

