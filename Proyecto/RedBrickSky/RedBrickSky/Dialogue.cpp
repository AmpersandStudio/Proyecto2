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
		if (!splittedString_.empty())
		{
			currentLines_[0] = splittedString_.front();
			splittedString_.pop();

		}

		if (!splittedString_.empty())
		{
			currentLines_[1] = splittedString_.front();
			splittedString_.pop();
		}
		else currentLines_[1] = "";
	}
}

void Dialogue::render()
{
	if (isActive())
	{
	/*	TheTextureManager::Instance()->drawText(currentLines_[0], TextureManager::ARIAL24, { 0,0,0,255 },
			TheCamera::Instance()->getPosition().getX(),
			TheCamera::Instance()->getPosition().getY() - 2087,
			Game::Instance()->getRenderer());*/

		TheTextureManager::Instance()->drawText(currentLines_[0], TextureManager::ARIAL24, { 0,0,0,255 },
			20,
			515,
			Game::Instance()->getRenderer());

		TheTextureManager::Instance()->drawText(currentLines_[1], TextureManager::ARIAL24, { 0,0,0,255 },
			20,
			540,
			Game::Instance()->getRenderer());

		/*cout << TheCamera::Instance()->getPosition().getX() << endl;
		cout << TheCamera::Instance()->getPosition().getY() - 2080 << endl;*/

	/*	TheTextureManager::Instance()->drawText(currentLines_[1], TextureManager::ARIAL24, { 0,0,0,255 },
			TheCamera::Instance()->getPosition().getX(),
			TheCamera::Instance()->getPosition().getY() - 2064,
			Game::Instance()->getRenderer());*/


		/*if (splittedString_.empty())
		{
			setActive(false);
			dialogueIndex_++;
		}*/
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
	int lines = length / 20;

	int j = 0;
	for (int i = 0; i < lines; i++)
	{
		std::string substring = s.substr(j, 20);
		splittedString_.push(substring);
		j += 20;
	}

	if (length % 20 != 0)
	{
		std::string substring = s.substr(j, s.size() - 1);
		splittedString_.push(substring);
	}
}

