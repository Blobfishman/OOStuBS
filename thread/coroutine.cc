/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                          C O R O U T I N E                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Implementierung des Koroutinenkonzepts.                                   */
/* Im Konstruktor wird der initiale Kontext der Koroutine eingerichtet.      */
/* Mit go() wird die erste Koroutine aktiviert. Alle weiteren Koroutinen-    */
/* wechsel sollten mit resume() erfolgen.                                    */
/* Um bei einem Koroutinenwechsel den Kontext sichern zu koennen, enthaelt   */
/* jedes Koroutinenobjekt eine Struktur toc, in dem die Werte der nicht-     */
/* fluechtigen Register gesichert werden koennen.                            */
/*****************************************************************************/

#include "thread/coroutine.h"

extern void kickoff(void*, void*, void*, void*, void*, void*, void*);

// Funktionen, die auf der C- oder Assembler-Ebene implementiert werden,
// muessen als extern "C" deklariert werden, da sie nicht dem Name-Mangeling
// von C++ entsprechen.
extern "C" {
void toc_settle(struct toc* regs, void* tos,
                void (*kickoff)(void*, void*, void*, void*, void*, void*,
                                void*),
                void* object);

void toc_go(struct toc* regs);

void toc_switch(struct toc* reg_now, struct toc* regs_then);
}

Coroutine::Coroutine(void* tos) {
    toc_settle(&m_regs, tos, &kickoff, this);
}

void Coroutine::go() {
    toc_go(&m_regs);
}

void Coroutine::resume(Coroutine& next) {
    toc_switch(&this->m_regs, &next.m_regs);
}
