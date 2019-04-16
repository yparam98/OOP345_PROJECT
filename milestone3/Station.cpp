//	program    : Station.cpp
//	programmer : Yathavan, Parameshwaran
//	date       : April 16, 2019
//	professor  : Chris, Szalwinski

#include "Station.h"

namespace sict
{
	// default constructor, initializes ItemSet sub-object with incoming string
	Station::Station(std::string &incomingString) : myItemSet(incomingString)
	{		
	}

	// display query, prints ItemSet subobject to display
	void Station::display(std::ostream &os) const
	{
		myItemSet.display(os, true);
	}    

	// fill function, fills the customer object at back of queue
	void Station::fill(std::ostream &os)
	{
		if (myCustomerOrder.size() >  0) 
		{
			if (!myCustomerOrder.back().isFilled()) 
			{
				myCustomerOrder.back().fillItem(myItemSet, os);
			} 			
		}
	}

	// name query, returns name of item
	const std::string& Station::getName() const
	{
		return myItemSet.getName();
	}

	// order release query, returns true if there is an order to be released
	bool Station::hasAnOrderToRelease() const
	{
		if (myCustomerOrder.empty())
		{
			return false;
		}
		else if (myCustomerOrder.front().isItemFilled(myItemSet.getName()))
		{
			return true;
		}
		else if (myItemSet.getQuantity() == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	// -- operator overload, calls the -- operator overload in ItemSet module
	Station& Station::operator--()
	{
		myItemSet.operator--();
		return *this;
	}

	// += operator overload, adds incoming rvalue CustomerOrder object to queue
	Station& Station::operator+=(CustomerOrder &&order)
	{
		CustomerOrder* newOrder = new CustomerOrder();
		newOrder->operator=(std::move(order));
		myCustomerOrder.push_back(std::move(*newOrder));			
		
		delete newOrder;			
		return *this;
	}

	// pop function, moves first order to incoming CustomerOrder object and pops it off queue
	bool Station::pop(CustomerOrder& ready)
	{
		if(!myCustomerOrder.empty())
		{
			ready.operator=(std::move(myCustomerOrder.front()));	
			
			myCustomerOrder.pop_front();
		
			return ready.isFilled() ? true : false;
		}
		else
		{
			return false;
		}
	}

	// validate query, prints validation information about item
	void Station::validate(std::ostream &os) const
	{
		os << " getName(): " << myItemSet.getName() 
			<< "\n getSerialNumber(): " << myItemSet.getSerialNumber()
			<< "\n getQuantity(): " << myItemSet.getQuantity()
			<< std::endl;
	}
}
