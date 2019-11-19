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

    kout << "Nur noch Keyboard-Eingabe (1 -> Buffer, 2-> repeate rate)" << endl;
    kout.flush();


    bool key_flag = true;
    bool buffer_flag = false;
    bool repeat = true;
    char c = ' ';
    char *p= 0;

    while (true) {
        key_pressed = controller.key_hit();

        if (key_pressed.valid()) {
            // bei der taste 1 wird der buffer benutzt oder nicht
            if (key_pressed.ascii() == 49)
            {
                if (key_flag)
                {
                    buffer_flag = true;
                    key_flag = false;

                    kout << endl;kout.flush();
                    kout << "Buffer einschalten" << endl;
                    kout.flush();

                }else
                {
                    buffer_flag = false;
                    key_flag = true;

                    kout << endl;kout.flush();
                    kout << "Buffer ausschalten" << endl;
                    kout.flush();

                }
            // bei 2 wird die repeat rate geändert
            }else if (key_pressed.ascii() == 50)
            {
                if (repeat)
                {
                    controller.set_repeat_rate(0, 0);
                    repeat = false;

                } else {
                    controller.set_repeat_rate(30, 3);
                    repeat = true;
                }
            }else
            {
                if (buffer_flag)
                {
                    kout << key_pressed.ascii();
                    
                }else
                {
                    c = key_pressed.ascii();
                    p = &c;
                    osstream.print(p , 1, 3);
                }
            }
        }
    }
    return 0;
}

