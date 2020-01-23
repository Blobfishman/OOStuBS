/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                           S E M A P H O R E                               */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Semaphore werden zur Synchronisation von Threads verwendet.               */
/*****************************************************************************/

#ifndef __Semaphore_include__
#define __Semaphore_include__

class Semaphore {
   private:
    Semaphore(const Semaphore &copy);  // Verhindere Kopieren

    int m_count;

   public:
    Semaphore(int c);

    inline void p();
    inline void v();
    void wait();
    void signal();
};

#endif
