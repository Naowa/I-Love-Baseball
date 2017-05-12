//VERSION 0.0.0.1

#include "stadium.h"

ILB::Stadium::Stadium(){
    stadium_name = "NO STADIUM NAME";
    team_name = "NO TEAM NAME";
    street_address = "NO STREET ADDRESS";
    city_state_zip = "NO CITY, STATE, ZIP";
    box_office_number = "NO BOX OFFICE NUMBER";
    date_opened = 0;
    seating_capacity = 0;
}

ILB::Stadium::Stadium(string input_stadium_name, string input_team_name, string input_street_address,
        string input_city_state_zip, string input_box_office_number, int input_date_opened,
        int input_seating_capacity){
    stadium_name = input_stadium_name;
    team_name = input_team_name;
    street_address = input_street_address;
    city_state_zip = input_city_state_zip;
    box_office_number = input_box_office_number;
    date_opened = input_date_opened;
    seating_capacity = input_seating_capacity;
}

ILB::Souvenir ILB::Stadium::operator [] (int index)
{
    //check out of bounds
    assert(index < Souvenirs.size());
    return Souvenirs[index];
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
}

void ILB::Stadium::add_souvenir(string input_item_name, double input_item_price)
{
    Souvenir new_souvenir;
    new_souvenir.origin_stadium_name = stadium_name;
    new_souvenir.item_name = input_item_name;
    new_souvenir.item_price = input_item_price;

    Souvenirs.push_back(new_souvenir);
}

void ILB::Stadium::remove_souvenir(string target_item_name)
{
    for (int i = 0; i < Souvenirs.size(); i++){
        if (Souvenirs[i].item_name == target_item_name){
            Souvenirs.erase(Souvenirs.begin() + i);
            return;
        }
    }
}

void ILB::Stadium::display_souvenirs()
{
    for (int i = 0; i < Souvenirs.size(); i++){
        cout << "{" << Souvenirs[i].item_name << ", " << Souvenirs[i].item_price << "}";
        cout << ", ";
    }
}

