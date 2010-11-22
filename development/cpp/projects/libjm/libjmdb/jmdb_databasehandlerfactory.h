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


#ifndef DATABASEHANDLERFACTORY_H
#define DATABASEHANDLERFACTORY_H


namespace JM {
namespace DB {

class DatabaseHandler;


class DatabaseHandlerFactory {
 public:
  /**
   * Create a new handler to the database pointed to by the connection string.
   * 
   * Currently only sqlite is supported but the format is:
   * "\<connector>::\<connectorOptions>"
   * 
   * Where connector is something like sqlite, mysql, pgsql
   * The options are usually something like
   * "username::password::file_or_host::database"
   * This is just an example! Each connector is slightly different.
   * 
   * See the open method on the specific subclass of DatabaseHandler for
   * the database you want to use.
   */
  static DatabaseHandler* open(const char* connectionString);
  
 private:
  DatabaseHandlerFactory() {}
};


} }  // namespace JM::DB

#endif  // DATABASEHANDLERFACTORY_H
