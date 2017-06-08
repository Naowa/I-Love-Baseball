//VERSION 0.0.2
#ifndef USER_H
#define USER_H
#include <iostream>
#include <vector>
#include "stadium.h"

class User
{
public:
    inline User() {}                                                            //User - default user constructor
    void buy(std::string item_name, std::string stadium_name, double price);    //buy - allows purchase of souvenir
    std::vector<ILB::Souvenir> get_purchases();                                 //get_purchases - returns purchases vector
    ILB::Souvenir get_souvenir(std::string item_name);                          //get_souvenir - returns souvenir object
    ILB::Souvenir operator [](std::string item_name);                           //operator [] - overloaded bracket operator
    ILB::Souvenir operator [](int index);                                       //operator [] - overloaded bracket operator
    std::string display_purchases();                                            //display_purchases - returns string of purchases
private:
    std::vector<ILB::Souvenir> purchases;                                       //purchases - vector of purchases
};

#endif // USER_H
