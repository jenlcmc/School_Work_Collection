#ifndef CARD_H
#define CARD_H
#include "Card.h"
#endif

/*******************************
 *  CARD CLASS 
*******************************/
/**Card()- default constructor of card class
 * Algorithm - set Suit and Value member varibale to '\0' and weight to -999
 */
Card::Card(){
    Suit = '\0';
    Value = '\0';
    Weight = -999;
}
/**Card()- constuctor
 * char suit- passed suit
 * char value- passed value of suit
 * Algorithm- set Suit and Value mem var to suit and value passed
 * then compare the value to specefic char to set the weight
 */
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
    if(value == '2'){
        Weight  = 2;
    }
    if(value == '3'){
        Weight  = 3;
    }
    if(value == '4'){
        Weight  = 4;
    }
    if(value == '5'){
        Weight  = 5;
    }
    if(value == '6'){
        Weight  = 6;
    }
    if(value == '7'){
        Weight  = 7;
    }
    if(value == '8'){
        Weight  = 8;
    }
    if(value == '9'){
        Weight  = 9;
    }
    
}

/**GetCard()- return a string representing the card.
 *  return a string representing the card.
 *  Algorithm: Use += to add each string with Suit and Value variables
 */ 
string Card::GetCard() const{
    string theCard = " |[";
    theCard += Suit;
    theCard += Value;
    theCard += "]| ";
    return theCard;
}

/**operator< - overload operator to compare
 * Card rhsCard- passed card
 * Algorithm- Check to see if Suit var is < than passed rhs or not, if yes, then return true
 * also check to see if suit == rhs or not. if yes, check it weight and return true
 * return false for other case
 */
bool Card::operator<(Card rhsCard) const{
    if(Suit < rhsCard.Suit){
        return true;
    }
    if(Suit == rhsCard.Suit && Weight < rhsCard.Weight){ //tie suit -> check the weight
        return true;
    }
    else{
        return false;
    }
}

/**operator> - overload operator to compare
 * Card rhsCard- passed card
 * Algorithm- Check to see if Suit var is > than passed rhs or not, if yes, then return true
 * also check to see if suit == rhs or not. if yes, check it weight and return true
 * return false for other case
 */
bool Card::operator>(Card rhsCard) const{
    if(Suit > rhsCard.Suit){
        return true;
    }
    if(Suit == rhsCard.Suit && Weight > rhsCard.Weight){ //if suit == -> check weight
        return true;
    }
    else{
        return false;
    }
}

/**GetWeight- return it weight
 * return weight var
 */
int Card::GetWeight() const{
    return Weight;
}
/*******************************
 *  DECK CLASS 
*******************************/
/**Deck()- default constructor
 * Algo- set head to null and size to 0
 */
Deck::Deck(){ 
    Head = NULL;
    SizeOfDeck = 0;
}

/**~deck()- destrcutor
 * Algo- use ClearDeck() to clear whole linked list
 */
// Rule of Three
Deck::~Deck(){
    ClearDeck();
}

/**operator=()- use to do deep copy of the passed linked list
 * const Deck &copy- passed copy deck
 * Algo- steps already write inside the function.
 * Have to clean deck 1st and copy the size
 * then set the current pointer to the head of copy before copy
 * After that, copy 1st node then use while loop to copy the remainding
 */
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

    //copy 1st node
    Head = new Node; //create node
    Head->card = current->card; //copy info
    Head->next = NULL; //set link of next node to null
    
    last = Head; //last point to 1st node
    current = current->next; //current point to next node

    //copy remaning list
    while(current != NULL){
        newNodes = new Node; //create new node
        newNodes->card = current->card; //copy the info
        newNodes->next = NULL; //set link of new node to null

        last->next = newNodes;// attach newNodes after last
        last = newNodes; //make last point to last node

        current = current->next; //update curr
    }
}

//copy constructor
/**const Deck& copy- passed list to copy
 * Algo- set Head to null so that it wont be delete when using = overload and accident delete unallocate element
 * then use = overload to copy
 */
Deck::Deck(const Deck& copy){
    Head = NULL; //if dont have this seg
    *this = copy;
}

/**operator[]- return a pointer to a node within the linked list.
 * int index = index of the return node
 * return a pointer to a node within the linked list.
 * Algo- create new node for tracking then check if the index is in bound or not
 * then loop through the index and if transverse not null, set current to next node
  */
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
/**AddToTopDeck()- add new card to the top of deck or linked list
 * Card  card - passed card to add
 * return void
 * Algo- the steps are already inside function
 */
void Deck::AddToTopOfDeck(Card card){
    Node* newNode = NULL;
    newNode =  new Node; //create new Node
    newNode->card = card; //add data into the data of the linked list
    newNode->next = Head; //make next of new node as head
    Head = newNode; //move head to point to new node
    SizeOfDeck++;
}

// Member Functions
/**RemoveTopCard()- remove card at the top of deck or linked list
 * return card that delete
 * Algo- the steps are already inside function
 */
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

/**ShuffleDeck()- shuffle the cards randomly
 * return void
 * Algo- set the shuffle time to size of deck * 3
 * the remain steps already writen inside the fucntion
 */
void Deck::ShuffleDeck(){  
    int ShuffleN = SizeOfDeck * 3;
    int rand1, rand2 = 0;
    Node* A = NULL;
    Node* B = NULL;
    Node *temp1 = NULL;
    Node* temp2 = NULL;
    
    //loop through custom time
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
/**ClearDeck()- clear the whole deck
 * return void;
 * Algo- step is already writen inside the func
 */
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

/**SortDeck()- clear the whole deck
 * return void;
 * Algo- step is already writen inside the func
 */
void Deck::SortDeck(){ 
    // s-h-d-c
    int i = 0; 
    int j = 0;
    //this inside class funct = pointer to obj it is called in
    //shuffle mem of Deck class has this pointer point to Deck obj
    //* get deck obj itself and [] return back Node* pointer
    //loop until null
    while((*this)[i] != NULL){
        j = i + 1; //j = next node from i /set j
        while((*this)[j] != NULL){ //loop j until null
            if((*this)[j] < (*this)[i]){ //compare to swap
                SwapCards((*this)[i], (*this)[j]);
            }
            j++; //j will be next node/ update node
        }
        i++; //update 
    }
}

/**SwapCards() - swap 2 cards (hard way)
 * Node* A and B passed node/card to swap
 * return void
 * Algo- already writen inside the funct
 */
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
    Node* prevB = NULL;
    Node* newA = Head;
    Node* newB = Head;

    //check for tracking node to see if para is head or not
    while(newB != B){ //if no, then set up the node
        prevB = newB; //prev will be head
        newB = newB->next; //new node will be the next node from head
    }

    //check for tracking node to see if para is head or not
    while(newA != A){ //if no, then set up the node
        prevA = newA; //prev will be head
        newA = newA->next; //new node will be the next node from head
    }

    //if they're null then do nothing
    if(newA == NULL || newB == NULL){
        return;
    }

    //check if prevA is not null then point to node B
    if(prevB != NULL){
        prevB->next = newA;
    }else{ //make B head
        Head = newA;
    }

    //check if prevA is not null then point to node B
    if(prevA != NULL){
        prevA->next = newB;
    }else{ //make A head
        Head = newB;
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