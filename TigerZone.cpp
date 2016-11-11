#include<iostream>
#include<string>
#include<vector>
using namespace std;

const int tileSize = 4;
const int numberOfTiles = 72;
const int numberOfTigers = 7;

class BoardPiece{
	public:
	int xPosition;
	int yPosition;
	Tile * tile
	BoardPiece(int x,int y, Tile *t);
};
BoardPiece::BoardPiece(int x, int y, Tile *t){
	xPosition=x;
	yPosition=y;
	tile=NULL;
};

class Player {
private:
	int tiger;
	int score;
public:
	void changeScore();
	void placeTiger();
	void placeTile();
	Player();

};

class Feature {
	public:
};


class Castle : public Feature {
	public:
	const char type='C';
	short tileValue;
	
	Player * platerControlled;
	short numberOfPlayer1Tigers;
	short  numberOfPlayer2Tigers;
	Castle();
	};
Castle::Castle(Tile * a,){
	
};


class Wall : public Castle {
	public:
	const char type = 'W';
	short tileValue;
	int numberOfTiles;
	Player * playerControlled;
	int numberOfTigers;
	Wall();
};
Wall::Wall(){
	
};


class Field : public Feature {
	const char type = 'F';
	int numberOfTiles;
	Castle * castleConnections;
	short numberOfPlayer1Controlled;
	short numberOfPlayer2Controlled;
	void addFields();
};

class Road : public Feature {
	const char type='R';
	int numberOfTiles;
	Road * roadConnections;
	Field * fieldConnections;
	short numberOfPlayer1Controlled;
	short numberOfPlayer2Controlled;
	void addRoad();
};

class Monastary : public Feature {
	const char type = 'M';
	int numberOfTiles;
	short numberOfPlayer1Controlled;
	short numberOfPlayer2Controlled;
};



class Tile{
private:
	Feature ** features;
	Field ** fields;
	BoardPiece * coordinate;
public: 
	void rotateTile();
	void printTile();
	Tile();
	Tile(char above, char right, char below, char left)//DEBUG;
	
};


Tile::Tile(char above, char right, char below, char left) {
	fDebug=new char[tileSize];
	fDebug[0]=above;
	fDebug[1]=right;
	fDebug[2]=below;
	fDebug[3]=left;
};





class Board {
private:
	Tile ** board;
	BoardPiece ** tilesOnBoardPosition;
	int tilesAlreadyPlaced;
	vector < BoardPiece> possibleTilePlacement;
public:
	Board();
	bool checkValidPlacement();
	void placeTiger(Player * player,int x,int y);
	void connectTileToBoard(int x, int y, Tile * newTile);
	void adjustEdges(int x, int y);
	void printEdges();
	void placeTile(int x, int y, Tile * typeOfTile);
	void print();

};

Board::Board() {
	tilesAlreadyPlaced = 0;
	board = new Tile * [numberOfTiles];
	tilesOnBoardPosition= new BoardPiece *[numberOfTiles];
	possibleTilePlacement.push_back(BoardPiece(0,0));
};

void Board::placeTile(int x, int y,Tile * typeOfTile) {
	tilesOnBoardPosition[tilesAlreadyPlaced]=new BoardPiece(x,y);
	board[tilesAlreadyPlaced] = typeOfTile;
	tilesAlreadyPlaced++;
	//cout<<"Before adjustEdges"<<endl;//DEBUG
	adjustEdges(x, y);
};
void Board::adjustEdges(int x, int y) {
	bool aboveTileAlreadyAvailiable = false;
	bool belowTileAlreadyAvailiable= false;
	bool rightTileAlreadyAvailiable = false;
	bool leftTileAlreadyAvailiable = false;
	for (int i = 0; i < possibleTilePlacement.size(); i++) {
		if (possibleTilePlacement[i].xPosition == x + 1 && possibleTilePlacement[i].yPosition == y) {
			rightTileAlreadyAvailiable = true;
		}
		if (possibleTilePlacement[i].xPosition == x - 1  && possibleTilePlacement[i].yPosition == y) {
			leftTileAlreadyAvailiable = true;
		}
		if (possibleTilePlacement[i].xPosition == x && possibleTilePlacement[i].yPosition == y+1) {
			aboveTileAlreadyAvailiable = true;
		}
		if (possibleTilePlacement[i].xPosition == x && possibleTilePlacement[i].yPosition == y-1) {
			belowTileAlreadyAvailiable = true;
		}
	}
	if (!rightTileAlreadyAvailiable) {
		possibleTilePlacement.push_back(BoardPiece(x+1,y));
	}
	if (!leftTileAlreadyAvailiable) {
		possibleTilePlacement.push_back(BoardPiece(x-1,y));
	}
	if (!aboveTileAlreadyAvailiable) {
		possibleTilePlacement.push_back(BoardPiece(x,y+1));
	}
	if (!belowTileAlreadyAvailiable) {
		possibleTilePlacement.push_back(BoardPiece(x,y-1));
	}
	for (int i = 0; i < possibleTilePlacement.size(); i++) {
		for (int j = 0; j < tilesAlreadyPlaced; j++) {
			if (possibleTilePlacement[i].xPosition==tilesOnBoardPosition[j]->xPosition && possibleTilePlacement[i].yPosition==tilesOnBoardPosition[j]->yPosition) {
				 possibleTilePlacement.erase(possibleTilePlacement.begin()+i);
				break;
			}
		}
	}
	
};
void Board::printEdges() {
	int numberOfEdges = possibleTilePlacement.size();
	for (int i = 0; i < numberOfEdges; i++) {
		cout << "(" << possibleTilePlacement[i].xPosition << "," << possibleTilePlacement[i].yPosition << ")" << " ";
	}
	cout << "\n";

}
void Board::print() {
	for (int i = 0; i <tilesAlreadyPlaced; i++) {
		cout << "(" <<tilesOnBoardPosition[i]->xPosition << "," << tilesOnBoardPosition[i]->yPosition << ")" << " " << &board[i] << endl;
	}

};

int main() {
	Board * b = new Board();
	Tile * t = new Tile(); 
	b->printEdges();
	b->placeTile(0, 0, t);
	b->printEdges();
	b->placeTile(0,1,t);
	b->printEdges();
	b->placeTile(-1,0,t);
	b->printEdges();
	return 0;
};