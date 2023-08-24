#pragma once
#include <SFML/Graphics.hpp>
#include "InputHandler.h"
#include "FileLoader.h"
#include <math.h>
#include <chrono>
#include <thread>

#define GRID 60
#define FLOOR 600

class Player
{
	sf::Sprite sprite;
	sf::Texture texture;
	sf::CircleShape circle;
	int x, y;
	bool onGround = true;
	bool onBlock = true;
	bool blownUp = false;

	float pi = 3.14159265359f;
	float yDelta = 0;

	float yAcceleration, yVelocity;

	std::chrono::high_resolution_clock::time_point animationLenght;


public:
	sf::RectangleShape playerBounds;

	Player();
	bool falling = false;
	bool jumping = false;


	void draw(sf::RenderWindow& window);
	void jump();
	void update();
	sf::FloatRect getBounds();
	void reset();
	void setOnGround(int y);
	bool getOnGround();
	void playerMove(float x, float y);
	void gravity();
	//DEBUG
	void changeColor(sf::Color color) { sprite.setColor(color); }
	
	void blowUp();
};

class Block
{
	//sf::RectangleShape rectangle;
	sf::VertexArray block;
	sf::Sprite s;
	sf::Texture t;
	//60x60px
	int x, y;

public:
	Block(int x, int y, const sf::Color& color);
	~Block();
	void draw(sf::RenderWindow& window);
	sf::FloatRect getBounds();
};

class Spike
{
	int x, y;
	sf::Texture tx;
	sf::Sprite sp;

	sf::VertexArray triangle;
	sf::CircleShape tri;


public:
	Spike();
	Spike(int _x, int _y, sf::Color color);

	void draw(sf::RenderWindow& window);
	sf::FloatRect getBounds();
};

class Finish
{
	int x;

	sf::VertexArray gradient;

public:
	Finish() {};
	Finish(int _x);
	~Finish() {};

	void draw(sf::RenderWindow& window);
	sf::FloatRect getBounds();

};

class Level : public Input
{
	std::string levelName;
	std::vector<Block *> blocks;
	std::vector<Spike *> spikes;

	Player player;
	Finish finish;
	sf::RectangleShape floor;

	sf::FloatRect lastPosition;

	sf::View view;

	sf::Vector2f levelView{640,360};


	bool eventQueue = false;
	bool updateLevel = true;
	std::chrono::milliseconds elapsed = std::chrono::milliseconds(200);
	std::chrono::high_resolution_clock::time_point start;
	std::chrono::high_resolution_clock::time_point end;



public:
	Level() {};
	Level(std::string name);
	~Level();

	void loadLevel();
	void loadBlocks(std::vector<std::pair<int, int>> coordinates, sf::Color c);
	void loadSpikes(std::vector<std::pair<int, int>> coordinates, sf::Color c);
	void draw(sf::RenderWindow& window);
	void space();
	void update();
	void finished();
};

