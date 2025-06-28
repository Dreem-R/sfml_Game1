#pragma once

#include<iostream>
#include<vector>
#include <ctime>

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
	
	sf::Vector2i Mouse_Position;

	//Game Logic
	int points;
	float enemyspawntimer;
	float enemytimermax;
	int maxEnemies;


	//private funcation
	void initVariable();
	void initEnemy();
	void initWindow();

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
	void Update();

	void RenderEnemy();
	void Render();
};