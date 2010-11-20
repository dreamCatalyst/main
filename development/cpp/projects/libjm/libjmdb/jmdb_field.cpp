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


#include "jmdb_field.h"
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <cstdio>

namespace JM {
namespace DB {


// ---------------------------- StringField implementation

char* StringField::getBinary(int* len) const
{
	len = 0;
	return 0;
}

double StringField::getDouble() const
{
	if(isNull())
		return 0.0;
	return atof(m_val.c_str());
}

int StringField::getInt() const
{
	if(isNull())
		return 0;
	return atoi(m_val.c_str());
}

long int StringField::getLong() const
{
	if(isNull())
		return 0;
	return atoll(m_val.c_str());
}

const char* StringField::getString()
{
	if(isNull())
		return "";  // TODO should we return an empty string or "NULL"??
	return m_val.c_str();
}

unsigned int StringField::getUInt() const
{
	return getULong();
}


long unsigned int StringField::getULong() const
{
	if(isNull())
		return 0;
	
	// homegrown always tastes better :)
	const unsigned int min = '0';
	const unsigned int max = '9';
	const unsigned int len = m_val.size();
	const char* str = m_val.c_str();
	
	// Check if all characters are valid numbers
	for(unsigned int i=0; i < len; ++i)
		if(str[i] < min || str[i] > max)
			return 0;
	
	long unsigned int value = 0;
	long unsigned int multiplier = 1;
	for(int i=len-1; i >= 0; --i) {
		int charVal = str[i] - min;  // a little funky char arithmetic
		value += (charVal * multiplier);
		multiplier *= 10;
	}
	return value;
}


// ---------------------------- IntField implementation

char* IntField::getBinary(int* len) const
{
	*len = 0;
	return 0;
}

double IntField::getDouble() const
{
	if(isNull())
		return 0.0;
	return (double)m_val;
}

int IntField::getInt() const
{
	if(isNull())
		return 0;
	return m_val;
}

long int IntField::getLong() const
{
	if(isNull())
		return 0;
	return m_val;
}

const char* IntField::getString()
{
	if(isNull())
		return "";
	
	if(m_strVal.empty()) {
		char buff[80]; // 80 characters is more than enough (min = sizeof(int)*8+2) (2=opt.sign + \0)
		sprintf(buff, "%d", m_val);
		m_strVal = buff;
	}
	return m_strVal.c_str();
}

unsigned int IntField::getUInt() const
{
	if(isNull())
		return 0;
	if(m_val < 0)
		return 0;
	return m_val;
}

long unsigned int IntField::getULong() const
{
	if(isNull())
		return 0;
	if(m_val < 0)
		return 0;
	return m_val;
}


// ---------------------------- RealField implementation

char* RealField::getBinary(int* len) const
{
	*len = 0;
	return 0;
}

double RealField::getDouble() const
{
	if(isNull())
		return 0.0;
	return m_val;
}

int RealField::getInt() const
{
	if(isNull())
		return 0;
	return round(m_val);
}

long int RealField::getLong() const
{
	if(isNull())
		return 0;
	return round(m_val);
}

const char* RealField::getString()
{
	if(isNull())
		return "";
	if(m_strVal.empty()) {
		// buff-size: sizeof(double)*8+3 = 71
		char buff[80];
		sprintf(buff, "%f", m_val);
		
		// strip off trailing zeros -sigh-
		while( strlen(buff) > 0 && buff[ strlen(buff)-1 ] == '0' )
			buff[ strlen(buff) -1 ] = '\0';
		
		if(strlen(buff) == 0) {
			buff[0] = '0';
			buff[1] = '\0';
		}
		if(buff[ strlen(buff) -1 ] == '.')
			buff[ strlen(buff) -1 ] = '\0';
		
		m_strVal = buff;
	}
	return m_strVal.c_str();
}

unsigned int RealField::getUInt() const
{
	if(isNull())
		return 0;
	if(m_val < 0)
		return 0;
	return round(m_val);
}

long unsigned int RealField::getULong() const
{
	if(isNull())
		return 0;
	if(m_val < 0)
		return 0;
	return round(m_val);
}


// ---------------------------- BinaryDataField implementation

BinaryDataField::BinaryDataField(const char* data, unsigned int length)
{
	m_data = new char[length];
	memcpy(m_data, data, length);
	m_length = length;
}

char* BinaryDataField::getBinary(int* len) const
{
	*len = m_length;
	return m_data;
}

BinaryDataField::~BinaryDataField()
{
	delete m_data;
	m_data = 0;
}


} } // namespace JM::DB

