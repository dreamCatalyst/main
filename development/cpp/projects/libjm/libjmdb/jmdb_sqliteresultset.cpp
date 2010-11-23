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

#include "jmdb_sqliteresultset.h"

#include "jmdb_sqliteresultrow.h"

namespace JM {
namespace DB {

SqliteResultSet::SqliteResultSet(ColumnInformation* colInfo, sqlite3_stmt* stmt)
  : ResultSet(colInfo), m_sqliteStatement(stmt), m_doneFetching(false),
  m_stmtFinalized(false), m_iterPosition(-1) {
}

SqliteResultSet::~SqliteResultSet() {
  if(!m_stmtFinalized)
    finalizeStatement();
  deleteAllRows();
}

void SqliteResultSet::finalizeStatement() {
  if(m_stmtFinalized)
    return;
  sqlite3_finalize(m_sqliteStatement);
  m_sqliteStatement = 0;
  m_stmtFinalized = true;
}

// TODO There's probably a more elegant way of doing this
void SqliteResultSet::deleteAllRows() {
  std::vector<ResultRow*>::const_iterator iter = m_rowList.begin();
  while(iter != m_rowList.end()) {
    delete *iter;
    iter++;
  }
}

std::vector<ResultRow*> SqliteResultSet::getRowList() {
  if(!m_doneFetching) {
    if(m_iterPosition == -1)
      initIterator();
    fetchAllRows();
  }
  return m_rowList;
}

int SqliteResultSet::rowCount() {
  if(!m_doneFetching) {
    if(m_iterPosition == -1)
      initIterator();
    fetchAllRows();
  }
  return m_rowList.size();
}

ResultRow* SqliteResultSet::current() {
  if(m_iterPosition == -1 && !m_doneFetching)
    return initIterator();
  if(m_iterPosition == -1)
    return 0;
  return m_rowList.at(m_iterPosition);
}

ResultRow* SqliteResultSet::next() {
  if(m_iterPosition == -1 && !m_doneFetching)
    return initIterator();
  if(m_iterPosition == -1)
    return 0;
  if(m_iterPosition < m_rowList.size()-1) {
    m_iterPosition++;
    return m_rowList.at(m_iterPosition);
  }
  
  fetchNextIterator();
  if(m_iterPosition < m_rowList.size()-1) {
    m_iterPosition++;
    return m_rowList.at(m_iterPosition);
  }
  m_iterPosition = -1;
  return 0;
}

ResultRow* SqliteResultSet::initIterator() {
  fetchNextIterator();
  if(m_rowList.size() == 0)
    return 0;
  m_iterPosition = 0;
  return m_rowList.at(0);
}

void SqliteResultSet::fetchAllRows() {
  while(!m_doneFetching)
    fetchNextIterator();
}

void SqliteResultSet::fetchNextIterator() {
  if(fetchNRows(m_fetchWindowSize) < m_fetchWindowSize)
    m_doneFetching = true;
}

int SqliteResultSet::fetchNRows(const int numRowsToFetch) {
  bool success = false;
  int numFetched = 0;
  do {
    success = fetchRow();
    if(success)
      numFetched++;
  } while(success && numFetched < numRowsToFetch);
  return numFetched;
}

bool SqliteResultSet::fetchRow() {
  if(m_doneFetching)
    return false;
  
  int r = sqlite3_step(m_sqliteStatement);
  switch(r) {
    case SQLITE_ROW: {
      addNewRow();
      return true;
    }
    case SQLITE_DONE: {
      m_doneFetching = true;
      finalizeStatement();
      return false;
    }
    default: {
      m_doneFetching = true;
      // set errorcode and message
      finalizeStatement();
      return false;
    }
  }
}

void SqliteResultSet::addNewRow() {
  ResultRow* row = new SqliteResultRow(m_columnInformation, m_sqliteStatement);
  m_rowList.push_back(row);
}


} }  // namespace JM::DB
