#ifndef __STORE_H
#define __STORE_H

#include "tool.h"
#include "plant.h"
#include "mulch.h"

#include "customer.h"
#include "order.h"

#include <algorithm>
#include <vector>

bool compareNames(Customer* lhs, Customer* rhs);

class Store {
  public:
    Store(std::string name);
    Store(std::istream& ist);     // Open a previously saved store | check lecture 17 canvas.h and canvas.cpp
    void save(std::ostream& ost); // Save the store
    
    std::string get_filename() {return _name;}
    void add_product(const Tool& product);
    void add_product(const Plant& product);
    void add_product(const Mulch& product);
    int products();
    Product& product(int index);
    
    void add_customer(const Customer& customer);
    int customers();
    const Customer& customer(int index);
    
    // look around pages 36 and 50 on pdf for slides 22
    // maybe page 25 as well, as well as 34
    
    int add_order(const Customer& customer); // _orders.push_back(new Order{customer});
    void add_item(int order, Product& product, int quantity);
    int orders(); // replace with iterators
    const Order& order(int index); // replace with iterators
    std::string storeName();
    
    //bool sortByName(const Customer &lhs, const Customer &rhs);
    //std::string getName(Customer& customer) {return customer.getCustomerName();}
    
    //bool compare(Customer* lhs, Customer* rhs);
    
    // https://stackoverflow.com/questions/34757448/sorting-a-vector-of-objects-alphabetically-in-c
    void sortCustomers();
  private:
    std::string _name;
    std::vector<Product*> _products;
    std::vector<Customer*> _customers;
    std::vector<Order*> _orders;
};

class Order_store {
    private:
        std::string _customer; // customer who has the order
        typedef std::vector<Order> Orders;
        Orders c_orders; // the customers list of orders
    public:
        Order_store(std::string customer_name) : _customer{customer_name} { }
        std::string customer_name() {return _customer;}
        void add_order(Order order) {c_orders.push_back(order);}
        
        typedef Orders::iterator iterator; 
        typedef Orders::const_iterator const_iterator;
        iterator begin() {return c_orders.begin();}
        iterator end() {return c_orders.end();}
};

#endif
