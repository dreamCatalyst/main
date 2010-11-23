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


#ifndef JMDB_COLUMNINFORMATION_H
#define JMDB_COLUMNINFORMATION_H

#include <vector>


namespace JM {
namespace DB {


/**
 * TODO add documentation
 */
class ColumnInformation {
 public:
  explicit ColumnInformation(std::vector<const char*> columnNames);
  ~ColumnInformation();
  
  unsigned int numColumns() const;
  const char* columnName(const unsigned int columnIndex) const;
  unsigned int columnIndex(const char* columnName) const;
  
  // TODO add per-column type information later
  // TODO do we want the nullAllowed method? Can we?
 protected:
  std::vector<const char*> m_columnNames;
};


} }  // namespace JM::DB

#endif  // JMDB_COLUMNINFORMATION_H
