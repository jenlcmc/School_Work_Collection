/*
    *
    * Descriptions: Knight Tour using recursive back tracking approach
    * and using a heuristic approach.
    * There are a maximum of 8 possible moves a knight can make
    * from a location on the chessboard, it moves up two spots and then one to the left
    * or up two spots and one to the right or up one spot
    * and then to the left two spots, or up one spot and then
    * two to the right, the last 4 are the same idea
    * but the knight moves down one/two and then to the left/right one/two
    *
    * Input: User input board size and the position for knight
    *
    * Output: a tour (write the knight move counter) onto each element of the board to construct
    * a knight tour on a given n ×n board and given the knight’s initial coordinates.

*/

#ifndef KNIGHTTYPE_H
#define KNIGHTTYPE_H

// libraries for the program
#include <iostream>
#include <vector>
#include <iomanip>

// std that uses in program
using std::cout;
using std::string;
using std::vector;

class knightType
{
public:
    struct position
    {
        position(int r = 0, int c = 0, int o = 0)
        {
            row = r;
            col = c;
            onwardMoves = o;
        }

        int row;
        int col;
        int onwardMoves;
    };
    knightType(int = 8);
    bool knightTour(int, int);
    void outputTour() const;

private:
    bool knightTour(int, int, int);
    std::vector<position> getAvailableMoves(int, int);
    bool fullBoard();
    std::vector<std::vector<int>> board;
    int functionsCalled;

    // helper functions
    bool inBound(int, int);
    int checkOnwards(int, int);
};

/**
 * @brief Construct a new knight Type::knight Type object
 *  constructor that allocates a dim ×dim vector to the board
 *  object and sets each element to 0, sets functionsCalled to 0
 * @param dim- to allocates the vec
 * @return-none
 */
knightType::knightType(int dim) : board(dim, vector<int>(dim, 0))
{
    functionsCalled = 0;
}

/**
 * @brief function that returns a list of possible moves a knight can
 * make from coordinate [r, c] along with the onward
 * moves that the knight can make if the new potential location is chosen,
 * @param r-row
 * @param c-col
 * @return std::vector<knightType::position>
 */
std::vector<knightType::position> knightType::getAvailableMoves(int r, int c)
{
    // lecture order from professor
    vector<int> xMoves = {-1, -1, -2, -2, 1, 1, 2, 2};
    vector<int> yMoves = {-2, 2, -1, 1, -2, 2, -1, 1};

    // vector to hold all posibles moves
    vector<position> moves;
    // index to loop 8 times
    int i = 0;

    while (i < xMoves.size())
    {
        // create a new pos for row and colum (possible moves)
        int newX = r + xMoves[i];
        int newY = c + yMoves[i];

        // push_back whenever the available space
        // is actually valid and not full
        if (inBound(newX, newY) && board[newX][newY] == 0)
        {
            // the count will check for onWard possible moves
            int count = checkOnwards(newX, newY);
            // then push the position() into moves vector
            moves.push_back(position(newX, newY, count));
        }
        i++;
    }
    return moves;
}

/**
 * @brief returns true if the knight tour is complete (every cell in board
 * contains an integer larger than 0), and false otherwise
 * @param none
 * @return true
 * @return false
 */
bool knightType::fullBoard()
{
    // flag to check if the board is full or not
    bool full = true;
    // count to check if we reach all cells
    int count = 0;
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board.size(); j++)
        {
            // if cell > 0 -> fill -> increment counter
            if (board[i][j] > 0)
            {
                count++;
            }
        }
    }

    // if counter == size of board-all fill up -> set flag to true
    if (count >= board.size() * board.size())
    {
        full = true;
    }
    else
        full = false;

    return full;
}

/**
 * @brief outputs the board and the amount of functions called, see
    the sample output
 * @param none
 * @return none
 */
void knightType::outputTour() const
{
    cout << '\n';
    string rows = "   ";
    char temp;

    // for loop to determine how many letter need based on board size
    for (int i = 0; i < board.size(); i++)
    {
        // then convert that to letter from numerical
        temp = (i % 26) + 'A';
        rows.push_back(temp);
        rows.append("  ");
    }
    // print out header letter
    cout << rows << '\n';

    temp = 'A';
    for (int i = 0; i < board.size(); i++)
    { // increment to add letters for row
        cout << temp++ << "  ";
        for (int j = 0; j < board.size(); j++)
        {

            cout << std::left << std::setw(2) << board[i][j] << " ";
        }
        cout << '\n';
    }
    cout << "\nFunctions called: " << functionsCalled << "\n";
}

/**
 * @brief function that makes the first initial call to the re-cursive function,
 * the function body is just return knightTour(r, c, 1);,
 * this is just a wrapper function that is called in main
 * @param r - row
 * @param c - col
 * @return true
 * @return false
 */
bool knightType::knightTour(int r, int c)
{
    return knightTour(r, c, 1);
}

/**
 * @brief this recursive function simulates the knight movement, the steps are
 * 1. Set the board[r][c] with tourIndex
 * 2. Check if the board is full if so, return true
 * 3. Get all the available moves from location [r, c]
 * 4. Pick the available move with the minimal onward moves
 * 5. Make a recursive call to this function,
 * pass in the new r and c values using the chosen available
 * move from the above step 2
 * @param r - row
 * @param c - col
 * @param tourIndex - init val
 * @return true
 * @return false
 */
bool knightType::knightTour(int r, int c, int tourIndex)
{
    // vector to hold all possible moves from getAvailableMoves
    vector<position> allMoves;

    // step 1
    board[r][c] = tourIndex;
    functionsCalled++;
    // temp index to delete
    int index = 0;

    // base case
    if (fullBoard() == true)
        return true;

    // get moves
    allMoves = getAvailableMoves(r, c);

    // check vector to determine whether continue or not
    if (allMoves.size() == 0)
        return false;

    // if there are moves -> init the variables to 1st one
    int min = allMoves[0].onwardMoves;
    int newX = allMoves[0].row;
    int newY = allMoves[0].col;
    index = 0;

    // for loop to check for minimum onWard move
    for (int i = 0; i < allMoves.size(); i++)
    {
        // if yes -> then set up new min and row & col
        if (allMoves[i].onwardMoves < min)
        {
            min = allMoves[i].onwardMoves;
            newX = allMoves[i].row;
            newY = allMoves[i].col;
            index = i;
        }
    }

    // if recursion bool is true -> true
    if (knightTour(newX, newY, tourIndex + 1) == true)
        return true;

    // second loop to check for second smallest
    for (int i = 0; i < allMoves.size(); i++)
    {
        if (allMoves[i].onwardMoves < min)
        {
            min = allMoves[i].onwardMoves;
            newX = allMoves[i].row;
            newY = allMoves[i].col;
        }
    }
    // call recursion again
    knightTour(newX, newY, tourIndex + 1);
    return false;
}

/**
 * @brief helper function to determine whether the r and c is in bound or mot
 *
 * @param r row
 * @param c col
 * @return true
 * @return false
 */
bool knightType::inBound(int r, int c)
{
    return (r < board.size() && c < board.size() && r >= 0 && c >= 0);
}

/**
 * @brief function to check all available moves of onwardMoves
 * using the same algorithm with getAvaiableMove
 * @param r row
 * @param c col
 * @return int total available moves
 */
int knightType::checkOnwards(int r, int c)
{
    // lecture order from professor
    vector<int> xMoves = {-1, -1, -2, -2, 1, 1, 2, 2};
    vector<int> yMoves = {-2, 2, -1, 1, -2, 2, -1, 1};

    // counter
    int count = 0;
    int i = 0;

    // loop 8 times as the knight can have 8 possible moves
    while (i < xMoves.size())
    {
        // get new row and col
        int newX = r + xMoves[i];
        int newY = c + yMoves[i];

        // check if in bound and fill or not
        if (inBound(newX, newY) && board[newX][newY] == 0)
        {
            count++;
        }
        i++;
    }
    return count;
}
#endif
