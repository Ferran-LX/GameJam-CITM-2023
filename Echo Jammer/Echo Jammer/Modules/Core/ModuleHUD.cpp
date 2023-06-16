#include "ModuleHUD.h"
#include <cctype>
#include "../../Application/Application.h"
#include "../../Application/FileNames.h"
#include "../../Modules/Core/ModuleTextures.h"
#include "../../Modules/Core/ModuleInput.h"
#include "../../Modules/Core/ModuleRender.h"
#include "../../Modules/Gameplay/ModulePlayer.h"

ModuleHUD::ModuleHUD(bool startEnabled) : Module(startEnabled) {

}

ModuleHUD::~ModuleHUD() {
	// Destructor
}

bool ModuleHUD::Start() {
	// Inicializa las variables de puntuación
	score = 0;
	highScore = 0;
	sizeVector = LoadVector();

	tamanyIconaVida.x = 0;
	tamanyIconaVida.y = 0;
	tamanyIconaVida.w = 56;
	tamanyIconaVida.h = 50;

	tamanyIconaBombes.x = 60;
	tamanyIconaBombes.y = 0;
	tamanyIconaBombes.w = 60;
	tamanyIconaBombes.h = 50;

	LOG("Loading HUD textures");
	bool ret = true;
	textureFont = App->textures->Load(FI_HUD_font1.c_str());
	textureIcons = App->textures->Load(FI_Iconos.c_str());

	return ret;
}


Update_Status ModuleHUD::Update()
{
	posIconVides.x = 30 + App->render->camera.x;
	posIconVides.y = 70 + App->render->camera.y;
	posContadorVides.x = 90 + App->render->camera.x;
	posContadorVides.y = 80 + App->render->camera.y;

	posIconBombes.x = 140 + App->render->camera.x;
	posIconBombes.y = 70 + App->render->camera.y;
	posContadorBombes.x = 200 + App->render->camera.x;
	posContadorBombes.y = 80 + App->render->camera.y;

	posPlayer1.x = 30 + App->render->camera.x;
	posPlayer1.y = 0 + App->render->camera.y;
	posScore1.x = 110 + App->render->camera.x;
	posScore1.y = 30 + App->render->camera.y;

	posPlayer2.x = 570 + App->render->camera.x;
	posPlayer2.y = 0 + App->render->camera.y;
	posScore2.x = 650 + App->render->camera.x;
	posScore2.y = 30 + App->render->camera.y;

	posHlScrore.x = 300 + App->render->camera.x;
	posHlScrore.y = 0 + App->render->camera.y;
	posScoreHl.x = 320 + App->render->camera.x;
	posScoreHl.y = 30 + App->render->camera.y;

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleHUD::PostUpdate() {
	// ICONES
	App->render->Blit(textureIcons, posIconVides.x-20, posIconVides.y, &tamanyIconaVida);
	PaintSentence("x", {posContadorVides.x - 20, posContadorVides.y});
	PaintSentence(std::to_string(App->player->lives), { posContadorVides.x, posContadorVides.y });

	App->render->Blit(textureIcons, posIconBombes.x-20, posIconBombes.y, &tamanyIconaBombes);
	PaintSentence("x", {posContadorBombes.x - 20, posContadorBombes.y});
	PaintSentence(std::to_string(App->player->bombs), { posContadorBombes.x, posContadorBombes.y });

	// TEXTOS
	PaintSentence(player1, { posPlayer1.x, posPlayer1.y });
	PaintSentence(std::to_string(App->player->score), { posScore1.x, posScore1.y });

	PaintSentence(player2, { posPlayer2.x, posPlayer2.y });
	PaintSentence("0", {posScore2.x, posScore2.y});

	PaintSentence(hlScore, { posHlScrore.x, posHlScrore.y });
	PaintSentence(std::to_string(655000), { posScoreHl.x, posScoreHl.y });

	//PaintSentence("LOADING...", { 150,550 });


	return Update_Status::UPDATE_CONTINUE;
}

bool ModuleHUD::CleanUp()
{
	return true;
}

int ModuleHUD::PosLetter(char leterToSearch) {

	char upperLetter = static_cast<char>(toupper(leterToSearch)); //  Converts the letter to uppercase

	for (int i = 0; i < sizeVector; i++)
	{
		if (vectorABC[i].lletra == upperLetter)
		{
			return i;
		}
	}
	return 0;
}

int ModuleHUD::LoadVector() {

	vectorABC.push_back({ '!', 0 });
	vectorABC.push_back({ '$', 1 });
	vectorABC.push_back({ '%', 2 });
	vectorABC.push_back({ '&', 3 });
	vectorABC.push_back({ '-', 4 });
	vectorABC.push_back({ '.', 5 });
	vectorABC.push_back({ '/', 6 });

	vectorABC.push_back({ '0', 7 });
	vectorABC.push_back({ '1', 8 });
	vectorABC.push_back({ '2', 9 });
	vectorABC.push_back({ '3', 10 });
	vectorABC.push_back({ '4', 11 });
	vectorABC.push_back({ '5', 12 });
	vectorABC.push_back({ '6', 13 });
	vectorABC.push_back({ '7', 14 });
	vectorABC.push_back({ '8', 15 });
	vectorABC.push_back({ '9', 16 });

	vectorABC.push_back({ '*', 17 }); //star
	vectorABC.push_back({ ';', 18 });
	vectorABC.push_back({ '<', 19 }); //arrow
	vectorABC.push_back({ 'º', 20 }); //heart
	vectorABC.push_back({ '?', 21 });

	vectorABC.push_back({ 'A', 22 });
	vectorABC.push_back({ 'B', 23 });
	vectorABC.push_back({ 'C', 24 });
	vectorABC.push_back({ 'D', 25 });
	vectorABC.push_back({ 'E', 26 });
	vectorABC.push_back({ 'F', 27 });
	vectorABC.push_back({ 'G', 28 });
	vectorABC.push_back({ 'H', 29 });
	vectorABC.push_back({ 'I', 30 });
	vectorABC.push_back({ 'J', 31 });
	vectorABC.push_back({ 'K', 32 });
	vectorABC.push_back({ 'L', 33 });
	vectorABC.push_back({ 'M', 34 });
	vectorABC.push_back({ 'N', 35 });
	vectorABC.push_back({ 'O', 36 });
	vectorABC.push_back({ 'P', 37 });
	vectorABC.push_back({ 'Q', 38 });
	vectorABC.push_back({ 'R', 39 });
	vectorABC.push_back({ 'S', 40 });
	vectorABC.push_back({ 'T', 41 });
	vectorABC.push_back({ 'U', 42 });
	vectorABC.push_back({ 'V', 43 });
	vectorABC.push_back({ 'W', 44 });
	vectorABC.push_back({ 'X', 45 });
	vectorABC.push_back({ 'Y', 46 });
	vectorABC.push_back({ 'Z', 47 });
	vectorABC.push_back({ ' ', 48 });

	return vectorABC.size();
}

void ModuleHUD::PaintSentence(std::string sentenceToPaint, iPoint positionToPaint) {
	int size = sentenceToPaint.size();
	int writedLetters = 0;
	std::vector<int> posicions;
	SDL_Rect cutFont = { 0, 0, 25, 29 };

	for (int i = 0; i < size; i++)
	{
		posicions.push_back(PosLetter(sentenceToPaint[i]));
	}

	for (int i = 0; i < size; i++)
	{
		cutFont.x = widthLetter * posicions[i];
		App->render->Blit(textureFont, positionToPaint.x + (writedLetters * widthLetter), positionToPaint.y, &cutFont);
		writedLetters++;
	}

}