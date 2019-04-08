#include "Station.h"

namespace sict
{
	Station::Station(std::string &incomingString)
	{
		this->myItemSet = new ItemSet(incomingString);
	}

	void Station::display(std::ostream &os) const
	{
		myItemSet->display(os, myItemSet->getQuantity());
	}    

	void Station::fill(std::ostream &os)
	{
		if (myCustomerOrder.size() >  0) 
		{
			if (!myCustomerOrder[myCustomerOrder.size()]->isFilled()) 
			{
				myCustomerOrder[myCustomerOrder.size()]->fillItem(*myItemSet, os); 
			} 
		}
	}

	const std::string& Station::getName() const
	{
		return myItemSet->getName();
	}

	bool Station::hasAnOrderToRelease() const
	{
		if (myCustomerOrder[0]->isFilled() || myItemSet->getQuantity() == 0) 
		{
			return true;
		}
		else if (myCustomerOrder.size() == 0) 
		{
			return false;
		}
		else
		{
			return false;
		}
	}

	Station& Station::operator--()
	{
		myItemSet->operator--();
		return *this;
	}

	Station& Station::operator+=(CustomerOrder &&order)
	{
		myCustomerOrder.push_back(&order);
		return *this;
	}

	bool Station::pop(CustomerOrder& ready)
	{
		// • bool pop(CustomerOrder& ready) – a modifier that receives an lvalue reference to a
		// customer order, removes the order at the front of the queue and moves it to the calling
		// function through the parameter list. This function returns true if the station filled its
		// part of the order; false otherwise. If there are no orders in the queue, this function
		// returns false.

		
		ready.operator=(std::move(*myCustomerOrder[0]));

		myCustomerOrder.pop_front();

		if (ready.isFilled()) 
		{
			return true;
		}
		else if (myCustomerOrder.size() == 0) 
		{
			return false;
		}
		else
		{
			return false;
		}

	}

	void Station::validate(std::ostream &os) const
	{
		os << " getItem(): " << myItemSet->getName() 
			<< "\n getSerialNumber(): " << myItemSet->getSerialNumber()
			<< "\n getQuantity(): " << myItemSet->getQuantity()
			<< std::endl;
	}
}
