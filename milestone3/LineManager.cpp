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
		for (int index = 0; index < myCustomerOrder.size(); index++)
		{
			if (!myCustomerOrder[myCustomerOrder.size()].isFilled) // if the last customer order on the queue has NOT been filled
			{
				for (int j = 0; j < myStation.size(); j++)
				{
					if (myIndexes[index] != myIndexes[myIndexes.size()])
					{
						myStation[myIndexes[index]]->operator+=(std::move(myCustomerOrder[myCustomerOrder.size()]));
						myStation[myIndexes[index]]->fill(os);
						if (myStation[myIndexes[index]]->hasAnOrderToRelease())
						{
							bool test = myStation[myIndexes[index]]->pop(myCustomerOrder[myCustomerOrder.size()]);
						}
					}
					else
					{
						/* code */
						
					}
					
				}
			}
		}
	}
}
