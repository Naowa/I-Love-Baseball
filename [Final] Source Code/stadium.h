//VERSION 0.1.0

#ifndef STADIUM_H
#define STADIUM_H

#include <vertex.h>
#include <cassert>
#include <vector>
#include <iostream>

namespace ILB {

struct Souvenir{
    std::string origin_stadium_name;
    std::string item_name;
    double item_price;
};

class Stadium : public Vertex<std::string>
{
public:
    //PUBLIC FUNCTIONS
    Stadium();                                  //Stadium - dfeault constructor
    Stadium(std::string input_stdium_name);     //Stadium - one param constructor
    Stadium(std::string input_stadium_name, std::string input_team_name, std::string input_street_address,
                std::string input_city_state_zip, std::string input_box_office_number, std::string input_date_opened,
                int input_seating_capacity, bool input_american_league, bool input_grass);          //Stadium - multi param constructor

    void add_souvenir(std::string input_item_name, double input_item_price);             //add_souvenir - adds a new souvenir to the souvenirs vector
    std::string display_souvenirs();                                                     //display_souvenirs - returns a string for displaying souvenirs
    std::string display_stadium_info();                                                  //display_stadium_info - returns string for displaying stadium info
    Souvenir operator[] (int index);                                                     //operator [] - overloaded bracket operator for souvenirs vector
    Souvenir operator[] (std::string name);                                              //operator [] - overloaded bracket operator
    Souvenir get_souvenir(std::string name);                                             //get_souvenir - returns souvenir objects with name
    bool remove_souvenir(std::string target_item_name);                                  //remove_souvenir - removes a souvenir from souvenirs vector
    void initialize_souvenirs();                                                         //initialize_souvenirs - initializes souvenirs
    bool operator==(ILB::Stadium&);                                                      //operator == - overloaded compare operator
    bool operator==(std::string);                                                        //operator == - overloaded compare operator
    bool find_souvenir(std::string target_item_name);                                    //find_souvenir - finds a souvenir with name

    //SETTERS
    inline void set_stadium_name(std::string input){ stadium_name = input; }            //set_stadium_name - sets stadium name
    inline void set_team_name(std::string input){ team_name = input; }                  //set_team_name - sets team name
    inline void set_street_address(std::string input){ street_address = input; }        //set_street_address - sets street addresss
    inline void set_city_state_zip(std::string input){ city_state_zip = input; }        //set_city_state_zip - sets city state zip
    inline void set_box_office_number(std::string input){ box_office_number = input; }  //set_box_office_number - sets box office number
    inline void set_date_opened(std::string input){ date_opened = input; }              //set_date_opened - sets date opened
    inline void set_seating_capacity(int input){ seating_capacity = input; }            //set_seating_capacity - sets seating capacity
    inline void set_american_league(bool input){ american_league = input; }             //set_american_league - sets american league
    inline void set_grass(bool input){ grass = input; }                                 //set_grass - sets grass
    Stadium& operator=(const Stadium& B);                                               //operator = - assignment operator

    //GETTERS
    inline std::string get_name() const{return stadium_name;}                           //get_name - returns stadium name
    inline std::string get_stadium_name(){ return stadium_name; }                       //get_stadium_name - returns stadium name
    inline std::string get_team_name(){ return team_name; }                             //get_team_name - returns team name
    inline std::string get_street_address(){ return street_address; }                   //get_street_address - returns street address
    inline std::string get_city_state_zip(){ return city_state_zip; }                   //get_city_state_zip - returns city state zip
    inline std::string get_box_office_number(){ return box_office_number; }             //get_box_office_number - returns box office number
    inline std::string get_date_opened(){ return date_opened; }                         //get_date_opened - returns date opened
    inline int get_seating_capacity(){ return seating_capacity; }                       //get_seating_capacity - returns seating capacity
    inline int get_size(){ return souvenirs.size(); }                                   //get_size - returns size
    inline bool if_american_league(){ return american_league;}                          //if_american_league - returns american league
    inline bool if_national_leauge(){ return !(american_league); }                      //if_national_leauge - returns national league
    inline bool get_american_league() { return american_league; }                       //get_american_league - returns american league
    inline bool get_grass(){ return grass; }                                            //get_grass - returns grass
    inline std::vector<Souvenir> get_souvenirs_list() {return this->souvenirs;}         //get_souvenirs_list - returns souvenirs vector

    //SOUVENIR SETTERS
    bool change_souvenir_name(std::string name, std::string new_name);                  //change_souvenir_name - changes souvenir name
    bool change_souvenir_price(std::string name, double price);                         //change_souvenir_price - changes souvenir price


private:
    //STADIUM PROPERTIES
    std::string stadium_name;               //stadium_name - stores stadium name
    std::string team_name;                  //team_name - stores team name
    std::string street_address;             //street_address - stores street address
    std::string city_state_zip;             //city_state_zip - stores city state zip
    std::string box_office_number;          //box_office_number - stores box office number
    std::string date_opened;                //date_opened - stores date opened

    int seating_capacity;                   //seating_capacity - stores seating capacity
    bool american_league;                   //american_league - stores american league
    bool grass;                             //grass - stores grass


    //SOUVENIR PROPERTIES
    std::vector<Souvenir> souvenirs;        //Souvenirs - vector of souvenir structs
};

}       //ILB namespace

#endif // STADIUM_H
