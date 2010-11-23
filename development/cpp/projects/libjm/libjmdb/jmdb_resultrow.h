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


#ifndef RESULTROW_H
#define RESULTROW_H

#include <stdint.h>
#include <vector>


namespace JM {
namespace DB {

class ColumnInformation;
class Field;


/**
 * Provides an interface for interacting with a row from a resultset.
 * 
 * Has ownership of the Field pointers.
 */
class ResultRow {
 public:
  explicit ResultRow(ColumnInformation* columnInfo);
  ~ResultRow();
  
  ColumnInformation* columnInformation() const;
  
  Field* getField(const char* columnIdent) const;
  Field* getField(const int columnNr) const;
  
  // Convenience methods
  
  const char* getString(const char* columnIdent) const;
  const char* getString(const int columnNr) const;
  
  int getInt(const char* columnIdent) const;
  int getInt(const int columnNr) const;
  
  double getDouble(const char* columnIdent) const;
  double getDouble(const int columnNr) const;
  
  int64_t getInt64(const char* columnIdent) const;
  int64_t getInt64(const int columnNr) const;
 protected:
  std::vector<Field*> m_fieldList;
  ColumnInformation* m_columnInfo;
};


} }  // namespace JM::DB

#endif  // RESULTROW_H
