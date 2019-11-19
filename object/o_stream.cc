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

#define SHORT_MAX_VALUE 65535
#define INT_MAX_VALUE 4294967295
#define LONG_MAX_VALUE 4294967295

O_Stream::O_Stream() {
    buffer_size = 20;
    cleanBuffer();
}

void O_Stream::convert_put(long power, long value) {
    long pow = 1;
    // Alle hex zeichen um zugriff zu vereinfachen, da in ascii tabelle nicht
    // hintereinander
    char* hex_character = "0123456789ABCDEF0";
    // zahlensysteme in 32 Bit darstellung
    char* hex_number = "00000000";
    char* oct_number = "00000000000";
    char* bin_number = "00000000000000000000000000000000";
    // index fuer die zahlensysteme
    int index = 0;
    // anzahl der stellen fuer dec, sonst werden nullen nicht geschrieben
    int digit_number = 1;

    switch (power) {
        case 16:
            put('0');
            put('x');

            // fuer hex array mit laenge 8
            index = 7;
            // bei negative werten positives komplement errechnen
            if (value < 0) {
                value = LONG_MAX_VALUE + value + 1;
            }
            // zahl in hex umwandeln
            while (value > 1) {
                hex_number[index] = hex_character[(value % power)];
                value /= power;
                index--;
            }
            // array in buffer schreiben
            for (int i = 0; i < 8; i++) {
                put(hex_number[i]);
            }

            break;
        case 10:
            // fuer negative zahlen minus auf buffer schreiben
            if (value < 0) {
                put('-');
                value *= -1;
            }

            // berechnung der 10er potenz
            while ((pow * power) <= value) {
                digit_number++;
                pow *= power;
            }
            // die einzelnen stellen der zahl auf buffer schreiben
            while (digit_number >= 1) {
                //+48 wegen ascii tabelle
                put((char)(value / pow) + 48);
                // letzte stelle entfernen
                value = value % pow;
                pow /= 10;
                digit_number--;
            }
            break;
        case 8:
            put('0');
            put('o');
            // fuer oct arraz laenge 11
            index = 10;

            // bei negativer zahl array auf 37777777777 setzen
            if (value < 0) {
                value = LONG_MAX_VALUE + value + 1;
            }
            // zahl in oct umwandeln
            while (value > 1) {
                //+48 fuer ascii
                oct_number[index] = value % power + 48;
                value /= power;
                index--;
            }
            // zahl in buffer schreiben
            for (int i = 0; i < 11; i++) {
                put(oct_number[i]);
            }

            break;
        case 2:
            index = 31;

            // bei negativer zahl array auf 37777777777 setzen
            if (value < 0) {
                value = LONG_MAX_VALUE + value + 1;
            }
            // zahl in bin umwandeln
            while (value > 0) {
                //+48 wegen ascii
                bin_number[index] = value % power + 48;
                value = value / power;
                index--;
            }

            // zahl auf buffer schreiben
            for (int i = 0; i < 32; i++) {
                if (i % 8 == 0) {
                    put(' ');
                }
                put(bin_number[i]);
            }
            break;
    }
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
    convert_put(8, (long)pointer);
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
