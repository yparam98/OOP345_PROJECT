//	program    : CustomerOrder.cpp
//	programmer : Yathavan, Parameshwaran
//	date       : March 22, 2019
//	professor  : Chris, Szalwinski

#define _CRT_SECURE_NO_WARNINGS

#include "CustomerOrder.h"
#include "Utilities.h"

namespace sict
{
    CustomerOrder::CustomerOrder()
    {
        customerName.clear();
        assembledProduct.clear();
        ItemInfo->itemName.clear();        
    }

    CustomerOrder::CustomerOrder(const std::string& incomingStr)
    {
        size_t beginningOfStr = 0;
		size_t positionOfFirstDelim = 0;
		size_t positionOfSecondDelim = 0;
		
        positionOfFirstDelim = incomingStr.find(helperObject.getDelimiter());
		std::string newStr = incomingStr.substr(positionOfFirstDelim + 1, incomingStr.length());
		positionOfSecondDelim = newStr.find_first_of(helperObject.getDelimiter());	
		std::string newStr1 = newStr.substr(positionOfSecondDelim + 1, newStr.length());
		
        try
        {
            this->customerName = helperObject.extractToken(incomingStr,beginningOfStr);
            this->assembledProduct = helperObject.extractToken(newStr,beginningOfStr);
            {
                size_t pos{0};
                newStr1 += '|';
                while ((pos = newStr1.find(helperObject.getDelimiter())) != std::string::npos) 
                {
                    ItemInfo[subCounter++].itemName = helperObject.extractToken(newStr1, beginningOfStr); 
                    newStr1.erase(0, pos+1); 
                }
            }
        }
        catch(const char* incomingErrorMessage)
        {
            std::cout << incomingErrorMessage << std::endl;
        }
        myFieldWidthForCustomerName = customerName.length();
    }

    CustomerOrder::~CustomerOrder()
    {

    }

    CustomerOrder::CustomerOrder(CustomerOrder&& incomingObj)
    {
        *this = std::move(incomingObj);
    }

    CustomerOrder& CustomerOrder::operator=(CustomerOrder&& incomingObj)
    {
        if (this != &incomingObj)
        {
            this->customerName = incomingObj.customerName;
            this->assembledProduct = incomingObj.assembledProduct;
            this->myFieldWidthForCustomerName = incomingObj.myFieldWidthForCustomerName;
            this->subCounter = incomingObj.subCounter;
            for (int index = 0; index < incomingObj.subCounter; index++)
            {
                this->ItemInfo[index].itemName = incomingObj.ItemInfo[index].itemName;
                this->ItemInfo[index].serialNumber = incomingObj.ItemInfo[index].serialNumber;
                this->ItemInfo[index].filled = incomingObj.ItemInfo[index].filled;                
            }

            incomingObj.customerName.clear();
            incomingObj.assembledProduct.clear();
            incomingObj.myFieldWidthForCustomerName = 0;
            incomingObj.subCounter = 0;
            for (int index = 0; index < incomingObj.subCounter; index++)
            {
                incomingObj.ItemInfo[index].itemName.clear();
                incomingObj.ItemInfo[index].serialNumber = 0;
                incomingObj.ItemInfo[index].filled = false;                
            }
        }
        return *this;
    }

    void CustomerOrder::fillItem(ItemSet& item, std::ostream& os)
    {
        for (int index = 0; index < subCounter; index++)
        {
            if (ItemInfo[index].itemName == item.getName())
            {
                ItemInfo[index].serialNumber = item.getSerialNumber();

                if (ItemInfo[index].filled != true && item.getQuantity() > 0)
                {
                    os << "Filled " << this->customerName
                       << " [" << this->assembledProduct << "]"
                       << "[" << item.getName() << "]"
                       << "[" << item.getSerialNumber() << "]"
                       << std::endl;

                    item.operator--();
                }
                else if (ItemInfo[index].filled == true)
                {
                    os << "Unable to fill " << this->customerName
                       << " [" << this->assembledProduct << "]"
                       << "[" << item.getName() << "]"
                       << "[" << item.getSerialNumber() << "]"
                       << " already filled" << std::endl;
                }
                else if (item.getQuantity() == 0)
                {
                    os << "Unable to fill " << this->customerName
                       << " [" << this->assembledProduct << "]"
                       << "[" << item.getName() << "]"
                       << "[" << item.getSerialNumber() << "]"
                       << " out of stock" << std::endl;
                }
                else
                {
                    os << "Your code is incorrect..." << std::endl;
                }
            }
        }
    }

    bool CustomerOrder::isFilled() const
    {
        bool temp{false};
        for (int index = 0; index < subCounter; index++)
        {
            if (ItemInfo[index].filled)
            {
                temp = true;
            }
        }

        if (temp)
            return true;
        else    
            return false;
    }

    bool CustomerOrder::isItemFilled(const std::string& item) const
    {
        for (int index = 0; index < subCounter; index++)
        {
            if (ItemInfo[index].itemName == item)
            {
                if (ItemInfo[index].filled == true)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
        }
        return false;
    }

    std::string CustomerOrder::getNameProduct() const
    {
        return (this->customerName + " [" + this->assembledProduct + "]");
    }

    void CustomerOrder::display(std::ostream& os, bool showDetail) const
    {
        if (showDetail)
        {
            os << this->customerName << " [" << this->assembledProduct << "]" << std::endl;
            for (int index = 0; index < subCounter; index++)
            {
                std::string temp;

                os << std::left << std::setw(myFieldWidthForCustomerName+1) 
                << "[" << ItemInfo[index].serialNumber << "] " 
                << ItemInfo[index].itemName
                << " - ";

                if (ItemInfo[index].filled)
                    temp = "true";
                else
                    temp = "false";

                os << temp << std::endl;
            }
        }
        else
        {
            os << this->customerName << " [" << this->assembledProduct << "]" << std::endl;
            for (int index = 0; index < subCounter; index++)
            {
                os << std::left << std::setw(myFieldWidthForCustomerName+1) << ItemInfo[index].itemName << std::endl;
            }
        }        
    }
}