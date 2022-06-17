#include "LL.h"

using namespace std;

int main(){
    LL<int > list;
    LL<int >:: iterator it;
    LL<int >:: iterator nil(NULL);
    int max;

    list.tailInsert (9);
    list.tailInsert (5);
    list.tailInsert (1);
    list.tailInsert (2);
    list.tailInsert (10);

    //print
    cout << "before: " << endl;
    it = list.begin();
    while (it != nil)
    {
        cout << *it << endl;
        it++;
    }

    LL<int>::iterator i, j, k;

    /*
    //case1 = when only 2 node
    i = list.begin();
    //i++;
    j = i;
    j++;
    list.swapNodes(i,j);
    */

    /*
    //case2: when A = head
    i = list.begin();
    j = i;
    j++;
    list.swapNodes(i,j);
    */

    /*
    //case3 when B = tail
    j = list.end();
    i = j;
    i--;
    list.swapNodes(i, j);
    */

    /*
    //case4: swap mid nodes;
    i = list.begin();
    i++;
    j = i;
    j++;
    list.swapNodes(i,j);
    */

    /*
    //test if node1 == nodeB
    i = list.begin();
    j = i;
    list.swapNodes(i,j);
    */

    /*bool swapped = true;
    k = NULL;
    i = list.begin();

    while(swapped == true){
        swapped = false;
        j = i;
        j++;
        while(i != NULL && j != NULL){
            if(*i > *j){
                list.swapNodes(i, j);
                swapped = true;
            }
            j++;
            i++;
        }
        i = list.begin();
    }*/

    i = list.end();

    while(i != list.begin()){
        j = list.begin();
        k = j;
        k++;
        while(k != NULL){
            if(*j > *k){
                list.swapNodes(j, k);
            }
            j++;
            k++;
        }
        i--;
    }

    //print
    cout << "after: " << endl;
    it = list.begin();
    while (it != nil)
    {
        cout << *it << " " << endl;
        it++;
    }
}