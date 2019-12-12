/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                               L O C K E R                                 */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Die Klasse Locker implementiert eine Sperrvariable, die verwendet wird,   */
/* um kritische Abschnitte zu schuetzen. Die Variable zeigt allerdings nur   */
/* an, ob der kritische Abschnitt frei ist. Ein eventuelles Warten und der   */
/* Schutz der fuer diese Klasse notwendigen Zaehlfunktion muss ausserhalb    */
/* erfolgen.                                                                 */
/*****************************************************************************/

#ifndef __Locker_include__
#define __Locker_include__

#include "device/cgastr.h"
#include "machine/cpu.h"

CPU cpu;

class Locker {
   private:
    Locker(const Locker &copy);  // Verhindere Kopieren

   public:
    Locker() : m_locked(false) {}

    inline void enter() {
        if (m_locked) {  // Bei doppelten Aufruf stoppen und Fehler anzeigen
            kout << "\nERROR: Locker::enter() called a 2nd time without "
                    "calling Locker::retne() first"
                 << endl;
            kout.flush();
            cpu.halt();
        }
        m_locked = true;
    }

    inline void retne() {
        if (!m_locked) {  // Bei doppelten Aufruf stoppen und Fehler anzeigen
            kout << "\nERROR: Locker::retne() called a 2nd time without "
                    "calling Locker::enter() first"
                 << endl;
            kout.flush();
            cpu.halt();
        }
        m_locked = false;
    }

    inline bool avail() { return m_locked; }

   protected:
    bool m_locked;
};

#endif
