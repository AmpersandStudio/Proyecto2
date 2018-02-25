#include "MovableObject.h"



MovableObject::MovableObject(Game* game,Vector2D vel):GameComponent(game),velocity_(vel)
{
	
}


MovableObject::~MovableObject()
{
}
