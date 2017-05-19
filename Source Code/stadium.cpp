//VERSION 0.0.4

#include "stadium.h"

using std::string;
using std::cout;
using std::endl;

ILB::Stadium::Stadium(){
    stadium_name = "NO STADIUM NAME";
    team_name = "NO TEAM NAME";
    street_address = "NO STREET ADDRESS";
    city_state_zip = "NO CITY, STATE, ZIP";
    box_office_number = "NO BOX OFFICE NUMBER";
    american_league = false;
    grass = false;
    date_opened = 0;
    seating_capacity = 0;
    this->initialize_souvenirs();
}

ILB::Stadium::Stadium(string input_stadium_name) {
    stadium_name = input_stadium_name;
    team_name = "NO TEAM NAME";
    street_address = "NO STREET ADDRESS";
    city_state_zip = "NO CITY, STATE, ZIP";
    box_office_number = "NO BOX OFFICE NUMBER";
    american_league = false;
    grass = false;
    date_opened = 0;
    seating_capacity = 0;
    this->initialize_souvenirs();
}

ILB::Stadium::Stadium(string input_stadium_name, string input_team_name, string input_street_address,
        string input_city_state_zip, string input_box_office_number, int input_date_opened,
        int input_seating_capacity, bool input_american_league, bool input_grass){
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
}

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

ILB::Souvenir ILB::Stadium::operator[] (int index)
{
    //check out of bounds
    assert(index < souvenirs.size());
    return souvenirs[index];
}

ILB::Souvenir ILB::Stadium::operator[] (std::string name) {
    return this->get_souviner(name);
}

ILB::Souvenir ILB::Stadium::get_souviner(std::string name) {
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

void ILB::Stadium::display_stadium_info()
{
    cout << stadium_name << endl;
    cout << team_name << endl;
    cout << street_address << endl;
    cout << city_state_zip << endl;
    cout << box_office_number << endl;
    cout << "Opened - " << date_opened << endl;
    cout << "Capacity - " << seating_capacity << endl;

    if (grass) cout << "Is a grass stadium." << endl;
    else cout << "Is not a grass stadium." << endl;

    if (american_league) cout << "Is part of American League." << endl;
    else cout << "Is part of National League." << endl;
}

void ILB::Stadium::add_souvenir(string input_item_name, double input_item_price)
{
    Souvenir new_souvenir;
    new_souvenir.origin_stadium_name = stadium_name;
    new_souvenir.item_name = input_item_name;
    new_souvenir.item_price = input_item_price;

    souvenirs.push_back(new_souvenir);
}

void ILB::Stadium::remove_souvenir(string target_item_name)
{
    for (int i = 0; i < souvenirs.size(); i++){
        if (souvenirs[i].item_name == target_item_name){
            souvenirs.erase(souvenirs.begin() + i);
            return;
        }
    }
}

void ILB::Stadium::display_souvenirs()
{
    for (int i = 0; i < souvenirs.size(); i++){
        cout << "{" << souvenirs[i].item_name << ", " << souvenirs[i].item_price << "}";
        cout << ", ";
    }
}

void ILB::Stadium::change_souvenir_name(std::string name, std::string new_name) {
    for (int i = 0; i < souvenirs.size(); i++){
        if (souvenirs[i].item_name == name){
            souvenirs[i].item_name = new_name;
            return;
        }
    }
}

void ILB::Stadium::change_souvenir_price(std::string name, double price) {
    for (int i = 0; i < souvenirs.size(); i++){
        if (souvenirs[i].item_name == name){
            souvenirs[i].item_price = price;
            return;
        }
    }
}

