#pragma once

// Penser a gèrer des sauvegardes (Stats joueur principal metton et inventaire)
// Penser a faire un tableau de score. Peut-être le cumul d'exp du joueur?

class Game
{
	private:
		sf::RectangleShape _fondEcranPlay;
		sf::Texture _textureBgMap;
		Joueur _ness;
		vecteur<Monstre> _monstres;
		Joueur _monstre;
	public:
		Game();
		~Game();
		void init(int posX, int posY, int w, int h, const char* nomSprite);
		void play();
		const sf::RectangleShape getBG()const;
};

