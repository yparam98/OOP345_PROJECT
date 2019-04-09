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
		bool inCompleted{false};
		
		if (!myCustomerOrder[myCustomerOrder.size()-1].isFilled())
		{
			CustomerOrder newObj;
			if (myStation[myIndexes[0]]->pop(newObj))
			{
				for (size_t index = 1; index < myStation.size(); index++)
				{
					if (myStation[myIndexes[index]]->hasAnOrderToRelease())
					{
						myStation[myIndexes[index]]->fill(os);
					}
					else
					{
						inCompleted = true;
					}					
				}
			}
		}
		if (inCompleted)
		{
			incompleteOrders.push_back(std::move(myCustomerOrder[myCustomerOrder.size()-1]));
			return false;
		}
		else
		{
			completeOrders.push_back(std::move(myCustomerOrder[myCustomerOrder.size()-1]));
			return true;
		}
	}
}
