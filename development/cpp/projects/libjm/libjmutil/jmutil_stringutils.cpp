/*
 *    libjmdb - A simple library for interacting with databases
 *    Copyright (C) 2010 - Jonathan Maasland
 * 
 *    This program is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 * 
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 * 
 *    You should have received a copy of the GNU General Public License
 *    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "jmutil_stringutils.h"

#include <cstring>
#include <cstdio>


namespace JM {
namespace Util {

const char* itoa(const int v) {
  char buff[80];
  snprintf(buff, sizeof(buff), "%d", v);
  
  int newBuffLen = strlen(buff) + 1;
  char* b2 = new char[ newBuffLen ];
  strncpy(b2, buff, newBuffLen);
  return b2;
}

// '0' == 48
inline char charForInt(const int i) {
  // assert(i >= 0 && i <= 9)
  return i+48;
}

/**
 * Because the printf function doesn't handle 64bit ints we have to do this
 * ourselves.
 */
const char* itoa(const int64_t v) {
  if(v == 0) {
    char* b = new char[2];
    b[0] = '0';
    b[1] = '\n';
    return b;
  }
  
  int64_t v2 = v;
  if(v < 0)
    v2 = -v;
  
  const int64_t maxForDivider = 1000000000000000000ll;  // don't ask
  bool maxLengthFound = false;
  int numDigits = 1;
  int64_t divider = 10;
  while(v2 - (v2 % divider) > 0) {
    ++numDigits;
    divider *= 10;
    if(divider == maxForDivider) {
      if(v2 - (v2%divider) != 0) {
        maxLengthFound = true;
        numDigits++;
      }
      break;
    }
  }
  if(!maxLengthFound)
    divider /= 10;
  
  char* buff;
  char* start;
  if(v > 0) {
    buff = new char[numDigits+1];
    start = buff;
  } else {
    buff = new char[numDigits+2];
    buff[0] = '-';
    start = buff;
    buff++;
  }
  
  buff[numDigits] = '\0';
  for(int i = 0; i < numDigits; ++i) {
    buff[i] = charForInt( v2/divider );
    v2 -= (v2/divider)*divider;
    divider /= 10;
  }
  return start;
}

} }  // namespace JM::Util
