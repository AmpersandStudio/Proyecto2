#include "Dialogue.h"
#include "Game.h"
#include <iostream>

Dialogue::Dialogue()
{
}


Dialogue::Dialogue(std::string name) : name_(name), active_(false)
{
	readFile();
}

Dialogue::~Dialogue()
{
}


void Dialogue::update()
{
	if (!isActive() /*&& Game::Instance()->canActivate(this)*/)
	{
		if (dialogueIndex_ >= numDialogues_)
			dialogueIndex_ = 0;

		splitString(dialogues_.at(dialogueIndex_));
		setActive(true);
	}

	if (isActive())
	{
		if (!splittedStrings_.empty())
		{
			currentLines_[0] = splittedStrings_.front();
			splittedStrings_.pop();

		}

		if (!splittedStrings_.empty())
		{
			currentLines_[1] = splittedStrings_.front();
			splittedStrings_.pop();
		}
		else currentLines_[1] = "";
	}
}


void Dialogue::render()
{
	if (isActive())
	{
		Game::Instance()->textPrinter(currentLines_[0], 200, 2, 2, Game::Instance()->getBlackColor());
		//Game::Instance()->textPrinter(currentLines_[1], 200, 2, 2, Game::Instance()->getBlackColor());
		
		/*std::cout << currentLines_[0] << std::endl;
		std::cout << currentLines_[1] << std::endl;*/

		if (splittedStrings_.empty())
		{
			setActive(false);
			dialogueIndex_++;
		}
	}
}


void Dialogue::readFile()
{
	std::ifstream file;
	std::string filename = "..\\Dialogues\\" + name_ + ".txt";
	file.open(filename);

	if (file.is_open())
	{
		std::string line;
		std::getline(file, line);
		numDialogues_ = std::stoi(line);

		for (int i = 0; i < numDialogues_; i++)
		{
			std::getline(file, line);
			dialogues_.push_back(line);
		}
	}

	file.close();
}


void Dialogue::splitString(std::string s)
{
	int length = s.size();
	int lines = length / 20;

	int j = 0;
	for (int i = 0; i < lines; i++)
	{
		std::string substring = s.substr(j, 20);
		splittedStrings_.push(substring);
		j += 20;
	}

	if (length % 20 != 0)
	{
		std::string substring = s.substr(j, s.size() - 1);
		splittedStrings_.push(substring);
	}
}
