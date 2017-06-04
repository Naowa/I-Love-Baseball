//VERSION 0.0.2
#include "user.h"
#include "stadium.h"

using std::string;
using ILB::Souvenir;
using std::vector;
using std::cout;
using std::endl;

void User::buy(string item_name, string stadium_name, double price) {
    Souvenir purchase;
    purchase.item_name = item_name;
    purchase.origin_stadium_name = stadium_name;
    purchase.item_price = price;
    this->purchases.push_back(purchase);
}

vector<ILB::Souvenir> User::get_purchases() {
    return this->purchases;
}

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

Souvenir User::operator [](string item_name) {
    return this->get_souvenir(item_name);
}

Souvenir User::operator[](int index) {
    assert(index < this->purchases.size());
    return this->purchases[index];
}

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
