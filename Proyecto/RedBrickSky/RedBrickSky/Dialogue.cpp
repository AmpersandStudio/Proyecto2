#include "Dialogue.h"
#include <iostream>

Dialogue::Dialogue()
{
}


Dialogue::Dialogue(int level_dialogues)
{
	level = level_dialogues;
	filename = "Nivel" + std::to_string(level_dialogues) + ".txt";
	std::cout << "Reading " << filename << std::endl;
}

Dialogue::~Dialogue()
{
}

//Encuentra el dialogo correspondiente
std::string Dialogue::findText(char id, int numDialog, std::ifstream& file)
{
	std::string s;

	std::getline(file, s);

	//Se da por hecho que el diálogo introducido va a estar en el archivo, por lo que no genera errores
	while (s == "" || (s[0] != id) && ((int)s[1] != numDialog))
	{
		std::getline(file, s);
	}

	std::getline(file, s);

	return s;
}

//Hace toda la búsqueda del diálogo abriendo y cerrando el archivo
std::string Dialogue::getText(char id, int numDialog)
{
	std::ifstream file_;
	file_.open("..\\Dialogues\\" + filename);

	std::string s = findText(id, numDialog, file_);

	file_.close();

	return s;
}
