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

#ifndef JMDB_SQLITERESULTSET_H
#define JMDB_SQLITERESULTSET_H

#include "jmdb_resultset.h"
#include <sqlite3.h>
#include <vector>

namespace JM {
namespace DB {


class SqliteResultSet : public ResultSet {
 public:
  SqliteResultSet(ColumnInformation* columnInfo, sqlite3_stmt* stmt);
  virtual ~SqliteResultSet();
  
  ResultRow* next();
  ResultRow* current();
  std::vector<ResultRow*> getRowList();
  int rowCount();
  
 private:
  void finalizeStatement();
  void deleteAllRows();
  
  ResultRow* initIterator();
  void fetchNextIterator();
  bool fetchRow();
  int fetchNRows(const int numRowsToFetch);
  void fetchAllRows();
  void addNewRow();
  
  sqlite3_stmt* m_sqliteStatement;
  bool m_doneFetching;
  bool m_stmtFinalized;
  int m_iterPosition;
  std::vector<ResultRow*> m_rowList;
};


} }  // namespace JM::DB

#endif  // JMDB_SQLITERESULTSET_H
