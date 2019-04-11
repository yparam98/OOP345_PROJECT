#include "LineManager.h"

namespace sict
{
	LineManager::LineManager(std::vector<Station*> &incomingStationAddr, std::vector<size_t> &incomingsizetobjects, std::vector<CustomerOrder> &incomingCustomerOrders, int index, std::ostream& os)
	{
		myStation = incomingStationAddr;

		sizeOfOrders = incomingCustomerOrders.size();

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
		for (size_t index = 0; index < incompleteOrders.size(); index++)
		{			
			incompleteOrders.at(index).display(os,true);
		}
	}

	bool LineManager::run(std::ostream &os)
	{
		if (!myCustomerOrder.back().isFilled()) 
		{
			myStation.at(startingVal)->operator+=(std::move(myCustomerOrder.back())); 

			for (auto stationIterator = myStation.begin(); stationIterator != myStation.end(); stationIterator++) 
			{
				(*stationIterator)->fill(os);			
			}
			myCustomerOrder.pop_back();		
			size_t temp{0};
			for (auto myIndexesIterator = myIndexes.begin(); myIndexesIterator != myIndexes.end(); myIndexesIterator++)
			{
				temp++;

				if (myStation.at(*myIndexesIterator)->hasAnOrderToRelease())
				{
					CustomerOrder newOrder;
					myStation.at(*myIndexesIterator)->pop(newOrder);
					
					if (*myIndexesIterator == myIndexes.back())
					{
						if (newOrder.isFilled())
						{
							*myOutputStream << " --> " << newOrder.getNameProduct() << " moved from " << myStation.at(*myIndexesIterator)->getName() << " to " << "Completed Set" << std::endl;
							completeOrders.push_back(std::move(newOrder));
						}
						else
						{
							*myOutputStream << " --> " << newOrder.getNameProduct() << " moved from " << myStation.at(*myIndexesIterator)->getName() << " to " << "Incomplete Set" << std::endl;
							incompleteOrders.push_back(std::move(newOrder));
						}
					}
					else
					{
						*myOutputStream << " --> " << newOrder.getNameProduct() << " moved from " << myStation.at(*myIndexesIterator)->getName() << " to " << myStation.at(myIndexes.at(temp))->getName() << std::endl;
						myStation.at(myIndexes.at(temp))->operator+=(std::move(newOrder));
					}
				}
			}
			processedOrdersCount++;			
		}
		return processedOrdersCount == sizeOfOrders ? true : false;
	}
}
