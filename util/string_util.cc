#include "util/string_util.h"

/**
 * @brief string_contains counts the number of c inside the string
 * @param str target string
 * @param length string length
 * @param c search char
 * @return number of c inside the string
 */
int string_contains(char *str, unsigned length, char c) {
  int count = 0;
  for (unsigned i = 0; i < length; i++) {
    if (str[i] == c) {
      count++;
    }
  }
  return count;
}

