#pragma once
#include <SFML/Graphics.hpp>
#include "InputHandler.h"
#include "FileLoader.h"
#include "Music.h"
#include <math.h>
#include <chrono>
#include <thread>
#include <atomic>
#include <vector>
#include <ranges>
#include <barrier>


#define GRID 60
#define FLOOR 600
/**Class implmenting player and his logic */
class Player
{
	sf::Sprite sprite;
	sf::Texture texture;
	sf::CircleShape circle;
	int x, y;
	bool onGround = true;
	bool onBlock = true;
	bool blownUp = false;
	bool falling = false;

	float pi = 3.14159265359f;
	float yDelta = 0;

	float yAcceleration, yVelocity;
	float animationAcc = 0, rotationAcc =0;

	std::chrono::high_resolution_clock::time_point animationLenght;


public:
	Player();

	void draw(sf::RenderWindow& window);
	/**Switches flags for jumping based on conditions, flags are processed in update()*/
	void jump();
	/**Switches flags for jumping based on conditions, flags are processed in update()*/
	void boost();
	/**Switches flags for double jumps based on conditions, flags are processed in update()*/
	void doubleJump();
	/**Handling all the flags and movements of the player*/
	void update();
	/**Returns bounding box of player*/
	sf::FloatRect getBounds();
	/**Resets player after colision*/
	void reset();
	/**Sets flags, restes position to a block or a floor specified by y variable*/
	void setOnGround(int y);
	/**Returns flag*/
	bool getOnGround();
	/**Sets flag whan player should fall down*/
	void gravity();
	/**Setup blowing up animation and flags*/
	void InitalizeBlowUp();
	/**Blowing up animation updater after colision*/
	bool blowUp();
	/**Self explanotary*/
	bool getAnimationEnded();
	/**Animation after crossing the finish line*/
	void finishAnimation();
};

/**Block object*/
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
	/**Draws single block on the screen*/
	void draw(sf::RenderWindow& window);
	/**Returns bounding box of a block*/
	sf::FloatRect getBounds();
};

/**Spike object*/
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
	/**Draws single spike on the screen*/
	void draw(sf::RenderWindow& window);
	/**Returns bounding box of a spike*/
	sf::FloatRect getBounds();
};

/**Finish line object*/
class Finish
{
	int x;

	sf::VertexArray gradient;

public:
	Finish() {};
	Finish(int _x);
	~Finish() {};

	float getFinishPosition();
	/**Draws finish line on the screen*/
	void draw(sf::RenderWindow& window);
	/**Returns bounding box of a finish line*/
	sf::FloatRect getBounds();
};

class Particle
{
private:
	int x, y;
	float velocity;
	sf::Vector2f direction;
	sf::RectangleShape particle;
public:
	Particle() {};
	Particle(int size, int lifespan, float velocity, sf::Vector2f direction);
	~Particle();

	void update();
	void draw(sf::RenderWindow &window);
};

/**Booster object*/
class Booster
{
	int x, y;
	sf::Sprite sprite;
	sf::Texture texture;

	std::vector<Particle> particles;


public:
	Booster() {};
	Booster(int _x, int _y);
	~Booster();
	/**Draws single booster on the screen*/
	void draw(sf::RenderWindow& window);
	/**Returns bounding box of a booster*/
	sf::FloatRect getBounds();


};

/**Double jump object*/
class Double
{
	int x, y;
	sf::Sprite sprite;
	sf::Texture texture;

	std::vector<Particle> particles;


public:
	Double() {};
	Double(int _x, int _y);
	~Double();
	/**Draws single double jump element on the screen*/
	void draw(sf::RenderWindow& window);
	/**Returns bounding box of a double jump*/
	sf::FloatRect getBounds();


};

/**Class implementing level logic, grapical interface and colision detection*/
class Level : public Input
{
	std::string levelName;
	std::vector<Block *> blocks;
	std::vector<Spike *> spikes;

	std::vector<Particle> particles;

	Player player;
	Finish finish;

	std::vector<std::unique_ptr<Booster>> boosters;
	std::vector<std::unique_ptr<Double>> doubles;
	sf::RectangleShape floor;
	sf::Texture texture;
	sf::Texture secondarytx;
	sf::Sprite background;
	sf::Sprite background2;
	sf::Sprite secondaryBg;
	sf::Sprite secondaryBg2;

	sf::FloatRect lastPosition;

	sf::View view;

	sf::Vector2f levelView{640,360};

	sf::Font* font = new sf::Font;
	sf::Text text, leave, highscore;

	SoundControler *sound = new SoundControler;


	bool eventQueue = false;
	bool updateLevel = true;
	bool levelReset = false;

	bool flag = false, prime = false;

	int score = 0;
	

	int textAnimation = 1;
	std::chrono::milliseconds elapsed = std::chrono::milliseconds(200);
	std::chrono::high_resolution_clock::time_point start;
	std::chrono::high_resolution_clock::time_point end;
	std::chrono::high_resolution_clock::time_point animation;



public:
	Level() {};
	Level(std::string name);
	~Level();

	/**Loads level data from json, crates blocks, spikes etc., test colors, plays music*/
	void loadLevel();
	/**Creates objects from coordinates, asigns colors*/
	void loadBlocks(std::vector<std::pair<int, int>> coordinates, sf::Color c);
	/**Creates objects from coordinates, asigns colors*/
	void loadSpikes(std::vector<std::pair<int, int>> coordinates, sf::Color c);
	/**Creates objects from coordinates*/
	void loadBoosters(std::vector<std::pair<int, int>> coordinates);
	/**Creates objects from coordinates*/
	void loadDoubles(std::vector<std::pair<int, int>> coordinates);
	/**Calls for update, then dynamically darws all the elements by calling their methods
	Updates view as well*/
	void draw(sf::RenderWindow& window);
	/**Sets event queue and calls jump() methode from Player class*/
	void space();
	/**Method updating everyting in the scene, handling flags, event queues,
	calling colision detection and moving textures*/
	void update();
	/**Checks if player has crossed the finish line, returns true if he has*/
	bool finished();
	/**Sets flag, restarts soundtack*/
	void reset();
	/**If player highscore was grater than the best one, saves it into JSON file*/
	void saveScore();
	/**Detects colision with blocks in range, blocks impossible to hit are not being checked*/
	void blockColision();
	/**Detects colision with spikes in range, spikes impossible to hit are not being checked*/
	void spikeColision();
	/**Draws blocks*/
	void drawBlocks(sf::RenderWindow& window);
	/**Draws spikes*/
	void drawSpikes(sf::RenderWindow& window);
};

