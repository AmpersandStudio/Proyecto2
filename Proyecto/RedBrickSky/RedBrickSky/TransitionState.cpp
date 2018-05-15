#include "TransitionState.h"
#include "DiscretMovementIAComponent.h"

TransitionState::TransitionState()
{
	TheSoundManager::Instance()->stopMusic();
	TheSoundManager::Instance()->closeChannel(3);
	/*TheSoundManager::Instance()->playMusic("trans_btl", 0);*/
	TheSoundManager::Instance()->playMusic("battle", 0);
	Vector2D position0(0, 0);
	double width = Game::Instance()->getWinWidth() / 7;
	double height = Game::Instance()->getWinWidth() / 7;
	RenderComponent* rc = new RenderFrameComponent();
	PhysicsComponent* pc = new DiscretMovementIAComponent();
	square = new GameComponent();
	square->setTextureId("22"); square->setPosition(position0); square->setWidth(width); square->setHeight(height); square->addRenderComponent(rc); square->addPhysicsComponent(pc);
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
