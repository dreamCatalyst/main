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

#include "jmdb_sqlitedatabasehandler.h"

#include "jmdb_sqliteresultset.h"
#include "jmdb_sqlitepreparedstatement.h"
#include <cstring>

namespace JM {
namespace DB {


SqliteDatabaseHandler::SqliteDatabaseHandler(const char* connectionString)
  : m_connection(0) {
  m_connectionString = (connectionString == 0)? "" : connectionString;
  if(m_connectionString.length() != 0)
    open();
}

SqliteDatabaseHandler::~SqliteDatabaseHandler() {
  if(isOpen())
    close();
}

int SqliteDatabaseHandler::open(const char* connectionString) {
  if(isOpen())
    return setError(CONNECTION_ERROR, "Connection already opened");
  
  if(connectionString != 0)
    m_connectionString = connectionString;
  
  if(!isConnectionStringValid())
    return errorCode();
  
  std::string filename = extractFilenameFromConnstr();
  int r = sqlite3_open(filename.c_str(), &m_connection);
  if(r != SQLITE_OK) {
    std::string msg = "Error opening connection. Sqlite errormsg: '";
    msg.append(sqlite3_errmsg(m_connection)).append("'");
    return setError(CONNECTION_ERROR, msg.c_str());
  }
  
  resetError();
  return 0;
}

int SqliteDatabaseHandler::close() {
  if(!isOpen())
    return setError(CONNECTION_ERROR, "Can't close as there is no connection");
  
  int r = sqlite3_close(m_connection);
  if(r != SQLITE_OK )
    return setError(CONNECTION_ERROR, "Error closing connection");
  
  m_connection = 0;
  resetError();
  return 0;
}

bool SqliteDatabaseHandler::isOpen() const {
  return m_connection != 0;
}

int SqliteDatabaseHandler::execute( const char* query) {
  if(!isOpen())
    return setError(CONNECTION_ERROR, "No connection to database-file!");
  
  char* errMsg = 0;
  int r = sqlite3_exec(m_connection, query, 0, 0, &errMsg);
  
  if(r != SQLITE_OK) {
    std::string m = "Error executing query. Sqlite error message: '";
    m.append(errMsg).append("'");
    return setError(SQL_ERROR, m.c_str());
  }
  
  resetError();
  return 0;
}

int SqliteDatabaseHandler::affectedRowCount() const {
  if(!isOpen())
    return 0;
  return sqlite3_changes(m_connection);
}

PreparedStatement* SqliteDatabaseHandler::prepareQuery(const char* query) {
  if(!isOpen()) {
    setError(CONNECTION_ERROR, "No connection to database-file!");
    return 0;
  }
  return new SqlitePreparedStatement(this, query);
}

ResultSet* SqliteDatabaseHandler::executeSelectQuery(const char* query) {
  if(!isOpen()) {
    setError(CONNECTION_ERROR, "No connection to database-file!");
    return 0;
  }
  
  sqlite3_stmt* stmt;
  int r = sqlite3_prepare(m_connection, query, strlen(query), &stmt, 0);
  if(r != SQLITE_OK) {
    setSqliteErrorCodeAndMessage();
    return 0;
  }
  resetError();
  ColumnInformation* ci = createColInfo(stmt);
  SqliteResultSet* rs = new SqliteResultSet(ci, stmt);
  return rs;
}

sqlite3* SqliteDatabaseHandler::getConnection() const {
  return m_connection;
}


ColumnInformation* SqliteDatabaseHandler::createColInfo(sqlite3_stmt* stmt) {
  std::vector<const char*> colNames;
  const int cc = sqlite3_column_count(stmt);
  for(int i = 0; i < cc; ++i) {
    const char* colName = sqlite3_column_name(stmt, i);
    const int l = strlen(colName) + 1;
    char* cpy = new char[l];
    strncpy(cpy, colName, l);
    colNames.push_back(cpy);
  }
  return new ColumnInformation(colNames);
}

void SqliteDatabaseHandler::setSqliteErrorCodeAndMessage() {
  std::string msg = "Sqlite error (";
  msg.append(sqlite3_errmsg(m_connection));
  msg.append(")");
  setError(SQL_ERROR, msg.c_str());
}

bool SqliteDatabaseHandler::isConnectionStringValid() {
  if(m_connectionString.length() == 0) {
    setError(CONNECTION_ERROR, "No connection string set");
    return false;
  }
  if(m_connectionString.find("sqlite::") != 0) {
    setError(CONNECTION_ERROR, 
             "Invalid connection string. Doesn't start with 'sqlite::'");
    return false;
  }
  
  std::string filename = extractFilenameFromConnstr();
  if(filename.length() == 0) {
    setError(CONNECTION_ERROR, "No filename provided");
    return false;
  }
  // TODO Add checks for options here when they get added
  return true;
}

std::string SqliteDatabaseHandler::extractFilenameFromConnstr() {
  size_t startPos = m_connectionString.find("::") + 2;
  size_t endPos = m_connectionString.find("::", startPos);
  
  return m_connectionString.substr(startPos, endPos);
}

} }  // namespace JM::DB
