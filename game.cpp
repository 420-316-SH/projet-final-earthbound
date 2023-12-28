#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Windows.h>

#include "queue.hpp"
#include <fstream>
#include <sstream>
#include "list.hpp"
#include "vecteur.hpp"
#include "entite.h"
#include "item.h"
#include "status.h"
#include "move.h"
#include "monstre.h"
#include "joueur.h"
#include "game.h"

using namespace sf;
Game::Game()
{

}
Game::~Game()
{
}
void Game::init(int posX, int posY, int w, int h, const char* nomSprite)
{
	_fondEcranPlay.setPosition(posX, posY);
	_fondEcranPlay.setSize(Vector2f(w, h));
	if (!_textureBgMap.loadFromFile("img/mapPetite.png"))
	{
		exit(1);
	}
	_fondEcranPlay.setTexture(&_textureBgMap);
	vecteur<Move> moveNess;
	sf::IntRect rectSpriteNess(0, 0, 16, 24);
 	_ness.setJoueur(true, 100, 2, 2, 0, 0, 1, 1, 0, 10, 10, moveNess, 1275, 350, 16, 24, rectSpriteNess, "img/charsetsNess.png");
	_monstre1.setMonstre(true, 100, 2, 2, 0, 0, 1, 1, 0, moveNess, 1200, 350, 16, 24, rectSpriteNess, "img/charsetsNess.png");

	_monstre2.setMonstre(true, 100, 2, 2, 0, 0, 1, 1, 0, moveNess, 1150, 350, 16, 24, rectSpriteNess, "img/charsetsNess.png");

}

void Game::setText(sf::Text& text, const char* message, sf::Font& font, const char* police, int posX, int posY, int taille, const sf::Color& color, int style)
{
	if (!font.loadFromFile(police))
		exit(1);

	text.setFont(font); //Set la police à utiliser (elle doit avoir été loadée)
	text.setString(message);		//Set le texte à afficher
	text.setCharacterSize(taille); 			//Set la taille (en pixels)
	text.setFillColor(color);			//Set la couleur du texte
	text.setStyle(style);	//Set le style du texte
	text.setPosition(posX, posY);
}

void Game::play()
{
	// ReadFile ////////////////////////////////////////////
	//_ness.getShape().getGlobalBounds().intersects()
	int typeCollision, multiplicateur;
	char garbage;
	int y = 0, x = 0, cptHitboxe = 0;
	std::string ligne;
	RectangleShape obstacle;
	std::vector<RectangleShape> mapHitbox;


	std::ifstream fileObj("ressources/collision.txt");
	std::string line;

	while (std::getline(fileObj, line))
	{
		std::istringstream iss(line);
		while (!iss.eof())
		{
			iss >> typeCollision >> garbage >> multiplicateur;

			switch (typeCollision)
			{
			case 1:
				for (int i = 0; i < multiplicateur; i++)
				{
					obstacle.setPosition(x, y);
					x += 5;
					obstacle.setSize(sf::Vector2f(5, 5));
					obstacle.setFillColor(sf::Color::Red);
					mapHitbox.push_back(obstacle);
					cptHitboxe++;
				}
				break;
			case 0:
				for (int i = 0; i < multiplicateur; i++)
				{
					obstacle.setPosition(x, y);
					x += 5;
					obstacle.setSize(sf::Vector2f(5, 5));
					obstacle.setFillColor(sf::Color::Green);
					mapHitbox.push_back(obstacle);
					cptHitboxe++;
				}
				break;
			case 2:
				for (int i = 0; i < multiplicateur; i++)
				{
					obstacle.setPosition(x, y);
					x += 5;
					obstacle.setSize(sf::Vector2f(5, 5));
					obstacle.setFillColor(sf::Color::Blue);
					mapHitbox.push_back(obstacle);
					cptHitboxe++;
				}
				break;
			default:
				break;
			}
		}
		//cout << "y = " << y << endl;
		x = 0;
		y += 5;
	}

	cout << cptHitboxe;
	fileObj.close();

	////////////////////////////////////////////////////////
	//Init Menu Principal ///////////////////////////////////
	RenderWindow window(VideoMode(1600, 900), "Earthbound");
	bool menubool = true; // Si true, on est dans le menu
	RectangleShape fondEcranMenu;
	Texture texturefondEcranMenu;
	fondEcranMenu.setPosition(0, 0);
	fondEcranMenu.setSize(Vector2f(1600, 900));
	if (!texturefondEcranMenu.loadFromFile("img/earthboundMenuBG.png"))
	{
		cout << "Erreur! L'image du menu background est introuvable";
		system("pause");
		exit(1); // Fichier musique Menu introuvable
	}
	fondEcranMenu.setTexture(&texturefondEcranMenu);
	
	// Texte menu //////////////////////////////////////////////
	Text play;
	Text stat;
	Text reglage;
	Text quit;

	Font font;
	if (!font.loadFromFile("ressources/arial.ttf")) {
		exit(1);
	}


	for (int i = 0; i < 4; i++)
	{
		switch (i)
		{
		case 0:
			setText(play, "Play", font, "ressources/arial.ttf", window.getSize().x / 2 - 60, 50 * i + 300, 24, Color::White, 0);
			break;
		case 1:
			setText(stat, "Stat", font, "ressources/arial.ttf", window.getSize().x / 2 - 60, 50 * i + 300, 24, Color::White, 0);
			break;
		case 2:
			setText(reglage, "Reglage", font, "ressources/arial.ttf", window.getSize().x / 2 - 60, 50 * i + 300, 24, Color::White, 0);
			break;
		case 3:
			setText(quit, "Quit", font, "ressources/arial.ttf", window.getSize().x / 2 - 60, 50 * i + 300, 24, Color::White, 0);
			break;
		default:
			break;
		}
	}

	////////////////////////////////////////////////////////////

	Sound musicMenu;
	SoundBuffer bufferMenu;
	if (!bufferMenu.loadFromFile("music/chooseAFile.mp3"))
	{
		cout << "Erreur! Fichier de musique pour le menu introuvable";
		system("pause");
		exit(1); // Fichier musique Menu introuvable
	}
	musicMenu.setBuffer(bufferMenu);
	musicMenu.setLoop(true);
	musicMenu.play();
	// Si on a le temps:
	// Faire méthode init menu
	// faire méthode init fight
	// faire méthode init jeu
	//////////////////////////////////////////////////////////


	// Init musique de la world map //////////////////////////
	Sound arrMusiquePlay[3];
	Sound musicPlay1;
	Sound musicPlay2;
	Sound musicPlay3;

	SoundBuffer bufferPlay1;
	SoundBuffer bufferPlay2;
	SoundBuffer bufferPlay3;

	bool mute = false;

	int indiceLecteurMusique = 0;

	if (!bufferPlay1.loadFromFile("music/theMetropolisofFourside.mp3"))
	{
		cout << "Erreur! Fichier de musique pour le menu introuvable";
		system("pause");
		exit(1); // Fichier musique Menu introuvable
	}
	musicPlay1.setBuffer(bufferPlay1);

	if (!bufferPlay2.loadFromFile("music/lisaThePainfulOSTGarbageDay.mp3"))
	{
		cout << "Erreur! Fichier de musique pour le menu introuvable";
		system("pause");
		exit(1); // Fichier musique Menu introuvable
	}
	musicPlay2.setBuffer(bufferPlay2);

	if (!bufferPlay3.loadFromFile("music/youveComeFarNess.mp3"))
	{
		cout << "Erreur! Fichier de musique pour le menu introuvable";
		system("pause");
		exit(1); // Fichier musique Menu introuvable
	}
	musicPlay3.setBuffer(bufferPlay3);

	arrMusiquePlay[0]=musicPlay1;
	arrMusiquePlay[1]=musicPlay2;
	arrMusiquePlay[2]=musicPlay3;

	///////////////////////////////////////////////////////////

	// Lecture d'un fichier ayant le nom du joueur et ses stats. Si aucun nom est trouver crée un nouveau nom ///////////////////

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	float lastX = 0;
	float lastY = 0;
	int dir = 0;
	int dirX = 0;
	int dirY = 0;
	float temp = 0;
	int animationCpt = 0;
	int cpt1 = 0;
	int cpt2 = 0;

	Vector2f dernierePosition;

	init(0, 0, 1716, 760, "img/mapPetite.png");
	Event event;
	RectangleShape fondEcran;
	RectangleShape fondEcranFight;
	RectangleShape statJoueur;
	View viewGame(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
	viewGame.zoom(0.3);
	viewGame.move(500, -100);

	fondEcranFight.setSize(Vector2f(_fondEcranPlay.getSize().x, _fondEcranPlay.getSize().y));
	fondEcranFight.setFillColor(Color::Black);

	statJoueur.setSize(Vector2f(40, 50));
	statJoueur.setFillColor(Color::Black);
	statJoueur.setOutlineThickness(4);
	statJoueur.setOutlineColor(Color::White);

	fondEcran.setSize(Vector2f(100, 100));
	fondEcran.setFillColor(Color::Green);



	Text nomJoueur;

	nomJoueur.setFont(font); //Set la police à utiliser (elle doit avoir été loadée)
	nomJoueur.setString("Ness");		//Set le texte à afficher
	nomJoueur.setCharacterSize(10); 			//Set la taille (en pixels)
	nomJoueur.setFillColor(Color::White);			//Set la couleur du texte
	nomJoueur.setStyle(0);	//Set le style du texte
	nomJoueur.setPosition(Vector2f(_ness.getShape().getPosition().x + 18, _ness.getShape().getPosition().y + 50));

	Text pp;
	Text ppJoueur;

	ppJoueur.setFont(font); //Set la police à utiliser (elle doit avoir été loadée)
	ppJoueur.setString(std::to_string(_ness.getPp()));		//Set le texte à afficher
	ppJoueur.setCharacterSize(10); 			//Set la taille (en pixels)
	ppJoueur.setFillColor(Color::White);			//Set la couleur du texte
	ppJoueur.setStyle(0);	//Set le style du texte
	ppJoueur.setPosition(Vector2f(_ness.getShape().getPosition().x + 30, _ness.getShape().getPosition().y + 80));

	pp.setFont(font); //Set la police à utiliser (elle doit avoir été loadée)
	pp.setString("Pp : ");		//Set le texte à afficher
	pp.setCharacterSize(10); 			//Set la taille (en pixels)
	pp.setFillColor(Color::White);			//Set la couleur du texte
	pp.setStyle(0);	//Set le style du texte
	pp.setPosition(Vector2f(_ness.getShape().getPosition().x + 10, _ness.getShape().getPosition().y + 80));

	Text hp;
	Text hpJoueur;

	hpJoueur.setFont(font); //Set la police à utiliser (elle doit avoir été loadée)
	hpJoueur.setString(std::to_string(_ness.getHp()));		//Set le texte à afficher
	hpJoueur.setCharacterSize(10); 			//Set la taille (en pixels)
	hpJoueur.setFillColor(Color::White);			//Set la couleur du texte
	hpJoueur.setStyle(0);	//Set le style du texte
	hpJoueur.setPosition(Vector2f(_ness.getShape().getPosition().x + 30, _ness.getShape().getPosition().y + 65));

	hp.setFont(font); //Set la police à utiliser (elle doit avoir été loadée)
	hp.setString("Hp : ");		//Set le texte à afficher
	hp.setCharacterSize(10); 			//Set la taille (en pixels)
	hp.setFillColor(Color::White);			//Set la couleur du texte
	hp.setStyle(0);	//Set le style du texte
	hp.setPosition(Vector2f(_ness.getShape().getPosition().x + 10, _ness.getShape().getPosition().y + 65));
	


	////////////////////////////////////////////////////////////////////////
	// MOVE ANIMATION Ne Pas Supprimer SVP
	// Fonctionnalité qu'on aura surement pas le temps d'implémenter, mais j'aimerais garder ce code quand même,car l'annimation fonctionnais

	//Clock pour limiter les fps surtout pour la gestion des animations
	/*Clock clock;
	Time time;

	RectangleShape animationTest;
	IntRect animationFrame(1 , 226, 256, 224);
	animationTest.setSize(Vector2f(256, 224));
	Texture textureAnimation;

	if (!textureAnimation.loadFromFile("img/testAnimation.png"))
	{
		exit(1);
	}

	animationTest.setTexture(&textureAnimation);
	animationTest.setTextureRect(animationFrame);
	int cptLeft=0;
	int cptTop=0;
	viewGame.zoom(5);
	viewGame.move(-1800,100);

	/////////////////////////////////////////////////////////////////////
	//ANIMATION

	time = clock.getElapsedTime();
	if (time.asMilliseconds() >= 100.0f)
	{
	////////////////////////////////////////////////////////////////////
		window.clear();
		window.setView(viewGame);
		window.draw(getBG());
		window.draw(_ness.getShape());
		//////////////////////////////////////////////////////////////
		//TEST ANIMATION

		window.draw(animationTest);
		if (cptLeft < 4 )
		{
			cptLeft++;
			animationFrame.left += 257;
		}
		else if (cptTop < 17)
		{
			cptTop++;
			cptLeft = 0;
			animationFrame.left = 1;
			animationFrame.top += 225;

		}
		else
		{
			cptLeft = 0;
			cptTop = 0;
			animationFrame.left = 1;
			animationFrame.top = 1;
		}
		cout << cptLeft << " " << cptTop;
		animationTest.setTextureRect(animationFrame);
		clock.restart();
		/////////////////////////////////////////////////////////////
		window.display();
	*/
	//////////////////////////////////////////////////////////////////



	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
			else if (event.type == Event::KeyPressed)
			{
				switch (event.key.code) {
				case Keyboard::Escape:
					window.close();
					break;
				case Keyboard::S:

					if (Keyboard::isKeyPressed(Keyboard::A))
					{
						dir = 5;//bas gauche
					}
					else if (Keyboard::isKeyPressed(Keyboard::D))
					{
						dir = 6;//bas droite
					}
					else
					{
						dir = 1;//bas
						
					}
					break;
				case Keyboard::W:
					if (Keyboard::isKeyPressed(Keyboard::A))
					{
						dir = 7;//haut gauche
					}
					else if (Keyboard::isKeyPressed(Keyboard::D))
					{
						dir = 8;//haut droite
					}
					else
					{
						dir = 2;//Haut
					}
					break;
				case Keyboard::A:
					if (Keyboard::isKeyPressed(Keyboard::S))
					{
						dir = 9;//Gauche bas
					}
					else if (Keyboard::isKeyPressed(Keyboard::W))
					{
						dir = 10;//Gauche haut
					}
					else
					{
						dir = 3;//gauche
					}

					break;
				case Keyboard::D:
					if (Keyboard::isKeyPressed(Keyboard::S))
					{
						dir = 11;//Droite bas
					}
					else if (Keyboard::isKeyPressed(Keyboard::W))
					{
						dir = 12;//Droite haut
					}
					else
					{
						dir = 4;//Droite
					}
					break;
				case Keyboard::P:
						if (musicMenu.getStatus() == sf::Music::Status::Playing)
						{
							musicMenu.stop();
						}
						if (!mute && menubool)
						{
							arrMusiquePlay[indiceLecteurMusique].play();
						}
						menubool = false;
					break;
				case Keyboard::N:
					arrMusiquePlay[indiceLecteurMusique].stop();
					break;
				case Keyboard::M:

					if (menubool == true)
					{
						if (mute == false)
						{
							musicMenu.stop();
							mute = true;
						}
						else
						{
							musicMenu.play();
							mute = false;
						}
					}
					else
					{
						if (mute == false)
						{
							mute = true;
							arrMusiquePlay[indiceLecteurMusique].stop();
						}
						else
						{
							mute = false;
							arrMusiquePlay[indiceLecteurMusique].play();
						}
					}
				
					break;
				default:
					dir = 0;
					break;
				}

				//std::cout << dir << std::endl;
			}
			else if (event.type == Event::KeyReleased)//Pour régler les diagonales qui continue même si on à Released une touche
			{
				switch (event.key.code)
				{
				case Keyboard::S:
					//std::cout << "Released" << event.type;
					switch (dir)
					{
					case 1:
						dir = 0;
						break;
					case 5:
						dir = 3;
						break;
					case 6:
						dir = 4;
						break;
					case 9:
						dir = 3;
						break;
					case 11:
						dir = 4;
					default:
						break;
					}
					break;
				case Keyboard::W:
					switch (dir)
					{
					case 2:
						dir = 0;
						break;
					case 7:
						dir = 3;
						break;
					case 8:
						dir = 4;
						break;
					case 10:
						dir = 3;
						break;
					case 12:
						dir = 4;
						break;
					default:
						break;
					}
					break;
				case Keyboard::A:
					switch (dir)
					{
					case 3:
						dir = 0;
						break;
					case 5:
						dir = 1;
						break;
					case 7:
						dir = 2;
						break;
					case 9:
						dir = 1;
						break;
					case 10:
						dir = 2;
						break;
					default:
						break;
					}
					break;
				case Keyboard::D:
					switch (dir)
					{
					case 4:
						dir = 0;
						break;
					case 6:
						dir = 1;
						break;
					case 8:
						dir = 2;
						break;
					case 11:
						dir = 1;
						break;
					case 12:
						dir = 2;
						break;
					default:
						break;
					}
					break;
				default:
					break;
				}
			}
			else if (event.type == Event::JoystickMoved)
			{
				if (event.joystickMove.axis == sf::Joystick::X)
				{
					lastX = Joystick::getAxisPosition(0, sf::Joystick::X) / 25;
					std::cout << "X: " << Joystick::getAxisPosition(0, sf::Joystick::X) << std::endl;
					if (lastX < 0)
					{
						dirX = 3;
					}
					else if (lastX > 0)
					{
						dirX = 4;
					}
				}
				if (event.joystickMove.axis == sf::Joystick::Y)
				{
					lastY = event.joystickMove.position / 25;
					std::cout << "Y: " << Joystick::getAxisPosition(0, sf::Joystick::Y) << std::endl;
					if (lastY < 0)
					{
						dirY = 2;
					}
					else if (lastY > 0)
					{
						dirY = 1;
					}
				}
				////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				// À METTRE EN FONCTIOM SI ON A LE TEMPS
				// Doit déterminer la valeur la plus importante pour choisir quelle sprite afficher pour le bonhomme
				// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				//comparer lastX et lastY
				if (lastX < 0 && lastY > 0)
				{
					//conversion
					temp = lastX * -1;
					if (temp >= lastY)
					{
						dir = dirX;
					}
					else
					{
						dir = dirY;
					}
				}
				else if (lastX > 0 && lastY < 0)
				{
					//conversion
					temp = lastY * -1;
					if (temp >= lastX)
					{
						dir = dirY;
					}
					else
					{
						dir = dirX;
					}
				}
				else if (lastY < 0 && lastX < 0)
				{
					if (lastX <= lastY)
					{
						dir = dirX;
					}
					else
					{
						dir = dirY;
					}
				}
				else if (lastY > 0 && lastX > 0)
				{
					if (lastX > lastY)
					{
						dir = dirX;
					}
					else
					{
						dir = dirY;
					}
				}
				//deadZone pas de movement
				if (lastX < 0.2 && lastX > -0.2 && lastY < 0.2 && lastY > -0.2)
				{
					dir = 0;
					lastX = 0;
					lastY = 0;
				}
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			}
		} 
		// FIN DU POLLEVENT //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


		// GESTION DE L'AFFICHAGE ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		// Affichage menu
		if (menubool)
		{
			window.clear();
			window.draw(fondEcranMenu);
			/*for (int i = 0; i < mapHitbox.size(); i++)
				window.draw(mapHitbox.at(i));*/
			window.draw(play);
			window.draw(stat);
			window.draw(reglage);
			window.draw(quit);
			window.display();
			/*
			if (nomJoueurTemp.length() == 3)
			{

				window.draw(nomJoueur);

				for (int i = 0; i < 3; i++)
				{
					window.draw(menu[i]);
					window.draw(txt1);
					window.draw(txt2);
					window.draw(txt3);
				}

			}
			else
			{
				window.draw(txtInfo);
				window.draw(nomJoueur);

			}*/
		}
		else if (_ness.getShape().getGlobalBounds().intersects(_monstre1.getShape().getGlobalBounds())) 
		{ // Si un combat doit s'ammorcer
			_monstre1.setPosition(Vector2f(_ness.getShape().getPosition().x + 20, _ness.getShape().getPosition().y - 20));
			statJoueur.setPosition(Vector2f(_ness.getShape().getPosition().x + 10, _ness.getShape().getPosition().y + 50));
			window.clear();
			window.setView(viewGame);
			window.draw(fondEcranFight);
			window.draw(_monstre1.getShape());
			window.draw(statJoueur);
			window.draw(nomJoueur);
			window.draw(hpJoueur);
			window.draw(hp);
			window.draw(ppJoueur);
			window.draw(pp);
			window.display();
			system("pause>0");
		}
		else if (_ness.getShape().getGlobalBounds().intersects(_monstre2.getShape().getGlobalBounds())) {
			_monstre2.setPosition(Vector2f(_ness.getShape().getPosition().x + 40, _ness.getShape().getPosition().y));
			window.clear();
			window.setView(viewGame);
			window.draw(fondEcranFight);
			window.draw(nomJoueur);
			window.draw(_monstre2.getShape());
			window.display();
			system("pause>0");
		}
		else
		{	// Affichage normal en jeu /////////////////////////////////////////////////
			
			//gestion musique
			if (arrMusiquePlay[indiceLecteurMusique].getStatus() == sf::Music::Status::Stopped && mute == false)
			{
				if (indiceLecteurMusique < sizeof(arrMusiquePlay)/ sizeof(Sound) - 1)
					indiceLecteurMusique++;
				else
					indiceLecteurMusique = 0;

				arrMusiquePlay[indiceLecteurMusique].play();
			}
			
			window.clear();
			window.setView(viewGame);

			window.draw(getBG());
			window.draw(_ness.getShape());
			window.draw(_monstre1.getShape());
			window.draw(_monstre2.getShape());


			//cout << _ness.getHitboxPosition().x << " " << _ness.getHitboxPosition().y;

			/*for (int i = 0; i < mapHitbox.size(); i++)
							window.draw(mapHitbox.at(i));*/


			if (dir != 0)
			{
				if (!ifcollision(mapHitbox))
				{
					dernierePosition = _ness.getPosition();
					viewGame = _ness.move(dir, lastX, lastY, animationCpt, viewGame);
				}
				else
				{
					_ness.setHitboxPosition(dernierePosition.x + 6, dernierePosition.y + 6);
					_ness.setPosition(dernierePosition.x, dernierePosition.y);
					viewGame.setCenter(dernierePosition.x, dernierePosition.y);

				}
			}


			//window.draw(mapHitbox.at(nbCellule));
			//window.draw(mapHitbox.at(nbCellule - 1));

			cpt1 = _monstre1.moveMonstre(cpt1);
			cpt2 = _monstre2.moveMonstre(cpt2);
			window.display();
		}

	}
}

bool Game::ifcollision(std::vector<RectangleShape> &Hitbox)
{
	int ligne = _ness.getHitboxPosition().y / 5;
	int col = _ness.getHitboxPosition().x / 5;
	int nbCellule = ((ligne + 3) * 343) + col + 1;

	return (Hitbox.at(nbCellule).getFillColor() == Color::Red || Hitbox.at(nbCellule - 1).getFillColor() == Color::Red);
}

const sf::RectangleShape Game::getBG() const
{
	return _fondEcranPlay;
}



