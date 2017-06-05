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
    state_admin = "NO_STATE";
    isAdmin = false;
    adminPass = "password";

    graph = new Baseball_Graph(50);
    graph->initialize_from_file("ILB Weights - Sheet1.csv", 0);
    graph->initialize_from_file("StadiumInfo.txt", 1);


//    ILB::Stadium* temp = graph->get_vert();

//    for (int i = 0; i < graph->get_vcount(); i++){
//        std::cout << temp[i].get_stadium_name() << std::endl;
//    }
//    std::swap(temp[0], temp[1]);
//    std::swap(temp[0], temp[graph->get_vcount() - 1]);
//    std::cout << std::endl;
//    for (int i = 0; i < graph->get_vcount(); i++){
//        std::cout << temp[i].get_stadium_name() << std::endl;
//    }

}

void MainWindow::btn_confirm_handler()
{
    std::string input_string = get_Str_Input();

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

        if (state_admin == "NO_STATE"){
            ui->instructions_Admin->setText("No Command!");
        }

        if (state_admin == "ADD_SOUVENIR"){
            if (add_souvenir(input_string)){
                ui->instructions_Admin->setText("Added Souvenir!");
                state_admin = "NO_STATE";
            }else{
                ui->instructions_Admin->setText("Failed to Add! (stadium/name/price):");
            }
        }

        if (state_admin == "DEL_SOUVENIR"){
            if (del_souvenir(input_string)){
                ui->instructions_Admin->setText("Removed Souvenir!");
                state_admin = "NO_STATE";
            }else{
                ui->instructions_Admin->setText("Failed to Remove! (stadium/name):");
            }
        }

        if (state_admin == "CHANGE_SOUVENIR_NAME"){
            if (change_souvenir_name(input_string)){
                ui->instructions_Admin->setText("Item Name Changed!");
                state_admin = "NO_STATE";
            }else{
                ui->instructions_Admin->setText("Failed to Change! (stadium/name/newname):");
            }
        }

        if (state_admin == "CHANGE_SOUVENIR_PRICE"){
            if (change_souvenir_price(input_string)){
                ui->instructions_Admin->setText("Item Price Changed!");
                state_admin = "NO_STATE";
            }else{
                ui->instructions_Admin->setText("Failed to Change! (stadium/name/newprice):");
            }
        }

    }
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

    while ( (input_str[i] != '/') && (input_str[i] != NULL) ){
        stadium_name_str += input_str[i];
        i++;
    }
    i++;
    valid = valid_string(item_name_str, input_str, i);
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

    if (stadium_name_str.empty() || item_name_str.empty() || item_price_input_str.empty()){
        valid = false;
    }
    if (valid){
        if (decimal_count == 0){
            item_price = stoi(item_price_input_str);
        }else{
            item_price = stod(item_price_input_str);
        }

        if (graph->vertice_exists(stadium_name_str)){
            graph->get_stadium_admin(stadium_name_str).add_souvenir(item_name_str, item_price);
        }else{
            valid = false;
        }
    }
    return valid;
}

bool MainWindow::del_souvenir(std::string input_str)
{
    bool valid = true;
    int i = 0;

    std::string stadium_name_str;
    std::string item_name_str;

    while ( (input_str[i] != '/') && (input_str[i] != NULL) ){
        stadium_name_str += input_str[i];
        i++;
    }
    i++;
    valid = valid_string(item_name_str, input_str, i);

    if (stadium_name_str.empty() || item_name_str.empty()){
        valid = false;
    }
    if (valid){
        if (graph->vertice_exists(stadium_name_str)){
             if (!graph->get_stadium_admin(stadium_name_str).remove_souvenir(item_name_str)){
                 valid = false;
             }
        }else{
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

    while ( (input_str[i] != '/') && (input_str[i] != NULL) ){
        stadium_name_str += input_str[i];
        i++;
    }
    i++;
    valid = valid_string(item_name_str, input_str, i);
    i++;
    valid = valid_string(new_item_name_str, input_str, i);

    if (stadium_name_str.empty() || item_name_str.empty() || new_item_name_str.empty()){
        valid = false;
    }
    if (valid){
        if (graph->vertice_exists(stadium_name_str)){
            if (!graph->get_stadium_admin(stadium_name_str).change_souvenir_name(item_name_str, new_item_name_str)){
                valid = false;
            }
        }else{
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

    while ( (input_str[i] != '/') && (input_str[i] != NULL) ){
        stadium_name_str += input_str[i];
        i++;
    }
    i++;
    valid = valid_string(item_name_str, input_str, i);

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

        if (graph->vertice_exists(stadium_name_str)){
            if (!graph->get_stadium_admin(stadium_name_str).change_souvenir_price(item_name_str, item_price)){
                valid = false;
            }
        }else{
            valid = false;
        }
    }
    return valid;
}

bool MainWindow::display_stadium(std::string input_str)
{
    bool valid = true;

    std::string stadium_name_str = input_str;
    std::string output_Str;

    if (stadium_name_str.empty()){
        valid = false;
    }
    if (valid){
        if (graph->vertice_exists(stadium_name_str)){
            output_Str += graph->get_stadium_admin(stadium_name_str).display_stadium_info();
            output_Str += "\n";
            output_Str += graph->get_stadium_admin(stadium_name_str).display_souvenirs();
            ui->displayBox->setText(QString::fromStdString(output_Str));
        }else{
            valid = false;
        }
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
        state_admin = "ADD_SOUVENIR";
        ui->instructions_Admin->setText("Add (stadium/name/price):");
    }
}

void MainWindow::btn_Del_Souvenir_Handler()
{
    if (isAdmin){
        state_admin = "DEL_SOUVENIR";
        ui->instructions_Admin->setText("Remove (stadium/name):");
    }
}

void MainWindow::btn_Change_Souvenir_Name_Handler()
{
    if (isAdmin){
        state_admin = "CHANGE_SOUVENIR_NAME";
        ui->instructions_Admin->setText("Change Name (stadium/name/newname):");
    }
}

void MainWindow::btn_Change_Souvenir_Price_Handler()
{
    if (isAdmin){
        state_admin = "CHANGE_SOUVENIR_PRICE";
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

    while ( (input_str[i] != '/') && (input_str[i] != NULL) ){
        stadium_name_str += input_str[i];
        i++;
    }
    i++;
    valid = valid_string(item_name_str, input_str, i);

    if (stadium_name_str.empty() || item_name_str.empty()){
        valid = false;
    }
    if (valid){
        if (graph->vertice_exists(stadium_name_str)){
            if (graph->get_stadium_admin(stadium_name_str).find_souvenir(item_name_str)){
                ILB::Souvenir temp = graph->get_stadium_admin(stadium_name_str).get_souvenir(item_name_str);
                string item_name = temp.item_name;
                string stadium_name = temp.origin_stadium_name;
                double price = temp.item_price;
                customer.buy(item_name, stadium_name, price);
            }else{
                valid = false;          //item not found
            }
        }else{
            valid = false;    //stadium not found
        }
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
    return valid;
}

void MainWindow::btn_Display_All_Stadiums_Handler()
{
    std::string output_Str;
    ILB::Stadium *temp = graph->get_vert();
    for (int i = 0; i < graph->get_vcount(); i++){
        output_Str += temp[i].display_stadium_info();
        output_Str += "\n";
    }
    ui->displayBox->setText(QString::fromStdString(output_Str));
    ui->instructions->setText("Displayed!");
}

