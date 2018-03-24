#pragma once

#include "GameObject.h"
#include "GameObjectFactory.h"

class Player : public GameObject
{
public:
	Player();
	virtual ~Player();

	virtual void load(Vector2D position, int width, int height, string textureId, int numFrames, int callbackID = 0, int animSpeed = 0);
	virtual bool handleEvent(const SDL_Event& event);
	
	virtual void update();
	virtual void render();
	virtual void clean() {};

	virtual void collision();
	virtual string type() { return "Player"; };

	bool isInteracting() const { return interacting_; }
	void setInteracting(bool b) { interacting_ = b; }

	SDL_Rect* getRect() { return &actionRect_; }
	
private:
	int m_moveSpeed;
	bool interacting_;
	bool running_;

	SDL_Rect actionRect_;

	void handleAnimation();
	void updateRect();

	void interacting();

	//METODOS Y VARIABLES PARA EL MANDO DE LA XBOX360
	void onJoystickAxisMove(SDL_Event event);
	void initialiseJoysticks();
	void onJoystickButtonDown(SDL_Event event);
	void onJoystickButtonUp(SDL_Event event);

	bool getButtonState(int joy, int buttonNumber) const { return m_buttonStates[joy][buttonNumber]; }

	std::vector<SDL_Joystick*> m_joysticks;
	std::vector<std::vector<bool>> m_buttonStates;
	std::vector<std::pair<Vector2D*, Vector2D*>> m_joystickValues;

	int xvalue(int joy, int stick);
	int yvalue(int joy, int stick);


	bool m_bJoysticksInitialised;
};

class PlayerCreator : public BaseCreator
{
	GameObject* createGameObject() const
	{
		return new Player();
	}
};