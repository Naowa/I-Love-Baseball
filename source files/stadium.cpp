//VERSION 0.1.0

#include "stadium.h"

using std::string;
using std::to_string;
using std::cout;
using std::endl;

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

void ILB::Stadium::initialize_souvenirs() {
    Souvenir initial_item1;
    Souvenir initial_item2;
    Souvenir initial_item3;
    Souvenir initial_item4;

//    initial_item1.item_name = "Baseball Cap";
//    initial_item1.item_price = 25.99;
//    initial_item1.origin_stadium_name = this->stadium_name;

//    initial_item2.item_name = "Baseball Bat";
//    initial_item2.item_price = 35.35;
//    initial_item2.origin_stadium_name = this->stadium_name;

//    initial_item3.item_name = "Team Pennant";
//    initial_item3.item_price = 12.99;
//    initial_item3.origin_stadium_name = this->stadium_name;

//    initial_item4.item_name = "Autographed Baseball";
//    initial_item4.item_price = 19.99;
//    initial_item4.origin_stadium_name = this->stadium_name;

//    this->souvenirs.push_back(initial_item1);
//    this->souvenirs.push_back(initial_item2);
//    this->souvenirs.push_back(initial_item3);
//    this->souvenirs.push_back(initial_item4);

}

ILB::Souvenir ILB::Stadium::operator[] (int index)
{
    //check out of bounds
    assert(index < souvenirs.size());
    return souvenirs[index];
}

ILB::Souvenir ILB::Stadium::operator[] (string name) {
    return this->get_souviner(name);
}

ILB::Souvenir ILB::Stadium::get_souviner(string name) {
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

void ILB::Stadium::add_souvenir(string input_item_name, double input_item_price)
{
    Souvenir new_souvenir;
    new_souvenir.origin_stadium_name = stadium_name;
    new_souvenir.item_name = input_item_name;
    new_souvenir.item_price = input_item_price;

    souvenirs.push_back(new_souvenir);
}

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

bool ILB::Stadium::change_souvenir_name(string name, string new_name) {
    for (int i = 0; i < souvenirs.size(); i++){
        if (souvenirs[i].item_name == name){
            souvenirs[i].item_name = new_name;
            return true;
        }
    }
    return false;
}

bool ILB::Stadium::change_souvenir_price(string name, double price) {
    for (int i = 0; i < souvenirs.size(); i++){
        if (souvenirs[i].item_name == name){
            souvenirs[i].item_price = price;
            return true;
        }
    }
    return false;
}

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

bool ILB::Stadium::operator ==(ILB::Stadium& B){
    return(this->stadium_name==B.stadium_name);
}
bool ILB::Stadium::operator ==(std::string B){
    return(this->stadium_name==B);
}

bool ILB::Stadium::find_souvenir(std::string target_item_name)
{
    for (int i = 0; i < souvenirs.size(); i++){
        if (souvenirs[i].item_name == target_item_name){
            return true;
        }
    }
    return false;
}
