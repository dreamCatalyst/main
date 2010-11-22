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


#include "jmdb_columninformation.h"

#include <cstring>

namespace JM {
namespace DB {

ColumnInformation::ColumnInformation(std::vector< const char* > columnNames)
  : m_columnNames(columnNames) {
}

const char* ColumnInformation::columnName(const unsigned int columnIndex) const {  // NOLINT
  return m_columnNames.at(columnIndex);
}

unsigned int ColumnInformation::numColumns() const {
  return m_columnNames.size();
}

unsigned int ColumnInformation::columnIndex(const char* columnName) const {
  for(int i = 0; i < m_columnNames.size(); ++i) {
    if(strcmp(columnName, m_columnNames.at(i)) == 0)
      return i;
  }
  return 0;
}


} }  // namespace JM::DB
