#include <iostream>
#include "archipelago.h"

using namespace std;

int main()
{

	//create the content of an archipelago with red island
	char red[25]={'r','x','x','r','r','r','r','x','r','r','x','r','r','r','r',
	'x','x','x','r','r','r','x','r','x','x'};
	archipelago redIsland(red,5,5,'r');
	cout<<"Printing the archipelago of size 5*5 of red islands:"<<endl;
	redIsland.showIslands(0,0);//printing the island
	cout <<"Number of islands in this archipelago:"<<redIsland.islandsCount(redIsland.getGrid())<<endl;
	cout <<"Painting the island starting at (0,0) to green"<<endl;
	redIsland.changeColor('g',0,0);//repaint the island starting at 0,0 to green
	cout <<"Printing the repainted archipelago:"<<endl;
	redIsland.showIslands(0,0);

	//create the content of an archipelago with blue island
	char blue[9]={'x','x','x','x','x','x','x','x','x'};
	archipelago blueIsland(blue,3,3,'b');
	cout <<endl<<endl<<"Printing the archipelago of size 3*3:"<<endl;
	blueIsland.showIslands(0,0);//printing the island
	cout <<"Number of islands is:"<<blueIsland.islandsCount(blueIsland.getGrid())<<endl;

	//create the content of an archipelago with white island
	char white[20]={'w','x','x','x','x','x','w','w','x','x','x','x','x',
	'w','w','w','w','w','x','x'};
	archipelago whiteIsland(white,4,5,'w');
	cout <<endl<<endl<<"Printing the archipelago:"<<endl;
	whiteIsland.showIslands(0,0);//printing the island
	cout <<"Number of islands is:"<<whiteIsland.islandsCount(whiteIsland.getGrid())<<endl;
	cout <<"Painting the island starting at (4,0) to orange"<<endl;
	whiteIsland.changeColor('o',4,0);//repaint the island at 4,0 to orange
	cout <<"Printing the repainted archipelago:"<<endl;
	whiteIsland.showIslands(0,0);

	//create the content of an archipelago with yellow island
	char yellow[4]={'x','x','y','x'};
	archipelago yellowIsland(yellow,2,2,'y');
	cout <<endl<<endl<<"Printing the archipelago of size 2*2 with yellow island:"<<endl;
	yellowIsland.showIslands(0,0);//printing the island
	cout <<"Number of islands is:"<<yellowIsland.islandsCount(yellowIsland.getGrid())<<endl;


	return 0;
}