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


#ifndef QUERYRESULT_H
#define QUERYRESULT_H

namespace JM {
namespace DB {

class ResultRow;


/**
 * Abstract baseclass specifying the ResultSet api.
 * 
 * A ResultSet is created and returned to the user after calling DatabaseHandler::selectQuery().
 * It provides a very simple way to navigate the results of the query.
 * 
 * A ResultSet also owns it's ResultRow objects. That means that when a ResultSet gets deleted
 * the ResultRow objects also get deleted.
 */
class ResultSet
{
public:
	/**
	 * Try to move the ResultSet to the next row and returns if the move was succesful.
	 */
	virtual bool next() = 0;
	
	/**
	 * Returns the pointer to the current row or 0 if there is no current row.
	 * 
	 * Users should take note to delete the ResultSet object itself and not
	 * ResultRow pointers. Those will get deleted when the ResultSet is deleted.
	 */
	virtual ResultRow* current() const = 0;
	
	/**
	 * Get the column information associated with this result set.
	 */
	virtual ColumnInformation getColumnInformation() const = 0;
};


} } // namespace JM::DB

#endif // QUERYRESULT_H
