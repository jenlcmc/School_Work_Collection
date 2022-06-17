#ifndef PLAYER_H
#define PLAYER_H
#include "Player.h"
#endif

Player::Player(){}

// Uses the Copy Constructor for Deck, which uses the Assignment Overload.
Player::Player(const Deck &DealtHand) : Hand(DealtHand){}

Card Player::TurnCardOver(){
    return Hand.RemoveTopCard();
}

bool Player::HasHand() const{
    return (Hand.GetSizeOfDeck() > 0);
}

bool Player::HasFoot() const{
    return (Foot.GetSizeOfDeck() > 0);
}

// this is called usually when a player has no more hand cards.
void Player::SwapHandAndFoot(){
    Deck temp = Hand;
    Hand = Foot;
    Foot = temp;
    // This makes it likely that the game will be finite. 
    Hand.ShuffleDeck();
}

// Claim a card and add it to the foot
void Player::ClaimCard(Card card){
    Foot.AddToTopOfDeck(card);
}

// At the end of the game, a player will need to combine both hands. 
void Player::CombineCards(){
    while(Foot.GetSizeOfDeck() > 0){
        Hand.AddToTopOfDeck(Foot.RemoveTopCard());
    }
}

// Sort a copy of the deck and show it.
void Player::ShowSortedCards() const{
    Deck temp = Hand;
    temp.SortDeck();
    temp.PrintDeck();
}

int Player::GetHandSize() const{
    return Hand.GetSizeOfDeck();
}