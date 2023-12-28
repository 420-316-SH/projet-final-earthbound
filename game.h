#pragma once

// Penser a gèrer des sauvegardes (Stats joueur principal metton et inventaire)
// Penser a faire un tableau de score. Peut-être le cumul d'exp du joueur?

class Game
{
	private:
		sf::RectangleShape _fondEcranPlay;
		sf::Texture _textureBgMap;
		Joueur _ness;
		Monstre _monstre1;
		Monstre _monstre2;
		Monstre _monstre3;
		Monstre _monstre4;
		Monstre _monstre5;
		Monstre _monstre6;
		Monstre _monstre7;
		Monstre _monstre8;
		Monstre _monstre9;
		//vecteur<RectangleShape> mapHitbox;

	public:
		Game();
		~Game();
		void init(int posX, int posY, int w, int h, const char* nomSprite);
		void setText(sf::Text& text, const char* message, sf::Font& font, const char* police, int posX, int posY, int taille, const sf::Color& color, int style);
		void play();
		const sf::RectangleShape getBG()const;
		
		bool ifcollision(vector<sf::RectangleShape> &Hitbox);
};

