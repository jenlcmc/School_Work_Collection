#include <string>
#include <iostream>
#include <fstream>

template <typename t1, typename t2>
class hashMap // we're using separate chaining & linear probing
{

public:
    struct hashPair // each element in the hash map, NODE in linked list that contains entry
    // linked lists can have at most 2 nodes
    // if we have 2 nodes in the linked lists and we don't find the search value,
    // we must linear probe to the next elemnent in our table
    {
        t1 key; // search key
        t2 value;
        hashPair *link; // pointer that points to another entry in the linked list
    };

    struct iteratorPair
    {
        // stores KEYS & VALUES in a separate linked list
        // allows us to cycle through them in main
        t1 *key;   // doesn't contain an actual key, contains a pointer that points to a key field within a node in the hash table's linked lsit
        t2 *value; //^^ but for value
        iteratorPair *link;
    };

    class iterator
    {
    public:
        friend class hashMap;
        iterator()
        {
            element = NULL;
        };
        const iterator &operator++(int)
        {
            element = element->link;
            return *this;
        }; // moves element over to the next linked list

        // element = element -> link, return *this
        bool operator==(const iterator &rhs) const
        {
            if (this->element == rhs.element)
                return true;
            else
                return false;
        };
        // compare element with rhs.element
        bool operator!=(const iterator &rhs) const
        {
            if (this->element != rhs.element)
                return true;
            else
                return false;
        };

        t1 first() // returns key field
        {
            return *(element->key);
        };

        t2 second() // returns value field
        {
            return *(element->value);
        };

    private:
        iterator(iteratorPair *p)
        {
            element = p;
        };
        iteratorPair *element;
    };

    hashMap()
    {
        size = 5;
        items = 0;
        head = NULL;

        table = new hashPair *[size];

        for (int i = 0; i < size; i++)
            table[i] = NULL;
    };

    ~hashMap()
    {
        for (int i = 0; i < size; i++)
        {
            if (table[i] != NULL)
            {
                hashPair *headNode = table[i];
                headNode = headNode->link;
                hashPair *i = headNode;

                if (headNode->link == NULL)
                {
                    delete headNode;
                }

                else if (headNode != NULL)
                {
                    while (headNode != NULL)
                    {
                        i = headNode; // continue deallocating the nodes
                        headNode = headNode->link;
                        delete i;
                    }
                }
                i = NULL;
                headNode = NULL;
            }
        }

        // deallocate the hash table
        delete[] table;
        table = NULL;

        // deallocate head pointer
        if (head->link == NULL) // if there is only one node
        {
            delete head;
            head = NULL;
        }

        if (head != NULL) // if there are nodes contained within the linked list
        {
            iteratorPair *del; // use this pointer to traverse through the linked list

            del = head;        // point to the head
            head = head->link; // move the head pointer to the next node
            delete del;        // deallocate the current node being pointed to

            while (head != NULL) // while the head pointer is not yet complete...
            {
                del = head; // continue deallocating the nodes
                head = head->link;
                delete del;
            }

            del = NULL; // at the end, set the pointer to NULL
        }
    };

    t2 &operator[](t1 key)
    {
        double sizeD = static_cast<double>(size);

        if (items / sizeD >= 0.5)
            resize();

        int x = h(key);

        hashPair *i = table[x];

        if (table[x] == NULL) // no node exists
        {
            table[x] = new hashPair;

            table[x]->key = key;
            table[x]->value = t2();
            table[x]->link = NULL;

            // table[x] = i;

            // iteratorPair *ins;
            // iteratorPair *j = head;
            // ins = new iteratorPair;

            if (head == NULL)
            {
                head = new iteratorPair;
                head->key = &(table[x]->key);
                head->value = &(table[x]->value);
                // j = NULL;
            }
            else
            {
                // maybe use loop to find last element
                // then insert new elem
            }

            /*else if (head->link == NULL) // if only one node exists
            {
                head->link = ins; // add the secondary node
                ins->key = &(table[x]->key);
                ins->value = &(table[x]->value);
            }

            else // if there are 2+ nodes in the linked list
            {
                while (j->link != NULL)
                    j = j->link;

                j->link = ins; // add the node at the end of the list
                ins->link = NULL;
                ins->key = &(table[x]->key);
                ins->value = &(table[x]->value);
            }*/

            return table[x]->value;
        }
        else
        {
            while (x < size)
            {
                if (table[x] != NULL)
                {
                    i = i->link;

                    if (i->key == key) // first node
                        return i->value;

                    else if (i->link == NULL) // make second node
                    {
                        hashPair *h;
                        h = i;

                        i = i->link;
                        i = new hashPair;
                        i->key = key;
                        i->value = t2();

                        h->link = i;
                        items++;

                        iteratorPair *j = head;

                        if (head == NULL)
                        {
                            j = new iteratorPair;
                            j->key = &(i->key);
                            j->value = &(i->value);
                        }

                        else if (head != NULL)
                        {
                            while (j != NULL)
                            {
                                j = j->link;
                            }

                            j = new iteratorPair;
                            j->key = &(i->key);
                            j->value = &(i->value);
                        }
                    }

                    else if (i->link != NULL) // check second node
                    {
                        i = i->link;

                        if (i->key == key)
                            return i->value;
                        else
                            x = (x + 1) % size;
                    }
                }
            }
        }
    };

    iterator begin() const
    {
        iteratorPair *it = head;
        return it;
    };
    iterator end() const
    {
        iteratorPair *it = NULL;
        return it;
    };

private:
    void resize()
    {
        double sizeD = static_cast<double>(size);

        if (items / sizeD >= 0.5)
        {
            size = size * 2;

            hashPair **oldTable = table;
            table = new hashPair *[size];

            // deallocate head linked list first
            if (head->link == NULL) // if there is only one node
            {
                delete head;
                head = NULL;
            }

            if (head != NULL) // if there are nodes contained within the linked list
            {
                iteratorPair *del; // use this pointer to traverse through the linked list

                del = head;        // point to the head
                head = head->link; // move the head pointer to the next node
                delete del;        // deallocate the current node being pointed to

                while (head != NULL) // while the head pointer is not yet complete...
                {
                    del = head; // continue deallocating the nodes
                    head = head->link;
                    delete del;
                }

                del = NULL; // at the end, set the pointer to NULL
            }

            int x = 0;

            while (x < size)
            {
                hashPair *i = table[x];

                if (i->link != NULL)
                {
                    i = i->link;
                    (*this)[i->key] = i->value;

                    i = i->link;

                    if (i != NULL)
                        (*this)[i->key] = i->value;
                    else
                        x = (x + 1) % size;
                }

                else
                    x = (x + 1) % size;

                // deallocate the old table
                for (int i = 0; i < size; i++)
                {
                    if (oldTable[i]->link != NULL)
                    {

                        for (int i = 0; i < size; i++)
                        {
                            if (oldTable[i]->link != NULL)
                            {
                                hashPair *pointer = oldTable[i]->link;
                                for (int j = 0; j < 2; j++)
                                {
                                    pointer = NULL;
                                }
                            }
                        }
                    }
                }

                // deallocate the hash table
                delete[] oldTable;
                oldTable = NULL;
            }
        }
    };
    int h(std::string str) const
    {
        int sum;

        for (int i = 0; str[i] != '\0'; i++)
            sum = sum + str[i];

        sum = sum % size;

        return sum;
    };
    int items;
    int size;
    hashPair **table;
    iteratorPair *head;
};

int main()
{
    hashMap<std::string, int> example;

    example["cat"] = 1;
    example["camel"] = 2;

    return 0;
}