//VERSION 0.0.0.2

#ifndef STADIUM_H
#define STADIUM_H

#include <cassert>
#include <vector>
#include <iostream>

namespace ILB {

struct Souvenir{
    std::string origin_stadium_name;
    std::string item_name;
    double item_price;
};

class Stadium
{
public:
    //PUBLIC FUNCTIONS
    Stadium();
    Stadium(std::string input_stdium_name);
    Stadium(std::string input_stadium_name, std::string input_team_name, std::string input_street_address,
                std::string input_city_state_zip, std::string input_box_office_number, int input_date_opened,
                int input_seating_capacity, bool input_american_league, bool input_grass);

    void add_souvenir(std::string input_item_name, double input_item_price);             //add_souvenir - adds a new souvenir to the souvenirs vector
    void display_souvenirs();                                                       ///**display_souvenirs - displays souvenirs to console (test function)
    void display_stadium_info();                                                    ///**display_stadium_info - displays stadium info to console (test function)
    Souvenir operator[] (int index);                                               //operator [] - overloaded bracket operator for souvenirs vector
    Souvenir operator[] (std::string name);
    void remove_souvenir(std::string target_item_name);                                  //remove_souvenir - removes a souvenir from souvenirs vector

    //SETTERS
    inline void set_stadium_name(std::string input){ stadium_name = input; }
    inline void set_team_name(std::string input){ team_name = input; }
    inline void set_street_address(std::string input){ street_address = input; }
    inline void set_city_state_zip(std::string input){ city_state_zip = input; }
    inline void set_box_office_number(std::string input){ box_office_number = input; }
    inline void set_date_opened(int input){ date_opened = input; }
    inline void set_seating_capacity(int input){ seating_capacity = input; }
    inline void set_american_league(bool input){ american_league = input; }
    inline void set_grass(bool input){ grass = input; }

    //GETTERS
    inline std::string get_stadium_name(){ return stadium_name; }
    inline std::string get_team_name(){ return team_name; }
    inline std::string get_street_address(){ return street_address; }
    inline std::string get_city_state_zip(){ return city_state_zip; }
    inline std::string get_box_office_number(){ return box_office_number; }
    inline int get_date_opened(){ return date_opened; }
    inline int get_seating_capacity(){ return seating_capacity; }
    inline int get_size(){ return souvenirs.size(); }
    inline bool if_american_league(){ return american_league;}
    inline bool if_national_leauge(){ return !(american_league); }
    inline bool if_grass(){ return grass; }

    //SOUVENIR SETTERS
    void change_souvenir_name(std::string name, std::string new_name);
    void change_souvenir_price(std::string name, double price);


private:
    //STADIUM PROPERTIES
    std::string stadium_name;
    std::string team_name;
    std::string street_address;
    std::string city_state_zip;
    std::string box_office_number;
    int date_opened;
    int seating_capacity;
    bool american_league;
    bool grass;


    //SOUVENIR PROPERTIES
    std::vector<Souvenir> souvenirs;                 //Souvenirs - vector of souvenir structs
};

}       //ILB namespace

#endif // STADIUM_H
