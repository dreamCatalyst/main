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


#ifndef JMDB_SQLITEDATABASEHANDLER_H
#define JMDB_SQLITEDATABASEHANDLER_H


#include "jmdb_databasehandler.h"
#include "sqlite3.h"
#include <stdint.h>
#include <string>


namespace JM {
namespace DB {


class SqliteDatabaseHandler : public DatabaseHandler {
 public:
  explicit SqliteDatabaseHandler(const char* connectionString = 0);
  
  // ------------------------------ interface implementation
  
  /**
   * Opens a connection to a sqlite database.
   * TODO I don't know if sqlite has any interesting options.
   * 
   * The format of the connectionString is very simple:
   * sqlite::filepath
   */
  int open(const char* connectionString = 0);
  
  int close();
  bool isOpen() const;
  PreparedStatement* prepareQuery(const char* query);
  ResultSet* executeSelectQuery(const char* query);
  int64_t execute(const char* query);
  
 private:
  bool isConnectionStringValid();
  std::string extractFilenameFromConnstr();
  
  std::string m_connectionString;
  sqlite3* m_connection;
};


} }  // namespace JM::DB

#endif  // JMDB_SQLITEDATABASEHANDLER_H
