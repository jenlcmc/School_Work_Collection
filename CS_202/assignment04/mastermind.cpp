#include "mastermind.h"
#include <vector>
#include <string>
using namespace std;

/*mastermind - constructor that sets the size of solution vector and assignseach element to contain"red", 

    sets maxMoves to 5 and moves to 0.
    int size - assign it to solution size

    Algorithm - assign color to default color red and maxmoves to 5, moves to 0
*/

mastermind::mastermind(int size) : solution(size)
{
    string defcolor = "red";
    maxMoves = 5;
    moves = 0;

    for(unsigned int i = 0; i < solution.size(); i++){
        solution.push_back(defcolor);
    }
}

/*mastermind - constructor that sets the solution vector with the content of initial vector (insensitive way)

    sets maxMoves to 5 and moves to 0.
    vector<string> initial -user input string that will be push to solution vector

    Algorithm - using nested for loop to to convert the vector of string initial to all uppercase and then put them in solution
    vec using push_back(). Also, assign maxMoves to 5 and moves to 0

*/
mastermind::mastermind(vector<string> initial)
{
    for(unsigned int i = 0; i < initial.size(); i++){
        string temp = initial[i];
        string convert;
        for(unsigned int j = 0; j < temp.length(); j++){
            convert += toupper(temp[j]);
        }
        solution.push_back(convert);
    }

    maxMoves = 5;
    moves = 0;
}

/*move - this function simulates one move/round of the mastermind game. 
    function needs to determine how many pegs’s colors are in the same respective column as the solution vector
    (update gold each time), and the colors from playerMove that matches with solution 
    but not in the same respective position(update silver each time), then update the moves counter. 

    vector<string> playerMove- consists of the user’s guess which is a set of pegs with their colors
    int gold - correct index(s) and same result(s)
    int silver - wrong index(s) but same result(s)
    return - The function returns 4 possible integers
    –If it returns 0, the game is not over
    -If it returns 1, the user won (i.e.  the amount of gold matches the width of the board)
    –If it returns -1, the user lost (ran out of attempts)
    –If it returns 2, then the amount of pegs in the playerMove does not match the amount in solution,so not a valid move,
    not update the moves counter in this case

    Algorithm - using nested loop to loop through solution and player vector. Then determine the gold value by compare
    2 vectors and mark it using bool. Then inside the nested loop, determine for silver, increment silver 1st
    and then check if vector of playermove in outerloop same with insideloop or not and 
    then check if it's already have mark or not. If it's the same and have mark, then subtract the silver value and break from the loop
    After nested loop, increment move. Return value based on above conditions
*/
int mastermind::move(vector<string> playerMove, int& gold, int& silver) 
{
    gold = 0;
    silver = 0;
    bool haveresult = false;

    for(unsigned int i = 0; i < solution.size(); i++){
        if(playerMove[i] == solution[i]){
            gold++;
            haveresult = true;
        }
        for(unsigned int j = 0; j < playerMove.size(); j++){
            if(playerMove[j] == solution[i] && i != j){
                silver++;
                if(playerMove[i] == playerMove[j] && haveresult == true){
                    silver--;
                    break;
                }
            }
        }
    }
    moves++;

    if(playerMove.size() != solution.size()){ 
        return 2;
    }
    if(static_cast<unsigned int>(gold) == solution.size()){
        return 1;
    }
    else if(moves >= maxMoves){
        return -1;
    }
    else if(moves <= maxMoves){
        return 0;
    }
    return 3;
}

/*getMoveIndex - get move index
    return move + 1

    Algorithm - return move +1 cause initial is 0
*/
int mastermind::getMoveIndex() const
{
    return(moves + 1);
}

/*getMoveIndex - get solution size/ columns numbers
    return solution size

    Algorithm - return solution size
*/
int mastermind::getNumberOfColumns() const
{   
    return(solution.size()); //seg
}
