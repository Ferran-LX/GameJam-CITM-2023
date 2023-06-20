#pragma once
#include "Enemy.h"
class EnemyBasic :
    public Enemy
{
public:

    // Constructor
    EnemyBasic(int x_, int y_, Collider* collider = nullptr);

    // Destructor
    ~EnemyBasic();

    void InitStateMachine() override;

    void UpdateBehaviour(const ModulePlayer* player) override;


};
