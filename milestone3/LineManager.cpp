#include "LineManager.h"

namespace sict
{
	LineManager::LineManager(std::vector<Station*> &incomingStationAddr, std::vector<size_t> &incomingsizetobjects, std::vector<CustomerOrder> &incomingCustomerOrders, int index, std::ostream& os)
	{
		myStation = incomingStationAddr;
		myCustomerOrder = std::move(incomingCustomerOrders);
		myIndexes = incomingsizetobjects;
		startingVal = index;
		myOutputStream = &os;
		secondVal = myIndexes.at(startingVal);
	}

	void LineManager::display(std::ostream& os) const
	{
		for (size_t index = 0; index < myCustomerOrder.size(); index++)
		{
			if (!myCustomerOrder[index].isFilled())
			{
				myCustomerOrder[index].display(os);
			}
		}
	}

	bool LineManager::run(std::ostream& os)
	{
		try 
		{
			for (size_t index = 0; index < myStation.size(); index++)
			{
				if (!this->myCustomerOrder[myCustomerOrder.size()].isFilled())
				{
					myStation[this->myIndexes[index]]->operator+=(std::move(myCustomerOrder[index]));
					myStation[this->myIndexes[index]]->fill(os);
				}
			}
			return true;
		}
		catch(...)
		{
			return false;
		}
	}
}
