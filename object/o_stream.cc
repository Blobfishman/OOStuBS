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
#define LONG_MAX_VALUE 18446744073709551615

O_Stream::O_Stream() {
  buffer_size = 20;
  cleanBuffer();
}

void O_Stream::init() {
  power = 1;
  digit_number = 1;
  index = 1;
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
  init();
  switch (system) {
    case PositionalNumeralSystem::bin:
      index = 15;
      // zahl in bin umwandeln
      while (number > 0) {
        //+48 wegen ascii
        bin_16Bit[index] = number % 2 + 48;
        number = number / 2;
        index--;
      }
      while (index >= 0) {
        bin_16Bit[index] = '0';
        index--;
      }
      // zahl auf buffer schreiben
      for (int i = 0; i < 16; i++) {
        if (i % 8 == 0) {
          put(' ');
        }
        put(bin_16Bit[i]);
      }

      break;
    case PositionalNumeralSystem::oct:
      put('0');
      put('o');
      index = 5;
      // zahl in oct umwandeln
      while (number > 0) {
        //+48 fuer ascii
        oct_16Bit[index] = number % 8 + 48;
        number /= 8;
        index--;
      }
      while (index >= 0) {
        oct_16Bit[index] = '0';
        index--;
      }
      // zahl in buffer schreiben
      for (int i = 0; i < 6; i++) {
        put(oct_16Bit[i]);
      }
      break;
    case PositionalNumeralSystem::dec:
      // 10er potenz ermitteln
      while ((power * 10) <= number) {
        digit_number++;
        power *= 10;
      }
      // die einzelnen stellen der zahl auf buffer schreiben
      while (digit_number >= 1) {
        //+48 wegen ascii tabelle
        put((char)(number / power) + 48);
        // letzte stelle entfernen
        number = number % power;
        power /= 10;
        digit_number--;
      }
      break;
    case PositionalNumeralSystem::hex:
      put('0');
      put('x');
      index = 3;
      // zahl in hex umwandeln
      while (number > 0) {
        hex_16Bit[index] = hex_character[(number % 16)];
        number /= 16;
        index--;
      }
      while (index >= 0) {
        hex_16Bit[index] = '0';
        index--;
      }
      // array in buffer schreiben
      for (int i = 0; i < 4; i++) {
        put(hex_16Bit[i]);
      }
      break;
  }
  return *this;
}

O_Stream& O_Stream::operator<<(unsigned int number) {
  init();
  switch (system) {
    case PositionalNumeralSystem::bin:
      index = 31;
      // zahl in bin umwandeln
      while (number > 0) {
        //+48 wegen ascii
        bin_32Bit[index] = number % 2 + 48;
        number = number / 2;
        index--;
      }

      while (index >= 0) {
        bin_32Bit[index] = '0';
        index--;
      }

      // zahl auf buffer schreiben
      for (int i = 0; i < 32; i++) {
        if (i % 8 == 0) {
          put(' ');
        }
        put(bin_32Bit[i]);
      }

      break;
    case PositionalNumeralSystem::oct:
      put('0');
      put('o');
      // fuer oct arraz laenge 11
      index = 10;

      // zahl in oct umwandeln
      while (number > 0) {
        //+48 fuer ascii
        oct_32Bit[index] = number % 8 + 48;
        number /= 8;
        index--;
      }
      while (index >= 0) {
        oct_32Bit[index] = '0';
        index--;
      }
      // zahl in buffer schreiben
      for (int i = 0; i < 11; i++) {
        put(oct_32Bit[i]);
      }
      break;
    case PositionalNumeralSystem::dec:
      // berechnung der 10er potenz
      while ((power * 10) <= number) {
        digit_number++;
        power *= 10;
      }
      // die einzelnen stellen der zahl auf buffer schreiben
      while (digit_number >= 1) {
        //+48 wegen ascii tabelle
        put((char)(number / power) + 48);
        // letzte stelle entfernen
        number = number % power;
        power /= 10;
        digit_number--;
      }
      break;
    case PositionalNumeralSystem::hex:
      put('0');
      put('x');
      // fuer hex array mit laenge 8
      index = 7;
      // zahl in hex umwandeln
      while (number > 0) {
        hex_32Bit[index] = hex_character[(number % 16)];
        number /= 16;
        index--;
      }
      while (index >= 0) {
        hex_32Bit[index] = '0';
        index--;
      }
      // array in buffer schreiben
      for (int i = 0; i < 8; i++) {
        put(hex_32Bit[i]);
      }
      break;
  }
  return *this;
}

O_Stream& O_Stream::operator<<(unsigned long number) {
  init();
  switch (system) {
    case PositionalNumeralSystem::bin:
      index = 63;
      // zahl in bin umwandeln
      while (number > 0) {
        //+48 wegen ascii
        bin_64Bit[index] = number % 2 + 48;
        number = number / 2;
        index--;
      }
      while (index >= 0) {
        bin_64Bit[index] = '0';
        index--;
      }

      // zahl auf buffer schreiben
      for (int i = 0; i < 64; i++) {
        if (i % 8 == 0) {
          put(' ');
        }
        put(bin_64Bit[i]);
      }

      break;
    case PositionalNumeralSystem::oct:
      put('0');
      put('o');
      // fuer oct arraz laenge 11
      index = 21;

      // zahl in oct umwandeln
      while (number > 0) {
        //+48 fuer ascii
        oct_64Bit[index] = number % 8 + 48;
        number /= 8;
        index--;
      }
      while (index >= 0) {
        oct_64Bit[index] = '0';
        index--;
      }
      // zahl in buffer schreiben
      for (int i = 0; i < 22; i++) {
        put(oct_64Bit[i]);
      }
      break;
    case PositionalNumeralSystem::dec:
      if (number < 0) {
        put('-');
        number *= -1;
      }

      // berechnung der 10er potenz
      while ((power * 10) <= number) {
        digit_number++;
        power *= 10;
      }
      // die einzelnen stellen der zahl auf buffer schreiben
      while (digit_number >= 1) {
        //+48 wegen ascii tabelle
        put((char)(number / power) + 48);
        // letzte stelle entfernen
        number = number % power;
        power /= 10;
        digit_number--;
      }
      break;
    case PositionalNumeralSystem::hex:
      put('0');
      put('x');
      // fuer hex array mit laenge 8
      index = 15;
      // zahl in hex umwandeln
      while (number > 0) {
        hex_64Bit[index] = hex_character[(number % 16)];
        number /= 16;
        index--;
      }
      while (index >= 0) {
        hex_64Bit[index] = '0';
        index--;
      }
      // array in buffer schreiben
      for (int i = 0; i < 16; i++) {
        put(hex_64Bit[i]);
      }
      break;
  }
  return *this;
}

O_Stream& O_Stream::operator<<(short number) {
  init();
  unsigned short n = 0;
  switch (system) {
    case PositionalNumeralSystem::bin:
      index = 15;
      // bei neg
      if (number < 0) {
        n = SHORT_MAX_VALUE + number + 1;
      } else {
        n = number;
      }
      // zahl in bin umwandeln
      while (n > 0) {
        //+48 wegen ascii
        bin_16Bit[index] = n % 2 + 48;
        n = n / 2;
        index--;
      }
      while (index >= 0) {
        bin_16Bit[index] = '0';
        index--;
      }

      // zahl auf buffer schreiben
      for (int i = 0; i < 16; i++) {
        if (i % 8 == 0) {
          put(' ');
        }
        put(bin_16Bit[i]);
      }

      break;
    case PositionalNumeralSystem::oct:
      put('0');
      put('o');
      // fuer oct arraz laenge 11
      index = 5;

      // bei negativer zahl array auf 37777777777 setzen
      if (number < 0) {
        n = SHORT_MAX_VALUE + number + 1;
      } else {
        n = number;
      }
      // zahl in oct umwandeln
      while (n > 0) {
        //+48 fuer ascii
        oct_16Bit[index] = n % 8 + 48;
        n /= 8;
        index--;
      }
      while (index >= 0) {
        oct_16Bit[index] = '0';
        index--;
      }
      // zahl in buffer schreiben
      for (int i = 0; i < 6; i++) {
        put(oct_16Bit[i]);
      }
      break;
    case PositionalNumeralSystem::dec:
      if (number < 0) {
        put('-');
        number *= -1;
      }

      // berechnung der 10er potenz
      while ((power * 10) <= number) {
        digit_number++;
        power *= 10;
      }
      // die einzelnen stellen der zahl auf buffer schreiben
      while (digit_number >= 1) {
        //+48 wegen ascii tabelle
        put((char)(number / power) + 48);
        // letzte stelle entfernen
        number = number % power;
        power /= 10;
        digit_number--;
      }
      break;
    case PositionalNumeralSystem::hex:
      put('0');
      put('x');
      // fuer hex array mit laenge 8
      index = 3;
      // bei negative werten positives komplement errechnen
      if (number < 0) {
        n = SHORT_MAX_VALUE + number + 1;
      } else {
        n = number;
      }
      // zahl in hex umwandeln
      while (n > 0) {
        hex_16Bit[index] = hex_character[(n % 16)];
        n /= 16;
        index--;
      }
      while (index >= 0) {
        hex_16Bit[index] = '0';
        index--;
      }
      // array in buffer schreiben
      for (int i = 0; i < 4; i++) {
        put(hex_16Bit[i]);
      }
      break;
  }
  return *this;
}

O_Stream& O_Stream::operator<<(int number) {
  init();
  unsigned int n = 0;
  switch (system) {
    case PositionalNumeralSystem::bin:
      index = 31;
      // bei neg
      if (number < 0) {
        n = INT_MAX_VALUE + number + 1;
      } else {
        n = number;
      }
      // zahl in bin umwandeln
      while (n > 0) {
        //+48 wegen ascii
        bin_32Bit[index] = n % 2 + 48;
        n = n / 2;
        index--;
      }
      while (index >= 0) {
        bin_32Bit[index] = '0';
        index--;
      }

      // zahl auf buffer schreiben
      for (int i = 0; i < 32; i++) {
        if (i % 8 == 0) {
          put(' ');
        }
        put(bin_32Bit[i]);
      }

      break;
    case PositionalNumeralSystem::oct:
      put('0');
      put('o');
      // fuer oct arraz laenge 11
      index = 10;

      // bei negativer zahl array auf 37777777777 setzen
      if (number < 0) {
        n = INT_MAX_VALUE + number + 1;
      } else {
        n = number;
      }
      // zahl in oct umwandeln
      while (n > 0) {
        //+48 fuer ascii
        oct_32Bit[index] = n % 8 + 48;
        n /= 8;
        index--;
      }
      while (index >= 0) {
        oct_32Bit[index] = '0';
        index--;
      }
      // zahl in buffer schreiben
      for (int i = 0; i < 11; i++) {
        put(oct_32Bit[i]);
      }
      break;
    case PositionalNumeralSystem::dec:
      if (number < 0) {
        put('-');
        number *= -1;
      }

      // berechnung der 10er potenz
      while ((power * 10) <= number) {
        digit_number++;
        power *= 10;
      }
      // die einzelnen stellen der zahl auf buffer schreiben
      while (digit_number >= 1) {
        //+48 wegen ascii tabelle
        put((char)(number / power) + 48);
        // letzte stelle entfernen
        number = number % power;
        power /= 10;
        digit_number--;
      }
      break;
    case PositionalNumeralSystem::hex:
      put('0');
      put('x');
      // fuer hex array mit laenge 8
      index = 7;
      // bei negative werten positives komplement errechnen
      if (number < 0) {
        n = INT_MAX_VALUE + number + 1;
      } else {
        n = number;
      }
      // zahl in hex umwandeln
      while (n > 0) {
        hex_32Bit[index] = hex_character[(n % 16)];
        n /= 16;
        index--;
      }
      while (index >= 0) {
        hex_32Bit[index] = '0';
        index--;
      }
      // array in buffer schreiben
      for (int i = 0; i < 8; i++) {
        put(hex_32Bit[i]);
      }
      break;
  }
  return *this;
}

O_Stream& O_Stream::operator<<(long number) {
  init();
  unsigned long n = 0;
  switch (system) {
    case PositionalNumeralSystem::bin:
      index = 63;
      // bei neg
      if (number < 0) {
        n = LONG_MAX_VALUE + number + 1;
      } else {
        n = number;
      }
      // zahl in bin umwandeln
      while (n > 0) {
        //+48 wegen ascii
        bin_64Bit[index] = n % 2 + 48;
        n = n / 2;
        index--;
      }
      while (index >= 0) {
        bin_64Bit[index] = '0';
        index--;
      }

      // zahl auf buffer schreiben
      for (int i = 0; i < 64; i++) {
        if (i % 8 == 0) {
          put(' ');
        }
        put(bin_64Bit[i]);
      }

      break;
    case PositionalNumeralSystem::oct:
      put('0');
      put('o');
      // fuer oct arraz laenge 11
      index = 21;

      // bei negativer zahl array auf 37777777777 setzen
      if (number < 0) {
        n = LONG_MAX_VALUE + number + 1;
      } else {
        n = number;
      }
      // zahl in oct umwandeln
      while (n > 0) {
        //+48 fuer ascii
        oct_64Bit[index] = n % 8 + 48;
        n /= 8;
        index--;
      }
      while (index >= 0) {
        oct_64Bit[index] = '0';
        index--;
      }
      // zahl in buffer schreiben
      for (int i = 0; i < 22; i++) {
        put(oct_64Bit[i]);
      }
      break;
    case PositionalNumeralSystem::dec:
      if (number < 0) {
        put('-');
        number *= -1;
      }

      // berechnung der 10er potenz
      while ((power * 10) <= number) {
        digit_number++;
        power *= 10;
      }
      // die einzelnen stellen der zahl auf buffer schreiben
      while (digit_number >= 1) {
        //+48 wegen ascii tabelle
        put((char)(number / power) + 48);
        // letzte stelle entfernen
        number = number % power;
        power /= 10;
        digit_number--;
      }
      break;
    case PositionalNumeralSystem::hex:
      put('0');
      put('x');
      // fuer hex array mit laenge 8
      index = 15;
      // bei negative werten positives komplement errechnen
      if (number < 0) {
        n = LONG_MAX_VALUE + number + 1;
      } else {
        n = number;
      }
      // zahl in hex umwandeln
      while (n > 0) {
        hex_64Bit[index] = hex_character[(n % 16)];
        n /= 16;
        index--;
      }
      while (index >= 0) {
        hex_64Bit[index] = '0';
        index--;
      }
      // array in buffer schreiben
      for (int i = 0; i < 16; i++) {
        put(hex_64Bit[i]);
      }
      break;
  }
  return *this;
}

O_Stream& O_Stream::operator<<(void* pointer) {
  long p = (long)pointer;
  init();
  unsigned long n = 0;
  put('0');
  put('o');
  // fuer oct arraz laenge 11
  index = 21;

  // bei negativer zahl array auf 37777777777 setzen
  if (p < 0) {
    n = LONG_MAX_VALUE + p + 1;
  } else {
    n = p;
  }
  // zahl in oct umwandeln
  while (n > 1) {
    //+48 fuer ascii
    oct_64Bit[index] = n % 8 + 48;
    n /= 8;
    index--;
  }
  while (index >= 0) {
    oct_64Bit[index] = '0';
    index--;
  }
  // zahl in buffer schreiben
  for (int i = 0; i < 22; i++) {
    put(oct_64Bit[i]);
  }
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
