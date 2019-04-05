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
		size_t positionOfDelim = str.find(getDelimiter());

		tempStr = str.substr(next_pos, positionOfDelim); //  This function extracts the next token in the string starting at the position next_pos, and ending immediately before the delimiter character.

		if (tempStr.length() > myFieldWidth) // // This function compares the size of the extracted token to the field width currently stored in the object and if the size of the token is greater than that width increases that width.
		{
			setFieldWidth(tempStr.length());
		}
		
		if (str.at(positionOfDelim + 1) != '\n') // This function returns in next_pos the position of the next token in the string if one exists.
		{
			next_pos = str.at(positionOfDelim + 1);
		}	
		else if (str.at(positionOfDelim + 1) == getDelimiter())// If not, this function returns the position that is beyond the end of the string.
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