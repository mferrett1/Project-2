/* 
 * File:   main.cpp
 * Author:  Malachi Ferrett
 * Created on:  May 20, 2023 3:17 PM
 * Purpose:  Project 2 Play Blackjack  Backup
 */
//System Libraries
#include <iostream>  //Input/Output
#include <fstream>  //File Input/output
#include <vector>   //Vector
#include <iomanip>  //Format
#include <cstdlib>  //Random Functions
#include <ctime>    //Time Library
#include <cmath>    //Math Library 
#include <string>   //String
using namespace std;

//Global Constants, no Global Variables are allowed
//Math/Physics/Conversions/Higher Dimensions - i.e. PI, e, etc.
const int NCARDS = 15;
const int TCARDS = 52;
// Assuming max hand size is 11 (smallest value for blackjack is 2, so you can have 11 cards max)
const int maxHand = 11;

//Function Prototypes
char detSuit(int);
char detFace(int);
int detCV(char,char);
void wrtFile(ofstream& ,int,int,char,char);
void rdFile(const string &,vector<int> &, vector<char> &, vector<char> &);
void bblSrt(int [],char [],char [],int);
void selSort(int [],char [], char [],int);
int plyGm(char [],char [],int);
bool plyAgn();
void dlCard(char &,char &, char [], char [], int &);
int calcHV(char [],int);
void dispSel(char [],char [],int);  //Display 1 Dimension
void dispSel(const char [][2], int);  //Display 2 Dimensions
bool bSrch(int [],int,int,int &);

//Execution Begins Here!
int main() {
    //Initialize Random Seed once here!
    srand(static_cast<unsigned int>(time(0)));
   
      //Declare Variables/Arrays/Vectors
        //Use of parallel arrays 
        vector<int> cNums;
        vector<char> cFaces;
        vector<char> cSuits;
        
        
         int selCN[NCARDS];
        char selCF[NCARDS];
        char selCS[NCARDS];
        
    ofstream out;
    out.open("cards.dat", ios::out);
// Creates a file with 52 playing cards
// with an assigned value, number, face, and suit
    for (int card = 0; card < TCARDS; card++) {
        char suit = detSuit(card);
        char face = detFace(card);
        int cardnum = card + 1;
        int cardval = detCV(face, suit);
        wrtFile(out, cardval, cardnum, face, suit); //passing by value
    }
    out.close();
   
     bool play = true;
     cout<<"Welcome to Blackjack - A standard deck of cards consists of 52 cards with 4 suits: Spades (S), Hearts (H), "
            <<"Diamonds (D), and Clubs (C). Each suit has 13 cards:  Ace,  2,  3, 4,  5, 6, 7, 8, 9, 10(T),   Jack, Queen, "
            <<"and King.  Cards 2 through 10 are worth their face value, and face cards Jack (J), Queen (Q), and King (K) "
            <<"are also worth 10. The hand with the highest total wins as long as it doesn't exceed 21; a hand with a "
            <<"higher total than 21 is said to bust.  The goal of each player is to beat the dealer by having the "
            <<"higher, unbusted hand. Hit: Take another card. Stand: Take   no  more cards.\n";
        cout << "Do you want to play Blackjack?(y/n)"<<endl;
        string response;
            
        cin >> response;
        if(response=="n"){
            exit(0);
        }
       
   while(play){
       vector<bool> selected(52,false);
        
     
       
        //Initialize or input i.e. set variable values
        rdFile("cards.dat",cNums,cFaces,cSuits);
        
        for (int i = 0; i < NCARDS; i++) {
          
            int randIdx = rand() % 52;
        
            if(selected[randIdx]==false){
                selCN[i] = cNums[randIdx];
                selCF[i] = cFaces[randIdx];
                selCS[i] = cSuits[randIdx];
                selected[randIdx] = true;
            }else{
                i--;
            }
        }

        // Bubble sort the selected cards
        if(rand()%2==0){
            bblSrt(selCN, selCF, selCS, NCARDS);
        } else{
            selSort(selCN, selCF, selCS, NCARDS);
                
        }

        float numGm = abs(0.0);
    
        numGm = plyGm(selCF, selCS, NCARDS);
        cout << "Total number of games played is: " << setw(2)<<numGm << endl;
        play = plyAgn();
    }
 //Exit stage right or left!
    return 0;
}
//Function Definitions
char detSuit(int card=0) {
    char suit;
    switch (card / 13) {
        case 0:
            suit = 'S';
            break;
        case 1: 
            suit = 'D';
            break;
        case 2: 
            suit = 'C';
            break;
        default: 
            suit = 'H';
    }
    return suit;
}
char detFace(int card=0) {
    char cmod = card % 13;
    return cmod == 0 ? 'A' : cmod == 1 ? '2'
                     : cmod == 2   ? '3'
                     : cmod == 3   ? '4'
                     : cmod == 4   ? '5'
                     : cmod == 5   ? '6'
                     : cmod == 6   ? '7'
                     : cmod == 7   ? '8'
                     : cmod == 8   ? '9'
                     : cmod == 9   ? 'T'
                     : cmod == 10  ? 'J'
                     : cmod == 11  ? 'Q'
                                   : 'K';
}
int detCV(char face, char suit) {
    int val;

    if (face == 'A'){
        val = 1;
    }else if (face == '2'){
        val = 2;
    }else if (face == '3'){
        val = 3;
    }else if (face == '4'){
        val = 4;
    }
    else if (face == '5'){
        val = 5;
    }else if (face == '6'){
        val = 6;
    }else if (face == '7'){
        val = 7;
    }
    else if (face == '8'){
        val = 8;
    }
    else if (face == '9'){
        val = 9;
    }
    else if (face == 'T'){
        val = 10;
    }
    else if (face == 'J'){
        val = 10;
    }
    else if (face == 'Q'){
        val = 10;
    }
    else if (face == 'K'){
        val = 10;
    }
    else {
        val = 0;
    }
    return val;
}
void wrtFile(ofstream& out, int cardval, int cardnum, char face, char suit) {
    out << setw(3) << cardval << " " << cardnum << " " << face << " " << suit << endl;
}
void rdFile(const string &filename, vector<int> &cNums, vector<char> &cFaces, vector<char> &cSuits) {
    ifstream in(filename);

    if (in.is_open()) {
        int cardVal, cardNum;
        char crdFc, crdSt;

        while (in >> cardVal >> cardNum >> crdFc >> crdSt) {
            cNums.push_back(cardNum);
            cFaces.push_back(crdFc);
            cSuits.push_back(crdSt);
        }

        in.close();
    } else {
        cout << "Unable to open file";
    }
}
void bblSrt(int arr[], char face[], char suit[], int n=1) {
    int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // swap arr[j] and arr[j + 1]
                swap(arr[j], arr[j + 1]);

                // swap corresponding faces and suits
                swap(face[j], face[j + 1]);
                swap(suit[j], suit[j + 1]);
            }
        }
    }
}
void selSort(int arr[], char face[], char suit[], int n=1) {
    int i, j, minIdx;
  
    for (i = 0; i < n - 1; i++) {
        minIdx = i;
        for (j = i + 1; j < n; j++)
            if (arr[j] < arr[minIdx])
                minIdx = j;

        // swap arr[minIdx] and arr[i]
        swap(arr[minIdx], arr[i]);

       //swap corresponding faces and suits
        swap(face[minIdx], face[i]);
        swap(suit[minIdx], suit[i]);
    }
}
// Function to play the game
int plyGm(char faces[], char suits[], int size) {
    static int totGm=0;

    // Create 2D arrays to store player's and dealer's hands
    char pHnd2D[maxHand][2];
    char dHnd2D[maxHand][2];

    char pFcs[21], pSts[21];
    char dealFac[21], dealSut[21];
    int playHS = 0, dealHS = 0;
    int cCrd = 0;

    totGm++;

    // Initial deal
    //Deal 2 cards to player
    dlCard(pFcs[playHS], pSts[playHS], faces, suits, cCrd);
    pHnd2D[playHS][0] = pFcs[playHS];
    pHnd2D[playHS][1] = pSts[playHS];
    playHS++;
    dlCard(pFcs[playHS], pSts[playHS], faces, suits, cCrd);
    pHnd2D[playHS][0] = pFcs[playHS];
    pHnd2D[playHS][1] = pSts[playHS];
    playHS++;
    
    //Deal 2 cards to dealer
    dlCard(dealFac[dealHS], dealSut[dealHS], faces, suits, cCrd);
    dHnd2D[dealHS][0] = dealFac[dealHS];
    dHnd2D[dealHS][1] = dealSut[dealHS];
    dealHS++;
    dlCard(dealFac[dealHS], dealSut[dealHS], faces, suits, cCrd);
    dHnd2D[dealHS][0] = dealFac[dealHS];
    dHnd2D[dealHS][1] = dealSut[dealHS];
    dealHS++;

    // Player's turn
    bool playTn = true;
    while (playTn) {
        cout << "Player's hand: \n";
        dispSel(pFcs, pSts, playHS);
        int playVal = calcHV(pFcs, playHS);
        cout << "Hand value: " << playVal << endl;
        if (playVal > 21) {
            cout << "Player busts! Dealer wins." << endl;
            return totGm;
        }else if (playVal == 21) {
            cout << "Blackjack. Congratulations! You win. " << endl;
            return totGm;
        }

        string response;
        cout << "Do you want to hit(h) or stand(s)? ";
        cin >> response;
        if (response == "h") {
            dlCard(pFcs[playHS], pSts[playHS], faces, suits, cCrd);
            pHnd2D[playHS][0] = pFcs[playHS];
            pHnd2D[playHS][1] = pSts[playHS];
            playHS++;
        } else if (response == "s") {
            playTn = false;
        } else {
            cout << "Invalid response. Please enter 'hit(h)' or 'stand(s)'." << endl;
        }
    }
    // Dealer's turn
    bool dealTn = true;
    while (dealTn) {
        cout << "Dealer's hand: \n";
        dispSel(dealFac, dealSut, dealHS);
        int dealVal = calcHV(dealFac, dealHS);
        cout << "Hand value: " << dealVal << endl;
        if (dealVal > 21) {
            cout << "Dealer busts! Player wins. Congratulations!" << endl;
            return totGm;
        }else if (dealVal == 21) {
            cout << "Blackjack. Dealer wins. " << endl;
            return totGm;
        }

        if (dealVal > calcHV(pFcs, playHS)) {
            dealTn = false;
        }
        if(dealTn){
            dlCard(dealFac[dealHS], dealSut[dealHS], faces, suits, cCrd);
            dHnd2D[dealHS][0] = dealFac[dealHS];
            dHnd2D[dealHS][1] = dealSut[dealHS];
            dealHS++;
        }
    }
    //Display player's and dealer's cards
    cout << "****************************************"<<endl; 
    cout << "Player's hand: ";
    dispSel(pHnd2D, playHS);
    cout << "Dealer's hand: ";
    dispSel(dHnd2D, dealHS);
    cout << "****************************************"<<endl; 
    if (calcHV(pFcs, playHS) > calcHV(dealFac, dealHS)) {
        cout << "Player wins. Congratulations!" << endl;
    } else {
        cout << "Dealer wins!" << endl;
    }
 
    return totGm;
    
}
bool plyAgn(){
    cout << "Would you like to play again? (y/n)" << endl;
    string response;
    cin >> response;
    if(response=="y"){
        cout << "Great!!! Lets play again."<<endl<<endl;
        
        return true;
    }else{
        return false;
    }
}
// Function to deal a card   Passing by reference
void dlCard(char &face, char &suit, char faces[], char suits[], int &cCrd) {
    face = faces[cCrd];
    suit = suits[cCrd];
    cCrd++;
}
// Function to calculate the value of a hand
int calcHV(char faces[], int size) {
    int value = 0;
    for (int i = 0; i < size; i++) {
        if (faces[i] == 'A') {
            value += 1;
        } else if (faces[i] == 'J' || faces[i] == 'Q' || faces[i] == 'K' || faces[i] == 'T') {
            value += 10;
        } else {
            value += faces[i] - '0';
        }
    }
    return value;
}
//print one dimensional array
void dispSel(char faces[], char suits[], int n) {
    for (int i = 0; i < n; i++) {
        cout << "Card " << i + 1 << ": "
             << faces[i] << suits[i] << " Value:"<< detCV(faces[i],suits[i]) << endl;
    }
}
// The overloaded function ---> print 2d array
void dispSel(const char hand2D[][2], int handSz) {
    for (int i = 0; i < handSz; i++) {
        cout << hand2D[i][0] << hand2D[i][1] << " Value:"<< detCV(hand2D[i][0],hand2D[i][1])<<" ";;
    }
    cout << endl;
}
bool bSrch(int a[],int n,int val,int& indx)
{
    int high=n-1,low=0;
    do{
      int middle=(high+low)/2;
      if(val==a[middle]){
          indx=middle;
          return true;
      }
      else if(val<a[middle]){
          high=middle-1;
      }else{
          low=middle+1;
      }
    }while (low<=high);
          
    return false;
}





