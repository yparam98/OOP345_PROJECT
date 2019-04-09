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
		lastStation = myIndexes.back();
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
			for (stationIterator = myStation.begin(); stationIterator != myStation.end(); stationIterator++) // for each station
			{
				(*stationIterator)->fill(os); // execute the fill step
				for (size_t index = 0; index < myStation.size(); index++) 
				{
					if (myStation.at(myIndexes.at(index))->hasAnOrderToRelease()) // if any station has an order to be released
					{
						CustomerOrder newOrder; 
						myStation.at(myIndexes.at(index))->pop(newOrder); // move that order into new object
						if (myStation.at(myIndexes.at(index))->getName() == (*myStation.end())->getName()) // if last station
						{
							if (newOrder.isFilled()) // if filled
							{
								completeOrders.push_back(std::move(newOrder)); // move to completed orders queue
							}
							else // if not filled
							{
								incompleteOrders.push_back(std::move(newOrder)); // move to incompleted orders queue
							}							
						}
					}
				}				
			}	
			processedOrdersCount++;
			myCustomerOrder.pop_back();		
		}

		{
			bool completed{true};
			for (customerOrderIterator = myCustomerOrder.begin(); customerOrderIterator != myCustomerOrder.end(); customerOrderIterator++)
			{
				if (!customerOrderIterator->isFilled())
				{
					completed = false;
				}
			}
			return completed ? true : false; // return true if all orders completed
		}
	}
}
