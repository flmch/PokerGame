
#include "CalculateHand.h"

int getposition(const char s[],char key){
    for(int i=0;i<14;i++){
        if(key==s[i]){
            return i;
        }
    }
    return -1;
}

bool compare_num(string s1,string s2){
    return getposition(straight, s1[0])<getposition(straight, s2[0]);
}

void CheckStraight(vector<string> seven,map<char,int> numTrack,vector<char> &fiveNumsInOrder,map<char,int> &fiveNums){
    for(int i=0;i<4;i++){
        bool flag=true;
        int base=getposition(straight, seven[i][0]);
        fiveNums[seven[i][0]]++;
        fiveNumsInOrder.push_back(seven[i][0]);
        for(int j=1;j<=4;j++){
            if(numTrack.find(straight[base+j])==numTrack.end()){
                flag=false;
            }else{
                fiveNums[straight[base+j]]++;
                fiveNumsInOrder.push_back(straight[base+j]);
            }
        }
        if(flag){
            break;
        }else{
            fiveNums.clear();
            fiveNumsInOrder.clear();
        }
    }
}

bool CheckStraightFlush(vector<string> seven,char maxcolor,map<char,int> fiveNums){
    int count=0;
    for(int i=0;i<7;i++){
        if(fiveNums.find(seven[i][0])==fiveNums.end()||
            seven[i][1]!=maxcolor){
                count++;
        }
    }
    return count>2?false:true;
}

vector<string> Calculatehands(vector<string> CardOnBoard, PokerPlayer p){
    vector<string> allsevencards; //put all seven cards in an array
    vector<string> result;   //five best cards out of seven to be used, in order
    vector<char> fiveNumsInorder;  //track the best five numbers
    string card1,card2;
    map<char,int> fiveNums;  //track the best five numbers, for search purpose. not in order,
                             //can be used to check if straight exist
    map<char,int> numTrack;  //store nums and the frequent they occur
    map<char,int> colorTrack;  //store color and the frequent they occur
    char MaxNum='0';    //the number occurs most of the time
    int NumCount=0;     //count how many times the most popular number occur
    char MaxColor='0';  //the color occurs most of time time
    int ColorCount=0;  //count how many times the most popular color occur
    
    //put seven cards in one array first
    allsevencards.assign(CardOnBoard.begin(),CardOnBoard.end());
    card1.push_back(p.num1);
    card1.push_back(p.color1);
    card2.push_back(p.num2);
    card2.push_back(p.color2);
    allsevencards.push_back(card1);
    allsevencards.push_back(card2);
    
    //sort seven cards
    sort(allsevencards.begin(),allsevencards.end(),compare_num);

    //store number and color seperately
    for(int i=0;i<allsevencards.size();i++){
        numTrack[allsevencards[i][0]]++;
        colorTrack[allsevencards[i][1]]++;
        if(numTrack[allsevencards[i][0]]>NumCount){
            NumCount=numTrack[allsevencards[i][0]];
            MaxNum=allsevencards[i][0];
        }
        if(colorTrack[allsevencards[i][1]]>ColorCount){
            ColorCount=colorTrack[allsevencards[i][1]];
            MaxColor=allsevencards[i][1];
        }
    }
    
    //Find if straight exist,
    
    CheckStraight(allsevencards,numTrack,fiveNumsInorder,fiveNums);
    bool findstraightflush=fiveNums.empty()?false:CheckStraightFlush(allsevencards, MaxColor, fiveNums);

    //check card level by level
    //for array "result", first element is the level, second to sixth number are cards.
    if(findstraightflush){   //check striaght flush
        result.clear();
        result.push_back("1");
        string temp;
        for(int i=0;i<fiveNumsInorder.size();i++){
            temp.push_back(fiveNumsInorder[i]);
            temp.push_back(MaxColor);
            result.push_back(temp);
            temp.clear();
        }
        for(int i=0;i<7;i++){
            if((fiveNums.find(allsevencards[i][0])==fiveNums.end()||
               allsevencards[i][1]!=MaxColor)&&
               result.size()<6){
                result.push_back(allsevencards[i]);
                break;
            }
        }
    }else if(NumCount==4){   //check quads
        result.clear();
        result.push_back("2");
        for(int i=0;i<7;i++){
            if(allsevencards[i][0]==MaxNum){
                result.push_back(allsevencards[i]);
            }
        }
        for(int i=0;i<7;i++){
            if(allsevencards[i][0]!=MaxNum){
                result.push_back(allsevencards[i]);
                break;
            }
        }
    }else if(NumCount==3&&numTrack.size()<5){  //check full house
        result.clear();
        result.push_back("3");
        char three;
        for(int i=0;i<7;i++){
            if(numTrack[allsevencards[i][0]]==3&&result.size()<4){
                result.push_back(allsevencards[i]);
                three=allsevencards[i][0];
            }
        }
        for(int i=0;i<7;i++){
            if(numTrack[allsevencards[i][0]]>=2&&
               allsevencards[i][0]!=three&&
               result.size()<6){
                result.push_back(allsevencards[i]);
            }
        }
    }else if(ColorCount>=5){  //check flush
        result.clear();
        result.push_back("4");
        for(int i=0;i<7;i++){
            if(allsevencards[i][1]==MaxColor&&result.size()<6){
                result.push_back(allsevencards[i]);
            }
        }
    }else if(!fiveNumsInorder.empty()){ //check straight
        result.clear();
        result.push_back("5");
        int track=0;
        for(int i=0;i<10;i++){
            if(allsevencards[i%7][0]==fiveNumsInorder[track]&&result.size()<6){
                result.push_back(allsevencards[i%7]);
                track++;
            }
        }
    }else if(NumCount==3&&numTrack.size()==5){  //check three of a kind
        result.clear();
        result.push_back("6");
        for(int i=0;i<7;i++){
            if(allsevencards[i][0]==MaxNum){
                result.push_back(allsevencards[i]);
            }
        }
        for(int i=0;i<7;i++){
            if(allsevencards[i][0]!=MaxNum&&result.size()<6){
                result.push_back(allsevencards[i]);
            }
        }
    }else if(NumCount==2&&numTrack.size()==5){  //check two pairs
        result.clear();
        result.push_back("7");
        for(int i=0;i<7;i++){
            if(numTrack[allsevencards[i][0]]==2&&result.size()<5){
                result.push_back(allsevencards[i]);
            }
        }
        for(int i=0;i<7;i++){
            if(numTrack[allsevencards[i][0]]!=2&&result.size()<6){
                result.push_back(allsevencards[i]);
            }
        }
    }else if(NumCount==2&&numTrack.size()==6){  //check one pair
        result.clear();
        result.push_back("8");
        for(int i=0;i<7;i++){
            if(numTrack[allsevencards[i][0]]==2&&result.size()<3){
                result.push_back(allsevencards[i]);
            }
        }
        for(int i=0;i<7;i++){
            if(numTrack[allsevencards[i][0]]!=2&&result.size()<6){
                result.push_back(allsevencards[i]);
            }
        }
    }else{ //high cards
        result.clear();
        result.assign(allsevencards.begin(), allsevencards.begin()+5);
        result.insert(result.begin(), "9");
    }
    
    
    
    return result;
}
