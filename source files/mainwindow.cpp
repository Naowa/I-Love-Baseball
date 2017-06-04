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

//    my_stadium.set_stadium_name("My stadium");
//    my_stadium.set_team_name("rangers");
//    my_stadium.set_street_address("123 seasame street");
//    my_stadium.set_city_state_zip("pasadena, ca, 123456");
//    my_stadium.set_box_office_number("(626)-111-1342");
////    my_stadium.set_date_opened(1996);
//    my_stadium.set_seating_capacity(34653);
//    graph = new Baseball_Graph(50);
//    graph->initialize_from_file("ILB Weights - Sheet1.csv");
    graph->initialize_from_file("ILB Weights - Sheet1.csv", 0);
//    graph-

//    std::cout << graph->get_stadium_admin("Dodger").display_stadium_info() << std::endl;
//    std::cout << std::endl;
//    std::cout << graph->get_stadium_admin("Angel").display_stadium_info() << std::endl;
//    std::cout << graph->get_stadium_admin("PNC").display_stadium_info() << std::endl;
//    std::cout << graph->get_stadium_admin("AT&T").display_stadium_info() << std::endl;
//    std::cout << graph->get_stadium_admin("Dodger").get << std::endl;
//    ILB::Stadium temp[50] = graph->get_vert_name();


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

    std::string stadium_name_str;
    std::string item_name_str;
    std::string item_price_input_str;
    double item_price;
    int decimal_count = 0;
    int numeral_count = 0;

//    //store item name, check a-z and A-Z
    while ( (input_str[i] != '/') && (input_str[i] != NULL) ){
            if ( ((input_str[i] > 64) && (input_str[i] < 91))
                 || ((input_str[i] > 96) && (input_str[i] < 123)) || (input_str[i] == 32)){
                stadium_name_str += input_str[i];
            }else{
                valid = false;
            }
        i++;
    }

//    valid = valid_string(stadium_name_str, input_str, i);

    i++;

//    store item name, check a-z and A-Z
    while ( (input_str[i] != '/') && (input_str[i] != NULL) ){
            if ( ((input_str[i] > 64) && (input_str[i] < 91))
                 || ((input_str[i] > 96) && (input_str[i] < 123)) || (input_str[i] == 32)){
                item_name_str += input_str[i];
            }else{
                valid = false;
            }
        i++;
    }
//    valid = valid_string(item_name_str, input_str, i);

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

    if ( stadium_name_str.empty() || item_name_str.empty() || item_price_input_str.empty() ){
        valid = false;
    }
    if (valid){
        if (decimal_count == 0){
            item_price = stoi(item_price_input_str);
        }else{
            item_price = stod(item_price_input_str);
        }
//        my_stadium.add_souvenir(item_name_str, item_price);

//        if (graph->find(stadium_name_str)){
//            graph->get_stadium_admin(stadium_name_str).add_souvenir(item_name_str, item_price);
//        }else{
//            valid = false;
//        }
    }
    return valid;
}

bool MainWindow::del_souvenir(std::string input_str)
{
    bool valid = true;
    int i = 0;

    std::string stadium_name_str;
    std::string item_name_str;

    //store item name, check a-z and A-Z
    while ( (input_str[i] != '/') && (input_str[i] != NULL) ){
            if ( ((input_str[i] > 64) && (input_str[i] < 91))
                 || ((input_str[i] > 96) && (input_str[i] < 123)) || (input_str[i] == 32)){
                stadium_name_str += input_str[i];
            }else{
                valid = false;
            }
        i++;
    }

    i++;

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

    if ( stadium_name_str.empty() || item_name_str.empty() ){
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

    std::string stadium_name_str;
    std::string item_name_str;
    std::string new_item_name_str;

    //store item name, check a-z and A-Z
    while ( (input_str[i] != '/') && (input_str[i] != NULL) ){
            if ( ((input_str[i] > 64) && (input_str[i] < 91))
                 || ((input_str[i] > 96) && (input_str[i] < 123)) || (input_str[i] == 32)){
                stadium_name_str += input_str[i];
            }else{
                valid = false;
            }
        i++;
    }

    i++;

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

    if (stadium_name_str.empty() || item_name_str.empty() || new_item_name_str.empty()){
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

    std::string stadium_name_str;
    std::string item_name_str;
    std::string item_price_input_str;
    double item_price;
    int decimal_count = 0;
    int numeral_count = 0;

    //store item name, check a-z and A-Z
    while ( (input_str[i] != '/') && (input_str[i] != NULL) ){
            if ( ((input_str[i] > 64) && (input_str[i] < 91))
                 || ((input_str[i] > 96) && (input_str[i] < 123)) || (input_str[i] == 32)){
                stadium_name_str += input_str[i];
            }else{
                valid = false;
            }
        i++;
    }

    i++;

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

    if ( stadium_name_str.empty() || item_name_str.empty() || item_price_input_str.empty() ){
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

    if (state == "BUY_SOUVENIR"){
        if (buy_souvenir(input_string)){
            ui->instructions->setText("Souvenir Bought!");
            state = "NO_STATE";
        }else{
            ui->instructions->setText("Failed to Buy! (stadium/name):");
        }
    }

    if (state == "DISPLAY_STADIUM"){
        if (display_stadium(input_string)){
            ui->instructions->setText("Displayed!");
            state = "NO_STATE";
        }else{
            ui->instructions->setText("Failed to Display! (stadium):");
        }
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
                ui->instructions_Admin->setText("Failed to Add! (stadium/name/price):");
            }
        }

        if (state == "DEL_SOUVENIR"){
            if (del_souvenir(input_string)){
                ui->instructions_Admin->setText("Removed Souvenir!");
                state = "NO_STATE";
            }else{
                ui->instructions_Admin->setText("Failed to Remove! (stadium/name):");
            }
        }

        if (state == "CHANGE_SOUVENIR_NAME"){
            if (change_souvenir_name(input_string)){
                ui->instructions_Admin->setText("Item Name Changed!");
                state = "NO_STATE";
            }else{
                ui->instructions_Admin->setText("Failed to Change! (stadium/name/newname):");
            }
        }

        if (state == "CHANGE_SOUVENIR_PRICE"){
            if (change_souvenir_price(input_string)){
                ui->instructions_Admin->setText("Item Price Changed!");
                state = "NO_STATE";
            }else{
                ui->instructions_Admin->setText("Failed to Change! (stadium/name/newprice):");
            }
        }

    }
}

bool MainWindow::display_stadium(std::string input_str)
{
    bool valid = true;
//    int i = 0;

    std::string stadium_name_str = input_str;
    std::string output_Str;

    //store item name, check a-z and A-Z
//    while ( (input_str[i] != '/') && (input_str[i] != NULL) ){
//            if ( ((input_str[i] > 64) && (input_str[i] < 91))
//                 || ((input_str[i] > 96) && (input_str[i] < 123)) || (input_str[i] == 32)){
//                stadium_name += input_str[i];
//            }else{
//                valid = false;
//            }
//        i++;
//    }

    if (stadium_name_str.empty()){
        valid = false;
    }
    if (valid){
        std::cout << "also, just feed in the exact string, dont check invalid input "
                     << "check if stadium exists before doing any operations with getstadium admin" << std::endl;

//        if (graph->find(stadium_name_str)){
//            output_Str += graph->get_stadium_admin(stadium_name_str).display_stadium_info();
            output_Str += "\n";
//            output_Str += graph->get_stadium_admin(stadium_name_str).display_souvenirs();
            ui->displayBox->setText(QString::fromStdString(output_Str));
//        }else{
//            valid = false;
//        }
    }
    return valid;
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
        ui->instructions_Admin->setText("Add (stadium/name/price):");
    }
}

void MainWindow::btn_Del_Souvenir_Handler()
{
    if (isAdmin){
        state = "DEL_SOUVENIR";
        ui->instructions_Admin->setText("Remove (stadium/name):");
    }
}

void MainWindow::btn_Change_Souvenir_Name_Handler()
{
    if (isAdmin){
        state = "CHANGE_SOUVENIR_NAME";
        ui->instructions_Admin->setText("Change Name (stadium/name/newname):");
    }
}

void MainWindow::btn_Change_Souvenir_Price_Handler()
{
    if (isAdmin){
        state = "CHANGE_SOUVENIR_PRICE";
        ui->instructions_Admin->setText("Change Price (stadium/name/newprice):");
    }
}

void MainWindow::btn_Display_Stadium_Handler()
{
    state = "DISPLAY_STADIUM";
    ui->instructions->setText("Display (stadium):");
}

void MainWindow::btn_Buy_Souvenir_Handler()
{
    state = "BUY_SOUVENIR";
    ui->instructions->setText("Buy (stadium/name):");
}

bool MainWindow::buy_souvenir(std::string input_str)
{
    bool valid = true;
    int i = 0;

    std::string stadium_name_str;
    std::string item_name_str;

    //store item name, check a-z and A-Z
    while ( (input_str[i] != '/') && (input_str[i] != NULL) ){
            if ( ((input_str[i] > 64) && (input_str[i] < 91))
                 || ((input_str[i] > 96) && (input_str[i] < 123)) || (input_str[i] == 32)){
                stadium_name_str += input_str[i];
            }else{
                valid = false;
            }
        i++;
    }

    i++;

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

    if (stadium_name_str.empty() || item_name_str.empty()){
        valid = false;
    }
    if (valid){
//        if (graph->find(stadium_name_str)){
//        if (graph->get_stadium_admin(stadium_name_str).find_souvenir(item_name_str)){
//            ILB::Souvenir temp = graph->get_stadium_admin(stadium_name_str).get_souvenir(item_name_str);
//            string item_name = temp.item_name;
//            string stadium_name = temp.origin_stadium_name;
//            double price = temp.item_price;
//            customer.buy(item_name, stadium_name, price);
//        }else{
//            valid = false;          //item not found
//        }
//        }else{
//            valid = false;    //stadium not found
//        }
    }
    return valid;
}

void MainWindow::btn_Display_Purchases_Handler()
{
    std::string output_Str;
    output_Str += customer.display_purchases();
    ui->displayBox->setText(QString::fromStdString(output_Str));
    ui->instructions->setText("Displayed!");
}

bool MainWindow::valid_string(std::string &val, std::string input_str, int &i)
{
    bool valid = true;
    //store item name, check a-z and A-Z
    while ( (input_str[i] != '/') && (input_str[i] != NULL) ){
            if ( ((input_str[i] > 64) && (input_str[i] < 91))
                 || ((input_str[i] > 96) && (input_str[i] < 123)) || (input_str[i] == 32)){
                val += input_str[i];
            }else{
                valid = false;
            }
        i++;
    }
}

