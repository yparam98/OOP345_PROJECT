#include "LineManager.h"

namespace sict
{
	LineManager::LineManager(std::vector<Station*> &incomingStationAddr, std::vector<size_t> &incomingsizetobjects, std::vector<CustomerOrder> &incomingCustomerOrders, int index, std::ostream& os)
	{
		myStation = incomingStationAddr;
		myCustomerOrder = std::move(incomingCustomerOrders);
		startingVal = index;
		myOutputStream = &os;

		{
			myIndexes.push_back(index);
			for (size_t index = 0; index < incomingsizetobjects.size(); index++)
			{
				myIndexes.push_back(incomingsizetobjects.at(myIndexes[index]));
			}
			
			myIndexes.pop_back();
		}
	}

	void LineManager::display(std::ostream& os) const
	{
		os << "COMPLETED ORDERS\n";
		for (size_t index = 0; index < completeOrders.size(); index++)
		{			
			completeOrders.at(index).display(os,true);
		}
		os << "INCOMPLETE ORDERS\n";
		for (size_t index = 0; index < completeOrders.size(); index++)
		{			
			incompleteOrders.at(index).display(os,true);
		}
	}

	bool LineManager::run(std::ostream &os)
	{
		if (!myCustomerOrder.back().isFilled()) // if last order is not filled
		{
			myStation.at(startingVal)->operator+=(std::move(myCustomerOrder.back())); // move to starting station
			for (auto indexIterator2 = myIndexes.cbegin(); indexIterator2 != myIndexes.cend(); indexIterator2++) // for each station
			{
				myStation[*indexIterator2]->fill(os); // execute the fill step
				for (auto indexIterator = myIndexes.cbegin(); indexIterator != myIndexes.cend(); indexIterator++) 
				{
					if (myStation.at(*indexIterator)->hasAnOrderToRelease()) // if any station has an order to be released
					{
						CustomerOrder newOrder; 
						myStation.at(*indexIterator)->pop(newOrder); // move that order into new object
						if ((*indexIterator2) == myIndexes.back()) // if last station
						{
							if (newOrder.isFilled()) // if filled
							{
								completeOrders.push_back(std::move(newOrder)); // move to completed orders queue
								os << "--> ";
								newOrder.display(os, false);
								os << "moved from" << myStation.at(*indexIterator2)->getName() << " to Completed Set" << std::endl;
							}
							else // if not filled
							{
								incompleteOrders.push_back(std::move(newOrder)); // move to incompleted orders queue
								os << "--> ";
								newOrder.display(os, false);
								os << "moved from" << myStation.at(*indexIterator2)->getName() << " to Incomplete Set" << std::endl;
							}							
						}
					}
				}				
			}	
			processedOrdersCount++;
			myCustomerOrder.pop_back();		
		}
		return processedOrdersCount == myCustomerOrder.size() ? true : false;
	}
}
