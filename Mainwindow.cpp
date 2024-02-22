#include "Mainwindow.h"
#include "./ui_mainwindow.h"
#include "Game.h"
#include <iostream>
#include <Qfile>
#include <QTextStream>
#include <string>
#include <QDir>
#include <QCoreApplication>
#include <QFile>
#include "MyException.h"
#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>


using namespace std;

MainWindow::MainWindow(string type, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(800,599);

    if(type == "1"){
        this->setStyleSheet("QMainWindow { border-image: url(:/background/background/blackjack.png) 0 0 0 0 stretch stretch; }");
        ui->nameText->setStyleSheet("color: black;");
    }
    else{
        this->setStyleSheet("QMainWindow { border-image: url(:/background/background/alternative.png) 0 0 0 0 stretch stretch; }");
        ui->nameText->setStyleSheet("color: white; font-size: 20px");
    }


   ui->pushButton->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 red, stop:1 darkred);"
                                  "color: white; /* Biały kolor tekstu */"
                                  "border: 2px solid black; /* Czarne obramowanie */"
                                  "padding: 5px; /* Dodatkowy odstęp wewnątrz przycisku */");
   ui->boxLayout->setAlignment(Qt::AlignCenter);
   ui->nameText->setAlignment(Qt::AlignCenter);



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    this->hide();
    QString pName = ui->userName->text();
    if(pName == ""){
        pName = "DefaultPlayer";
    }
    string str = pName.toStdString();

    if(isRep(pName) == false){
        binary(pName);
    }
    else{
        cout<<"Wystapilo powtorzenie"<<endl;
    }

    Game game(pName);
    game.setModal(true);
    game.exec();

    binary();



}

void MainWindow::binary(QString name){
    QString filePath = QCoreApplication::applicationDirPath() + QDir::separator() + "save.txt";

    try{
        QFile file(filePath);
        name+=":";
        name+="1000";
        if (file.open(QIODevice::Append)) {
            QDataStream stream(&file);
            QByteArray nameBytes = name.toUtf8();
            stream << static_cast <quint32>(nameBytes.size());
            stream.writeRawData(nameBytes.constData(),nameBytes.size());
            file.close();
        } else {
            throw MyException("Błąd otwarcia pliku");
        }
    }
    catch(const MyException &e){
        cerr<<"Wyjątek: "<<e.what() << endl;
        QCoreApplication::quit();
    }
    catch(const exception &e){
        cerr<<"Standardowy wyjątek: " << e.what() <<endl;
        QCoreApplication::quit();
    }

    catch(...){
        cerr<<"Wystąpił wyjątek spoza standarowej bilbioteki wyjątków "<<endl;
        QCoreApplication::quit();
    }



}

void MainWindow::binary(){
    QString filePath = QCoreApplication::applicationDirPath() + QDir::separator() + "save.txt";

    try{
        QFile file(filePath);

        if (file.open(QIODevice::ReadOnly)) {
            QDataStream stream(&file);

            while(!stream.atEnd()){
                quint32 dataSize;
                stream >> dataSize;

                QByteArray data;
                data.resize(dataSize);
                stream.readRawData(data.data(), dataSize);

                qDebug() << "Binary File Content:";
                qDebug().noquote() << data;
            }

            file.close();
        } else {
            throw MyException("Błąd otwarcia pliku");

        }
    }
    catch(const MyException &e){
        cerr<<"Wyjątek: "<<e.what() << endl;
        QCoreApplication::quit();
    }
    catch(const exception &e){
        cerr<<"Standardowy wyjątek: " << e.what() <<endl;
        QCoreApplication::quit();
    }

    catch(...){
        cerr<<"Wystąpił wyjątek spoza standarowej bilbioteki wyjątków "<<endl;
        QCoreApplication::quit();
    }

}


bool MainWindow::isRep(QString name){

    QString filePath = QCoreApplication::applicationDirPath() + QDir::separator() + "save.txt";
    try {
        QFile file(filePath);
        if (file.open(QIODevice::ReadOnly)){
            QDataStream stream(&file);
            while(!stream.atEnd()){
                quint32 dataSize;
                stream >> dataSize;
                QByteArray data;
                data.resize(dataSize);
                stream.readRawData(data.data(),dataSize);
                QString line = QString::fromUtf8(data);
                if(line.startsWith(name)){
                    file.close();
                    return true;
                }
            }
            file.close();
        }
        else{
            throw MyException("Błąd otwarcia pliku");
        }


    }
    catch(const MyException &e){
        cerr<<"Wyjątek: "<<e.what() << endl;
        QCoreApplication::quit();
    }
    catch(const exception &e){
        cerr<<"Standardowy wyjątek: " << e.what() <<endl;
        QCoreApplication::quit();
    }

    catch(...){
        cerr<<"Wystąpił wyjątek spoza standarowej bilbioteki wyjątków "<<endl;
        QCoreApplication::quit();
    }


    return false;
}







