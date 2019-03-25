#ifndef SICT_CUSTOMER_ORDER_H
#define SICT_CUSTOMER_ORDER_H

#include <iostream>
#include <string>
#include <deque>
#include "Utilities.h"
#include "ItemSet.h"

namespace sict
{
    class CustomerOrder
    {
        Utilities helperObject;
        std::string customerName;
        std::string assembledProduct;
        std::deque<std::string> components;

    public:
        CustomerOrder();
        CustomerOrder(const std::string& incomingStr);
        ~CustomerOrder();
        void fillItem(ItemSet& item, std::ostream& os);
        bool isFilled() const;
        bool isItemFilled(const std::string& item) const;
        std::string getNameProduct() const;
        void display(std::ostream& os, bool showDetail) const;
    };
}

#endif // SICT_CUSTOMER_ORDER_H