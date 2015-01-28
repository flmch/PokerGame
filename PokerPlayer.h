//define poker player in a class
//the class contain variables of cards, chip amount, and the player's name
//the action this poket can take include:
//bet,call, raise,allin, rebuy when busted,
//And it can obtain new cards, display card and how much he left etc.

#ifndef PG_PokerPlayer_h
#define PG_PokerPlayer_h

#include <string>
#include <vector>
#include <map>
using namespace std;

class PokerPlayer{
private:
    string name;
    char num1,num2,color1,color2;
    int chipAmount;
public:
    PokerPlayer();
    PokerPlayer(string name,int chip);
    PokerPlayer(char num1,char color1,char num2, char color2); //contructor, initialize cards
    void DisplyName();  // display name
    void DisplyCards();  // display the current card
    void DisplyMoneyLeft();  // display money left
    void GetCards(char n1,char c1,char n2, char c2);  //Get new cards
    void GetCards(string c1,string c2);  //Get new cards
    void winMoney(int win);  //get all the money win
    void payMoney(int pay);  //pay some money
    void Bet(int &currenthighestbet,int &currentpot,vector<int> &playerbet,int position); //bet function
    void Call(int &currenthighestbet,int &currentpot,vector<int> &playerbet,int position); //call function
    void Raise(int &currenthighestbet,int &currentpot,vector<int> &playerbet,int position); //raise function
    void AllIn(int &currenthighestbet,int &currentpot,vector<int> &playerbet,int position); //all in
    void rebuy(int &totalmoney);
    friend vector<string> Calculatehands(vector<string> CardOnBoard, PokerPlayer p);
    friend void gameFlow(vector<PokerPlayer> &players,int SBposition, int &pot,bool ifpreflop,
                         map<int,int> &playerleft,vector<int> &playerbet,bool &ifeveryAllin);
    friend void distributePot(map<int,int> playerleft, int &pot, vector<PokerPlayer> &players,vector<int> &playerbet,
                              vector<string> board,int &totalMoney);
};


#endif
