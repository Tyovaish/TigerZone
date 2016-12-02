
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


/*
int main() {

	Board * b = new Board();
	Player* p1 = new Player(1, b);

	
	Tile * t1 = new Tile("TTTT-");
	p1->setCurrentTile(t1);
	p1->placeTile(make_pair(make_pair(0, 0), 0));
	
	cout << endl;

	Tile * t2 = new Tile("JLTT-");
	p1->setCurrentTile(t2);
	p1->placeTile(make_pair(make_pair(-1, 0), 90));

	cout << endl;

	Tile * t3 = new Tile("JLTT-");
	p1->setCurrentTile(t3);
	p1->placeTile(make_pair(make_pair(-1, -1), 180));

	cout << endl;

	Tile * t4 = new Tile("JLTT-");
	p1->setCurrentTile(t4);
	p1->placeTile(make_pair(make_pair(0, -1), 270));
	
	cout << endl;


	//GameTrail* gt = dynamic_cast<GameTrail*>(t2->getEfeat());
	
	//gt->checkIfScored();

	p1->setCurrentTile(t3);
	p1->placeTiger(6);

	cout << endl;
	
	system("PAUSE");
	
}
*/

/*
int main() {
	
	Game* game = new Game();
	string fileName = "C:\\Users\\aleca\\Desktop\\GameTiles.txt";
	game->readTilesFromFile(fileName);

	Player* p1 = game->getPlayer1();
	stack<Tile*>* bagOfTiles = game->getBagOfTiles();
	stack<Tile*>* tmp = new stack<Tile*>;
	while (!bagOfTiles->empty()) {
		tmp->push(bagOfTiles->top());
		bagOfTiles->pop();
	}
	bagOfTiles = tmp;
	
	while (!tmp->empty()) {
		p1->setCurrentTile(tmp->top());
		tmp->pop();
		if (game->getBoard()->possiblePositions(p1->getCurrentTile()).size() != 0) {
			pair<pair<int, int>, int> position_orientation = game->getBoard()->possiblePositions(p1->getCurrentTile()).at(0);
			p1->placeTile(position_orientation);
		}
		else {
			cout << "CANNOT PLACE TILE";
		}
		cout << endl;
		cout << endl;
	}
	

	int tilesRead = 0;

	/*
	while (!bagOfTiles->empty()) {
		bagOfTiles->top()->print();
		cout << endl;
		bagOfTiles->pop();
		tilesRead++;
		cout << endl << tilesRead << endl << endl;
	}
	/*
	return 0;
}
*/

/*
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
*/

/*
int main() {
	
	Board * b = new Board();
	Player* p1 = new Player(1, b);


	Tile * t1 = new Tile("LJLJ-");
	p1->setCurrentTile(t1);
	p1->placeTile(make_pair(make_pair(0, 0), 0));

	cout << endl;

	Tile * t2 = new Tile("LLJJ-");
	p1->setCurrentTile(t2);
	p1->placeTile(make_pair(make_pair(0,1), 270));

	cout << endl;

	Tile * t3 = new Tile("LLJJ-");
	p1->setCurrentTile(t3);
	p1->placeTile(make_pair(make_pair(1,1), 180));

	cout << endl;

	Tile * t4 = new Tile("JLJL-");
	p1->setCurrentTile(t4);
	p1->placeTile(make_pair(make_pair(1,0), 90));

	cout << endl;

	Tile * t5 = new Tile("LLJJ-");
	p1->setCurrentTile(t5);
	p1->placeTile(make_pair(make_pair(1, -1), 90));

	cout << endl;

	Tile * t6 = new Tile("LLJJ-");
	p1->setCurrentTile(t6);
	p1->placeTile(make_pair(make_pair(0, -1), 0));

	cout << endl;

	p1->setCurrentTile(t5);
	p1->placeTiger(4);

	cout << endl;

	t1->getSfeat()->checkIfScored();

	cout << endl;

}
*/ 

