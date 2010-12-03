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

#include "jmdb_preparedstatement.h"

namespace JM {
namespace DB {

ValueWrapper* ValueWrapper::createInt(const int intVal) {
  ValueWrapper* v = new ValueWrapper(VT_INT);
  v->setInt(intVal);
  return v;
}

ValueWrapper* ValueWrapper::createInt64(const int64_t int64Val) {
  ValueWrapper* v = new ValueWrapper(VT_INT64);
  v->setInt64(int64Val);
  return v;
}

ValueWrapper* ValueWrapper::createString(const char* strVal) {
  ValueWrapper* v = new ValueWrapper(VT_STRING);
  v->setString(strVal);
  return v;
}

ValueWrapper* ValueWrapper::createDouble(const double dblVal) {
  ValueWrapper* v = new ValueWrapper(VT_DOUBLE);
  v->setDouble(dblVal);
  return v;
}

ValueWrapper::ValueWrapper(const ValueType vtype)
  : m_valueType(vtype), m_intValue(0), m_int64Value(0),
    m_stringValue(""), m_doubleValue(0.0) {
  // empty ctor
}

ValueWrapper::~ValueWrapper() {
  // perhaps free the string?
}

ValueType ValueWrapper::getType() const {
  return m_valueType;
}

void ValueWrapper::setType(const ValueType vt) {
  m_valueType = vt;
}

void ValueWrapper::setInt(const int intVal) {
  m_intValue = intVal;
}

void ValueWrapper::setInt64(const int64_t int64Val) {
  m_int64Value = int64Val;
}

void ValueWrapper::setString(const char* strVal) {
  m_stringValue = strVal;
}

void ValueWrapper::setDouble(const double dblVal) {
  m_doubleValue = dblVal;
}

int ValueWrapper::getInt() const {
  return m_intValue;
}

int64_t ValueWrapper::getInt64() const {
  return m_int64Value;
}

const char* ValueWrapper::getString() const {
  return m_stringValue.c_str();
}

double ValueWrapper::getDouble() const {
  return m_doubleValue;
}

// ---------------------------- PreparedStatement baseclass methods

PreparedStatement::PreparedStatement(const char* query) : m_query(query) {
}


PreparedStatement::~PreparedStatement() {
  // free all the valuewrapper objects
}

void PreparedStatement::bind(const char* paramId, const char* value, int /*maxLen*/) {  // NOLINT
  m_bindValueMapByParamId[paramId] = ValueWrapper::createString(value);
}

void PreparedStatement::bind(const char* paramId, const int value) {
  m_bindValueMapByParamId[paramId] = ValueWrapper::createInt(value);
}

void PreparedStatement::bind(const char* paramId, const double value) {
  m_bindValueMapByParamId[paramId] = ValueWrapper::createDouble(value);
}

void PreparedStatement::bind(const char* paramId, const int64_t value) {
  m_bindValueMapByParamId[paramId] = ValueWrapper::createInt64(value);
}

void PreparedStatement::bind(const int paramIndex, const char* value, int maxLen) {  // NOLINT
  m_bindValueMapByIndex[paramIndex] = ValueWrapper::createString(value);
}

void PreparedStatement::bind(const int paramIndex, const int value) {
  m_bindValueMapByIndex[paramIndex] = ValueWrapper::createInt(value);
}

void PreparedStatement::bind(const int paramIndex, const double value) {
  m_bindValueMapByIndex[paramIndex] = ValueWrapper::createDouble(value);
}

void PreparedStatement::bind(const int paramIndex, const int64_t value) {
  m_bindValueMapByIndex[paramIndex] = ValueWrapper::createInt64(value);
}

/*
 * Freeing bound variables is a complex matter because the same variable can be
 * used by multiple resultSets.
 */
void PreparedStatement::freeBindDataForResult(ResultSet* resultSet) {
  std::vector<ValueWrapper*> boundVars = m_inUseBoundValues[resultSet];
  m_inUseBoundValues.erase(resultSet);
  
  std::vector<ValueWrapper*> varsToFree;
  std::vector<ValueWrapper*>::const_iterator boundVarIterator;
  for(boundVarIterator = boundVars.begin();
      boundVarIterator != boundVars.end(); ++boundVarIterator) {
    ValueWrapper* boundVar = *boundVarIterator;
    bool found = false;
    std::map<ResultSet*, std::vector<ValueWrapper*> >::const_iterator iter;
    for(iter = m_inUseBoundValues.begin();
        iter != m_inUseBoundValues.end(); ++iter) {
      std::vector<ValueWrapper*> otherVarList = iter->second;
      std::vector<ValueWrapper*>::const_iterator otherVarListIter;
      for(otherVarListIter = otherVarList.begin();
          otherVarListIter != otherVarList.end(); ++otherVarListIter) {
        if(*otherVarListIter == boundVar) {
          found = true;
          break;
        }
      }
      if(found)
        break;
    }
    if(!found)
      varsToFree.push_back(boundVar);
  }
  
  std::vector<ValueWrapper*>::const_iterator varsToFreeIter;
  for(varsToFreeIter = varsToFree.begin();
      varsToFreeIter != varsToFree.end(); ++varsToFreeIter) {
    delete *varsToFreeIter;
  }
}

/* All the current bind-values are put in a list and added to the inuse map
 * so we can properly free them in freeBindDataForResult()
 */
void PreparedStatement::registerBoundValues(ResultSet* resultSet) {
  std::vector<ValueWrapper*> varList;
  
  std::map<int, ValueWrapper*>::const_iterator iter;
  for(iter = m_bindValueMapByIndex.begin();
      iter != m_bindValueMapByIndex.end(); ++iter)
    varList.push_back( iter->second );
  
  std::map<std::string, ValueWrapper*>::const_iterator iter2;
  for(iter2 = m_bindValueMapByParamId.begin();
      iter2 != m_bindValueMapByParamId.end(); ++iter2)
    varList.push_back( iter2->second );
  
  m_inUseBoundValues[resultSet] = varList;
}


} }  // namespace JM::DB
