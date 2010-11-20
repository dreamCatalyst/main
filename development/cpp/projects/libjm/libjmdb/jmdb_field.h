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


#ifndef JMDB_FIELD_H
#define JMDB_FIELD_H

#include <string>


namespace JM {
namespace DB {

/**
 * 
 */
class Field
{
public:
	Field(const bool isNull = false) : m_isNull(isNull) { }
	
	virtual bool isNull() const { return m_isNull; }
	
	virtual const char* getString() = 0;
	virtual double getDouble() const = 0;
	virtual int getInt() const = 0;
	virtual long int getLong() const = 0;
	virtual unsigned int getUInt() const = 0;
	virtual long unsigned int getULong() const = 0;
	
	/**
	 * Use this method only for fields that you know are of the BinaryDataField type.
	 * It is not implemented for other types!
	 */
	virtual char* getBinary(int* len) const = 0;
	
protected:
	bool m_isNull;
};


class StringField : public Field
{
public:
	StringField() : Field(true) { }
	StringField(const char* val) : m_val(val) { }
	virtual ~StringField() { }
	
	virtual const char* getString();
	virtual double getDouble() const;
	virtual int getInt() const;
	virtual long int getLong() const;
	virtual unsigned int getUInt() const;
	virtual long unsigned int getULong() const;
	virtual char* getBinary(int* len) const;
protected:
	std::string m_val;
};


class IntField : public Field
{
public:
    IntField() : Field(true), m_val(0) { }
	IntField(const int v) : m_val(v) { }
	virtual ~IntField() { }
	
	virtual const char* getString();
	virtual double getDouble() const;
	virtual int getInt() const;
	virtual long int getLong() const;
	virtual unsigned int getUInt() const;
	virtual long unsigned int getULong() const;
	virtual char* getBinary(int* len) const;
protected:
	int m_val;
	std::string m_strVal;
};


class RealField : public Field
{
public:
    RealField() : Field(true), m_val(0.0) { }
	RealField(const double v) : m_val(v) { }
	virtual ~RealField() { }
	
	virtual const char* getString();
	virtual double getDouble() const;
	virtual int getInt() const;
	virtual long int getLong() const;
	virtual unsigned int getUInt() const;
	virtual long unsigned int getULong() const;
	virtual char* getBinary(int* len) const;
protected:
	double m_val;
	std::string m_strVal;
};


/**
 * BinaryField is a special field type in that it doesn't convert to other
 * datatypes. At all.
 * If a column in a database is of this type it's content can only be retrieved
 * as straight binary data.
 */
class BinaryDataField : public Field
{
public:
	BinaryDataField() : Field(true), m_data(0), m_length(0) { }
	BinaryDataField(const char* data, unsigned int length);
	virtual ~BinaryDataField();
	
	virtual const char* getString() { return ""; }
	virtual double getDouble() const { return 0.0; }
	virtual int getInt() const { return 0; }
	virtual long int getLong() const { return 0l; }
	virtual unsigned int getUInt() const { return 0; }
	virtual long unsigned int getULong() const { return 0l; }
	
	virtual char* getBinary(int* len) const;
protected:
	char* m_data;
	unsigned int m_length;
};

} } // namespace JM::DB

#endif // JMDB_FIELD_H
