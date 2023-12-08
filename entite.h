#pragma once
class entite
{
	protected:
		std::string _nom;
		sf::RectangleShape _shape;	// Pour la position et la forme
		sf::Texture _texture;		// Pour les sprite
		sf::IntRect _rectSprite;	// Pour les animations
		sf::RectangleShape _hitbox; // Pour les collisions

	public:
		entite();
		~entite();
		void init(int posX, int posY, int w, int h, const sf::IntRect& rectSprite, const char* nomSprite);

		const std::string getNom()const;
		const sf::Vector2f& getPosition()const;
		const sf::Vector2f& getHitboxPosition()const;
		const sf::RectangleShape getHitbox()const;

		void setNom(std::string nom);
		void setPosition(int posX, int posY);
		void setPosition(const sf::Vector2f& pos);
		void setHitboxPosition(int posX, int posY);



};

