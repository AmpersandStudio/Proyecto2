#include "GameComponent.h"

GameComponent::GameComponent()
{
}

GameComponent::~GameComponent()
{
	clean();
}

bool GameComponent::handleEvent(const SDL_Event& event) {
	bool handledEvent = false;
	for (InputComponent* ic : inputComp_) {
		handledEvent = ic->handleEvent(this, event);
	}
	return handledEvent;
}

void GameComponent::update() {
	for (PhysicsComponent* pc : physicsComp_) {
		pc->update(this);
	}
}

void GameComponent::render() {
	for (RenderComponent* rc : renderComp_) {
		rc->render(this);
	}
}

void GameComponent::addInputComponent(InputComponent* ic) {
	inputComp_.push_back(ic);
}

void GameComponent::addPhysicsComponent(PhysicsComponent* pc) {
	physicsComp_.push_back(pc);
}

void GameComponent::addRenderComponent(RenderComponent* rc) {
	renderComp_.push_back(rc);
}

void GameComponent::delInputComponent(InputComponent* ic) {
	std::vector<InputComponent*>::iterator position = std::find(
		inputComp_.begin(), inputComp_.end(), ic);
	if (position != inputComp_.end())
		inputComp_.erase(position);
}

void GameComponent::delPhysicsComponent(PhysicsComponent* pc) {
	std::vector<PhysicsComponent*>::iterator position = std::find(
		physicsComp_.begin(), physicsComp_.end(), pc);
	if (position != physicsComp_.end())
		physicsComp_.erase(position);
}

void GameComponent::delRenderComponent(RenderComponent* rc) {
	std::vector<RenderComponent*>::iterator position = std::find(
		renderComp_.begin(), renderComp_.end(), rc);
	if (position != renderComp_.end())
		renderComp_.erase(position);
}

void GameComponent::clean() {
	for (InputComponent* ic : inputComp_)
		if (ic != nullptr) { delete ic; ic = nullptr; }

	for (RenderComponent* rc : renderComp_)
		if (rc != nullptr) { delete rc; rc = nullptr; }

	for (PhysicsComponent* pc : physicsComp_)
		if (pc != nullptr) { delete pc; pc = nullptr; }

	inputComp_.clear(); renderComp_.clear(); physicsComp_.clear();
}