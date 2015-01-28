
#include "PokerPlayer.h"
#include "GenerateCards.h"
#include "CalculateHand.h"
#include "CompareTwo.h"
#include "GameFlow.h"
#include "DistributePot.h"
#include "Display.h"
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>

using namespace std;

int main()
{
    startBanner();
    gameNotes();
    
    //Define a deck of card as an array of string
    vector<string> CardDeck;
    for(int i=0;i<13;i++){
        for(int j=0;j<4;j++){
            string temp;
            temp.push_back(cardnumber[i]);
            temp.push_back(cardcolor[j]);
            CardDeck.push_back(temp);
        }
    }
    
    //shuffle the card
    shuffleCardDeck(CardDeck);
    
    /////////////////////////////////////////////////////////////////////
    //define players
    /////////////////////////////////////////////////////////////////////
    int numofPlayer;
    int totalMoney=0;
    cout << "-- Enter number of players-- (number of players limited from 2 to 10): ";
    cin >> numofPlayer;
    while(cin.fail()||numofPlayer<2||numofPlayer>10){
        cout << "invalid input, try again: ";
        cin.clear();
        cin.ignore(1000,'\n');
        cin >> numofPlayer;
    }
    cout << endl << "--" << numofPlayer << "-- players on board." << endl << endl;
    /*while(numofPlayer<2||numofPlayer>10){
        cout << "invalid input, number of player set to 2 by default" << endl;
        numofPlayer=2;
        cin.clear();
        cin>>numofPlayer;
    }*/
    vector<PokerPlayer> playerArray;
    cout << "-- Input each player's name and starting chip amount-- " << endl;
    for(int i=0;i<numofPlayer;i++){
        string tempname;
        int tempchip;
        cout << "Player " << i+1 << "'s name: ";
        cin >> tempname;
        cout << "Player " << i+1 << "'s buy-in: $";
        cin >> tempchip;
        while(cin.fail()){
            cout << "invalid input, try again: $";
            cin.clear();
            cin.ignore(1000,'\n');
            cin >> tempchip;
        }
        PokerPlayer pp(tempname,tempchip);
        playerArray.push_back(pp);
        totalMoney+=tempchip;
    }
    cout << endl;
    cout << "*********************************************************" << endl << endl;
    cout << "               Input finished, Game Start!               " << endl << endl;
    cout << "*********************************************************" << endl << endl;
    //players define finished
    
    char continueGame='Y';
    int round=0;  //dealer position will be defined as (round+numberofPlayer-1)%numberofPlayer
    
    while(continueGame!='Q'&&continueGame!='q'){
        
    /////////////////////////////////////////////////////////////////////
    //Deal cards, define position, define necessary element and array
    /////////////////////////////////////////////////////////////////////
        //print round divider
        cout << endl;
        for(int i=0;i<20;i++){
            cout << "-";
        }
        cout << "Round " << round+1;
        for(int i=0;i<20;i++){
            cout << "-";
        }
        cout << endl << endl;
        
        /////////////////////////////
        //shufflecard and deal cards
        shuffleCardDeck(CardDeck);
        for(int i=round;i<round+numofPlayer;i++){
            playerArray[i%numofPlayer].GetCards(CardDeck[i-round], CardDeck[i-round+numofPlayer]);
        }
        
        
        //remove dealed card from card deck
        CardDeck.erase(CardDeck.begin(),CardDeck.begin()+numofPlayer*2);
 
        /////////////////////////////
        //Print Cards for each player
        /////////////////////////////
        cin.get();
        for(int i=0;i<numofPlayer;i++){
            cout << "When ready, press Enter to show -- ";
            playerArray[i].DisplyName();
            cout << "--'s card. ";
            cin.get();
            for(int j=0;j<50;j++){
                cout << endl;
            }
            cout << "---------------------------" << endl;
            playerArray[i].DisplyCards();
            cout << "---------------------------" << endl;
            cout << "When finished, press Enter to confirm. ";
            cin.get();
            for(int j=0;j<50;j++){
                cout << endl;
            }
        }
        
        
        /////////////////////////////
        //show position for each player
        /////////////////////////////
        
        dealerPostionDiaplay(playerArray, round);
        
        
    //////////////////////////////////////////////////////////////////////////////
    //define amount of money each player has put on table, set 0 for all at beginning
    //intialize player left hash table
    //define array to store card on board
    //////////////////////////////////////////////////////////////////////////////
        vector<int> eachplayerBet(numofPlayer,0);
        map<int,int> playerleft; //store all player's position
        for(int i=0;i<numofPlayer;i++){
            playerleft[i]++;
        }
        int pot=0;
        bool ifeveryAllin=false;
        vector<string> board;
        
        //create board
        //CardDeck[0],CardDeck[4],CardDeck[6] are burned cards
        board.push_back(CardDeck[1]); //flop
        board.push_back(CardDeck[2]); //flop
        board.push_back(CardDeck[3]); //flop
        board.push_back(CardDeck[5]); //turn
        board.push_back(CardDeck[7]); //river
        /*board.push_back("As"); //flop
        board.push_back("Ks"); //flop
        board.push_back("Qs"); //flop
        board.push_back("Js"); //turn
        board.push_back("Ts"); //river*/

        cout << endl << "Preflop bet start, small blind $1, big blind $2: " << endl << endl;
    /////////////////////////////////////////////////////////////////////
    //Round start
    //preflop bet
    /////////////////////////////////////////////////////////////////////
        gameFlow(playerArray, round, pot, true, playerleft, eachplayerBet,ifeveryAllin);
        
        if(playerleft.size()>1&&ifeveryAllin){
            distributePot(playerleft, pot, playerArray, eachplayerBet, board, totalMoney);
        }else if(playerleft.size()==1){ //if only one player left, he wins, otherwise keep going
            playerArray[playerleft.begin()->first].winMoney(pot);
            cout << endl;
            playerArray[playerleft.begin()->first].DisplyName();
            cout << "$$$$$$$$$$$$$$$$$$$$" << endl;
            cout << "wins $" << pot << endl;
            cout << "$$$$$$$$$$$$$$$$$$$$" << endl << endl;
            cout << endl << "Current round of game end. Chip count: " << endl;
            for(int i=0;i<playerArray.size();i++){
                playerArray[i].DisplyMoneyLeft();
            }
        }else{
            //deal flop, three cards
            cout << endl << "***************** Flop ********************" ;
            cout << endl << "Cards on board: ";
            displayCardonBoard(board, 3);
            cout << "Pot: $" << pot << endl <<endl;
            cout << "Players Stack Size: " << endl;
            for(map<int,int>::iterator it=playerleft.begin();it!=playerleft.end();it++){
                playerArray[it->first].DisplyMoneyLeft();
            }
            cout << "***************** Flop ********************" << endl ;
            /////////////////////////////////////////////////////////////////////
            //flop bet
            /////////////////////////////////////////////////////////////////////
            gameFlow(playerArray, round, pot, false, playerleft, eachplayerBet,ifeveryAllin);
            
            if(playerleft.size()>1&&ifeveryAllin){
                distributePot(playerleft, pot, playerArray, eachplayerBet, board, totalMoney);
            }else if(playerleft.size()==1){
                playerArray[playerleft.begin()->first].winMoney(pot);
                cout << endl;
                playerArray[playerleft.begin()->first].DisplyName();
                cout << "$$$$$$$$$$$$$$$$$$$$" << endl;
                cout << "wins $" << pot << endl;
                cout << "$$$$$$$$$$$$$$$$$$$$" << endl << endl;
                cout << endl << "Current round of game end. Chip count: " << endl;
                for(int i=0;i<playerArray.size();i++){
                    playerArray[i].DisplyMoneyLeft();
                }
            }else{
                //deal turn card
                cout << endl << "***************** Turn ********************" ;
                cout << endl << "Cards on board: ";
                displayCardonBoard(board, 4);
                cout << "Pot: $" << pot << endl << endl;
                cout << "Players Stack Size: " << endl;
                for(map<int,int>::iterator it=playerleft.begin();it!=playerleft.end();it++){
                    playerArray[it->first].DisplyMoneyLeft();
                }
                cout << "***************** Turn ********************" << endl ;
                /////////////////////////////////////////////////////////////////////
                //turn bet
                /////////////////////////////////////////////////////////////////////
                gameFlow(playerArray, round, pot, false, playerleft, eachplayerBet,ifeveryAllin);
                
                if(playerleft.size()>1&&ifeveryAllin){
                    distributePot(playerleft, pot, playerArray, eachplayerBet, board, totalMoney);
                }else if(playerleft.size()==1){
                    playerArray[playerleft.begin()->first].winMoney(pot);
                    cout << endl;
                    playerArray[playerleft.begin()->first].DisplyName();
                    cout << "$$$$$$$$$$$$$$$$$$$$" << endl;
                    cout << "wins $" << pot << endl;
                    cout << "$$$$$$$$$$$$$$$$$$$$" << endl << endl;
                    cout << endl << "Current round of game end. Chip count: " << endl;
                    for(int i=0;i<playerArray.size();i++){
                        playerArray[i].DisplyMoneyLeft();
                    }
                }else{
                    //deal river card
                    cout << endl << "***************** River ********************" ;
                    cout << endl << "Cards on board: ";
                    displayCardonBoard(board, 5);
                    cout << "Pot: $" << pot << endl <<endl;
                    cout << "Players Stack Sizen: " << endl;
                    for(map<int,int>::iterator it=playerleft.begin();it!=playerleft.end();it++){
                        playerArray[it->first].DisplyMoneyLeft();
                    }
                    cout << "***************** River ********************" << endl ;
                    /////////////////////////////////////////////////////////////////////
                    //river bet
                    /////////////////////////////////////////////////////////////////////
                    gameFlow(playerArray, round, pot, false, playerleft, eachplayerBet,ifeveryAllin);
                    
                    if(playerleft.size()==1){
                        playerArray[playerleft.begin()->first].winMoney(pot);
                        cout << endl;
                        playerArray[playerleft.begin()->first].DisplyName();
                        cout << "wins $" << pot << endl;
                        cout << endl << "Current round of game end. Chip count: " << endl;
                        for(int i=0;i<playerArray.size();i++){
                            playerArray[i].DisplyMoneyLeft();
                        }
                    }else{
                        distributePot(playerleft, pot, playerArray, eachplayerBet, board, totalMoney);
                    }
                }
            }
        }
        
        round++;
        cout << endl << "Press 'Q' to quit, any other key to keep playing, ";
        cin >>continueGame;
    }
    
    cout << endl << "Good Luck! See you.";
    
    return 0;
}

