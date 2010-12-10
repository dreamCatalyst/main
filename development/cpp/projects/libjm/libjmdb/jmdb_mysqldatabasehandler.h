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

#ifndef JMDB_MYSQLDATBATABASEHANDLER_H
#define JMDB_MYSQLDATBATABASEHANDLER_H

#include "jmdb_databasehandler.h"
#include <mysql/mysql.h>
#include <string>

namespace JM {
namespace DB {

/**
 * TODO Write something that makes sense here
 * 
 * The mysql connection string uses :: as a field-seperator.
 * Required for each connection is the following:
 *   mysql::host::username::[optionalPassword]
 * This string can be followed by and optional database field for example:
 *   mysql::localhost::myUsername::myPassword::jmdbTestingDatabase
 * 
 * Password can be empty therefore making the following connection strings also
 * valid:
 *   mysql::localhost::myUsername::
 *   mysql::localhost::myUsername::::jmdbTestingDatabase
 * 
 * In the last example no password is provided but a database is selected.
 * 
 * In addition to these fields it is also possible to specify the port to use
 * when connecting to the server. Add "@nr" to the end of the host-field:
 *   mysql::host@4400::user::pass
 * 
 * TODO Add connecting through Unix-sockets and named pipes
 */
class MysqlDatabaseHandler : public DatabaseHandler {
 public:
  explicit MysqlDatabaseHandler(const char* connectionString = 0);
  virtual ~MysqlDatabaseHandler();
  
  int open(const char* connectionString = 0);
  int close();
  bool isOpen() const;
  PreparedStatement* prepareQuery(const char* query);
  ResultSet* executeSelectQuery(const char* query);
  int execute(const char* query);
  int affectedRowCount() const;
  
 private:
  bool isConnectionStringValid();
  void extractConnectionStringFields();
  bool extractFieldFromConnectionString(const int index, std::string* result);
  
  bool doMysqlConnect();
  int setMysqlErrorCodeAndMessage();
  
  MYSQL* m_connection;
  std::string m_connectionString;
  std::string m_username;
  std::string m_password;
  std::string m_host;
  std::string m_database;
  int m_portNr;
};


} }  // namespace JM::DB

#endif  // JMDB_MYSQLDATBATABASEHANDLER_H
