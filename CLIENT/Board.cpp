#include "Board.h";
#include <utility>;
#include <algorithm>;
#include <iostream>;
using namespace std;

//default constructor initializes the board to have one open position, (0,0) where the first tile will be placed
Board::Board() {
	openPositions.push_back(make_pair(0,0));
}

Board::Board(vector<Tile*> &tiles, vector<pair<int,int>> &openpositions) {
	Tiles = tiles;
	openPositions = openpositions;
} 

//erases given position from the open position vector
void Board::eraseOpenPosition(pair<int, int> position) {
	openPositions.erase(find(openPositions.begin(), openPositions.end(), position));
}

//adds given position to the open positions vector
void Board::addOpenPosition(pair<int, int> position) {
	openPositions.push_back(position);
}

//returns vector of open positions
vector<pair<int, int>> Board::getOpenPositions() {
	return openPositions;
}

//returns pointer to tile at position x,y or NULL if no tile at that position. 
Tile* Board::tileAt(int x, int y) {
	for (vector<Tile*>::iterator it = Tiles.begin(); it != Tiles.end(); it++) {
		if ((*it)->getX() == x && (*it)->getY() == y) {
			return *it;
		}
	}
	return NULL;
}
	
//returns true if the given position is open or false otherwise
bool Board::positionOpen(pair<int, int> position) {
	return (find(openPositions.begin(), openPositions.end(), position) != openPositions.end());
}
	
//returns a vector of all positions the given tile can be legally placed
vector<pair<pair<int,int>,int>> Board::possibleTilePlacements(Tile* tileToPlace) {
	vector<pair<pair<int, int>,int>> result; //vector of pairs, holding the position and orientation where the tile can be placed
	int currX, currY;
	char leftBorder, topBorder, rightBorder, bottomBorder;
	Tile *left, *top, *right, *bottom;
	//for each of 4 tile orientations,
	for (int j = 0; j < 4; j++) {
		//iterate through the list of open positions and check if the tile can be placed legally in that position.
		for (size_t i = 0; i < openPositions.size(); i++) {
			currX = openPositions.at(i).first;
			currY = openPositions.at(i).second;
			left = tileAt(currX - 1, currY);
			top = tileAt(currX, currY + 1);
			right = tileAt(currX + 1, currY);
			bottom = tileAt(currX, currY - 1);

			//if there is no tile to the left, right, top, or bottom of the open position, represent that border as a space character
			//else, represent that border as the character corresponding to the type of that feature ('r','c', or 'f')
			if (left == NULL) {
				leftBorder = ' ';
			}
			else {
				leftBorder = left->getEfeat()->getType();
			}
			if (top == NULL) {
				topBorder = ' ';
			}
			else {
				topBorder = top->getSfeat()->getType();
			}
			if (right == NULL) {
				rightBorder = ' ';
			}
			else {
				rightBorder = right->getWfeat()->getType();
			}
			if (bottom == NULL) {
				bottomBorder = ' ';
			}
			else {
				bottomBorder = bottom->getNfeat()->getType();
			}
			//compare each side of the tile to its bordering features. If they match, add this 
			//position and orientation to the list of possible positions/orientations for the given tile
			if (((tileToPlace->getWfeat()->getType() == leftBorder) || (leftBorder == ' ')) &&
				((tileToPlace->getNfeat()->getType() == topBorder) || (topBorder == ' ')) &&
				((tileToPlace->getEfeat()->getType() == rightBorder) || (rightBorder == ' ')) &&
				((tileToPlace->getSfeat()->getType() == bottomBorder) || (bottomBorder == ' '))) {
					result.push_back(make_pair(openPositions.at(i),90*j));
			}
		}
		//rotate the tile
		tileToPlace->rotateCCW();
	}
	return result;
}

pair<pair<int,int>,int>* Board::bestTilePlacement(Tile* tileToPlace) {
	pair<pair<int, int>, int>* result = NULL;
	int currX, currY;
	char leftBorder, topBorder, rightBorder, bottomBorder;
	Tile *left, *top, *right, *bottom;
	int currentBest = 0;
	int possiblePoints;
	//for each of 4 tile orientations,
	for (int j = 0; j < 4; j++) {
		//iterate through the list of open positions and check if the tile can be placed legally in that position.
		for (size_t i = 0; i < openPositions.size(); i++) {
			possiblePoints = 0;
			currX = openPositions.at(i).first;
			currY = openPositions.at(i).second;
			left = tileAt(currX - 1, currY);
			top = tileAt(currX, currY + 1);
			right = tileAt(currX + 1, currY);
			bottom = tileAt(currX, currY - 1);

			//if there is no tile to the left, right, top, or bottom of the open position, represent that border as a space character
			//else, represent that border as the character corresponding to the type of that feature ('r','c', or 'f')
			if (left == NULL) {
				leftBorder = ' ';
			}
			else {
				leftBorder = left->getEfeat()->getType();
				possiblePoints += left->getEfeat()->getPotentialPoints();
			}
			if (top == NULL) {
				topBorder = ' ';
			}
			else {
				topBorder = top->getSfeat()->getType();
				possiblePoints += top->getSfeat()->getPotentialPoints();
			}
			if (right == NULL) {
				rightBorder = ' ';
			}
			else {
				rightBorder = right->getWfeat()->getType();
				possiblePoints += right->getWfeat()->getPotentialPoints();

			}
			if (bottom == NULL) {
				bottomBorder = ' ';
			}
			else {
				bottomBorder = bottom->getNfeat()->getType();
				possiblePoints += bottom->getNfeat()->getPotentialPoints();

			}
			//compare each side of the tile to its bordering features. If they match, add this 
			//position and orientation to the list of possible positions/orientations for the given tile
			if (((tileToPlace->getWfeat()->getType() == leftBorder) || (leftBorder == ' ')) &&
				((tileToPlace->getNfeat()->getType() == topBorder) || (topBorder == ' ')) &&
				((tileToPlace->getEfeat()->getType() == rightBorder) || (rightBorder == ' ')) &&
				((tileToPlace->getSfeat()->getType() == bottomBorder) || (bottomBorder == ' '))) {
					if (possiblePoints >= currentBest || result == NULL) {
						currentBest = possiblePoints;
						result = &make_pair(openPositions.at(i), 90 * j);
					}
			}
		}
		//rotate the tile
		tileToPlace->rotateCCW();
	}
	return result;
}

//adds a tile to the board after the position and orientation have been decided, and updates the open positions vector
//also makes pointer connections between adjacent features
void Board::addTile(Tile* &tile)  {
	int xpos = tile->getX();
	int ypos = tile->getY();
	Tiles.push_back(tile); //add the new tile to the vector of tiles on the board
	pair<int,int> tilePos = make_pair(tile->getX(), tile->getY()); //this is the position of the new tile, which must be deleted from the vector of open positions
	eraseOpenPosition(tilePos); //remove the new tile's position from the vector of open positions
	if ( !positionOpen(make_pair(xpos-1,ypos)) && tileAt(xpos-1,ypos) == NULL ) {
		addOpenPosition(make_pair(xpos-1, ypos));
	}
	if ( !positionOpen(make_pair(xpos,ypos+1)) && tileAt(xpos,ypos+1) == NULL ) {
		addOpenPosition(make_pair(xpos,ypos+1));
	}
	if ( !positionOpen(make_pair(xpos+1,ypos)) && tileAt(xpos+1,ypos) == NULL ) {
		addOpenPosition(make_pair(xpos+1,ypos));
	}
	if ( !positionOpen(make_pair(xpos,ypos-1)) && tileAt(xpos,ypos-1) == NULL ) {
		addOpenPosition(make_pair(xpos,ypos-1));
	}
	//now make the connections

	if (tileAt(xpos - 1, ypos) != NULL) {
		tile->getWfeat()->merge(tileAt(xpos - 1, ypos)->getEfeat());
		if (tile->getWfeat()->getType() == 'T') {
			tile->getSWfeat()->merge(tileAt(xpos - 1, ypos)->getSEfeat());
			vector<Feature*> NWconnected = tile->getNWfeat()->getConnectedFeatures();
			if (find(NWconnected.begin(), NWconnected.end(), tileAt(xpos - 1, ypos)->getNEfeat()) == NWconnected.end()) {
				tile->getSWfeat()->merge(tileAt(xpos - 1, ypos)->getSEfeat());
			}
		}
	}
	if (tileAt(xpos, ypos + 1) != NULL) {
		tile->getNfeat()->merge(tileAt(xpos, ypos + 1)->getSfeat());
		if (tile->getNfeat()->getType() == 'T') {
			tile->getNWfeat()->merge(tileAt(xpos, ypos+1)->getSWfeat());
			vector<Feature*> NEconnected = tile->getNEfeat()->getConnectedFeatures();
			if (find(NEconnected.begin(), NEconnected.end(), tileAt(xpos, ypos+1)->getSEfeat()) == NEconnected.end()) {
				tile->getNEfeat()->merge(tileAt(xpos, ypos+1)->getSEfeat());
			}
		}
	}
	if (tileAt(xpos + 1, ypos) != NULL) {
		tile->getEfeat()->merge(tileAt(xpos + 1, ypos)->getWfeat());
		if (tile->getEfeat()->getType() == 'T') {
			tile->getNEfeat()->merge(tileAt(xpos + 1, ypos)->getNWfeat());
			vector<Feature*> SEconnected = tile->getSEfeat()->getConnectedFeatures();
			if (find(SEconnected.begin(), SEconnected.end(), tileAt(xpos + 1, ypos)->getSWfeat()) == SEconnected.end()) {
				tile->getSEfeat()->merge(tileAt(xpos + 1, ypos)->getSWfeat());
			}
		}
	}
	if (tileAt(xpos, ypos - 1) != NULL) {
		tile->getSfeat()->merge(tileAt(xpos, ypos - 1)->getNfeat());
		if (tile->getSfeat()->getType() == 'T') {
			tile->getSEfeat()->merge(tileAt(xpos, ypos-1)->getNEfeat());
			vector<Feature*> SWconnected = tile->getSWfeat()->getConnectedFeatures();
			if (find(SWconnected.begin(), SWconnected.end(), tileAt(xpos, ypos-1)->getNWfeat()) == SWconnected.end()) {
				tile->getSWfeat()->merge(tileAt(xpos, ypos-1)->getNWfeat());
			}
		}
	}
}

bool Board::tileIsSurrounded(Tile* const &t) {
	int x = t->getX();
	int y = t->getY();
	if (tileAt(x, y + 1) != NULL && tileAt(x + 1, y + 1) != NULL && tileAt(x + 1, y) != NULL && tileAt(x + 1, y - 1) != NULL && tileAt(x, y - 1) != NULL
		&& tileAt(x - 1, y - 1) != NULL && tileAt(x - 1, y) != NULL && tileAt(x - 1, y + 1) != NULL) {
			return true;
	}
	else {
		return false;
	}
}