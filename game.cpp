#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Windows.h>
#include <cmath>
#include <time.h>
#include "queue.hpp"
#include "liste.hpp"
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
	//Init Menu Principal ///////////////////////////////////
	RenderWindow window(VideoMode(1600, 900), "Earthbound");
	bool menubool = true; // Si true, on est dans le menu
	string nomJoueurTemp = "test";
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

	init(0, 0, 1716, 760, "img/mapPetite.png");
	Event event;
	RectangleShape fondEcran;
	RectangleShape fondEcranFight;
	RectangleShape statJoueur;
	RectangleShape actionJoueur;
	View viewGame(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
	viewGame.zoom(0.3);
	viewGame.move(500, -100);
	View viewFight(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
	
	

	fondEcranFight.setSize(Vector2f(1600, 900));
	fondEcranFight.setFillColor(Color::Black);

	actionJoueur.setSize(Vector2f(400, 180));
	actionJoueur.setFillColor(Color::Black);
	actionJoueur.setOutlineThickness(16);
	actionJoueur.setOutlineColor(Color::White);

	statJoueur.setSize(Vector2f(160, 200));
	statJoueur.setFillColor(Color::Black);
	statJoueur.setOutlineThickness(16);
	statJoueur.setOutlineColor(Color::White);

	fondEcran.setSize(Vector2f(100, 100));
	fondEcran.setFillColor(Color::Green);



	Text nomJoueur;

	nomJoueur.setFont(font); //Set la police à utiliser (elle doit avoir été loadée)
	nomJoueur.setString("Ness");		//Set le texte à afficher
	nomJoueur.setCharacterSize(40); 			//Set la taille (en pixels)
	nomJoueur.setFillColor(Color::White);			//Set la couleur du texte
	nomJoueur.setStyle(0);	//Set le style du texte
	

	Text pp;
	Text ppJoueur;

	ppJoueur.setFont(font); //Set la police à utiliser (elle doit avoir été loadée)
	ppJoueur.setString(std::to_string(_ness.getPp()));		//Set le texte à afficher
	ppJoueur.setCharacterSize(40); 			//Set la taille (en pixels)
	ppJoueur.setFillColor(Color::White);			//Set la couleur du texte
	ppJoueur.setStyle(0);	//Set le style du texte
	

	pp.setFont(font); //Set la police à utiliser (elle doit avoir été loadée)
	pp.setString("Pp : ");		//Set le texte à afficher
	pp.setCharacterSize(40); 			//Set la taille (en pixels)
	pp.setFillColor(Color::White);			//Set la couleur du texte
	pp.setStyle(0);	//Set le style du texte
	

	Text hp;
	Text hpJoueur;

	hpJoueur.setFont(font); //Set la police à utiliser (elle doit avoir été loadée)
	hpJoueur.setString(std::to_string(_ness.getHp()));		//Set le texte à afficher
	hpJoueur.setCharacterSize(40); 			//Set la taille (en pixels)
	hpJoueur.setFillColor(Color::White);			//Set la couleur du texte
	hpJoueur.setStyle(0);	//Set le style du texte
	

	hp.setFont(font); //Set la police à utiliser (elle doit avoir été loadée)
	hp.setString("Hp : ");		//Set le texte à afficher
	hp.setCharacterSize(40); 			//Set la taille (en pixels)
	hp.setFillColor(Color::White);			//Set la couleur du texte
	hp.setStyle(0);	//Set le style du texte
	
	Text attaque;

	attaque.setFont(font); //Set la police à utiliser (elle doit avoir été loadée)
	attaque.setString("Move");		//Set le texte à afficher
	attaque.setCharacterSize(40); 			//Set la taille (en pixels)
	attaque.setFillColor(Color::White);			//Set la couleur du texte
	attaque.setStyle(0);	//Set le style du texte

	Text fuite;

	fuite.setFont(font); //Set la police à utiliser (elle doit avoir été loadée)
	fuite.setString("Fuite");		//Set le texte à afficher
	fuite.setCharacterSize(40); 			//Set la taille (en pixels)
	fuite.setFillColor(Color::White);			//Set la couleur du texte
	fuite.setStyle(0);	//Set le style du texte

	Text item;

	item.setFont(font); //Set la police à utiliser (elle doit avoir été loadée)
	item.setString("Item");		//Set le texte à afficher
	item.setCharacterSize(40); 			//Set la taille (en pixels)
	item.setFillColor(Color::White);			//Set la couleur du texte
	item.setStyle(0);	//Set le style du texte

	Text resultSuite;

	resultSuite.setFont(font); //Set la police à utiliser (elle doit avoir été loadée)
	resultSuite.setString("");		//Set le texte à afficher
	resultSuite.setCharacterSize(40); 			//Set la taille (en pixels)
	resultSuite.setFillColor(Color::White);			//Set la couleur du texte
	resultSuite.setStyle(0);	//Set le style du texte

	Text suivant;

	suivant.setFont(font); //Set la police à utiliser (elle doit avoir été loadée)
	suivant.setString("Suivant");		//Set le texte à afficher
	suivant.setCharacterSize(40); 			//Set la taille (en pixels)
	suivant.setFillColor(Color::White);			//Set la couleur du texte
	suivant.setStyle(0);	//Set le style du texte

	Text retour;

	retour.setFont(font); //Set la police à utiliser (elle doit avoir été loadée)
	retour.setString("Retour");		//Set le texte à afficher
	retour.setCharacterSize(40); 			//Set la taille (en pixels)
	retour.setFillColor(Color::White);			//Set la couleur du texte
	retour.setStyle(0);	//Set le style du texte

	Item arme(1, "big league bat", 10, "force", false);
	Item armure(2, "diamond band", 10, "def", false);
	Item frites(3, "bag of fries", 10, "hp", true);
	Item banane(4, "banana", 10, "force", true);
	Item burger(5, "double burger", 10, "pp", true);
	Item cookie(6, "cookie", 10, "def", true);

	_ness.addItem(burger);
	_ness.addItem(arme);
	_ness.addItem(cookie);


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
			else if (event.type == Event::MouseButtonPressed && menubool && nomJoueurTemp.length() >= 3)
			{
				if (play.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
				{
					play.setFillColor(Color::Black);
				}
				else if (stat.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
				{
					stat.setFillColor(Color::Black);
				}
				else if (reglage.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
				{
					reglage.setFillColor(Color::Black);
				}
				else if (quit.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
				{
					exit(0);
				}

			}
			else if (event.type == sf::Event::MouseMoved && menubool && nomJoueurTemp.length() >= 3)
			{
				
				if (play.getGlobalBounds().contains(Vector2f(sf::Mouse::getPosition(window))))
				{
					play.setFillColor(Color::Red);
				}
				else
				{
					play.setFillColor(Color::White);
				}

				if (stat.getGlobalBounds().contains(Vector2f(sf::Mouse::getPosition(window))))
				{
					stat.setFillColor(Color::Red);
				}
				else
				{
					stat.setFillColor(Color::White);
				}

				if (reglage.getGlobalBounds().contains(Vector2f(sf::Mouse::getPosition(window))))
				{
					reglage.setFillColor(Color::Red);
				}
				else
				{
					reglage.setFillColor(Color::White);
				}

				if (quit.getGlobalBounds().contains(Vector2f(sf::Mouse::getPosition(window))))
				{
					quit.setFillColor(Color::Red);
				}
				else
				{
					quit.setFillColor(Color::White);
				}
				
			}
		}

		// FIN DU POLLEVENT //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


		// GESTION DE L'AFFICHAGE ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		// Affichage menu
		
		if (menubool)
		{
			if (play.getFillColor() == Color::Black)
			{
				if (musicMenu.getStatus() == sf::Music::Status::Playing)
				{
					musicMenu.stop();
				}
				if (!mute && menubool)
				{
					arrMusiquePlay[indiceLecteurMusique].play();
				}
				menubool = false;
			}
			else
			{
				window.clear();
				window.draw(fondEcranMenu);
				window.draw(play);
				window.draw(stat);
				window.draw(reglage);
				window.draw(quit);
				window.display();
			}

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
			
			bool fight = true;
			int menu = 0;
			float positionMonstreX = _monstre1.getPosition().x;
			float positionMonstreY = _monstre1.getPosition().y;
			_monstre1.setPosition(Vector2f(700, 360));
			_monstre1.setSize(200, 180);
			actionJoueur.setPosition(Vector2f(60, 45));
			attaque.setPosition(Vector2f(75, 50));
			item.setPosition(Vector2f(75, 150));
			fuite.setPosition(Vector2f(300, 150));
			statJoueur.setPosition(Vector2f(720, 650));
			nomJoueur.setPosition(Vector2f(755, 660));
			hp.setPosition(Vector2f(725, 720));
			hpJoueur.setPosition(Vector2f(800, 720));
			pp.setPosition(Vector2f(725, 780));
			ppJoueur.setPosition(Vector2f(800, 780));
			suivant.setPosition(Vector2f(500, 150));
			retour.setPosition(Vector2f(500, 150));
		
			while (fight==true) {
				while (window.pollEvent(event)) {
					

					window.clear();
					window.setView(viewFight);
					window.draw(fondEcranFight);
					window.draw(_monstre1.getShape());
					window.draw(actionJoueur);
					if (menu == 0) 
					{
						window.draw(attaque);
						window.draw(item);
						window.draw(fuite);
						window.draw(statJoueur);
						window.draw(nomJoueur);
						window.draw(hpJoueur);
						window.draw(hp);
						window.draw(ppJoueur);
						window.draw(pp);
						window.display();
					}
					
					if (event.type == Event::MouseButtonPressed || menu > 0)
					{
						if (attaque.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y) || menu == 1) {
							window.draw(actionJoueur);
							window.draw(attaque);
							menu = 1;
						}
						else if (item.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y) || menu == 2) {
							_ness.getInventaire().begin();
							window.draw(actionJoueur);
							for (int i = 0; i < _ness.getInventaire().size(); i++) {
								cout << _ness.getInventaire().value().getNom();
								_ness.getInventaire().next();
							}
							window.draw(retour);
							window.draw(statJoueur);
							window.draw(nomJoueur);
							window.draw(hpJoueur);
							window.draw(hp);
							window.draw(ppJoueur);
							window.draw(pp);
							window.display();
								
							menu = 2;
						}
						else if (fuite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y) || menu == 3) {
							int chanceFuite = rand() % (4 + 1 - 1) + 1;
							bool next = false;
							if (chanceFuite == 1) {
								 do {
									window.draw(actionJoueur);
									resultSuite.setString("Vous avez réussi \nà vous enfuir!");
									resultSuite.setPosition(Vector2f(75, 50));
									window.draw(resultSuite);
									window.draw(suivant);
									window.draw(statJoueur);
									window.draw(nomJoueur);
									window.draw(hpJoueur);
									window.draw(hp);
									window.draw(ppJoueur);
									window.draw(pp);
									window.display();
									while (window.pollEvent(event)) {
										if (event.type == Event::MouseButtonPressed) {
											if (suivant.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
												next = true;
												_monstre1.~Monstre();
												
											}
										}
									}
								} while (next == false);

								
								fight = false;
							}
							else {
								do {
									window.draw(actionJoueur);
									resultSuite.setString("Vous n'avez pas \nréussi à vous enfuir!");
									resultSuite.setPosition(Vector2f(75, 50));
									window.draw(resultSuite);
									window.draw(suivant);
									window.draw(statJoueur);
									window.draw(nomJoueur);
									window.draw(hpJoueur);
									window.draw(hp);
									window.draw(ppJoueur);
									window.draw(pp);
									window.display();
									while (window.pollEvent(event)) {
										if (event.type == Event::MouseButtonPressed) {
											if (suivant.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
												next = true;
											}
										}
									}
								} while (next == false);
							}
							
							
						}

					}
					
				}
		
			}
			attaque.setFillColor(Color::White);
			item.setFillColor(Color::White);
			fuite.setFillColor(Color::White);
			suivant.setFillColor(Color::White);

		}
		else if (_ness.getShape().getGlobalBounds().intersects(_monstre2.getShape().getGlobalBounds())) {
		bool fight = true;
		int menu = 0;
		float positionMonstreX = _monstre2.getPosition().x;
		float positionMonstreY = _monstre2.getPosition().y;
		_monstre2.setPosition(Vector2f(700, 360));
		_monstre2.setSize(200, 180);
		actionJoueur.setPosition(Vector2f(60, 45));
		attaque.setPosition(Vector2f(75, 50));
		item.setPosition(Vector2f(75, 150));
		fuite.setPosition(Vector2f(300, 150));
		statJoueur.setPosition(Vector2f(720, 650));
		nomJoueur.setPosition(Vector2f(755, 660));
		hp.setPosition(Vector2f(725, 720));
		hpJoueur.setPosition(Vector2f(800, 720));
		pp.setPosition(Vector2f(725, 780));
		ppJoueur.setPosition(Vector2f(800, 780));
		suivant.setPosition(Vector2f(500, 150));

		while (fight == true) {
			while (window.pollEvent(event)) {


				window.clear();
				window.setView(viewFight);
				window.draw(fondEcranFight);
				window.draw(_monstre2.getShape());
				window.draw(actionJoueur);
				if (menu == 0)
				{
					window.draw(attaque);
					window.draw(item);
					window.draw(fuite);
					window.draw(statJoueur);
					window.draw(nomJoueur);
					window.draw(hpJoueur);
					window.draw(hp);
					window.draw(ppJoueur);
					window.draw(pp);
					window.display();
				}

				if (event.type == Event::MouseButtonPressed || menu > 0)
				{
					if (attaque.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y) || menu == 1) {
						
						window.draw(actionJoueur);
						window.draw(attaque);
						menu = 1;
					}
					else if (item.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y) || menu == 2) {
						
						menu = 2;
					}
					else if (fuite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y) || menu == 3) {
						
						int chanceFuite = rand() % (4 + 1 - 1) + 1;
						bool next = false;
						if (chanceFuite == 1) {
							do {
								window.draw(actionJoueur);
								resultSuite.setString("Vous avez réussi \nà vous enfuir!");
								resultSuite.setPosition(Vector2f(75, 50));
								window.draw(resultSuite);
								window.draw(suivant);
								window.draw(statJoueur);
								window.draw(nomJoueur);
								window.draw(hpJoueur);
								window.draw(hp);
								window.draw(ppJoueur);
								window.draw(pp);
								window.display();
								while (window.pollEvent(event)) {
									if (event.type == Event::MouseButtonPressed) {
										if (suivant.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
											next = true;
											_monstre2.~Monstre();
										}
									}
								}
							} while (next == false);
							fight = false;
						}
						else {
							do {
								window.draw(actionJoueur);
								resultSuite.setString("Vous n'avez pas \nréussi à vous enfuir!");
								resultSuite.setPosition(Vector2f(75, 50));
								window.draw(resultSuite);
								window.draw(suivant);
								window.draw(statJoueur);
								window.draw(nomJoueur);
								window.draw(hpJoueur);
								window.draw(hp);
								window.draw(ppJoueur);
								window.draw(pp);
								window.display();
								while (window.pollEvent(event)) {
									if (event.type == Event::MouseButtonPressed) {
										if (suivant.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
											next = true;
										}
									}
								}
							} while (next == false);
						}


					}

				}

			}

		}
		attaque.setFillColor(Color::White);
		item.setFillColor(Color::White);
		fuite.setFillColor(Color::White);
		suivant.setFillColor(Color::White);
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

			viewGame = _ness.move(dir, lastX, lastY, animationCpt, viewGame);

			cpt1 = _monstre1.moveMonstre(cpt1);
			cpt2 = _monstre2.moveMonstre(cpt2);
			window.display();
		}

	}
}



const sf::RectangleShape Game::getBG() const
{
	return _fondEcranPlay;
}



