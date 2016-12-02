#include "Feature.h"
#include <iostream>


//Feature


Feature::Feature() {}
bool Feature::isVisited() {
	return visited;
}
void Feature::setVisited(bool v) {
	visited = v;
}
vector<Feature*> Feature::getConnectedFeatures() {
	return connectedFeatures;
}
void Feature::addTiger(int player) {
	switch (player) {
	case 1: hasP1tiger = true; break;
	case 2: hasP2tiger = true; break;
	}
}
void Feature::merge(Feature* const &f) {
	connectedFeatures.push_back(f);
	f->connectedFeatures.push_back(this);
	mergeFeature(f);
}


//Den


Den::Den() {
	visited = false;
	hasP1tiger = false;
	hasP2tiger = false;
}
char Den::getType() {
	return type;
}
void Den::checkIfScored(int &numberOfP1Tigers, int &numberOfP2Tigers) {
	return;
}
void Den::mergeFeature(Feature* const &f) {}
bool Den::canPlaceTiger() {
	return true;
}
bool Den::canPlaceCrocodile() {
	return false;
}
int Den::getPotentialPoints() {
	return 2;
}
void Den::addCrocodile() {}


//Lake


Lake::Lake(bool isWall, int nWalls) {
	wall = isWall;
	numberOfWalls = nWalls;
	visited = false;
	hasP1tiger=false;
	hasP2tiger=false;

	hasBoar = false;
	hasBuffalo = false;
	hasDeer = false;
	hasCrocodile = false;
};
Lake::Lake(bool isWall, int nWalls, char animal) {
	wall = isWall;
	numberOfWalls = nWalls;
	visited = false;


	hasBoar = false;
	hasBuffalo = false;
	hasDeer = false;
	hasCrocodile = false;
	switch (animal) {
	case 'P': hasBoar = true; break;
	case 'B': hasBuffalo = true; break;
	case 'D': hasDeer = true; break;
	case 'C': hasCrocodile = true; break;
	}
}
char Lake::getType() {
	return type;
};
void Lake::mergeFeature(Feature* const &f) {
	Lake * c = dynamic_cast<Lake *> (f);
	lakeConnected.push_back(c);
	c->lakeConnected.push_back(this);
};

//PLACE LAKE METHODS FROM SCORE DOWNWARD
void Lake::traverseLakeForScore(Lake * previousLake,Lake *startingLake,bool &finishedChecking,int &lakeSize,bool &hasDeer, bool &hasBuffalo, bool &hasBoar, int &numberOfCrocodiles,int &player1,int &player2){
	if(this->wall==true){
		lakeSize++;
		player1+=hasP1tiger;
		player2+=hasP2tiger;
		hasDeer|=this->hasDeer;
		hasBuffalo|=this->hasBuffalo;
		hasBoar|=this->hasBoar;
		numberOfCrocodiles+=hasCrocodile;
		return;
	}
	if(this==startingLake){
		finishedChecking=true;
		return;
	}
	if(startingLake->wall==true && this->wall!=true){
		startingLake=this;
	}
		lakeSize++;
		player1+=hasP1tiger;
		player2+=hasP2tiger;
		hasDeer|=this->hasDeer;
		hasBuffalo|=this->hasBuffalo;
		hasBoar|=this->hasBoar;
		numberOfCrocodiles+=hasCrocodile;
	
	for(int i=0;i<lakeConnected.size();i++){
		if(lakeConnected[i]!=previousLake){
		lakeConnected[i]->traverseLakeForScore(this,startingLake,finishedChecking,lakeSize,hasDeer,hasBuffalo,hasBoar,numberOfCrocodiles,player1,player2);
		}
		if(finishedChecking){
			return;
		}
	}
	return;
};
bool Lake::traverseLakeForCompleteness(Lake * previousLake,Lake *startingLake,bool &finishedChecking,int &player1, int&player2){
	if(this->wall==true){
		player1+=hasP1tiger;
		player2+=hasP2tiger;
		return true;
	}
	if(this==startingLake){
		finishedChecking=true;
		return true;
	}
	if(this->wall==false && (lakeConnected.size()+numberOfWalls)!=4){
		return false;
	}
	
	if(startingLake->wall==true && this->wall!=true){
		startingLake=this;
	}
	
		bool isComplete=true;
		player1+=hasP1tiger;
		player2+=hasP2tiger;
		
	for(int i=0;i<lakeConnected.size();i++){
		if(lakeConnected[i]!=previousLake){
		isComplete&=lakeConnected[i]->traverseLakeForCompleteness(this,startingLake,finishedChecking,player1,player2);
		}
		if(finishedChecking || isComplete==false){
			return isComplete;
		}
	}
	return isComplete;
};


bool Lake::traverseLakeForTigers(Lake *previousLake, Lake *startingLake){
	if(this->wall==true){
		if(hasP1tiger || hasP2tiger){
			return false;
		}
		return true;
	}
	
	if(this==startingLake){
		return true;
	}
	
	if(startingLake->wall==true && this->wall!=true){
		startingLake=this;
	}
	
	if(hasP1tiger||hasP2tiger){
		return false;
	}
	bool isNotOwnedByAPlayer=true;	
	for(int i=0;i<lakeConnected.size();i++){
		if(lakeConnected[i]!=previousLake){
		isNotOwnedByAPlayer&=lakeConnected[i]->traverseLakeForTigers(this,startingLake);
		}
		if(isNotOwnedByAPlayer==false){
			break;
		}
	}
	return isNotOwnedByAPlayer;	
};


bool Lake::traverseLakeForCrocodiles(Lake *previousLake, Lake *startingLake){
	if(this->wall==true){
		if(this->hasCrocodile==true){
			return false;
		}
		return true;
	}
	if(this==startingLake){
		return true;
	}
	if(startingLake->wall==true && this->wall!=true){
		startingLake=this;
	}
	if(this->hasCrocodile==true){
		return false;
	}
	bool isNotOwnedByCrocodile=true;	
	for(int i=0;i<lakeConnected.size();i++){
		if(lakeConnected[i]!=previousLake){
		isNotOwnedByCrocodile&=lakeConnected[i]->traverseLakeForCrocodiles(this,startingLake);
		}
		if(isNotOwnedByCrocodile==false){
			break;
		}
	}
	return isNotOwnedByCrocodile;	
};


void Lake::checkIfScored(int &numberOfP1Tigers,int&numberOfP2Tigers){
	if(hasBeenCheckedForCompleteness==false){
	bool isComplete;
	numberOfP1Tigers=hasP1tiger;
	numberOfP2Tigers=hasP2tiger;
	bool finishedChecking=false;
	if(lakeConnected.empty()){
		isComplete=false;
	} else{
		isComplete=true;
	}
	if(this->wall==false && (lakeConnected.size()+numberOfWalls)!=4){
			isComplete=false;
	}
	for(int i=0;i<lakeConnected.size();i++){
		isComplete&=lakeConnected[i]->traverseLakeForCompleteness(this,this,finishedChecking,numberOfP1Tigers,numberOfP2Tigers);
		if(finishedChecking||isComplete==false){
			break;
		}
	}

	if(isComplete){
		cout<<"lake is complete"<<endl;
		cout<<numberOfP1Tigers<<endl;
		cout<<numberOfP2Tigers<<endl;
	} else {
		numberOfP1Tigers=0;
		numberOfP2Tigers=0;
	}
		hasBeenCheckedForCompleteness=true;
	}
};


bool Lake::canPlaceTiger(){
	bool placeTiger=(!hasP1tiger&&!hasP2tiger);
	for(int i=0;i<lakeConnected.size();i++){
		placeTiger&=lakeConnected[i]->traverseLakeForTigers(this,this);
		if(placeTiger==false){
			break;
		}
	}
	if(placeTiger){
		cout<<"Can place Tiger"<<endl;
	} else{
		cout<<"Can't Place Tiger"<<endl;
	}
	return placeTiger;
};


bool Lake::canPlaceCrocodile(){
	bool placeCrocodile=!hasCrocodile;
	for(int i=0;i<lakeConnected.size();i++){
		placeCrocodile&=lakeConnected[i]->traverseLakeForCrocodiles(this,this);
		if(placeCrocodile==false){
			break;
		}
	}
	if(placeCrocodile){
		cout<<"Can place Crocodile"<<endl;
	} else{
		cout<<"Can't Place Crocodile"<<endl;
	}
	return placeCrocodile;
	
};


int Lake::getPotentialPoints(){
	int numberOfP1Tigers=hasP1tiger;
	int numberOfP2Tigers=hasP2tiger;
	bool hasDeer=this->hasDeer;
	bool hasBoar=this->hasBoar;
	bool hasBuffalo=this->hasBuffalo;
	int numberOfCrocodiles=this->hasCrocodile;
	bool finishedChecking=false;
	int lakeSize=1;
	for(int i=0;i<lakeConnected.size();i++){
		lakeConnected[i]->traverseLakeForScore(this,this,finishedChecking,lakeSize,hasDeer,hasBuffalo,hasBoar,numberOfCrocodiles,numberOfP1Tigers,numberOfP2Tigers);
	}
	int scoringFactor=0;
	if(hasDeer+hasBuffalo+hasBoar-numberOfCrocodiles<=0){
		scoringFactor=1;
	} else {
		scoringFactor=hasDeer+hasBuffalo+hasBoar-numberOfCrocodiles;
	}
	if(numberOfP1Tigers<numberOfP2Tigers){
		scoringFactor*=-1;
	}
	potentialPoints=lakeSize*scoringFactor;
	return  lakeSize*scoringFactor;
	
	
};

void Lake::addCrocodile() {
	hasCrocodile = true;
	numberOfCrocodile += 1;
}


//Jungle


Jungle::Jungle() {
	visited = false;
}
void Jungle::traverse(Jungle* const &current, int &completedLakes, int &p1tigers, int &p2tigers) {
	current->visited = true;
	if (current->hasP1tiger) {
		p1tigers += 1;
	}
	if (current->hasP2tiger) {
		p2tigers += 1;
	}
	for (int i = 0; i < current->getConnectedFeatures().size(); i++) {
		if (!current->getConnectedFeatures()[i]->isVisited()) {
			traverse(dynamic_cast<Jungle*>(current->getConnectedFeatures()[i]), completedLakes, p1tigers, p2tigers);
		}
	}
	current->visited = false;
}
char Jungle::getType() {
	return type;
};
void Jungle::mergeFeature(Feature* const &f) {
	Jungle* j = dynamic_cast<Jungle*>(f);
}
void Jungle::checkIfScored(int &numberOfP1Tigers, int&numberOfP2Tigers) {}
bool Jungle::canPlaceTiger() {
	int p1tigers;
	int p2tigers;
	int completedLakes;
	traverse(this, completedLakes, p1tigers, p2tigers);
	if (p1tigers + p2tigers == 0) {
		return true;
	}
	else {
		return false;
	}
}
bool Jungle::canPlaceCrocodile() {
	return true;
}
void Jungle::addCrocodile() {}
int Jungle::getPotentialPoints() {
	return 0;
}

//GameTrail


GameTrail::GameTrail() {
	gameTrailEnd = false;
	hasBoar = false;
	hasBuffalo = false;
	hasDeer = false;
	hasCrocodile = false;
	visited = false;
};
GameTrail::GameTrail(char animal) {
	hasBoar = false;
	hasBuffalo = false;
	hasDeer = false;
	hasCrocodile = false;
	gameTrailEnd = false;
	visited = false;
	switch (animal) {
	case 'P': hasBoar = true; break;
	case 'B': hasBuffalo = true; break;
	case 'D': hasDeer = true; break;
	case 'C': hasCrocodile = true; break;
	}
}
GameTrail::GameTrail(bool end) {
	hasBoar = false;
	hasBuffalo = false;
	hasDeer = false;
	hasCrocodile = false;
	gameTrailEnd = end;
	visited = false;
}
GameTrail::GameTrail(char animal, bool end) {
	hasBoar = false;
	hasBuffalo = false;
	hasDeer = false;
	hasCrocodile = false;
	gameTrailEnd = end;
	visited = false;
	switch (animal) {
	case 'P': hasBoar = true; break;
	case 'B': hasBuffalo = true; break;
	case 'D': hasDeer = true; break;
	case 'C': hasCrocodile = true; break;
	}
}
char GameTrail::getType() {
	return type;
};
void GameTrail::mergeFeature(Feature * const &f) {
	GameTrail * g = dynamic_cast<GameTrail *> (f);
	gameTrailsConnected.push_back(g);
	g->gameTrailsConnected.push_back(this);
};
int GameTrail::traverseGameTrailForScore(GameTrail * previousGameTrail, GameTrail * startingGameTrail,int &numberOfGameTrailEnds,int &numberOfPrey,int &numberOfCrocodiles,int &player1,int &player2){
	if(gameTrailEnd){
		numberOfGameTrailEnds++;
		if(hasBoar||hasDeer||hasBuffalo){
			numberOfPrey++;
		}
		numberOfCrocodiles+=hasCrocodile;
		player1+=hasP1tiger;
		player2+=hasP2tiger;
		return 1;
	}
	if(this==startingGameTrail){
		return 0;
	}
	if(gameTrailsConnected.size()==1){
		player1+=hasP1tiger;
		player2+=hasP2tiger;
		return 1;
	}
	
	player1+=hasP1tiger;
	player2+=hasP2tiger;
	if(this->hasBoar||this->hasDeer||this->hasBuffalo){
			numberOfPrey++;
	}
	int roadSize=0;
	numberOfCrocodiles+=hasCrocodile;	
	if(gameTrailsConnected[0]==previousGameTrail){
		roadSize+=gameTrailsConnected[1]->traverseGameTrailForScore(this,startingGameTrail,numberOfGameTrailEnds,numberOfPrey,numberOfCrocodiles,player1,player2);
	} else {
		roadSize+=gameTrailsConnected[0]->traverseGameTrailForScore(this,startingGameTrail,numberOfGameTrailEnds,numberOfPrey,numberOfCrocodiles,player1,player2);
	}
	roadSize++;
	return roadSize;
	
};

void GameTrail::traverseGameTrailForCompleteness(GameTrail * previousGameTrail, GameTrail * startingGameTrail,int &numberOfGameTrailEnds,bool &isComplete,int &player1, int &player2){
	if(gameTrailEnd){
		numberOfGameTrailEnds++;
		player1+=hasP1tiger;
		player2+=hasP2tiger;
		return;
	}
	if(this==startingGameTrail){
		isComplete=true;
		return;
	}
	if(gameTrailsConnected.size()==1){
		return;
	}
	
	player1+=hasP1tiger;
	player2+=hasP2tiger;
	if(gameTrailsConnected[0]==previousGameTrail){
		gameTrailsConnected[1]->traverseGameTrailForCompleteness(this,startingGameTrail,numberOfGameTrailEnds,isComplete,player1,player2);
	} else{
	    gameTrailsConnected[0]->traverseGameTrailForCompleteness(this,startingGameTrail,numberOfGameTrailEnds,isComplete,player1,player2);
	}
	return;
	
};


bool GameTrail::traverseGameTrailForTigers(GameTrail * previousGameTrail, GameTrail * startingGameTrail){
	if(this==startingGameTrail){
		return true;
	}
	if(gameTrailsConnected.size()==1){
		if(hasP1tiger||hasP2tiger){
				return false;
		}
		return true;
	}
	
	if(hasP1tiger||hasP2tiger){
		return false;
	}
	bool canPlaceTiger=true;
	if(gameTrailsConnected[0]==previousGameTrail){
		canPlaceTiger&=gameTrailsConnected[1]->traverseGameTrailForTigers(this,startingGameTrail);
	} else {
		canPlaceTiger&=gameTrailsConnected[0]->traverseGameTrailForTigers(this,startingGameTrail);
	}
	return canPlaceTiger;
	
};

bool GameTrail::traverseGameTrailForCrocodile(GameTrail * previousGameTrail,GameTrail * startingGameTrail){
	if(this==startingGameTrail){
		return true;
	}
	if(gameTrailsConnected.size()==1){
		if(hasCrocodile){
				return false;
		}
		return true;
	}
	
	if(hasCrocodile){
		return false;
	}
	bool canPlaceCrocodile=true;
	if(gameTrailsConnected[0]==previousGameTrail){
		canPlaceCrocodile&=gameTrailsConnected[1]->traverseGameTrailForCrocodile(this,startingGameTrail);
	} else {
		canPlaceCrocodile&=gameTrailsConnected[0]->traverseGameTrailForCrocodile(this,startingGameTrail);
	}
	return canPlaceCrocodile;
	
};


void GameTrail::checkIfScored(int &numberOfP1Tigers,int &numberOfP2Tigers){
	if(hasBeenCheckedForCompleteness==false){
	GameTrail * startingGameTrail=this;
	int numberOfGameTrailEnds=0;
	numberOfP1Tigers=hasP1tiger;
	numberOfP2Tigers=hasP2tiger;
	bool isComplete=false;
	if(gameTrailEnd){
		numberOfGameTrailEnds++;
	}
	for(int i=0;i<gameTrailsConnected.size();i++){
		gameTrailsConnected[i]->traverseGameTrailForCompleteness(startingGameTrail,startingGameTrail,numberOfGameTrailEnds,isComplete,numberOfP1Tigers,numberOfP2Tigers);
		if(isComplete){
			break;
		}
	}
	if(numberOfGameTrailEnds==2){
		isComplete=true;
	}
	if(isComplete){
	cout<<"You have scored!"<<endl;
	cout<<numberOfP1Tigers<<endl;
	cout<<numberOfP2Tigers<<endl;
	}
	hasBeenCheckedForCompleteness=true;
	}
};

bool GameTrail::canPlaceTiger(){
	bool canPlaceTiger=(!hasP1tiger&&!hasP2tiger); 
	GameTrail * startingGameTrail=this;
	for(int i=0;i<gameTrailsConnected.size();i++){                                                        
		canPlaceTiger&=gameTrailsConnected[i]->traverseGameTrailForTigers(startingGameTrail,startingGameTrail);
		if(canPlaceTiger==false){
			break;
		}
	}
	if(canPlaceTiger){
		cout<<"You can place a tiger"<<endl;
	} else{
		cout<<"You cannot place a tiger"<<endl;
	}
return canPlaceTiger;	
};

bool GameTrail::canPlaceCrocodile(){
	bool placeCrocodile=!hasCrocodile;
	GameTrail * startingGameTrail=this;
	for(int i=0;i<gameTrailsConnected.size();i++){                                                        
		placeCrocodile&=gameTrailsConnected[i]->traverseGameTrailForTigers(startingGameTrail,startingGameTrail);
		if(placeCrocodile==false){
			break;
		}
	}
	if(placeCrocodile){
		cout<<"You can place a tiger"<<endl;
	} else{
		cout<<"You cannot place a tiger"<<endl;
	}
return placeCrocodile;
	
};
int GameTrail::getPotentialPoints(){
	int numberOfP1Tigers=hasP1tiger;
	int numberOfP2Tigers=hasP2tiger;
	int numberOfGameTrailEnds=gameTrailEnd;
	int numberOfCrocodiles=hasCrocodile;
	int roadSize=1;
	int numberOfPrey=hasDeer||hasCrocodile||hasBuffalo;
	for(int i=0;i<gameTrailsConnected.size();i++){
		roadSize+=gameTrailsConnected[i]->traverseGameTrailForScore(this,this,numberOfGameTrailEnds,numberOfPrey,numberOfCrocodiles,numberOfP1Tigers,numberOfP2Tigers);
	}
	int scoringFactor=0;
	if(numberOfP1Tigers>=numberOfP2Tigers){
		scoringFactor=1;
	} else {
		scoringFactor=-1;
	}
	potentialPoints=scoringFactor*(roadSize+numberOfPrey-numberOfCrocodiles);
	return scoringFactor*(roadSize+numberOfPrey-numberOfCrocodiles);
};


void GameTrail::addCrocodile() {}

int main(){

// Starting at row 2, column 1 from left to right on "Catalog of tile types". 
// Lake Features  

	Feature * f1  = new Lake(false, 0);
	Feature * f2  = new Lake(false, 1);
	Feature * f3  = new Lake(false, 2);
	Feature * f4  = new Lake(false, 2);
	Feature * f5a = new Lake(true, 1);
	Feature * f5b = new Lake(true, 1);
	Feature * f6  = new Lake(true, 3);
	Feature * f7a = new Lake(true, 1);
	Feature * f7b = new Lake(true, 1);
	Feature * f8  = new Lake(true, 3);
	Feature * f9  = new Lake(true, 3);
	Feature * f10 = new Lake(true, 3);
	Feature * f11 = new Lake(true, 3);
	Feature * f12 = new Lake(true, 3);
	Feature * f13 = new Lake(true, 3);
	Feature * f14 = new Lake(false, 1);
	Feature * f15 = new Lake(true, 3);
	Feature * f16 = new Lake(true, 3);
	Feature * f17 = new Lake(false, 2);
	Feature * f18 = new Lake(false, 2);
	Feature * f19 = new Lake(true, 3);
	Feature * f20 = new Lake(true, 3);
	Feature * f21 = new Lake(false, 1);

// Merging multiple combinations of 'lake' tiles to check whether or not a tiger can be placed.
// If a tiger can be placed, check if it is scored for testing purposes.

	/*f1->merge(f2);
	f1->addTiger(1);
	int a=0;
	int b=0;
	f1->canPlaceTiger();
	f2->canPlaceTiger();
	f1->checkIfScored(a,b);
	a=0;
	b=0;
	f2->checkIfScored(a,b);

	f3->merge(f4);
	f3->addTiger(1);
	f3->canPlaceTiger();
	f4->canPlaceTiger();
	f3->checkIfScored(a,b);
	f4->checkIfScored(a,b);
	
	f5->merge(f6);
	f5->addTiger(1);
	f5->canPlaceTiger();
	f6->canPlaceTiger();
	f5->checkIfScored(a,b);
	f6->checkIfScored(a,b);*/

	/*f7a->merge(f8);
	f7a->addTiger(1);
	int a = 0;
	int b = 0;
	f7a->canPlaceTiger();
	f8->canPlaceTiger();
	f7a->checkIfScored(a,b);
	a=0;
	b=0;
	f8->checkIfScored(a,b);

	f7b->merge(f9);
	f7b->addTiger(1);
	f7b->canPlaceTiger();
	f9->canPlaceTiger();
	f7b->checkIfScored(a,b);
	f9->checkIfScored(a,b);*/

	/*f10->merge(f11);
	f10->addTiger(1);
	int a = 0;
	int b = 0;
	f10->canPlaceTiger();
	f11->canPlaceTiger();
	f10->checkIfScored(a,b);
	a=0;
	b=0;
	f11->checkIfScored(a,b);*/

	/*f12->merge(f13);
	f12->addTiger(1);
	int a = 0;
	int b = 0;
	f12->canPlaceTiger();
	f13->canPlaceTiger();
	f12->checkIfScored(a,b);
	a=0;
	b=0;
	f13->checkIfScored(a,b);*/

	/*f14->merge(f15);
	f14->addTiger(1);
	int a = 0;
	int b = 0;
	f14->canPlaceTiger();
	f15->canPlaceTiger();
	f14->checkIfScored(a,b);
	a=0;
	b=0;
	f15->checkIfScored(a,b);*/

	/*f16->merge(f17);
	f16->addTiger(1);
	int a = 0;
	int b = 0;
	f16->canPlaceTiger();
	f17->canPlaceTiger();
	f16->checkIfScored(a,b);
	a=0;
	b=0;
	f17->checkIfScored(a,b);*/

	/*f18->merge(f19);
	f18->addTiger(1);
	int a = 0;
	int b = 0;
	f18->canPlaceTiger();
	f19->canPlaceTiger();
	f18->checkIfScored(a,b);
	a=0;
	b=0;
	f19->checkIfScored(a,b);*/

	/*f20->merge(f21);
	f20->addTiger(1);
	int a = 0;
	int b = 0;
	f20->canPlaceTiger();
	f21->canPlaceTiger();
	f20->checkIfScored(a,b);
	a=0;
	b=0;
	f21->checkIfScored(a,b);*/

	/*f5a->merge(f6);
	f5a->addTiger(1);
	int a=0;
	int b=0;
	f5a->canPlaceTiger();
	f6->canPlaceTiger();
	f5a->checkIfScored(a,b);
	a=0;
	b=0;
	f6->checkIfScored(a,b);*/

	/*f6->merge(f3);
	f3->merge(f8);
	f6->addTiger(1);
	f3->canPlaceTiger();
	f3->addTiger(1);
	int a=0;
	int b=0;
	f6->canPlaceTiger();
	f3->canPlaceTiger();
	f8->canPlaceTiger();
	f6->checkIfScored(a,b);
	a=0;
	b=0;
	f6->checkIfScored(a,b);

	f7b->merge(f8);
	f7b->addTiger(1);
	f7b->canPlaceTiger();
	f8->canPlaceTiger();
	f7b->checkIfScored(a,b);
	f8->checkIfScored(a,b);*/

// Road Tile Features

	Feature * g1   = new GameTrail(true); 
	Feature * g2a  = new GameTrail(true); 
	Feature * g2b  = new GameTrail(true);
	Feature * g2c  = new GameTrail(true);
	Feature * g2d  = new GameTrail(true);
	Feature * g3   = new GameTrail(false);
	Feature * g4   = new GameTrail(false);
	Feature * g5a  = new GameTrail(true);
	Feature * g5b  = new GameTrail(true);
	Feature * g5c  = new GameTrail(true);
	Feature * g6   = new GameTrail(false);
	Feature * g7   = new GameTrail(false);
	Feature * g8   = new GameTrail(false);
 	Feature * g9   = new GameTrail(false);
	Feature * g10  = new GameTrail(false);
	Feature * g11  = new GameTrail(false);
	Feature * g12  = new GameTrail(true);
	Feature * g13a = new GameTrail(true);
	Feature * g13b = new GameTrail(true);
	Feature * g13c = new GameTrail(true);	
	Feature * g14a = new GameTrail(true);
	Feature * g14b = new GameTrail(true);
	Feature * g14c = new GameTrail(true);
	Feature * g15  = new GameTrail(false);
	Feature * g16  = new GameTrail(false);
	Feature * g17  = new GameTrail(true);
	Feature * g18  = new GameTrail(true);
	Feature * g19  = new GameTrail(true);

// Testing the completeness of a road and whether a tiger can be placed and checking the score.

	/*g1->merge(g2a);
	g1->addTiger(1);
	g2a->addTiger(1);
	int a=0;
	int b=0;
	g1->canPlaceTiger();
	g2a->canPlaceTiger();
	g1->checkIfScored(a,b);
	a=0;
	b=0;
	g2a->checkIfScored(a,b);*/

	/*g6a->merge(g7a);
	g6a->addTiger(1);
	int a = 0;
	int b = 0; 
	g6a->canPlaceTiger();
	g7a->canPlaceTiger();
	g6a->checkIfScored(a,b);
	a=0;
	b=0;
	g7a->checkIfScored(a,b);*/

	/*g1->merge(g12);
	g1->addTiger(1);
	int a = 0;
	int b = 0;
	g1->canPlaceTiger();
	g12->canPlaceTiger();
	g1->checkIfScored(a,b);
	a=0;
	b=0;
	g12->checkIfScored(a,b);*/

	/*g1->merge(g2a);
	g2b->merge(g6);
	g6->merge(g7);
	g7->merge(g8);
	g8->merge(g2c);
	g1->addTiger(1);
	g6->addTiger(1);
	g8->addTiger(1);
	int a = 0;
	int b = 0;
	g1->canPlaceTiger();
	g2a->canPlaceTiger();
	g2b->canPlaceTiger();
	g2c->canPlaceTiger();
	g6->canPlaceTiger();
	g7->canPlaceTiger();
	g8->canPlaceTiger();
	g1->checkIfScored(a,b);
	g2a->checkIfScored(a,b);
	g6->checkIfScored(a,b);
	g8->checkIfScored(a,b);
	a=0;
	b=0;
	g7->checkIfScored(a,b);
	g2b->checkIfScored(a,b);
	g2c->checkIfScored(a,b);*/

	/*g18->merge(g11);
	g11->merge(g19);
	//g18->addTiger(1);
	g11->addTiger(1);
	g19->addTiger(1);
	int a=0;
	int b=0;
	g18->canPlaceTiger();
	g11->canPlaceTiger();
	g19->canPlaceTiger();
	g18->checkIfScored(a,b);
	g11->checkIfScored(a,b);
	g19->checkIfScored(a,b);*/

	/*g18->merge(g11);
	g11->merge(g19);
	//g18->addTiger(2);
	g11->addTiger(2);
	g19->addTiger(2);
	int a=0;
	int b=0;
	g18->canPlaceTiger();
	g11->canPlaceTiger();
	g19->canPlaceTiger();
	g18->checkIfScored(a,b);
	g11->checkIfScored(a,b);
	g19->checkIfScored(a,b);*/

	g1->merge(g2a);
	g2b->merge(g6);
	g6->merge(g7);
	g7->merge(g8);
	g8->merge(g2c);
	g1->addTiger(2);
	g6->addTiger(2);
	g8->addTiger(2);
	int a = 0;
	int b = 0;
	g1->canPlaceTiger();
	g2a->canPlaceTiger();
	g2b->canPlaceTiger();
	g2c->canPlaceTiger();
	g6->canPlaceTiger();
	g7->canPlaceTiger();
	g8->canPlaceTiger();
	g1->checkIfScored(a,b);
	g2a->checkIfScored(a,b);
	g6->checkIfScored(a,b);
	g8->checkIfScored(a,b);
	a=0;
	b=0;
	g7->checkIfScored(a,b);
	g2b->checkIfScored(a,b);
	g2c->checkIfScored(a,b);









};