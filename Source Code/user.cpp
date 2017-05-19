#include "user.h"

User::User()
{

}

void User::buy(string item, string team, double p)
{
    ILB::Souvenir s;
    s.item_name = item;
    s.origin_stadium_name = team;
    s.item_price = p;
    purchases.push_back(s);
}

//?
//ILB::Souvenir* User::getPurchases()
//{
//    ILB::Souvenir* purchaseList = purchases;
//    return purchaseList;
//}

ILB::Souvenir User::operator[](int index)
{
    vector<ILB::Souvenir>::iterator it = purchases.begin()+index;
    return *it;
}
