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

/*******************************
 *  CARD CLASS 
*******************************/
class Card{
private:
    char Suit, Value;
    // Weight Proves that A > K > Q > J > T > 9-2
    short Weight; 
public:
    Card();
    Card(char suit, char value);
    string GetCard() const;
    bool operator<(Card rhsCard) const;
    bool operator>(Card rhsCard) const;
    int GetWeight() const;
};

/*******************************
 *  DECK CLASS 
*******************************/
class Deck{
private:
    struct Node{
        Card card;
        Node* next;
    };

    Node* Head; 
    int SizeOfDeck = 0;
    // Operator
    Node* operator[](int index);
public:
    // Default Constructor
    Deck();
    // Rule of Three
    ~Deck();
    void operator=(const Deck &copy);
    Deck(const Deck &copy);
    // Member Functions
    void AddToTopOfDeck(Card card);
    Card RemoveTopCard();
    void ShuffleDeck();
    void ClearDeck();
    void SortDeck();
    void SwapCards(Node* n1, Node* n2);
    // Getters
    int GetSizeOfDeck() const;
    bool isEmpty() const;
    int GetRandomCardIndex() const;
    void PrintDeck();
};