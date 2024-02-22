#include "Card.h"
#include <iostream>

using namespace std;

vector<string> Card::cards;

Card::Card() {
    cardRand();
}

Card::Card(int a){
    splitCardRand();
}

Card::Card(double a){
    splitHitCardRand();
}


string Card::translateType(int a){
    switch(a){
    case 1:
        return "c";


    case 2:
        return "d";

    case 3:
        return "h";

    case 4:
        return "s";


    default:
        return "unknown";
    }
}

int Card::getCard(){
    return name;
}

string Card::getCardType(){
    return symbolString;
}

int Card::getValue(){
    return value;
}

void Card::setValue(int a){
    value = a;
}


void Card::setName(int a){
    name = a;
}

void Card::setSymbol(int a){
    symbol = a;
}


void Card::cardRand(){
    name = (rand() % 13) + 2;
    symbol = (rand() % 4) + 1;
    symbolString = translateType(symbol);
    string check = symbolString + to_string(name);

    cardRep(&name, &symbol, &symbolString, &check);
    cards.push_back(check);

    if(name == 11 || name == 12 || name == 13){
        value = 10;
    }
    else if (name == 14){
        value = 11;
    }
    else{
        value = name;
    }

}


void Card::splitCardRand(){

    name = 8;
    symbol = 3;
    symbolString = translateType(symbol);
    string check = symbolString + to_string(name);
    cards.push_back(check);

    if(name == 11 || name == 12 || name == 13){
        value = 10;
    }
    else if (name == 14){
        value = 11;
    }
    else{
        value = name;
    }
}


void Card::splitHitCardRand(){
    name = 14;
    symbol = 3;
    symbolString = translateType(symbol);
    string check = symbolString + to_string(name);
    cards.push_back(check);

    if(name == 11 || name == 12 || name == 13){
        value = 10;
    }
    else if (name == 14){
        value = 11;
    }
    else{
        value = name;
    }
}

void Card::cardRep(int *name, int *symbol, string *symbolString, string *check){
    int maxAttempts = 100;
    int attempts = 0;

    for (size_t i = 0; i < cards.size(); ++i) {

        string tmp = *check;

        if(cards[i] == tmp){
            do {
                *name = (rand() % 13) + 2;
                *symbol = (rand() % 4) + 1;
                *symbolString = translateType(*symbol);
                *check = *symbolString + to_string(*name);


                auto it = find(cards.begin(), cards.end(), *check);

                if (it == cards.end()) {

                    break;
                }

                attempts++;
            } while (attempts < maxAttempts);

            break;
        }
    }


}



