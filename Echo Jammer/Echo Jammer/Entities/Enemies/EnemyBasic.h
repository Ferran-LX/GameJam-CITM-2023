#pragma once
#include "Enemy.h"
class EnemyBasic :
    public Enemy
{
public:

    // Constructor
    EnemyBasic(int x_, int y_);

    // Destructor
    ~EnemyBasic();

    void InitStateMachine() override;

    void Update() override;

    void OnCollision(Collider* collider) override;


};
