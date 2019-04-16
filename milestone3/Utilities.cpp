//	program    : Utilities.cpp
//	programmer : Yathavan, Parameshwaran
//	date       : March 4, 2019
//	professor  : Chris, Szalwinski

#include <iostream>
#include "Utilities.h"

namespace sict
{
	char Utilities::myDelim = '\0';
	size_t Utilities::myFieldWidth = 0;

	//default constructor
	Utilities::Utilities() {}

	//extracts tokens based on incoming params
	const std::string Utilities::extractToken(const std::string & str, size_t & next_pos)
	{
		std::string tempStr;
		size_t positionOfDelim = str.find(getDelimiter(),next_pos);

		tempStr = str.substr(next_pos, (positionOfDelim-next_pos)); 

		if (tempStr.length() > myFieldWidth) 
		{
			setFieldWidth(tempStr.length());
		}
		
		if ((str.at(positionOfDelim + 1) != '\0') && (str.at(positionOfDelim + 1) != getDelimiter()) && (positionOfDelim != std::string::npos)) 
		{
			next_pos = positionOfDelim + 1;
		}	
		else if (str.at(positionOfDelim + 1) == getDelimiter())
		{
			throw("delims are too close to one another!");
		}	
		else
		{
			next_pos = std::string::npos;
		}

		return tempStr;
	}

	//returns local delimiter character
	const char Utilities::getDelimiter() const
	{
		return this->myDelim;
	}

	//returns field width for current object
	size_t Utilities::getFieldWidth() const
	{
		return this->myFieldWidth;
	}

	//sets delimiter character based on incoming param
	void Utilities::setDelimiter(const char d)
	{
		myDelim = d;
	}

	//sets field width for current object based on incoming param
	void Utilities::setFieldWidth(size_t t)
	{
		myFieldWidth = t;
	}
}