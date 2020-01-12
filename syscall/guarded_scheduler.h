/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                   G U A R D E D _ S C H E D U L E R                       */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Systemaufrufschnittstelle zum Scheduler.                                  */
/*****************************************************************************/

#ifndef __guarded_scheduler_include__
#define __guarded_scheduler_include__

#include "guard/secure.h"
#include "syscall/thread.h"
#include "thread/scheduler.h"

class Guarded_Scheduler : public Scheduler {
   private:
    Guarded_Scheduler(const Guarded_Scheduler& copy);  // Verhindere Kopieren
   public:
    Guarded_Scheduler() {}

    void ready(Thread& that);

    void exit();

    void kill(Thread& that);

    void resume();

    void schedule();

};

extern Guarded_Scheduler scheduler;

#endif
