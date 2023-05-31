/*
 * File:   main.cpp
 * Author: Malachi Ferrett
 * Created on April 16, 2023 5:15 PM
 * Purpose:  Project 1 Play Black Jack
 */

// System Libraries
#include <iostream> //INput/Output LIbrary
#include <cstdlib>  //Srand
#include <ctime>    //Time to set randm number seed
#include <iomanip>  //Format Library
#include <fstream>  //File in/out
#include <cmath>    //Math Library
#include <string>   // string library
using namespace std;

// Global Constants, no Global Variable are allowed
// Math/Physics/Math/Conversions/Higher Dimensions found here
const char NCARDS = 52;

// Function Prototypes

// Execution Begins Here
int main(int argc, char **argv)
{
    // Set random number seed
    srand(static_cast<unsigned>(time(0)));

    // Declare Variables
    fstream out;
    int cardnum, cardval;
    unsigned int nC1, nC2, nC3, nC4, nC5; // Card number
    unsigned int vC1, vC2, vC3, vC4, vC5; // Card value
    unsigned char face, suit, face1, face2, face3, face4, face5,
        suit1, suit2, suit3, suit4, suit5; // Card face and suit
    float sum = 0.0;
    int cardsPulled = 0;
    string response = "";

    // Initialize Variables
    out.open("cards.dat", ios::out);

    // Map the inputs/known to the outputs
    // Creates a file with 52 playing cards
    // with an assigned value, number, face, and suit
    for (int card = 0; card < NCARDS; card++)
    {
        switch (card / 13)
        {
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
        char cmod = card % 13;
        face = cmod == 0 ? 'A' : cmod == 1 ? '2'
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

        cardnum = card + 1;
        if ((face == 'A') && (suit == 'S' || 'D' || 'H'))
            cardval = 1;
        else if (face == '2')
            cardval = 2;
        else if (face == '3')
            cardval = 3;
        else if (face == '4')
            cardval = 4;
        else if (face == '5')
            cardval = 5;
        else if (face == '6')
            cardval = 6;
        else if (face == '7')
            cardval = 7;
        else if (face == '8')
            cardval = 8;
        else if (face == '9')
            cardval = 9;
        else if (face == 'T')
            cardval = 10;
        else if ((face == 'J') && (suit == 'S' || 'D' || 'H'))
            cardval = 11;
        else if ((face == 'Q') && (suit == 'S' || 'D' || 'H'))
            cardval = 12;
        else if ((face == 'K') && (suit == 'S' || 'D' || 'H'))
            cardval = 13;
        else
            cardval = 0;
        // cout<<setw(3)<<cardval<<" "<<cardnum<<" "<<face<<suit<<endl;
        out << setw(3) << cardval << " " << cardnum << " " << face << suit << endl;
    }
    // Clean up files
    out.close();

    // Randomly selects 5 cards from the 52 card file and
    // sorts them from the lowest number to the highest
    // The number of each card is displayed.
    fstream cards;
    nC1 = rand() % NCARDS + 1;
    do
    {
        nC2 = rand() % NCARDS + 1;
    } while (nC1 == nC2);
    if (nC1 > nC2)
    {
        unsigned short temp = nC1;
        nC1 = nC2;
        nC2 = temp;
    }
    do
    {
        nC3 = rand() % NCARDS + 1;
    } while (nC1 == nC3 || nC2 == nC3);
    if (nC2 > nC3)
    {
        unsigned short temp = nC2;
        nC2 = nC3;
        nC3 = temp;
    }
    if (nC1 > nC2)
    {
        unsigned short temp = nC1;
        nC1 = nC2;
        nC2 = temp;
    }
    do
    {
        nC4 = rand() % NCARDS + 1;
    } while (nC1 == nC4 || nC2 == nC4 || nC3 == nC4);
    if (nC3 > nC4)
    {
        unsigned short temp = nC3;
        nC3 = nC4;
        nC4 = temp;
    }
    if (nC2 > nC3)
    {
        unsigned short temp = nC2;
        nC2 = nC3;
        nC3 = temp;
    }
    if (nC1 > nC2)
    {
        unsigned short temp = nC1;
        nC1 = nC2;
        nC2 = temp;
    }
    do
    {
        nC5 = rand() % NCARDS + 1;
    } while (nC1 == nC5 || nC2 == nC5 || nC3 == nC5 || nC4 == nC5);

    if (nC4 > nC5)
    {
        unsigned short temp = nC4;
        nC4 = nC5;
        nC5 = temp;
    }
    if (nC3 > nC4)
    {
        unsigned short temp = nC3;
        nC3 = nC4;
        nC4 = temp;
    }
    if (nC2 > nC3)
    {
        unsigned short temp = nC2;
        nC2 = nC3;
        nC3 = temp;
    }
    if (nC1 > nC2)
    {
        unsigned short temp = nC1;
        nC1 = nC2;
        nC2 = temp;
    }
    cout<<"A deck of cards consists of 52 cards with 4 suits:  Spades (S), Hearts (H), Diamonds (D), and Clubs (C).\n";
    cout<<"Each suit has 13 cards:  Ace, 2, 3, 4, 5, 6, 7, 8, 9, Jack, Queen, and King.\n";
    cout<<"To win when playing Blackjack, the player has to have cards that add up to 21.\n"<<endl;
    cout << "Here are 5 randomly selected cards from a 52-card deck and their number or position in a new deck."<<endl;
    cout << setw(3) << nC1
         << setw(3) << nC2
         << setw(3) << nC3
         << setw(3) << nC4
         << setw(3) << nC5 << endl;

    // User invited to play Back Jack
    cout << "Do you want to play Blackjack? (y/n)\n";
    cin >> response;
    {
        if (response == "y");
    }
    cards.open("cards.dat", ios::in);
    if (cards.is_open())
    {
        bool done = false;
        while (!done && (cards >> cardval >> cardnum >> face >> suit))
        {
            if (cardnum == nC1)
            {
                vC1 = cardval;
                face1 = face;
                suit1 = suit;
                sum += cardval;
                cardsPulled++;
                // The value, card number, and face/suit of the first card is displayed.
                cout << "First Card:";
                cout << " Card Number = " << setw(3) << nC1 << " "
                     << "Card Value = " << setw(3) << vC1 << " "
                     << "Face/Suit = " << setw(3) << face1 << suit1 << endl;
                cout << "Sum Of Card Values = " << sum << endl;
            }

            if (cardnum == nC2)
            {
                vC2 = cardval;
                face2 = face;
                suit2 = suit;
                sum += cardval;
                cardsPulled++;
                // The value, card number, and face/suit of the second card is displayed
                // along with the sum of the value of the first two cards.
                cout << "Second Card:";
                cout << " Card Number = " << setw(3) << nC2 << " "
                     << "Card Value = " << setw(3) << vC2 << " "
                     << "Face/Suit = " << setw(3) << face2 << suit2 << endl;
                cout << "Sum Of Card Values = " << sum << endl;
            }
            if (cardsPulled == 2)
            {
                done = true;
            }
        }
    }
    else
    {
        cout << "Unable to read cards.dat file!";
    }

    while (cardsPulled >= 2)
    {
        if (sum > 21)
        {
            cout << "Bust!";
            exit(0);
        }
        else if (sum == 21)
        {
            cout << "Congratulations"; //If sum of cards = 21 "Congratulations"
            exit(0);
        }
        else if (sum < 21)
        {
            if (cardsPulled == 5)
            {
                cout << "Game over!";
                exit(0);
            }
            else if (cardsPulled < 5)
            {
                while (sum < 21)
                {
                    cout << "Draw another card ('hit') (y/n): )"; //Invite to draw a third card
                    cin >> response;

                    if (response == "y")
                    {
                        cout << "Cards pulled = " << cardsPulled << endl;
                        cards.close();
                        cards.open("cards.dat", ios::in);
                        if (cards.is_open())
                        {
                            int i = 0;
                            bool done = false;
                            while (!done && (cards >> cardval >> cardnum >> face >> suit))
                            {

                                if (cardsPulled == 2 && cardnum == nC3)
                                {
                                    vC3 = cardval;
                                    face3 = face;
                                    suit3 = suit;
                                    sum += cardval;
                                    cardsPulled++;
                                    // The value, card number, and face/suit of the third card is displayed
                                    // along with the sum of the value of the first three cards.
                                    cout << "Card Number = " << setw(3) << cardnum << " "
                                         << "Card Value = " << setw(3) << cardval << " "
                                         << "Face/Suit = " << setw(3) << face << suit << endl;
                                    cout << "Sum Of Card Values = " << sum << endl;
                                }
                                else if (cardsPulled == 3 && cardnum == nC4)
                                {
                                    vC4 = cardval;
                                    face4 = face;
                                    suit4 = suit;
                                    sum += cardval;
                                    cardsPulled++;
                                    cout << "Card Number = " << setw(3) << cardnum << " "
                                         << " Card Value = " << setw(3) << cardval << " "
                                         << " Face/Suit = " << setw(3) << face << suit << endl;
                                    cout << "Sum Of Card Values = " << sum << endl;
                                }
                                else if (cardsPulled == 4 && cardnum == nC5)
                                {
                                    vC5 = cardval;
                                    face5 = face;
                                    suit5 = suit;
                                    sum += cardval;
                                    cardsPulled++;
                                    // The value, card number, and face/suit of the fourth card is displayed
                                    // along with the sum of the value of the first four cards.
                                    cout << "Card Number = " << setw(3) << cardnum << " "
                                         << "Card Value = " << setw(3) << cardval << " "
                                         << "Face/Suit = " << setw(3) << face << suit << endl;
                                    cout << "Sum Of Card Values = " << sum << endl;
                                }
                                if (cardsPulled == 5 || sum == 21 || sum > 21)
                                {
                                    if (i == 0)
                                    {
                                        cout << "Cards pulled = " << cardsPulled << endl;
                                        cout << "Sum Of Card Values = " << sum << endl;
                                        done = true;
                                    }
                                }
                            }
                        }
                        else
                        {
                            cout << "Unable to read cards.dat file" << endl;
                        }
                        if (response == "n")
                        {
                            cout << "Exit";
                        }
                    }
                }
            }
            cards.close();
        }
    }
    // Exit stage right!
    return 0;
}
