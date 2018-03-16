#include "NameSelectorState.h"
#include "RenderFullComponent.h"
#include "KeyInputComponent.h"
#include "GameManager.h"
#include "RenderSingleFrameComponent.h"

NameSelectorState::NameSelectorState()
{
	selector_ = new GameComponent();
	letters_ = new GameComponent();

	Vector2D position0(0, 0);

	int rows = 6;
	int cols = 9;
	int selectorWidth = Game::Instance()->getWinWidth() / cols;
	int selectorHeight = Game::Instance()->getWinHeight() / rows;

	RenderComponent* rc = new RenderSingleFrameComponent();
	RenderComponent* rc2 = new RenderFullComponent();
	InputComponent* ic = new KeyInputComponent(SDLK_w, SDLK_s, SDLK_d, SDLK_a, rows, cols);

	selector_->setTextureId("12"); selector_->setPosition(position0); selector_->setWidth(selectorWidth); selector_->setHeight(selectorHeight); selector_->addRenderComponent(rc); selector_->addInputComponent(ic);
	selector_->setColFrame(0); selector_->setRowFrame(0);

	letters_->setTextureId("11"); letters_->addRenderComponent(rc2);

	stage.push_back(letters_);
	stage.push_back(selector_);
}

NameSelectorState::~NameSelectorState()
{
}

void NameSelectorState::render() {
	GameState::render();
}

bool NameSelectorState::handleEvent(const SDL_Event& event) {
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