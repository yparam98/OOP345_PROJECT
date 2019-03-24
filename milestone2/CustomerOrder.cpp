#include <iostream>
#include "CustomerOrder.h"
#include "Utilities.h"

namespace sict
{
    CustomerOrder::CustomerOrder()
    {
        customerName.clear();
        assembledProduct.clear();
        components.clear();
    }

    CustomerOrder::CustomerOrder(const std::string& incomingStr)
    {
        
    }

    CustomerOrder::~CustomerOrder()
    {

    }

    void CustomerOrder::fillItem(ItemSet& item, std::ostream& os)
    {

    }

    bool CustomerOrder::isFilled() const
    {

    }

    bool CustomerOrder::isItemFilled(const std::string& item) const
    {

    }

    std::string CustomerOrder::getNameProduct() const
    {

    }

    void CustomerOrder::display(std::ostream& os, bool showDetail) const
    {

    }
}