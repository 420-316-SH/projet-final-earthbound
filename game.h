#pragma once

// Penser a gèrer des sauvegardes (Stats joueur principal metton et inventaire)
// Penser a faire un tableau de score. Peut-être le cumul d'exp du joueur?

class game
{
	private:
		sf::RenderWindow _window;
	public:
		void init(/*Mettre les paramètres à init*/);
		void play();
};

