#include "TransitionState.h"
#include "DiscretMovementIAComponent.h"

TransitionState::TransitionState(Game* gamePtr) : GameState (gamePtr)
{
	Texture* tx0 = gamePtr->getTexture(22);
	Vector2D position0(-1, 0);
	double width = gamePtr->getWinWidth() / 5;
	double height = gamePtr->getWinWidth() / 5;
	RenderComponent* rc = new RenderFrameComponent();
	PhysicsComponent* pc = new DiscretMovementIAComponent();
	square = new GameComponent(gamePtr);
	square->setText(tx0); square->setPosition(position0); square->setWidth(width); square->setHeight(height); square->addRenderComponent(rc); square->addPhysicsComponent(pc);
	stage.push_back(square);
}


TransitionState::~TransitionState()
{
}

void TransitionState::render() {
	//redefinimos render sin el clear
	for (unsigned int i = 0; i < stage.size(); i++)
		stage[i]->render();
}
