#include "NPC.h"
#include "Level.h"
#include <time.h>
#include <stdlib.h> 
#include "Camera.h"


NPC::NPC()
{

}

void NPC::load(Vector2D position, int width, int height, string textureId, int numFrames, int callbackID, int animSpeed)
{
	position_ = position;
	width_ = width;
	height_ = height;
	textureId_ = textureId;
	numFrames_ = numFrames;
	callbackId_ = callbackID;
	animSpeed_ = animSpeed;
	oriPosX_ = position.getX();
	oriPosY_ = position.getY();
	isFighter_ = true;

	dialogueActive = false;
	isInteracting_ = false;	
	generateCollider();
}


NPC::~NPC()
{
}

void NPC::activate() {
	isInteracting_ = true;
	if (!dialogueActive && !GameManager::Instance()->getDialogueState()) {
		dialogueActive = true;
		GameManager::Instance()->setDialogueState(true);
		//DESCOMENTAR ESTO CUANDO SE VUELVA A PODER PARAR A LOS NPCs TETES 
	}
	else if (dialogueActive) {
		dialogueActive = text.nextDialogue();
		if (!dialogueActive) {
			GameManager::Instance()->setDialogueState(false);
			if (isFighter_) {
				GameManager::Instance()->getNPC(this);
				GameManager::Instance()->toBattle();
			}
		}
	}
}


void NPC::update() {

	if (dialogueActive) {
		text.setX(position_.getX());
		text.setY(position_.getY());
		if (!text.isActive()) {
			text.update();
		}
	}
}

void NPC::isDefeated()
{
	isFighter_ = false;

	//HAY QUE CREAR DESTRUCTORA DE DIALOGUES Y RECARGAR LA VERSION B DE CADA DIALOGO CUANDO HAYA
	/*Message_.append("B");*/
	/*text = Dialogue(Message_);*/
}


void NPC::handleStoppedAnimation()
{
	if (vel.getY() < 0)
	{
		rowFrame_ = 3;
	}
	else if (vel.getY() > 0)
	{
		rowFrame_ = 0;
	}
	else if (vel.getY() == 0)
	{
		rowFrame_ = (vel.getX() < 0) ? 1 : 2;
	}

	colFrame_ = 1;
}

void NPC::render()
{
	if (dialogueActive && GameManager::Instance()->getDialogueState()) {
		text.render();
	}
	//SDL_Rect fillRect = { (Uint32)position_.getX() - TheCamera::Instance()->getPosition().getX() , (Uint32)position_.getY() - TheCamera::Instance()->getPosition().getY(), width_, height_ };
	//SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 0xFF, 0x00, 0x00, 0xFF);
	//SDL_RenderFillRect(Game::Instance()->getRenderer(), &fillRect);
	////SDL_RenderPresent(Game::Instance()->getRenderer());

	Interactuable::render();
}
