#include "NameSelectorState.h"
#include "RenderFullComponent.h"
#include "KeyInputComponent.h"
#include "GameManager.h"

NameSelectorState::NameSelectorState(Game* gamePtr) : GameState(gamePtr)
{
	selector_ = new GameComponent(gamePtr);

	abcdary_ = gamePtr->getTexture(11); //letras
	Texture* tx0 = gamePtr->getTexture(12); //selector

	Vector2D position0(0, 0);

	int rows = 6;
	int cols = 9;
	int selectorWidth = gamePtr->getWinWidth() / cols;
	int selectorHeight = gamePtr->getWinHeight() / rows;

	RenderComponent* rc = new RenderFrameComponent();
	InputComponent* ic = new KeyInputComponent(SDLK_w, SDLK_s, SDLK_d, SDLK_a, 6, 9);

	selector_->setText(tx0); selector_->setPosition(position0); selector_->setWidth(selectorWidth); selector_->setHeight(selectorHeight); selector_->addRenderComponent(rc); selector_->addInputComponent(ic);

	stage.push_back(selector_);
}

NameSelectorState::~NameSelectorState()
{
}

void NameSelectorState::render() {
	abcdary_->renderComplete();
	GameState::render();
}

bool NameSelectorState::handleEvent(SDL_Event& event) {
	bool handledEvent = false;
	handledEvent = GameState::handleEvent(event);

	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_SPACE) {
			handledEvent = true;
			Vector2D pos = selector_->getPosition();
			int x = pos.getX();
			int y = pos.getY();
			name_ += letters[y][x];
		}
		else if (event.key.keysym.sym == SDLK_RETURN) {
			handledEvent = true;
			cout << name_ << endl;
			GameManager::Instance()->setName(name_);
		}
	}
	return handledEvent;

}