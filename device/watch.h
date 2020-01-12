/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              W A T C H                                    */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/*****************************************************************************/

#ifndef __watch_include__
#define __watch_include__

#include "guard/gate.h"
#include "machine/pit.h"

static const int INTERRUPT_COUNT_MAX = 500;

class Watch : public Gate, public PIT {
   private:
    Watch(const Watch &copy);  // Verhindere Kopieren

    int m_current_time{0};

   public:
    // WATCH: Initialisiert die Uhr.
    Watch(int us) : PIT(us) {}

    // WINDUP: "zieht die Uhr auf". Danach laeuft sie los und loest in
    //         regelmaessigen Abstaenden Unterbrechungen aus.
    void windup();

    // PROLOGUE: Prologue der Uhrenunterbrechung
    bool prologue();

    // EPILOGUE: Epilogue der Uhrenunterbrechung
    void epilogue();

    void rest() {m_current_time = 0;};
};

extern Watch watch;

#endif
