#pragma once
#include <fstream>
#include <string>

class Dialogue
{
private:
	int level;
	std::string filename;
	std::string findText(char id, int numDialog, std::ifstream& file);
public:
	Dialogue();
	Dialogue(int level_dialogues);
	~Dialogue();
	std::string getText(char id, int numDialog);
};

