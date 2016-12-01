#include "Feature.h";
using namespace std;
#define NA 100

class Tile {

	string name;
	Feature *N_feat, *NE_feat, *E_feat, *SE_feat, *S_feat, *SW_feat, *W_feat, *NW_feat, *C_feat;
	int xpos, ypos;
	Feature* inTilePositions[9];

public:

	Tile(string Name);
	bool hasDen();
	void setWfeat(Feature* const &f);
	void setNfeat(Feature* const &f);
	void setEfeat(Feature* const &f);
	void setSfeat(Feature* const &f);
	void setPosition(int x, int y);
	string getName();
	Feature* getNfeat();
	Feature* getNEfeat();
	Feature* getEfeat();
	Feature* getSEfeat();
	Feature* getSfeat();
	Feature* getSWfeat();
	Feature* getWfeat();
	Feature* getNWfeat();
	Feature* getCfeat();
	Feature* getFeatAt(int pos);
	int getX();
	int getY();
	void rotateCCW();
	//Given the number corresponding to a feature on the current tile,
	//return the smallest number that corresponds to that feature, if applicable
	int minInTilePlacement(int num);
	int minInTilePlacement(Feature* const &curr, int &num);
	bool canPlaceCrocodile();
	void addCrocodile();
	vector<int> possibleTigerPlacements();
	int bestTigerPlacement();
	int getPossiblePoints();
	void print();

};