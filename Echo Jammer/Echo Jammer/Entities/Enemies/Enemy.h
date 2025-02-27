#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "../../Utils/p2Point.h"
#include "../../Utils/Animation.h"
#include "../../Utils/Directions.h"

#include <functional>
#include <vector>
#include "../../Utils/PatrolPath.h"

#define MAX_TRANSITIONS 5 

struct SDL_Texture;
struct Collider;
struct EnemyStateMachine;
enum class Enemy_Type;
enum Enemy_State;
class ModulePlayer;

class Enemy {
protected:
	// Constructor requerit per classes derivades
	Enemy(int x_, int y_, Enemy_Type type_, Collider* collider_ = nullptr);

public:
	// Constructor
	// Saves the spawn position for later movement calculations
	//Enemy(int x, int y);

	// Destructor
	virtual ~Enemy();

	// Implementacio de la FSM per cadascun dels enemics
	virtual void InitStateMachine();

	// Called from inhering enemies' Uppate
	// Updates animation and collider position
	virtual void Update();

	// Defineix el comportament de cada enemic
	virtual void UpdateBehaviour(const ModulePlayer* player);

	// Called from ModuleEnemies' Update
	virtual void Draw();

	// Resposta de col�lisi�
	virtual void OnCollision(Collider* collider);

	// Marca aquest enemic i el seu collider per ser eliminats
	virtual void SetToDelete();

#pragma region MovementMethods

	virtual Directions ChangeDirection();

	virtual void HandleMove();

	virtual bool Move(Directions dir);

#pragma endregion

#pragma region Setters

	void SetTexture(SDL_Texture* nTexture) { _texture = nTexture; }

	void setAnimation(Animation* nAnim) { _currentAnim = nAnim; }

	void ChangeAnimationSet(std::vector<std::vector<Animation>>& nAnimSet) { _animSet = nAnimSet; }

	// Elimina el collider actual i n'assigna un de nou
	void SetCollider(Collider* nCollider);

	void SetSpeed(int nSpeed) { _speed = nSpeed; }

	void SetAggro(int nAggro) { _aggro = nAggro; }

	void SetAggroThreshold(int nAggroMax) { _aggroMax = nAggroMax; }

	void SetAttackRange(int nRange) { _attackRange = nRange; }

	void SetVisionRange(int nRange) { _visionRange = nRange; }

	void SetSearchRange(int nRange) { _searchRange = nRange; }

	void SetState(Enemy_State nState) { _currState = nState; }

#pragma endregion

#pragma region Getters

	Enemy_Type GetType() const { return type; }

	const SDL_Texture* GetTexture() const { return _texture; }

	const Animation* GetAnimation() const { return _currentAnim; }

	// Returns the enemy's collider
	const Collider* GetCollider() const { return _collider; }

	int GetSpeed() const { return _speed; }

	int GetAggro() const { return _aggro; }

	int GetAggroThreshold() const { return _aggroMax; }

	int GetAttackRange() const { return _attackRange; }

	int GetVisionRange() const { return _visionRange; }

	int GetSearchRange() const { return _searchRange; }

	Enemy_State GetState() const { return _currState; }

#pragma endregion

public:
	// The current position in the world
	iPoint position;

	PatrolPath patrolPath;

	// A flag for the enemy removal. Important! We do not delete objects instantly
	bool pendingToDelete = false;

protected:

	Enemy_Type type;

	// The enemy's texture
	SDL_Texture* _texture = nullptr;

	// A ptr to the current animation
	Animation* _currentAnim = nullptr;

	// Ptr a animacions corresponents a aquest enemic
	// Animation originalSet[MAX_STATES][DIRECTIONS_TOTAL]
	std::vector <std::vector<Animation>> _animSet;

	// The enemy's collider
	Collider* _collider = nullptr;

	// Original spawn position. Stored for movement calculations
	iPoint _spawnPos;

	bool _moving = true;

	uint _dirChangeTimer = 0;

	int _speed = 0;

	int _aggro = 0;

	int _aggroMax = 50;

	int _attackRange = 0;

	int _visionRange = 0;

	int _searchRange = 0;

	uint _attackDelay = 0;

	uint _attackStart = 0;

	Directions _currDirection = Directions::SOUTH;

	Enemy_State _currState;

	EnemyStateMachine* _stateMachine = nullptr;

	std::function<void(Collider*, Collider*)> _collisionCallback;
};

#endif // __ENEMY_H__