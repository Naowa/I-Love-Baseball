//VERSION 0.1.0

#include "stadium.h"

using std::string;
using std::to_string;
using std::cout;
using std::endl;

/**********************************************************
 *
 * Stadium
 *_________________________________________________________
 * default constructor
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following will need defined values
 * needs all stadium info
 *
 **********************************************************/

//O(1)
ILB::Stadium::Stadium() : Vertex(){
    stadium_name = "NO STADIUM NAME";
    team_name = "NO TEAM NAME";
    street_address = "NO STREET ADDRESS";
    city_state_zip = "NO CITY, STATE, ZIP";
    box_office_number = "NO BOX OFFICE NUMBER";
    american_league = false;
    grass = false;
    date_opened = "01/01/2000";
    seating_capacity = 0;
    this->initialize_souvenirs();

}

/**********************************************************
 *
 * Stadium
 *_________________________________________________________
 * one param constructor
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following will need defined values
 * needs all stadium info
 *
 **********************************************************/

//O(1)
ILB::Stadium::Stadium(string input_stadium_name) : Vertex(input_stadium_name){
    stadium_name = input_stadium_name;
    team_name = "NO TEAM NAME";
    street_address = "NO STREET ADDRESS";
    city_state_zip = "NO CITY, STATE, ZIP";
    box_office_number = "NO BOX OFFICE NUMBER";
    american_league = false;
    grass = false;
    date_opened = "01/01/2000";
    seating_capacity = 0;
    this->initialize_souvenirs();
    name=stadium_name;
}

/**********************************************************
 *
 * Stadium
 *_________________________________________________________
 * multi param constructor
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following will need defined values
 * needs all stadium info
 *
 **********************************************************/

//O(1)
ILB::Stadium::Stadium(string input_stadium_name, string input_team_name, string input_street_address,
        string input_city_state_zip, string input_box_office_number, string input_date_opened,
        int input_seating_capacity, bool input_american_league, bool input_grass) : Vertex(input_stadium_name){
    stadium_name = input_stadium_name;
    team_name = input_team_name;
    street_address = input_street_address;
    city_state_zip = input_city_state_zip;
    box_office_number = input_box_office_number;
    american_league = input_american_league;
    grass = input_grass;
    date_opened = input_date_opened;
    seating_capacity = input_seating_capacity;
    this->initialize_souvenirs();
    name=stadium_name;
}

/**********************************************************
 *
 * initialize_souvenirs
 *_________________________________________________________
 * initializes souvenirs
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following will need defined values
 * souvenirs: needs a souvenirs vector
 *
 **********************************************************/

//O(1)
void ILB::Stadium::initialize_souvenirs() {
    Souvenir initial_item1;
    Souvenir initial_item2;
    Souvenir initial_item3;
    Souvenir initial_item4;

    initial_item1.item_name = "Baseball Cap";
    initial_item1.item_price = 25.99;
    initial_item1.origin_stadium_name = this->stadium_name;

    initial_item2.item_name = "Baseball Bat";
    initial_item2.item_price = 35.35;
    initial_item2.origin_stadium_name = this->stadium_name;

    initial_item3.item_name = "Team Pennant";
    initial_item3.item_price = 12.99;
    initial_item3.origin_stadium_name = this->stadium_name;

    initial_item4.item_name = "Autographed Baseball";
    initial_item4.item_price = 19.99;
    initial_item4.origin_stadium_name = this->stadium_name;

    this->souvenirs.push_back(initial_item1);
    this->souvenirs.push_back(initial_item2);
    this->souvenirs.push_back(initial_item3);
    this->souvenirs.push_back(initial_item4);

}

/**********************************************************
 *
 * operator[]
 *_________________________________________________________
 * accesses a souvenir based on index
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following will need defined values
 * souvenirs: needs a souvenirs vector
 *
 **********************************************************/

//O(1)
ILB::Souvenir ILB::Stadium::operator[] (int index)
{
    //check out of bounds
    assert(index < souvenirs.size());
    return souvenirs[index];
}

/**********************************************************
 *
 * operator[]
 *_________________________________________________________
 * accesses a souvenir based on name
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following will need defined values
 * name: needs a name of a souvenir
 *
 **********************************************************/

//O(1)
ILB::Souvenir ILB::Stadium::operator[] (string name) {
    return this->get_souvenir(name);
}

/**********************************************************
 *
 * get_souvenir
 *_________________________________________________________
 * returns a souvenir object with a name
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following will need defined values
 * name: needs a name of a souvenir
 * souvenirs: needs a vector of souvenirs
 *
 **********************************************************/

//O(n)
ILB::Souvenir ILB::Stadium::get_souvenir(string name) {
    try {
        for (Souvenir item : souvenirs) {
            if (item.item_name == name) {
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
 * display_stadium_info
 *_________________________________________________________
 * displays stadium info by returning a string
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following will need defined values
 * needs all stadium properties
 *
 **********************************************************/

//O(1)
string ILB::Stadium::display_stadium_info()
{
    string output_Str;

    output_Str += stadium_name; output_Str += "\n";
    output_Str += "     "; output_Str += team_name; output_Str += "\n";
    output_Str += "     "; output_Str += street_address; output_Str += "\n";
    output_Str += "     "; output_Str += city_state_zip; output_Str += "\n";
    output_Str += "     "; output_Str += box_office_number; output_Str += "\n";
    output_Str += "     "; output_Str += "Opened - "; output_Str += date_opened; output_Str += "\n";
    output_Str += "     "; output_Str += "Capacity - "; output_Str += to_string(seating_capacity); output_Str += "\n";

    return output_Str;
}

/**********************************************************
 *
 * add_souvenir
 *_________________________________________________________
 * adds a souvenir to souvenirs vector
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following will need defined values
 * input_item_name: needs an item name
 * input_item_price: needs an item price
 *
 **********************************************************/

//O(1)
void ILB::Stadium::add_souvenir(string input_item_name, double input_item_price)
{
    Souvenir new_souvenir;
    new_souvenir.origin_stadium_name = stadium_name;
    new_souvenir.item_name = input_item_name;
    new_souvenir.item_price = input_item_price;

    souvenirs.push_back(new_souvenir);
}

/**********************************************************
 *
 * remove_souvenir
 *_________________________________________________________
 * removes a souvenir
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following will need defined values
 * souvenirs: needs a souvenirs vector
 * target_item_name: needs a target item name
 *
 **********************************************************/

//O(n)
bool ILB::Stadium::remove_souvenir(string target_item_name)
{
    for (int i = 0; i < souvenirs.size(); i++){
        if (souvenirs[i].item_name == target_item_name){
            souvenirs.erase(souvenirs.begin() + i);
            return true;
        }
    }
    return false;
}

/**********************************************************
 *
 * display_souvenirs
 *_________________________________________________________
 * displays souvenirs
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following will need defined values
 * souvenirs: needs a souvenirs vector
 *
 **********************************************************/

//O(n)
string ILB::Stadium::display_souvenirs()
{
    string output_Str;

    for (int i = 0; i < souvenirs.size(); i++){
        output_Str += "{";
        output_Str += souvenirs[i].item_name; output_Str += ", ";
        output_Str += to_string(souvenirs[i].item_price);
        output_Str += "}";
        output_Str += ", ";
    }

    return output_Str;
}

/**********************************************************
 *
 * change_souvenir_name
 *_________________________________________________________
 * changes souvenir names
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following will need defined values
 * souvenirs: needs a souvenirs vector
 * name: needs a name of souvenir
 * new_name: needs a new name to change souvenir name
 *
 **********************************************************/

//O(n)
bool ILB::Stadium::change_souvenir_name(string name, string new_name) {
    for (int i = 0; i < souvenirs.size(); i++){
        if (souvenirs[i].item_name == name){
            souvenirs[i].item_name = new_name;
            return true;
        }
    }
    return false;
}

/**********************************************************
 *
 * change_souvenir_price
 *_________________________________________________________
 * changes souvenir prices
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following will need defined values
 * souvenirs: needs a souvenirs vector
 * name: needs a name of souvenir
 * price: needs new price
 *
 **********************************************************/

//O(n)
bool ILB::Stadium::change_souvenir_price(string name, double price) {
    for (int i = 0; i < souvenirs.size(); i++){
        if (souvenirs[i].item_name == name){
            souvenirs[i].item_price = price;
            return true;
        }
    }
    return false;
}

/**********************************************************
 *
 * operator =
 *_________________________________________________________
 * assignment operator
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following will need defined values
 * needs all stadium properties
 * B: needs a stadium
 *
 **********************************************************/

//O(1)
ILB::Stadium& ILB::Stadium::operator=(const Stadium& B){
     stadium_name=B.stadium_name;
     team_name=B.team_name;
     street_address=B.street_address;
     city_state_zip=B.city_state_zip;
     box_office_number=B.box_office_number;
     date_opened=B.date_opened;
     seating_capacity=B.seating_capacity;
     american_league=B.american_league;
     grass=B.grass;
     name=B.stadium_name;

     return *this;

}

/**********************************************************
 *
 * operator ==
 *_________________________________________________________
 * comparison operator
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following will need defined values
 * stadium_name: needs a stadium name
 *
 **********************************************************/

//O(1)
bool ILB::Stadium::operator ==(ILB::Stadium& B){
    return(this->stadium_name==B.stadium_name);
}

/**********************************************************
 *
 * operator ==
 *_________________________________________________________
 * comparison operator
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following will need defined values
 * stadium_name: needs a stadium name
 *
 **********************************************************/

//O(1)
bool ILB::Stadium::operator ==(std::string B){
    return(this->stadium_name==B);
}

/**********************************************************
 *
 * find_souvenir
 *_________________________________________________________
 * finds a souvenir with item name
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following will need defined values
 * target_item_name: needs a target item name
 *
 **********************************************************/

//O(n)
bool ILB::Stadium::find_souvenir(std::string target_item_name)
{
    for (int i = 0; i < souvenirs.size(); i++){
        if (souvenirs[i].item_name == target_item_name){
            return true;
        }
    }
    return false;
}
