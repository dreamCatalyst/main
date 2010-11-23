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

#ifndef JMDB_SQLITERESULTROW_H
#define JMDB_SQLITERESULTROW_H

#include "jmdb_resultrow.h"
#include <sqlite3.h>

namespace JM {
namespace DB {

class SqliteResultRow : public ResultRow {
 public:
  SqliteResultRow(ColumnInformation* columnInfo, sqlite3_stmt* stmt);
  
 private:
  void initFields();
  void addIntegerField(const int col);
  void addDoubleField(const int col);
  void addStringField(const int col);
  void addBinaryField(const int col);
  
  sqlite3_stmt* m_stmt;
};

} }  // namespace JM::DB

#endif  // JMDB_SQLITERESULTROW_H
