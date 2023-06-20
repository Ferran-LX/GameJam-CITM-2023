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
#define NUM_IMAGES 2
	SDL_Texture* ArrayImagesHud[NUM_IMAGES];
	
	bool stopEcho = true;

private:
	int score;
	int score2;
	int highScore;
	int sizeVector;



























	int widthLetter = 100;
	int startTime;

	std::vector<abecedari> vectorABC;
	


	/*SDL_Texture* textureFont = nullptr;
	SDL_Texture* textureIcons = nullptr;*/

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