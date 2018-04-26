#pragma once
#include <iostream>
#include "TextureManager.h"

#include <queue>
#include <vector>

class Game;
class StringToScreen
{
private:
	StringToScreen();
	static StringToScreen* s_pInstance;

	std::queue<std::string> splittedString_;
	std::string currentLines_[3];

	int posX_ = 350;
	int posY_ = 450;
	int offsetX_ = 25;
	int offsetY_ = 20;
	int dBoxWidth_ = 450;
	int dBoxHeight_ = 135;
	int lineSpace_ = 30;
	int lineLength_ = 24;

	bool messaging_ = false;
	int msgCont_ = 0;
	bool renderBack = false;

	struct inf {
		std::string InfMSG_;
		int x; int y;
	};

	std::vector<inf> infiniteMsg;

public:
	~StringToScreen();
	static StringToScreen* Instance()
	{
		if (s_pInstance == 0) {
			s_pInstance = new StringToScreen();
		}
		return s_pInstance;
	}

	void splitString(std::string s);
	bool isConsonant(char c);
	bool isVowel(char c);
	bool isDots(std::string s);
	bool isPunctuation(char c);

	virtual void render();

	void renderMessage();
	void setMessage(std::string s);
	void setMessageAt(std::string s, int x, int y);
	void startMessagin();

	void pushInfinite(std::string m, int x, int y);
	void renderinfinite();
	void changeInfinite(int i, std::string m);
	void clearInfinite();
	void stopRendering();
	void renderBackGround();
};

