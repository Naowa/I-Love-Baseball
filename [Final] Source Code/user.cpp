//VERSION 0.0.2
#include "user.h"
#include "stadium.h"

using std::string;
using ILB::Souvenir;
using std::vector;
using std::cout;
using std::endl;

/**********************************************************
 *
 * buy
 *_________________________________________________________
 * allows buying of souvenirs
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following will need defined values
 * item_name: needs an item name
 * stadium_name: needs a stadium name
 * price: needs a price
 * purchases: needs a purchases struct
 *
 **********************************************************/

//O(1)
void User::buy(string item_name, string stadium_name, double price) {
    Souvenir purchase;
    purchase.item_name = item_name;
    purchase.origin_stadium_name = stadium_name;
    purchase.item_price = price;
    this->purchases.push_back(purchase);
}

/**********************************************************
 *
 * get_purchases
 *_________________________________________________________
 * returns souvenirs vector
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following will need defined values
 * purchases: needs a purchases
 *
 **********************************************************/

//O(1)
vector<ILB::Souvenir> User::get_purchases() {
    return this->purchases;
}

/**********************************************************
 *
 * get_souvenir
 *_________________________________________________________
 * returns a souvenir with item name
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following will need defined values
 * purchases: needs a purchases
 *
 **********************************************************/

//O(n)
Souvenir User::get_souvenir(string item_name) {
    try {
        for (Souvenir item : purchases) {
            if (item.item_name == item_name) {
                return item;
            }
        }
        throw;
    }
    catch (...) {
        cout << "Souvenir not found." << endl;
    }
}

/**********************************************************
 *
 * operator []
 *_________________________________________________________
 * returns a souvenir with item name
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following will need defined values
 * item_name: returns souvenir with item name
 *
 **********************************************************/

//O(1)
Souvenir User::operator [](string item_name) {
    return this->get_souvenir(item_name);
}

/**********************************************************
 *
 * operator []
 *_________________________________________________________
 * returns a souvenir with item name
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following will need defined values
 * purchases: needs a purchases vector
 * index: needs an index
 *
 **********************************************************/

//O(1)
Souvenir User::operator[](int index) {
    assert(index < this->purchases.size());
    return this->purchases[index];
}

/**********************************************************
 *
 * display_purchases
 *_________________________________________________________
 * displays purchases
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following will need defined values
 * purchases: needs a purchases vector
 *
 **********************************************************/

//O(n)
std::string User::display_purchases()
{
    string output_Str;

    for (int i = 0; i < this->purchases.size(); i++){
        output_Str += "{";
        output_Str += this->purchases[i].item_name; output_Str += ", ";
        output_Str += std::to_string(this->purchases[i].item_price);
        output_Str += "}";
        output_Str += ", ";
    }

    return output_Str;
}
