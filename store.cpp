#include "store.h"
#include <stdexcept>
#include <cstdlib>

bool compareNames(Customer *lhs, Customer *rhs) { return lhs->getCustomerName() < rhs->getCustomerName(); }

Store::Store(std::string name) : _name{name} {}

Store::Store(std::istream &ist)
{
    std::getline(ist, _name);
    int size;
    std::string s;

    ist >> size;
    ist.ignore(32767, '\n');
    while (size-- > 0)
    {
        std::getline(ist, s);
        if (s == "tool")
            _products.push_back(new Tool(ist));
        else if (s == "plant")
            _products.push_back(new Plant(ist));
        else if (s == "mulch")
            _products.push_back(new Mulch(ist));
        else if (s.size())
            throw std::runtime_error{"Invalid product type on input: " + s};
    }

    ist >> size;
    ist.ignore(32767, '\n');
    while (size-- > 0)
    {
        _customers.push_back(new Customer(ist));
    }

    ist >> size;
    ist.ignore(32767, '\n');
    if (ist.eof())
        return; // Older file format
    while (size-- > 0)
    {
        _orders.push_back(new Order(ist));
    }
}

void Store::save(std::ostream &ost)
{
    ost << _name << '\n';

    ost << _products.size() << '\n';
    for (Product *p : _products)
        p->save(ost);

    ost << _customers.size() << '\n';
    for (Customer *c : _customers)
        c->save(ost);

    ost << _orders.size() << '\n';
    for (Order *o : _orders)
        o->save(ost);
}

std::string Store::storeName() { return _name; }

void Store::add_product(const Tool &product) { _products.push_back(new Tool{product}); }
void Store::add_product(const Plant &product) { _products.push_back(new Plant{product}); }
void Store::add_product(const Mulch &product) { _products.push_back(new Mulch{product}); }
int Store::products() { return _products.size(); }
Product &Store::product(int index) { return *_products.at(index); }

void Store::add_customer(const Customer &customer)
{
    // sortByName(&customer); tried to order here but it wasn't working
    // sortByName(&customer);
    _customers.push_back(new Customer{customer});
}
int Store::customers()
{
    return _customers.size();
}

const Customer &Store::customer(int index)
{
    return *_customers.at(index);
}

int Store::add_order(const Customer &customer)
{
    _orders.push_back(new Order{customer});
    return _orders.size() - 1;
}
void Store::add_item(int order, Product &product, int quantity)
{
    _orders[order]->add_item(Item{product, quantity});
}

////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// P11  C O D E //////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

// https://www.cplusplus.com/reference/algorithm/sort/
// https://stackoverflow.com/questions/1380463/sorting-a-vector-of-custom-objects

// void Store::sortByName() {return std::sort(_customers.begin(), _customers.end());}

void Store::sortCustomers()
{
    std::sort(_customers.begin(), _customers.end(), compareNames);
}

// I know you guys wanted a composite class that was able to do iterators. But each time I tried it would tell me
// I was out of scope on what I was trying to access, so doing the iterators for the vector already in our store class
// was all I knew how to do. I had issues with the other way you wanted it done, but I do have my composite class still there.

int Store::orders()
{
    int Count = 0;
    for (std::vector<Order *>::iterator o = _orders.begin(); o != _orders.end(); ++o)
        ++Count;
    return Count;
}

const Order &Store::order(int index)
{
    std::vector<Order *>::iterator o = _orders.begin();
    advance(o, index); // http://www.cplusplus.com/reference/iterator/advance/
    return **o;        // http://www.cplusplus.com/reference/iterator/advance/
}

/*
int Order_store::orders() {
    int Count = 0;
    for(Orders::iterator o = c_orders.begin(); o != c_orders.end(); ++o)
    Count++;
    return Count;
}

const Order& Order_store::order(int index) {
    Orders::iterator o = c_orders.begin();
    advance(o, index);  // http://www.cplusplus.com/reference/iterator/advance/
    return **o;         // http://www.cplusplus.com/reference/iterator/advance/
}
*/
