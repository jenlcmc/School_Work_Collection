#ifndef PRIOQ_H
#define PRIOQ_H

#include <string>
#include <vector>
#include <iostream>
using namespace std;

struct stockType
{
    std::string name;
    int timesPurchased;
    double dividend;
    double price;
    /**
     * @brief The operator will be needed
    for comparison to maintain a priority queue of available stocks
    (so we pick the next best available stock).
    The operator will allow the priority queue determine which stock has the higher priority.
    Between any two stocks, the stock with the higher priority will be
    1. The stock with the cheapest price has the higher priority
    2. If the prices are the same, the stock that was purchased more has the higher priority
    3. If the amount of times purchased is the same, the stock with larger dividend has the higher priority
    4. If the dividend amount is the same, the stock that would go earlier in the alphabet has the higher
    priority
     *
     * @param rhs
     * @return true
     * @return false
     */
    bool operator>(const stockType &rhs)
    {
        if (this->price != rhs.price)
            return this->price > rhs.price;

        if (this->price != rhs.price)
            return this->timesPurchased > rhs.timesPurchased;

        if (this->timesPurchased != rhs.timesPurchased)
            return this->dividend > rhs.dividend;

        if (this->dividend != rhs.dividend)
            return this->name > rhs.name;

        return this->name > rhs.name;
    }
};

template <class Type>
class priorityQ
{
public:
    priorityQ(int = 10);

    priorityQ(vector<Type>);
    priorityQ(const priorityQ<Type> &);
    ~priorityQ();
    const priorityQ<Type> &operator=(const priorityQ<Type> &);
    void insert(Type);
    void deletePriority();
    Type getPriority() const;
    bool isEmpty() const;
    void bubbleUp(int);
    void bubbleDown(int);
    int getSize() const;

private:
    int capacity;
    int size;
    Type *heapArray;
    /**
     * @brief Get the Parent object
     *
     * @param index
     * @return int
     */
    int getParent(int index)
    {
        int parent = 0;
        if (index < capacity && index > 1)
            parent = index / 2;

        return parent;
    }

    /**
     * @brief Get the Left object
     *
     * @param index
     * @return int
     */
    int getLeft(int index)
    {
        int leftChild = 0;

        if (((2 * index) < capacity) && index >= 1)
            leftChild = 2 * index;

        return leftChild;
    }

    /**
     * @brief Get the Right object
     *
     * @param index
     * @return int
     */
    int getRight(int index)
    {
        int rightChild = 0;

        if (((2 * index + 1) < capacity) && index >= 1)
            rightChild = 2 * index + 1;

        return rightChild;
    }
};

/**
 * @brief Construct a new priority Q<Type>::priority Q object
 *
 * @tparam Type
 * @param cap
 */
template <class Type>
priorityQ<Type>::priorityQ(int cap)
{
    capacity = cap;
    size = 0;
    heapArray = new Type[capacity];
}

/**
 * @brief Construct a new priority Q<Type>::priority Q object
 *
 * @tparam Type
 * @param v
 */
template <class Type>
priorityQ<Type>::priorityQ(vector<Type> v)
{
    capacity = v.size() + 1;
    size = capacity;
    heapArray = new Type[capacity];

    // assign vec to heap
    for (int i = 0; i < v.size(); i++)
    {
        heapArray[i + 1] = v[i];
    }

    // build heap
    for (int i = size - 1; i > 0; i--)
    {
        bubbleDown(i);
    }
}

/**
 * @brief Construct a new priority Q<Type>::priority Q object (copy)
 *
 * @tparam Type
 * @param copy
 */
template <class Type>
priorityQ<Type>::priorityQ(const priorityQ<Type> &copy)
{
    capacity = copy.capacity;
    size = copy.size;

    for (int i = 1; i <= size + 1; i++)
        heapArray[i] = copy[i];

    for (int i = size - 1; i > 0; i--)
        bubbleDown(i);
}

/**
 * @brief Destroy the priority Q<Type>::priority Q object
 *
 * @tparam Type
 */
template <class Type>
priorityQ<Type>::~priorityQ()
{
    delete[] heapArray;
    size = 0;
    capacity = 0;
}

/**
 * @brief assign operator
 *
 * @tparam Type
 * @param rhs
 * @return const priorityQ<Type>&
 */
template <class Type>
const priorityQ<Type> &priorityQ<Type>::operator=(const priorityQ<Type> &rhs)
{
    if (this != rhs)
    {
        // clear heap array
        delete[] heapArray;
        capacity = rhs.capacity;
        size = rhs.size;

        for (int i = 1; i <= size; i++)
            heapArray[i] = rhs[i];

        for (int i = size; i >= 0; i--)
            bubbleDown(i);
    }
    return *this;
}

/**
 * @brief assigns the item to the back of the heapArray (size
denotes the back of the heap array), increments size
and then bubbles up the element (must double
the size of the heapArray if maxed out
 *
 * @tparam Type
 * @param item
 */
template <class Type>
void priorityQ<Type>::insert(Type item)
{
    // if nothing there
    if (isEmpty())
    {
        size++;
        heapArray[size] = item;
    }
    // if not empty -> find last elem to insert at the end
    else
    {
        // if maxed out -> double the size
        if (size >= capacity)
        {
            capacity = capacity * 2;
            Type *tmp = heapArray;
            heapArray = new Type[capacity];

            for (int i = 1; i < size; i++)
            {
                heapArray[i] = tmp[i];
            }
            delete[] tmp;

            // find last node to insert
            size++;
            heapArray[size] = item;
            bubbleUp(size);
        }
        else
        {
            // find last node to insert
            size++;
            heapArray[size] = item;
            bubbleUp(size);
        }
    }
}

/**
 * @brief overwrites the root with the last element in the heap,
decrements the size by 1, and then bubbles down the element
 *
 * @tparam Type
 */
template <class Type>
void priorityQ<Type>::deletePriority()
{
    if (!isEmpty())
    {
        heapArray[1] = heapArray[size - 1];
        size--;
        bubbleDown(1);
    }
}

/**
 * @brief returns the root item
 *
 * @tparam Type
 * @return Type
 */
template <class Type>
Type priorityQ<Type>::getPriority() const
{
    return heapArray[1];
}

/**
 * @brief returns true if the heap is empty and false otherwise,
the value of size will tell you if the heap is empty or not
 *
 * @tparam Type
 * @return true
 * @return false
 */
template <class Type>
bool priorityQ<Type>::isEmpty() const
{
    return size == 0;
}

/**
 * @brief bubbles up the element at heapArray[index], com-
pares the item with its parent and swaps heapArray[index]
with its parent if violates heap order,
continues this as long as the heap order is not maintained
 *
 * @tparam Type
 * @param index
 */
template <class Type>
void priorityQ<Type>::bubbleUp(int index)
{
    // base case
    if (size == 0 || heapArray[getParent(index)] > heapArray[index])
        return;
    // condition to loop and swap
    while (index > 0 && heapArray[index] < heapArray[getParent(index)])
    {
        // swap
        Type temp = heapArray[index];
        heapArray[index] = heapArray[getParent(index)];
        heapArray[getParent(index)] = temp;
        // update index
        index = getParent(index);
    }
}

/**
 * @brief bubbles down the element at heapArray[index]
with one of its children (larger or smaller child),
 swaps heapArray[index] with the left or right child
and continues this process as long as the array is not in heap order
 *
 * @tparam Type
 * @param index
 */
template <class Type>
void priorityQ<Type>::bubbleDown(int index)
{
    // get index
    int leftChild = getLeft(index);
    int rightChild = getRight(index);
    int minPos = index;

    /*if (leftChild >= size || rightChild >= size)
        return;*/

    // find where is the smallest
    if (leftChild > 0 && leftChild <= size && heapArray[minPos] > heapArray[leftChild])
    {
        minPos = leftChild;
    }

    if (rightChild > 0 && rightChild <= size && heapArray[minPos] > heapArray[rightChild])
    {
        minPos = rightChild;
    }

    // if smallest is not the given index -> swap
    if (minPos != index)
    {
        Type tmp = heapArray[index];
        heapArray[index] = heapArray[minPos];
        heapArray[minPos] = tmp;

        bubbleDown(minPos);
    }
}

/**
 * @brief returns the amount of elements in the heap array
 *
 * @tparam Type
 * @return int
 */
template <class Type>
int priorityQ<Type>::getSize() const
{
    return size;
}
#endif