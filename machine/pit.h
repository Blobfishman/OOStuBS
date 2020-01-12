/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                  P I T                                    */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Programmable Interval Timer.                                              */
/*****************************************************************************/

#ifndef __pit_include__
#define __pit_include__

class PIT {
   private:
    PIT(const PIT &copy);  // Verhindere Kopieren

    int m_time;

   public:
    PIT(int us) { interval(us); }
    int interval() { return m_time; }
    void interval(int us);
};

#endif
