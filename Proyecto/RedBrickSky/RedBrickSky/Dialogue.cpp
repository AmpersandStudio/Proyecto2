#include "Dialogue.h"
#include "Game.h"
#include "TextureManager.h"
#include "Camera.h"


Dialogue::Dialogue()
{
}

Dialogue::Dialogue(std::string name) : name_(name), dialogueIndex_(0), active_(false)
{
	readFile();
}

Dialogue::~Dialogue()
{
}

void Dialogue::update()
{
	if (!isActive())
	{
		if (dialogueIndex_ >= numDialogues_) dialogueIndex_ = 0;
		splitString(dialogues_.at(dialogueIndex_));
		setActive(true);
	}

	if (isActive())
	{
		for (int i = 0; i < 3; i++) {
			if (!splittedString_.empty())
			{
				currentLines_[i] = splittedString_.front();
				splittedString_.pop();
			}
			else {
				currentLines_[i] = " ";
			}
		}
	}
}

bool Dialogue::nextDialogue() {
	dialogueIndex_++;
	setActive(false);
	if (dialogueIndex_ >= numDialogues_) {
		update();
		return false;
	}
	else {
		return true;
	}
}

void Dialogue::render()
{
	if (isActive())
	{
		TheTextureManager::Instance()->drawFull("viñeta", posX_ - TheCamera::Instance()->getPosition().getX() - 20, posY_ - TheCamera::Instance()->getPosition().getY() - 20, 335, 125,
			Game::Instance()->getRenderer(), 0, 255);
		//RENDERIZO EL BOCADILLO
		for (int i = 0; i < 3; i++) {
			TheTextureManager::Instance()->drawText(currentLines_[i], TextureManager::ARIAL24, { 0,0,0,255 },
				posX_ - TheCamera::Instance()->getPosition().getX(),
				posY_ + i * 15 - TheCamera::Instance()->getPosition().getY(),
				Game::Instance()->getRenderer());
		}
	}
}

void Dialogue::readFile()
{
	std::ifstream input;
	std::string filename = "..\\Dialogues\\" + name_ + ".txt";
	input.open(filename);

	if (input.is_open())
	{
		std::string line;
		std::getline(input, line);
		numDialogues_ = std::stoi(line);

		for (int i = 0; i < numDialogues_; i++)
		{
			std::getline(input, line);
			dialogues_.push_back(line);
		}
	}

	input.close();
}

void Dialogue::splitString(std::string s)
{
	int length = s.size();
	int lines = length / 24;

	int j = 0;
	for (int i = 0; i < lines; i++)
	{
		std::string substring = s.substr(j, 24);
		if (substring[23] != ' ' && substring[23] != ',' && substring[23] != '.') {
			substring.append("-");
		}
		splittedString_.push(substring);
		j += 24;
	}

	if (length % 24 != 0)
	{
		std::string substring = s.substr(j, s.size() - 1);
		splittedString_.push(substring);
	}
}

