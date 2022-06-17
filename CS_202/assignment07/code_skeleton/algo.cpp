#include <vector>
#include <iostream>
using namespace std;

template <class T>
int findModeTransaction(vector<T> records,vector<int>  ids) //what does the ids vector have to do with this?
{
    /**You just have to check the day of the transaction. 
    *because vector<T> is template, so it would be mean that records can be either Date or price
    *then what does it mean that we will check day and price? Like do i have to create temp object?
    * Anyday that gets the most transactions should be returned. 
    * == operator for the date object hasbeen overloaded to check if two transaction happened on the same day. 
    * For this one, == operator, we will have to check it after we find the mode or inside the loop when we find mode?
    *Similarly, mode ofthe product price means the price which has occurred the most
    *Print the content of vector //when it say this, are we supposed to print out the content of vec records or ids?
     */
    //pseudo code .... check code 
	int mode = 0;
    int max = 0;
    int count = 0;
    int current = 0;

    for(unsigned int i = 0; i < records.size(); i++){
        current = records.at(i); // .at because it's vector<T> *
        count = 1; //read one value/marking

        for(unsigned int j = i + 1; j < records.size(); j++){ //this check the next num
            if(records.at(j) == current){ //if the number we check (next one) is same with current
                count++; //add it
            }
        }
        if(count >= max){ //if last element is the one most occur
            max = count; 
            mode = current; //the mode will be the current one
        }
    }
	
	return mode;


}