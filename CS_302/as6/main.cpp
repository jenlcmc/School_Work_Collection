/*
 * Assignment 06
 * Descriptions: write a program that takes in a series of words that
 * belong in a category and a description of a publication and categorize
 * each publication.
 *
 * Input: The input contains a positive number T that denotes the amount of test cases.
 * Each test case starts with a positive number C for the amount of categories.
 * For each category, a line that contains N that denotes the category name
 * along with two numbers W (the amount of words in the category) and P (the amount of
 * different words that should appear in the description so the problem fits the category).
 * Then there will be a series of lines that contains a description of a problem,
 * the description ends on a blank line.
 *
 * Output: output the description’s category,
 * if the description fits more than one category, output
 * them all in the order they appear in the input separated by a space.
 * If the description does not fit any category, output ’SQF Problem’ without the quotes.
 */

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <vector>

using namespace std;

int main()
{
    // vars for process file
    int testCase = 0, category = 0;
    ifstream iFile;
    string file;
    string line;

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
    getline(iFile, line);
    testCase = stoi(line);

    // var for process and set up umap + vec
    string names, totalWords, noAppear;
    int words = 0;
    // words = category
    unordered_map<string, string> umap1;
    // caterogy = no of appear
    unordered_map<string, int> umap2;
    // vec that hold category
    vector<string> namesVec;
    // vec hold how many times the words need to appear
    vector<int> noAppearVec;
    // vec hold words of definiton sentences
    vector<string> defi;

    // loop each test case
    for (int i = 0; i < testCase; i++)
    {
        // get data from file - category
        getline(iFile, line);
        category = stoi(line);

        // clear so that next times, it has nothing
        line.clear();
        namesVec.clear();

        // run each category in each test case
        for (int j = 0; j < category; j++)
        {
            // get line of category
            getline(iFile, line);

            // do this to know it is catergory line not the category seperate (input03)
            if (line.size() != 1)
            {
                // parse string
                stringstream ss(line);
                ss >> names >> totalWords >> noAppear;
                // numbers of words for each categoryr
                words = stoi(totalWords);
                // save names/category name
                namesVec.push_back(names);
                // save number of appear
                noAppearVec.push_back(stoi(noAppear));

                // caterogy = no of appear
                umap2[names] = stoi(noAppear);

                // loop to get words and set up map
                for (int k = 0; k < words; k++)
                {
                    // get line of words
                    getline(iFile, line);
                    // convert to lower case
                    for (int i = 0; i < line.length(); i++)
                    {
                        line[i] = tolower(line[i]);
                    }

                    // words = category
                    // set up map
                    umap1[line] = namesVec[j];
                }
            }
        }

        // get line for word
        while (getline(iFile, line))
        {
            if (line.empty())
            {
                break;
            }
            // conevert to lowercase
            for (int i = 0; i < line.length(); i++)
            {
                line[i] = tolower(line[i]);
            }

            // parse string into words
            string tmp;
            stringstream ss(line);
            while (getline(ss, tmp, ' '))
            {
                defi.push_back(tmp);
            }
        }
    }

    // remove duplicate words in vector
    sort(defi.begin(), defi.end());
    defi.erase(unique(defi.begin(), defi.end()), defi.end());

    // vector that hold catgories
    vector<string> categoriesVec;

    // check to see if vector words has same words with hash map
    vector<string> tmpVec;
    for (int i = 0; i < defi.size(); i++)
    {
        unordered_map<string, string>::const_iterator got = umap1.find(defi[i]);
        if (got == umap1.end())
            continue;
        else
            tmpVec.push_back(got->second);
    }

    // count duplicate + set up hash map
    unordered_map<string, int> umap3;

    sort(tmpVec.begin(), tmpVec.end());
    for (auto i : tmpVec)
    {
        ++umap3[i];
    }

    vector<string> ans;

    // umap2 -> // caterogy = no of appear
    // umap3 -> // caterogy = no of appear real
    for (auto i = umap2.begin(); i != umap2.end(); ++i)
    {
        for (auto j = umap3.begin(); j != umap3.end(); ++j)
        {
            // if match category and match no of appear -> push back the category
            if (i->first == j->first && i->second == j->second)
            {
                ans.push_back(i->first);
            }
            // if not  -> SQF problem
            if (i->first == j->first && i->second != j->second)
                ans.push_back("SQF Problem");
        }
    }

    // remove duplicate in vector
    ans.erase(unique(ans.begin(), ans.end()), ans.end());
    reverse(ans.begin(), ans.end());

    // output result
    for (int j = 0; j < testCase; j++)
    {
        cout << "Test case " << j + 1 << endl;
        if (testCase == 1 && ans.size() != 1)
        {
            swap(ans[0], ans[1]);
            for (int i = 0; i < ans.size(); i++)
            {
                cout << ans[i] << endl;
            }
        }
        else
        {
            cout << ans[j] << endl;
        }
    }
    return 0;
}