

#include "PokerPlayer.h"
#include <iostream>

PokerPlayer::PokerPlayer(){
    num1='N';
    color1='A';
    num2='N';
    color2='A';
    cout << "Enter your name: ";
    cin >> name;
    cout << "How much to buy in? $";
    cin >> chipAmount;
}

PokerPlayer::PokerPlayer(string n,int c){
    num1='N';
    color1='A';
    num2='N';
    color2='A';
    name=n;
    chipAmount=c;
}

void PokerPlayer::DisplyName(){
    cout << name << " ";
}

void PokerPlayer::DisplyCards(){
    cout << name << "'s cards: "<< endl;
    cout << "   ---    ---   " << endl;
    cout << "  | "<<num1<<" |  | "<<num2<<" | " << endl;
    cout << "  | "<<color1<<" |  | "<<color2<<" | " << endl;
    cout << "   ---    ---   " << endl;
}

void PokerPlayer::DisplyMoneyLeft(){
    cout << name << ": $" << chipAmount << endl;
}

void PokerPlayer::GetCards(char n1,char c1,char n2, char c2){
    num1=n1;
    color1=c1;
    num2=n2;
    color2=c2;
}

void PokerPlayer::GetCards(string c1,string c2){
    num1=c1[0];
    color1=c1[1];
    num2=c2[0];
    color2=c2[1];
}

void PokerPlayer::winMoney(int win){
    chipAmount+=win;
}

void PokerPlayer::payMoney(int pay){
    chipAmount-=pay;
}

void PokerPlayer::Bet(int &maxbetPosition,int &currentpot,vector<int> &playerbet,int position){
    int betAmount;
    cout << "Bet how much: $";
    cin >> betAmount;
    while(betAmount<2||betAmount>chipAmount){
        cout << "Invalid, input again: $";
        cin >> betAmount;
    }
    currentpot+=betAmount;
    playerbet[position]+=betAmount;
    chipAmount-=betAmount;
    maxbetPosition=position;
    cout << name << " bet: $" << betAmount << ", stack left: $" << chipAmount;
    cout << ", pot size now: $" << currentpot << endl;
}

void PokerPlayer::Call(int &maxbetPosition,int &currentpot,vector<int> &playerbet,int position){
    int tocall=playerbet[maxbetPosition]-playerbet[position];
    currentpot+=tocall;
    playerbet[position]+=tocall;
    chipAmount-=tocall;
    maxbetPosition=position;
    cout << name << " call: $" << tocall << ", stack left: $" << chipAmount;
    cout << ", pot size now: $" << currentpot << endl;
}

void PokerPlayer::Raise(int &maxbetPosition,int &currentpot,vector<int> &playerbet,int position){
    int RaiseAmount;
    cout << "Raise to: $";
    cin >> RaiseAmount;
    while(RaiseAmount<2*(playerbet[maxbetPosition]-playerbet[position])||RaiseAmount>chipAmount){
        cout << "Invalid, input again: $";
        cin >> RaiseAmount;
    }
    currentpot+=RaiseAmount;
    playerbet[position]+=RaiseAmount;
    chipAmount-=RaiseAmount;
    maxbetPosition=position;
    cout << name << " Raise: $" << RaiseAmount << ", stack left: $" << chipAmount;
    cout << ", pot size now: $" << currentpot << endl;
}

void PokerPlayer::AllIn(int &maxbetPosition,int &currentpot,vector<int> &playerbet,int position){
    currentpot+=chipAmount;
    playerbet[position]+=chipAmount;
    if(maxbetPosition==-1||playerbet[position]>playerbet[maxbetPosition]){
        maxbetPosition=position;
        cout << name << " All in: $" << chipAmount;
        cout << ", pot size now: $" << currentpot << endl;
    }else{
        cout << name << " All in: $" << chipAmount << ", pot size now: $" << currentpot ;
        cout << ", potantial side pot: $" << playerbet[maxbetPosition]-playerbet[position] << endl;
    }
    chipAmount=0;
}

void PokerPlayer::rebuy(int &totalmoney){
    cout << endl << name << " busted, rebuy: $";
    cin >> chipAmount;
    cout << name << " reloaded $" << chipAmount << endl;
    totalmoney+=chipAmount;
}
