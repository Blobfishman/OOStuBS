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

#define SHORT_NEG_MIN_VALUE 32768
#define INT_NEG_MIN_VALUE 2147483648
#define LONG_NEG_MIN_VALUE 9223372036854775808

O_Stream::O_Stream() {
    buffer_size = 256;
    cleanBuffer();
}

void O_Stream::convert_put(long power, long value) {
    long pow = power;

    while (pow <= value) {
        pow *= power;
    }

    switch (power) {
        case 16:
            put('0');
            put('x');
            break;
        case 10:
            if (value < 0) {
                put('-');
            }
        case 8:
            put('0');
            put('o');
            break;
    }

    do {
        pow /= power;
        if ((value / pow) >= 10) {
            put((char)(value / pow) + 55);
        } else {
            put((char)(value / pow) + 48);
        }
        value %= pow;
        pow /= power;

    } while (pow != 0);
}

void O_Stream::set_system(PositionalNumeralSystem sys) { system = sys; }

PositionalNumeralSystem O_Stream::get_system() { return system; }

O_Stream& O_Stream::operator<<(unsigned char c) {
    put(c);
    return *this;
}

O_Stream& O_Stream::operator<<(char c) {
    put(c);
    return *this;
}

O_Stream& O_Stream::operator<<(unsigned short number) {
    switch (system) {
        case PositionalNumeralSystem::bin:
            convert_put(2, (long)number);
            break;
        case PositionalNumeralSystem::oct:
            convert_put(8, (long)number);
            break;
        case PositionalNumeralSystem::dec:
            convert_put(10, (long)number);
            break;
        case PositionalNumeralSystem::hex:
            convert_put(16, (long)number);
            break;
    }
    return *this;
}

O_Stream& O_Stream::operator<<(unsigned int number) {
    switch (system) {
        case PositionalNumeralSystem::bin:
            convert_put(2, (long)number);
            break;
        case PositionalNumeralSystem::oct:
            convert_put(8, (long)number);
            break;
        case PositionalNumeralSystem::dec:
            convert_put(10, (long)number);
            break;
        case PositionalNumeralSystem::hex:
            convert_put(16, (long)number);
            break;
    }
    return *this;
}

O_Stream& O_Stream::operator<<(unsigned long number) {
    switch (system) {
        case PositionalNumeralSystem::bin:
            convert_put(2, (long)number);
            break;
        case PositionalNumeralSystem::oct:
            convert_put(8, (long)number);
            break;
        case PositionalNumeralSystem::dec:
            convert_put(10, (long)number);
            break;
        case PositionalNumeralSystem::hex:
            convert_put(16, (long)number);
            break;
    }
    return *this;
}

O_Stream& O_Stream::operator<<(short number) {
    if (number < 0) {
        number += SHORT_NEG_MIN_VALUE;
    }
    switch (system) {
        case PositionalNumeralSystem::bin:
            convert_put(2, (long)number);
            break;
        case PositionalNumeralSystem::oct:
            convert_put(8, (long)number);
            break;
        case PositionalNumeralSystem::dec:
            convert_put(10, (long)number);
            break;
        case PositionalNumeralSystem::hex:
            convert_put(16, (long)number);
            break;
    }

    return *this;
}

O_Stream& O_Stream::operator<<(int number) {
    if (number < 0) {
        number += INT_NEG_MIN_VALUE;
    }
    switch (system) {
        case PositionalNumeralSystem::bin:
            convert_put(2, (long)number);
            break;
        case PositionalNumeralSystem::oct:
            convert_put(8, (long)number);
            break;
        case PositionalNumeralSystem::dec:
            convert_put(10, (long)number);
            break;
        case PositionalNumeralSystem::hex:
            convert_put(16, (long)number);
            break;
    }
    return *this;
}

O_Stream& O_Stream::operator<<(long number) {
    if (number < 0) {
        number += LONG_NEG_MIN_VALUE;
    }
    switch (system) {
        case PositionalNumeralSystem::bin:
            convert_put(2, (long)number);
            break;
        case PositionalNumeralSystem::oct:
            convert_put(8, (long)number);
            break;
        case PositionalNumeralSystem::dec:
            convert_put(10, (long)number);
            break;
        case PositionalNumeralSystem::hex:
            convert_put(16, (long)number);
            break;
    }
    return *this;
}

O_Stream& O_Stream::operator<<(void* pointer) {
    convert_put(8, (long) pointer);
    return *this;
}

O_Stream& O_Stream::operator<<(char* text) {
    for (char* pos = text; *pos != '\0'; pos++) {
        put(*pos);
    }
    return *this;
}

O_Stream& O_Stream::operator<<(O_Stream& (*fkt)(O_Stream&)) {
    return fkt(*this);
}

O_Stream& endl(O_Stream& os) {
    os.put('\n');
    return os;
}

O_Stream& bin(O_Stream& os) {
    os.set_system(PositionalNumeralSystem::bin);
    return os;
}

O_Stream& oct(O_Stream& os) {
    os.set_system(PositionalNumeralSystem::oct);
    return os;
}

O_Stream& dec(O_Stream& os) {
    os.set_system(PositionalNumeralSystem::dec);
    return os;
}

O_Stream& hex(O_Stream& os) {
    os.set_system(PositionalNumeralSystem::hex);
    return os;
}
