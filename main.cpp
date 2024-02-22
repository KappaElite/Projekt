#include "Mainwindow.h"
#include "Player.h"
#include <QApplication>
#include <cstdlib>
#include <ctime>
#include <stdio.h>
#include <string>
using namespace std;

int main(int argc, char *argv[])
{


    QApplication a(argc, argv);
    string argument = argv[1];

    srand(time(NULL));

    if(argc > 1){
        MainWindow w(argument);
        w.show();
        return a.exec();
    }
    else{
        MainWindow w("1");
        w.show();
        return a.exec();
    }



}
