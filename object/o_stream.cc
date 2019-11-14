/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                            O _ S T R E A M                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Die Klasse O_Stream enthaelt die Definition des << Operators fuer die     */
/* wichtigsten der vordefinierten Datentypen und realisiert somit die        */
/* bekannte Ausgabefunktion der C++ IO_Stream Bibliothek. Zur Zeit wird die  */
/* Darstellung von Zeichen, Zeichenketten und ganzen Zahlen unterstuetzt.    */
/* Ein weiterer << Operator erlaubt die Verwendung von Manipulatoren.        */
/*                                                                           */
/* Neben der Klasse O_Stream sind hier auch die Manipulatoren hex, dec, oct  */
/* und bin fuer die Wahl der Basis bei der Zahlendarstellung, sowie endl     */
/* fuer den Zeilenumbruch definiert.                                         */
/*****************************************************************************/

#include "object/o_stream.h"

O_Stream::O_Stream() {
    buffer_size = 200;
    cleanBuffer();
}

void O_Stream::flush() { cleanBuffer(); }

O_Stream& O_Stream::operator<<(unsigned char c) {
    put(c);
    return *this;
}

O_Stream& O_Stream::operator<<(char c) {
    put(c);
    return *this;
}

O_Stream& O_Stream::operator<<(unsigned short number) {
    short p = 1;
    short char_number = 0;
    while (p <= number) {
        p *= 10;
        char_number++;
    }
    p /= 10;

    while (p > 1) {
        put(((char)(number / p)));
        number %= p;
        p /= 10;
    }
    return *this;
}

O_Stream& O_Stream::operator<<(short number) {
    short p = 1;
    short char_number = 0;
    bool flag = false;

    if (number < 0) {
        flag = true;
        number *= (-1);
        char_number++;
    }

    while (p <= number) {
        p *= 10;
        char_number++;
    }
    p = p / 10;

    if (flag) {
        put('-');
    }
    while (p > 1) {
        put(((char)(number / p)));
        number %= p;
        p /= 10;
    }
    return *this;
}

O_Stream& O_Stream::operator<<(unsigned int number) { return *this; }

O_Stream& O_Stream::operator<<(int number) { return *this; }

O_Stream& O_Stream::operator<<(unsigned long number) { return *this; }

O_Stream& O_Stream::operator<<(long number) { return *this; }
