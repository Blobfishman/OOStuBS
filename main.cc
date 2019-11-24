/* $Id: main.cc 8485 2017-03-27 11:50:06Z friesel $ */

#include "device/cgastr.h"
#include "machine/keyctrl.h"

int main() {
    CGA_Stream kout;
    CGA_Screen osstream;

    short neg_short = -1;
    unsigned short u_short = 1;
    short normal_short =1;

/*     kout << endl; */
/*     kout.flush(); */
/*     kout << "| sys/zahl | (short) " << normal_short << " | (unsigned short) " << u_short << " | (short) " << neg_short << " | " << endl; */
/*     kout.flush(); */
/*     kout << "| dec      |" << dec << normal_short << " | " << u_short << " | " << neg_short << " | " << endl; */
/*     kout.flush(); */
/*     kout << "| hex      | " << hex << normal_short << "     | " << u_short << "     | "  << neg_short << "     | " << endl; */
/*     kout.flush(); */
/*     kout << "| oct      | " << oct << normal_short << " | " << u_short << " | " << neg_short << " | " << endl; */
/*     kout.flush(); kout << endl; */
/*     kout << "| Bin+     | (short)          " << bin << normal_short << " | " << endl; */
/*     kout.flush(); */
/*     kout << "| Bin+     | (unsigned short) " << bin << u_short << " | " << endl; */
/*     kout.flush(); */
/*     kout << "| Bin-     | (short)          " << neg_short << " | " << endl; */
/*     kout.flush(); */

    int neg_int = -1;
    unsigned int u_int = 1;
    int normal_int =1;

    /* kout << endl; */
    /* kout.flush(); */
    /* kout << "| sys/zahl | (int) " << normal_int << " | (unsigned int) " << u_int << " | (int) " << neg_int << " | " << endl; */
    /* kout.flush(); */
    /* kout << "| dec      |" << dec << normal_int << " | " << u_int << " | " << neg_int << " | " << endl; */
    /* kout.flush(); */
    /* kout << "| hex      | " << hex << normal_int << "     | " << u_int << "     | "  << neg_int << "     | " << endl; */
    /* kout.flush(); */
    /* kout << "| oct      | " << oct << normal_int << " | " << u_int << " | " << neg_int << " | " << endl; */
    /* kout.flush(); kout << endl; */
    /* kout << "| Bin+     | (int)          " << bin << normal_int << " | " << endl; */
    /* kout.flush(); */
    /* kout << "| Bin+     | (unsigned int) " << bin << u_int << " | " << endl; */
    /* kout.flush(); */
    /* kout << "| Bin-     | (int)          " << neg_int << " | " << endl; */
    /* kout.flush(); */
    
    long neg_long =-1;
    unsigned long u_long=1;
    long normal_long =1;
    
    kout << endl;
    kout.flush();
    kout << "| dec (long)   |" << dec << normal_long << endl;
    kout.flush();
    kout << "| dec (u_long) |" << dec << u_long << endl;
    kout.flush();
    kout << "| dec (long)   |" << dec << neg_long << endl;
    kout.flush();

    kout << "| hex (long)   | " << hex << normal_long << endl;
    kout.flush();
    kout << "| hex (u_long) | " << hex << u_long << endl;
    kout.flush();
    kout << "| hex (long)   | " << hex << neg_long << endl;
    kout.flush();

    kout << "| oct (long)   | " << oct << normal_long << endl;
    kout.flush();
    kout << "| oct (u_long) | " << oct << u_long << endl;
    kout.flush();
    kout << "| oct (long)   | " << oct << neg_long << endl;
    kout.flush(); kout << endl;
    kout << "| Bin+ (long)   | " << bin << normal_long << " | " << endl;
    kout.flush();
    kout << "| Bin+ (u_long) | " << bin << u_long << " | " << endl;
    kout.flush();
    kout << "| Bin- (long)   | " << neg_long << " | " << endl;
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
    char *p = 0;

    while (true) {
        key_pressed = controller.key_hit();

        if (key_pressed.valid()) {
            // bei der taste 1 wird der buffer benutzt oder nicht
            if (key_pressed.ascii() == 49) {
                if (key_flag) {
                    buffer_flag = true;
                    key_flag = false;

                    kout << endl;
                    kout.flush();
                    kout << "Buffer einschalten" << endl;
                    kout.flush();

                } else {
                    buffer_flag = false;
                    key_flag = true;

                    kout << endl;
                    kout.flush();
                    kout << "Buffer ausschalten" << endl;
                    kout.flush();
                }
                // bei 2 wird die repeat rate geändert
            } else if (key_pressed.ascii() == 50) {
                if (repeat) {
                    kout << endl << "set_repeat_rate(5, 0)" << endl;
                    kout.flush();
                    controller.set_repeat_rate(5, 0);
                    repeat = false;

                } else {
                    kout << endl << "set_repeat_rate(30, 3)" << endl;
                    kout.flush();
                    controller.set_repeat_rate(30, 3);
                    repeat = true;
                }
            } else {
                if (buffer_flag) {
                    kout << key_pressed.ascii();

                } else {
                    c = key_pressed.ascii();
                    p = &c;
                    osstream.print(p, 1, 3);
                }
            }
        }
    }
    return 0;
}

