//this file contain functions that are used to classify a hand from straight flush to high card

#ifndef PG_CalculateHand_h
#define PG_CalculateHand_h

#include "PokerPlayer.h"
#include <vector>
#include <map>


//Poker hands rankings
//1. Royal Flush
//2. Quads
//3. Full house
//4. Flush
//5. Straight
//4. Three of a kind
//5. Two pairs
//6. One pair
//7. High card

//this array is used to find straight or five high cards if straight doesn't exist
const char straight[14]={'A','K','Q','J','T','9','8','7','6','5','4','3','2','A'};

//return a character's position in array "straight"
int getposition(const char s[14],char key);

//operator overloading for sorting accoring to "straight"
bool compare_num(string s1,string s2);

//check if there is straight exist
//if yes, return these five numbers in array "fiveNumsInorder", and also in order
//if not, put five highest number in hash table "fiveNums"
void CheckStraight(vector<string> seven,map<char,int> numTrack,vector<char> &fiveNumsInOrder,map<char,int> &fiveNums);

bool CheckStraightFlush(vector<string> seven,char maxcolor,map<char,int> fiveNums);

//the following function input five cards on board and two card from one player, so total seven cards,
//output the best five cards
vector<string> Calculatehands(vector<string> CardOnBoard, PokerPlayer p);



#endif
