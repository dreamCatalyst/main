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

#include "jmdb_sqlitepreparedstatement.h"
#include "jmdb_sqlitedatabasehandler.h"
#include "jmdb_sqliteresultset.h"


#include <iostream>
using namespace std;

namespace JM {
namespace DB {

SqlitePreparedStatement::SqlitePreparedStatement(SqliteDatabaseHandler* dbh,
  const char* sql) : PreparedStatement(sql), m_dbh(dbh) {
}

int64_t SqlitePreparedStatement::execute() {
  sqlite3_stmt* stmt = createStatement();
  if(stmt == 0)
    return -1;
  sqlite3_step(stmt);
  if(sqlite3_errcode(m_dbh->getConnection()) != SQLITE_DONE) {
    setHandlerError();  // don't really know if this is correct in all cases
    return -1;
  }
  sqlite3_finalize(stmt);
  return sqlite3_changes(m_dbh->getConnection());
}

ResultSet* SqlitePreparedStatement::executeSelectQuery() {
  // cout << "--SqlitePreparedStatement::executeSelectQuery() start" << endl;
  sqlite3_stmt* stmt = createStatement();
  if(stmt == 0) {
    // cout << "returning 0 because stmt == 0" << endl;
    return 0;
  }
  
  ColumnInformation* colInfo = SqliteDatabaseHandler::createColInfo(stmt);
  SqliteResultSet* rs = new SqliteResultSet(colInfo, stmt);
  registerBoundValues(rs);
  return rs;
}

sqlite3_stmt* SqlitePreparedStatement::createStatement() {
  // cout << "--SqlitePreparedStatement::createStatement() start" << endl;
  sqlite3* conn = m_dbh->getConnection();
  sqlite3_stmt* stmt;
  sqlite3_prepare(conn, m_query.c_str(), -1, &stmt, 0);
  if(sqlite3_errcode(conn) != SQLITE_OK) {
    setHandlerError();
    // cout << "returning 0 because errcode was not SQLITE_OK" << endl;
    return 0;
  }
  if(!bindIndexVars(stmt)) {
    // cout << "returning 0 because bindIndexVars failed" << endl;
    setHandlerError();
    return 0;
  }
  if(!bindNameVars(stmt)) {
    // cout << "returning 0 because bindNameVars failed" << endl;
    setHandlerError();
    return 0;
  }
  
  return stmt;
}

bool SqlitePreparedStatement::bindIndexVars(sqlite3_stmt* stmt) {
  std::map<int, ValueWrapper*>::const_iterator iter;
  for(iter = m_bindValueMapByIndex.begin();
      iter != m_bindValueMapByIndex.end(); ++iter) {
    if(!bindIndexVar(stmt, iter->first, iter->second))
      return false;
  }
  return true;
}

bool SqlitePreparedStatement::bindIndexVar(sqlite3_stmt* stmt, int index,
    ValueWrapper* value) {
  // cout << "--SqlitePreparedStatement::bindIndexVar start" << endl;
  int result;
  switch(value->getType()) {
    case VT_INT: {
      // cout << "binding int-value: " << value->getInt() << " on index: " << index << endl;
      result = sqlite3_bind_int(stmt, index, value->getInt());
      break;
    }
    case VT_INT64: {
      // cout << "binding int64" << endl;
      result = sqlite3_bind_int64(stmt, index, value->getInt64());
      break;
    }
    case VT_STRING: {
      // cout << "binding string" << endl;
      result = sqlite3_bind_text(stmt, index, value->getString(), -1, 0);
      break;
    }
    case VT_DOUBLE: {
      // cout << "binding double" << endl;
      result = sqlite3_bind_double(stmt, index, value->getDouble());
      break;
    }
  };
  // cout << "result of binding is: " << result << endl;
  return result == SQLITE_OK;
}


bool SqlitePreparedStatement::bindNameVars(sqlite3_stmt* stmt) {
  // cout << "--SqlitePreparedStatement::bindNameVars start" << endl;
  // cout << "Iterating over named variables" << endl;
  std::map<std::string, ValueWrapper*>::const_iterator iter;
  for(iter = m_bindValueMapByParamId.begin();
      iter != m_bindValueMapByParamId.end(); ++iter) {
    // cout << "varname: '" << iter->first.c_str() << "'" << endl;
    if(!bindNameVar(stmt, iter->first.c_str(), iter->second)) {
      // cout << "bailing out because bindNameVar failed" << endl;
      return false;
    }
  }
  // cout << "--SqlitePreparedStatement::bindNameVars finished returning true" << endl;
  return true;
}

bool SqlitePreparedStatement::bindNameVar(sqlite3_stmt* stmt, 
    const char* name, ValueWrapper* value) {
  // cout << "--SqlitePreparedStatement::bindNameVar start" << endl;
  int idx = sqlite3_bind_parameter_index(stmt, name);
  // cout << "name='" << name << "'" << " associated index: " << idx << endl;
  return bindIndexVar(stmt, idx, value);
}


void SqlitePreparedStatement::setHandlerError() {
  m_dbh->setSqliteErrorCodeAndMessage();
}


} }  // namespace JM::DB
