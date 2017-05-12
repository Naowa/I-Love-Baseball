#ifndef USER_H
#define USER_H
#include <iostream>
#include <vector>
#include "stadium.h"

class User
{
public:
    User();
//    User(const User& other);
//    ~User();
//    void operator =(const User& other);
    void buy(string item, string team, double p);
//    ILB::Souvenir* getPurchases();//?
//    ILB::Souvenir operator [](string item);  doesnt make sense to make this
    ILB::Souvenir operator [](int index);
private:
    vector<ILB::Souvenir> purchases;
};

#endif // USER_H
