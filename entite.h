#pragma once
class Entite
{
	protected:
		std::string _nom;			
		sf::RectangleShape _shape;	// Pour la position et la forme
		sf::Texture _texture;		// Pour les sprite
		sf::IntRect _rectSprite;	// Pour les animations
		sf::RectangleShape _hitbox; // Pour les collisions

	public:
		Entite();
		Entite(std::string nom, sf::RectangleShape& _shape, sf::Texture& _texture, sf::IntRect& _rectSprite, sf::RectangleShape& _hitbox);
		~Entite();
		void init(int posX, int posY, int w, int h, const sf::IntRect& rectSprite, const char* nomSprite);

		const std::string getNom()const;
		const sf::RectangleShape getShape()const;
		const sf::Vector2f& getPosition()const;
		const sf::Vector2f& getHitboxPosition()const;
		const sf::RectangleShape getHitbox()const;

		void setNom(std::string nom);
		void setPosition(int posX, int posY);
		void setPosition(const sf::Vector2f& pos);
		void setHitboxPosition(int posX, int posY);
		void setSize(int w, int h);

		sf::View move(int& dir, float x, float y, int& animationCpt, sf::View viewGame);
		int moveMonstre(int cpt);
};

