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

#include "jmdb_mysqldatabasehandler.h"

#include <cstdlib>
#include <mysql/errmsg.h>


namespace JM {
namespace DB {


MysqlDatabaseHandler::MysqlDatabaseHandler(const char* connStr)
  : m_connection(0), m_portNr(0) {
  if(connStr != 0) {
    m_connectionString = connStr;
    open();
  }
}

MysqlDatabaseHandler::~MysqlDatabaseHandler() {
  if(isOpen())
    close();
}

int MysqlDatabaseHandler::open(const char* connectionString) {
  if(isOpen())
    return setError(CONNECTION_ERROR, "Connection already opened");
  
  if(connectionString != 0)
    m_connectionString = connectionString;
  if(!isConnectionStringValid())
    return CONNECTION_ERROR;
  
  extractConnectionStringFields();
  if(!doMysqlConnect())
    return CONNECTION_ERROR;
  
  resetError();
  return NO_ERROR;
}

bool MysqlDatabaseHandler::doMysqlConnect() {
  const char* password = (m_password.length() == 0)? 0 : m_password.c_str();
  const char* database = (m_database.length() == 0)? 0 : m_database.c_str();
  
  m_connection = new MYSQL;
  mysql_init(m_connection);
  MYSQL* res = mysql_real_connect(m_connection, m_host.c_str(),
      m_username.c_str(), password, database, m_portNr, 0, 0 );
  
  if(res != m_connection) {
    setMysqlErrorCodeAndMessage();
    return false;
  }
  return true;
}

bool MysqlDatabaseHandler::isOpen() const {
  return m_connection != 0;
}

int MysqlDatabaseHandler::close() {
  if(!isOpen())
    return setError(CONNECTION_ERROR, "Can't close as there is no connection");
  
  mysql_close(m_connection);
  delete m_connection;
  m_connection = 0;
  
  resetError();
  return NO_ERROR;
}

int MysqlDatabaseHandler::affectedRowCount() const {
  //return setError(SQL_ERROR, "MysqlDatabaseHandler::affectedRowCount() not implemented");  //NOLINT
  return 0;
}

int MysqlDatabaseHandler::execute(const char* query) {
  if(!isOpen())
    return setError(SQL_ERROR,
        "Can't execute query as there is not connection");
  
  int res = mysql_query(m_connection, query);
  if(res != 0)
    return setMysqlErrorCodeAndMessage();
  
  resetError();
  return NO_ERROR;
}

ResultSet* MysqlDatabaseHandler::executeSelectQuery(const char* query) {
  setError(SQL_ERROR, "MysqlDatabaseHandler::execute() not implemented");
  return 0;
}

PreparedStatement* MysqlDatabaseHandler::prepareQuery(const char* query) {
  setError(SQL_ERROR, "MysqlDatabaseHandler::prepareQuery() not implemented");
  return 0;
}

/**
 * To check if a connection string is valid all we need to do is count the
 * number of field-seperators. A minimum of four fields are required
 * so if there are three field-seperators the connectionString is valid.
 */
bool MysqlDatabaseHandler::isConnectionStringValid() {
  std::string s;
  
  if(!extractFieldFromConnectionString(0, &s) || s != "mysql") {
    setError(CONNECTION_ERROR,
        "Invalid connection string, it needs to start with mysql::");
    return false;
  }
  
  if(!extractFieldFromConnectionString(1, &s) || s.length() == 0) {
      setError(CONNECTION_ERROR,
          "Invalid connection string, no host provided");
      return false;
  }
  
  if(!extractFieldFromConnectionString(2, &s) || s.length() == 0) {
    setError(CONNECTION_ERROR,
        "Invalid connection string, no username provided");
    return false;
  }
  
  if(!extractFieldFromConnectionString(3, &s)) {
    if(m_connectionString.find_last_of("::") != m_connectionString.length()-3) {
      setError(CONNECTION_ERROR,
          "Invalid connection string, no password-field provided");
      return false;
    }
  }
  return true;
}

void MysqlDatabaseHandler::extractConnectionStringFields() {
  extractFieldFromConnectionString(1, &m_host);
  extractFieldFromConnectionString(2, &m_username);
  extractFieldFromConnectionString(3, &m_password);
  extractFieldFromConnectionString(4, &m_database);
  
  unsigned int atPos = m_host.find("@");
  if(atPos != std::string::npos) {
    m_portNr = atoi(m_host.substr(atPos+1).c_str());
    m_host = m_host.substr(0, atPos);
  }
}

bool MysqlDatabaseHandler::extractFieldFromConnectionString(const int index,
    std::string* result) {
  unsigned int startPos = 0;
  unsigned int endPos = m_connectionString.find("::");
  int currentFieldIndex = 0;
  
  while( currentFieldIndex < index && endPos != std::string::npos &&
      m_connectionString.length() > endPos + 2 ) {
    startPos = endPos + 2;
    endPos = m_connectionString.find("::", startPos);
    ++currentFieldIndex;
  }
  if(currentFieldIndex == index) {
    *result = m_connectionString.substr(startPos, endPos-startPos);
    return true;
  }
  return false;
}

int MysqlDatabaseHandler::setMysqlErrorCodeAndMessage() {
  std::string msg("Mysql error (");
  msg.append(mysql_error(m_connection));
  msg.append(")");
  return setError(SQL_ERROR, msg.c_str());
}


} }  // namespace JM::DB
