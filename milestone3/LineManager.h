#ifndef SICT_LINE_MANAGER_H
#define SICT_LINE_MANAGER_H

#include <iostream>
#include <vector>
#include "Station.h"


namespace sict
{
    class LineManager
    {
        std::vector<Station*> myStation;
        std::vector<CustomerOrder> myCustomerOrder;
        std::vector<size_t> myIndexes;
        int startingVal{0};
        std::ostream* myOutputStream;
        size_t secondVal{0};
    public:
        LineManager(std::vector<Station*> &incomingStationAddr, std::vector<size_t> &incomingsizetobjects, std::vector<CustomerOrder> &incomingCustomerOrders, int index, std::ostream& os);
        void display(std::ostream& os) const;
        bool run(std::ostream& os);
    };
}

#endif // SICT_LINE_MANAGER_H