#ifndef SICT_LINE_MANAGER_H
#define SICT_LINE_MANAGER_H

#include <iostream>
#include <vector>
#include "Station.h"


namespace sict
{
    class LineManager
    {

    public:
        LineManager(std::vector<Station*> &incomingStationAddr, std::vector<size_t> &incomingsizetobjects, std::vector<CustomerOrder> &incomingCustomerOrders, int index, std::ostream& os);
        void display(std::ostream& os) const;
        bool run(std::ostream& os);
    };
}

#endif // SICT_LINE_MANAGER_H