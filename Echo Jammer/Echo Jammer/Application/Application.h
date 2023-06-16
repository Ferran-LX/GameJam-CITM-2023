#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"
#include <vector>

class Module;

class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleAudio;
class ModulePlayer;
class ModuleParticles;
class ModuleCollisions;
class ModuleEnemies;
class ModuleFadeToBlack;
class ModuleFonts;
class ModuleRender;
class ModuleHUD;
class ModuleInsertCoin;

class ScenePreintro;
class SceneIntro;
class SceneStart;
class SceneEscoger;
class SceneLevel1;
class SceneLevel1_Foreground;
class ScenePantallaLose;
class SceneOutro;

class Application {

public:
	//Constructor. Creates all necessary modules for the application
	Application();

	//Destructor. Removes all module objects
	~Application();

	//Initializes all modules
	bool Init();

	//Updates all modules (PreUpdate, Update and PostUpdate)
	Update_Status Update();

	//Releases all the application data
	bool CleanUp();


public:
	// An array to store all modules
	//Module* modules[NUM_MODULES];
	std::vector<Module*> modules;

	// All the modules stored individually
	ModuleWindow* window = nullptr;
	ModuleInput* input = nullptr;
	ModuleTextures* textures = nullptr;
	ModuleAudio* audio = nullptr;
	ModulePlayer* player = nullptr;
	ModuleEnemies* enemies = nullptr;
	ModuleParticles* particles = nullptr;
	ModuleCollisions* collisions = nullptr;
	ModuleFadeToBlack* fade = nullptr;
	ModuleFonts* fonts = nullptr;
	ModuleRender* render = nullptr;
	ModuleHUD* hud = nullptr;
	ModuleInsertCoin* insertCoins = nullptr;

	ScenePreintro* scenePreintro = nullptr;
	SceneIntro* sceneIntro = nullptr;
	SceneStart* sceneStart = nullptr;
	SceneEscoger* sceneEscoger = nullptr;
	SceneLevel1* sceneLevel_1 = nullptr;
	SceneLevel1_Foreground* sceneLevel_1_foreground = nullptr;
	ScenePantallaLose* scenePantallaLose = nullptr;
	SceneOutro* sceneOutro = nullptr;

private:
	int sizeVector = 0;
};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__