#include <iostream>
#include <set>
using namespace std;

class archipelago
{
private:
	char ** islands;
	int rows;
	int columns;
	char type;

	int navR[5];
	int navC[5];

	int navigate(char** &,int, int); 
	bool isSafe(int,int) const;

public:
	archipelago(char[],int,int,char);
	~archipelago(); //extra destructor
	void showIslands(int,int) const;
	int islandsCount(char **);

	char ** getGrid() const;

	void changeColor(char,int,int);

	bool sameIsland(archipelago&,archipelago&);
	



};

/*Constructor
*char colors[] - pass color to the variable
int r - passed row
int c - passed column
char t - type, either land or water
Algorithm- set all the value to private variables
also allocate islands char variable and then populate it with color
and assign values to nav array
*/
archipelago::archipelago(char colors[],int r,int c,char t)
{
	
	//setter
	rows = r;
	columns = c;
	type = t;
	
	//allocate a dynamic 2d array
	islands = new char*[r];
	for( int i = 0; i < r; i++){
		islands[i] = new char[c];
	}

	//populate
	int index = 0;
	for(int i = 0; i < r; i ++){
		for(int j = 0 ; j < c; j++){
			islands[i][j] = colors[index];
			index++;
		}
	}
	navC[0] = 0;
	navC[1] = 1;
	navC[2] = -1;
	navC[3] = 0;
	navC[4] = 0;

	navR[0] = 0;
	navR[1] = 0;
	navR[2] = 0;
	navR[3] = 1;
	navR[4] = -1;
}

// extra destructor
//Algorithm- use to delete 2d array and assign to null
archipelago::~archipelago(){
	for(int i = 0; i < rows; i++){
	delete[] islands[i];
	}
	delete[] islands;
	islands = NULL;
	
}
/*Function to print the content of an archipelago*/
void archipelago::showIslands(int r,int c) const
{
	//cout <<"The island is:"<<endl;
	if(r<rows)
	{
		if(c<columns)
		{
			cout <<islands[r][c]<<" ";
			showIslands(r,++c);
			return;
		}
		cout <<endl;
		showIslands(++r,0);
	}

}

/*Function to make a deep copy of the archipelago grid*/
char** archipelago:: getGrid() const
{
	
	char ** grid=new char *[rows];

	for(int row=0;row<rows;row++)
		grid[row]=new char[columns];

	for(int row=0;row<rows;row++)
	{
		for(int col=0;col<columns;col++)
		{
			grid[row][col]=islands[row][col];
		}
	}

	return grid;

}

/*Function to count the total number of islands in an
archipelago*/
int archipelago::islandsCount(char ** grid)
{
	int totalIslands=0;
	for(int row=0;row<rows;row++)
	{
		for(int col=0;col<columns;col++)
		{
			if(grid[row][col]==type)
				totalIslands+=navigate(grid,row,col);
		}
	}
	return totalIslands;
}
/*Function to navigate the island starting from a position
row and col
char ** &grid- grid of the 2d array
int row- starting point
int col- starting point
return 1 for correct and 0 for fail
Algorithm- check the base case and see if it's safe or not
if safe, then loop so that it do 5 navigate
check to see if the current position is already mark or not
if not, then check if that navigate is safe and if it's land or water
then do recursion for all naviagte directions and return 1
*/
int archipelago::navigate(char ** &grid,int row,int col)
{
	const int nav = 5;
	if(isSafe(row, col) == false){ //base case
		return 0;
	}
	else{ //safe to process
		for(int k = 0; k < nav; k ++){ //do neightbord check// 5 neighborhood
			if(grid[row][col] != 2){ //flag and current position
				grid[row][col] = 2; //fl	
				//current
				if(isSafe(row + navR[0], col + navC[0]) && grid[row + navR[0]][col + navC[0]] != 'x'){ // check to see if out of bound
					
					navigate(grid, row + navR[0], col + navC[0]); //then recursive
				}	
				//go right
				if(isSafe(row + navR[1], col + navC[1]) && grid[row + navR[1]][col + navC[1]] != 'x'){ // check to see if out of bound
					navigate(grid, row + navR[1], col + navC[1]); //then recursive
				}	
				//go left
				if(isSafe(row + navR[2], col + navC[2]) && grid[row + navR[2]][col + navC[2]] != 'x'){
					navigate(grid, row + navR[2], col + navC[2]);
				}
				//go down
				if(isSafe(row + navR[3], col + navC[3]) && grid[row + navR[3]][col + navC[3]] != 'x'){
					navigate(grid, row + navR[3], col + navC[3]);
				}
				//go up
				if(isSafe(row + navR[4], col + navC[4]) &&grid[row + navR[4]][col + navC[4]] != 'x'){
					navigate(grid, row + navR[4], col + navC[4]);
				}
			}
		}
	}
	return 1;
}
/*Function to return true if the provided position is within 
the boundary of the archipelago
*/
bool archipelago::isSafe(int r,int c) const
{
	if(r>=0 && r<rows && c>=0 && c<columns)
		return true;
	else
		return false;
}

/*Function to change the color of an island
char newColor- color to pain
int r- starting point
int c- starting point
return void
Algorithm- check the base case and see if it's safe or not
if safe, then loop so that it do 5 navigate
check to see if the current position is already mark or not
if not, then check if that navigate is safe and if it's land or water
then do recursion for all naviagte directions and pain.
*/
void archipelago::changeColor(char newColor,int r,int c)
{
	const int nav = 5;
	if(isSafe(r, c) == false && r >= rows){ //special case
		r = r -1;
	}
	if(isSafe(r,c) == false){ //base case
		return;
	}
	else{
		for(int k = 0; k < nav; k++){ // do 5 navigate
			if(islands[r][c] != newColor){  //check for flag to end
				islands[r][c] = newColor; //fla	
				//current
				if(isSafe(r + navR[0], c + navC[0]) && islands[r + navR[0]][c + navC[0]] != 'x'){
					changeColor(newColor, r + navR[0], c + navC[0]);
				}
				//right
				if(isSafe(r + navR[1], c + navC[1]) && islands[r + navR[1]][c + navC[1]] != 'x'){
					changeColor(newColor, r + navR[1], c + navC[1]);
				}
				//left
				if(isSafe(r + navR[2], c + navC[2]) && islands[r + navR[2]][c + navC[2]] != 'x'){
					changeColor(newColor, r + navR[2], c + navC[2]);
				}
				//down
				if(isSafe(r + navR[3], c + navC[3]) && islands[r + navR[3]][c + navC[3]] != 'x'){
					changeColor(newColor, r + navR[3], c + navC[3]);
				}
				//up
				if(isSafe(r + navR[4], c + navC[4]) && islands[r + navR[4]][c + navC[4]] != 'x'){
					changeColor(newColor, r + navR[4], c + navC[4]);
				}
			}
		}
	}
}