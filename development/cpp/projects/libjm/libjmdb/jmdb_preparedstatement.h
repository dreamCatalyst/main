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

namespace JM {
namespace DB {

class QueryResult;

/**
 * Abstract baseclass for interacting with prepared statements.
 */
class PreparedStatement {
 public:
  virtual ~PreparedStatement() { }
  
  /**
   * Executes this query and returns a pointer to the QueryResult.
   * The user is responsible for deleting the pointer.
   */
  virtual QueryResult* selectQuery() = 0;
  
  /**
   * Executes this query and returns the number of affected rows.
   */
  virtual int64_t executeQuery() = 0;
  
  virtual void bind(const char* paramId, const char* value, int maxLen = 0);
  virtual void bind(const char* paramId, const int value);
  virtual void bind(const char* paramId, const double value);
  virtual void bind(const char* paramId, const int64_t value);
};

} }  // namespace JM::DB

#endif  // PREPAREDSTATEMENT_H
