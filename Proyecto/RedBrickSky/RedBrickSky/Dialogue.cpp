#include "Dialogue.h"
#include "Game.h"
#include "TextureManager.h"
#include "Camera.h"
#include "SoundManager.h"


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
	if (numDialogues_ > 0)
	{
		if (!isActive())
		{
			if (dialogueIndex_ >= numDialogues_) dialogueIndex_ = 0;
			splitString(dialogues_.at(dialogueIndex_));
			setActive(true);
		}
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
		TheSoundManager::Instance()->playSound("dialogo", 0);
		return true;
	}
}

void Dialogue::render()
{
	SDL_RenderSetLogicalSize(Game::Instance()->getRenderer(), Game::Instance()->getWinWidth(), Game::Instance()->getWinHeight());

	if (isActive())
	{
		if (posX_ - TheCamera::Instance()->getPosition().getX() > (Game::Instance()->getWinWidth() / 2) + offsetX_) {
			posX_ += (-2 * offsetX_) - dBoxWidth_;
		}
		else {
			posX_ += 10;
		}

		TheTextureManager::Instance()->drawFull("vi�eta", posX_ - TheCamera::Instance()->getPosition().getX() - offsetX_, posY_ - TheCamera::Instance()->getPosition().getY() - offsetY_ - 10,
			dBoxWidth_, dBoxHeight_, Game::Instance()->getRenderer(), 0, 255);

		//RENDERIZO EL BOCADILLO
		for (int i = 0; i < 3; i++) {
			TheTextureManager::Instance()->drawText(currentLines_[i], TextureManager::Pixel16, { 0,0,0,255 },
				posX_ - TheCamera::Instance()->getPosition().getX(),
				posY_ + i * lineSpace_ - TheCamera::Instance()->getPosition().getY(),
				Game::Instance()->getRenderer());
		}
	}

	SDL_RenderSetLogicalSize(Game::Instance()->getRenderer(), Game::Instance()->getWinWidth() / Game::Instance()->getScaleFact(), Game::Instance()->getWinHeight() / Game::Instance()->getScaleFact());
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
	//Usamos variables de tipo double porque hay veces que la division da valores muy cercanos al siguiente d�gito
	//y si no se lo sumamos no nos va a separar el di�logo en diferentes l�neas

	double length_ = s.size();
	int lines_ = length_ / lineLength_;
	double lines = lines_;

	lines += tolerance;


	if (length_ / lineLength_ > lines)
		lines_++;

	int j = 0;
	for (int i = 0; i < lines_; i++)
	{
		std::string substring = s.substr(j, lineLength_ + 1);
		/*if ( isVowel(substring[23]) && (substring[24] != ' '||','||'.') &&  isConsonant(substring[24]) && substring.length() > 24) {
		substring.erase(24, 1);
		substring.append("-");
		}
		else if(substring.length() > 24) {
		substring.erase(24, 1);
		}*/

		if (substring.size() > lineLength_
			&& (isVowel(substring[substring.size() - 1]) || isConsonant(substring[substring.size() - 1]) || isDots(substring))
			&& substring[substring.size() - 2] != ' ') {
			int temp = 0;
			int pos = 0;
			while ((temp = substring.find(' ', temp)) != std::string::npos) {
				pos = temp;
				temp++;
			};
			substring.erase(pos, (substring.size() - pos));
			splittedString_.push(substring);
			j += (pos + 1);
		}
		else {
			if (substring.size() > lineLength_) {
				substring.erase(lineLength_, 1);
			}
			splittedString_.push(substring);
			j += lineLength_;
		}
	}


	if ((int)length_ % (int)lineLength_ != 0 && j < s.size())
	{
		std::string substring = s.substr(j, s.size() - 1);
		splittedString_.push(substring);
	}
}


bool Dialogue::isConsonant(char c)
{
	std::string consonantes = "bBcCdDfFgGhHjJkKlLmMnN��pPqQrRsStTvVwWxXyYzZ";
	if (consonantes.find(c) != std::string::npos) {
		return true;
	}
	return false;
}

bool Dialogue::isVowel(char c)
{
	std::string vocales = "aA��e�E�i�I�o�O�u�U�";
	if (vocales.find(c) != std::string::npos) {
		return true;
	}
	return false;
}

bool Dialogue::isDots(std::string s) {
	if (s.find("...", (s.size() - 4)) != std::string::npos) {
		return true;
	}
	return false;
}

bool Dialogue::isPunctuation(char c) {
	std::string signos = "�?�!,.;:";
	if (signos.find(c) != std::string::npos) {
		return true;
	}
	return false;
}