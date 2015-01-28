

#include "GameFlow.h"
#include <iostream>

bool checkReady(vector<int> playerbet,map<int,int> playerleft,int maxposition){
    bool check=true;
    if(maxposition!=-1){
        for(map<int,int>::iterator it=playerleft.begin();it!=playerleft.end();it++){
            if(playerbet[it->first]<playerbet[maxposition]&&it->second!=0){
                check=false;
                break;
            }
        }
    }
    return check;
}

void gameFlow(vector<PokerPlayer> &players,int SBposition, int &pot,bool ifpreflop,
              map<int,int> &playerleft,vector<int> &playerbet,bool &ifeveryAllin){
    int numofPlayer=players.size();
    bool readyForNextCard=false;  //if all active player call the same value, this will return true
    int curPosition=SBposition;  //track current player that is in action
    int MaxBetPosition=-1;    //max bet is the max bet from one single player in this round of bet
    int count=0;            //count how many players has taken action
    
    ////////////////////////////////////////////
    //if this is pre-flop,
    //small blind and big blind put $1 or $2
    ////////////////////////////////////////////
    if(ifpreflop){          
        //Small blind put 1
        playerbet[curPosition]=1;
        players[curPosition].chipAmount-=1;
        curPosition=(curPosition+1)%numofPlayer;
        //big blind put 2
        MaxBetPosition=curPosition;
        playerbet[curPosition]=2;
        players[curPosition].chipAmount-=2;
        curPosition=(curPosition+1)%numofPlayer;
        count+=1;  
        pot=3;
    }

    ////////////////////////////////////////////
    //find first active player for this round.
    ////////////////////////////////////////////
    bool firstfound=true;  //check if
    if(playerleft.find(curPosition)==playerleft.end()){
        firstfound=false;
    }else{
        if(playerleft[curPosition]==0){
            firstfound=false;
        }
    }
    while(!firstfound){
        curPosition=(curPosition+1)%numofPlayer;
        if(playerleft.find(curPosition)!=playerleft.end()){
            if(playerleft[curPosition]!=0){
                firstfound=true;
            }
        }
    }
    
    ////////////////////////////////////////////
    //start betting
    ////////////////////////////////////////////
    while(playerleft.size()>1&&(count<playerleft.size()||!readyForNextCard)){
        if(MaxBetPosition==-1||    //if no one has bet so far
           (ifpreflop&&curPosition==(SBposition+1)%numofPlayer&&playerbet[MaxBetPosition]==2)){  //or preflop big blind
            int decision;
            cout << endl << players[curPosition].name << ", please select: 1.Fold 2.Check 3.Bet/Raise 4.All-in ";
            cin >> decision;
            while(cin.fail()||(decision!=1&&decision!=2&&decision!=3&&decision!=4)){
                cout << "invalid input, try again: ";
                cin.clear();
                cin.ignore(1000,'\n');
                cin >> decision;
            }
            switch (decision) {
                case 1:
                    cout << players[curPosition].name << " fold, " << endl;
                    playerleft.erase(playerleft.find(curPosition));
                    break;
                case 2:
                    cout << players[curPosition].name << " check, " << endl;
                    break;
                case 3:
                    players[curPosition].Bet(MaxBetPosition,pot,playerbet,curPosition);
                    break;
                case 4:
                    players[curPosition].AllIn(MaxBetPosition,pot,playerbet,curPosition);
                    playerleft[curPosition]=0;
                    break;
                    
                default:
                    break;
            }
        }else if(players[curPosition].chipAmount<=(playerbet[MaxBetPosition]-playerbet[curPosition])){
            //if chip left less than max bet, only fold or all-in to call
            int decision;
            cout << endl << players[curPosition].name << ", please select 1.Fold 2.All-in: ";
            cin >> decision;
            while(cin.fail()||(decision!=1&&decision!=2)){
                cout << "invalid input, try again: ";
                cin.clear();
                cin.ignore(1000,'\n');
                cin >> decision;
            }
            switch (decision) {
                case 1:
                    cout << players[curPosition].name << " fold, " << endl;
                    playerleft.erase(playerleft.find(curPosition));
                    break;
                case 2:
                    players[curPosition].AllIn(MaxBetPosition,pot,playerbet,curPosition);
                    playerleft[curPosition]=0;
                    break;
                default:
                    break;
            }
        }else if(players[curPosition].chipAmount<=2*(playerbet[MaxBetPosition]-playerbet[curPosition])){
            //if chip left larget than max bet, but less than 2 times max bet, can't raise
            int decision;
            cout << endl << players[curPosition].name << ", please select 1.Fold 2.Call 3.All-in: ";
            cin >> decision;
            while(cin.fail()||(decision!=1&&decision!=2&&decision!=3)){
                cout << "invalid input, try again: ";
                cin.clear();
                cin.ignore(1000,'\n');
                cin >> decision;
            }
            switch (decision) {
                case 1:
                    cout << players[curPosition].name << " fold, " << endl;
                    playerleft.erase(playerleft.find(curPosition));
                    break;
                case 2:
                    players[curPosition].Call(MaxBetPosition,pot,playerbet,curPosition);
                    break;
                case 3:
                    players[curPosition].AllIn(MaxBetPosition,pot,playerbet,curPosition);
                    playerleft[curPosition]=0;
                    break;
                default:
                    break;
            }
        }else if(players[curPosition].chipAmount>2*(playerbet[MaxBetPosition]-playerbet[curPosition])){
            //if chip reamining larger than 2 times max bet, can take any action
            int decision;
            cout << endl << players[curPosition].name << ", please select 1.Fold 2.Call 3.Raise 4.All-in: ";
            cin >> decision;
            while(cin.fail()||(decision!=1&&decision!=2&&decision!=3&&decision!=4)){
                cout << "invalid input, try again: ";
                cin.clear();
                cin.ignore(1000,'\n');
                cin >> decision;
            }
            switch (decision) {
                case 1:
                    cout << players[curPosition].name << " fold, " << endl;
                    playerleft.erase(playerleft.find(curPosition));
                    break;
                case 2:
                    players[curPosition].Call(MaxBetPosition,pot,playerbet,curPosition);
                    break;
                case 3:
                    players[curPosition].Raise(MaxBetPosition,pot,playerbet,curPosition);
                    break;
                case 4:
                    players[curPosition].AllIn(MaxBetPosition,pot,playerbet,curPosition);
                    playerleft[curPosition]=0;
                    break;
                default:
                    break;
            }
        }
        
        //if one player left, he wins already
        //if there are more than one active playersdecide if all of them have all in
        //if all of them all in, compare their hand
        //otherwise, find next player that is able to take action
        if(playerleft.size()!=1){
            /////////////////////////////////////////
            //check if every active player all in
            /////////////////////////////////////////
            ifeveryAllin=true;
            for(map<int,int>::iterator it=playerleft.begin();it!=playerleft.end();it++){
                if(it->second!=0&&it->first!=MaxBetPosition){
                    ifeveryAllin=false;
                    break;
                }
            }
            if(ifeveryAllin){
                int secondmax=-1; //find second max bet, put the difference between max bet and second bet
                                  //back to the player who made max bet, no one can win that part of money.
                for(map<int,int>::iterator it=playerleft.begin();it!=playerleft.end();it++){
                    if(it->first!=MaxBetPosition&&playerbet[it->first]>secondmax){
                        secondmax=playerbet[it->first];
                    }
                }
                int moneyback=playerbet[MaxBetPosition]-secondmax;
                players[MaxBetPosition].chipAmount+=moneyback;
                pot-=moneyback;
                playerbet[MaxBetPosition]-=moneyback;
                cout << endl << "Every active player all-in, now pot is: " << pot << endl;
                break;
            }else{
                //if not every all in, find next active position
                bool nextfound=false;
                while(!nextfound){
                    curPosition=(curPosition+1)%numofPlayer;
                    if(playerleft.find(curPosition)!=playerleft.end()){
                        if(playerleft[curPosition]!=0){
                            nextfound=true;
                        }
                    }
                }
                count++;
                if(count>=playerleft.size()){
                    readyForNextCard=checkReady(playerbet,playerleft,MaxBetPosition);
                }
                //preflop big blind position is an exception,
                if(ifpreflop&&curPosition==(SBposition+1)%numofPlayer&&playerbet[MaxBetPosition]==2){
                    readyForNextCard=false;
                }
            }
        }
    }
}
