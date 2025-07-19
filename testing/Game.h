#pragma once

#include<iostream>
#include<vector>
#include <ctime>
#include<sstream>

#include<SFML/Network.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

/*
	Game Engine Class
	Wrapper Class
*/
class Game
{
private:
	//Varible

	sf::RenderWindow* window;
	sf::VideoMode videomode;
	sf::Event ev;


	std::vector<sf::RectangleShape> enemies;
	sf::RectangleShape enemy;
	
	//Resources
	sf::Font fonts;

	//Text
	sf::Text UItext;

	//Mouse Position
	sf::Vector2i MousePosWindow;
	sf::Vector2f MousePosView;

	//Game Logic
	bool Gameover;
	unsigned points;
	int healthbar;
	float enemyspawntimer;
	float enemytimermax;
	int maxEnemies;
	bool mouseheld;

	//private funcation
	void initVariable();
	void initEnemy();
	void initWindow();
	void initText();
	void initFonts();

//Contructor /Destructor
public:
	Game();
	virtual ~Game();

	//Accessors
	const bool running() const;

	//Functions
	void SpawnEnemy();

	void PollEvent();
	void UpdateMousePosition();
	void UpdateEnemy();
	void UpdateText();
	void Update();

	void RenderEnemy();
	void RenderText();
	void Render();
};