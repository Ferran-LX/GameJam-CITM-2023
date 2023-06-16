#ifndef __MODULE_HUD_H__
#define __MODULE_HUD_H__

#include <vector>
#include <string>

#include <SDL.h> 
#include <SDL_image.h> 

#include "../Module.h"
#include "../../Utils/p2Point.h"

struct abecedari {
	char lletra;
	int posicio;
};


class ModuleHUD : public Module {

public:
	ModuleHUD(bool startEnabled);
	~ModuleHUD();

	bool Start() override;
	Update_Status Update() override;
	Update_Status PostUpdate() override;
	bool CleanUp();



private:
	int score;
	int score2;
	int highScore;
	int sizeVector;
	int widthLetter = 25;

	std::vector<abecedari> vectorABC;

	std::string player1 = "Player 1";
	std::string player2 = "Player 2";
	std::string hlScore = "Hi-Score";
	std::string X = "x";

	SDL_Texture* textureFont = nullptr;
	SDL_Texture* textureIcons = nullptr;

	int PosLetter(char leterToSearch);
	int LoadVector();
	void PaintSentence(std::string sentenceToPaint, iPoint positionToPaint);

	iPoint posPlayer1, posPlayer2, posHlScrore;
	iPoint posScore1, posScore2, posScoreHl;
	iPoint posIconVides, posIconBombes;
	iPoint posContadorVides, posContadorBombes;

	SDL_Rect tamanyIconaVida;
	SDL_Rect tamanyIconaBombes;

	//IMPRIMEIX ELS CARÀCTER DEL VECTOR 
};

#endif