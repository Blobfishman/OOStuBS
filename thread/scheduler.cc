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

void Scheduler::ready(Entrant& that) { ready_list.enqueue(&that); }

void Scheduler::schedule() {
    Entrant* app = (Entrant*) ready_list.dequeue();
    if (app != nullptr) {
        go(*app);
    }
}

void Scheduler::exit() {
    Entrant* app = (Entrant*) ready_list.dequeue();
    if (app != nullptr) {
        dispatch(*app);
    }
}

void Scheduler::kill(Entrant& that) { ready_list.remove(&that); }

void Scheduler::resume() {
    Entrant* app_next = (Entrant*)ready_list.dequeue();
    if (app_next != nullptr) {
        Entrant* app_now = (Entrant*)active();
        ready_list.enqueue(app_now);
        dispatch(*app_next);
    }
}
