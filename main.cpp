#include <SFML/Graphics.hpp>
#include <Windows.h>
#include "liste.hpp"
#include "vecteur.hpp"
#include "status.h"
#include "move.h"
#include "entite.h"
#include "item.h"
#include "status.h"
#include "monstre.h"
#include "joueur.h"
#include "monstre.h"
#include "game.h"


int main() {
	// Ajout Antho pour test
	srand(time(NULL));
	Game earthbound;
	earthbound.play();

	system("pause>0");

	return 0;
}
