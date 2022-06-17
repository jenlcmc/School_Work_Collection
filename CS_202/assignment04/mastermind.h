#include <string>
#include <vector>
using namespace std;

class mastermind
{
public:
	mastermind(int);
	mastermind(vector<string>);
	int move(vector<string>, int&, int&);
	int getMoveIndex() const;
	int getNumberOfColumns() const;
private:
	int maxMoves;
	vector<string> solution;
	int moves;
};