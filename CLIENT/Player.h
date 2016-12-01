#include "Board.h";

class Player {

	int score;
	int playerNumber;
	int numberOfTigers;
	int numberOfCrocodiles;
	int tigersPlacedOnJungles;
	Tile* currentTile;
	Board* board;

public:
	Player(int num);
	Player(int num, Board* &b);
	int getScore();
	int getNumberOfTigers();
	int getNumberOfCrocodiles();
	Board* getBoard();
	void setCurrentTile(Tile* &tile);
	Tile* getCurrentTile();
	//Given the position and orientation, add tile to board
	string placeTile(pair<pair<int, int>,int> position_orientation);
	void placeTiger(int position);
	void placeCrocodile();
	//Place tile and tiger at first legal position (if possible)
	void makeDumbMove();
	string makeSmarterMove();
	void getTigersBack();
	int getPlayerNumber();
};
