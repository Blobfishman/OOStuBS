/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                          B E L L R I N G E R                              */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Der "Gloeckner" wird im Rahmen der Timer-Epilog Bearbeitung aktiviert.    */
/* Er prueft, ob irgendwelche Glocken (Bell-Objekte) laeuten muessen. Die    */
/* Glocken befinden sich in einer Queue, die der Gloeckner verwaltet.        */
/*****************************************************************************/

#include "meeting/bellringer.h"
#include "device/cgastr.h"
#include "machine/cpu.h"

Bellringer bellringer;

void Bellringer::check() {
    Bell *first_element = (Bell *)first();
    if (first_element == nullptr) {
        return;
    }
    first_element->tick();
    while (first_element->run_down()) {
        remove(first_element);
        first_element->ring();
        first_element = (Bell *)first();
    }
}

void Bellringer::job(Bell *bell, int ticks) {
    Bell *cur = (Bell *)first();
    if (cur == nullptr) {
        bell->wait(ticks);
        insert_first(bell);
        return;
    }
    int t = cur->wait();
    bool found = false;
    while (cur->next != nullptr && !found) {
        cur = (Bell *)cur->next;
        t += cur->wait();
        if (t + ((Bell *)cur->next)->wait() >= ticks) {
            found = true;
        }
    }
    if (!found) {
        bell->wait(ticks - t);
    }
    insert_after(cur, bell);
}

void Bellringer::cancel(Bell *bell) {
    if (bell == nullptr) {
        kout << "PANIC: Unexpected nullptr object of bell in "
             << __PRETTY_FUNCTION__;
        kout.flush();
        cpu.halt();
    }
    Bell *cur = (Bell *)bell->next;
    cur->wait(cur->wait() + bell->wait());
    remove(bell);
}
