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


#ifndef QUERYRESULT_H
#define QUERYRESULT_H

#include "jmdb_columninformation.h"
#include <vector>

namespace JM {
namespace DB {

class ResultRow;


/**
 * Abstract baseclass specifying the ResultSet api.
 * It provides a very simple way to navigate the results of the query.
 * 
 * Provides two ways get get at the rows:
 * - the iterator methods next() and current() which loads one row at a time
 * - the getRowList() method which fetches all the rows at once
 * Choose your method depending on the potential size of the set.
 * In addition the setFetchWindowSize() method allows for more performance
 * control by allowing the iterator method to fetch more than one row if needed.
 * 
 * A ResultSet is created and returned to the user after calling
 * DatabaseHandler::executeSelectQuery()
 * 
 * A ResultSet owns the ResultRow objects. Ie. when a ResultSet gets deleted
 * the ResultRow objects also get deleted.
 */
class ResultSet {
 public:
  explicit ResultSet(ColumnInformation* colInfo)
    : m_columnInformation(colInfo), m_fetchWindowSize(1) {
  }
  virtual ~ResultSet() {
    delete m_columnInformation;
    m_columnInformation = 0;
  }
  
  /**
   * Get the column information associated with this result set.
   */
  virtual ColumnInformation* getColumnInformation() const {
    return m_columnInformation;
  }
  
  /**
   * Try to move the ResultSet to the next row.
   * Returns 0 if there aren't any more rows.
   */
  virtual ResultRow* next() = 0;
  
  /**
   * Returns the pointer to the current row or 0 if there is no current row.
   * 
   * Users should take note to delete the ResultSet object itself and not
   * ResultRow pointers. Those will get deleted when the ResultSet is deleted.
   */
  virtual ResultRow* current() = 0;
  
  /**
   * Returns a vector containing all the ResultRow objects for this ResultSet.
   */
  virtual std::vector<ResultRow*> getRowList() = 0;
  
  /**
   * Returns the number of rows in this ResultSet.
   * After calling this method all rows are guaranteed to have been fetched
   * from the database.
   */
  virtual int rowCount() = 0;
  
  /**
   * Sets the number of rows to fetch when using the iterator methods for
   * retrieving rows.
   * Defaults to 1.
   */
  virtual void setFetchWindowSize(const int windowSize) {
    m_fetchWindowSize = windowSize;
  }
  
 protected:
  int m_fetchWindowSize;
  ColumnInformation* m_columnInformation;
};


} }  // namespace JM::DB

#endif  // QUERYRESULT_H
