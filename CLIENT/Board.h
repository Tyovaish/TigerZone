#include "Tile.h";
#include <vector>;

using namespace std;

class Board {

	vector<Tile*> Tiles; //tiles on board
	vector<pair<int, int>> openPositions; //all open positions bordering tiles
	
	//erases given position from the open position vector
	void eraseOpenPosition(pair<int, int> position);
	//adds given position to the open positions vector
	void addOpenPosition(pair<int, int> position);

public:

	//default constructor initializes the board to have one open position, (0,0) where the first tile will be placed
	Board();
	Board(vector<Tile*> &tiles, vector<pair<int, int>> &openpositions);
	//returns vector of open positions
	vector<pair<int, int>> getOpenPositions();
	//returns pointer to tile at position x,y or NULL if no tile at that position. 
	Tile* tileAt(int x, int y);
	//returns true if the given position is open or false otherwise
	bool positionOpen(pair<int, int> position);
	//returns a vector of all positions the given tile can be legally placed
	vector<pair<pair<int, int>,int>> possibleTilePlacements(Tile* tileToPlace);
	pair<pair<int, int>, int>* bestTilePlacement(Tile* tileToPlace);
	//adds a tile to the board after the position and orientation have been decided, and updates the open positions vector
	//also makes pointer connections between adjacent features
	void addTile(Tile* &tile);
	bool tileIsSurrounded(Tile* const &t);
};

/*
int main() {
Board* b = new Board();
Tile* t1 = new Tile('r', 'r', 'f', 'f', 0, 0);
b->addTile(t1);

vector<pair<int, int>> open = b->getOpenPositions();

for (size_t i = 0; i < open.size(); i++) {
cout << "(" << open.at(i).first << "," << open.at(i).second << ")\n";
}

cout << endl;

Tile* t2 = new Tile('r', 'r', 'c', 'c');
vector<pair<int, int>> test = b->possiblePositions(t2);
for (size_t s = 0; s < test.size(); s++) {
cout << "(" << test.at(s).first << "," << test.at(s).second << ")\n";
}

t2->setPosition(-1,0);

b->addTile(t2);

open = b->getOpenPositions();

cout << endl;

for (size_t i = 0; i < open.size(); i++) {
cout << "(" << open.at(i).first << "," << open.at(i).second << ")\n";
}

system("PAUSE");

return 0;

}
*/