#ifndef HASHMAP_H
#define HASHMAP_H

#include <iostream>
#include <string>

using std::string;

template <typename t1, typename t2>
class hashMap
{
public:
    struct hashPair
    {
        t1 key;
        t2 value;
        hashPair *link;
    };

    struct iteratorPair
    {
        t1 *key;
        t2 *value;
        iteratorPair *link;
    };

    class iterator
    {
    public:
        friend class hashMap;
        iterator();
        const iterator &operator++(int);
        bool operator==(const iterator &) const;
        bool operator!=(const iterator &) const;
        t1 first();
        t2 second();

    private:
        iterator(iteratorPair *);
        iteratorPair *element;
    };

    hashMap();
    ~hashMap();
    t2 &operator[](t1);
    iterator begin() const;
    iterator end() const;

private:
    void resize();
    int h(std::string) const;
    int items;
    int size;
    hashPair **table;
    iteratorPair *head;
};

/**
 * @brief Construct a new hash Map<t1, t2>::hash Map object
 *  default constructor, sets the size to 5, items to 0, sets head with NULL,
 *  allocates the hash table table = new hashPair*[size]
 *  and then sets each element of table with NULL
 * @tparam t1
 * @tparam t2
 */
template <typename t1, typename t2>
hashMap<t1, t2>::hashMap()
{
    size = 5;
    items = 0;
    head = NULL;

    table = new hashPair *[size];
    // init table with NULL
    for (int i = 0; i < size; i++)
    {
        table[i] = NULL;
    }
}

/**
 * @brief Destroy the hash Map<t1, t2>::hash Map object
 * destructor, deallocate the hash table (you first need to deallocate
    each linked list within table and then deallocate table),
    and then dellocate the linked list that head points to
 * @tparam t1
 * @tparam t2
 */
template <typename t1, typename t2>
hashMap<t1, t2>::~hashMap()
{
    // delete HashPair
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

    // delete IteratorPair
    iteratorPair *prevIter = NULL;
    iteratorPair *currIter = head;

    while (currIter != NULL)
    {
        prevIter = currIter;
        currIter = currIter->link;
        delete prevIter;
    }
    // delete whole table-array of linked list
    delete[] table;

    // set up others to 0 and NULL
    items = size = 0;
    head = NULL;
    table = NULL;
}

/**
 * @brief the bracket operator that performs the insert/find for
    the hash map,
 * @tparam t1
 * @tparam t2
 * @param key
 * @return t2&
 */
template <typename t1, typename t2>
t2 &hashMap<t1, t2>::operator[](t1 key)
{
    // create a var loadfactor to store the load factor by doing int to double
    double loadFactor = static_cast<double>(items / size);

    // if load >= 50 -> resize()
    if (loadFactor >= 0.50)
        resize();

    // Call the hash function and store
    int x = h(key);

    // check loc for table[x]
    while (true)
    {
        // if not exist
        if (table[x] == NULL)
        {
            // create entry in linkde list
            table[x] = new hashPair;
            table[x]->key = key;
            table[x]->value = t2();
            table[x]->link = NULL;

            // create iteratorPair for entry
            iteratorPair *tmp = new iteratorPair;
            tmp->key = &(table[x]->key);
            tmp->value = &(table[x]->value);
            tmp->link = NULL;

            // if head NULL -> empty linked list
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

            // ret elem
            return table[x]->value;
        }
        // if has entry
        else
        {
            int counter = 0;

            hashPair *hold = table[x];

            // check for NULL
            if (hold != NULL)
            {
                // if contain entry
                while (hold != NULL)
                {
                    // if key exist
                    if (hold->key == key)
                        return hold->value;

                    // count the elem in LL
                    counter++;

                    // if last elem
                    if (hold->link == NULL)
                        break;

                    // if not last -> go to next
                    hold = hold->link;
                }
            }

            // if >= 2 elem
            if (counter >= 2)
            {
                // update x and reset
                x = (x + 1) % size;
                counter = 0;
            }
            // if < 2
            else
            {
                // do 3 again
                // create new entry
                table[x]->link = new hashPair;
                table[x]->link->key = key;
                table[x]->link->value = t2();
                table[x]->link->link = NULL;

                // create iteratorPair for the entry
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

                // increment item
                items++;
                // ret value
                return table[x]->link->value;
            }
        }
    }
}

/**
 * @brief returns an iterator that
    points to the first node in the linked list
    that head points to
 * @tparam t1
 * @tparam t2
 * @return hashMap<t1, t2>::iterator
 */
template <typename t1, typename t2>
typename hashMap<t1, t2>::iterator hashMap<t1, t2>::begin() const
{
    iterator it(head);
    return it;
}

/**
 * @brief returns a null iterator
 *
 * @tparam t1
 * @tparam t2
 * @return hashMap<t1, t2>::iterator
 */
template <typename t1, typename t2>
typename hashMap<t1, t2>::iterator hashMap<t1, t2>::end() const
{
    iterator it;
    return it;
}

/**
 * @brief doubles the size of the hash table,
 * needs to remap all the elements
    from the original table to a larger table
 *
 * @tparam t1
 * @tparam t2
 */
template <typename t1, typename t2>
void hashMap<t1, t2>::resize()
{
    // keep old size and old table
    // and update new size + table
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

    // delete old iterator linked list
    iteratorPair *prevIter = NULL;
    iteratorPair *currIter = head;

    while (currIter != NULL)
    {
        prevIter = currIter;
        currIter = currIter->link;
        delete prevIter;
    }
}

/**
 * @brief hash function specific for when the key is of
    type std::string, this function adds up all the
    ASCII values of the string then mods it by the size
    and returns this value
 *
 * @tparam t1
 * @tparam t2
 * @param key
 * @return int
 */
template <typename t1, typename t2>
int hashMap<t1, t2>::h(std::string key) const
{
    int sum = 0;
    // loop to sum all ascii char
    for (int i = 0; i < key.length(); i++)
    {
        sum += key[i];
    }
    return sum % size;
}

/**
 * @brief Construct a new hash Map<t1, t2>::iterator::iterator object
 *
 * @tparam t1
 * @tparam t2
 */
template <typename t1, typename t2>
hashMap<t1, t2>::iterator::iterator()
{
    element = NULL;
}

/**
 * @brief Construct a new hash Map<t1, t2>::iterator::iterator object
 *
 * @tparam t1
 * @tparam t2
 * @param p
 */
template <typename t1, typename t2>
hashMap<t1, t2>::iterator::iterator(iteratorPair *p)
{
    element = p;
}

/**
 * @brief postfix operator that moves the iterator over to the next node in the linked list
 *
 * @tparam t1
 * @tparam t2
 * @return const hashMap<t1, t2>::iterator&
 */
template <typename t1, typename t2>
const typename hashMap<t1, t2>::iterator &hashMap<t1, t2>::iterator::operator++(int)
{
    element = element->link;
    return *this;
}

/**
 * @brief compares if two iterators point to the same node,
 * compares this->element with rhs.element, then
it returns true if they are the same address or false otherwise
 *
 * @tparam t1
 * @tparam t2
 * @param rhs
 * @return true
 * @return false
 */
template <typename t1, typename t2>
bool hashMap<t1, t2>::iterator::operator==(const hashMap<t1, t2>::iterator &rhs) const
{
    return (this->element) == (rhs.element);
}

/**
 * @brief compares if two iterators point to the same node,
 * compares this->element with rhs.element, then
it returns false if they are the same address or true otherwise
 *
 * @tparam t1
 * @tparam t2
 * @param rhs
 * @return true
 * @return false
 */
template <typename t1, typename t2>
bool hashMap<t1, t2>::iterator::operator!=(const hashMap<t1, t2>::iterator &rhs) const
{
    return (this->element) != (rhs.element);
}

/**
 * @brief eturns the key field of the node, since each node in the
linked list contains a pointer to a key in the existing table,
 *
 * @tparam t1
 * @tparam t2
 * @return t1
 */
template <typename t1, typename t2>
t1 hashMap<t1, t2>::iterator::first()
{
    return *(element->key);
}

/**
 * @brief eturns the value field of the node, since each node in
the linked list contains a pointer to a key in the existing table,
 *
 * @tparam t1
 * @tparam t2
 * @return t2
 */
template <typename t1, typename t2>
t2 hashMap<t1, t2>::iterator::second()
{
    return *(element->value);
}

#endif