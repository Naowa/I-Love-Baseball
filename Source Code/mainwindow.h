//VERSION 0.2.0

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

private:
    Ui::MainWindow *ui;

    std::string state;                              //state - determines the state for btn_confirm_handler()

    void display(std::string input_str);            //display - takes in a string parameter and displays it to the GUI

    ILB::Stadium my_stadium;                        //my_stadium - temporarily initialized a stingle stadium for testing purposes/presenting to professor
                                                    ///***later on, we should be able to set a stadium as "selected,"
                                                    ///***and use the GUI functions to manipulate that "selected" stadium

    //private helper functions for btn_confirm_handler()
    //All input functions should utilize btn_confirm_handler()
    bool add_souvenir(std::string input_str);
    bool del_souvenir(std::string input_str);

private slots:
    //Button Slot Functions
    void btn_confirm_handler();                     //confirms ALL user input
    void btn_Add_Souvenir_Handler();
    void btn_Del_Souvenir_Handler();
    void btn_Display_Handler();
};

#endif // MAINWINDOW_H
