#include "hashMap.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    ifstream iFile;
    string file;
    string line;
    string line2;

    // process file
    // run until correct file
    do
    {
        cout << "Enter file name: ";
        cin >> file;

        iFile.open(file);

        if (!iFile.is_open())
        {
            cout << "Can't open file" << std::endl;
            cin.clear();
            cin.ignore(100, '\n');
        }
    } while (!iFile.is_open());

    // get data from file - testCase
    int testCases = 0, categories = 0, polls = 0;
    getline(iFile, line);
    testCases = stoi(line);

    // name - party
    hashMap<string, string> umap1;
    // name - times
    hashMap<string, int> umap2;
    // string for names of candidates
    vector<string> names;
    int max = 0;
    string winner = "";

    // loop each test case
    for (int i = 0; i < testCases; i++)
    {
        names.clear();
        // get data from file - category
        getline(iFile, line);
        categories = stoi(line);

        // get candidate & party
        for (int j = 0; j < categories; j++)
        {
            getline(iFile, line);
            getline(iFile, line2);

            // map candidate to party
            umap1[line] = line2;
            // reset umap2
            umap2[line] = 0;
        }

        // get number of votes
        getline(iFile, line);
        polls = stoi(line);

        // clear vector for next test case
        names.clear();

        // get polls
        for (int k = 0; k < polls; k++)
        {
            line.clear();
            getline(iFile, line);
            names.push_back(line);
        }

        // count duplicates
        for (int i = 0; i < names.size(); i++)
        {
            umap2[names[i]]++;
        }

        // find max and winner
        for (hashMap<string, int>::iterator i = umap2.begin(); i != umap2.end(); i++)
        {
            if (i.second() > max)
            {
                // update max and winner
                max = i.second();
                winner = i.first();
            }
        }

        // recheck again for multiple case
        int counter = 0;
        for (hashMap<string, int>::iterator i = umap2.begin(); i != umap2.end(); i++)
        {
            // if more than 1 winner
            if (max == i.second())
                counter++;

            // res
            if (counter == 1 && max == i.second())
                winner = i.first();
            if (counter > 1)
                winner = "tie";
        }

        // recheck
        for (hashMap<string, string>::iterator i = umap1.begin(); i != umap1.end(); i++)
        {
            if (i.first() == winner)
                winner = i.second();
        }

        cout << "Case " << i + 1 << " results: " << winner << endl;
    }

    return 0;
}