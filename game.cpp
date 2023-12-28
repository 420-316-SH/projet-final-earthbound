#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Windows.h>
#include <cmath>
#include <time.h>
#include <fstream>
#include <sstream>
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

	_monstre1.setMonstre(true, 100, 2, 2, 0, 0, 1, 1, 0, moveNess, 1380, 410, 16, 24, rectSpriteNess, "img/charsetsNess.png");
	_monstre2.setMonstre(true, 100, 2, 2, 0, 0, 1, 1, 0, moveNess, 845, 370, 16, 24, rectSpriteNess, "img/charsetsNess.png");
	_monstre3.setMonstre(true, 100, 2, 2, 0, 0, 1, 1, 0, moveNess, 1020, 610, 16, 24, rectSpriteNess, "img/charsetsNess.png");
	_monstre4.setMonstre(true, 100, 2, 2, 0, 0, 1, 1, 0, moveNess, 705, 450, 16, 24, rectSpriteNess, "img/charsetsNess.png");
	_monstre5.setMonstre(true, 100, 2, 2, 0, 0, 1, 1, 0, moveNess, 265, 480, 16, 24, rectSpriteNess, "img/charsetsNess.png");
	_monstre6.setMonstre(true, 100, 2, 2, 0, 0, 1, 1, 0, moveNess, 265, 280, 16, 24, rectSpriteNess, "img/charsetsNess.png");
	_monstre7.setMonstre(true, 100, 2, 2, 0, 0, 1, 1, 0, moveNess, 370, 210, 16, 24, rectSpriteNess, "img/charsetsNess.png");
	_monstre8.setMonstre(true, 100, 2, 2, 0, 0, 1, 1, 0, moveNess, 820, 165, 16, 24, rectSpriteNess, "img/charsetsNess.png");
	_monstre9.setMonstre(true, 100, 2, 2, 0, 0, 1, 1, 0, moveNess, 740, 85, 16, 24, rectSpriteNess, "img/charsetsNess.png");

}

void Game::setText(sf::Text& text, const char* message, sf::Font& font, const char* police, int posX, int posY, int taille, const sf::Color& color, int style)
{
	if (!font.loadFromFile(police))
		exit(1);

	text.setFont(font); //Set la police � utiliser (elle doit avoir �t� load�e)
	text.setString(message);		//Set le texte � afficher
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
	RenderWindow window(VideoMode(1600, 900), "Earthbound Window");
	bool menubool = true; // Si true, on est dans le menu
	bool menuReglage = false;
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
	Text reglage;
	Text quit;

	Text reglageSon;
	Text difficulte;
	Text fullscreen;
	Text retourMenu;
	Text bonusActif;

	float boost = 1;

	Font font;
	if (!font.loadFromFile("ressources/arial.ttf")) {
		exit(1);
	}


	for (int i = 1; i < 4; i++)
	{
		switch (i)
		{
		case 1:
			setText(play, "Play", font, "ressources/arial.ttf", window.getSize().x / 2 - 60, 50 * i + 300, 24, Color::White, 0);
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

	for (int i = 0; i < 4; i++)
	{
		switch (i)
		{
		case 0:
			setText(reglageSon, "D�sactiver le son", font, "ressources/arial.ttf", window.getSize().x / 2 - 100, 50 * i + 300, 24, Color::White, 0);
			break;
		case 1:
			setText(difficulte, "Hard mode", font, "ressources/arial.ttf", window.getSize().x / 2 - 100, 50 * i + 300, 24, Color::White, 0);
			break;
		case 2:
			setText(fullscreen, "Mode plein �cran", font, "ressources/arial.ttf", window.getSize().x / 2 - 100, 50 * i + 300, 24, Color::White, 0);
			break;
		case 3:
			setText(retourMenu, "Retour", font, "ressources/arial.ttf", window.getSize().x / 2 - 100, 50 * i + 300, 24, Color::White, 0);
			break;
		default:
			break;
		}
	}
		
	setText(bonusActif, "HARD MODE", font, "ressources/arial.ttf", window.getSize().x - 200, 10, 16, Color::Red, 0);
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
	// Init affichage Win /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	RectangleShape winBG;


	Text finDePartie;

	setText(finDePartie, "Retour au menu", font, "ressources/arial.ttf", window.getSize().x - 200, 10, 16, Color::White, 0);

	Texture texturefondEcranWin;
	winBG.setPosition(0, 0);
	winBG.setSize(Vector2f(300, 150));
	if (!texturefondEcranWin.loadFromFile("img/winBG.png"))
	{
		cout << "Erreur! L'image du menu background est introuvable";
		system("pause");
		exit(1); // Fichier musique Menu introuvable
	}
	winBG.setTexture(&texturefondEcranWin);

	// Init affichage Loose /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	RectangleShape loseBG;

	Texture texturefondEcranLose;
	loseBG.setPosition(0, 0);
	loseBG.setSize(Vector2f(300, 150));
	if (!texturefondEcranLose.loadFromFile("img/loseBG.png"))
	{
		cout << "Erreur! L'image du menu background est introuvable";
		system("pause");
		exit(1); // Fichier musique Menu introuvable
	}
	loseBG.setTexture(&texturefondEcranLose);


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
	///////////////////////////////////////////////////////////////////
	Sound musicWin;
	SoundBuffer bufferWin;
	if (!bufferWin.loadFromFile("music/youWin.mp3"))
	{
		cout << "Erreur! Fichier de musique pour le menu introuvable";
		system("pause");
		exit(1); // Fichier musique Menu introuvable
	}
	musicWin.setBuffer(bufferWin);
	///////////////////////////////////////////////////////////////////
	Sound musicLose;
	SoundBuffer bufferLose;
	if (!bufferLose.loadFromFile("music/aBadDream.mp3"))
	{
		cout << "Erreur! Fichier de musique pour le menu introuvable";
		system("pause");
		exit(1); // Fichier musique Menu introuvable
	}
	musicLose.setBuffer(bufferLose);

	// Si on a le temps:
	// Faire m�thode init menu
	// faire m�thode init fight
	// faire m�thode init jeu
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
	bool fullscrmode = false;

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
	int cpt3 = 0;
	int cpt4 = 0;
	int cpt5 = 0;
	int cpt6 = 0;
	int cpt7 = 0;
	int cpt8 = 0;
	int cpt9 = 0;

	int deadMonster = 0;
	bool win = false;
	bool lose = false;


	Vector2f dernierePosition;

	init(0, 0, 1716, 760, "img/mapPetite.png");
	Event event;
	RectangleShape fondEcran;
	RectangleShape fondEcranFight;
	RectangleShape statJoueur;
	RectangleShape actionJoueur;
	View viewGame(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
	viewGame.zoom(0.3);
	viewGame.setCenter(_ness.getPosition());
	View viewFight(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
	View endGame(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
	endGame.zoom(0.3);
	endGame.setCenter(150, 75);
	
	

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

	nomJoueur.setFont(font); //Set la police � utiliser (elle doit avoir �t� load�e)
	nomJoueur.setString("Ness");		//Set le texte � afficher
	nomJoueur.setCharacterSize(40); 			//Set la taille (en pixels)
	nomJoueur.setFillColor(Color::White);			//Set la couleur du texte
	nomJoueur.setStyle(0);	//Set le style du texte
	

	Text pp;
	Text ppJoueur;

	ppJoueur.setFont(font); //Set la police � utiliser (elle doit avoir �t� load�e)
	ppJoueur.setString(std::to_string(_ness.getPp()));		//Set le texte � afficher
	ppJoueur.setCharacterSize(40); 			//Set la taille (en pixels)
	ppJoueur.setFillColor(Color::White);			//Set la couleur du texte
	ppJoueur.setStyle(0);	//Set le style du texte
	

	pp.setFont(font); //Set la police � utiliser (elle doit avoir �t� load�e)
	pp.setString("Pp : ");		//Set le texte � afficher
	pp.setCharacterSize(40); 			//Set la taille (en pixels)
	pp.setFillColor(Color::White);			//Set la couleur du texte
	pp.setStyle(0);	//Set le style du texte
	

	Text hp;
	Text hpJoueur;

	hpJoueur.setFont(font); //Set la police � utiliser (elle doit avoir �t� load�e)
	hpJoueur.setString(std::to_string(_ness.getHp()));		//Set le texte � afficher
	hpJoueur.setCharacterSize(40); 			//Set la taille (en pixels)
	hpJoueur.setFillColor(Color::White);			//Set la couleur du texte
	hpJoueur.setStyle(0);	//Set le style du texte
	

	hp.setFont(font); //Set la police � utiliser (elle doit avoir �t� load�e)
	hp.setString("Hp : ");		//Set le texte � afficher
	hp.setCharacterSize(40); 			//Set la taille (en pixels)
	hp.setFillColor(Color::White);			//Set la couleur du texte
	hp.setStyle(0);	//Set le style du texte
	
	Text attaque;

	attaque.setFont(font); //Set la police � utiliser (elle doit avoir �t� load�e)
	attaque.setString("Move");		//Set le texte � afficher
	attaque.setCharacterSize(40); 			//Set la taille (en pixels)
	attaque.setFillColor(Color::White);			//Set la couleur du texte
	attaque.setStyle(0);	//Set le style du texte

	Text fuite;

	fuite.setFont(font); //Set la police � utiliser (elle doit avoir �t� load�e)
	fuite.setString("Fuite");		//Set le texte � afficher
	fuite.setCharacterSize(40); 			//Set la taille (en pixels)
	fuite.setFillColor(Color::White);			//Set la couleur du texte
	fuite.setStyle(0);	//Set le style du texte

	Text item;

	item.setFont(font); //Set la police � utiliser (elle doit avoir �t� load�e)
	item.setString("Item");		//Set le texte � afficher
	item.setCharacterSize(40); 			//Set la taille (en pixels)
	item.setFillColor(Color::White);			//Set la couleur du texte
	item.setStyle(0);	//Set le style du texte

	Text resultSuite;

	resultSuite.setFont(font); //Set la police � utiliser (elle doit avoir �t� load�e)
	resultSuite.setString("");		//Set le texte � afficher
	resultSuite.setCharacterSize(40); 			//Set la taille (en pixels)
	resultSuite.setFillColor(Color::White);			//Set la couleur du texte
	resultSuite.setStyle(0);	//Set le style du texte

	Text suivant;

	suivant.setFont(font); //Set la police � utiliser (elle doit avoir �t� load�e)
	suivant.setString("Suivant");		//Set le texte � afficher
	suivant.setCharacterSize(40); 			//Set la taille (en pixels)
	suivant.setFillColor(Color::White);			//Set la couleur du texte
	suivant.setStyle(0);	//Set le style du texte

	Text retour;

	retour.setFont(font); //Set la police � utiliser (elle doit avoir �t� load�e)
	retour.setString("Retour");		//Set le texte � afficher
	retour.setCharacterSize(40); 			//Set la taille (en pixels)
	retour.setFillColor(Color::White);			//Set la couleur du texte
	retour.setStyle(0);	//Set le style du texte

	Text obj[10];

	Item arme(1, "big league bat", 10, "force", false);
	Item armure(2, "diamond band", 10, "def", false);
	Item frites(3, "bag of fries", 10, "def", true);
	Item banane(4, "banana", 10, "force", true);
	Item burger(5, "double burger", 10, "pp", true);
	Item cookie(6, "cookie", 10, "hp", true);

	_ness.addItem(burger);
	_ness.addItem(arme);
	_ness.addItem(cookie);


	////////////////////////////////////////////////////////////////////////
	// MOVE ANIMATION Ne Pas Supprimer SVP
	// Fonctionnalit� qu'on aura surement pas le temps d'impl�menter, mais j'aimerais garder ce code quand m�me,car l'annimation fonctionnais

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

					if (menubool == true || menuReglage == true)
					{
						if (mute == false)
						{
							musicMenu.stop();
							mute = true;
							reglageSon.setFillColor(Color::Green);
						}
						else
						{
							musicMenu.play();
							mute = false;
							reglageSon.setFillColor(Color::White);
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
				case Keyboard::F:

					if (fullscrmode == false)
					{
						window.create((VideoMode(1600, 900)), "Earthbound Fullscreen", sf::Style::Fullscreen);
						fullscrmode = true;
						fullscreen.setFillColor(Color::Green);

					}
					else
					{
						window.create((VideoMode(1600, 900)), "Earthbound Window", sf::Style::Default);
						fullscrmode = false;
						fullscreen.setFillColor(Color::White);
					}

					break;
				case Keyboard::I:
					if (lose == true)
						lose = false;
					win = true;
					break;
				case Keyboard::O:
					if (win == true)
						win = false;
					lose = true;
					break;
				default:
					dir = 0;
					break;
				}

				//std::cout << dir << std::endl;
			}
			else if (event.type == Event::KeyReleased)//Pour r�gler les diagonales qui continue m�me si on � Released une touche
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
				// � METTRE EN FONCTIOM SI ON A LE TEMPS
				// Doit d�terminer la valeur la plus importante pour choisir quelle sprite afficher pour le bonhomme
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
			else if (event.type == Event::MouseButtonPressed && menubool)
			{
				if (play.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
				{
					play.setFillColor(Color::Black);
				}
				else if (reglage.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
				{
					menubool = false;
					menuReglage = true;
				}
				else if (quit.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
				{
					exit(0);
				}

			}
			else if (event.type == Event::MouseButtonPressed && menuReglage == true)
			{
				if (reglageSon.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
				{
					if (mute == true)
					{
						reglageSon.setFillColor(Color::White);
						mute = false;
						musicMenu.play();
					}
					else
					{
						reglageSon.setFillColor(Color::Green);
						mute = true;
						musicMenu.stop();
					}
					
				}
				else if (difficulte.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
				{
					if (boost == 1)
					{
						boost = 1.5;
						difficulte.setFillColor(Color::Green);
					}
					else
					{
						boost = 1;
						difficulte.setFillColor(Color::White);
					}
				}
				else if (fullscreen.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
				{
					if (fullscrmode == false)
					{
						window.create((VideoMode(1600, 900)), "Earthbound Fullscreen", sf::Style::Fullscreen);
						fullscrmode = true;
						fullscreen.setFillColor(Color::Green);

					}
					else
					{
						window.create((VideoMode(1600, 900)), "Earthbound Window", sf::Style::Default);
						fullscrmode = false;
						fullscreen.setFillColor(Color::White);
					}
				}
				else if (retourMenu.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
				{
					menubool = true;
					menuReglage = false;
				}

			}
			else if (event.type == sf::Event::MouseMoved && menubool)
			{
				
				if (play.getGlobalBounds().contains(Vector2f(sf::Mouse::getPosition(window))))
				{
					play.setFillColor(Color::Red);
				}
				else
				{
					play.setFillColor(Color::White);
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
			else if (event.type == sf::Event::MouseMoved && menuReglage)
			{
				if (reglageSon.getGlobalBounds().contains(Vector2f(sf::Mouse::getPosition(window))))
				{
					reglageSon.setFillColor(Color::Red);
				}
				else
				{
					if (mute)
					{
						reglageSon.setFillColor(Color::Green);
					}
					else
					{
						reglageSon.setFillColor(Color::White);
					}
				}


				if (difficulte.getGlobalBounds().contains(Vector2f(sf::Mouse::getPosition(window))))
				{
					difficulte.setFillColor(Color::Red);
				}
				else
				{
					if (boost == 1)
					{
						difficulte.setFillColor(Color::White);
					}
					else
					{
						difficulte.setFillColor(Color::Green);
					}
					
				}

				if (fullscreen.getGlobalBounds().contains(Vector2f(sf::Mouse::getPosition(window))))
				{
					fullscreen.setFillColor(Color::Red);
				}
				else
				{
					if (fullscrmode == true)
					{
						fullscreen.setFillColor(Color::Green);
					}
					else
					{
						fullscreen.setFillColor(Color::White);
					}	
				}

				if (retourMenu.getGlobalBounds().contains(Vector2f(sf::Mouse::getPosition(window))))
				{
					retourMenu.setFillColor(Color::Red);
				}
				else
				{
					retourMenu.setFillColor(Color::White);
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
				window.draw(reglage);
				window.draw(quit);
				if (boost == 1.5)
				{
					window.draw(bonusActif);
				}
				window.display();
			}
		}
		else if (menuReglage)
		{
			window.clear();
			window.draw(fondEcranMenu);
			window.draw(reglageSon);
			window.draw(difficulte);
			window.draw(fullscreen);
			window.draw(retourMenu);
			if (boost == 1.5)
			{
				window.draw(bonusActif);
			}
			window.display();
		}
		else if (win == true)
		{
			window.setView(endGame);
			window.clear();
			window.draw(winBG);
			window.display();
			if (arrMusiquePlay[indiceLecteurMusique].getStatus() == sf::Music::Status::Playing)
			{
				arrMusiquePlay[indiceLecteurMusique].stop();
			}
			if (musicLose.getStatus() == sf::Music::Status::Playing)
			{
				musicLose.stop();
			}
			if (mute == false && musicWin.getStatus() == sf::Music::Status::Stopped)
			{
				musicWin.play();
			}
			else if (musicWin.getStatus() == sf::Music::Status::Playing && mute == true)
			{
				musicWin.stop();
			}
			

		}
		else if (lose == true)
		{
			window.setView(endGame);
			window.clear();
			window.draw(loseBG);
			window.display();
			if (arrMusiquePlay[indiceLecteurMusique].getStatus() == sf::Music::Status::Playing)
			{
				arrMusiquePlay[indiceLecteurMusique].stop();
			}
			if (musicWin.getStatus() == sf::Music::Status::Playing)
			{
				musicWin.stop();
			}
			if ( mute == false && musicLose.getStatus() == sf::Music::Status::Stopped)
			{
				musicLose.play();
			}
			else if (musicLose.getStatus() == sf::Music::Status::Playing && mute == true)
			{
				musicLose.stop();
			}


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
			actionJoueur.setSize(Vector2f(400, 180));
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
			retour.setPosition(Vector2f(500, 90 * _ness.getInventaire().size()));
		
			while (fight==true) {
				while (window.pollEvent(event)) {
					
					actionJoueur.setSize(Vector2f(400, 180));
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
							
							bool prev = false; 
							menu = 2;
							
							
							do {
								_ness.getInventaire().begin();
								actionJoueur.setSize(Vector2f(400, 90 * _ness.getInventaire().size()));
								window.draw(actionJoueur);
								for (int i = 0; i < _ness.getInventaire().size(); i++) {
									obj[i].setFont(font); //Set la police � utiliser (elle doit avoir �t� load�e)
									obj[i].setString("");		//Set le texte � afficher
									obj[i].setCharacterSize(40); 			//Set la taille (en pixels)
									obj[i].setFillColor(Color::White);			//Set la couleur du texte
									obj[i].setStyle(0);	//Set le style du texte
									obj[i].setString(_ness.getInventaire().value().getNom());		//Set le texte � afficher
									obj[i].setPosition(Vector2f(75, 50 + (90 * i)));
									window.draw(obj[i]);
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
								while (window.pollEvent(event)) {
									if (event.type == Event::MouseButtonPressed) {
										if (retour.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
											prev = true;
											menu = 0;
										}
										for (int i = 0; i < _ness.getInventaire().size(); i++) {
											if (obj[i].getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
												_ness.getInventaire().begin();
												for (int j = 0; j < i; j++) {
													_ness.getInventaire().next();
												}
												std::string effetObj = _ness.getInventaire().value().getStat();
												if (effetObj == "pp") {
													_ness.setPp(_ness.getPp() + _ness.getInventaire().value().getForce());
													ppJoueur.setString(std::to_string(_ness.getPp()));
													
												}
												else if (effetObj == "force") {
													_ness.setForce(_ness.getForce() + _ness.getInventaire().value().getForce());
													ppJoueur.setString(std::to_string(_ness.getPp()));
												}
												else if (effetObj == "def") {
													_ness.setDef(_ness.getDef() + _ness.getInventaire().value().getForce());
													ppJoueur.setString(std::to_string(_ness.getPp()));
												}
												else if (effetObj == "hp") {
													_ness.setHp(_ness.getHp() + _ness.getInventaire().value().getForce());
													hpJoueur.setString(std::to_string(_ness.getHp()));
												}
											}
										}
										
									}

								}
							} while (prev == false);
						
							
						}
						else if (fuite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y) || menu == 3) {
							int chanceFuite = rand() % (10 + 1 - 1) + 1;
							bool next = false;
							if (chanceFuite > 1 && chanceFuite < 5) {
								 do {
									window.draw(actionJoueur);
									resultSuite.setString("Vous avez r�ussi \n� vous enfuir!");
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
									resultSuite.setString("Vous n'avez pas \nr�ussi � vous enfuir!");
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
								resultSuite.setString("Vous avez r�ussi \n� vous enfuir!");
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
								resultSuite.setString("Vous n'avez pas \nr�ussi � vous enfuir!");
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
			window.draw(_monstre3.getShape());
			window.draw(_monstre4.getShape());
			window.draw(_monstre5.getShape());
			window.draw(_monstre6.getShape());
			window.draw(_monstre7.getShape());
			window.draw(_monstre8.getShape());
			window.draw(_monstre9.getShape());

			if (dir != 0)
			{
				if (!ifcollision(mapHitbox))
				{
					dernierePosition = _ness.getPosition();
					viewGame = _ness.move(dir, lastX, lastY, animationCpt, viewGame);
					viewGame.setCenter(_ness.getPosition());
				}
				else
				{
					_ness.setHitboxPosition(dernierePosition.x + 6, dernierePosition.y + 6);
					_ness.setPosition(dernierePosition.x, dernierePosition.y);
					viewGame.setCenter(dernierePosition.x, dernierePosition.y);

				}
			}


			int ligne = _ness.getHitboxPosition().y / 5;
			int col = _ness.getHitboxPosition().x / 5;
			int nbCellule = ((ligne + 3) * 343) + col + 1;
			window.draw(mapHitbox.at(nbCellule+1));
			window.draw(mapHitbox.at(nbCellule - 2));


			cpt1 = _monstre1.moveMonstre(cpt1);
			cpt2 = _monstre2.moveMonstre(cpt2);
			cpt3 = _monstre3.moveMonstre(cpt3);
			cpt4 = _monstre4.moveMonstre(cpt4);
			cpt5 = _monstre5.moveMonstre(cpt5);
			cpt6 = _monstre6.moveMonstre(cpt6);
			cpt7 = _monstre7.moveMonstre(cpt7);
			cpt8 = _monstre8.moveMonstre(cpt8);
			cpt9 = _monstre9.moveMonstre(cpt9);
			window.display();
		}

	}
}

bool Game::ifcollision(std::vector<RectangleShape> &Hitbox)
{
	int ligne = _ness.getHitboxPosition().y / 5;
	int col = _ness.getHitboxPosition().x / 5;
	int nbCellule = ((ligne + 3) * 343) + col + 1;


	return (Hitbox.at(nbCellule+1).getFillColor() == Color::Red || Hitbox.at(nbCellule - 2).getFillColor() == Color::Red);
}

const sf::RectangleShape Game::getBG() const
{
	return _fondEcranPlay;
}



