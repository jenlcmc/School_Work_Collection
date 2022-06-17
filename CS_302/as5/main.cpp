#include "binTree.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

int main()
{
    std::string filename, redApple;
    std::vector<bool> apples;
    std::ifstream infile;

    std::cout << "Enter apple tree file: ";
    std::cin >> filename;

    infile.open(filename);

    infile >> redApple;

    while (!infile.eof())
    {
        apples.push_back(redApple == "True" ? true : false);

        infile >> redApple;
    }

    infile.close();

    binTree appleTree(apples);

    std::cout
        << "Minimum Time Needed: " << appleTree.minTime() << std::endl;

    return 0;
}