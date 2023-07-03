#include "Level.h"

Player::Player()
{
	texture.loadFromFile("res/player.png");
	
	sprite.setTexture(texture);
	//sprite.setOrigin(sf::Vector2f(30, 30));
	sprite.setPosition(sf::Vector2f(20.f, FLOOR-GRID +
	sprite.getOrigin().y));

	playerBounds.setPosition(sf::Vector2f(20.f, FLOOR - GRID +
		sprite.getOrigin().y));
	yAcceleration = 0.5f;
	yVelocity = 0;
}

void Player::draw(sf::RenderWindow& window)
{
	update();
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

void Player::gravity()
{
	falling = true;
}

void Player::reset()
{
	onGround = true;
	yDelta = 0;
	sprite.setPosition(sf::Vector2f(20.f, FLOOR - GRID + 
		sprite.getOrigin().y));
	sprite.setRotation(0);

}

sf::FloatRect Player::getBounds()
{
	return sprite.getGlobalBounds();
}

void Player::playerMove(float x, float y)
{
	sprite.move(x, y);
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

Level::Level()
{

	floor.setSize(sf::Vector2f(1400, 3));
	floor.setFillColor(sf::Color::White);
	floor.setOutlineThickness(0);
	floor.setPosition(0, FLOOR);


	blocks.push_back(block1);
	blocks.push_back(block2);
	blocks.push_back(block3);
	blocks.push_back(block4);

	spikes.push_back(spike1);
}

Level::~Level()
{

}

void Level::draw(sf::RenderWindow& window)
{
	update();
	view = window.getDefaultView();
	
	if (player.getBounds().left + GRID / 2 > view.getCenter().x)
	{
		view.setCenter(sf::Vector2f(player.getBounds().left + GRID / 2,
			720/2));
	}

	window.setView(view);
	
	window.clear(sf::Color::Black);
	for (auto block : blocks)
	{
		block.draw(window);
	}
	for (auto spike : spikes)
	{
		spike.draw(window);
	}
	player.draw(window);
	window.draw(floor);

	
}

void Level::update()
{
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
	

	for (auto block : blocks)
	{
		if (player.getBounds().intersects(block.getBounds()))
		{
			//i dont like how it's made but i have no ide how to change it
			//without changing all the objects
			if (!player.getOnGround() &&
				block.getBounds().top > player.getBounds().top &&
				player.getBounds().top < block.getBounds().top -
				GRID + 20)
			{
				player.setOnGround(block.getBounds().top - GRID);
			}
			else
			{
				player.reset();
			}
				
		}
		

		sf::FloatRect playerBounds = player.getBounds();
		playerBounds.top = player.getBounds().top + 1;
		if (block.getBounds().intersects(playerBounds))
		{
			flag = false;

		} 
		else
		{
			flag = true;
		}

		

	}
	for (auto spike : spikes)
	{
		if (player.getBounds().intersects(spike.getBounds()))
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