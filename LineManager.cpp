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

	bool LineManager::run(std::ostream& os) // incorrect
	{
		// need to work on this next...
		bool returnVal{ false };

		if (!myCustomerOrder.at(myCustomerOrder.size()-1).isFilled())
		{
			for (int index = 0; index < myStation.size(); index++)
			{
				CustomerOrder newObj;
				myStation[myIndexes[index]]->pop(newObj);
				if (myStation[myIndexes[index]]->hasAnOrderToRelease())
				{
					myStation[myIndexes[index]]->fill(os);
					display(os);
					returnVal = newObj.isFilled() ? false : true;
				}

			}
		}
		return returnVal;
	}
}
