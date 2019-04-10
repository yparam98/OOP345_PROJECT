#include "LineManager.h"

namespace sict
{
	LineManager::LineManager(std::vector<Station*> &incomingStationAddr, std::vector<size_t> &incomingsizetobjects, std::vector<CustomerOrder> &incomingCustomerOrders, int index, std::ostream& os)
	{
		myStation = incomingStationAddr;
		
		for (int index = incomingCustomerOrders.size()-1; index >= 0; index--)
		{
			myCustomerOrder.push_back(std::move(incomingCustomerOrders[index]));
		}
		
		startingVal = index;
		myOutputStream = &os;

		{
			myIndexes.push_back(index);
			for (size_t index = 0; index < incomingsizetobjects.size(); index++)
			{
				myIndexes.push_back(incomingsizetobjects.at(myIndexes[index]));
			}
			
			myIndexes.pop_front();
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
		for (size_t index = 0; index < incompleteOrders.size(); index++)
		{			
			incompleteOrders.at(index).display(os,true);
		}
	}

	bool LineManager::run(std::ostream &os)
	{
		if (!myCustomerOrder.back().isFilled()) // if last order is not filled
		{
			myStation.at(startingVal)->operator+=(std::move(myCustomerOrder.back())); // move to starting station

			for (auto stationIterator = myStation.begin(); stationIterator != myStation.end(); stationIterator++) // for each station
			{
				(*stationIterator)->fill(os); // execute the fill step								
			}
			
			for (size_t index = 0; index < myIndexes.size(); index++) // calls hasAnOrderToRelease on every station
			{
				if (myStation.at(index)->hasAnOrderToRelease()) // if any station has an order to be released
				{
					CustomerOrder newOrder;
					myStation.at(index)->pop(newOrder); // move that order into new object

					if (myStation.at(index)->getName() == myStation.at(myIndexes.at(index-1))->getName())   // if last station
					{
						if (newOrder.isFilled()) // if filled
						{
							os << " --> " 
							<< newOrder.getNameProduct() 
							<< " moved from " 
							<< myStation.at(index)->getName() 
							<< " to " 
							<< "Completed Set"
							<< std::endl;
							completeOrders.push_back(std::move(newOrder)); // move to completed orders queue
						}
						else // if not filled
						{
							os << " --> " 
							<< newOrder.getNameProduct() 
							<< " moved from " 
							<< myStation.at(index)->getName() 
							<< " to " 
							<< "Incomplete Set"
							<< std::endl;
							incompleteOrders.push_back(std::move(newOrder)); // move to incompleted orders queue
						}
					}
					else // if not last station
					{
						os << " --> " 
							<< newOrder.getNameProduct() 
							<< " moved from " 
							<< myStation.at(index)->getName() 
							<< " to " 
							<< myStation.at(index+1)->getName() 
							<< std::endl;
							
						myStation.at(myIndexes.at(index))->operator+=(std::move(newOrder));						
					}
				}
			}

			processedOrdersCount++;
			myCustomerOrder.pop_back();		
		}
		return processedOrdersCount == myCustomerOrder.size() ? true : false;
	}
}
