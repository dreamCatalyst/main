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


#ifndef PREPAREDSTATEMENT_H
#define PREPAREDSTATEMENT_H

namespace JM {
namespace DB {

class QueryResult;

/**
 * Abstract baseclass for interacting with prepared statements.
 */
class PreparedStatement
{
public:
	/**
	 * Executes this query and returns a pointer to the QueryResult.
	 * The user is responsible for deleting the pointer.
	 */
	virtual QueryResult* selectQuery() = 0;
	
	/**
	 * Executes this query and returns the number of affected rows.
	 */
	virtual unsigned long executeQuery() = 0;
	
	virtual void bind(const char* paramId, const char* value, int maxLen = 0);
	virtual void bind(const char* paramId, const int value);
	virtual void bind(const char* paramId, const double value);
	virtual void bind(const char* paramId, const long value);
};

} } // namespace JM::DB

#endif // PREPAREDSTATEMENT_H
