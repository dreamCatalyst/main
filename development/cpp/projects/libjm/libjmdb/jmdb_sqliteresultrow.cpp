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

#include "jmdb_sqliteresultrow.h"

#include "jmdb_columninformation.h"
#include "jmdb_field.h"
#include <climits>

namespace JM {
namespace DB {

SqliteResultRow::SqliteResultRow(ColumnInformation* colInfo, sqlite3_stmt* stmt)
  : ResultRow(colInfo), m_stmt(stmt) {
  initFields();
}

void SqliteResultRow::initFields() {
  for(int i = 0; i < m_columnInfo->numColumns(); ++i) {
    switch(sqlite3_column_type(m_stmt, i)) {
      case SQLITE_INTEGER: {
        addIntegerField(i);
        break;
      }
      case SQLITE_FLOAT: {
        addDoubleField(i);
        break;
      }
      case SQLITE_BLOB: {
        addBinaryField(i);
        break;
      }
      default: {
        addStringField(i);  // for both SQLITE_STRING and SQLITE_NULL
        break;
      }
    };
  }
}

void SqliteResultRow::addIntegerField(const int col) {
  sqlite_int64 val = sqlite3_column_int64(m_stmt, col);
  if(val < INT_MIN || val > INT_MAX)
    m_fieldList.push_back(new IntField(val));
  else
    m_fieldList.push_back(new IntField(sqlite3_column_int(m_stmt, col)));
}

void SqliteResultRow::addStringField(const int col) {
  if(sqlite3_column_type(m_stmt, col) == SQLITE_NULL) {
    m_fieldList.push_back(new StringField());
    return;
  }
  const unsigned char* text = sqlite3_column_text(m_stmt, col);
  m_fieldList.push_back(new StringField(reinterpret_cast<const char*>(text)));
}

void SqliteResultRow::addDoubleField(const int col) {
  m_fieldList.push_back(new RealField(sqlite3_column_double(m_stmt, col)));
}

void SqliteResultRow::addBinaryField(const int col) {
  m_fieldList.push_back(new BinaryDataField());  // TODO implement this
}



} }  // namespace JM::DB
