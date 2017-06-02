//VERSION 0.3.0

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <fstream>

using std::string;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    state = "NO_STATE";
    isAdmin = false;
    adminPass = "password";

    my_stadium.set_stadium_name("My stadium");
    my_stadium.set_team_name("rangers");
    my_stadium.set_street_address("123 seasame street");
    my_stadium.set_city_state_zip("pasadena, ca, 123456");
    my_stadium.set_box_office_number("(626)-111-1342");
//    my_stadium.set_date_opened(1996);
    my_stadium.set_seating_capacity(34653);
    graph = new Baseball_Graph(50);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::compare_dates(string lhs_date, string rhs_date)
{
    int lhs_mm = stoi(lhs_date.substr(0, 2));
    int lhs_dd = stoi(lhs_date.substr(3, 2));
    int lhs_yyyy = stoi(lhs_date.substr(6, 4));

    int rhs_mm = stoi(rhs_date.substr(0, 2));
    int rhs_dd = stoi(rhs_date.substr(3, 2));
    int rhs_yyyy = stoi(rhs_date.substr(6, 4));

    if (lhs_yyyy < rhs_yyyy){
        return true;
    }
    if (lhs_yyyy == rhs_yyyy){
        if (lhs_mm < rhs_mm){
            return true;
        }
    }
    if (lhs_mm == rhs_mm){
        if (lhs_dd < rhs_dd){
            return true;
        }
    }

    return false;
}

bool MainWindow::add_souvenir(std::string input_str)
{
    bool valid = true;
    int i = 0;

    std::string item_name_str;
    std::string item_price_input_str;
    double item_price;
    int decimal_count = 0;
    int numeral_count = 0;

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
                numeral_count++;
                item_price_input_str += input_str[i];
            }else{
                if (input_str[i] == 46){        //check decimal, add to string
                    if (decimal_count == 0){
                        decimal_count++;
                        item_price_input_str += input_str[i];
                    }else{
                        valid = false;
                    }
                }else{
                    valid = false;
                }
            }
        i++;
    }

    if (numeral_count == 0){
        valid = false;
    }

    if ( (item_name_str.empty()) || (item_price_input_str.empty()) ){
        valid = false;
    }
    if (valid){
        if (decimal_count == 0){
            item_price = stoi(item_price_input_str);
        }else{
            item_price = stod(item_price_input_str);
        }

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

bool MainWindow::change_souvenir_name(std::string input_str)
{
    bool valid = true;
    int i = 0;

    std::string item_name_str;
    std::string new_item_name_str;

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

    while ( (input_str[i] != '/') && (input_str[i] != NULL) ){
            if ( ((input_str[i] > 64) && (input_str[i] < 91))
                 || ((input_str[i] > 96) && (input_str[i] < 123)) || (input_str[i] == 32)){
                new_item_name_str += input_str[i];
            }else{
                valid = false;
            }
        i++;
    }

    if (item_name_str.empty() || new_item_name_str.empty()){
        valid = false;
    }
    if (valid){
        if (!my_stadium.change_souvenir_name(item_name_str, new_item_name_str)){
            valid = false;
        }
    }
    return valid;
}

bool MainWindow::change_souvenir_price(std::string input_str)
{
    bool valid = true;
    int i = 0;

    std::string item_name_str;
    std::string item_price_input_str;
    double item_price;
    int decimal_count = 0;
    int numeral_count = 0;

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
                numeral_count++;
                item_price_input_str += input_str[i];
            }else{
                if (input_str[i] == 46){        //check decimal, add to string
                    if (decimal_count == 0){
                        decimal_count++;
                        item_price_input_str += input_str[i];
                    }else{
                        valid = false;
                    }
                }else{
                    valid = false;
                }
            }
        i++;
    }

    if (numeral_count == 0){
        valid = false;
    }

    if ( (item_name_str.empty()) || (item_price_input_str.empty()) ){
        valid = false;
    }
    if (valid){
        if (decimal_count == 0){
            item_price = stoi(item_price_input_str);
        }else{
            item_price = stod(item_price_input_str);
        }

        if (!my_stadium.change_souvenir_price(item_name_str, item_price)){
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

//    if (state == "ADD_SOUVENIR"){
//        if (add_souvenir(input_string)){
//            ui->instructions->setText("Added Souvenir!");
//            state = "NO_STATE";
//        }else{
//            ui->instructions->setText("Failed to Add! (name/price):");
//        }
//    }
//    if (state == "DEL_SOUVENIR"){
//        if (del_souvenir(input_string)){
//            ui->instructions->setText("Removed Souvenir!");
//            state = "NO_STATE";
//        }else{
//            ui->instructions->setText("Failed to Remove! (name):");
//        }
//    }

    if (state == "NO_STATE"){
        ui->instructions->setText("No Command!");
    }
}

void MainWindow::btn_confirm_admin_handler()
{
    std::string input_string = get_Str_Input_Admin();

    if (!isAdmin){
        if (input_string == adminPass){
            ui->instructions_Admin->setText("Sign in Successful!");
            isAdmin = true;
        }else{
            ui->instructions_Admin->setText("Error, Sign in Required!");
        }
    }else{

        if (state == "NO_STATE"){
            ui->instructions_Admin->setText("No Command!");
        }

        if (state == "ADD_SOUVENIR"){
            if (add_souvenir(input_string)){
                ui->instructions_Admin->setText("Added Souvenir!");
                state = "NO_STATE";
            }else{
                ui->instructions_Admin->setText("Failed to Add! (name/price):");
            }
        }

        if (state == "DEL_SOUVENIR"){
            if (del_souvenir(input_string)){
                ui->instructions_Admin->setText("Removed Souvenir!");
                state = "NO_STATE";
            }else{
                ui->instructions_Admin->setText("Failed to Remove! (name):");
            }
        }

        if (state == "CHANGE_SOUVENIR_NAME"){
            if (change_souvenir_name(input_string)){
                ui->instructions_Admin->setText("Item Name Changed!");
                state = "NO_STATE";
            }else{
                ui->instructions_Admin->setText("Failed to Change! (name/newname):");
            }
        }

        if (state == "CHANGE_SOUVENIR_PRICE"){
            if (change_souvenir_price(input_string)){
                ui->instructions_Admin->setText("Item Price Changed!");
                state = "NO_STATE";
            }else{
                ui->instructions_Admin->setText("Failed to Change! (name/newprice):");
            }
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

std::string MainWindow::get_Str_Input_Admin()
{
    return ui->inputBox_Admin->text().toStdString();
}

void MainWindow::btn_Add_Souvenir_Handler()
{
    if (isAdmin){
        state = "ADD_SOUVENIR";
        ui->instructions_Admin->setText("Add (name/price):");
    }
}

void MainWindow::btn_Del_Souvenir_Handler()
{
    if (isAdmin){
        state = "DEL_SOUVENIR";
        ui->instructions_Admin->setText("Remove (name):");
    }
}

void MainWindow::btn_Change_Souvenir_Name_Handler()
{
    if (isAdmin){
        state = "CHANGE_SOUVENIR_NAME";
        ui->instructions_Admin->setText("Change Name (name/newname):");
    }
}

void MainWindow::btn_Change_Souvenir_Price_Handler()
{
    if (isAdmin){
        state = "CHANGE_SOUVENIR_PRICE";
        ui->instructions_Admin->setText("Change Price (name/newprice):");
    }
}

void MainWindow::btn_Display_Handler()
{
    std::string output_Str;
    output_Str += my_stadium.display_stadium_info();
    output_Str += "\n\n";
    output_Str += my_stadium.display_souvenirs();
    ui->displayBox->setText(QString::fromStdString(output_Str));
}

