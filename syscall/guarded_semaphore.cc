/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                   G U A R D E D _ S E M A P H O R E                       */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Systemaufrufschnittstelle zum Semaphor.                                   */
/*****************************************************************************/

#include "syscall/guarded_semaphore.h"

void Guarded_Semaphore::p() {
    Secure secure;
    Semaphore::p();
}

void Guarded_Semaphore::v() {
    Secure secure;
    Semaphor::v();
}

void Guarded_Semaphore::wait() {
    Secure secure;
    Semaphore::p();
}

void Guarded_Semaphore::signal() {
    Secure secure;
    Semaphore::v();
}
