
#include "DistributePot.h"
#include <iostream>

void printHandLevel(int l){
    switch (l) {
        case 1:
            cout << "(Straight Flush)";
            break;
        case 2:
            cout << "(Quads/Four of a kind)";
            break;
        case 3:
            cout << "(Full House)";
            break;
        case 4:
            cout << "(Flush)";
            break;
        case 5:
            cout << "(Straight)";
            break;
        case 6:
            cout << "(Three of a kind)";
            break;
        case 7:
            cout << "(Two Pairs)";
            break;
        case 8:
            cout << "(One Pair)";
            break;
        case 9:
            cout << "(High card)";
            break;
        default:
            break;
    }
}

int sumofbet(vector<int> playerbet){
    int result=0;
    for(int i=0;i<playerbet.size();i++){
        result+=playerbet[i];
    }
    return result;
}

void distributePot(map<int,int> playerleft, int &pot, vector<PokerPlayer> &players,vector<int> &playerbet,
                   vector<string> board,int &totalMoney){
    
    //for players left, put their position in an array
    vector<int> ranking;
    for(map<int,int>::iterator it=playerleft.begin();it!=playerleft.end();it++){
        ranking.push_back(it->first);
    }
    
    //sort the array, so that good hand goes to smaller index
    //if two hands tied, the player bet less money goes to smaller index
    for(int i=0;i<ranking.size();i++){
        for(int j=i+1;j<ranking.size();j++){
            if(compareTwo(board, players[ranking[i]], players[ranking[j]])==2){
                int temp=ranking[i];
                ranking[i]=ranking[j];
                ranking[j]=temp;
            }
        }
    }

    for(int i=0;i<ranking.size();i++){
        for(int j=i+1;j<ranking.size();j++){
            if(compareTwo(board, players[ranking[i]], players[ranking[j]])==0){
                if(playerbet[ranking[i]]>playerbet[ranking[j]]){
                    int temp=ranking[i];
                    ranking[i]=ranking[j];
                    ranking[j]=temp;
                }
            }
        }
    }
    
    //calculate max possible pot a player can win
    vector<int> possiblePot;
    for(int i=0;i<ranking.size();i++){
        int possible=0;
        for(int j=0;j<playerbet.size();j++){
            if(playerbet[j]<=playerbet[ranking[i]]){
                possible+=playerbet[j];
            }else{
                possible+=playerbet[ranking[i]];
            }
        }
        possiblePot.push_back(possible);
    }

    ///////////////////////////////////////////////////////
    //show down hands
    ///////////////////////////////////////////////////////
    cout << endl;
    cout << "*********************************************************" << endl << endl;
    cout << "                        Show Down                        " << endl << endl;
    cout << "*********************************************************" << endl;
    cout << "Cards on board:";
    displayCardonBoard(board, 5);
    for(map<int,int>::iterator it=playerleft.begin();it!=playerleft.end();it++){
        players[it->first].DisplyCards();
        cout << players[it->first].name << "'s hand made: ";
        vector<string> hands=Calculatehands(board, players[it->first]);
        for(int i=1;i<hands.size();i++){
            cout << hands[i] << ", ";
        }
        printHandLevel(hands[0][0]-'0');
        cout << endl << endl;
    }
    
    ///////////////////////////////////////////////////////
    //distribute the money
    ///////////////////////////////////////////////////////
    int cur=0;
    int track=0;
    cout <<endl<< "$$$$$$$$$$$$$$$$$$$$" << endl;
    while(sumofbet(playerbet)>0&&track<playerleft.size()){
            while(track<playerleft.size()-1&&compareTwo(board, players[ranking[cur]], players[ranking[track+1]])==0){
                track++;
            }
        
            for(int i=cur;i<=track;i++){
                //cout << playerbet[ranking[i]] << endl;
                int base=playerbet[ranking[i]];
                //cout << "Base : " << base << endl;
                for(int j=0;j<playerbet.size();j++){
                    if(j<ranking[cur]||j>ranking[track]){
                        int subtract=(playerbet[j]<=base?playerbet[j]:base)/(track-i+1);
                        //cout << "subtract" << subtract << endl;
                        for(int k=i;k<=track;k++){
                            playerbet[ranking[k]]+=subtract;
                            playerbet[j]-=subtract;
                        }
                    }
                }
            }
        
        for(int i=cur;i<=track;i++){
            players[ranking[i]].winMoney(playerbet[ranking[i]]);
            if(playerbet[ranking[i]]>0){
                cout << "--" << players[ranking[i]].name << "--" <<  " wins: $";
                cout << playerbet[ranking[i]] << endl;
            }
            playerbet[ranking[i]]=0;
        }
                
        cur=track;
        while(playerbet[ranking[cur]]==0&&cur<playerleft.size()-1){
            cur++;
        }
        track=cur;
    }
    cout << "$$$$$$$$$$$$$$$$$$$$" << endl;

    cout << endl << "Current round of game end. Chip count: " << endl;
    for(int i=0;i<players.size();i++){
        cout << players[i].name << ": $" <<players[i].chipAmount << endl;
    }
    
    ///////////////////////////////////////////////////////
    //Rebuy if any player lose all the money
    ///////////////////////////////////////////////////////
    for(int i=0;i<players.size();i++){
        if(players[i].chipAmount==0){
            players[i].rebuy(totalMoney);
        }
    }
}
