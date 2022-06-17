#include <iostream>
#include <vector>
#include <cstdlib>
#include <sstream>
#include "mastermind.h"
using namespace std;

void setupGame(mastermind*&, mastermind*&);
void loadGame(mastermind*&, mastermind*&);
void saveGame(mastermind*&, mastermind*&);
bool yesOrNo(string);
void playGame(mastermind*&, mastermind*&);
string formatString(string);

int main()
{
	mastermind * currentGame;
	mastermind * savedGame;
	char choice;
	bool done = false;

	currentGame = savedGame = NULL;

	while (!done)
	{
		cout << endl;
		cout << "Do wish to (P)lay a new game, (C)ontinue current game"
			 << ", (L)oad saved game, or (Q)uit)? ";

		cin >> choice;
		cin.ignore(); //extra to prevent skipping
		switch (tolower(choice))
		{
			case 'p':
				setupGame(currentGame, savedGame);
				playGame(currentGame, savedGame);
				break;

			case 'l': 
				loadGame(currentGame, savedGame);
				playGame(currentGame, savedGame);
				break;

			case 'c':
				playGame(currentGame, savedGame);
				break;

			case 'q':
				done = true;
				break;

			default:
				cout << "Nope. 0/10. Do not approve of this input" << endl;
				break;
		}

	}

	//deallocate the objects if any are still left after
	//user decides to quit
	if (currentGame != NULL)
		delete currentGame;

	if (savedGame != NULL)
		delete savedGame;

	cout << endl;
	cout << "Ok well, I hope this was enjoyable" << endl;

	return 0;
}

/*setupGame - this function creates a new game

	mastermind*& currentGame - points to a mastermind object of the current game in play
	mastermind*& savedGame - points toamastermindobject of a saved game.
	return void

	Algorithm - using while loop to take user input and only break if user input is = and player size > 0.
	If user input is 0 and less size == 0, then output messages and repromp the user until they enter correct format.
	After that, pushback user input into vector. Check to see if currentGame is null or not. 
	If there is a current game in progress, ask the user if they wish to save the game using yes/no function, 
	if they wish to save the game call the saveGame function 
	if the saveGame function did not actually save the game then exit the setup function, 
	otherwise Allocate a new game to currentGame pointer by passing the vector  to the constructor and return
	If there is a current game in progress, and the user does not want to save the game, 
	deallocatethe currentGame and Allocate a new game to currentGame pointer by passing the vector  to the constructor .  
	Allocate a new game to currentGame pointer by passing the vector  to the constructor

*/

void setupGame(mastermind*& currentGame, mastermind*& savedGame)
{
	string wholeline;
	string color;
	vector <string> PlayerChoice;
	
	cout << endl;
	cout << "Enter the peg color followed by 0" << endl;
	while(cin >> wholeline){

		while(wholeline.length() <= 1 && PlayerChoice.size() == 0){
			cout << "Sorry! You  need at least 1 peg to play the game" << endl;
			cin >> wholeline;
		}
		if(wholeline == "0" && PlayerChoice.size() > 0){
			break;
		} 
		PlayerChoice.push_back(formatString(wholeline)); 
	}
	
	if(currentGame == NULL){
		currentGame = new mastermind(PlayerChoice); 
		return;
		
	}
	if(currentGame != NULL){ 
		cout << endl;
		cout << "You are already have game in progress" << endl;
		cout << "Would you like to save the game?" << endl;

		if (yesOrNo("(Y/N): ")){
			saveGame(currentGame, savedGame); 
			cout << "Saving current game..." << endl;
		}else{
			delete currentGame;
			currentGame = new mastermind(PlayerChoice);
			return;
		}

		if(currentGame != NULL){ // to check if the save function actually work or not
			//saved game rn will have address of previous current
			return;
		}else{
			delete currentGame;
			currentGame = new mastermind(PlayerChoice);
		}
	}
}

/*saveGame - this function saves a current game
	mastermind*& currentGame - points to a mastermind object of the current game in play
	mastermind*& savedGame - points toamastermindobject of a saved game.
	return void

	Algorithm - If there is no saved game, set saveGame to currentGame and assign currentGame to NULL and exit function
	If there is a saved game, ask the user if they still want to save over the savedGame using yes/no function
	if they want to save over, deallocate savedGame and set it to currentGame, then set currentGame to NULL
	If the user does not want to save the game then do nothing and exit from the function

*/

void saveGame(mastermind*& currentGame, mastermind*& savedGame)
{

	if(savedGame == NULL){
		savedGame = currentGame;
		currentGame = NULL;
		// if null then we will save it and not null, we will override the previous game
		return;
	}
	if(savedGame != NULL){
		cout << endl;
		cout << "Saving current game..." << endl;
		cout << "There is a saved game" << endl;
		cout << "This action will destroy/overwrite previously saved game. Is this ok?" << endl;

		if (yesOrNo("(Y/N): ")){
			delete savedGame;
			savedGame = currentGame;
			currentGame = NULL;
		}else{
			return;
		}
	}
}


/*saveGame - this function load a current game and save game
	mastermind*& currentGame - points to a mastermind object of the current game in play
	mastermind*& savedGame - points toamastermindobject of a saved game.
	return void

	Algorithm - If there is no saved game, exit out of the function
	If there is a current game, ask the user if they wish to destroy this game with yes/no function
	If they do, destroy the game and Set current game with the game in saved game and set saved game to NULL
	If they do not wish to destroy the current game, then exit the function

*/
void loadGame(mastermind*& currentGame, mastermind*& savedGame)
{

	if(savedGame == NULL){
		cout << endl;
		cout << "There is no game to load. Unable to complete the task. \n" << endl;
		return;
	}

	else if(savedGame != NULL){ 
		if(currentGame == NULL){
			currentGame = savedGame;
			savedGame = NULL;
			return; 
		}

		if(currentGame != NULL){
			cout << endl;
			cout << "This action will destroy current game." << endl;
			cout << "This  action  cannot  be  undone." << endl;
			cout << "Do you  wish to  continue?" << endl;

			if (yesOrNo("(Y/N): ")){
				cout << "Ok, loading game" << endl;
				delete currentGame;
				currentGame = savedGame;
				savedGame = NULL; 
			}else{
				return;
			}
		}
	}
}


/*yesOrNo- all this function does prompt the user by outputting msg and re-prompts if the user does not enter Y/y or N/n, 
	string msg - user input
	returns true if the user entered Y/y and returns false if they entered N/n.

	Algorithm - this function is written by professor

*/
bool yesOrNo(string msg)
{
	char choice;

	cout << endl;

	do
	{
		cout << msg;
		cin >> choice;
		choice = tolower(choice);
	}
	while (choice != 'y' && choice != 'n');

	return choice == 'y';
}

/*playGame- user interact to play the game
	mastermind*& currentGame - points to a mastermind object of the current game in play
	mastermind*& savedGame - points toamastermindobject of a saved game.
	return void

	Algorithm- using outer while loop to continue loop if the playermove that take return value from move() == 0
	Inside while loop, check if currentGame is NULL or not. If NULL, output error, and return. Otherwise, prompt the user
	using getMOveIndex() and getNumberOfColumn. Then using for loop to loop through solution size and get user input.
	If user input is p/P then flag and break. Otherwise, push input into vector.
	Outside the for loop, if flag then ask user if they want to save the game or not. If yes, save game by saveGame() and return
	If no, return and do nothing to current and saved game. 
	If not flag, check to see if vector is equal solution size or not. If yes, get return value from move() 
	and output gold and siver. Then clear the vector
	-If playermove is 1 = user win, output messange, delete currentGame, set currentGame to null and return
	-If playerMove is -1 = user lose, output messange, delete currentGame, set currentGame to null and return
	-If playerMove is 2 then return;

*/

void playGame(mastermind*& currentGame, mastermind*& savedGame)
{
	vector <string> PlayerChoice;
	string guess;
	int gold = 0;
	int silver = 0;
	int Playermoves = 0;
	bool pause = false;

	while(Playermoves == 0){
		if(currentGame == NULL){
			cout << endl;
			cout << "No current game found" << endl;
			return;
		}
		else if(currentGame != NULL){
			cout << endl;
			cout << "Turn " << currentGame->getMoveIndex()  
				<< ": Enter " << currentGame->getNumberOfColumns() 
				<< " color or (P)ause:" << endl;

			for(int i = 0; i < currentGame->getNumberOfColumns(); i++){
				//cin.clear();
				cin >> guess; 
				//cin.ignore(80,'\n');


				if(guess == "p" || guess == "P"){
					pause = true;
					break;
				}else{
					PlayerChoice.push_back(formatString(guess));
				}
			}
			cin.ignore(100,'\n');

			if(pause == true){
				cout << "Ok, we all need a break sometimes" << endl;
				cout << "Would you like to save the game?" << endl;
				if (yesOrNo("(Y/N): ")){
					cout << "Ok, saving game..." << endl;
					saveGame(currentGame, savedGame);
					return;
				}
				else{
					cout << "Ok, that's fine, you can alway resume" << endl;
					return;
				}
			}
			else{
				if(static_cast <int> (PlayerChoice.size()) == currentGame->getNumberOfColumns()){
					Playermoves = currentGame->move(PlayerChoice, gold, silver);
					cout << "Gold pegs: " <<  gold << endl;
					cout << "Silver pegs: " << silver << endl; 
					PlayerChoice.clear();
				}
			}
		}
	}
		if(Playermoves == 1 || Playermoves == -1){
			if(Playermoves == 1){
				cout << "You won! :)" << endl;
				cout << "Destroying game" << endl;
				delete currentGame;
				currentGame = NULL;
				return;
			}
			else{
				cout << "You lose! :(" << endl;
				cout << "Destroying game" << endl;
				delete currentGame;
				currentGame = NULL;
				return;
			}
		}
		else if(Playermoves == 2){ 
			return;
		}
}

/*formatString - format string to uppercase
	string s- user input string
	return upper string value

	Algorithm- using for loop to loop through the string and then user another var to hold uppercase of the string
	After that, return the uppercase value
*/

string formatString(string s){
	string value;
    for(unsigned int i = 0; i < s.length(); i++){
        value += toupper(s[i]);
    }
    return value;
    
}