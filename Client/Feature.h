#include<iostream>
#include<vector>
using namespace std;


//Feature
class Feature {

protected:
	bool visited;
	vector<Feature*> connectedFeatures;
	bool hasP1tiger;
	bool hasP2tiger;
	bool hasCrocodile;

public:

	Feature();
	bool isVisited();
	void setVisited(bool v);
	virtual char getType() = 0; //RETURNS FEATURE TYPE
	virtual void checkIfScored(int &numberOfP1Tigers, int &numberOfP2Tigers) = 0; //CHECKS TO SEE IF FEATURE IS COMPLETED AND CAN BE SCORED,RETURNS NUMBER OF TIGERS
	void merge(Feature* const &f);
	virtual void mergeFeature(Feature * const &f) = 0;  // MERGES TWO FEATURE OBJECTS TOGETHER
	virtual bool canPlaceTiger() = 0;  //RETURNS IF YOU CAN PLACE TIGER ON THAT FEATURE
	virtual bool canPlaceCrocodile() = 0; // RETURNS IF YOU CAN PLACE CROCODILE ON THAT FEATURE
	void addTiger(int player); //place player Tiger
	void addCrocodile(); //Place Crocodile
	virtual int getPotentialPoints() = 0; //Returns potential points
	vector<Feature*> getConnectedFeatures();
	bool hasP1Tiger();
	bool hasP2Tiger();
};


//Den 
class Den : public Feature {

	const char type = 'X';

public:
	Den();
	char getType();
	void checkIfScored(int &numberOfP1Tigers, int &numberOfP2Tigers);
	void mergeFeature(Feature* const &f);
	bool canPlaceTiger();
	bool canPlaceCrocodile();
	int getPotentialPoints();
};


//Lake
class Lake : public Feature {

	const char type = 'L';
	bool isComplete;
	bool hasDeer;
	bool hasBuffalo;
	bool hasBoar;
	bool hasCrocodile;
	int numberOfCrocodile;
	int potentialPoints;
	bool hasBeenCheckedForCompleteness;
	bool wall;
	int numberOfWalls;
	vector < Lake *> lakeConnected;

public:
	Lake(bool isWall, int nWalls);
	Lake(bool isWall, int nWalls, char animal);
	char getType();
	void mergeFeature(Feature* const &f);
	void checkIfScored(int &numberOfP1Tigers, int &numberOfP2Tigers);
	void traverseLakeForScore(Lake * previousLake, Lake *startingLake, bool &finishedChecking, int &lakeSize, int &nWalls, int &nLakes, bool &hasDeer, bool &hasBuffalo, bool &hasBoar, int &numberOfCrocodile, int &player1, int &player2);
	bool traverseLakeForCompleteness(Lake * previousLake, Lake *startingLake,vector<Lake *> &lakesVisited,bool &finishedChecking, int &player1, int &player2);
	bool traverseLakeForTigers(Lake *previousLake, Lake *startingLake);
	bool traverseLakeForCrocodiles(Lake *previousLake, Lake *startingLake);
	bool canPlaceTiger();
	bool canPlaceCrocodile();
	int getPotentialPoints();
};


//Jungle
class Jungle : public Feature {

	const char type = 'J';

public:
	Jungle();
	void traverse(Jungle* const &current, int &completedLakes, int &p1tigers, int &p2tigers);
	void mergeFeature(Feature* const &F);
	char getType();
	void checkIfScored(int &numberOfP1Tigers, int &numberOfP2Tigers);
	bool canPlaceTiger();  //RETURNS IF YOU CAN PLACE TIGER ON THAT FEATURE
	bool canPlaceCrocodile(); // RETURNS IF YOU CAN PLACE CROCODILE ON THAT FEATURE
	int getPotentialPoints(); //Returns potential points
};


//GameTrail
class GameTrail : public Feature {

private:
	vector< GameTrail *> gameTrailsConnected; // All GameTrail 
	const char type = 'T'; //Identify the type of Feature
	bool hasCrocodile;
	bool hasDeer; //tile has Deer
	bool hasBoar; //tile has Boar
	bool hasBuffalo; //tile has Buffalo
	bool hasBeenCheckedForCompleteness;
	bool gameTrailEnd; //The GameTrail is ending
	int  potentialPoints;

public:
	GameTrail();
	GameTrail(char animal);
	GameTrail(bool end);
	GameTrail(char animal, bool end);
	char getType();  //Return Feature Type
	void mergeFeature(Feature* const &f); //connects two GameTrails together
	void checkIfScored(int &numberOfP1Tigers, int &numberOfP2Tigers);
	int traverseGameTrailForScore(GameTrail * previousGameTrail, GameTrail * startingGameTrail, int &numberOfGameTrailEnds, int &numberOfPrey, int &numberOfCrocodiles, int &player1, int &player2);
	void traverseGameTrailForCompleteness(GameTrail * previousGameTrail, GameTrail * startingGameTrail, int &numberOfGameTrailEnds, bool &isComplete, int &player1, int &player2);
	bool traverseGameTrailForTigers(GameTrail * previousGameTrail, GameTrail * startingGameTrail); //traverse the GameTrail to check if any player owns the GameTrail
	bool traverseGameTrailForCrocodile(GameTrail * previousGameTrail, GameTrail * startingGameTrail);
	bool canPlaceTiger();//Checks to see if you can place a tiger
	bool canPlaceCrocodile();
	int getPotentialPoints();
};