#include "LineManager.h"

namespace sict
{
	LineManager::LineManager(std::vector<Station*> &incomingStationAddr, std::vector<size_t> &incomingsizetobjects, std::vector<CustomerOrder> &incomingCustomerOrders, int index, std::ostream& os)
	{
        int arrayOne[incomingStationAddr.size()];

        myCustomerOrder = incomingCustomerOrders;
	}

	void LineManager::display(std::ostream& os) const
	{

	}

	bool LineManager::run(std::ostream& os)
	{
        if(!myCustomerOrder[myCustomerOrder.size()].isFilled())
        {
            
        }
	}
}