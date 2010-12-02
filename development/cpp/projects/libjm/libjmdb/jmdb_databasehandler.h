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


#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include <stdint.h>
#include <string>

namespace JM {
namespace DB {

class PreparedStatement;
class ResultSet;

/**
 * TODO: Should subclasses be responsible for resetting the errorCode and message
 * after _each_ operation. Ie. set it to NO_ERROR and empty string after things
 * work as expected.
 * 
 * What is the expectation?
 */
class DatabaseHandler {
 public:
  DatabaseHandler() : m_errorMessage(""), m_errorCode(0) { }
  virtual ~DatabaseHandler() {}

  /**
   * All the different error codes.
   * 
   * KISS: Keep it simple silly
   * We don't want finegrained error-codes. Use the error-message to
   * describe exactly what went wrong.
   */
  enum ERROR_CODES {
    NO_ERROR = 0,
    CONNECTION_ERROR = 1,
    SQL_ERROR = 2
  };

  /**
   * Returns the errorCode of the last operation.
   * If anything fails we don't throw exceptions. We return null
   * and set the errorCode and message appropriately.
   */
  virtual int errorCode() const { return m_errorCode; }
  
  /**
   * Returns the error-message associated with the last operation.
   * If there was no error this method should return an empty string.
   */
  virtual const char* errorMessage() const { return m_errorMessage.c_str(); }
  
  /**
   * Open a connection to the database with the specified connection string.
   * Returns non-zero on failure.
   */
  virtual int open(const char* connectionString) = 0;
  
  /**
   * Close this handler and all associated resources.
   * Returns non-zero on failure to close.
   */
  virtual int close() = 0;
  
  /**
   * Check to see whether the connection is open and valid.
   * Returns false if there is no connection or it has been closed.
   */
  virtual bool isOpen() const = 0;
  
  /**
   * Creates a new PreparedStatement for the given query.
   * The user is responsible for deleting the pointer.
   * 
   * This method is intended for queries with parameters.
   * Using parameters ensures a layer of protection against SQL-injection
   * (intentional or otherwise)
   */
  virtual PreparedStatement* prepareQuery(const char* query) = 0;
  
  /**
   * Executes the given query and returns a pointer to the new ResultSet.
   * The user is responsible for deleting the pointer.
   * 
   * If executing the query fails in any way this method returns 0.
   * Use errorCode() and errorMessage() functions to find out what went wrong.
   */
  virtual ResultSet* executeSelectQuery(const char* query) = 0;
  
  /**
   * Executes the given query. Returns the error code.
   */
  virtual int execute(const char* query) = 0;
  
  /**
   * Returns the number of rows that were affected by the last executed
   * INSERT, UPDATE or DELETE queries.
   */
  virtual int affectedRowCount() const = 0;
  
 protected:
  virtual void setErrorCode(const int errorCode) { 
    m_errorCode = errorCode;
  }
  
  virtual void setErrorMessage(const char* message) {
    m_errorMessage = message;
  }
  
  virtual int setError(const int errorCode, const char* msg) {
    setErrorCode(errorCode);
    setErrorMessage(msg);
    return errorCode;  // returning errorCode for convenience
  }
  
  virtual void resetError() {
    setErrorCode(NO_ERROR);
    setErrorMessage("");
  }
  
 private:
  std::string m_errorMessage;
  int m_errorCode;
};


} }  // namespace JM::DB

#endif  // DATABASEHANDLER_H
