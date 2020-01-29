/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                         I D L E - T H R E A D                             */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Die Klasse Idle_Thread versetzt die CPU in den Idle Zustand               */
/*****************************************************************************/

#ifndef __idle_thread_include__
#define __idle_thread_include__

#include "syscall/thread.h"

class Idle_Thread : public Thread {
   private:
    Idle_Thread(const Idle_Thread& copy);  // Verhindere Kopieren

   public:
    Idle_Thread(void* stack);
    void action();
};

extern Idle_Thread idle_thread;
#endif
