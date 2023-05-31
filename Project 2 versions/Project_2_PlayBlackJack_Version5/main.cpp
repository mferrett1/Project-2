/*
 * File:   main.cpp
 * Author: Malachi Ferrett
 * Created on April 16, 2023 5:15 PM
 * Purpose:  Project 2 Play Black Jack
 */

///System Libraries
#include <iostream>  //Input/Output
#include <fstream>  //File Input/output
#include <vector>  //Vector
#include <iomanip>  //Format
#include <cstdlib>   //Random Functions
#include <ctime>     //Time Library
#include <cmath>  //Math Library 
#include <string> //string
using namespace std;

// Global Constants, no Global Variable are allowed
// Math/Physics/Math/Conversions/Higher Dimensions found here
const int NCARDS = 15;
const int TCARDS = 52;
// assuming max hand size is 11 (smallest value for blackjack is 2, so you can have 11 cards max)
const int maxHand = 11;

// Function Prototypes
char detSuit(int);
char detFace(int);
int detCV(char,char);
void wrtFile(ofstream& ,int,int,char,char);
void rdFile(const string &,vector<int> &, vector<char> &, vector<char> &);
void bblSrt(int [],char [],char [],int);
void selSort(int [],char [], char [],int);

// Execution Begins Here
int main(int argc, char **argv)
{
    // Set random number seed
    srand(static_cast<unsigned>(time(0)));

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
        string response;"n";
            
        cin >> response;
        if(response=="n"){
            exit(0);
        }while(play){
         //Declare Variables/Arrays/Vectors
        //Use of parallel arrays 
        vector<int> cNums;
        vector<char> cFaces;
        vector<char> cSuits;
        
        vector<bool> selected(52,false);
        //Initialize or input i.e. set variable values
        rdFile("cards.dat",cNums,cFaces,cSuits);
        
        int selCN[NCARDS];
        char selCF[NCARDS];
        char selCS[NCARDS];
        
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
        //Else Selection Sort
        if(rand()%2==0){
            bblSrt(selCN, selCF, selCS, NCARDS);
        } else{
            selSort(selCN, selCF, selCS, NCARDS);
                
        }

    // Exit stage right!
    return 0;
}
//Function Definitions
char detSuit(int card=0) {
    switch (card / 13) {
        case 0: return 'S';
        case 1: return 'D';
        case 2: return 'C';
        default: return 'H';
    }
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
    if (face == 'A') return 1;
    else if (face == '2') return 2;
    else if (face == '3') return 3;
    else if (face == '4') return 4;
    else if (face == '5') return 5;
    else if (face == '6') return 6;
    else if (face == '7') return 7;
    else if (face == '8') return 8;
    else if (face == '9') return 9;
    else if (face == 'T') return 10;
    else if (face == 'J') return 10;
    else if (face == 'Q') return 10;
    else if (face == 'K') return 10;
    else return 0;
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