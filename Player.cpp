#include "Player.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Card.h"
#include "ui_game.h"
#include <QPixmap>
#include <QDir>
#include <QFile>
#include <string>
#include "MyException.h"



using namespace std;


Player::Player() {
}


Player::~Player(){
    free(objects);
}


int Player::getSum(){
    return sum;
}


double Player::getMoney(){
    return money;
}


int Player::getSplitSum(){
    return splitSum;
}



int Player::getCardNum(){
    return cardNumP;
}

void Player::setSplitFlag(int a){
    if(a == 0){
        splitFlag = false;
    }
    else if(a == 1){
        splitFlag = true;
    }
}

bool Player::getSplitFlag(){
    return splitFlag;
}


void Player::setMoney(){
    money = 1000;
}

void Player::setSplitHitFlag(int a){
    if(a == 1){
        splitHitFlag = true;
    }
    else if(a == 0){
        splitHitFlag = false;
    }
}


void Player::setUsername(QString a){
    username = a;
}


bool Player::splitAcces(){

    if(objects[0].getCard() == objects[1].getCard()){
        return true;
    }
    else{
        return false;
    }
}

string Player::cardCreator(){


    objects[arraySize - 1] = Card();
    if(splitHitFlag == true){
        splitCards.push_back(objects[arraySize-1]);
    }
    arraySize++;
    objects = static_cast<Card*>(realloc(objects,arraySize*sizeof(Card)));



    int a = objects[cardNumP].getCard();
    int tmp = objects[cardNumP].getValue();
    string b = objects[cardNumP].getCardType();
    string path = b + to_string(a);
    path += ".png";

    if(splitHitFlag == true){
        splitSum += tmp;
        aceChoice();
    }
    else{
        sum += tmp;
        aceChoice();
    }

    cardNumP += 1;

    return path;
}


string Player::splitCardCreator(){
    objects[arraySize - 1] = Card(1);
    if(splitHitFlag == true){
        splitCards.push_back(objects[arraySize-1]);
    }
    arraySize++;
    objects = static_cast<Card*>(realloc(objects,arraySize*sizeof(Card)));

    int a = objects[cardNumP].getCard();
    int tmp = objects[cardNumP].getValue();
    string b = objects[cardNumP].getCardType();
    string path = b + to_string(a);
    path += ".png";

    if(splitHitFlag == true){
        splitSum += tmp;
        aceChoice();
    }
    else{
        sum += tmp;
        aceChoice();
    }

    cardNumP += 1;

    return path;
}



string Player::splitHitCardCreator(){
    objects[arraySize - 1] = Card(3.14);
    if(splitHitFlag == true){
        splitCards.push_back(objects[arraySize-1]);
    }
    arraySize++;
    objects = static_cast<Card*>(realloc(objects,arraySize*sizeof(Card)));



    int a = objects[cardNumP].getCard();
    int tmp = objects[cardNumP].getValue();
    string b = objects[cardNumP].getCardType();
    string path = b + to_string(a);
    path += ".png";

    if(splitHitFlag == true){
        splitSum += tmp;
        aceChoice();
    }
    else{
        sum += tmp;
        aceChoice();
    }

    cardNumP += 1;

    return path;
}


void Player::correctSplitValue(){
    int a = objects[1].getValue();
    splitCards.push_back(objects[1]);
    sum -= a;
    splitSum += a;
}


void Player::getMoneyFromFile(){

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
                if(line.startsWith(username)){
                    string tmp = line.toStdString();
                    size_t colonPos = tmp.find(':');
                    money = stod(tmp.substr(colonPos + 1));
                    break;
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
    }
    catch(const exception &e){
        cerr<<"Standardowy wyjątek: " << e.what() <<endl;
    }

    catch(...){
        cerr<<"Wystąpił wyjątek spoza standarowej bilbioteki wyjątków "<<endl;
    }


}

void Player::saveMoneyToFile(){

    QString filePath = QCoreApplication::applicationDirPath() + QDir::separator() + "save.txt";
    QString tempPath = QCoreApplication::applicationDirPath() + QDir::separator() + "temp.txt";

    QFile file(filePath);
    QFile tempFile(tempPath);
    try {
        if (file.open(QIODevice::ReadWrite) && tempFile.open(QIODevice::ReadWrite)){
            QDataStream stream(&file);
            QDataStream temp(&tempFile);

            while(!stream.atEnd()){

                quint32 dataSize;
                stream >> dataSize;
                QByteArray data;
                data.resize(dataSize);


                stream.readRawData(data.data(),dataSize);
                QString line = QString::fromUtf8(data);

                if(line.startsWith(username)){
                    string tmp = line.toStdString();
                    size_t colonPos = tmp.find(':');
                    string f = tmp.substr(0,colonPos);
                    f+=":";
                    f+=to_string(money);
                    QString updated = QString::fromStdString(f);
                    QByteArray updatedData = updated.toUtf8();

                    temp << static_cast<quint32>(updatedData.size());
                    temp.writeRawData(updatedData.constData(), updatedData.size());

                }
                else{
                    temp<<static_cast<quint32>(dataSize);
                    temp.writeRawData(data.constData(),dataSize);
                }
            }
            file.close();
            tempFile.close();
            file.remove();
            tempFile.rename(filePath);
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



}


void Player::blackJack(int a, string b, int timesDouble, int timesSplitDouble){

    double temp = stod(b);
    if(a == 0){
        if(sum == 21){
            money = money + timesDouble*temp + timesDouble*temp + 0.5*timesDouble*temp;
        }
        else{
            money = money + timesDouble*temp + timesDouble*temp;
        }
        saveMoneyToFile();
    }
    else if (a == 1){
        saveMoneyToFile();
    }
    else if (a == 2){
        if(splitSum == 21){
            money = money + timesSplitDouble*temp + timesSplitDouble*temp + 0.5*timesSplitDouble*temp;
        }
        else{
            money = money + timesSplitDouble*temp + timesSplitDouble*temp;
        }
        saveMoneyToFile();
    }

}

void Player::aceChoice(){
    int splitAceCounter = 0;
    int aceCounter = 0;
    vector<int> index;

    for (int i = 0; i<splitCards.size(); ++i){
        if(splitCards[i].getValue() == 11){

            splitAceCounter++;
            index.push_back(i);
        }
    }

    for (int i = 0; i < arraySize; ++i) {
        if(objects[i].getValue() == 11){
            aceCounter++;
            index.push_back(i);
        }
    }

    if (splitHitFlag == true && objects[0].getValue() == 1 ){
        objects[0].setValue(11);
        sum += 10;
    }


    if(splitHitFlag == true){
        for (int i = 0; i < splitAceCounter; ++i){
            if(splitSum > 21){
                objects[index[i]].setValue(1);
                splitCards[index[i]].setValue(1);
                splitSum -= 10;
            }
        }
    }
    else{
        for(int i = 0; i < aceCounter-splitAceCounter; ++i){
            if(sum > 21){
                objects[index[i]].setValue(1);
                sum -= 10;
            }
            else{
                break;
            }
        }
    }


}









