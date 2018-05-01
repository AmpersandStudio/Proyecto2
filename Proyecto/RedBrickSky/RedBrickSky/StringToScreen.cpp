#include "StringToScreen.h"
#include "Game.h"
StringToScreen* StringToScreen::s_pInstance = 0;

StringToScreen::StringToScreen()
{


}


StringToScreen::~StringToScreen()
{
}


void StringToScreen::renderMessage() {

	if(renderBack)
		TheTextureManager::Instance()->drawFull("viñeta", posX_ - offsetX_, posY_ - offsetY_,
		300, 100, Game::Instance()->getRenderer(), 0, 255);

	for (int i = 0; i < 3; i++) {
		TheTextureManager::Instance()->drawText(currentLines_[i], TextureManager::Pixel16, { 0,0,0,255 },
			posX_ + offsetX_,
			posY_ + offsetY_ * i,
			Game::Instance()->getRenderer());
	}
}

void StringToScreen::setMessage(std::string s) {
	splitString(s);
}

void StringToScreen::setMessageAt(std::string s, int x, int y) {
	posX_ = x;
	posY_ = y;
	splitString(s);
}

void StringToScreen::startMessagin() {

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

	msgCont_ = 0;
	messaging_ = true;
}

void StringToScreen::renderBackGround() {
	renderBack = true;
}
void StringToScreen::splitString(std::string s)
{
	int length = s.size();
	int lines = length / lineLength_;

	int j = 0;
	for (int i = 0; i < lines; i++)
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

	if (length % lineLength_ != 0)
	{
		std::string substring = s.substr(j, s.size() - 1);
		splittedString_.push(substring);
	}
}


bool StringToScreen::isConsonant(char c)
{
	std::string consonantes = "bBcCdDfFgGhHjJkKlLmMnNñÑpPqQrRsStTvVwWxXyYzZ";
	if (consonantes.find(c) != std::string::npos) {
		return true;
	}
	return false;
}

bool StringToScreen::isVowel(char c)
{
	std::string vocales = "aAáÁeéEÉiíIÍoóOÓuúUÚ";
	if (vocales.find(c) != std::string::npos) {
		return true;
	}
	return false;
}

bool StringToScreen::isDots(std::string s) {
	if (s.find("...", (s.size() - 4)) != std::string::npos) {
		return true;
	}
	return false;
}

bool StringToScreen::isPunctuation(char c) {
	std::string signos = "¿?¡!,.;:";
	if (signos.find(c) != std::string::npos) {
		return true;
	}
	return false;
}

void StringToScreen::render() {
	renderinfinite();
	if (messaging_) {
		msgCont_++;
		renderMessage();

		if (msgCont_ == 100) {
			msgCont_ = 0;
			messaging_ = false;
			renderBack = false;
		}
	}
}

void StringToScreen::pushInfinite(std::string m, int x, int y) {

	inf a;
	a.InfMSG_ = m;
	a.x = x;
	a.y = y;

	infiniteMsg.push_back(a);
}

void StringToScreen::renderinfinite() {

	for (int p = 0; p < infiniteMsg.size(); p++)
	{

		TheTextureManager::Instance()->drawText(infiniteMsg[p].InfMSG_, TextureManager::NESChimera16, { 0,0,0,255 },
			infiniteMsg[p].x + offsetX_,
			infiniteMsg[p].y + offsetY_ * p,
			Game::Instance()->getRenderer());
	}
}

void StringToScreen::changeInfinite(int i, std::string m) {
	infiniteMsg[i].InfMSG_ = m;
}

void StringToScreen::clearInfinite() {
	infiniteMsg.clear();
}

void StringToScreen::stopRendering() {
	messaging_ = false;
}