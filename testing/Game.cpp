#include "Game.h"

using namespace std;
//Private Funcations
void Game::initVariable()
{
	this->window = nullptr;
	this->mouseheld = false;
	this->Gameover = false;
	this->points = 0;
	this->healthbar = 3;
	this->enemytimermax = 40.f;
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

void Game::initText()
{
	this->UItext.setFont(this->fonts);
	this->UItext.setCharacterSize(24);
	this->UItext.setFillColor(sf::Color::White);
	this->UItext.setString("Points: 0 \n Health: 3");
}

void Game::initFonts()
{
	this->fonts.loadFromFile("Fonts/BebasNeue-Regular.ttf");
}

Game::Game()
{
	this->initVariable();
	this->initEnemy();
	this->initWindow();
	this->initFonts();
	this->initText();
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
		0.f
		//static_cast<float>(rand() % static_cast<int>(this->window->getSize().y - this->enemy.getSize().y))
	);
	this->enemy.setFillColor(sf::Color::Green);

	this->enemies.push_back(this->enemy);
}

void Game::UpdateEnemy()
{
	/*
		Update Enemy:
			- Checking timer
			- Spawning Enemy
			-decresing/resetting timer
			- Updating Enemy:
				- Moving Enemy Downwards
				-Remove Enemy at Edge of screen
				-Remove Emeny after Mouse Click

			//TODO:
				-Add Score System
	*/
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
	//move enemy
	for (int i = 0; i < enemies.size(); i++)
	{
		this->enemies[i].move(0.f, 4.f);

		//Check If Box Out Of Screen
		if (this->enemies[i].getPosition().y > this->window->getSize().y) {
			this->enemies.erase(this->enemies.begin() + i);
			//Lose Points
			this->healthbar -= 1;
			std::cout << "HealthBar: " << this->healthbar << std::endl;
			if (healthbar<=0)
			{
				this->Gameover = true;
			}
		}
	}

	//Check If Mouse Clicked
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if (this->mouseheld == false)
		{
			this->mouseheld = true;
			bool Delete = false;
			//Delete Enemy on Mouse Click if its inside the Enemy Rectangle
			for (int i = 0; i < enemies.size() && !Delete; i++)
			{
				if (this->enemies[i].getGlobalBounds().contains(this->MousePosView)) {
					Delete = true;
					this->enemies.erase(this->enemies.begin() + i);
					//Gain Points
					this->points += 1;
					std::cout << "Points: " << this->points << std::endl;
				}
			}
		
		}
	}
	else
	{
		this->mouseheld = false;
	}
}

void Game::UpdateText()
{
	std::stringstream ss;
	ss << "Points: " << this->points << "\nHealth: " << this->healthbar;
	this->UItext.setString(ss.str());
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

	this->MousePosWindow = sf::Mouse::getPosition(*this->window);
	this->MousePosView = this->window->mapPixelToCoords(this->MousePosWindow);
}

void Game::Update()
{
	this->PollEvent();
	if (!this->Gameover)
	{
		this->UpdateMousePosition();
		this->UpdateEnemy();
		this->UpdateText();

	}
}

void Game::RenderEnemy()
{
	for (auto& e : this->enemies) {
		this->window->draw(e);
	}

}

void Game::RenderText()
{
	this->window->draw(this->UItext);
}

void Game::Render()
{
	this->window->clear(sf::Color::Black);
	
	//Draw Game Objects
	this->RenderEnemy();
	this->RenderText();

	this->window->display();
}
