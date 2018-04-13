#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <queue>

#include "checkML.h"

class Dialogue
{
public:

	Dialogue();
	Dialogue(std::string name);
	~Dialogue();

	void update();
	void render();

	inline bool isActive() const { return active_; };
	inline void setActive(bool b) { active_ = b; };

private:

	void readFile();	//Lee el archivo y almacena cada frase en dialogues_
	void splitString(std::string s);	//Corta un string en substrings m�s peque�os

	std::string name_;	//Nombre del personaje
	int numDialogues_;	//N� di�logos del personaje
	int dialogueIndex_;	//Contador del di�logo a renderizar
	bool active_;

	std::vector<std::string> dialogues_;	//Vector que almacena los dialogos
	std::queue<std::string> splittedStrings_;	//Cola que almacena los di�logos cortados
	std::string currentLines_[2];	//Vector est�tico

	int level;
	std::string filename;

};

