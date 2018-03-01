#pragma once

#include <utility>

#include "BattleEnemy.h"
#include "BattlePlayer.h"
#include "BattleCharacter.h"

enum PlayerAttack {
	PINCHO_ELIPTICO, CIRCULO_PERFECTO, GOLPE_SUCIO, LIMPIEZA_FONDO, MEDIDA_EXACTA, CONVERSION_UNIDADES, ESCRIBIR_APUNTES, GARABATO,
	ALUSIONES_FAMILIARES, EXPLORAR_LUGARES, INDICE_CONFUSO, CONJURO_PAGINA, SECADO_RAPIDO, METAMATERIAL, COMIDA_PASADA, INTERCAMBIO_POSTRES,
	BOLA_PAPEL, SALIVA_CERTERA, GLOBO_AZUL, ESO_NO_AGUA, PIEDRA_SUELO, DIANA_FRENTE, GRAPAS_EXAMEN, PUNTERIA_PROFESOR,
	AFILADO_TECNICO, PRECISION_DIBUJO, DERIVAR, MEMORIA_LLENA, REFLEJO, BANDEJAZO_FINAL, POLVOS_TIZA, TEMA_NUEVO
};

enum EnemyAttack {
	PLACAJE, FINTA_LATERAL, GOLPE_BAJO, ATURDIR,
	SOPLO, VENDAVAL, CAÍDA_LIBRE, POLVAREDA,
	CONJURO, MALDICION, AS_OCULTO, PSICOSIS
};

class Combat
{
public:
	Combat();
	~Combat();

	void run();

private:
	BattlePlayer* player = nullptr;
	BattleEnemy* enemy = nullptr;

	void init();
	void displayAttacks();
	void handleInput();

	std::vector<Attack> ataques;
	std::vector<Attack> e_ataques;
	int input;
	int turno;
};
