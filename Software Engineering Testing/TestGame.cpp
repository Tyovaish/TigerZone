
#include "Game.h";
#include <iostream>;
#include <fstream>;
#include <string>;

using namespace std;

Game::Game() {
	queueOfTiles = new queue<Tile*>;
	board = new Board();
	player1 = new Player(1,board);
	player2 = new Player(2,board);
}

void Game::addTileToQueue(string name) {
	Tile* t = new Tile(name);
	queueOfTiles->push(t);
}

queue<Tile*>* Game::getQueueOfTiles() {
	return queueOfTiles;
}

Player* Game::getPlayer1() {
	return player1;
}

Player* Game::getPlayer2() {
	return player2;
}

Board* Game::getBoard() {
	return board;
}

void Game::readTilesFromFile(string &Filename) {
	ifstream s;
	s.open(Filename);

	int numOfDifferentTiles;
	s >> numOfDifferentTiles;
//	cout << numOfDifferentTiles << endl; //testing
	int numOfCurrentTile;
	string name;

	for (int i = 0; i < numOfDifferentTiles; i++) {
		s >> numOfCurrentTile;
	//	cout << numOfCurrentTile << " ";
		s >> name;
		for (int j = 0; j < numOfCurrentTile; j++) {
			queueOfTiles->push(new Tile(name));
		}
	}
}

int main() {
	
	Game* g = new Game();
	string fileName = "C:\\Users\\aleca\\Desktop\\GameTiles.txt";
	g->readTilesFromFile(fileName);
	Player* p1 = g->getPlayer1();
	Player* p2 = g->getPlayer2();
	Board* b = g->getBoard();
	queue<Tile*> * tileQueue = g->getQueueOfTiles();
	vector<Tile*> tileVect;
	while (!tileQueue->empty()) {
		tileVect.push_back(tileQueue->front());
		tileQueue->pop();
	}
	random_shuffle(tileVect.begin(), tileVect.end());
	for (int i = 0; i < tileVect.size(); i++) {
		tileQueue->push(tileVect[i]);
	}
	Tile* firstTile = new Tile("TLTJ-");
	firstTile->setPosition(0, 0);
	b->addTile(firstTile);
	cout << "Game begins, starting tile placed:" << endl << endl;
	firstTile->print();
	cout << endl << endl << endl << endl;
	
	Tile* currentTile;
	Player* currentPlayer;
	for (int i = 1; !tileQueue->empty(); i++) {
		if (i % 2 == 1) {
			currentPlayer = p1;
		}
		else {
			currentPlayer = p2;
		}
		currentTile = tileQueue->front();
		currentPlayer->setCurrentTile(currentTile);
		tileQueue->pop();
		currentPlayer->makeSmarterMove();
		currentPlayer->getTigersBack();
		cout << "Player " << currentPlayer->getPlayerNumber() << " has " << currentPlayer->getNumberOfTigers() << " tigers and " << currentPlayer->getNumberOfCrocodiles() << " crocodiles left." << endl;
		if (currentPlayer == p1) {
			currentPlayer = p2;
		}
		else {
			currentPlayer = p1;
		}
		currentPlayer->setCurrentTile(currentTile);
		currentPlayer->getTigersBack();
		cout << "Player " << currentPlayer->getPlayerNumber() << " has " << currentPlayer->getNumberOfTigers() << " tigers and " << currentPlayer->getNumberOfCrocodiles() << " crocodiles left." << endl << endl;
		cout << endl << endl << endl << endl;
	}
	 	return 0;
}
