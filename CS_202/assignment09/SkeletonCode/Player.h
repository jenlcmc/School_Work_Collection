#ifndef CARD_H
#define CARD_H
#include "Card.h"
#endif

#ifndef IO_H
#define IO_H
#include <iostream>
#endif

#ifndef RAND_H
#define RAND_H
#include <stdlib.h> 
#include <time.h>
#endif

using namespace std;

class Player{
private:
    Deck Hand, Foot;
public:
    Player();
    Player(const Deck &DealtHand);
    Card TurnCardOver();
    void ClaimCard(Card card);
    void ShowSortedCards() const;
    void CombineCards();
    bool HasHand() const;
    bool HasFoot() const;
    void SwapHandAndFoot();
    int GetHandSize() const;
};