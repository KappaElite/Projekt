#include "Croupier.h"


Croupier::Croupier() {
    cardNumP = 0;
}

vector<Card>Croupier::getVector(){
    return objects;
}

int Croupier::getSum(){
    return sum;
}


string Croupier::cardCreator(){
    objects.push_back(Card());;
    int a = objects[cardNumP].getCard();
    int tmp = objects[cardNumP].getValue();
    string b = objects[cardNumP].getCardType();
    string path = b + to_string(a);
    path += ".png";
    sum+=tmp;

    aceChoice();
    cardNumP += 1;

    return path;
}

void Croupier::aceChoice(){
    int aceCounter = 0;
    vector<int> index;
    for (int i = 0; i < objects.size(); ++i) {
        if(objects[i].getValue() == 11){
            aceCounter++;
            index.push_back(i);
        }
    }


    for(int i = 0; i < aceCounter; ++i){
        if(sum > 21){
            objects[index[i]].setValue(1);
            sum -= 10;
        }
        else{
            break;
        }
    }
}





