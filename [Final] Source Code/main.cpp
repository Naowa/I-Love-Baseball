/*********************************************************
 * AUTHOR : Andy Tang, Kenny Van, Armen Mouradyan, Jillian Ongoco
 * I Love Baseball Group Project
 * CLASS : CS008
 * SECTION : MW: 7:00am - 8:25am, F: 7:00am - 11:15am
 * Due Date : 6/9/17
 *********************************************************/

#include "mainwindow.h"
#include <QApplication>

/**********************************************************
 * I Love Baseball Group Project
 *_________________________________________________________
 * implement a graph to store stadium information
 * implement a user interface that:
 * separates the user from admin
 * users are able to access stadiums but cannot modify its information
 *_________________________________________________________
 **********************************************************/

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
