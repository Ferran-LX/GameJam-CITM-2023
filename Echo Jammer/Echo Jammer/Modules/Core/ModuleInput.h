#ifndef __MODULE_INPUT_H__
#define __MODULE_INPUT_H__

#include "../../Modules/Module.h"
#include "../../Application/Globals.h"

#include <SDL_scancode.h>

#define MAX_KEYS 256
#define MAX_PADS 4

struct _SDL_GameController;
struct _SDL_Haptic;

enum Key_State
{
	KEY_IDLE,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};

struct GamePad
{
	//Input data
	bool start, back, guide;
	bool x, y, a, b, l1, r1, l3, r3;
	bool up, down, left, right;
	float l2, r2;
	float l_x, l_y, r_x, r_y, l_dz, r_dz;

	//Controller data
	bool enabled;
	int index;
	_SDL_GameController* controller;
	_SDL_Haptic* haptic;

	//Rumble controller
	int rumble_countdown;
	float rumble_strength;
};

enum KeyboardSetup {
	MoveUp = SDL_Scancode::SDL_SCANCODE_W,
	MoveDown = SDL_Scancode::SDL_SCANCODE_S,
	MoveLeft = SDL_Scancode::SDL_SCANCODE_A,
	MoveRight = SDL_Scancode::SDL_SCANCODE_D,
	Sprint = SDL_Scancode::SDL_SCANCODE_LSHIFT,
	Dash = SDL_Scancode::SDL_SCANCODE_SPACE,
	Pause = SDL_Scancode::SDL_SCANCODE_I

};
class PlayerInput
{
public:
	PlayerInput();
	~PlayerInput();

	Key_State moveUp;
	Key_State moveDown;
	Key_State moveLeft;
	Key_State moveRight;
	Key_State dash;
	Key_State sprint;
	Key_State pause;
	void StoreInput(const Key_State keyboard[MAX_KEYS], const GamePad& gamepad);

};

class ModuleInput : public Module
{
public:
	// Constructor
	ModuleInput(bool startEnabled);

	// Destructor
	~ModuleInput();

	// Called on application start.
	// Initializes the SDL system for input detection
	bool Init() override;

	// Called at the beginning of the application loop
	// Updates all input data received from SDL
	Update_Status PreUpdate() override;

	// Called on application exit.
	// Uninitializes the SDL system for input detection
	bool CleanUp() override;

	// Activates SDL device funcionallity when a gamepad has been connected
	void HandleDeviceConnection(int index);

	// Deactivates SDL device funcionallity when a gamepad has been disconnected
	void HandleDeviceRemoval(int index);

	// Called at PreUpdate
	// Iterates through all active gamepads and update all input data
	void UpdateGamepadsInput();

	bool ShakeController(int id, int duration, float strength = 0.5f);
	const char* GetControllerName(int id) const;

public:
	// An array to fill in the state of all the keyboard keys
	Key_State keys[MAX_KEYS] = { KEY_IDLE };

	// An array to fill in all detected gamepads
	GamePad pads[MAX_PADS];

	PlayerInput controlP1;
};

#endif // __ModuleInput_H__