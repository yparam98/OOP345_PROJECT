#include "Station.h"

namespace sict
{
    Station::Station(std::string &incomingString)
    {
        /* A one-argument constructor that receives a reference 
        to an unmodifiable string and passes that reference to 
        the ItemSet sub-object of the current object */

        this->myItemSet = new ItemSet(incomingString);
    }

    void Station::display(std::ostream &os) const
    {
        /* a query that receives a reference to an std::ostream 
        object os and displays the data for its ItemSet on os. */

        myItemSet->display(os, myItemSet->getQuantity());
        
    }    

    void Station::fill(std::ostream &os)
    {
        /* a modifier that fills the last order in the customer 
        order queue, if there is one. If the queue is empty, 
        this function does nothing */

        if (myCustomerOrder.size() >  0) // if queue exists...
        {
            if (!myCustomerOrder[myCustomerOrder.size()]->isFilled()) // if the last order is not filled
            {
                myCustomerOrder[myCustomerOrder.size()]->fillItem(*myItemSet, os); // fill order
            } 
        }
    }

    const std::string& Station::getName() const
    {
        /* – a forwarding query that returns a reference 
        to the name of the ItemSet sub-object. */
        return myItemSet->getName();
    }

    bool Station::hasAnOrderToRelease() const
    {
        /* a query that returns the release state of the current object. 
        This function returns true if the station has filled the item 
        request(s) for the customer order at the front of the queue 
        or the station has no items left; otherwise, it returns false. 
        If there are no orders in the queue, this function returns false. */

        if (myCustomerOrder[0]->isFilled() || myItemSet->getQuantity() == 0) // if station filled item request for order OR station has no items left
        {
            return true;
        }
        else if (myCustomerOrder.size() == 0) // if no orders in queue
        {
            return false;
        }
        else
        {
            return false;
        }
    }

    Station& Station::operator--()
    {
        /* a modifier that decrements the number of items in the ItemSet, 
        increments the serial number for the next item, and returns a 
        reference to the current object. */

        myItemSet->operator--();
        return *this;
    }

    Station& Station::operator+=(CustomerOrder &&order)
    {
        /* a modifier that receives an rvalue reference to a customer 
        order and moves that order to the back of the station’s queue 
        and returns a reference to the current object */

        myCustomerOrder.push_back(&order);
        return *this;
    }

    bool Station::pop(CustomerOrder& ready)
    {
        /* a modifier that receives an lvalue reference to a customer 
        order, removes the order at the front of the queue and moves 
        it to the calling function through the parameter list. This 
        function returns true if the station filled its part of the 
        order; false otherwise. If there are no orders in the queue, 
        this function returns false */

        // ask prof for help 

	// recieve: reference to a customer order object
	// return: boolean value stating order filled or not
	// do: remove order @ front of queue, move to calling function
		  
	// how do I remove an order from a queue, when the only thing I recieve is a reference to a CustomerOrder object!?!?!?      
        
        myCustomerOrder.pop_front(); // remove order @ front of queue, BUT... the "ready" needs to be somewhere involved in this
         
        if (ready.isFilled()) // check if filled
        {
            return true;
        }
        else if (myCustomerOrder.size() == 0) // check if queue empty
        {
            return false;
        }
        else
        {
            return false;
        }
        
    }
    
    void Station::validate(std::ostream &os) const
    {
        /* a query that reports the state of the ItemSet object in 
        the following format:
                                getName(): ITEM
                                getSerialNumber(): SERIAL NUMBER
                                getQuantity(): NUMBER_OF_ITEMS_LEFT
        A detailed example of the formatting is shown in the output above. */

        os << " getItem(): " << myItemSet->getName() 
            << "\n getSerialNumber(): " << myItemSet->getSerialNumber()
            << "\n getQuantity(): " << myItemSet->getQuantity()
            << std::endl;
    }
}
