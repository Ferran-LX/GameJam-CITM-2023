#ifndef __MODULE_INSERTCOIN_H__
#define __MODULE_INSERTCOIN_H__

#include <vector>
#include <string>

#include <SDL.h> 
#include <SDL_image.h> 

#include "../Module.h"
#include "../../Utils/p2Point.h"

struct abecedari2 {
	char lletra;
	int posicio;
};


class ModuleInsertCoin : public Module {

public:
	ModuleInsertCoin(bool startEnabled);
	~ModuleInsertCoin();

	bool Start() override;
	Update_Status Update() override;
	Update_Status PostUpdate() override;
	bool CleanUp();


private:
	int coins;
	int sizeVector;
	int widthLetter = 25;

	std::vector<abecedari2> vectorABC;

	//std::string str_insertCoin = "INSERT A COIN ";
	std::string str_insertCoin = "CREDIT ";

	SDL_Texture* texture = nullptr;

	int PosLetter(char leterToSearch);
	int LoadVector();
	void PaintSentence(std::string sentenceToPaint, iPoint positionToPaint);

	iPoint posPlayer1, posPlayer2, posHlScrore;
	iPoint posScore1, posScore2, posScoreHl;
};

#endif