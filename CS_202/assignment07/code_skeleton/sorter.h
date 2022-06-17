#include <iostream>
#include <vector>
using namespace std;

//Notes: template will make this Sorter class accept any data types
template <class T>
class Sorter
{
private:
	vector<T> *list;
	vector<int> ids;

public:
	//T = List, i = id
	//because vector, so can use = to copy 
	/**Sorter- contrucstor of class Sorter
	 * vecotor<T> *l- vector of pointer type T which is can accept any type of data (Date or Transaction)
	 * vector<int> i = vector of ids 
	 */
	Sorter(vector<T> *l,vector<int> i){
		list = l;
		ids = i;
	}

	/**void sort- sorter function that sort the data
	 * return void
	 * Algorithm- using optimize bubble sort to sort the data
	 * 1= loop through the vector list and put flag to false to mark
	 * 2= loop through the vecotr but backward
	 * 3= if the current element = the next, then swap both vector and set flag to true
	 * 4= lastly, check for flag, if flag is not true, then break
	 */
	void sort(){
		for(unsigned int i = 0; i < list->size(); i++){
			bool flag = false;
			for(unsigned int j = 0; j < list->size() - 1 -i; j++){
				if(list->at(j) > list->at(j + 1)){
					T tempList = list->at(j);
					list->at(j) = list->at(j + 1);
					list->at(j+ 1) = tempList;

					int tempIds = ids[j];
					ids[j] = ids[j+1];
					ids[j+1] = tempIds;
					flag = true;
				}
			}
			if(!flag){
				break;
			}
		}
	}

	/**vector<T> * getListVector() - get data from list vector
	 * return vector list
	 */
	vector<T> * getListVector(){
		return list;
	}

	/**vector<int>  getIdsVector()- get data from ids vector
	 * return vec ids
	 */
	vector<int>  getIdsVector(){
		return ids;
	}

};
