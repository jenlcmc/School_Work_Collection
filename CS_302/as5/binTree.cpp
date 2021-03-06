#include "binTree.h"

/**
 * @brief Construct a new bin Tree::bin Tree object
 * @description default constructor that sets the root with NULL
 */
binTree::binTree()
{
    root = NULL;
}

/**
 * @brief Construct a new bin Tree::bin Tree object
 *  @description constructor that takes in a vector of apples
 * first allocate a node to the root, and set its apple with apples[0],
 * set the rest of the fields of the root node + call the function buildTree
 * and pass root node, the vector of apples, and the initial index 0
 * @param apples
 */
binTree::binTree(vector<bool> apples)
{
    // make new node
    root = new binTreeNode;
    // inti root
    root->apple = apples[0];
    root->left = root->right = NULL;

    buildTree(root, apples, 0);
}

/**
 * @brief Destroy the bin Tree::bin Tree object
 * @description call destroyTree(root)
 */
binTree::~binTree()
{
    destroyTree(root);
}

/**
 * @brief contains return minTime(root, 0)
 *
 */
int binTree::minTime()
{
    return minTime(root, 0);
}

/**
 * @brief function that deallocates a binary tree rooted at
 * node r, deallocates the left subtree, then the right subtree,
 * then deallocates r
 * @param r
 */
void binTree::destroyTree(binTreeNode *r)
{
    // delete until NULL
    if (r != NULL)
    {
        // call recursive to delete each side
        destroyTree(r->left);
        destroyTree(r->right);

        r->left = r->right = NULL;
        delete r;
        r = NULL;
    }
}

/**
 * @brief compute the left index and right index given index i,
 * and then possibly build a left and right child,
 * assign the value from apples vector to the left and right child node
 * and the recursively build the left and right side
 * @param r - root
 * @param apples - vector of apple to build
 * @param i - index to indicate element
 */
void binTree::buildTree(binTreeNode *r, vector<bool> apples, int i)
{
    // compute index to determine which element go left/right
    int leftPos = (i * 2) + 1;
    int rightPos = (i * 2) + 2;

    // build until the compute value/index >= size of vec
    if (leftPos < apples.size() || rightPos < apples.size())
    {
        // set up left node
        r->left = new binTreeNode;
        // put elem from vec to apple
        r->left->apple = apples[leftPos];
        // make sure the left & right == NULL prepare for next node
        r->left->left = r->left->right = NULL;
        // recursive call
        buildTree(r->left, apples, leftPos);

        // same thing as left side/above
        r->right = new binTreeNode;
        r->right->apple = apples[rightPos];
        r->right->right = r->right->left = NULL;
        buildTree(r->right, apples, rightPos);
    }
}

/**
 * @brief counts the minimal amount of moves
 * needed to retrieve all the red apples
 * in the binary tree staring from the root.
 * Every forward move to a child causes the time to increment by 1,
 * every movement back to its parent also increments time by 1,
 * if a path leads to a leaf where no red apples where found along the way,
 * then you do not want to maintain those time counts.
 * @param r - root
 * @param time - count time to get red apples
 * @return int - time to get apples
 */
int binTree::minTime(binTreeNode *r, int time)
{
    // local variables for the function
    int leftPath = 0;
    int rightPath = 0;
    int tmp = 0;

    // base case -> tree has nothing
    if (r == NULL)
    {
        return 0;
    }

    // leaf nodes case
    if (r->left == NULL && r->right == NULL)
    {
        // if go to leaf + no apple -> return 0
        if (r->apple == false)
            return 0;
        // yes -> count the time
        return time * 2;
    }

    // internal node case
    if (r->left != NULL && r->right != NULL)
    {
        // if find internal -> hold the value in tmp for future
        if (r->apple == true)
            tmp += time * 2;

        // recursive call left & right
        leftPath = minTime(r->left, time + 1);
        rightPath = minTime(r->right, time + 1);

        // case in which internal & leaf nodes in same path
        if (tmp != 0 && leftPath > 0 && rightPath > 0)
        {
            return leftPath + rightPath - tmp;
        }

        // when opposite tree contain more than 1 inner node
        if (tmp != 0 && leftPath > 0 && rightPath == 0)
        {
            return leftPath + rightPath;
        }

        // case in which internal & leaf nodes in same path
        //  but there are more than 1 internal nodes
        if (leftPath == rightPath && leftPath != 0 && rightPath != 0)
        {
            return rightPath + leftPath - time * 2;
        }
    }

    // case in which apples in different side of tree
    return leftPath + rightPath + tmp;
}