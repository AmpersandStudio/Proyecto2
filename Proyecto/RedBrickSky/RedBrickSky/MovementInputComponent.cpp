#include "MovementInputComponent.h"



MovementInputComponent::MovementInputComponent(SDL_Keycode up, SDL_Keycode down, SDL_Keycode left, SDL_Keycode right) :
	up_(up), down_(down), left_(left), right_(right)
{
}




MovementInputComponent::~MovementInputComponent()
{
}

bool MovementInputComponent::handleEvent(GameObject * o, const SDL_Event & event)
{
	bool eventHandled = false;

	if (event.type == SDL_KEYDOWN) 
	{
		Vector2D auxPos = o->getPosition();
		Vector2D auxVel = o->getVel();
	
		// Eje X
		if (event.key.keysym.sym == left_)
		{
			auxPos = auxPos + Vector2D(-auxVel.getX(),0);
			eventHandled = true;
		}

		else if (event.key.keysym.sym == right_)
		{
			auxPos = auxPos + Vector2D(auxVel.getX(), 0);
			eventHandled = true;
		}

		// Eje Y
		else if(event.key.keysym.sym == up_)
		{ 
			auxPos = auxPos + Vector2D(0, -auxVel.getY());
			eventHandled = true;
		}
		else if(event.key.keysym.sym == down_)
		{ 
			auxPos = auxPos + Vector2D(0, auxVel.getY());
			eventHandled = true;
		}
		
		o->setPosition(auxPos);
	}
	return eventHandled;
}
