#ifndef SICT_CUSTOMER_ORDER_H
#define SICT_CUSTOMER_ORDER_H

#include <iostream>
#include <string>
#include <deque>
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
        
        struct
        {
            std::string itemName;
            long serialNumber;
            bool filled;
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
        void display(std::ostream& os, bool showDetail) const;
    };
}

#endif // SICT_CUSTOMER_ORDER_H