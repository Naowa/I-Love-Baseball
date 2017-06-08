//VERSION 0.3.0

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <fstream>

using std::string;

//O(n^4)
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
    graph->initialize_from_file("NationalStadiums.txt", 2);
//    std::cout << graph->get_vcount() << std::endl;
}

//O(n)
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

    if (state == "DISTANCE"){
        if (display_distance_between(input_string)){
            ui->instructions->setText("Displayed!");
            state = "NO_STATE";
        }else{
            ui->instructions->setText("Failed to Find Distance! (stadium1/stadium2):");
        }
    }

    if (state == "CUSTOM_TRIP"){
        if (display_distance_between_custom_trip(input_string)){
            ui->instructions->setText("Displayed!");
            state = "NO_STATE";
        }else{
            ui->instructions->setText("Failed to Find Distance For Custom Trip! (stadium1/stadium2/stadium3/...):");
        }
    }
}

//O(n)
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

//O(1)
MainWindow::~MainWindow()
{
    delete ui;
}

//O(n^2)
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

//O(n^3)
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

//O(n^2)
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

//O(n^4)
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

//O(n^2)
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

//O(1)
std::string MainWindow::get_Str_Input()
{
    return ui->inputBox->text().toStdString();
}

//O(1)
std::string MainWindow::get_Str_Input_Admin()
{
    return ui->inputBox_Admin->text().toStdString();
}

//O(1)
void MainWindow::btn_Add_Souvenir_Handler()
{
    if (isAdmin){
        state_admin = "ADD_SOUVENIR";
        ui->instructions_Admin->setText("Add (stadium/name/price):");
    }
}

//O(n)
void MainWindow::btn_Del_Souvenir_Handler()
{
    if (isAdmin){
        state_admin = "DEL_SOUVENIR";
        ui->instructions_Admin->setText("Remove (stadium/name):");
    }
}

//O(n)
void MainWindow::btn_Change_Souvenir_Name_Handler()
{
    if (isAdmin){
        state_admin = "CHANGE_SOUVENIR_NAME";
        ui->instructions_Admin->setText("Change Name (stadium/name/newname):");
    }
}

//O(n)
void MainWindow::btn_Change_Souvenir_Price_Handler()
{
    if (isAdmin){
        state_admin = "CHANGE_SOUVENIR_PRICE";
        ui->instructions_Admin->setText("Change Price (stadium/name/newprice):");
    }
}

//O(n)
void MainWindow::btn_Display_Stadium_Handler()
{
    state = "DISPLAY_STADIUM";
    ui->instructions->setText("Display (stadium):");
}

//O(1)
void MainWindow::btn_Buy_Souvenir_Handler()
{
    state = "BUY_SOUVENIR";
    ui->instructions->setText("Buy (stadium/name):");
}

//O(n^2)
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

//O(n)
void MainWindow::btn_Display_Purchases_Handler()
{
    std::string output_Str;
    output_Str += customer.display_purchases();
    ui->displayBox->setText(QString::fromStdString(output_Str));
    ui->instructions->setText("Displayed!");
}

//O(n)
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

//O(n)
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

//O(1)
string MainWindow::to_lexicographical_order(string date)
{
    string answer;

    string y = date.substr(6, 4);
    string m = date.substr(0, 2);
    string d = date.substr(3, 2);

    answer += y;
    answer += m;
    answer += d;

    return answer;
}

//O(n^2)
void MainWindow::display_sorted_by_date()
{
    std::string output_Str;

    int i_min;
    ILB::Stadium *temp = graph->get_vert();
    int sz = graph->get_vcount();

    string date1, date2;

    for (int i = 0; i < sz; i++){
        i_min = i;
        date1 = to_lexicographical_order(temp[i_min].get_date_opened());
        for (int j = (i + 1); j < sz; j++){
            date2 = to_lexicographical_order(temp[j].get_date_opened());
            if (date2 < date1){
                i_min = j;
                date1 = to_lexicographical_order(temp[i_min].get_date_opened());
            }
        }
        if (i_min != i){
            std::swap(temp[i], temp[i_min]);
        }
    }

    for (int k = 0; k < sz; k++){
        output_Str += temp[k].display_stadium_info();
        output_Str += "\n";
    }
    ui->displayBox->setText(QString::fromStdString(output_Str));
    ui->instructions->setText("Displayed Sorted By Date Opened!");
}

//O(n^2)
void MainWindow::display_sorted_by_stadium_names()
{
    std::string output_Str;

    int i_min;
    ILB::Stadium *temp = graph->get_vert();
    int sz = graph->get_vcount();

    string stadium1, stadium2;

    for (int i = 0; i < sz; i++){
        i_min = i;
        stadium1 = temp[i_min].get_stadium_name();
        for (int j = (i + 1); j < sz; j++){
            stadium2 = temp[j].get_stadium_name();
            if (stadium2 < stadium1){
                i_min = j;
                stadium1 = temp[i_min].get_stadium_name();
            }
        }
        if (i_min != i){
            std::swap(temp[i], temp[i_min]);
        }
    }

    for (int k = 0; k < sz; k++){
        output_Str += temp[k].display_stadium_info();
        output_Str += "\n";
    }
    ui->displayBox->setText(QString::fromStdString(output_Str));
    ui->instructions->setText("Displayed Sorted By Stadium Names!");
}

//O(n^2)
void MainWindow::display_sorted_by_team_names()
{
    std::string output_Str;

    int i_min;
    ILB::Stadium *temp = graph->get_vert();
    int sz = graph->get_vcount();

    string team1, team2;

    for (int i = 0; i < sz; i++){
        i_min = i;
        team1 = temp[i_min].get_team_name();
        for (int j = (i + 1); j < sz; j++){
            team2 = temp[j].get_team_name();
            if (team2 < team1){
                i_min = j;
                team1 = temp[i_min].get_team_name();
            }
        }
        if (i_min != i){
            std::swap(temp[i], temp[i_min]);
        }
    }

    for (int k = 0; k < sz; k++){
        output_Str += temp[k].display_stadium_info();
        output_Str += "\n";
    }
    ui->displayBox->setText(QString::fromStdString(output_Str));
    ui->instructions->setText("Displayed Sorted By Team Names!");
}

//O(n^3)
void MainWindow::display_sorted_by_team_names_american()
{
    std::string output_Str;

    int i_min;
    ILB::Stadium *temp = graph->get_vert();
    int sz = graph->get_vcount();

        ILB::Stadium american_league[60];
        int american_league_sz = 0;
        for (int q = 0; q < sz; q++){
            if (temp[q].get_american_league() == true){
                american_league[american_league_sz] = temp[q];
                american_league_sz++;
            }
        }
        std::cout << "american_league_sz: " << american_league_sz << std::endl;

    string team1, team2;

    for (int i = 0; i < american_league_sz; i++){
        i_min = i;
        team1 = american_league[i_min].get_team_name();
        for (int j = (i + 1); j < american_league_sz; j++){
            team2 = american_league[j].get_team_name();
            if (team2 < team1){
                i_min = j;
                team1 = american_league[i_min].get_team_name();
            }
        }
        if (i_min != i){
            std::swap(american_league[i], american_league[i_min]);
        }
    }

    for (int k = 0; k < american_league_sz; k++){
        output_Str += american_league[k].display_stadium_info();
        output_Str += "\n";
    }
    ui->displayBox->setText(QString::fromStdString(output_Str));
    ui->instructions->setText("Displayed Sorted By American Team Names!");
}

//O(n^3)
void MainWindow::display_sorted_by_team_names_national()
{
    std::string output_Str;

    int i_min;
    ILB::Stadium *temp = graph->get_vert();
    int sz = graph->get_vcount();

        ILB::Stadium national_league[60];
        int national_league_sz = 0;
        for (int q = 0; q < sz; q++){
            if (temp[q].get_american_league() == false){
                national_league[national_league_sz] = temp[q];
                national_league_sz++;
            }
        }
        std::cout << "national_league_sz: " << national_league_sz << std::endl;

    string team1, team2;

    for (int i = 0; i < national_league_sz; i++){
        i_min = i;
        team1 = national_league[i_min].get_team_name();
        for (int j = (i + 1); j < national_league_sz; j++){
            team2 = national_league[j].get_team_name();
            if (team2 < team1){
                i_min = j;
                team1 = national_league[i_min].get_team_name();
            }
        }
        if (i_min != i){
            std::swap(national_league[i], national_league[i_min]);
        }
    }

    for (int k = 0; k < national_league_sz; k++){
        output_Str += national_league[k].display_stadium_info();
        output_Str += "\n";
    }
    ui->displayBox->setText(QString::fromStdString(output_Str));
    ui->instructions->setText("Displayed Sorted By National Team Names!");
}

//O(n^4)
void MainWindow::display_sorted_by_grass_surface_and_team_names()
{
    std::string output_Str;

    int i_min;
    ILB::Stadium *temp = graph->get_vert();
    int sz = graph->get_vcount();

        ILB::Stadium grass_stadiums[60];
        int grass_stadiums_sz = 0;

        ILB::Stadium non_grass_stadiums[60];
        int non_grass_stadiums_sz = 0;
        for (int q = 0; q < sz; q++){
            if (temp[q].get_grass() == true){
                grass_stadiums[grass_stadiums_sz] = temp[q];
                grass_stadiums_sz++;
            }else{
                non_grass_stadiums[non_grass_stadiums_sz] = temp[q];
                non_grass_stadiums_sz++;
            }
        }
        std::cout << "grass_stadiums_sz: " << grass_stadiums_sz << std::endl;
        std::cout << "non_grass_stadiums_sz: " << non_grass_stadiums_sz << std::endl;

    string grass_team1, grass_team2;

    for (int i = 0; i < grass_stadiums_sz; i++){
        i_min = i;
        grass_team1 = grass_stadiums[i_min].get_team_name();
        for (int j = (i + 1); j < grass_stadiums_sz; j++){
            grass_team2 = grass_stadiums[j].get_team_name();
            if (grass_team2 < grass_team1){
                i_min = j;
                grass_team1 = grass_stadiums[i_min].get_team_name();
            }
        }
        if (i_min != i){
            std::swap(grass_stadiums[i], grass_stadiums[i_min]);
        }
    }

    for (int i = 0; i < non_grass_stadiums_sz; i++){
        i_min = i;
        grass_team1 = non_grass_stadiums[i_min].get_team_name();
        for (int j = (i + 1); j < non_grass_stadiums_sz; j++){
            grass_team2 = non_grass_stadiums[j].get_team_name();
            if (grass_team2 < grass_team1){
                i_min = j;
                grass_team1 = non_grass_stadiums[i_min].get_team_name();
            }
        }
        if (i_min != i){
            std::swap(non_grass_stadiums[i], non_grass_stadiums[i_min]);
        }
    }

    output_Str += ">Stadiums Listed Below Have Grass Surfaces\n";
    for (int k = 0; k < grass_stadiums_sz; k++){
        output_Str += grass_stadiums[k].display_stadium_info();
        output_Str += "\n";
    }

    output_Str += "\n";

    output_Str += ">Stadiums Listed Below Do Not Have Grass Surfaces\n";
    for (int k = 0; k < non_grass_stadiums_sz; k++){
        output_Str += non_grass_stadiums[k].display_stadium_info();
        output_Str += "\n";
    }
    ui->displayBox->setText(QString::fromStdString(output_Str));
    ui->instructions->setText("Displayed Sorted By Grass Surface And Team Names!");
}

//O(1)
void MainWindow::btn_display_distance_between_handler()
{
    state = "DISTANCE";
    ui->instructions->setText("Distance (stadium1/stadium2):");
}

//O(n^3)
bool MainWindow::display_distance_between(std::string input_str)
{
    bool valid = true;
    int i = 0;

    std::string output_Str;
    std::string stadium_name_str1;
    std::string stadium_name_str2;

    while ( (input_str[i] != '/') && (input_str[i] != NULL) ){
        stadium_name_str1 += input_str[i];
        i++;
    }
    i++;
    while ( (input_str[i] != '/') && (input_str[i] != NULL) ){
        stadium_name_str2 += input_str[i];
        i++;
    }

    if (stadium_name_str1.empty() || stadium_name_str2.empty()){
        valid = false;
    }
    if (valid){
        if (graph->vertice_exists(stadium_name_str1) && graph->vertice_exists(stadium_name_str2)){
            int* temp = graph->shortest_path(stadium_name_str1, stadium_name_str2);
            int distance = temp[0];
            int visited = temp[1];
            output_Str += "Distance: "; output_Str += std::to_string(distance); output_Str += "\n";
            output_Str += "Total Locations Visited: "; output_Str += std::to_string(visited); output_Str += "\n";
            ui->displayBox->setText(QString::fromStdString(output_Str));
        }else{
            valid = false;
        }
    }
    return valid;
}

//O(1)
void MainWindow::btn_display_custom_trip_handler()
{
    state = "CUSTOM_TRIP";
    ui->instructions->setText("Custom Trip: (stadium1/stadium2/stadium3/...)");
}

//O(n^2)
bool MainWindow::display_distance_between_custom_trip(std::string input_str)
{
    bool valid = true;

    std::string stadium_name_str;
    std::string output_Str;

    string stadium_collection[30];
    int stadium_collection_sz = 0;
    int i = 0;

    while (input_str[i] != NULL){
        while ((input_str[i] != '/') && (input_str[i] != NULL)){
            stadium_name_str += input_str[i];
            i++;
        }
        if ((input_str[i] == '/') || (input_str[i] == NULL)){
            if ((!stadium_name_str.empty()) && (graph->vertice_exists(stadium_name_str))){
            stadium_collection[stadium_collection_sz] = stadium_name_str;
            stadium_collection_sz++;
            }
            stadium_name_str.clear();
        }
        i++;
    }

    for (int i = 0; i < stadium_collection_sz; i++){
        std::cout << stadium_collection[i] << std::endl;
    }
    std::cout << std::endl;

    if (stadium_collection_sz == 0){
        valid = false;
    }
    if (valid){
        int* temp = graph->planned_path(stadium_collection, stadium_collection_sz);
        int distance = temp[0];
        int visited = temp[1];
        output_Str += "Custom Trip Info:\n";
        output_Str += "Distance: "; output_Str += std::to_string(distance); output_Str += "\n";
        output_Str += "Total Locations Visited: "; output_Str += std::to_string(visited); output_Str += "\n";
        ui->displayBox->setText(QString::fromStdString(output_Str));
    }
    return valid;
}

//O(n)
void MainWindow::change_stadium_property()
{
    if (isAdmin){

    bool valid = true;
    int i = 0;

    string selected_stadium = ui->inputBox_Admin_1->text().toStdString();
    string stadium_name = ui->inputBox_Admin_2->text().toStdString();
    string team_name = ui->inputBox_Admin_3->text().toStdString();
    string street_address = ui->inputBox_Admin_4->text().toStdString();
    string city_state_zip = ui->inputBox_Admin_5->text().toStdString();
    string box_office_number = ui->inputBox_Admin_6->text().toStdString();
    string date_opened = ui->inputBox_Admin_7->text().toStdString();
    string seating_capacity_str = ui->inputBox_Admin_8->text().toStdString();
    string american_league_str = ui->inputBox_Admin_9->text().toStdString();
    string grass_str = ui->inputBox_Admin_10->text().toStdString();

    int seating_capacity;
    bool american_league;
    bool grass;

    while (seating_capacity_str[i] != NULL){
        if ( (seating_capacity_str[i] > 47) && (seating_capacity_str[i] < 58) ){
            //valid
        }else{
            valid = false;
        }
        i++;
    }

    if (stadium_name.empty() || team_name.empty() || street_address.empty()
            || city_state_zip.empty() || box_office_number.empty() || date_opened.empty()
            || seating_capacity_str.empty() || american_league_str.empty() || grass_str.empty()){
        valid = false;
    }
    if (valid){
        if (graph->vertice_exists(selected_stadium)){
            seating_capacity = stoi(seating_capacity_str);
            if (american_league_str[0] == 'y'){
                american_league = true;
            }else{
                american_league = false;
            }

            if (grass_str[0] == 'y'){
                grass = true;
            }else{
                grass = false;
            }

            graph->get_stadium_admin(selected_stadium).set_team_name(team_name);
            graph->get_stadium_admin(selected_stadium).set_street_address(street_address);
            graph->get_stadium_admin(selected_stadium).set_city_state_zip(city_state_zip);
            graph->get_stadium_admin(selected_stadium).set_box_office_number(box_office_number);
            graph->get_stadium_admin(selected_stadium).set_date_opened(date_opened);
            graph->get_stadium_admin(selected_stadium).set_seating_capacity(seating_capacity);
            graph->get_stadium_admin(selected_stadium).set_american_league(american_league);
            graph->get_stadium_admin(selected_stadium).set_grass(grass);
            graph->get_stadium_admin(selected_stadium).set_stadium_name(stadium_name);
            ui->instructions_Admin_Special->setText("Changed Stadium Info!");
        }else{
            valid = false;
        }
    }else{
        ui->instructions_Admin_Special->setText("Failed to Change Stadium Info!");
    }

    }
}

//O(n^2)
void MainWindow::add_stadium()
{
    if (isAdmin){

    bool valid = true;
    int i = 0;
    string stadium_name = ui->inputBox_Admin_2->text().toStdString();
    string team_name = ui->inputBox_Admin_3->text().toStdString();
    string street_address = ui->inputBox_Admin_4->text().toStdString();
    string city_state_zip = ui->inputBox_Admin_5->text().toStdString();
    string box_office_number = ui->inputBox_Admin_6->text().toStdString();
    string date_opened = ui->inputBox_Admin_7->text().toStdString();
    string seating_capacity_str = ui->inputBox_Admin_8->text().toStdString();
    string american_league_str = ui->inputBox_Admin_9->text().toStdString();
    string grass_str = ui->inputBox_Admin_10->text().toStdString();

    int seating_capacity;
    bool american_league;
    bool grass;

    while (seating_capacity_str[i] != NULL){
        if ( (seating_capacity_str[i] > 47) && (seating_capacity_str[i] < 58) ){
            //valid
        }else{
            valid = false;
        }
        i++;
    }

    if (stadium_name.empty() || team_name.empty() || street_address.empty()
            || city_state_zip.empty() || box_office_number.empty() || date_opened.empty()
            || seating_capacity_str.empty() || american_league_str.empty() || grass_str.empty()){
        valid = false;
    }
    if (valid){
            seating_capacity = stoi(seating_capacity_str);
            if (american_league_str[0] == 'y'){
                american_league = true;
            }else{
                american_league = false;
            }

            if (grass_str[0] == 'y'){
                grass = true;
            }else{
                grass = false;
            }

            ILB::Stadium new_stadium(stadium_name, team_name, street_address, city_state_zip, box_office_number, date_opened, seating_capacity, american_league, grass);
            graph->addVertex(new_stadium);

            ui->instructions_Admin_Special->setText("Added Stadium Info!");
    }else{
        ui->instructions_Admin_Special->setText("Failed to Add Stadium Info!");
    }

    }
}

//O(1)
void MainWindow::btn_TRIP_major_league_shortest()
{
    std::string output_Str;

    int distance = graph->shortest_ham_path(0);
    int visited = 1337;
    output_Str += "Major League Trip Info:\n";
    output_Str += "Distance: "; output_Str += std::to_string(distance); output_Str += "\n";
    output_Str += "Total Locations Visited: "; output_Str += std::to_string(visited); output_Str += "\n";
    ui->displayBox->setText(QString::fromStdString(output_Str));
}

//O(1)
void MainWindow::btn_TRIP_american_league_shortest()
{
    std::string output_Str;

    int distance = graph->shortest_ham_path(1);
    int visited = 1337;
    output_Str += "American League Trip Info:\n";
    output_Str += "Distance: "; output_Str += std::to_string(distance); output_Str += "\n";
    output_Str += "Total Locations Visited: "; output_Str += std::to_string(visited); output_Str += "\n";
    ui->displayBox->setText(QString::fromStdString(output_Str));
}

//O(1)
void MainWindow::btn_TRIP_national_league_shortest()
{
    std::string output_Str;

    int distance = graph->shortest_ham_path(2);
    int visited = 1337;
    output_Str += "National League Trip Info:\n";
    output_Str += "Distance: "; output_Str += std::to_string(distance); output_Str += "\n";
    output_Str += "Total Locations Visited: "; output_Str += std::to_string(visited); output_Str += "\n";
    ui->displayBox->setText(QString::fromStdString(output_Str));
}
