//VERSION 0.3.0

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "stadium.h"
#include "baseball_graph.h"
//#include "Graph.h"
#include "user.h"

namespace Ui {

//Baseball_Graph agt();
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    std::string get_Str_Input();                    //get_Str_Input - returns user input on the GUI as a string
    std::string get_Str_Input_Admin();              //same as above, but for admin input

private:
    Ui::MainWindow *ui;                             //ui - ui for the gui interface

    std::string state;                              //state - determines the state for btn_confirm_handler()
    std::string state_admin;                        //state_admin - determines the state for btn_confirm_admin_handler()
    bool isAdmin;                                   //isAdmin - determines if user is admin
    std::string adminPass;                          //adminPass - stores password for admin

    User customer;                                  //customer - stores customer class (user), keeps track of purchases
    Baseball_Graph *graph;                          //graph - stores the graph with stadiums

    ///**PRIVATE FUNCTIONS
    bool valid_string(std::string &val, std::string input_str, int &i);     //valid_string - determines if a string is valid and updates its contents
    std::string to_lexicographical_order(std::string date);                 //to_lexicographical_order - converts a string date to lexicographical

    ///**ADMINISTRATOR FUNCTIONS
    bool add_souvenir(std::string input_str);                               //add_souvenir - adds a souvenir to a stadium
    bool del_souvenir(std::string input_str);                               //del_souvenir - deletes a souvenir
    bool change_souvenir_name(std::string input_str);                       //change_souvenir_name - changes a souvenir's name
    bool change_souvenir_price(std::string input_str);                      //change_souvenir_price - changes a souvenir's price

    ///***USER FUNCTIONS
    bool display_stadium(std::string input_str);                            //display_stadium - displays a stadium to the gui
    bool buy_souvenir(std::string input_str);                               //buy_souvenir - allows purchase of souvenir
    bool display_distance_between(std::string input_str);                   //display_distance_between - displays distance between stadiums
    bool display_distance_between_custom_trip(std::string input_str);       //display_distance_between_custom_trip - displays distance between custom trips generated

    ///***Initialize Stadium Count

private slots:
    //Button Slot Functions
    void btn_confirm_handler();                     //btn_confirm_handler - confirms user input
    void btn_confirm_admin_handler();               //btn_confirm_admin_handler - confirms admin input
    void btn_Add_Souvenir_Handler();                //btn_Add_Souvenir_Handler - handles button for adding souvenirs
    void btn_Del_Souvenir_Handler();                //btn_Del_Souvenir_Handler - handles deletion of souvenirs
    void btn_Change_Souvenir_Name_Handler();        //btn_Change_Souvenir_Name_Handler - handles button to change a souvenir's name
    void btn_Change_Souvenir_Price_Handler();       //btn_Change_Souvenir_Price_Handler - handles button to change a souvenir's price
    void btn_Display_Stadium_Handler();             //btn_Display_Stadium_Handler - handles displaying a stadium
    void btn_Buy_Souvenir_Handler();                //btn_Buy_Souvenir_Handler - handles buying souvenirs
    void btn_Display_Purchases_Handler();           //btn_Display_Purchases_Handler - handles displaying purchases
    void btn_Display_All_Stadiums_Handler();        //btn_Display_All_Stadiums_Handler - handles displaying all stadiums
    void display_sorted_by_date();                  //display_sorted_by_date - handles displaying stadiums by sorted date
    void display_sorted_by_stadium_names();         //display_sorted_by_stadium_names - handles displaying sorted by stadium names
    void display_sorted_by_team_names();            //display_sorted_by_team_names - handles displaying sorted by team names
    void display_sorted_by_team_names_american();   //display_sorted_by_team_names_american - handles displaying sorted by american team names
    void display_sorted_by_team_names_national();   //display_sorted_by_team_names_national - handles displaying sorted by national team names
    void display_sorted_by_grass_surface_and_team_names();      //display_sorted_by_grass_surface_and_team_names - handles displaying sorted by grass surface and team names
    void btn_display_distance_between_handler();    //btn_display_distance_between_handler - handles displaying distance between stadiums
    void btn_display_custom_trip_handler();         //btn_display_custom_trip_handler - handles custom trip displaying
    void change_stadium_property();                 //change_stadium_property - handles changing stadium properties
void add_stadium();                                 //add_stadium - adds stadium to graph
void btn_TRIP_major_league_shortest();              //btn_TRIP_major_league_shortest - displays shortest pathing for mlb stadiums
void btn_TRIP_american_league_shortest();           //btn_TRIP_american_league_shortest - displays shortest pathing for american league stadiums
void btn_TRIP_national_league_shortest();           //btn_TRIP_national_league_shortest - displays shortest pathing for nationa league stadiums
};

//Baseball_Graph gw(50);

#endif // MAINWINDOW_H
