
#include "Display.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;


void startBanner(){
    cout << "*********************************************************" << endl;
    cout << " ##### ##### #   # ##### ####     $$$    $   $   $ $$$$$ " << endl;
    cout << " #   # #   # #  #  #     #   #   $      $ $  $$ $$ $     " << endl;
    cout << " ##### #   # ###   ##### ####    $ $$$ $$$$$ $$ $$ $$$$$ " << endl;
    cout << " #     #   # #  #  #     #  #    $   $ $   $ $ $ $ $     " << endl;
    cout << " #     ##### #   # ##### #   #    $$$  $   $ $ $ $ $$$$$ " << endl;
    cout << "*********************************************************" << endl << endl;
    cout << "                 Welcome to Poker Game !!                " << endl << endl;
    cout << "*********************************************************" << endl << endl;
}


void gameNotes(){
    
    cout << "Game Regulations: " << endl;
    cout << "1. Following $1/$2 unlimit Texas Holdem game rules." << endl;
    cout << "2. In this game, card suite are displayed in letters:" << endl;
    cout << "   * h = Heart " << endl;
    cout << "   * s = Spade " << endl;
    cout << "   * c = Club " << endl;
    cout << "   * d = Diamond " << endl;
    cout << "3. Card numbers(except number ten) are displayed in numbers, for others:" << endl;
    cout << "   * A = Ace " << endl;
    cout << "   * K = King " << endl;
    cout << "   * Q = Queen " << endl;
    cout << "   * J = Jack " << endl;
    cout << "   * T = Number Ten " << endl << endl;
    cout << "For example: Th = Ten of heart, Ks = King of spade. " << endl << endl;
    cout << "*********************************************************" << endl << endl;
    cout << "                     Setting and Input                   " << endl << endl;
    cout << "*********************************************************" << endl << endl;
}

void dealerPostionDiaplay(vector<PokerPlayer> players,int round){
    int numofPlayer=players.size();
    cout << "*********************************************************" << endl << endl;
    cout << "Dealer and small blind position for this round: " << endl << endl;
    cout << "*********************************************************" << endl << endl;
    for(int i=0;i<numofPlayer;i++){
        players[i].DisplyName();
        if(i==(round+numofPlayer-1)%numofPlayer){
            cout << "(Dealer)";
        }else if(i==(round+numofPlayer)%numofPlayer){
            cout << "(Small Blind)";
        }
        cout << " --> ";
    }
    players[0].DisplyName();
    if(0==(round+numofPlayer-1)%numofPlayer){
        cout << "(Dealer)" << endl;
    }else if(0==(round+numofPlayer)%numofPlayer){
        cout << "(Small Blind)" << endl;
    }
}

void displayCardonBoard(vector<string> c,int stage){
    switch (stage) {
        case 3:
            cout << endl << endl;
            cout << "          Flop      " << endl;
            cout << "   ---    ---    ---  " << endl;
            cout << "  | "<<c[0][0]<<" |  | "<<c[1][0]<<" |  | "<<c[2][0]<<" | " << endl;
            cout << "  | "<<c[0][1]<<" |  | "<<c[1][1]<<" |  | "<<c[2][1]<<" | " << endl;
            cout << "   ---    ---    ---  " << endl << endl;
            break;

        case 4:
            cout << endl << endl;
            cout << "          Flop           Turn   " << endl;
            cout << "   ---    ---    ---      ---   " << endl;
            cout << "  | "<<c[0][0]<<" |  | "<<c[1][0]<<" |  | "<<c[2][0]<<" |    | "<<c[3][0]<<" |  " << endl;
            cout << "  | "<<c[0][1]<<" |  | "<<c[1][1]<<" |  | "<<c[2][1]<<" |    | "<<c[3][1]<<" |  " << endl;
            cout << "   ---    ---    ---      ---   " << endl << endl;
            break;

        case 5:
            cout << endl << endl;
cout << "          Flop           Turn    River " << endl;
cout << "   ---    ---    ---      ---     ---   " << endl;
cout << "  | "<<c[0][0]<<" |  | "<<c[1][0]<<" |  | "<<c[2][0]<<" |    | "<<c[3][0]<<" |   | "<<c[4][0]<<" |  " << endl;
cout << "  | "<<c[0][1]<<" |  | "<<c[1][1]<<" |  | "<<c[2][1]<<" |    | "<<c[3][1]<<" |   | "<<c[4][1]<<" |  " << endl;
cout << "   ---    ---    ---      ---     ---   " << endl << endl;
            break;
            
        default:
            break;
    }
}
