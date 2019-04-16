#include "LineManager.h"

namespace sict
{
	LineManager::LineManager(std::vector<Station*> &incomingStationAddr, std::vector<size_t> &incomingsizetobjects, std::vector<CustomerOrder> &incomingCustomerOrders, int index, std::ostream& os)
	{
		myStation = incomingStationAddr;

		sizeOfOrders = incomingCustomerOrders.size();

		// myCustomerOrder = std::move(incomingCustomerOrders);

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

			lastStation =  myIndexes.back();

			myIndexes = incomingsizetobjects;
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
		// CustomerOrder* newOrder = new CustomerOrder(); // creating new CustomerOrder object 
		CustomerOrder newOrder;

		if (!myCustomerOrder.back().isFilled()) // if the customer order on back of queue not filled 
		{
			myStation.at(startingVal) = &myStation.at(startingVal)->operator+=(std::move(myCustomerOrder.back())); // move the customer order at back of queue to the station at starting position
		}
			for (auto stationIterator = myStation.begin(); stationIterator != myStation.end(); stationIterator++) // cycle through every station
			{
				(*stationIterator)->fill(os); // fill station positioned at every incrementing iteration				
			}

			myCustomerOrder.pop_back(); // remove the station at back of the queue
		
		//size_t temp{0}; // creating size_t variable called temp, initialized to 0

		for (size_t myIndexesIterator = 0; myIndexesIterator < myStation.size(); myIndexesIterator++) // cycle through every every element in myIndexes container
		{
			//temp++; // increment temp variable by one for every iteration

			if (myStation.at(myIndexesIterator)->hasAnOrderToRelease()) // if the station at position of current myIndex has an order to release
			{
				if (myIndexesIterator == 3) // if current station is not the last station
				{
					processedOrdersCount++;	// increments the count for processed order
					if (myStation.at(myIndexesIterator)->pop(newOrder)) // moves the first order in station's customer order queue to newOrder, and returns true if the station filled its part of the order
					{
						*myOutputStream << " --> " << newOrder.getNameProduct() << " moved from " << myStation.at(myIndexesIterator)->getName() << " to " << "Completed Set" << std::endl;

						completeOrders.push_back(std::move(newOrder)); // move order to completed queue
						// delete &newOrder; // deallocate memory for newOrder
					}
					else
					{
						*myOutputStream << " --> " << newOrder.getNameProduct() << " moved from " << myStation.at(myIndexesIterator)->getName() << " to " << "Incomplete Set" << std::endl;

						incompleteOrders.push_back(std::move(newOrder)); // if order is not filled, move to incomplete queue
						// delete &newOrder; // deallocate memory for newOrder
					}
				}
				else
				{
					
					myStation.at(myIndexesIterator)->pop(newOrder);

					*myOutputStream << " --> " << newOrder.getNameProduct() << " moved from " << myStation.at(myIndexesIterator)->getName() << " to " << myStation.at(myIndexes.at(myIndexesIterator))->getName() << std::endl;

					myStation.at(myIndexes.at(myIndexesIterator))->operator+=(std::move(newOrder)); // ERROR -> OBJECT NOT PROPERLY MOVING, THE OBJECT PUSHED INTO STATION IS JUST A POINTER TO THIS OBJECT!! // move the order to the next station
					// delete &newOrder; // deallocates memory for newOrder
					// delete newOrder;
					//	}
				}
			} 
		}
		return processedOrdersCount == sizeOfOrders ? true : false; // returns true of false, depending if the number of processed orders match the number of original orders
	}
}
