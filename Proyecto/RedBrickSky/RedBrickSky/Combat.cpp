#include "Combat.h"

Combat::Combat()
{
	player = new BattlePlayer("Tyler", Physical, 100, 10, 10, 100, 10);
	enemy = new BattleEnemy("Pajaro", Ranged, 70, 10, 10, 100, 11);

	ataques.resize(32);

	// Ataques de Armas Fisicas
	ataques[0] = Attack("Punta Afilada", Physical, 20, 20, 15, 75, 1, 1, 1);
	ataques[1] = Attack("Golpe de Goma", Physical, 20, 20, 20, 80, 1, 0.8f, 1);
	ataques[2] = Attack("Eso No Es Chocolate", Physical, 15, 15, 40, 75, 0.9f, 1, 0.9f);
	ataques[3] = Attack("Limpieza a Fondo", Physical, 15, 15, 35, 80, 0.9f, 0.9f, 1);
	ataques[4] = Attack("360 No Scope", Physical, 20, 20, 65, 70, 1, 1, 0.8f);
	ataques[5] = Attack("¡Pasalo a Radianes!", Physical, 15, 15, 55, 85, 0.9f, 0.9f, 0.9f);
	ataques[6] = Attack("Tajo Recto", Physical, 10, 10, 95, 80, 1, 1, 1);
	ataques[7] = Attack("Golpe de Remo", Physical, 15, 15, 80, 90, 1, 1, 1);

	// Ataques de Armas Magicas
	ataques[8] = Attack("Hijo de Fruta", Magical, 20, 20, 20, 75, 0.9f, 0.9f, 1);
	ataques[9] = Attack("Dedo Mágico", Magical, 20, 20, 15, 80, 1, 1, 0.8f);
	ataques[10] = Attack("Comida Sorpresa", Magical, 20, 20, 30, 80, 1, 0.8f, 1);
	ataques[11] = Attack("Hoy Toca Lentejas", Magical, 20, 20, 45, 75, 1, 1, 1);
	ataques[12] = Attack("Esto No Pega", Magical, 15, 15, 60, 90, 1, 0.9f, 1);
	ataques[13] = Attack("Metamaterial", Magical, 15, 15, 75, 80, 0.9f, 0.9f, 0.9f);
	ataques[14] = Attack("Indice Confuso", Magical, 10, 10, 85, 95, 1, 1, 1);
	ataques[15] = Attack("Lectura Ligera", Magical, 10, 10, 95, 80, 1, 1, 1);

	// Ataques de Armas con Proyectiles
	ataques[16] = Attack("Proyectil Humedo", Ranged, 30, 30, 15, 90, 1, 1, 0.8f);
	ataques[17] = Attack("Escupitajo Supersonico", Ranged, 30, 30, 25, 80, 1, 1, 0.9f);
	ataques[22] = Attack("Grapas Atómicas", Ranged, 25, 25, 30, 90, 1, 1, 1);
	ataques[23] = Attack("Corchograpa", Ranged, 25, 25, 45, 75, 1, 0.9f, 0.9f);
	ataques[19] = Attack("Eso no era Agua", Ranged, 15, 15, 65, 85, 1, 1, 0.8f);
	ataques[18] = Attack("Eso Tampoco", Ranged, 15, 15, 75, 75, 1, 0.8f, 0.9f);
	ataques[20] = Attack("¡ZAS! En Toda la Boca", Ranged, 5, 5, 85, 100, 1, 1, 1);
	ataques[21] = Attack("Meteorito Hentai", Ranged, 5, 5, 95, 90, 1, 1, 1);

	// Ataques de Armas de Apoyo
	ataques[24] = Attack("Afilador", Support, 20, 20, 0, 100, 1.2f, 1, 1);
	ataques[25] = Attack("Trazado Fino", Support, 20, 0, 100, 20, 1, 1, 1.2f);
	ataques[26] = Attack("Calculo Algebraico Complejo", Support, 20, 20, 0, 100, 1.2f, 1, 1.1f);
	ataques[27] = Attack("Stack Overflow", Support, 5, 5, 0, 100, 1.5f, 1, 1);
	ataques[28] = Attack("Reflejo Fidedigno", Support, 10, 10, 0, 100, 1, 1, 1.5f);
	ataques[29] = Attack("Escudo de Adamantium", Support, 5, 5, 0, 100, 1, 1.5f, 1);
	ataques[30] = Attack("Polvos de Tiza", Support, 20, 20, 0, 100, 1, 1.2f, 2);
	ataques[31] = Attack("Empezamos Tema Nuevo", Support, 5, 5, 0, 100, 1.4f, 1, 1.1f);

	e_ataques.resize(12);
	e_ataques[0] = Attack("Placaje", Physical, 20, 20, 20, 90, 1, 1, 1);
	e_ataques[1] = Attack("Finta Lateral", Physical, 15, 15, 15, 80, 1, 1, 0.9f);
	e_ataques[2] = Attack("Golpe Bajo", Physical, 10, 10, 15, 30, 1, 0.8f, 1);
	e_ataques[3] = Attack("Aturdir", Physical, 15, 15, 35, 25, 0.9f, 1, 1);

	e_ataques[4] = Attack("Soplo", Ranged, 20, 20, 30, 90, 1, 0.9f, 1);
	e_ataques[5] = Attack("Vendaval", Ranged, 10, 10, 45, 90, 1, 1, 1);
	e_ataques[6] = Attack("Caida Libre", Ranged, 10, 10, 60, 50, 1, 1, 1);
	e_ataques[7] = Attack("Polvareda", Ranged, 15, 15, 15, 90, 1, 1, 0.8f);

	e_ataques[8] = Attack("Conjuro", Magical, 15, 15, 70, 90, 0.8f, 1, 1);
	e_ataques[9] = Attack("Maldición", Magical, 10, 10, 80, 90, 1, 0.8f, 1);
	e_ataques[10] = Attack("As Oculto", Magical, 5, 5, 90, 90, 0.9f, 0.9f, 1);
	e_ataques[11] = Attack("Psicosis", Magical, 5, 5, 35, 90, 0.9f, 0.9f, 0.9f);

	init();
}


Combat::~Combat()
{
}

void Combat::init()
{
	player->addAttack(ataques[PINCHO_ELIPTICO]);
	player->addAttack(ataques[CIRCULO_PERFECTO]);
	player->addAttack(ataques[ALUSIONES_FAMILIARES]);
	player->addAttack(ataques[EXPLORAR_LUGARES]);

	std::vector<bool> ea;
	for (int i = 0; i < e_ataques.size(); i++) ea.push_back(true);
	Type aux_type = enemy->getType();
	int count = 0;
	while (count < 2)
	{
		int rnd = rand() % e_ataques.size();
		if (e_ataques[rnd].type == aux_type && ea[rnd])
		{
			ea[rnd] = false;
			count++;
			enemy->addAttack(e_ataques[rnd]);
		}
	}

	float vel_player = player->getVelocity();
	float vel_enemy = enemy->getVelocity();
	// TODO
	// Definir quién empieza

	std::cout << enemy->getName() << " quiere luchar!" << std::endl;

}

void Combat::displayAttacks()
{
	for (int i = 0; i < 4; i++) {
		Attack temp_a = player->getAttack(i);
		std::cout << temp_a.pp << "/" << temp_a.max_pp << " " << temp_a.name << " (" << temp_a.strength << ")" << std::endl;
	}
}

void Combat::handleInput()
{
	displayAttacks();
	input = 0;
	do {
		std::cout << "Que quieres hacer? ";
		std::cin >> input;
	} while (input < 1 || input > 4);

	std::cout << std::endl;

	input--;
}

bool Combat::run()
{
	bool endBattle = false;

	if (player->getHealth() > 0 && enemy->getHealth() > 0)
	{
		std::cout << std::endl;

		handleInput();
		while (!player->useAttack(input)) {
			std::cout << "No quedan PP para este ataque!" << std::endl;
		}

		bool b;
		float dmg = player->combat(input, enemy->getDefense(), enemy->getType(), b);
		if (player->hasTarget())
		{
			enemy->receiveDamage(dmg);
			Attack temp_a = player->getAttack(input);
			enemy->receiveFactors(temp_a.atk_factor, temp_a.def_factor, temp_a.prc_factor);
		}

		std::cout << std::endl;

		if (enemy->getHealth() > 0)
		{
			enemy->useAttack(0);
			int e_input = enemy->getInput();
			bool b;
			dmg = enemy->combat(e_input, player->getDefense(), player->getType(),b );
			if (enemy->hasTarget())
			{
				player->receiveDamage(dmg);
				Attack temp_a = enemy->getAttack(e_input);
				player->receiveFactors(temp_a.atk_factor, temp_a.def_factor, temp_a.prc_factor);
			}
		}

		std::cout << player->getName() << ": " << player->getHealth() << " HP" << std::endl;
		std::cout << enemy->getName() << ": " << enemy->getHealth() << " HP" << std::endl;

		std::cout << std::endl << "-------------------------------------------------------------" << std::endl;
	}

	if (player->getHealth() > 0 && enemy->getHealth() <= 0) {
		std::cout << "HAS GANADO!" << std::endl;
		endBattle = true;
	}
	else if (player->getHealth() <= 0 && enemy->getHealth() > 0) {
		std::cout << "HAS PERDIDO!" << std::endl;
		endBattle = true;
	}
	else if (player->getHealth() <= 0 && enemy->getHealth() <= 0) {
		std::cout << "WTF EMPATE LOCO!" << std::endl;
		endBattle = true;
	}
	return endBattle;
}