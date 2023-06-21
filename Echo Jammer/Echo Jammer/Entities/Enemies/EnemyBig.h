#pragma once
#include "Enemy.h"
class EnemyBig:
    public Enemy
{
public:

    // Constructor
    EnemyBig(int x_, int y_, Collider* collider = nullptr);

    // Destructor
    ~EnemyBig();

    void InitStateMachine() override;

    void UpdateBehaviour(const ModulePlayer* player) override;


};
