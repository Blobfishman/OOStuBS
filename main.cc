/* $Id: main.cc 8485 2017-03-27 11:50:06Z friesel $ */

#include "device/cgastr.h"

int main() { 
    CGA_Stream cgastream;
    CGA_Screen osstream;

    osstream.show('c', 5, 5, 3);

    cgastream << hex << 16 << endl;
    cgastream.flush();


    return 0; }

