//VERSION 0.3.0

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "stadium.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void read_file();                               ///***read_file - redacted function, delete if not needed, was partially implemented

    std::string get_Str_Input();                    //get_Str_Input - returns user input on the GUI as a string
    std::string get_Str_Input_Admin();              //same as above, but for admin input

private:
    Ui::MainWindow *ui;

    std::string state;                              //state - determines the state for btn_confirm_handler()
    bool isAdmin;
    std::string adminPass;

    void display(std::string input_str);            //display - takes in a string parameter and displays it to the GUI

    ILB::Stadium my_stadium;                        //my_stadium - temporarily initialized a stingle stadium for testing purposes/presenting to professor
                                                    ///***later on, we should be able to set a stadium as "selected,"
                                                    ///***and use the GUI functions to manipulate that "selected" stadium

    //private helper functions for btn_confirm_handler()
    //All input functions should utilize btn_confirm_handler()


    ///**ADMINISTRATOR FUNCTIONS
    bool add_souvenir(std::string input_str);
    bool del_souvenir(std::string input_str);
    bool change_souvenir_name(std::string input_str);
    bool change_souvenir_price(std::string input_str);
    bool compare_dates(std::string lhs_date, std::string rhs_date);     ///     mm/dd/yyyy
                                                                        ///     return true if lhs_date is before rhs_date
                                                                        ///     ex: lhs is 2000; rhs is 2003 - return true since lhs is before rhs


private slots:
    //Button Slot Functions
    void btn_confirm_handler();                     //confirms ALL user input
    void btn_confirm_admin_handler();
    void btn_Add_Souvenir_Handler();
    void btn_Del_Souvenir_Handler();
    void btn_Change_Souvenir_Name_Handler();
    void btn_Change_Souvenir_Price_Handler();
    void btn_Display_Handler();
};

#endif // MAINWINDOW_H
