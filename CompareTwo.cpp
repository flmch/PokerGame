
#include "CompareTwo.h"

int compareTwo(vector<string> board, PokerPlayer p1, PokerPlayer p2){
    vector<string> cp1=Calculatehands(board, p1);
    vector<string> cp2=Calculatehands(board, p2);
    

    if((int)cp1[0][0]<(int)cp2[0][0]){
        return 1;
    }else if((int)cp1[0][0]>(int)cp2[0][0]){
        return 2;
    }else{
        for(int i=1;i<=5;i++){
            if(getposition(straight, cp1[i][0])<getposition(straight, cp2[i][0])){
                return 1;
            }else if(getposition(straight, cp1[i][0])>getposition(straight, cp2[i][0])){
                return 2;
            }
        }
        return 0;
    }
}
