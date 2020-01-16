
// File: random.cpp
// Compiler: g++ 

// Program Description:  
// This program plays 
// blackjack (simple version)


#include <iostream>
#include <cstdlib>
#include <ctime>
# include <string>

using namespace std;


void draw_card(int & card, int & suit, bool & blackjack, bool & bust,
               int & total, int & num_aces, int *values)
{
    // draw card at random
    card = rand() % 13;
    suit = rand() % 4;

    //check value of card
    if (values[card])
        total = total + values[card];
    else
    {
        num_aces++;
    }

    // now see if bust
    if (total>21) bust = true;
    if (total+num_aces>21) bust = true;

    // now see if 21 - only need to check if 1 ace is 
    // counted as 11 because any more would bust
    if (total == 21) blackjack = true;
    if (total + num_aces == 21) blackjack = true;
    if (num_aces > 0 && (total + num_aces - 1 + 11 == 21)) blackjack = true; 
        
}

int main()
{
    srand(time(NULL));

    string cards[] = {"2","3","4","5","6","7","8","9",
                     "10","Jack","Queen","King","Ace"};

    // card values NB 0 will be either 1 or 11 eventually

    int values[] = {2,3,4,5,6,7,8,9,10,10,10,10,0}; 
    string suits[] = {" of Spades"," of Clubs"," of Hearts", 
                     " of Diamonds"};

    string arrow = "------------------------> "; // just for decoration
    bool draw = true;
    bool bust = false; // check whether player bust or not
    bool blackjack = false; // and if they have blackjack
    char status;
    
    int total = 0;
    int num_aces = 0; // number of aces in hand (treat differently)
    while (draw)
    {
        int card, suit;
        draw_card(card,  suit,  blackjack,  bust,
                  total,  num_aces, values);
        // output card drawn
        cout << arrow << cards[card] << suits[suit] << endl;

        // Now resolve outcomes
        if (bust) 
        {
            cout << arrow << "BUST! You lose!" << endl;
            exit(EXIT_SUCCESS);
        }
        if (blackjack) 
        {
            cout << arrow << "Blackjack! You win!" << endl;
            exit(EXIT_SUCCESS);
        }

        
        cout << "Hit (h) or stand (s)? ";
        cin >> status;
        switch (status)
        {
            case 'h':
                draw = true;
                break;
            case 's':
                draw = false;
                break;
            default:
                cout << "Couldn't hear you, say it again?"
                     << endl;
                continue;
        }
        
    }
    // output score
    int score;
    if (total + num_aces - 1 + 11 <= 21) 
        score = total + num_aces - 1 + 11;
    else score = total + num_aces;

    cout << "\nYour hand is worth " << score << endl;
    cout << endl;
    cout << "Dealer hand:" << endl;

    draw = true;
    total = 0;
    num_aces = 0; 
    blackjack = false; // don't really need these since
    bust = false;      // if true game already won/lost
    while (draw)
    {
        int card, suit;
        draw_card(card,  suit,  blackjack,  bust,
                  total,  num_aces, values);
        
        // output card drawn
        cout << arrow << cards[card] << suits[suit] << endl;

        // Now resolve outcomes
        if (bust) 
        {
            cout << arrow << "BUST! You win!" << endl;
            exit(EXIT_SUCCESS);
        }
        if (blackjack) 
        {
            cout << arrow << "Blackjack! You lose!" << endl;
            exit(EXIT_SUCCESS);
        }
        if (total > 17) break;
        if (total + num_aces > 17) break;
    }

    int dealer_score;
    if (total + num_aces - 1 + 11 <= 21) 
        dealer_score = total + num_aces - 1 + 11;
    else dealer_score = total + num_aces;

    cout << "\nDealer score: " << dealer_score << endl << endl;

    if (score > dealer_score) cout << arrow << "You win!" << endl;
    else cout << arrow << "You lose" << endl;
    return 0;
}