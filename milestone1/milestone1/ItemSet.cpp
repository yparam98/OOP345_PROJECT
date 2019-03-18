//	program    : ItemSet.cpp
//	programmer : Yathavan, Parameshwaran
//	date       : March 4, 2019
//	professor  : Chris, Szalwinski

#include <iostream>
#include "ItemSet.h"

namespace sict
{
	//default constructor
	ItemSet::ItemSet()
	{
		this->myName.clear();
		this->myDescription.clear();
	}

	//1 arg. constructor, initializes object
	ItemSet::ItemSet(std::string & incomingStr)
	{
		size_t beginningOfStr = 0;
		size_t positionOfFirstDelim = 0;
		size_t positionOfSecondDelim = 0;
		size_t positionOfThirdDelim = 0;

		positionOfFirstDelim = incomingStr.find(helper.getDelimiter());
		std::string newStr = incomingStr.substr(positionOfFirstDelim + 1, incomingStr.length());
		positionOfSecondDelim = newStr.find_first_of(helper.getDelimiter());	
		std::string newStr1 = newStr.substr(positionOfSecondDelim + 1, newStr.length());
		positionOfThirdDelim = incomingStr.rfind(helper.getDelimiter());

		try 
		{
			this->myName = helper.extractToken(incomingStr, beginningOfStr);
			this->mySerialNum = std::stol(helper.extractToken(newStr, beginningOfStr));
			this->myQuantity = std::stoi(helper.extractToken(newStr1, beginningOfStr));
			this->myDescription = incomingStr.substr(positionOfThirdDelim + 1, incomingStr.length());
		}
		catch (const char* errMsg) 
		{
			std::cout << "ERROR : " << errMsg << std::endl;
		}
	}

	//move constructor
	ItemSet::ItemSet(ItemSet && incomingObj)
	{
		if (this != &incomingObj)
		{
			this->myName = incomingObj.myName;
			this->myDescription = incomingObj.myDescription;
			this->mySerialNum = incomingObj.mySerialNum;
			this->myQuantity = incomingObj.myQuantity;

			incomingObj.myName.clear();
			incomingObj.myDescription.clear();
			incomingObj.mySerialNum = 0;
			incomingObj.myQuantity = 0;
		}
	}

	//query, returns name
	const std::string & ItemSet::getName() const
	{
		return this->myName;
	}

	//query, returns serial number
	const unsigned int ItemSet::getSerialNumber() const
	{
		return this->mySerialNum;
	}

	//query, returns quantity
	const unsigned int ItemSet::getQuantity() const
	{
		return this->myQuantity;
	}

	//operator-- overload, gets called when product stock depletes
	ItemSet & ItemSet::operator--()
	{
		this->myQuantity--;
		this->mySerialNum++;
		return *this;
	}

	//display query
	void ItemSet::display(std::ostream & os, bool full) const
	{
		if (full)
		{
			os << std::left << std::setw(helper.getFieldWidth()) << this->myName << " [" <<
				std::setw(5) << this->mySerialNum << "] Quantity " <<
				std::setw(3) << this->myQuantity << " Description: " <<
				this->myDescription << std::endl;
		}
		else
		{
			os << std::left << std::setw(helper.getFieldWidth()) << this->myName << " [" <<
				std::setw(5) << this->mySerialNum << "]" << std::endl;
		}
	}
}