

#include "GenerateCards.h"


void shuffleCardDeck(vector<string> &deck){
    deck.clear();
    srand(time(NULL));
    for(int i=0;i<13;i++){
        for(int j=0;j<4;j++){
            string cur;
            cur.push_back(cardnumber[i]);
            cur.push_back(cardcolor[j]);
            deck.push_back(cur);
        }
    }
    for(int i=0;i<156;i++){
        int rn=rand()%52;
        if(rn!=i%52){
            string temp=deck[rn];
            deck[rn]=deck[i%52];
            deck[i%52]=temp;
        }
    }
}

void GetNewCards(vector<string> &deck,PokerPlayer &p){
    p.GetCards(deck[0][0], deck[0][1], deck[1][0], deck[1][1]);
    deck.erase(deck.begin(),deck.begin()+2);
}
