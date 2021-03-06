#ifndef BINTREE_H
#define BINTREE_H

#include <iostream>
#include <vector>
#include <string>

// std that uses in program
using std::cout;
using std::endl;
using std::string;
using std::vector;

class binTree
{
public:
    struct binTreeNode
    {
        bool apple;
        binTreeNode *left;
        binTreeNode *right;
    };
    binTree();
    binTree(std::vector<bool>);
    ~binTree();
    int minTime();

private:
    void destroyTree(binTreeNode *);
    void buildTree(binTreeNode *r, std::vector<bool>, int);
    int minTime(binTreeNode *r, int);
    binTreeNode *root;
};

#endif
