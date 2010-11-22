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


#ifndef JMDB_FIELD_H
#define JMDB_FIELD_H

#include <stdint.h>
#include <string>


namespace JM {
namespace DB {

/**
 * Abstract baseclass for representing a value in a ResultRow.
 * Provides simple data-access methods all subclasses must implement.
 * 
 * It is obvious that you should use these methods carefully. Ask these
 * int value of a field containing text doesn't really make sense. Defaults
 * are provided for underlying datatypes.
 * For example toInt() will correctly round up or down for a field of type Real.
 * 
 * Use the getBinary() method only for fields that you know are of the
 * BinaryDataField type. It is not implemented for other types!
 */
class Field {
 public:
  explicit Field(const bool isNull = false) : m_isNull(isNull) { }
  virtual ~Field() { }
  
  virtual bool isNull() const {
    return m_isNull;
  }
  
  virtual const char* getString() = 0;
  virtual double getDouble() const = 0;
  virtual int getInt() const = 0;
  virtual int64_t getInt64() const = 0;
  virtual char* getBinary(int* len) const = 0;
  
 protected:
  bool m_isNull;
};


class StringField : public Field {
 public:
  StringField() : Field(true) { }
  explicit StringField(const char* val) : m_val(val) { }
  virtual ~StringField() { }
  
  virtual const char* getString();
  virtual double getDouble() const;
  virtual int getInt() const;
  virtual int64_t getInt64() const;
  virtual char* getBinary(int* len) const;
 protected:
  std::string m_val;
};


class IntField : public Field {
 public:
  IntField() : Field(true), m_val(0), m_longVal(0), m_isLong(false) { }
  explicit IntField(const int v);
  explicit IntField(const int64_t v);
  virtual ~IntField() { }
  
  virtual const char* getString();
  virtual double getDouble() const;
  virtual int getInt() const;
  virtual int64_t getInt64() const;
  virtual char* getBinary(int* len) const;
 protected:
  int m_val;
  int64_t m_longVal;
  bool m_isLong;
  std::string m_strVal;
};


class RealField : public Field {
 public:
  RealField() : Field(true), m_val(0.0) { }
  explicit RealField(const double v) : m_val(v) { }
  virtual ~RealField() { }
  
  virtual const char* getString();
  virtual double getDouble() const;
  virtual int getInt() const;
  virtual int64_t getInt64() const;
  virtual char* getBinary(int* len) const;
 protected:
  double m_val;
  std::string m_strVal;
};


/**
 * BinaryField is a special field type in that it doesn't convert to other
 * datatypes. At all.
 * If a column in a database is of this type it's content can only be retrieved
 * as straight binary data.
 */
class BinaryDataField : public Field {
 public:
  BinaryDataField() : Field(true), m_data(0), m_length(0) { }
  BinaryDataField(const char* data, unsigned int length);
  virtual ~BinaryDataField();
  
  virtual const char* getString() { return ""; }
  virtual double getDouble() const { return 0.0; }
  virtual int getInt() const { return 0; }
  virtual int64_t getInt64() const { return 0; }
  virtual char* getBinary(int* len) const;
 protected:
  char* m_data;
  unsigned int m_length;
};

} }  // namespace JM::DB

#endif  // JMDB_FIELD_H
