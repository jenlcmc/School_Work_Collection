#ifndef CARD_H
#define CARD_H
#include "Card.h"
#endif

#ifndef IO_H
#define IO_H
#include <iostream>
#endif

#ifndef PLAYER_H
#define PLAYER_H
#include "Player.h"
#endif

#ifndef RAND_H
#define RAND_H
#include <stdlib.h> 
#include <time.h>
#endif

using namespace std;

int main(){
    srand (time(NULL)); // Makes things more random
    bool print = false; // Keeps the output small if user wants.
    cout << "Would you like the print the game? Chances are it will go on forever....(Y/N)" << endl;
    cout << " : ";
    char ans;
    cin >> ans;
    if(ans == 'Y' || ans == 'y'){
        print = true;
    }
    // Deck to deal out cards evenly.
    Deck DealingDeck;
    for(int i = 2; i <= 14; i++ ){ // Cards 2 through Ace
        char val;
        switch(i){
            case(14):{val = 'A'; break;}
            case(13):{val = 'K'; break;}
            case(12):{val = 'Q'; break;}
            case(11):{val = 'J'; break;}
            case(10):{val = 'T'; break;}
            default:{val = i + 48; break;} // i+48 converts and int to its char representation.
            // int x = 5; char z = 5 + 48; --> '5'
        }
        DealingDeck.AddToTopOfDeck(Card('S', val)); // Spade
        DealingDeck.AddToTopOfDeck(Card('H', val)); // Heart
        DealingDeck.AddToTopOfDeck(Card('C', val)); // Club
        DealingDeck.AddToTopOfDeck(Card('D', val)); // Diamond
    }
    // 2 Hands, 1 for each player.
    Deck Pile1, Pile2;
    // Evenly deal out equal amount of weighted cards
    while(DealingDeck.GetSizeOfDeck() > 0){
        Pile1.AddToTopOfDeck(DealingDeck.RemoveTopCard());
        Pile2.AddToTopOfDeck(DealingDeck.RemoveTopCard());
    }
    // Dealer will shuffle the hands.
    Pile1.ShuffleDeck();
    Pile2.ShuffleDeck();
    // Players are given thier hands.
    Player Player1(Pile1);
    Player Player2(Pile2);
    // Prove to the user that the cards are properly distributed.
    cout << "Here are the Decks (Players cannot see these):" << endl << " - Player 1: " << endl;
    Pile1.PrintDeck();
    cout << " - Player 2: " << endl;
    Pile2.PrintDeck();
    // The pile is where Players will put thier cards
    Deck pile;
    // Pointer is used to minimize use of if statements.
    Player* WinningPlayer = NULL;
    // Limit number of turns. This game could be inifinite.
    int NumTurns = 0;
    // While both players have cards.
    while((Player1.HasFoot() || Player1.HasHand()) && (Player2.HasFoot() || Player2.HasHand())){
        // There is a chance during a duel that player(s) will deal ALL thier cards into the pile.
        // This bool says that either the pile can be claimed or it cannot
        bool noClaim = false;
        // NumTurns limit
        if(NumTurns > 1000){
            cout << "************************" << endl;
            cout << "The players got bored..." << endl;
            cout << "************************" << endl;
            break;
        }
        // While loop for a single turn. While needed for Duels.
        while(true){
            // If player 1 is out of cards, pick up thier foot.
            if(!Player1.HasHand()){
                Player1.SwapHandAndFoot();
            }
            // If player 2 is out of cards, pick up thier foot.
            if(!Player2.HasHand()){
                Player2.SwapHandAndFoot();
            }
            // If a player has no cards (resulting of duel), end game.
            if((!Player1.HasHand()) || (!Player2.HasHand())){
                if(print){
                    cout << "***************************************************************************" << endl;
                    cout << "One player has dealt all their cards into the pile... We cannot continue..." << endl;
                    cout << "***************************************************************************" << endl;
                }
                // Pile cannot be claimed, no one won it.
                noClaim = true;
                break;
            }
            // Players each deal 1 card.
            Card C1 = Player1.TurnCardOver();
            Card C2 = Player2.TurnCardOver();
            // Place on pile.
            pile.AddToTopOfDeck(C1);
            pile.AddToTopOfDeck(C2);
            if(print){
                cout << C1.GetCard() << "vs." << C2.GetCard() << "...";
            }
            // Check thier weights
            //Note **
            if(C1.GetWeight() < C2.GetWeight()){ //leak
                if(print){
                    cout << "Player 2 Wins!" << endl;
                }
                WinningPlayer = &Player2;
                break;
            }
            else if(C2.GetWeight() < C1.GetWeight()){ //leak 
                if(print){
                    cout << "Player 1 Wins!" << endl;
                }
                WinningPlayer = &Player1;
                break;
            }
            // They are the same weight. Duel!
            else{
                if(print){
                    cout << "Tie! Turn 3 Cards Over and Go Again!" << endl;
                }
                // Perhaps a player does not have 3 cards left
                // Deal out how ever many they can.
                int t = ((Player1.GetHandSize() < 3) ? Player1.GetHandSize() : 3);
                for(int i = 0; i < t; i++){
                    pile.AddToTopOfDeck(Player1.TurnCardOver());
                }

                t = ((Player2.GetHandSize() < 3) ? Player2.GetHandSize() : 3);
                for(int i = 0; i < t; i++){
                    pile.AddToTopOfDeck(Player2.TurnCardOver());
                }
            }
        }
        if(print){
            cout << " - " << pile.GetSizeOfDeck() << " cards in the pile!" << endl;
        }
        // If the pile is allowed to be claimed
        if(!noClaim){
            // Player gets all the cards.
            while(pile.GetSizeOfDeck() > 0){
                WinningPlayer->ClaimCard(pile.RemoveTopCard());
            }
        }
        NumTurns += 1;
    }

    cout << "*******************" << endl;
    cout << "Show us your cards!" << endl;
    cout << "*******************" << endl;
    cout << " - Player 1:" << endl;
    Player1.CombineCards();
    Player1.ShowSortedCards();
    cout << endl;
    cout << " - Player 2:" << endl;
    Player2.CombineCards();
    Player2.ShowSortedCards();
    cout << endl;
    cout << " - The Pile:" << endl;
    pile.SortDeck();
    pile.PrintDeck();

    return 0;
}