/*
    libjmdb - A simple library for interacting with databases
    Copyright (C) 2010 - Jonathan Maasland

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "jmdb_field.h"
#include "jmutil_stringutils.h"
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <cstdio>

namespace JM {
namespace DB {


// ---------------------------- StringField implementation

char* StringField::getBinary(int* len) const {
  len = 0;
  return 0;
}

double StringField::getDouble() const {
  if(isNull())
    return 0.0;
  return atof(m_val.c_str());
}

int StringField::getInt() const {
  if(isNull())
    return 0;
  return atoi(m_val.c_str());
}

int64_t StringField::getInt64() const {
  if(isNull())
    return 0;
  return atoll(m_val.c_str());
}

const char* StringField::getString() {
  if(isNull())
    return "";  // TODO should we return an empty string or "NULL"??
  return m_val.c_str();
}


// ---------------------------- IntField implementation

IntField::IntField(const int v)
  : m_val(v), m_longVal(0), m_isLong(false) {
}

IntField::IntField(const int64_t v)
  : m_val(0), m_longVal(v), m_isLong(true) {
}


char* IntField::getBinary(int* len) const {
  *len = 0;
  return 0;
}

double IntField::getDouble() const {
  if(isNull())
    return 0.0;
  if(m_isLong)
    return static_cast<double>(m_longVal);
  return static_cast<double>(m_val);
}

int IntField::getInt() const {
  if(isNull())
    return 0;
  if(m_isLong)
    return 0;
  return m_val;
}

int64_t IntField::getInt64() const {
  if(isNull())
    return 0;
  if(m_isLong)
    return m_longVal;
  return m_val;
}

const char* IntField::getString() {
  if(isNull())
    return "";
  
  // TODO move this to jmstring
  if(m_strVal.empty()) {
    if(m_isLong) {
      const char* s = JM::Util::itoa(m_longVal);
      m_strVal = s;
      delete s;
    } else {
      const char* s = JM::Util::itoa(m_val);
      m_strVal = s;
      delete s;
    }
  }
  return m_strVal.c_str();
}


// ---------------------------- RealField implementation

char* RealField::getBinary(int* len) const {
  *len = 0;
  return 0;
}

double RealField::getDouble() const {
  if(isNull())
    return 0.0;
  return m_val;
}

int RealField::getInt() const {
  if(isNull())
    return 0;
  return round(m_val);
}

int64_t RealField::getInt64() const {
  if(isNull())
    return 0;
  return round(m_val);
}

const char* RealField::getString() {
  if(isNull())
    return "";
  // TODO move this to jmutil possibly jmstring
  if(m_strVal.empty()) {
    // buff-size: sizeof(double)*8+3 = 71
    char buff[80];
    snprintf(buff, sizeof(buff), "%f", m_val);
    
    // strip off trailing zeros -sigh-
    while(strlen(buff) > 0 && buff[ strlen(buff)-1 ] == '0')
      buff[ strlen(buff) -1 ] = '\0';
    
    if(strlen(buff) == 0) {
      buff[0] = '0';
      buff[1] = '\0';
    }
    if(buff[ strlen(buff) -1 ] == '.')
      buff[ strlen(buff) -1 ] = '\0';
    
    m_strVal = buff;
  }
  return m_strVal.c_str();
}


// ---------------------------- BinaryDataField implementation

BinaryDataField::BinaryDataField(const char* data, unsigned int length) {
  m_data = new char[length];
  memcpy(m_data, data, length);
  m_length = length;
}

char* BinaryDataField::getBinary(int* len) const {
  *len = m_length;
  return m_data;
}

BinaryDataField::~BinaryDataField() {
  delete m_data;
  m_data = 0;
}


} }  // namespace JM::DB

