/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) <year>  <name of author>

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

// TODO Add compile-time flags here to check for supported databases
#include "jmdb_sqlitedatabasehandler.h"

using namespace JM::DB;


DatabaseHandler* DatabaseHandlerFactory::open(const char* connectionString)
{
	std::string s = connectionString;
	
	std::size_t pos = s.find("sqlite");
	if(pos == 0) {
		return new SqliteDatabaseHandler(connectionString);
	}
	
	// TODO add other databases later
	
	return 0;
}
