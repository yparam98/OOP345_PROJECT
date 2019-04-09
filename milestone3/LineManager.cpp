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
		os << "COMPLETED ORDERS\n";
		for (size_t index = 0; index < completeOrders.size(); index++)
		{			
			completeOrders[index].display(os,true);
		}
		os << "INCOMPLETE ORDERS\n";
		for (size_t index = 0; index < completeOrders.size(); index++)
		{			
			incompleteOrders[index].display(os,true);
		}
	}

	bool LineManager::run(std::ostream &os)
	{
		bool notCompleted{false};

		// if last customer order waiting to be filled
		if (!myCustomerOrder[myCustomerOrder.size()].isFilled())
		{
			// move to starting station
			myStation[myIndexes[0]]->pop(myCustomerOrder[0]);

			for (int index = 1; index < myStation.size(); index++)
			{
				if (myStation[myIndexes[index]]->hasAnOrderToRelease())
				{
					// execute fill of assembly at each station on line
					myStation[myIndexes[index]]->fill(os);
				}
				else
				{
					notCompleted = true;
				}
			}
		}
		if (notCompleted)
		{
			incompleteOrders.push_back(myCustomerOrder[myCustomerOrder.size()]);
		}
		else
		{
			completeOrders.push_back(myCustomerOrder[myCustomerOrder.size()]);
		}

	}
}
