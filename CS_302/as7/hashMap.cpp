#include "hashMap.h"

#include <iostream>
#include <string>

using namespace std;

template <typename t1, typename t2>
hashMap<t1, t2>::hashMap()
{
    size = 5;
    items = 0;
    head = NULL;

    table = new hashPair *[size];
    for (int i = 0; i < size; i++)
    {
        table[i] = NULL;
    }
}

template <typename t1, typename t2>
hashMap<t1, t2>::~hashMap()
{
    for (int i = 0; i < size; i++)
    {
        if (table[i] != NULL)
        {
            hashPair *prev = NULL;
            hashPair *curr = table[i];

            while (curr != NULL)
            {
                prev = curr;
                curr = curr->link;
                delete prev;
            }
        }
    }

    iteratorPair *prevIter = NULL;
    iteratorPair *currIter = head;

    while (currIter != NULL)
    {
        prevIter = currIter;
        currIter = currIter->link;
        delete prevIter;
    }
    delete[] table;

    items = size = 0;
    head = NULL;
    table = NULL;
}

template <typename t1, typename t2>
t2 &hashMap<t1, t2>::operator[](t1 key)
{
    // create a var loadfactor to store the load factor by doing int to double
    double loadFactor = static_cast<double>(items / size);

    if (loadFactor >= 0.50)
    {
        resize();
    }

    // do step 2 from pdf
    int x = h(key);

    while (true)
    {
        if (table[x] == NULL)
        {
            table[x] = new hashPair;
            table[x]->key = key;
            table[x]->value = t2();
            table[x]->link = NULL;

            iteratorPair *tmp = new iteratorPair;
            tmp->key = &(table[x]->key);
            tmp->value = &(table[x]->value);
            tmp->link = NULL;

            // if head NULL -> empty
            if (head == NULL)
            {
                head = tmp;
            }
            // find last node + add the newNode
            else
            {
                // this use to find last node
                iteratorPair *last = head;
                // last node -> next == NULL
                while (last->link != NULL)
                {
                    last = last->link;
                }
                // add the new node at the end of linked list
                last->link = tmp;
            }

            return table[x]->value;
        }
        else
        {
            int counter = 0;

            hashPair *hold = table[x];

            if (hold != NULL)
            {
                while (hold != NULL)
                {
                    if (hold->key == key)
                        return hold->value;

                    counter++;

                    if (hold->link == NULL)
                        break;

                    hold = hold->link;
                }
            }

            if (counter >= 2)
            {
                x = (x + 1) % size;
                counter = 0;
            }
            else
            {
                table[x]->link = new hashPair;
                table[x]->link->key = key;
                table[x]->link->value = t2();
                table[x]->link->link = NULL;

                iteratorPair *tmp = new iteratorPair;
                tmp->key = &(table[x]->link->key);
                tmp->value = &(table[x]->link->value);
                tmp->link = NULL;

                // if head NULL -> empty
                if (head == NULL)
                {
                    head = tmp;
                }
                // find last node + add the newNode
                else
                {
                    // this use to find last node
                    iteratorPair *last = head;
                    // last node -> next == NULL
                    while (last->link != NULL)
                    {
                        last = last->link;
                    }
                    // add the new node at the end of linked list
                    last->link = tmp;
                }

                items++;
                return table[x]->link->value;
            }
        }
    }
}

// const
template <typename t1, typename t2>
typename hashMap<t1, t2>::iterator hashMap<t1, t2>::begin() const
{
    iterator it(head);
    return it;
}

template <typename t1, typename t2>
typename hashMap<t1, t2>::iterator hashMap<t1, t2>::end() const
{
    iterator it;
    return it;
}

template <typename t1, typename t2>
void hashMap<t1, t2>::resize()
{
    int oldSize = size;
    size *= 2;
    hashPair **oldTable = table;

    table = new hashPair *[size];

    // init table to null to clear
    for (int i = 0; i < size; i++)
    {
        table[i] = NULL;
    }

    // loop through all table
    for (int i = 0; i < oldSize; i++)
    {
        // if old table has value
        if (oldTable[i] != NULL)
        {
            // set few ptr and node
            hashPair *oldElem;
            hashPair *entry = oldTable[i];

            // run until all new node not NULL
            while (entry != NULL)
            {
                // using []() to set up the value
                (*this)[entry->key] = entry->value;
                // go to next one
                oldElem = entry;
                entry = entry->link;
                // delete old node
                delete oldElem;
            }
        }
    }

    iteratorPair *prevIter = NULL;
    iteratorPair *currIter = head;

    while (currIter != NULL)
    {
        prevIter = currIter;
        currIter = currIter->link;
        delete prevIter;
    }
}

template <typename t1, typename t2>
int hashMap<t1, t2>::h(string key) const
{
    int sum = 0;
    for (int i = 0; i < key.length(); i++)
    {
        sum += key[i];
    }
    return sum % size;
}

template <typename t1, typename t2>
hashMap<t1, t2>::iterator::iterator()
{
    element = NULL;
}

template <typename t1, typename t2>
hashMap<t1, t2>::iterator::iterator(iteratorPair *p)
{
    element = p;
}

template <typename t1, typename t2>
const typename hashMap<t1, t2>::iterator &hashMap<t1, t2>::iterator::operator++(int)
{
    element = element->link;
    return *this;
}

template <typename t1, typename t2>
bool hashMap<t1, t2>::iterator::operator==(const hashMap<t1, t2>::iterator &rhs) const
{
    return (this->element) == (rhs.element);
}

template <typename t1, typename t2>
bool hashMap<t1, t2>::iterator::operator!=(const hashMap<t1, t2>::iterator &rhs) const
{
    return (this->element) != (rhs.element);
}

template <typename t1, typename t2>
t1 hashMap<t1, t2>::iterator::first()
{
    return *(element->key);
}

template <typename t1, typename t2>
t2 hashMap<t1, t2>::iterator::second()
{
    return *(element->value);
}
