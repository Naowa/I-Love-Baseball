//VERSION 0.2.0

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <fstream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    state = "NO_STATE";

    my_stadium.set_stadium_name("My stadium");
    my_stadium.set_team_name("rangers");
    my_stadium.set_street_address("123 seasame street");
    my_stadium.set_city_state_zip("pasadena, ca, 123456");
    my_stadium.set_box_office_number("(626)-111-1342");
    my_stadium.set_date_opened(1996);
    my_stadium.set_seating_capacity(34653);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::add_souvenir(std::string input_str)
{
    bool valid = true;
    int i = 0;

    std::string item_name_str;
    std::string item_price_input_str;
    double item_price;

    ////(************************************************check for souvenirs with spaces in name
    //store item name, check a-z and A-Z
    while ( (input_str[i] != '/') && (input_str[i] != NULL) ){
            if ( ((input_str[i] > 64) && (input_str[i] < 91))
                 || ((input_str[i] > 96) && (input_str[i] < 123)) || (input_str[i] == 32)){
                item_name_str += input_str[i];
            }else{
                valid = false;
            }
        i++;
    }

    i++;

    //store item price, check 0-9
    while ( (input_str[i] != '/') && (input_str[i] != NULL) ){
            if ( (input_str[i] > 47) && (input_str[i] < 58) ){
                item_price_input_str += input_str[i];
            }else{
                valid = false;
            }
        i++;
    }

    if ( (item_name_str.empty()) || (item_price_input_str.empty()) ){
        valid = false;
    }
    if (valid){
        item_price = stoi(item_price_input_str);

        std::cout << item_name_str << std::endl;
        std::cout << item_price << std::endl;
        my_stadium.add_souvenir(item_name_str, item_price);
    }
    return valid;
}

bool MainWindow::del_souvenir(std::string input_str)
{
    bool valid = true;
    int i = 0;

    std::string item_name_str;

    //store item name, check a-z and A-Z
    while ( (input_str[i] != '/') && (input_str[i] != NULL) ){
            if ( ((input_str[i] > 64) && (input_str[i] < 91))
                 || ((input_str[i] > 96) && (input_str[i] < 123)) || (input_str[i] == 32)){
                item_name_str += input_str[i];
            }else{
                valid = false;
            }
        i++;
    }

    if (item_name_str.empty()){
        valid = false;
    }
    if (valid){
        if (!my_stadium.remove_souvenir(item_name_str)){
            valid = false;
        }
    }
    return valid;
}

//universal function for confirmation
//call all input related functions in this one function
//state will change to whatever mode the user is in
//ui->instructions - you use this to guide the user in what to do (what you want them to input into the input box)
//Example: user clicks add souvenir button, state is set to ADD_SOUVENIR and btn_confirm will confirm what the user inputted
///***After the user confirms input and it was successful, reset the state to NO_STATE
///*** functions should be boolean for contingency handling
void MainWindow::btn_confirm_handler()
{
    std::string input_string = get_Str_Input();

    if (state == "ADD_SOUVENIR"){
        if (add_souvenir(input_string)){
            ui->instructions->setText("Added Souvenir!");
            state = "NO_STATE";
        }else{
            ui->instructions->setText("Failed to Add! (name/price):");
        }
    }
    if (state == "DEL_SOUVENIR"){
        if (del_souvenir(input_string)){
            ui->instructions->setText("Removed Souvenir!");
            state = "NO_STATE";
        }else{
            ui->instructions->setText("Failed to Remove! (name):");
        }
    }
}

void MainWindow::display(std::string input_str)
{
    ui->displayBox->setText(QString::fromStdString(input_str));
}

void MainWindow::read_file()
{
//    string inFileName = "american league teams.txt";
//    ifstream dataIn;

//    string line;

//    //stadium reading properties
//    string input_stadium_name;
//    string input_team_name;
//    string input_street_address;
//    string input_city_state_zip;
//    string input_box_office_number;
//    string string_input_date_opened;               //convert to int
//    string string_input_seating_capacity;          //convert to int

//    //START OF FILE READING
//    dataIn.open(inFileName);

//    //skip three lines
//    getline(dataIn, line);
//    getline(dataIn, line);
//    getline(dataIn, line);

//    string output_str;

////        while (getline(dataIn, line)){
//            input_stadium_name = line; getline(dataIn, line);
//            input_team_name = line; getline(dataIn, line);
//            input_street_address = line; getline(dataIn, line);
//            input_city_state_zip = line; getline(dataIn, line);
//            input_box_office_number = line; getline(dataIn, line);
//            string_input_date_opened = line; getline(dataIn, line);
//            string_input_seating_capacity = line; getline(dataIn, line);

//            output_str += input_stadium_name; output_str += "\n";
//            output_str += input_team_name; output_str += "\n";
//            output_str += input_street_address; output_str += "\n";
//            output_str += input_city_state_zip; output_str += "\n";
//            output_str += input_box_office_number; output_str += "\n";
//            output_str += string_input_date_opened; output_str += "\n";
//            output_str += string_input_seating_capacity; output_str += "\n";

//            //skip two lines
//            getline(dataIn, line);
//            getline(dataIn, line);

//            output_str += "\n";
////        }

//    display(output_str);

//    dataIn.close();
}

std::string MainWindow::get_Str_Input()
{
    return ui->inputBox->text().toStdString();
}

void MainWindow::btn_Add_Souvenir_Handler()
{
    state = "ADD_SOUVENIR";
    ui->instructions->setText("Add (name/price):");
}

void MainWindow::btn_Del_Souvenir_Handler()
{
    state = "DEL_SOUVENIR";
    ui->instructions->setText("Remove (name):");
}

void MainWindow::btn_Display_Handler()
{
    std::string output_Str;
    output_Str += my_stadium.display_stadium_info();
    output_Str += "\n\n";
    output_Str += my_stadium.display_souvenirs();
    ui->displayBox->setText(QString::fromStdString(output_Str));
}

