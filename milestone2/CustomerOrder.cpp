#include <iostream>
#include <sstream>
#include <string>
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
        size_t positionOfFirstDelim = incomingStr.find_first_of(helperObject.getDelimiter);
        size_t positionOfSecondDelim{0};
        size_t positionOfThirdDelim{0};
        size_t beginningOfStr{0};

        customerName = helperObject.extractToken(incomingStr, beginningOfStr);
        assembledProduct = helperObject.extractToken(incomingStr, positionOfFirstDelim);
        size_t pos;
        while ((pos = incomingStr.find(helperObject.getDelimiter())) != std::string::npos)
        {
            components.push_back(helperObject.extractToken(incomingStr,pos));
            incomingStr.erase(0, pos + 1);
        }
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