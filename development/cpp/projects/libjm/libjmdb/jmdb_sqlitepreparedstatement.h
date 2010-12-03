/*
 *  libjmdb - A simple library for interacting with databases
 *  Copyright (C) 2010 - Jonathan Maasland
 * 
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 * 
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 * 
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef JMDB_SQLITE_PREPAREDSTATEMENT_H
#define JMDB_SQLITE_PREPAREDSTATEMENT_H

#include "jmdb_preparedstatement.h"
#include "sqlite3.h"

namespace JM {
namespace DB {

class SqliteDatabaseHandler;


class SqlitePreparedStatement : public PreparedStatement {
 public:
  SqlitePreparedStatement(SqliteDatabaseHandler* dbh, const char* sql);
  
  ResultSet* executeSelectQuery();
  int64_t execute();
  
 private:
  sqlite3_stmt* createStatement();
  bool bindIndexVars(sqlite3_stmt* stmt);
  bool bindIndexVar(sqlite3_stmt* stmt, int index, ValueWrapper* value);
  bool bindNameVars(sqlite3_stmt* stmt);
  bool bindNameVar(sqlite3_stmt* stmt, const char* name, ValueWrapper* value);
  void setHandlerError();
  
  SqliteDatabaseHandler* m_dbh;
};

} }  // namespace JM::DB

#endif  // JMDB_SQLITE_PREPAREDSTATEMENT_H
