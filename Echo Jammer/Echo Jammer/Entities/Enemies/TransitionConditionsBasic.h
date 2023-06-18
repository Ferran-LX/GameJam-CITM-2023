#pragma once

#include "EnemyBasic.h"
#include "../../Modules/Gameplay/ModulePlayer.h"
namespace Transitions_Basic {
	static bool Patrulla_Perseguir(const EnemyBasic& r, const iPoint& p) {
		return r.position.DistanceTo(p) < r.GetVisionRange() && r.GetAggro() >= r.GetAggroThreshold();
	}

	static bool Perseguir_Cerca(const EnemyBasic& r, const iPoint& p) {
		return r.position.DistanceTo(p) > r.GetVisionRange();
	}

	static bool Perseguir_Atacar(const EnemyBasic& r, const iPoint& p) {
		return r.position.DistanceTo(p) < r.GetAttackRange();
	}

	static bool Cerca_Perseguir(const EnemyBasic& r, const iPoint& p) {
		return r.position.DistanceTo(p) < r.GetSearchRange();
	}

	static bool Cerca_Patrulla(const EnemyBasic& r) {
		return r.GetAggro() <= 0;
	}

	static bool Atacar_Perseguir(const ModulePlayer& player) {
		return player.alive;
	}

	static bool Atacar_Final(const ModulePlayer& player) {
		return !player.alive;
	}

}