#include<iostream>
#include<string>
#include<vector>
using namespace std;

const int tileSize = 4;
const int numberOfTiles = 72;
const int numberOfTigers = 7;



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
	char type;
	Feature();
	virtual char getType();
};
Feature::Feature(){
	
};
char Feature::getType(){
	return type;
}


class Castle : public Feature {
	public:
	const char type='C';
	short tileValue;
	char getType();
	Player * platerControlled;
	short numberOfPlayer1Tigers;
	short  numberOfPlayer2Tigers;
	
	Castle();
	};
Castle::Castle(){
};

char Castle::getType(){
	return type;
}
class Wall : public Castle {
	public:
	const char type = 'W';
	short tileValue;
	int numberOfTiles;
	Player * playerControlled;
	int numberOfTigers;
	char getType();
	Wall();
};
Wall::Wall(){
	
};
char Wall::getType(){
	return type;
}


class Field : public Feature {
	public:
	const char type = 'F';
	int numberOfTiles;
	Castle * castleConnections;
	short numberOfPlayer1Controlled;
	short numberOfPlayer2Controlled;
	char getType();
	void addFields();
	Field();
};
Field::Field(){
	
};
char Field::getType(){
	return type;
}

class Road : public Feature {
	public:
	//vector< BoardPiece> numberOfTiles;
	vector< Road> roadsConnected;
	int numOfEnds;
	const char type='R';
	//short numberOfPlayer1Controlled;
	//short numberOfPlayer2Controlled;
	char getType();
	void mergeRoad(Road * r);
	Road();
};
Road::Road(){
};
void Road::mergeRoad(Road * r){
	
};
char Road::getType(){
	return type;
}

class Monastary : public Feature {
	const char type = 'M';
	char getType();
	int numberOfTiles;
	short numberOfPlayer1Controlled;
	short numberOfPlayer2Controlled;
};
char Monastary::getType(){
	return type;
}


class Tile{
private:
	Feature * topFeature;
	Feature * rightFeature;
	Feature * bottomFeature;
	Feature * leftFeature;
	//Field ** fields;
public: 
	void rotateTile();
	void printTile();
	Tile(Feature * above, Feature * right, Feature * bottom, Feature * left);//DEBUG;
	
	
};

Tile::Tile(Feature * above, Feature * right, Feature * bottom, Feature * left) {
	topFeature=above;
	rightFeature=right;
	bottomFeature=bottom;
	leftFeature=left;
};

void Tile::rotateTile(){
	Feature ** orientationFeatures= new Feature *[4];
	orientationFeatures[0]=topFeature;
	orientationFeatures[1]=rightFeature;
	orientationFeatures[2]=bottomFeature;
	orientationFeatures[3]=leftFeature;
	rightFeature=orientationFeatures[0];
	bottomFeature=orientationFeatures[1];
	leftFeature=orientationFeatures[2];
	topFeature=orientationFeatures[3];
	delete orientationFeatures;	
};

void Tile::printTile(){
	cout<<"Top:"<<topFeature->getType()<<" Right: "<<rightFeature->getType()<<" Bottom: "<<bottomFeature->getType()<<" Left: "<<leftFeature->getType()<<endl;
};

class BoardPiece{
	public:
	int xPosition;
	
	
	int yPosition;
	Tile * tile;
	BoardPiece(int x,int y, Tile *t);
	BoardPiece(int x,int y);
};
BoardPiece::BoardPiece(int x, int y, Tile *t){
	xPosition=x;
	yPosition=y;
	tile=t;
};
BoardPiece::BoardPiece(int x,int y){
	xPosition=x;
	yPosition=y;
	tile=NULL;
};




class Board {
private:
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
	tilesOnBoardPosition= new BoardPiece *[numberOfTiles];
	possibleTilePlacement.push_back(BoardPiece(0,0));
};

void Board::placeTile(int x, int y,Tile * typeOfTile) {
	tilesOnBoardPosition[tilesAlreadyPlaced]=new BoardPiece(x,y,typeOfTile);
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
		cout << "(" <<tilesOnBoardPosition[i]->xPosition << "," << tilesOnBoardPosition[i]->yPosition << ")";
		tilesOnBoardPosition[i]->tile->printTile();
		cout<<"\n";
	}

};

int main() {
	Board * b = new Board();
	Feature * f= new Field();
	Feature * c= new Castle();
	Feature * w=new Wall();
	Tile * t = new Tile(f,c,w,f);
	t->printTile();
	t->rotateTile();
	t->printTile();
	/*b->printEdges();
	b->placeTile(0, 0, t);
	b->printEdges();
	b->placeTile(0,1,t);
	b->printEdges();
	b->placeTile(-1,0,t);
	b->printEdges();*/
	return 0;
};