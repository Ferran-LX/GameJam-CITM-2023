#include "Module.h"

Module::Module(bool startEnabled_) : startEnabled(startEnabled_) {
}

bool Module::Init() {
	return true;
}

bool Module::Start() {
	return true;
}

Update_Status Module::PreUpdate() {
	return Update_Status::UPDATE_CONTINUE;
}

Update_Status Module::Update() {
	return Update_Status::UPDATE_CONTINUE;
}

Update_Status Module::PostUpdate() {
	return Update_Status::UPDATE_CONTINUE;
}

bool Module::CleanUp() {
	return true;
}

void Module::OnCollision(Collider* c1, Collider* c2) {
}

bool Module::Enable() {
	bool ret = true;
	if (!isEnabled) {
		isEnabled = true;
		ret = Start();
	}
	return ret;
}

bool Module::Disable() {
	bool ret = true;
	if (isEnabled) {
		isEnabled = false;
		ret = CleanUp();
	}
	return ret;
}
