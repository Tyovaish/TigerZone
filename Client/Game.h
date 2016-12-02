#include "Player.h";
#include <queue>;
using namespace std;

class Game {

	queue<Tile*>* queueOfTiles;
	Board* board;
	Player *player1, *player2;

public:

	Game();
	void addTileToQueue(string name);
	queue<Tile*>* getQueueOfTiles();
	Player* getPlayer1();
	Player* getPlayer2();
	Board* getBoard();
	void readTilesFromFile(string &Filename);

};