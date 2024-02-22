#include "Game.h"
#include "ui_game.h"
#include <QPixmap>
#include "Player.h"
#include "Card.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <cctype>
#include "Ending.h"
#include "EndingSplit.h"
#include "BadInput.h"
#include "MyException.h"

using namespace std;


Game::Game(QString name, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Game)
{
    ui->setupUi(this);
    setFixedSize(1301,815);
    participantCreator();

    playerName = name;
    playerPtr->setUsername(playerName);
    playerPtr->getMoneyFromFile();
    if(playerPtr->getMoney() == 0){
        playerPtr->setMoney();
    }
    moneyUpdate();

    QPixmap pix(":/img/img/blank_card.jpg");
    ui->pcard1->setPixmap(pix.scaled(100,100,Qt::KeepAspectRatio));
    ui->pcard2->setPixmap(pix.scaled(100,100,Qt::KeepAspectRatio));
    ui->ccard1->setPixmap(pix.scaled(100,100,Qt::KeepAspectRatio));
    ui->ccard2->setPixmap(pix.scaled(100,100,Qt::KeepAspectRatio));
    ui->addCard->setStyleSheet("QPushButton { background-color: black; }");
    ui->split->setStyleSheet("QPushButton { background-color: black; }");
    ui->stand->setStyleSheet("QPushButton { background-color: black; }");
    ui->double_2->setStyleSheet("QPushButton { background-color: black; }");
    ui->doublesplit->setStyleSheet("QPushButton { background-color: black; }");
    ui->standsplit->setStyleSheet("QPushButton { background-color: black; }");
    ui->hitsplit->setStyleSheet("QPushButton { background-color: black; }");
    ui->addCash->setAlignment(Qt::AlignCenter);
    ui->doublesplit->hide();
    ui->double_2->setEnabled(false);
    ui->stand->setEnabled(false);
    ui->standsplit->hide();
    ui->label_4->hide();
    ui->split->setEnabled(false);
    ui->hitsplit->hide();
    ui->cardsplitsum->hide();
    ui->addCard->setEnabled(false);
    ui->label_3->setStyleSheet("QLabel { color: white; font-size: 25pt; font-weight: bold; }");
    this->setStyleSheet("QDialog { border-image: url(:/background/background/blackjack.png) 0 0 0 0 stretch stretch; }");

}

Game::~Game()
{
    delete ui;
}

void Game::on_start_clicked()
{
    moneyChange = ui->upMoney->text();
    try {
        if(moneyChange == ""){
            throw MyException("Nie podano ilości pieniędzy");
        }
    } catch (const MyException &e) {
        cerr<<"Wyjątek: " << e.what()<<endl;
        moneyChange = "10";
    }

    inputCheck(moneyChange);
    moneyChangeToString = moneyChange.toStdString();

    ui->label_3->hide();
    ui->upMoney->hide();
    ui->start->setEnabled(false);
    ui->double_2->setEnabled(true);
    ui->stand->setEnabled(true);
    ui->addCard->setEnabled(true);

    cardNumP += 2;

    try {
        if(stod(moneyChangeToString) > playerPtr->getMoney()){
            throw MyException("Podano za dużą kwotę pieniędzy");
        }

    }  catch (const MyException &e) {
        cerr<<"Wyjątek: " << e.what() << endl;
        moneyChangeToString = to_string(playerPtr->getMoney());
    }


    string pathA = playerPtr->cardCreator();
    string pathB = playerPtr->cardCreator();
    string pathC = croupierPtr->cardCreator();
    string pathD = croupierPtr->cardCreator();

    bool flag = playerPtr->splitAcces();

    if(flag == true){
        ui->split->setEnabled(true);
    }

    upValue(moneyChangeToString);

    if(playerPtr->getMoney() - stod(moneyChangeToString) < 0){
        ui->double_2->setEnabled(false);
        ui->split->setEnabled(false);
    }

    moneyUpdate();
    playerPtr->saveMoneyToFile();
    sumUpdate();
    splitCard = prefix + pathA;

    QPixmap c1(QString::fromStdString(prefix + pathA));
    QPixmap c2(QString::fromStdString(prefix + pathB));
    QPixmap cc1(QString::fromStdString(prefix + pathC));

    ui->pcard1->setPixmap(c1.scaled(100,100,Qt::KeepAspectRatio));
    ui->pcard2->setPixmap(c2.scaled(100,100,Qt::KeepAspectRatio));
    ui->ccard1->setPixmap(cc1.scaled(100,100,Qt::KeepAspectRatio));


    if(playerPtr->getSum() == 21){
        playerPtr->blackJack(0,moneyChangeToString,timesDouble,timesSplitDouble);
        ui->addCard->setEnabled(false);
        ui->stand->setEnabled(false);
        ui->double_2->setEnabled(false);

        Ending win(croupierPtr->getVector(),this,playerName,3);
        win.setModal(true);
        win.exec();
    }
    else if(croupierPtr->getSum() == 21){
        ui->addCard->setEnabled(false);
        ui->stand->setEnabled(false);
        ui->double_2->setEnabled(false);

        Ending lose(croupierPtr->getVector(),this,playerName,4);
        lose.setModal(true);
        lose.exec();
    }
}


void Game::on_addCard_clicked()
{
    cardNumP+=1;
    string path = playerPtr->cardCreator();
    sumUpdate();



    if(cardNumP == 3){
        QPixmap c3(QString::fromStdString(prefix+path));
        ui->pcard3->setPixmap(c3.scaled(100,100,Qt::KeepAspectRatio));
    }
    else if(cardNumP == 4){
        QPixmap c4(QString::fromStdString(prefix+path));
        ui->pcard4->setPixmap(c4.scaled(100,100,Qt::KeepAspectRatio));
    }
    else if(cardNumP == 5){
        QPixmap c5(QString::fromStdString(prefix+path));
        ui->pcard5->setPixmap(c5.scaled(100,100,Qt::KeepAspectRatio));
    }
    else if(cardNumP == 6){
        QPixmap c6(QString::fromStdString(prefix+path));
        ui->pcard6->setPixmap(c6.scaled(100,100,Qt::KeepAspectRatio));
    }
    else if(cardNumP == 7){
        QPixmap c7(QString::fromStdString(prefix+path));
        ui->pcard7->setPixmap(c7.scaled(100,100,Qt::KeepAspectRatio));
    }
    else if(cardNumP == 8){
        QPixmap c8(QString::fromStdString(prefix+path));
        ui->pcard8->setPixmap(c8.scaled(100,100,Qt::KeepAspectRatio));
    }
    else if(cardNumP == 9){
        QPixmap c9(QString::fromStdString(prefix+path));
        ui->pcard9->setPixmap(c9.scaled(100,100,Qt::KeepAspectRatio));
    }
    else if(cardNumP == 10){
        QPixmap c10(QString::fromStdString(prefix+path));
        ui->pcard10->setPixmap(c10.scaled(100,100,Qt::KeepAspectRatio));
    }
    else if(cardNumP == 11){
        QPixmap c11(QString::fromStdString(prefix+path));
        ui->pcard11->setPixmap(c11.scaled(100,100,Qt::KeepAspectRatio));
    }

    if(playerPtr->getSum() > 21){
        playerPtr->blackJack(1,moneyChangeToString,timesDouble,timesSplitDouble);
        if(playerPtr->getSplitFlag() == true && playerPtr->getSplitSum() <= 21){
            if(playerPtr->getSplitSum() == croupierPtr->getSum()){
                playerPtr->blackJack(1,moneyChangeToString,timesDouble,timesSplitDouble);
            }
            else if(playerPtr->getSplitSum() > croupierPtr->getSum()){
                playerPtr->blackJack(2,moneyChangeToString,timesDouble,timesSplitDouble);
            }
        }
        ui->addCard->setEnabled(false);
        ui->stand->setEnabled(false);
        ui->double_2->setEnabled(false);


        Ending lose(croupierPtr->getVector(),this,playerName,1);
        lose.setModal(true);
        lose.exec();

    }

    if(playerPtr->getSum() == 21){
        if(playerPtr->getSplitFlag() == true && playerPtr->getSplitSum() <= 21){
            if(playerPtr->getSplitSum() == croupierPtr->getSum()){
                playerPtr->blackJack(1,moneyChangeToString,timesDouble,timesSplitDouble);
            }
            else if(playerPtr->getSplitSum() > croupierPtr->getSum()){
               playerPtr->blackJack(2,moneyChangeToString,timesDouble,timesSplitDouble);
            }
        }
        playerPtr->blackJack(0,moneyChangeToString,timesDouble,timesSplitDouble);
        ui->addCard->setEnabled(false);
        ui->stand->setEnabled(false);
        ui->double_2->setEnabled(false);

        Ending win(croupierPtr->getVector(),this,playerName,3);
        win.setModal(true);
        win.exec();
    }
    ui->double_2->setEnabled(false);

}


void Game::on_double_2_clicked()
{
    timesDouble++;
    upValue(moneyChangeToString);
    moneyUpdate();
    playerPtr->saveMoneyToFile();
    string path = playerPtr->cardCreator();
    moneyUpdate();
    sumUpdate();
    QPixmap c3(QString::fromStdString(prefix+path));
    ui->pcard3->setPixmap(c3.scaled(100,100,Qt::KeepAspectRatio));
    ui->addCard->setEnabled(false);
    ui->split->setEnabled(false);
    ui->double_2->setEnabled(false);

    if(playerPtr->getSum() > 21){
        playerPtr->blackJack(1,moneyChangeToString,timesDouble,timesSplitDouble);
        if(playerPtr->getSplitFlag() == true && playerPtr->getSplitSum() <= 21){
            if(playerPtr->getSplitSum() == croupierPtr->getSum()){
                playerPtr->blackJack(1,moneyChangeToString,timesDouble,timesSplitDouble);
            }
            else if(playerPtr->getSplitSum() > croupierPtr->getSum()){

                playerPtr->blackJack(2,moneyChangeToString,timesDouble,timesSplitDouble);
            }
        }

        ui->addCard->setEnabled(false);
        ui->stand->setEnabled(false);
        ui->double_2->setEnabled(false);

        Ending lose(croupierPtr->getVector(),this,playerName,1);
        lose.setModal(true);
        lose.exec();
    }
    if(playerPtr->getSum() == 21){
        if(playerPtr->getSplitFlag() == true && playerPtr->getSplitSum() <= 21){
            if(playerPtr->getSplitSum() == croupierPtr->getSum()){
                playerPtr->blackJack(1,moneyChangeToString,timesDouble,timesSplitDouble);
            }
            else if(playerPtr->getSplitSum() > croupierPtr->getSum()){

                playerPtr->blackJack(2,moneyChangeToString,timesDouble,timesSplitDouble);
            }
        }
        playerPtr->blackJack(0,moneyChangeToString,timesDouble,timesSplitDouble);
        ui->addCard->setEnabled(false);
        ui->stand->setEnabled(false);
        ui->double_2->setEnabled(false);


        Ending win(croupierPtr->getVector(),this,playerName,3);
        win.setModal(true);
        win.exec();
    }
}


void Game::moneyUpdate(){
    ui->money->setText(QString::number(playerPtr->getMoney()));

}

void Game::on_stand_clicked(){
    ui->addCard->setEnabled(false);
    ui->stand->setEnabled(false);
    ui->double_2->setEnabled(false);

    while(croupierPtr->getSum() < 17){
        string tmp = croupierPtr->cardCreator();
        sumUpdate();
        croupierPix.push_back(QPixmap(QString::fromStdString(prefix+tmp)));
        croupierCard++;
        croupierAdd();
    }
    if(playerPtr->getSplitFlag() == true && playerPtr->getSplitSum() <= 21){
        if(playerPtr->getSplitSum() == croupierPtr->getSum()){
            playerPtr->blackJack(1,moneyChangeToString,timesDouble,timesSplitDouble);
        }
        else if(playerPtr->getSplitSum() > croupierPtr->getSum()){

            playerPtr->blackJack(2,moneyChangeToString,timesDouble,timesSplitDouble);
        }
    }
    if(croupierPtr->getSum() > 21){
        playerPtr->blackJack(0,moneyChangeToString,timesDouble,timesSplitDouble);
        ui->addCard->setEnabled(false);
        ui->stand->setEnabled(false);
        ui->double_2->setEnabled(false);


        Ending winCp(croupierPtr->getVector(),this,playerName,2);
        winCp.setModal(true);
        winCp.exec();
    }



    if(playerPtr->getSum() == croupierPtr->getSum()){
        playerPtr->blackJack(1,moneyChangeToString,timesDouble,timesSplitDouble);
        ui->addCard->setEnabled(false);
        ui->stand->setEnabled(false);
        ui->double_2->setEnabled(false);


        Ending lose(croupierPtr->getVector(),this,playerName,5);
        lose.setModal(true);
        lose.exec();
    }

    if(playerPtr->getSum() > croupierPtr->getSum()){
        playerPtr->blackJack(0,moneyChangeToString,timesDouble,timesSplitDouble);
        ui->addCard->setEnabled(false);
        ui->stand->setEnabled(false);
        ui->double_2->setEnabled(false);


        Ending win(croupierPtr->getVector(),this,playerName,0);
        win.setModal(true);
        win.exec();
    }

    if(croupierPtr->getSum() > playerPtr->getSum() && croupierPtr->getSum()<= 21){
        ui->addCard->setEnabled(false);
        ui->stand->setEnabled(false);
        ui->double_2->setEnabled(false);


        Ending lose(croupier->getVector(),this,playerName,6);
        lose.setModal(true);
        lose.exec();
    }


}

void Game::croupierAdd(){
    if(croupierCard == 1){
        ui->ccard3->setPixmap(croupierPix[0].scaled(100,100,Qt::KeepAspectRatio));
    }
    else if(croupierCard == 2){
        ui->ccard4->setPixmap(croupierPix[1].scaled(100,100,Qt::KeepAspectRatio));
    }
    else if(croupierCard == 3){
        ui->ccard5->setPixmap(croupierPix[2].scaled(100,100,Qt::KeepAspectRatio));
    }
    else if(croupierCard == 4){
        ui->ccard6->setPixmap(croupierPix[3].scaled(100,100,Qt::KeepAspectRatio));
    }
    else if(croupierCard == 5){
        ui->ccard7->setPixmap(croupierPix[4].scaled(100,100,Qt::KeepAspectRatio));
    }
    else if(croupierCard == 6){
        ui->ccard8->setPixmap(croupierPix[5].scaled(100,100,Qt::KeepAspectRatio));
    }
    else if(croupierCard == 7){
        ui->ccard9->setPixmap(croupierPix[6].scaled(100,100,Qt::KeepAspectRatio));
    }
    else if(croupierCard == 8){
        ui->ccard10->setPixmap(croupierPix[7].scaled(100,100,Qt::KeepAspectRatio));
    }
}

void Game::sumUpdate(){

    ui->cardsum->setText(QString::number(playerPtr->getSum()));
    ui->cardsplitsum->setText(QString::number(playerPtr->getSplitSum()));


}

void Game::on_split_clicked()
{
    ui->stand->setEnabled(false);
    ui->double_2->setEnabled(false);
    ui->addCard->setEnabled(false);
    ui->split->setEnabled(false);
    ui->doublesplit->setEnabled(true);
    ui->standsplit->setEnabled(true);
    ui->hitsplit->setEnabled(true);
    ui->doublesplit->show();
    ui->standsplit->show();
    ui->hitsplit->show();
    ui->cardsplitsum->show();
    ui->label_4->show();

    playerPtr->correctSplitValue();
    playerPtr->setSplitFlag(1);
    upValue(moneyChangeToString);
    moneyUpdate();
    playerPtr->saveMoneyToFile();
    sumUpdate();
    moneyUpdate();

    QPixmap c2(QString::fromStdString(splitCard));
    size_t found = splitCard.find("14");
    if(found != string::npos){
        splitAce = true;
        ui->doublesplit->setEnabled(false);
    }
    if(playerPtr->getMoney() - stod(moneyChangeToString) < 0){
        ui->doublesplit->setEnabled(false);
    }

    ui->pcard2->clear();
    ui->splitcard1->setPixmap(c2.scaled(100,100,Qt::KeepAspectRatio));
}


void Game::on_standsplit_clicked()
{
    ui->standsplit->setEnabled(false);
    ui->hitsplit->setEnabled(false);
    ui->doublesplit->setEnabled(false);
    ui->stand->setEnabled(true);
    ui->double_2->setEnabled(true);
    ui->addCard->setEnabled(true);
}


void Game::on_hitsplit_clicked()
{
    if(splitAce == true){
        ui->hitsplit->setEnabled(false);
    }
    cardNumPSplit+=1;
    playerPtr->setSplitHitFlag(1);
    string path = playerPtr->cardCreator();
    playerPtr->setSplitHitFlag(0);
    sumUpdate();

    ui->doublesplit->setEnabled(false);


    if(cardNumPSplit == 2){
        QPixmap c12(QString::fromStdString(prefix+path));
        ui->splitcard2->setPixmap(c12.scaled(100,100,Qt::KeepAspectRatio));
    }
    else if(cardNumPSplit == 3){
        QPixmap c13(QString::fromStdString(prefix+path));
        ui->splitcard3->setPixmap(c13.scaled(100,100,Qt::KeepAspectRatio));
    }
    else if(cardNumPSplit == 4){
        QPixmap c14(QString::fromStdString(prefix+path));
        ui->splitcard4->setPixmap(c14.scaled(100,100,Qt::KeepAspectRatio));
    }
    else if(cardNumPSplit == 5){
        QPixmap c15(QString::fromStdString(prefix+path));
        ui->splitcard5->setPixmap(c15.scaled(100,100,Qt::KeepAspectRatio));
    }
    else if(cardNumPSplit == 6){
        QPixmap c16(QString::fromStdString(prefix+path));
        ui->splitcard7->setPixmap(c16.scaled(100,100,Qt::KeepAspectRatio));
    }
    else if(cardNumPSplit == 7){
        QPixmap c17(QString::fromStdString(prefix+path));
        ui->splitcard8->setPixmap(c17.scaled(100,100,Qt::KeepAspectRatio));
    }
    else if(cardNumPSplit == 8){
        QPixmap c18(QString::fromStdString(prefix+path));
        ui->splitcard9->setPixmap(c18.scaled(100,100,Qt::KeepAspectRatio));
    }
    else if(cardNumPSplit == 9){
        QPixmap c19(QString::fromStdString(prefix+path));
        ui->splitcard10->setPixmap(c19.scaled(100,100,Qt::KeepAspectRatio));
    }
    else if(cardNumPSplit == 10){
        QPixmap c20(QString::fromStdString(prefix+path));
        ui->splitcard11->setPixmap(c20.scaled(100,100,Qt::KeepAspectRatio));
    }
    else if(cardNumPSplit == 11){
        QPixmap c21(QString::fromStdString(prefix+path));
        ui->splitcard12->setPixmap((c21.scaled(100,100,Qt::KeepAspectRatio)));
    }


    if(playerPtr->getSplitSum() > 21){
        playerPtr->blackJack(1,moneyChangeToString,timesDouble,timesSplitDouble);
        on_standsplit_clicked();
        EndingSplit lose(1);
        lose.setModal(true);
        lose.exec();
    }

}


void Game::on_doublesplit_clicked()
{
    timesSplitDouble++;
    sumUpdate();
    upValue(moneyChangeToString);
    moneyUpdate();
    playerPtr->saveMoneyToFile();
    playerPtr->setSplitHitFlag(1);
    string path = playerPtr->cardCreator();
    playerPtr->setSplitHitFlag(0);
    moneyUpdate();
    sumUpdate();
    QPixmap c12(QString::fromStdString(prefix+path));
    ui->splitcard2->setPixmap(c12.scaled(100,100,Qt::KeepAspectRatio));
    ui->hitsplit->setEnabled(false);
    ui->doublesplit->setEnabled(false);
    if(playerPtr->getSum() > 21){
        playerPtr->blackJack(1,moneyChangeToString,timesDouble,timesSplitDouble);
        EndingSplit lose(1);
        lose.setModal(true);
        lose.exec();
    }

}

void Game::participantCreator(){


    player = new Player();
    croupier = new Croupier();
    participant.push_back(player);
    participant.push_back(croupier);
    playerPtr = dynamic_cast<Player*>(participant[0]);
    croupierPtr = dynamic_cast<Croupier*>(participant[1]);

}



void Game::upValue(string input){
   *playerPtr-=stod(input);
}



void Game::inputCheck(QString a){
    bool isDouble = false;
    double doubleValue = a.toDouble(&isDouble);

    try {
        if(isDouble == false){
            throw MyException("Podana ilość pieniędzy nie jest liczbą");

        }
    } catch (MyException &e) {
        cerr << "Wyjątek: "<< e.what()<<endl;
        moneyChange = "10";
        BadInput badNum;
        badNum.setModal(true);
        badNum.exec();
    }

}

