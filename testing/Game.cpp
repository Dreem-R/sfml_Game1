#include "Game.h"

using namespace std;
//Private Funcations
void Game::initVariable()
{
	this->window = nullptr;

	this->points = 0;
	this->enemytimermax = 1000.f;
	this->enemyspawntimer = this->enemytimermax;
	this->maxEnemies = 5;
}

void Game::initEnemy()
{
	this->enemy.setPosition(10,10);
	this->enemy.setSize(sf::Vector2f(100.f, 100.f));
	this->enemy.setScale(sf::Vector2(0.5f, 0.5f));
	this->enemy.setFillColor(sf::Color::Red);
	this->enemy.setOutlineColor(sf::Color::Yellow);
	this->enemy.setOutlineThickness(1.f);

}


//Public Function
void Game::initWindow()
{
	this->videomode.height = 600;
	this->videomode.width = 800;
	this->window = new sf::RenderWindow(this->videomode, "First Game", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);
}

Game::Game()
{
	this->initVariable();
	this->initEnemy();
	this->initWindow();
}

Game::~Game()
{
	delete this->window;
}

//Accessors
const bool Game::running() const
{
	return this->window->isOpen();
}

//Functions

void Game::SpawnEnemy()
{
	/*
		Spawn Enemy
		- Random Position
	*/
	this->enemy.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().y - this->enemy.getSize().y))
	);
	this->enemy.setFillColor(sf::Color::Green);

	this->enemies.push_back(this->enemy);
}

void Game::UpdateEnemy()
{
	if (enemies.size() < this->maxEnemies) {
		if (this->enemyspawntimer >= this->enemytimermax)
		{
			this->SpawnEnemy();
			this->enemyspawntimer = 0.f;
		}
		else {
			this->enemyspawntimer += 1.f;
		}
	}
}

void Game::PollEvent()
{
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape) {
				this->window->close();
			}
			break;
		}
	}
}

void Game::UpdateMousePosition()
{
	/*
		@return Void
		This Funcation Stores the Mouse Position
		Relative to the Game Window in the Mouse_Position (Varible)
		which is sf::vector2i
	*/

	this->Mouse_Position = sf::Mouse::getPosition(*this->window);
}

void Game::Update()
{
	this->PollEvent();
	this->UpdateMousePosition();
	
	this->UpdateEnemy();
}

void Game::RenderEnemy()
{
	this->window->draw(enemy);

}

void Game::Render()
{
	this->window->clear(sf::Color::Black);
	
	//Draw Game Objects
	this->RenderEnemy();
	
	this->window->display();
}
