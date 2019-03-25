//	program    : CustomerOrder.h
//	programmer : Yathavan, Parameshwaran
//	date       : March 22, 2019
//	professor  : Chris, Szalwinski

#ifndef SICT_CUSTOMER_ORDER_H
#define SICT_CUSTOMER_ORDER_H

#include <iostream>
#include <string>
#include <deque>
#include <sstream>
#include <algorithm>

#include "Utilities.h"
#include "ItemSet.h"

namespace sict
{
    const unsigned int maxNumOfItems = 10;

    class CustomerOrder
    {
        Utilities helperObject;
        ItemSet itemSetObject;
        std::string customerName;
        std::string assembledProduct;
        int subCounter{0};
        
        struct
        {
            std::string itemName;
            long serialNumber{0};
            bool filled{false};
        } ItemInfo[maxNumOfItems];

    public:
        CustomerOrder();
        CustomerOrder(const std::string& incomingStr);
        ~CustomerOrder();
        CustomerOrder (CustomerOrder&& incomingObj);
        CustomerOrder& operator=(CustomerOrder&& incomingObj);
        void fillItem(ItemSet& item, std::ostream& os);
        bool isFilled() const;
        bool isItemFilled(const std::string& item) const;
        std::string getNameProduct() const;
        void display(std::ostream& os, bool showDetail = false) const;
    };
}

#endif // SICT_CUSTOMER_ORDER_H