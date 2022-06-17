/*
    * Descriptions: Implement of bubble sort using doubly linked list
    * Input: File contains list of numbers
    * Output: Sort list of numbers from the file

*/

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <list>
#include <algorithm>
#include <unordered_map>
#include <map>

using namespace std;

/**
 * @brief DFS algorithm that find all ancestors for a Node. The function will start with node that
 * has no ancestors and will go through all the nodes and find all the ancestors by recursive DFS
 * and transverse through nerighbor to find other nodes that has ancestors.
 * When find, it will add to unordered_map of ancestors.
 *
 * @param current - current node to traverse
 * @param searchName - name of the search node
 * @param adjList - unordered_map of adjacency list-neighbor nodes
 * @param visited - unordered_map of visited nodes
 * @param listOfAncrstors - unordered_map of ancestors
 * @param AncestorPaths - possible numbers of path to find a node
 * @return true
 * @return false
 */
bool ancestors(string current, string searchName, unordered_map<string, list<string>> adjList,
               unordered_map<string, bool> &visited, unordered_map<string, bool> &listOfAncrstors,
               map<string, int> &AncestorPaths)
{
    // if find -> return true
    // flag to determine to stop or not
    bool res = false;
    if (current == searchName)
        return true;

    // mark as visit
    visited[current] = true;

    // search list of adjacency list to find ancestors
    for (auto &adj : adjList[current])
    {
        // limit to check for paths
        if (AncestorPaths[current] >= -10)
        {
            visited[current] = false;
        }
        // if not visit -> visit
        if (!visited[adj])
        {
            AncestorPaths[current]--;
            // recursive for ancestors
            if (ancestors(adj, searchName, adjList, visited, listOfAncrstors, AncestorPaths))
            {
                // if find -> set that true in the list of ancestors & return
                listOfAncrstors[current] = true;
                // should not return as it will stop find other paths
                //  return true;
                res = true;
            }
        }
    }
    return res;
}

int main()
{
    // set up open file
    string file;
    cout << "Enter file: ";
    cin >> file;

    ifstream in(file);

    // set up parse string
    string line;
    string delim = " -> ";
    size_t pos = 0;
    vector<string> inputs;
    vector<string> from;
    vector<string> to;

    // parse whole string
    while (getline(in, line))
    {
        inputs.push_back(line);
    }

    // parse string to put it into parent & children vector
    for (int i = 0; i < inputs.size(); i++)
    {
        while ((pos = inputs[i].find(delim)) != string::npos)
        {
            from.push_back(inputs[i].substr(0, pos));
            to.push_back(inputs[i].substr(pos + delim.length()));
            inputs[i].erase(0, pos + delim.length());
        }
    }

    // set up adjList
    unordered_map<string, list<string>> adjList;

    for (int i = 0; i < from.size(); ++i)
    {
        adjList[from[i]].push_back(to[i]);
    }

    // clear to set up inputs again
    inputs.clear();

    // merge 2 vectors and erase duplicates to have list of strings to find
    inputs.resize(from.size() + to.size());
    merge(from.begin(), from.end(), to.begin(), to.end(), inputs.begin());

    sort(inputs.begin(), inputs.end());
    inputs.erase(unique(inputs.begin(), inputs.end()), inputs.end());

    // vectors to store parent & children + filter it
    vector<string> noAncestors;
    vector<string> fromTmp;
    vector<string> toTmp;

    fromTmp = from;
    toTmp = to;

    // to find list of string that has no ancestors
    sort(fromTmp.begin(), fromTmp.end());
    sort(toTmp.begin(), toTmp.end());
    fromTmp.erase(unique(fromTmp.begin(), fromTmp.end()), fromTmp.end());
    toTmp.erase(unique(toTmp.begin(), toTmp.end()), toTmp.end());

    // find no ancestors
    set_difference(fromTmp.begin(), fromTmp.end(), toTmp.begin(), toTmp.end(), back_inserter(noAncestors));

    // set up map for how many possible path we could do
    map<string, int> AncestorPaths;
    if (noAncestors.size() <= 1)
    {
        for (int i = 0; i < inputs.size(); i++)
        {
            string name = inputs[i];
            int size = adjList[name].size();
            AncestorPaths[name] = size;
        }
    }

    // set up loop to call dfs
    unordered_map<string, bool> visited;
    unordered_map<string, bool> listOfAncrstors;
    map<string, list<string>> ans;

    // set all of the visited into false
    for (int i = 0; i < inputs.size(); i++)
    {
        visited[inputs[i]] = false;
    }

    // using function ancestors, output a sorted list of all ancestors
    // for each person (if a person has no ancestors then output "None" without the quotes).
    // The list should be sorted in alphabetical order.

    for (int i = 0; i < inputs.size(); i++)
    {
        for (int j = 0; j < noAncestors.size(); j++)
        {
            if (ancestors(noAncestors[j], inputs[i], adjList, visited, listOfAncrstors, AncestorPaths))
            {
                // cout << inputs[i] << ": ";
                //  set up so in case we have only 1 node that has no ancestors
                ans[noAncestors[j]].push_back("None");
                for (auto &anc : listOfAncrstors)
                {
                    // cout << anc.first << " ";
                    ans[inputs[i]].push_back(anc.first);
                }
                // cout << endl;
            }
            else
            {
                // cout << inputs[i] << ": None" << endl;
                ans[inputs[i]].push_back("None");
            }
            listOfAncrstors.clear();
            visited.clear();
        }
    }

    // print answers
    cout << endl;
    for (auto &res : ans)
    {
        cout << "Relative Name: " << res.first << endl;
        cout << "List of ancestors" << endl;

        // sort + remove duplicate & none string
        res.second.sort();
        res.second.unique();
        res.second.remove("None");

        // if it empty -> have no ancestors
        if (res.second.empty())
        {
            cout << "None" << endl;
        }

        // if yes -> loop to print ancestors
        for (auto &adj : res.second)
        {
            cout << adj << endl;
        }
        cout << endl;
    }

    return 0;
}