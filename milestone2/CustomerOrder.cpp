#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include "CustomerOrder.h"
#include "Utilities.h"

namespace sict
{
    CustomerOrder::CustomerOrder()
    {
        customerName.clear();
        assembledProduct.clear();
        ItemInfo.itemName.clear();
        ItemInfo.serialNumber = 0;
        
    }

    CustomerOrder::CustomerOrder(const std::string& incomingStr)
    {
        size_t beginningOfStr = 0;
		size_t positionOfFirstDelim = 0;
		size_t positionOfSecondDelim = 0;
		size_t positionOfThirdDelim = 0;
        static int counter = 0;

		positionOfFirstDelim = incomingStr.find(helperObject.getDelimiter());
		std::string newStr = incomingStr.substr(positionOfFirstDelim + 1, incomingStr.length());
		positionOfSecondDelim = newStr.find_first_of(helperObject.getDelimiter());	
		std::string newStr1 = newStr.substr(positionOfSecondDelim + 1, newStr.length());
		positionOfThirdDelim = incomingStr.rfind(helperObject.getDelimiter());

        try
        {
            this->customerName = helperObject.extractToken(incomingStr,positionOfFirstDelim);
            this->assembledProduct = helperObject.extractToken(newStr,beginningOfStr);
            
            
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
    }

    CustomerOrder::~CustomerOrder()
    {

    }

    CustomerOrder::CustomerOrder(CustomerOrder&& incomingObj)
    {

    }

    CustomerOrder& CustomerOrder::operator=(CustomerOrder&& incomingObj)
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