#include "util/print.h"
#include "device/cgastr.h"

void print_stack() {
    void* p = 0;
    void* sp = &p;
    for (int i=0; i < 24; i++) {
        kout << *((void**)++sp) << '\n';
    }
    kout.flush();
}
