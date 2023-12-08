#pragma once

// Penser a g�rer des sauvegardes (Stats joueur principal metton et inventaire)
// Penser a faire un tableau de score. Peut-�tre le cumul d'exp du joueur?

class Game
{
	private:
		sf::RenderWindow _window;
		sf::RectangleShape _fondEcranPlay;
		sf::Texture _textureBgMap;
		//Entite _ness;
	public:
		void init(int posX, int posY, int w, int h, const char* nomSprite);
		void play();
		const sf::RectangleShape getBG()const;
};

