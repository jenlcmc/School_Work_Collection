#ifndef LL_H
#define LL_H

#include <iostream>

template <typename type>
class LL
{
    struct node
    {
        type data;
        node * prev;
        node * next;
    };

    public:
        class iterator
        {
            public:
                friend class LL;
                iterator ();
                iterator(node *);
                type operator *() const;
                const iterator& operator ++(int);
                const iterator& operator --(int);
                bool operator ==( const iterator &) const;
                bool operator !=( const iterator &) const;
            private:
                node * current;
        };

        LL();
        LL(const LL <type >&);
        const LL <type >& operator =(const LL<type >&);
        ~LL();
        void tailInsert(const type &);
        iterator begin () const;
        iterator end() const;
        void swapNodes(iterator&, iterator &);
        void clear();
    private:
        node * head;
        node * tail;
};

/**
 * @brief: Construct a new LL<myType>::iterator::iterator object
 * by setting current to NULL
 * @tparam: None
 * @return: None
 */
template <typename myType>
LL<myType>::iterator::iterator(){
    current = NULL;
}

/**
 * @brief Construct a new LL<myType>::iterator::iterator object
 * by setting current to the passing ptr in parameter
 * @param ptr 
 * @return None
 */
template <typename myType>
LL<myType>::iterator::iterator(node* ptr){
    current = ptr;
}

/**
 * @brief operator*()const = deference the ptr by using overloading *
 * by return current->data
 * @tparam None
 * @return deference of the current
 */
template <typename myType>
myType LL<myType>::iterator::operator*() const{
    return current->data;
}

/**
 * @brief overlaoding operator++ by setting current to current->next
 * using this to go to the next node
 * @tparam myType 
 * @return const LL<myType>::iterator& 
 */
template<typename myType>
const typename LL<myType>::iterator& LL<myType>::iterator::operator++(int){
    current = current->next;
    return *this;
}

/**
 * @brief overloading operator-- by setting current to current->prev
 * using this to go back a node
 * @tparam myType 
 * @return const LL<myType>::iterator& 
 */
template<typename myType>
const typename LL<myType>::iterator& LL<myType>::iterator::operator--(int){
    current = current->prev;
    return *this;
}

/**
 * @brief using boolean fuction to return if the parameter is ==
 * or != to the current
 * @param rhs-passing the iterator to check for bool value
 * @return true 
 * @return false 
 */
template<typename myType>
bool LL<myType>::iterator::operator==(const iterator& rhs) const{
    return current == rhs.current ? true : false;
}

/**
 * @brief using boolean fuction to return if the parameter is ==
 * or != to the current
 * @param rhs-passing the iterator to check for bool value 
 * @return true 
 * @return false 
 */
template<typename myType>
bool LL<myType>::iterator::operator!=(const iterator& rhs) const{
    return current != rhs.current ? true : false;
}

/**
 * @brief Construct a new LL<myType>::LL object
 * setting head and tail to NULl
 * @tparam none
 */
template<typename myType>
LL<myType>::LL(){
    head = tail = NULL;
}

/**
 * @brief Construct a new LL<myType>::LL object using copy constructor
 * @tparam myType 
 * @param copy-passing list to do deep copy of linked list
 */
template<typename myType>
LL<myType>::LL(const LL<myType>& copy){
    //making a new node use to track the list
    node* curr  = NULL;

    //clear out the list
    this->clear();

    //if nothing in list then point head and tail to null
    if(copy.head == NULL){
        head = tail = NULL; 
    }else{
        //otherwise, set the new node to passing head
        curr = copy.head;

        //making temp node
        node* ins = new node;

        //setting up temp node
        ins->prev = NULL;
        ins->next = NULL;
        ins->data = curr->data;

        //if the head is not null
        // set up the tail and head for the node
        if(head != NULL){
            tail->next = ins;
            ins->prev = tail;
            tail = ins;
            //othersie, set head and tail to that temp node
        }else{ head = tail = ins;}

        //go to next node
        curr = curr->next;

        //using loop to set up the rest of the node using same logic above
        while(curr != NULL){
            node* myNode = new node;
            myNode->prev = NULL;
            myNode->next = NULL;
            myNode->data = curr->data;
            if(head != NULL){
                tail->next = myNode;
                myNode->prev = tail;
                tail = myNode;
            }else{ head = tail = myNode;}

            curr = curr->next;
        } 
    }
}

/**
 * @brief overloading operator= to set list to the passing list
 * @param rhs- passing list to do overloading of =
 * @return const LL<myType>& 
 */
template<typename myType>
const LL<myType>& LL<myType>::operator=(const LL<myType>& rhs){
    //check whether the list is same or not
    //if not same->do the overloading=
    if(this != &rhs){
        //implement this same logic with the deep copy constructor
        node* curr  = NULL;

        //clear the list
        this->clear();

        //check if list is empty or not
        if(rhs.head == NULL){
            head = tail = NULL; 
        }else{
            //implement same logic with the deep copy
            curr = rhs.head;

            node* ins = new node;
            
            //copy 1st node
            ins->prev = NULL;
            ins->next = NULL;
            ins->data = curr->data;

            if(head != NULL){
                tail->next = ins;
                ins->prev = tail;
                tail = ins;
            }else{ head = tail = ins;}

            curr = curr->next;

            //copy rest of the node
            while(curr != NULL){
                node* myNode = new node;
                myNode->prev = NULL;
                myNode->next = NULL;
                myNode->data = curr->data;

                if(head != NULL){
                    tail->next = myNode;
                    myNode->prev = tail;
                    tail = myNode;
                }else{ head = tail = myNode;}

                curr = curr->next;
            }
        }
    }
    //return this
    return *this;
}

/**
 * @brief Destroy the LL<myType>::LL object
 * by using clear() function
 * @tparam none
 */
template<typename myType>
LL<myType>::~LL(){
    clear();
}

/**
 * @brief- insert new data/node into tail of the list
 * @param item- data to insert to the list
 */
template<typename myType>
void LL<myType>::tailInsert(const myType& item){
    //temp node using to insert data
    node* ins = new node;

    //set up temp node
    ins->prev = NULL;
    ins->next = NULL;
    ins->data = item;

    //check if the head of list is empty or not
    if(head != NULL){
        //set up tail and head if not empty
        tail->next = ins;
        ins->prev = tail;
        tail = ins;
    }else{ 
        //set up head and tail if empty
        head = ins;
        tail = ins; 
    }
}

/**
 * @brief- return a 1st node or head node of the list
 * @tparam None
 * @return LL<myType>::iterator 
 */
template<typename myType>
typename LL<myType>::iterator LL<myType>::begin() const{
    return iterator(head);
}

/**
 * @brief Returns last node or tail node of the list
 * @tparam None
 * @return LL<myType>::iterator 
 */
template<typename myType>
typename LL<myType>::iterator LL<myType>::end() const{
    return iterator(tail);
}

/**
 * @brief-swapping adjacent node with multiple cases
 * @param it1-left node to swap
 * @param it2-right node to swap
 */
template<typename myType>
void LL<myType>::swapNodes(iterator& it1, iterator& it2){
    //temp nodes using to check the swap nodes
    node* A = it1.current; 
    node* B = it2.current;
    node* prevA = A->prev;
    node* nextB = B->next;

    //if the data or the node is the same then do nothing
    if(*it1 == *it2 || A == B){ return;}

    //case in which swap nodes is mid/not head and tail
    if(A != head && B != tail){
        //NULL<-C-><-A-><-B-><-D->NULL;
        //NULL<-C-><-B-><-A-><-D->NULL;

        it1.current->prev = B;
        it1.current->next = nextB;
        
        it2.current->prev = prevA;
        it2.current->next = A;

        it1.current->next->prev = A;
        it2.current->prev->next = B;
    }

    //case when there is only 2 nodes
    if(A == head  && B == tail){
        head = tail = NULL;

        //NULL<-A-><-B->NULL
        //NULL<-B-><-A->NULL
        it1.current->prev = B;
        it1.current->next = NULL;
        
        it2.current->prev = NULL;
        it2.current->next = A;

        head = it2.current;
        tail = it1.current;
    }

    //case when either one of the node is head or tail
    if(A == head || B == tail){
        //if left node is head
        if(A == head){
            head = NULL;
            //NULL<-A-><-B-><-C->NULL
            //NULL<-B-><-A-><-C->NULL

            it1.current->prev = B;
            it1.current->next = nextB;

            it2.current->prev = NULL;
            it2.current->next = A;

            it1.current->next->prev = A;

            head = it2.current;
        }
        //if right node is tail
        if(B == tail){
            tail = NULL;
            //NULL<-C-><-A-><-B->NULL
            //NULL<-C-><-B-><-A->NULL

            it1.current->prev = B;
            it1.current->next = NULL;

            it2.current->prev = prevA;
            it2.current->next = A;

            it2.current->prev->next = B;

            tail = it1.current;
        }
    }

    //swap node
    node* temp = it1.current;
    it1.current = it2.current;
    it2.current = temp;
}

/**
 * @brief-function uses to clear the linked list
 * @tparam None 
 */
template<typename myType>
void LL<myType>::clear(){
    //temp node using to track and clear the whole list
    node* temp = head;
    //delete using while loop until temp != NULl
    while(temp != NULL){
        head = head->next;
        delete temp;
        temp = head;
    }
    //then set up head and tail to NULl to prevent dangling ptr
    head = NULL;
    tail = NULL;
}
#endif
