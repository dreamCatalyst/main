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

#include "jmdb_resultrow.h"
#include "jmdb_columninformation.h"
#include "jmdb_field.h"

namespace JM {
namespace DB {


ResultRow::ResultRow(ColumnInformation* columnInfo)
  : m_columnInfo(columnInfo) {
}

ResultRow::~ResultRow() {
  std::vector<Field*>::const_iterator iter = m_fieldList.begin();
  while(iter < m_fieldList.end()) {
    delete *iter;
    ++iter;
  }
}

ColumnInformation* ResultRow::columnInformation() const {
  return m_columnInfo;
}

Field* ResultRow::getField(const char* columnIdent) const {
  return m_fieldList.at( m_columnInfo->columnIndex(columnIdent) );
}

Field* ResultRow::getField(const int columnNr) const {
  return m_fieldList.at(columnNr);
}

double ResultRow::getDouble(const char* columnIdent) const {
  return getField(columnIdent)->getDouble();
}

double ResultRow::getDouble(const int columnNr) const {
  return getField(columnNr)->getDouble();
}

int ResultRow::getInt(const char* columnIdent) const {
  return getField(columnIdent)->getInt();
}

int ResultRow::getInt(const int columnNr) const {
  return getField(columnNr)->getInt();
}

int64_t ResultRow::getInt64( const char* columnIdent) const {
  return getField(columnIdent)->getInt64();
}

int64_t ResultRow::getInt64( const int columnNr) const {
  return getField(columnNr)->getInt64();
}

const char* ResultRow::getString(const char* columnIdent) const {
  return getField(columnIdent)->getString();
}

const char* ResultRow::getString(const int columnNr) const {
  return getField(columnNr)->getString();
}


} }  // namespace JM::DB
