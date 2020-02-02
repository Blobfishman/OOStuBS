/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                          S C H E D U L E R                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Implementierung des Schedulers.                                           */
/*****************************************************************************/
#include "thread/scheduler.h"

#include "device/cgastr.h"
#include "machine/cpu.h"
#include "thread/idle_thread.h"

void Scheduler::ready(Entrant& that) { ready_list.enqueue(&that); }

void Scheduler::schedule() {
    Entrant* app = (Entrant*)ready_list.dequeue();
    if (app != nullptr) {
        go(*app);
    } else {
        // Unerwarteter nullptr
        kout << "PANIC: Unexpected nullptr object of Entrant in "
             << __PRETTY_FUNCTION__;
        kout.flush();
        cpu.halt();
    }
}

void Scheduler::exit() {
    Entrant* app = (Entrant*)ready_list.dequeue();
    if (app != nullptr) {
        dispatch(*app);
    } else {
        dispatch(idle_thread);
    }
}

void Scheduler::kill(Entrant& that) { ready_list.remove(&that); }

void Scheduler::resume() {
    Entrant* app_next = (Entrant*)ready_list.dequeue();
    if (app_next != nullptr) {
        Entrant* app_now = (Entrant*)active();
        if (app_now == &idle_thread) {
            dispatch(*app_next);
            return;
        }
        ready_list.enqueue(app_now);
        dispatch(*app_next);
    }
}
