#include "Station.h"

namespace sict
{
	Station::Station(std::string &incomingString)
	{
		this->myItemSet = new ItemSet(incomingString);
	}

	void Station::display(std::ostream &os) const
	{
		myItemSet->display(os, true);
	}    

	void Station::fill(std::ostream &os)
	{
		if (myCustomerOrder.size() >  0) 
		{
			if (!myCustomerOrder.back().isFilled()) 
			{
				myCustomerOrder.back().fillItem(*myItemSet, os); 
			} 
		}
	}

	const std::string& Station::getName() const
	{
		return myItemSet->getName();
	}

	bool Station::hasAnOrderToRelease() const
	{
		if (myCustomerOrder.empty())
		{
			return false;
		}
		else if (myCustomerOrder.front().isItemFilled(myItemSet->getName()))
		{
			return true;
		}
		else if (myItemSet->getQuantity() == 0)
		{
			return true;
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
		CustomerOrder* newOrder = new CustomerOrder();
		newOrder->operator=(std::move(order));
		myCustomerOrder.push_back(std::move(*newOrder));	
		delete newOrder;			
		return *this;
	}

	bool Station::pop(CustomerOrder& ready)
	{
		if(!myCustomerOrder.empty())
		{
			ready.operator=(std::move(myCustomerOrder.front()));	
			
			myCustomerOrder.pop_front();
		
			return ready.isItemFilled(this->getName()) ? true : false;
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
