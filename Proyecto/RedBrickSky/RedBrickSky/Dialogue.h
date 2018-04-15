#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <queue>


class Dialogue
{
public:
	Dialogue();
	Dialogue(std::string name);
	~Dialogue();

	inline bool isActive() const { return active_; }
	inline void setActive(bool b) { active_ = b; }

	void update();
	void render();

private:
	std::string name_;
	int numDialogues_;
	int dialogueIndex_;

	std::vector<std::string> dialogues_;
	std::queue<std::string> splittedString_;
	std::string currentLines_[2];

	bool active_;

	void readFile();
	void splitString(std::string s);
};