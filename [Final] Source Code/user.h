//VERSION 0.0.2
#ifndef USER_H
#define USER_H
#include <iostream>
#include <vector>
#include "stadium.h"

class User
{
public:
    inline User() {}
    void buy(std::string item_name, std::string stadium_name, double price);
    std::vector<ILB::Souvenir> get_purchases();
    ILB::Souvenir get_souvenir(std::string item_name);
    ILB::Souvenir operator [](std::string item_name);
    ILB::Souvenir operator [](int index);
    std::string display_purchases();
private:
    std::vector<ILB::Souvenir> purchases;
};

#endif // USER_H
