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


#ifndef PREPAREDSTATEMENT_H
#define PREPAREDSTATEMENT_H

#include <stdint.h>
#include <map>
#include <string>
#include <vector>

namespace JM {
namespace DB {

class ResultSet;

enum ValueType {
  VT_INT = 0,
  VT_INT64 = 1,
  VT_STRING = 2,
  VT_DOUBLE = 3,
  VT_BINARY = 4
};

/**
 * Helper class to wrap a value that is bound to a PreparedStatement.
 */
class ValueWrapper {
 public:
  static ValueWrapper* createInt(const int intVal);
  static ValueWrapper* createInt64(const int64_t int64Val);
  static ValueWrapper* createString(const char* strVal);
  static ValueWrapper* createDouble(const double dblVal);
  
  explicit ValueWrapper(const ValueType vtype);
  ~ValueWrapper();
  
  ValueType getType() const;
  int getInt() const;
  int64_t getInt64() const;
  const char* getString() const;
  double getDouble() const;
  
  void setType(const ValueType vt);
  void setInt(const int intVal);
  void setInt64(const int64_t int64Val);
  void setString(const char* strVal);
  void setDouble(const double dblVal);
 protected:
  ValueType m_valueType;
  int m_intValue;
  int64_t m_int64Value;
  std::string m_stringValue;
  double m_doubleValue;
  // TODO binary
};

/**
 * Abstract baseclass representing a prepared statement.
 * 
 * Allows for variables to be 'bound' to a query.
 * TODO write $nnn documentation
 * 
 * It is important to note that the bind(const int, ...) variants use
 * 1-based indexing. This means that the leftmost variables has an index of 1.
 */
class PreparedStatement {
 public:
  explicit PreparedStatement(const char* query);
  virtual ~PreparedStatement();
  
  /**
   * Executes this query and returns a pointer to the ResultSet.
   * The user is responsible for deleting the pointer.
   * 
   * It is important to note that the correct order for deletion is:
   * first all ResultsSets then the PreparedStatement.
   * 
   * Subclasses should always call registerBoundValues().
   */
  virtual ResultSet* executeSelectQuery() = 0;
  
  /**
   * Executes this query and returns the number of affected rows.
   */
  virtual int64_t execute() = 0;
  
  virtual void bind(const char* paramId, const char* value, int maxLen = 0);
  virtual void bind(const char* paramId, const int value);
  virtual void bind(const char* paramId, const double value);
  virtual void bind(const char* paramId, const int64_t value);
  // TODO bind for binary data
  virtual void bind(const int paramIndex, const char* value, int maxLen = 0);
  virtual void bind(const int paramIndex, const int value);
  virtual void bind(const int paramIndex, const double value);
  virtual void bind(const int paramIndex, const int64_t value);
  // TODO bind for binary data
  
  void freeBindDataForResult(ResultSet* resultSet);
 protected:
  void registerBoundValues(ResultSet* resultSet);
  
  std::map<int, ValueWrapper*> m_bindValueMapByIndex;
  std::map<std::string, ValueWrapper*> m_bindValueMapByParamId;
  std::string m_query;
 private:
  std::map<ResultSet*, std::vector<ValueWrapper*> > m_inUseBoundValues;
};

} }  // namespace JM::DB

#endif  // PREPAREDSTATEMENT_H
