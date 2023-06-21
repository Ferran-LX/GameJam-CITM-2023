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
class ModuleOscuridad;

class Scene_00_Portada;
class Scene_01_tutorial;
class Scene_02_nivel1;
class Scene_03_nivel2;

class SceneStart;
class SceneIntro;

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
	ModuleOscuridad* oscuridad = nullptr;

	Scene_00_Portada* scene_00_Portada = nullptr;
	Scene_01_tutorial* scene_01_tutorial = nullptr;
	Scene_02_nivel1* scene_02_nivel1 = nullptr;
	Scene_03_nivel2* scene_03_nivel2 = nullptr;
	SceneIntro* sceneIntro = nullptr;
	SceneStart* sceneStart = nullptr;

private:
	int sizeVector = 0;
};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__