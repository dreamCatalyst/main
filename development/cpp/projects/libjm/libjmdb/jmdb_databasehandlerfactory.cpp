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


#include "jmdb_databasehandlerfactory.h"

#include <string>

#include "config.h"
#ifdef HAVE_SQLITE3
#include "jmdb_sqlitedatabasehandler.h"
#endif
#ifdef HAVE_MYSQL
#include "jmdb_mysqldatabasehandler.h"
#endif


namespace JM {
namespace DB {

DatabaseHandler* DatabaseHandlerFactory::open(const char* connectionString) {
  std::string s = connectionString;
  std::size_t pos;

#ifdef HAVE_SQLITE3
  pos = s.find("sqlite");
  if(pos == 0) {
    return new SqliteDatabaseHandler(connectionString);
  }
#endif
  
#ifdef HAVE_MYSQL
  pos = s.find("mysql");
  if(pos == 0) {
    return new MysqlDatabaseHandler(connectionString);
  }
#endif

  // log an error message
  return 0;
}

} }  // namespace JM::DB
