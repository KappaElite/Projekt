#include "Ending.h"
#include "ui_ending.h"
#include "Game.h"
#include <QCoreApplication>

Ending::Ending(vector<Card> cards,Game* game,QString name, int flag, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Ending)
    , gamePtr(game)
{

    ui->setupUi(this);
    setFixedSize(893,637);
    ui->verticalLayout->setAlignment(Qt::AlignCenter);
    ui->label->setStyleSheet("QLabel { color: white; font-size: 20px, font-weight: bold; }");


    for(int i = 0; i< cards.size(); ++i){
        int a = cards[i].getCard();
        string b = cards[i].getCardType();
        string path = b + to_string(a);
        path += ".png";

        if(i == 0){
            QPixmap c1(QString::fromStdString(prefix + path));
            ui->ccard1->setPixmap(c1.scaled(100,100,Qt::KeepAspectRatio));
        }
        else if(i == 1){
            QPixmap c2(QString::fromStdString(prefix + path));
            ui->ccard2->setPixmap(c2.scaled(100,100,Qt::KeepAspectRatio));
        }
        else if(i == 2){
            QPixmap c3(QString::fromStdString(prefix + path));
            ui->ccard3->setPixmap(c3.scaled(100,100,Qt::KeepAspectRatio));
        }
        else if(i == 3){
            QPixmap c4(QString::fromStdString(prefix + path));
            ui->ccard4->setPixmap(c4.scaled(100,100,Qt::KeepAspectRatio));
        }
        else if(i == 4){
            QPixmap c5(QString::fromStdString(prefix + path));
            ui->ccard5->setPixmap(c5.scaled(100,100,Qt::KeepAspectRatio));
        }
        else if(i == 5){
            QPixmap c6(QString::fromStdString(prefix + path));
            ui->ccard6->setPixmap(c6.scaled(100,100,Qt::KeepAspectRatio));
        }
        else if(i == 6){
            QPixmap c7(QString::fromStdString(prefix + path));
            ui->ccard7->setPixmap(c7.scaled(100,100,Qt::KeepAspectRatio));
        }
        else if(i == 7){
            QPixmap c8(QString::fromStdString(prefix + path));
            ui->ccard8->setPixmap(c8.scaled(100,100,Qt::KeepAspectRatio));
        }
        else if(i == 8){
            QPixmap c9(QString::fromStdString(prefix + path));
            ui->ccard9->setPixmap(c9.scaled(100,100,Qt::KeepAspectRatio));
        }
        else if(i == 9){
            QPixmap c10(QString::fromStdString(prefix + path));
            ui->ccard10->setPixmap(c10.scaled(100,100,Qt::KeepAspectRatio));
        }
    }


    if(flag == 0){
        ui->result->setText("Wygrałeś przewagą punktów");
        ui->result->setStyleSheet("QLabel { color: white; font-size: 20px }");
        this->setStyleSheet("QDialog { border-image: url(:/background/background/win.png) 0 0 0 0 stretch stretch; }");
    }
    else if(flag == 1){
        ui->result->setText("Przekroczyłeś 21 punktów");
        ui->result->setStyleSheet("QLabel { color: white; font-size: 20px }");
        this->setStyleSheet("QDialog { border-image: url(:/background/background/lo.png) 0 0 0 0 stretch stretch; }");
    }
    else if(flag == 2){
        ui->result->setText("Krupier przekroczył 21 punktów - wygrałeś");
        ui->result->setStyleSheet("QLabel { color: white; font-size: 20px }");
        this->setStyleSheet("QDialog { border-image: url(:/background/background/win.png) 0 0 0 0 stretch stretch; }");
    }
    else if(flag == 3){
        ui->result->setText("Wygrałeś przez Black Jack");
        ui->result->setStyleSheet("QLabel { color: white; font-size: 20px }");
        this->setStyleSheet("QDialog { border-image: url(:/background/background/win.png) 0 0 0 0 stretch stretch; }");
    }
    else if(flag == 4){
        ui->result->setText("Krupier wygrał przez Black Jack");
        ui->result->setStyleSheet("QLabel { color: white; font-size: 20px }");
        this->setStyleSheet("QDialog { border-image: url(:/background/background/lo.png) 0 0 0 0 stretch stretch; }");
    }
    else if(flag == 5){
        ui->result->setText("Remis- wygrywa krupier");
        ui->result->setStyleSheet("QLabel { color: white; font-size: 20px }");
        this->setStyleSheet("QDialog { border-image: url(:/background/background/lo.png) 0 0 0 0 stretch stretch; }");
    }
    else if(flag == 6){
        ui->result->setText("Krupier wygrał przewagą punktów");
        ui->result->setStyleSheet("QLabel { color: white; font-size: 20px }");
        this->setStyleSheet("QDialog { border-image: url(:/background/background/lo.png) 0 0 0 0 stretch stretch; }");
    }
    nextGameName = name;



}

Ending::~Ending()
{
    delete ui;
}


void Ending::on_nextGame_clicked()
{
    this->close();
    gamePtr->close();
    Game g1(nextGameName);
    g1.setModal(true);
    g1.exec();
}


void Ending::on_close_clicked()
{
    QCoreApplication::quit();
}





