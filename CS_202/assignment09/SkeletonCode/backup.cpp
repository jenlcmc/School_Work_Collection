#ifndef CARD_H
#define CARD_H
#include "Card.h"
#endif

/*******************************
 *  CARD CLASS 
*******************************/
Card::Card(){
    Suit = '\0';
    Value = '\0';
    Weight = -999;
}

Card::Card(char suit, char value){
    Suit = suit;
    Value = value;

    if(value == 'A'){
        Weight = 14;
    }
    if(value == 'K'){
        Weight = 13;
    }
    if(value == 'Q'){
        Weight = 12;
    }
    if(value == 'J'){
        Weight = 11;
    }
    if(value == 'T'){
        Weight = 10;
    }
    if(value == 2){
        Weight  = 2;
    }
    if(value == 3){
        Weight  = 3;
    }
    if(value == 4){
        Weight  = 4;
    }
    if(value == 5){
        Weight  = 5;
    }
    if(value == 6){
        Weight  = 6;
    }
    if(value == 7){
        Weight  = 7;
    }
    if(value == 8){
        Weight  = 8;
    }
    if(value == 9){
        Weight  = 9;
    }

}

string Card::GetCard() const{
    string theCard = " |[";
    theCard += Suit;
    theCard += Value;
    theCard += "]| ";
    return theCard;
}

bool Card::operator<(Card rhsCard) const{
    if(Suit < rhsCard.Suit){
        //cout << 1 << endl;
        return true;
    }
    else if(Suit == rhsCard.Suit && Weight < rhsCard.Weight){ //this error
        //cout << 2 << endl; //for some reason, it never go into here.
        return true;
    } 
    else{
        //cout << 3 << endl;
        return false;
    }
}

bool Card::operator>(Card rhsCard) const{
    if(Suit > rhsCard.Suit){
        return true;
    }
    else if(Suit == rhsCard.Suit && Weight > rhsCard.Weight){ //this error
        return true;
    }
    else{
        return false;
    }
}

int Card::GetWeight() const{ //leak
    return Weight;
}
/*******************************
 *  DECK CLASS 
*******************************/
Deck::Deck(){ 
    Head = NULL;
    SizeOfDeck = 0;
}

// Rule of Three
Deck::~Deck(){
    ClearDeck();
}

void Deck::operator=(const Deck &copy){
    Node* newNodes = NULL; //for new node
    Node* current = NULL; // for transverse
    Node* last = NULL; //last element/node

    this->ClearDeck();
    this->SizeOfDeck = copy.GetSizeOfDeck();

    if(copy.Head == NULL || copy.SizeOfDeck == 0){//if copy list is empty
        return;
    }
    current = copy.Head; //current point to list to be copied

    //transverse the copy list
    while(current != NULL){
        newNodes = new Node; //allocate new node for this
        newNodes->next = NULL; //set next link to null

        if(current != copy.Head){ //case = current is not head
            last->next = newNodes; //next node will be newNode
            last = newNodes; //set the last into that newNode
            last->card = current->card; //copy the info
            current = current->next; //make new node
        }else{ //case = current is head
            last = newNodes;
            Head = newNodes;
            //copy cards into new one
            last->card = current->card;
            Head->card = current->card;
            current = current->next; //link to next node
        }
    }//end copy
}

//copy constructor
Deck::Deck(const Deck& copy){ //ask this
    Head = NULL;
    *this = copy;
}

Deck::Node* Deck::operator[](int index){
    Node* current = Head; //create tracking node to tranverse
    if(index >= SizeOfDeck){ //error case
        return NULL;
    }
    else{
        for(int i = 0; i < index; i++){ //loop the linked list
            if(current != NULL){ //check condition
                current = current->next; //current will be the node
            }
        }
    }
    return current;
}

// Member Functions
void Deck::AddToTopOfDeck(Card card){
    Node* newNode = NULL;
    newNode =  new Node; //create new Node
    newNode->card = card; //add data into the data of the linked list
    newNode->next = Head; //make next of new node as head
    Head = newNode; //move head to point to new node
    SizeOfDeck++;
}

Card Deck::RemoveTopCard(){ //ask this function
    if(Head != NULL){
    Node* oldNode = NULL;
    Card temp = Head->card; //return card
    oldNode = Head; //old Note that point to head
    Head = Head->next; //head will be the next node
    delete oldNode; //delete the old note which is from head
    SizeOfDeck--;
    return temp; 
    }
    return Card();
}

void Deck::ShuffleDeck(){  
    int ShuffleN = SizeOfDeck * 3;
    int rand1, rand2 = 0;
    Node* A, *B, *temp1, *temp2 = NULL;
    
    for(int i = 0; i < ShuffleN; i++){
        rand1 = GetRandomCardIndex(); 
        rand2 = GetRandomCardIndex();
        //this inside class funct = pointer to obj it is called in
        //shuffle mem of Deck class has this pointer point to Deck obj
        //* get deck obj itself and [] return back Node* pointer
        A = (*this)[rand1]; 
        temp1 = A;
        B = (*this)[rand2];
        temp2 = B;
        SwapCards(temp1, temp2);
    }
}

// This is essentially the Destructor. Has use outside of destructor
void Deck::ClearDeck(){
    Node* current = NULL;
    current = Head;//set current = head
    while(current != NULL){ //loop until null
        Head = Head->next; //head is next node
        delete current; //delete current
        current = Head;//update current
    }
    Head = NULL; //avoid dangling pointer
    SizeOfDeck = 0;
}

void Deck::SortDeck(){ //leak
    // s-h-d-c
    Node* i, *j = NULL;
    i = Head;
    //loop until null
    while(i != NULL){
        j = i->next; //j = next node from i /set j
        while(j != NULL){ //loop j until null
            if(j->card < i->card){ //compare to swap
                SwapCards(i, j);
            }
            j = j->next; //j will be next node/ update node
        }
        i = i->next; //update 
    }
}

void Deck::SwapCards(Node* A, Node* B){
    if(A == B){ //if both are same 
        return;
    }
    if(Head == NULL){ // if list is empty 
        return;
    }
    
    //tracking nodes
    Node* temp = NULL;
    Node* prevA = NULL;
    //Node* prevA = Head;
    Node* prevB = NULL;
    //Node* prevB = Head;
    Node* newA = Head;
    // Node* newA = prevA->next;
    Node* newB = Head;
    // Node* newB = prevB->next;

    //check for tracking node to see if para is head or not
    while(newA != A){ //if no, then set up the node
        prevA = newA; //prev will be head
        newA = newA->next; //new node will be the next node from head
    }

    //check for tracking node to see if para is head or not
    while(newB != B){ //if no, then set up the node
        prevB = newB; //prev will be head
        newB = newB->next; //new node will be the next node from head
    }

    //if they're null then do nothing
    if(newA == NULL || newB == NULL){
        return;
    }

    //check if prevA is not null then point to node B
    if(prevA != NULL){
        prevA->next = newB;
    }else{ //make A head
        Head = newB;
    }
    
    //check if prevA is not null then point to node B
    if(prevB != NULL){
        prevB->next = newA;
    }else{ //make B head
        Head = newA;
    }

    //swap
    temp = newB->next;
    newB->next = newA->next;
    newA->next = temp;

}

// Getters
int Deck::GetSizeOfDeck() const{
    return SizeOfDeck;
}

bool Deck::isEmpty() const{
    if(SizeOfDeck == 0){
        return true;
    }
    return false;
}

int Deck::GetRandomCardIndex() const{
    return (rand() % SizeOfDeck);
}

void Deck::PrintDeck(){
    cout << "-------------------------" << endl;
    for(int i = 0; i < SizeOfDeck; i++){
        cout << (*this)[i]->card.GetCard();
        if((i + 1) % 4 == 0){
            cout << endl;
        }
    }
     cout << endl << "-------------------------" << endl;
}