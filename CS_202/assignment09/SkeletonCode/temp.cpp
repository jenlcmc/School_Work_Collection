#ifndef CARD_H
#define CARD_H
#include "Card.h"
#endif

#ifndef IO_H
#define IO_H
#include <iostream>
#endif

using namespace std;

int main(){
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

    cout << "before everything" << endl;
    DealingDeck.PrintDeck();
    Deck NewDeck;
    NewDeck = DealingDeck;
    //cout << NewDeck.GetSizeOfDeck() << endl;
    cout << "Assignment operator" << endl;
    NewDeck.PrintDeck();
    
    Deck NewDeck2(DealingDeck);
    cout << "Copy construct" << endl;
    NewDeck2.PrintDeck();


    //these 
    cout << "Sort deck copy" << endl;
    NewDeck2.SortDeck();
    NewDeck2.PrintDeck();
    cout << "Sort deck assignmnt" << endl;
    NewDeck.SortDeck();
    NewDeck.PrintDeck();
    

    cout << "Shuffle deck copy" << endl;
    NewDeck2.ShuffleDeck();
    NewDeck2.PrintDeck();
    cout << "Shuffle deck assignmnt" << endl;
    NewDeck.ShuffleDeck();
    NewDeck.PrintDeck();



}