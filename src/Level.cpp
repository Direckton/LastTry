#include "Level.h"

Player::Player()
{
	texture.loadFromFile("res/player.png");
	
	sprite.setTexture(texture);
	//sprite.setOrigin(sf::Vector2f(30, 30));
	sprite.setPosition(sf::Vector2f(20.f, FLOOR-GRID +
	sprite.getOrigin().y));

	//sprite.setPosition(sprite.getPosition().x, -20);
	playerBounds.setPosition(sf::Vector2f(20.f, FLOOR - GRID +
		sprite.getOrigin().y));
	yAcceleration = 0.5f;
	yVelocity = 0;
}

void Player::draw(sf::RenderWindow& window)
{
	//update();
	window.draw(circle);
	window.draw(sprite);
}

void Player::jump()
{
	if (onGround == true)
	{
		onGround = false;
		yVelocity = -12;
	}
	if (onBlock == true)
	{
		onBlock = false;
		yVelocity = -12;
	}
}

void Player::setOnGround(int y)
{
	if (y == FLOOR)
	{
		onGround = true;
	}
	else
	{
		onBlock = true;
	}
	sprite.setPosition(sf::Vector2f(sprite.getPosition().x, y +
		sprite.getOrigin().y));
	yVelocity = 0;
}

bool Player::getOnGround()
{
	return onGround;
}

void Player::update()
{
	if (blownUp)
	{
		blowUp();
		return;
	}
	sprite.move(sf::Vector2f(4.f, 0.f));

	if (!onGround)
	{
		sprite.move(sf::Vector2f(0.f, yVelocity));
		if (yVelocity < 12)
		{
			yVelocity += 0.5;
		}
		if (sprite.getGlobalBounds().top + GRID  > FLOOR)
		{
			onGround = true;
			setOnGround(FLOOR-GRID);
		}
	}
	
	

}

bool Player::getAnimationEnded()
{
	return blownUp;
}

void Player::gravity()
{
	falling = true;
}

void Player::reset()
{
	onGround = true;
	yDelta = 0;
	InitalizeBlowUp();
	//if main is threaded this might break
	
}

sf::FloatRect Player::getBounds()
{
	return sprite.getGlobalBounds();
}

void Player::playerMove(float x, float y)
{
	sprite.move(x, y);
}

void Player::InitalizeBlowUp()
{
	sprite.setScale(sf::Vector2f(0, 0));
	circle.setFillColor(sf::Color::White);
	circle.setRadius(70.f);
	circle.setOrigin(GRID,GRID);
	circle.setScale(0.5,0.5);
	circle.setPosition(sf::Vector2f(sprite.getPosition().x,
		sprite.getPosition().y));

	blownUp = true;
	animationLenght = std::chrono::high_resolution_clock::now();
}

bool Player::blowUp()
{
	if (blownUp)
	{

		circle.setScale(circle.getScale().x + 0.05,
			circle.getScale().y + 0.05);
		if (circle.getFillColor().a - 5 > 0)
		{
			circle.setFillColor(sf::Color(circle.getFillColor().r,
				circle.getFillColor().g,
				circle.getFillColor().b,
				circle.getFillColor().a - 5));

		}
		else
		{
			circle.setFillColor(sf::Color::Transparent);
			blownUp = false;
			sprite.setPosition(sf::Vector2f(20.f, FLOOR - GRID +
				sprite.getOrigin().y));
			sprite.setRotation(0);
			sprite.setScale(sf::Vector2f(1, 1));
			return true;
		}
	}
	return false;
}

void Player::finishAnimation()
{
	if (animationAcc < 3)
	{
		animationAcc += 0.1f;
	}
	if (rotationAcc < 3)
	{
		rotationAcc += 0.1f;
	}
	sprite.move(animationAcc, -2);
	sprite.rotate(rotationAcc);
}

Block::Block(int _x, int _y, const sf::Color& color)
{
	x = _x * GRID;
	y = _y * GRID;


	block = sf::VertexArray(sf::Quads, 4);

	block[0].position = sf::Vector2f(x, FLOOR - y);
	block[1].position = sf::Vector2f(x, FLOOR - y - GRID);
	block[2].position = sf::Vector2f(x+GRID, FLOOR - y - GRID);
	block[3].position = sf::Vector2f(x+GRID, FLOOR - y);

	block[0].color = color;
	block[1].color = sf::Color::Black;
	block[2].color = sf::Color::Black;
	block[3].color = color;

	t.loadFromFile("res/glow.png");
	s.setTexture(t);
	s.setPosition(x-3, FLOOR - y - GRID-3);

}

void Block::draw(sf::RenderWindow& window)
{
	window.draw(block);
	window.draw(s);
	//window.draw(rectangle);
}

sf::FloatRect Block::getBounds()
{
	return block.getBounds();
}

Block::~Block()
{

}
Spike::Spike()
{
}

Spike::Spike(int _x, int _y ,sf::Color color)
{
	x = _x * GRID;
	y = _y * GRID;
	triangle = sf::VertexArray(sf::Triangles, 3);

	triangle[0].position = sf::Vector2f(x, FLOOR - y);
	triangle[1].position = sf::Vector2f(x+GRID/2, FLOOR - y - GRID);
	triangle[2].position = sf::Vector2f(x + GRID, FLOOR - y);

	triangle[0].color = color;
	triangle[1].color = sf::Color::Black;
	triangle[2].color = color;


	tx.loadFromFile("res/triangle_glow.png");

	sp.setTexture(tx);
	sp.setPosition(x - 3, FLOOR - y - GRID-2);
	
}

void Spike::draw(sf::RenderWindow& window)
{
	
	window.draw(triangle);
	window.draw(sp);
	//window.draw(tri);
}

sf::FloatRect Spike::getBounds()
{
	return triangle.getBounds();
}

Finish::Finish(int _x)
{
	x = _x * GRID;

	gradient = sf::VertexArray(sf::Quads, 4);

	gradient[0].position = sf::Vector2f(x-100, -1280);
	gradient[1].position = sf::Vector2f(x, -1280);
	gradient[2].position = sf::Vector2f(x, FLOOR);
	gradient[3].position = sf::Vector2f(x-100, FLOOR);

	gradient[0].color = sf::Color::Transparent;
	gradient[1].color = sf::Color::White;
	gradient[2].color = sf::Color::White;
	gradient[3].color = sf::Color::Transparent;

	

}

sf::FloatRect Finish::getBounds()
{
	return gradient.getBounds();
}

void Finish::draw(sf::RenderWindow &window)
{
	window.draw(gradient);
}

Level::Level(std::string name)
{
	levelName = name;
	floor.setSize(sf::Vector2f(1400, 3));
	floor.setFillColor(sf::Color::White);
	floor.setOutlineThickness(0);
	floor.setPosition(0, FLOOR);

	finish = Finish(35);

	loadLevel();

}

Level::~Level()
{
	for (auto b : blocks)
	{
		delete b;
	}
	blocks.clear();
	for (auto s : spikes)
	{
		delete s;
	}
	spikes.clear();
}

void Level::loadLevel()
{
	Fileloader file;
	//TODO change to dynamic level selection based on index
	if (levelName != "LEVEL2.json")
	{
		std::cout << "pizda";
	}
	json data = file.getJson("res/json/level/" + levelName);
	auto BlockCoordinates = file.getBlockCoordinates(data);
	auto rgb = file.getColor(data);
	sf::Color c(rgb[0],rgb[1],rgb[2]);
	auto SpikeCoordinates = file.getSpikeCoordinates(data);
	std::thread t1(&Level::loadBlocks,this, BlockCoordinates, c);
	std::thread t2(&Level::loadSpikes,this, SpikeCoordinates, c);
	t1.join();
	t2.join();

}

void Level::loadBlocks(std::vector<std::pair<int,int>> coordinates, sf::Color c)
{
	auto start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < coordinates.size(); i++)
	{
		blocks.push_back(new Block(coordinates[i].first, coordinates[i].second,
			c));
	}
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "Blocks done in: " << duration.count() << " ms" << std::endl;
}

void Level::loadSpikes(std::vector<std::pair<int, int>> coordinates, sf::Color c)
{
	auto start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < coordinates.size(); i++)
	{
		spikes.push_back(new Spike(coordinates[i].first, coordinates[i].second,
			c));
	}
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "Spikes done in: " << duration.count() << " ms" << std::endl;

}

void Level::draw(sf::RenderWindow& window)
{
	update();
	if (updateLevel)
	{
		player.update();

	}
	else
	{
		if(player.blowUp());
		{
		}
		
			//trigger LEVEL COMPLATE sequence
			if (!font.loadFromFile("OXYGENE1.ttf"))
			{
				std::cout << "Error while loading font!";
			}
			text.setFont(font);
			text.setFillColor(sf::Color::White);
			text.setCharacterSize(60);
			text.setString("LEVEL COMPLATE");
			text.setPosition(view.getCenter());
		
	}

	view = window.getDefaultView();
	

	if (updateLevel)
	{
		if (player.getBounds().left + GRID / 2 > view.getCenter().x)
		{
			levelView.x = player.getBounds().left + GRID / 2;
		}

		if (player.getBounds().top + GRID / 2 < 360)
		{
  			levelView.y = std::min(player.getBounds().top + GRID / 2,
					levelView.y);
		}
		if (player.getBounds().top + GRID / 2 > levelView.y + 250)
		{
			//sketchy af but ok
			levelView.y += 12;

		}
		if (player.getOnGround() && levelView.y != 360)
		{
			levelView.y++;
		}

		if (levelView != sf::Vector2f(-1, -1))
		{
			view.setCenter(levelView);

		}
		if (player.getBounds().left < view.getCenter().x)
		{
			levelView = sf::Vector2f(640, 360);
		}
		window.setView(view);

	}
	
	window.clear(sf::Color::Black);
	for (auto it = blocks.begin(); it!= blocks.end();it++)
	{
		(*it)->draw(window);
	}
	for (auto it = spikes.begin(); it != spikes.end(); it++)
	{
		(*it)->draw(window);
	}

	window.draw(text);
	window.draw(floor);
	player.draw(window);
	finish.draw(window);

}

void Level::update()
{
	if (finished()) {
		return;
	}

	//PLAYER EVENT QUEUEING
	if (eventQueue)
	{
		end = std::chrono::high_resolution_clock::now();
		if (start + elapsed > end)
		{
			player.jump();
		}
		else
		{
			eventQueue = false;
		}

	}

	//SCENE UPDATE
	floor.setPosition(sf::Vector2f(view.getCenter().x - floor.getSize().x / 2,
		FLOOR));
	
	
	//COLISSION DETECTION
	bool flag = false, prime = false; 
	

	for (auto it = blocks.begin(); it != blocks.end(); it++)
	{
		if (player.getBounds().intersects((*it)->getBounds()))
		{
			//i dont like how it's made but i have no ide how to change it
			//without changing all the objects
			if (!player.getOnGround() &&
				(*it)->getBounds().top > player.getBounds().top &&
				player.getBounds().top < (*it)->getBounds().top -
				GRID + 20)
			{
				player.setOnGround((*it)->getBounds().top - GRID);
			}
			else
			{
				player.reset();
			}
				
		}
		

		sf::FloatRect playerBounds = player.getBounds();
		playerBounds.top = player.getBounds().top + 1;
		if ((*it)->getBounds().intersects(playerBounds))
		{
			flag = false;

		} 
		else
		{
			flag = true;
		}

		

	}
	for (auto it = spikes.begin(); it != spikes.end(); it++)
	{
		if (player.getBounds().intersects((*it)->getBounds()))
		{
			player.reset();
		}
	}

	if (flag)
	{
		player.gravity();
	}
	//GRAVITY

}


bool Level::finished()
{
	if (player.getBounds().left > finish.getBounds().left - 4 * GRID)
	{
		updateLevel = false;
		
	}
	if (!updateLevel)
	{
		player.finishAnimation();
		
		if (player.getBounds().left + GRID > finish.getBounds().left +95 &&
			player.getBounds().left + GRID < finish.getBounds().left +100)
		{
			//player.reset();
			player.InitalizeBlowUp();
			//player.blowUp();
		}
		return true;
	}
	return false;
}

void Level::space()
{
	//event life
	//so when user pressed space right before the player landing 
	//the event of jumping will be called sepite player not being on ground
	// the next time onGround flag is insavtibe in 200ms window
	
	start = std::chrono::high_resolution_clock::now();
	eventQueue = true;
	player.jump();
	
}