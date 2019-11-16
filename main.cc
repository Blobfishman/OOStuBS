/* $Id: main.cc 8485 2017-03-27 11:50:06Z friesel $ */

#include "device/cgastr.h"
#include "machine/keyctrl.h"

int main() {
    CGA_Stream kout;
    CGA_Screen osstream;

    long neg_number = -20000;
    long number = 20000;

    kout << endl;
    kout.flush();
    kout << "| sys/zahl |     20000      |     -20000      |" << endl;
    kout.flush();
    kout << "| dec      |     " << dec << number << "      |     " << neg_number
         << "      |" << endl;
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

    kout << bin << 1 << endl;

    kout << "Nur noch Keyboard-Eingabe" << endl;
    kout.flush();
    while (true) {
        key_pressed = controller.key_hit();
        if (key_pressed.valid()) {
            kout << key_pressed.ascii();
            kout.flush();
        }
    }

    return 0;
}

