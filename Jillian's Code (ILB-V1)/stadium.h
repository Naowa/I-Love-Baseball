//VERSION 0.0.0.1

#ifndef STADIUM_H
#define STADIUM_H

#include <cassert>
#include <vector>
#include <iostream>
using namespace std;

namespace ILB {

struct Souvenir{
    string origin_stadium_name;
    string item_name;
    double item_price;
};

class Stadium
{
public:
    //PUBLIC FUNCTIONS
    Stadium();
    Stadium(string input_stadium_name, string input_team_name, string input_street_address,
                string input_city_state_zip, string input_box_office_number, int input_date_opened,
                int input_seating_capacity);

    void add_souvenir(string input_item_name, double input_item_price);             //add_souvenir - adds a new souvenir to the souvenirs vector
    void display_souvenirs();                                                       ///**display_souvenirs - displays souvenirs to console (test function)
    void display_stadium_info();                                                    ///**display_stadium_info - displays stadium info to console (test function)
    Souvenir operator [] (int index);                                               //operator [] - overloaded bracket operator for souvenirs vector
    void remove_souvenir(string target_item_name);                                  //remove_souvenir - removes a souvenir from souvenirs vector

    //SETTERS
    inline void set_stadium_name(string input){ stadium_name = input; }
    inline void set_team_name(string input){ team_name = input; }
    inline void set_street_address(string input){ street_address = input; }
    inline void set_city_state_zip(string input){ city_state_zip = input; }
    inline void set_box_office_number(string input){ box_office_number = input; }
    inline void set_date_opened(int input){ date_opened = input; }
    inline void set_seating_capacity(int input){ seating_capacity = input; }

    //GETTERS
    inline string get_stadium_name(){ return stadium_name; }
    inline string get_team_name(){ return team_name; }
    inline string get_street_address(){ return street_address; }
    inline string get_city_state_zip(){ return city_state_zip; }
    inline string get_box_office_number(){ return box_office_number; }
    inline int get_date_opened(){ return date_opened; }
    inline int get_seating_capacity(){ return seating_capacity; }
    inline int get_size(){ return Souvenirs.size(); }

private:
    //STADIUM PROPERTIES
    string stadium_name;
    string team_name;
    string street_address;
    string city_state_zip;
    string box_office_number;
    int date_opened;
    int seating_capacity;

    //SOUVENIR PROPERTIES
    vector<Souvenir> Souvenirs;                 //Souvenirs - vector of souvenir structs
};

}       //ILB namespace

#endif // STADIUM_H
