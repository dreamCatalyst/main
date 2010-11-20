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


#ifndef JMDB_COLUMNINFORMATION_H
#define JMDB_COLUMNINFORMATION_H

#include <vector>


namespace JM {
namespace DB {


/**
 * TODO Rename: Bad name for the class. Change it!
 */
class ColumnInformation
{
public:
	ColumnInformation(std::vector<const char*> columnNames);
	
	unsigned int numColumns() const;
	const char* columnName(const unsigned int columnIndex) const;
	unsigned int columnIndex(const char* columnName) const;
	
	// add per-column type information later
	// also do we want the nullAllowed method?
protected:
	std::vector<const char*> m_columnNames;
};


} } // namespace JM::DB

#endif // JMDB_COLUMNINFORMATION_H
