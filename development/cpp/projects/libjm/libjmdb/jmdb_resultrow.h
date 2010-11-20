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


#ifndef RESULTROW_H
#define RESULTROW_H

#include <vector>


namespace JM {
namespace DB {

class ColumnInformation;
class Field;


/**
 * Provides an interface for interacting with a row from a resultset.
 * 
 * Has ownership of the Field pointers.
 */
class ResultRow
{
public:
	ResultRow(ColumnInformation* columnInfo, std::vector<Field*> fields);
	~ResultRow();
	
	ColumnInformation* columnInformation() const;
	
	Field* getField(const char* columnIdent) const;
	Field* getField(const unsigned int columnNr) const;
	
	// Convenience methods
	
	const char* getString(const char* columnIdent) const;
	const char* getString(const unsigned int columnNr) const;
	
	int getInt(const char* columnIdent) const;
	int getInt(const unsigned int columnNr) const;
	
	double getDouble(const char* columnIdent) const;
	double getDouble(const unsigned int columnNr) const;
	
	long getLong(const char* columnIdent) const;
	long getLong(const unsigned int columnNr) const;
	
	unsigned int getUInt(const char* columnIdent) const;
	unsigned int getUInt(const unsigned int columnNr) const;
	
	unsigned long getULong(const char* columnIdent) const;
	unsigned long getULong(const unsigned int columnNr) const;
protected:
	std::vector<Field*> m_fieldList;
	ColumnInformation* m_columnInfo;
};


} } // namespace JM::DB

#endif // RESULTROW_H
