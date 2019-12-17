/* $Id: cgascr.cc 5834 2013-10-08 17:04:08Z os $ */

/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                             C G A _ S C R E E N                           */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Mit Hilfe dieser Klasse kann man auf den Bildschirm des PCs zugreifen.    */
/* Der Zugriff erfolgt direkt auf der Hardwareebene, d.h. ueber den Bild-    */
/* schirmspeicher bzw. die I/O-Ports der Grafikkarte.                        */
/*****************************************************************************/

#include "cgascr.h"
#include "../util/string_util.h"
#include "io_port.h"

#define CGA_BASE 0xb8000
#define CURSOR_LOW 15
#define CURSOR_HIGH 14
#define INDEX_REGISTER 0x3d4
#define DATA_REGISTER 0x3d5

static const int MAX_ROW_COUNT = 25;
static const int MAX_COLUMN_COUNT = 80;
/**
 * @brief show prints one char on the screen at the given pos
 * @param x x position
 * @param y y position
 * @param c ascii char
 * @param attrib char attributes
 */
void CGA_Screen::show(int x, int y, char c, unsigned char attrib) {
  if (x > MAX_COLUMN_COUNT || y > MAX_ROW_COUNT || x < 0 || y < 0) {
    return;  // prevent setting cursor pos outside the screen area.
  }

  char *pos;
  char *CGA_START = (char *)CGA_BASE;

  pos = CGA_START + 2 * (x + y * MAX_COLUMN_COUNT);
  *pos = c;
  *(pos + 1) = attrib;
}

/**
 * @brief setpos sets the position of the cursor on the screen
 * @param x x coordinate
 * @param y y coordinate
 */
void CGA_Screen::setpos(int x, int y) {
  if (x > MAX_COLUMN_COUNT || y > MAX_ROW_COUNT || x < 0 || y < 0) {
    return;  // prevent setting cursor pos outside the screen area.
  }

  int offset = x + y * MAX_COLUMN_COUNT;

  IO_Port ioIndex((int)INDEX_REGISTER);
  IO_Port ioData((int)DATA_REGISTER);

  // set low byte
  ioIndex.outb(CURSOR_LOW);
  ioData.outb(offset);

  // set high byte
  ioIndex.outb(CURSOR_HIGH);
  ioData.outb(offset >> 8);
}

/**
 * @brief getpos returns the current position of the cursor on the screen
 * @param x reference to the x return variable
 * @param y reference to the y return variable
 */
void CGA_Screen::getpos(int &x, int &y) {
  IO_Port ioIndex((int)INDEX_REGISTER);
  IO_Port ioData((int)DATA_REGISTER);

  int pos = 0;
  ioIndex.outb(CURSOR_LOW);
  pos = ioData.inb();
  ioIndex.outb(CURSOR_HIGH);
  pos = pos | (ioData.inb()) << 8;
  y = pos / MAX_COLUMN_COUNT;
  x = pos % MAX_COLUMN_COUNT;
}

/**
 * @brief prints the given string to the screen using the cursor pos as start
 * pos. In the end the cursor is moved at the end of the printed string
 * @param text string without null terminator
 * @param length string length
 * @param attrib text attributes
 */
void CGA_Screen::print(char *text, int length, unsigned char attrib) {
  int x;
  int y;

  char *CGA_START = (char *)CGA_BASE;
  char *pos;

  getpos(x, y);

  for (int i = 0; i < length; i++) {
    if (text[i] == '\n') {
      x = 0;
      y++;
    } else {
      if (x == MAX_COLUMN_COUNT) {
        x = 0;
        y++;
      }

      if (y == MAX_ROW_COUNT) {
        for (int z = 1; z < MAX_ROW_COUNT; z++) {
          for (int j = 0; j < MAX_COLUMN_COUNT; j++) {
            pos = CGA_START + 2 * (j + z * MAX_COLUMN_COUNT);
            show(j, z - 1, *pos, *(pos + 1));
            *pos = ' ';
          }
        }
        y--;
      }

      show(x, y, text[i], attrib);
      x++;
    }
  }
    setpos(x, y);
}
