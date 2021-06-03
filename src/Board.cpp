#include "Board.h"
//-----------------------------------------------------------------------------
Board::Board() : m_beginLine(0), m_upToLine(0), m_levelTime(sf::Time::Zero),
m_vaccines(0), m_showTime(), m_gameOver(false)
{
	m_font.loadFromFile("C:/Windows/Fonts/SHOWG.TTF");
	m_showTime.setFillColor(sf::Color::Red);
	m_showTime.setFont(m_font);
	initializeLevel();
};
//-----------------------------------------------------------------------------
Board::~Board() = default;
//-----------------------------------------------------------------------------
void Board::initializeLevel()
{
	auto file = std::ifstream("Board.txt");
	int rows = 0, cols = 0;
	float time = 0.f;
	if (LevelUp())
	{
		auto points = 0;
		auto lives = 3;
		auto level = 1;
		if (m_objects.size() == OBJECTS && m_objects[objectIndex(objectsType::player)].size() != 0)
		{
			points = static_cast<Player&>(**m_objects[objectIndex(objectsType::player)].data()).getPoints();
			lives = static_cast<Player&>(**m_objects[objectIndex(objectsType::player)].data()).getLives();
			level = static_cast<Player&>(**m_objects[objectIndex(objectsType::player)].data()).getLevel() + 1;//level up
			points += 50 * level;
		}
		m_objects.clear();
		m_diggedWalls.clear();
		m_diggedTimers.clear();
		m_objects = objectsArr(OBJECTS);//ideal
		
		m_beginLine = m_upToLine;
		file.seekg(m_beginLine);
		file.peek();
		if (file.eof())
			m_gameOver = true;
		else
		{
			file >> rows >> cols;
			file >> time;
		}
		m_levelTime = sf::Time((sf::seconds(time)));
		m_integratedTime = (time != -1.f);
		

		m_objects[0].push_back(createObject(objectsType::baseObjects, Location((float)cols, (float)rows)));
		file.get();//get rid of '\n'
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				char object;
				object = file.get();
				if(object == (char)objectsType::player)
					m_objects[objectIndex(objectsType::player)]
					.push_back(createObject(Location((float)j, (float)i) * STATIC_SPRITE_SIZE,
						lives, points, level));
				else if (object != ' ')
					m_objects[objectIndex(objectsType(object))]
					.push_back(createObject(objectsType(object),
						Location((float)j, (float)i) * STATIC_SPRITE_SIZE));
			}
			file.get();//get rid of '\n'
		}
		if (m_vaccines == 0)
			m_vaccines = -1;
	}
	else
	{
		m_vaccines = 0;
		m_objects[objectIndex(objectsType::presents)].clear();
		m_objects[objectIndex(objectsType::vaccine)].clear();
		m_objects[objectIndex(objectsType::enemy)].clear();
		file.seekg(m_beginLine);
		file >> rows >> cols;
		file >> time;
		m_levelTime = sf::Time((sf::seconds(time)));
		file.get();
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				char object;
				object = file.get();
				if (object == (char)objectsType::presents
					|| object == (char)objectsType::vaccine || object == (char)objectsType::enemy)
					m_objects[objectIndex(objectsType(object))]
					.push_back(createObject(objectsType(object),
						Location((float)j, (float)i) * STATIC_SPRITE_SIZE));
			}
			file.get();//get rid of '\n'
		}
	}
	m_upToLine = file.tellg();
	file.close();
}
//-----------------------------------------------------------------------------
float Board::getBoardHeight() const
{
	return (m_objects[objectIndex(objectsType::baseObjects)].size() > 0) ?
		static_cast<BaseObjects&>(**m_objects[objectIndex(objectsType::baseObjects)].data()).getHeight()
		: 0.f;
}
//-----------------------------------------------------------------------------
float Board::getBoardWidth() const
{
	return (m_objects[objectIndex(objectsType::baseObjects)].size() > 0) ?
		static_cast<BaseObjects&>(**m_objects[objectIndex(objectsType::baseObjects)].data()).getWidth()
		: 0.f;
}
//-----------------------------------------------------------------------------
int Board::objectIndex(objectsType type) const
{
	int index;
	switch (type)
	{
	case objectsType::wall:
		index = 1;
		break;
	case objectsType::vaccine: case objectsType::presents:
		index = 2;
		break;
	case objectsType::player:
		index = 3;
		break;
	case objectsType::enemy:
		index = 4;
		break;
	default:
		index = 0;
		break;
	};
	return index;
}
//-----------------------------------------------------------------------------
int Board::textureIndex(objectsType type) const
{
	int index;
	switch (type)
	{
	case objectsType::baseObjects:
		index = 0;
		break;
	case objectsType::ladder:
		index = 1;
		break;
	case objectsType::wall:
		index = 2;
		break;
	case objectsType::rope:
		index = 3;
		break;
	case objectsType::vaccine:
		index = 4;
		break;
	case objectsType::player:
		index = 5;
		break;
	case objectsType::presents:
		index = 6;
		break;
	default:
		index = 0;
		break;
	}
	return index;
}
//-----------------------------------------------------------------------------
int Board::textureIndex(enemiesType type) const
{
	int index;
	switch (type)
	{
	case enemiesType::leftrightEnemy:
		index = 7;
		break;
	case enemiesType::randomEnemy:
		index = 8;
		break;
	case enemiesType::smartEnemy:
		index = 9;
		break;
	default:
		index = 0;
	}
	return index;
}
//-----------------------------------------------------------------------------
int Board::textureIndex(presentsType type) const
{
	return textureIndex(objectsType::presents);
}
//-----------------------------------------------------------------------------
std::unique_ptr<GameObjects> Board::createObject(objectsType type, Location location)
{
	switch (type)
	{
	case objectsType::baseObjects:
		return std::make_unique<BaseObjects>(getTexture(textureIndex(type)), location);
	case objectsType::ladder:
		return std::make_unique<Ladder>(getTexture(textureIndex(type)), location);
	case objectsType::wall:
		return std::make_unique<Wall>(getTexture(textureIndex(type)), location);
	case objectsType::vaccine:
	{
	m_vaccines++;
	return std::make_unique<Vaccine>(getTexture(textureIndex(type)), location);
	}
	case objectsType::presents:
		return createRandomObjects(type, m_integratedTime ? PRESENTS_TYPE : PRESENTS_TYPE - 1, location);
	case objectsType::enemy:
		return createRandomObjects(type, ENEMIES_TYPE, Location(location.x + (STATIC_SPRITE_SIZE - DYNAMIC_SPRITE_SIZE) / 2,
			location.y + (STATIC_SPRITE_SIZE - DYNAMIC_SPRITE_SIZE)));
	case objectsType::rope:
		return std::make_unique<Rope>(getTexture(textureIndex(type)), location);
	case objectsType::player:
		return std::make_unique<Player>(getTexture(textureIndex(type)), Location(location.x + (STATIC_SPRITE_SIZE - DYNAMIC_SPRITE_SIZE) / 2,
			location.y + (STATIC_SPRITE_SIZE - DYNAMIC_SPRITE_SIZE)));
	default:
		return nullptr;
	}
}
//-----------------------------------------------------------------------------
std::unique_ptr<GameObjects> Board::createObject(Location location, int lives, int points, int level)
{
	return std::make_unique<Player>(getTexture(textureIndex(objectsType::player)), Location(location.x + (STATIC_SPRITE_SIZE - DYNAMIC_SPRITE_SIZE)/2,
		location.y + (STATIC_SPRITE_SIZE - DYNAMIC_SPRITE_SIZE)), lives, points, level);
}
//-----------------------------------------------------------------------------
std::unique_ptr<GameObjects> Board::createObject(enemiesType type, Location location)
{
	switch (type)
	{
	case enemiesType::smartEnemy:
		return std::make_unique<SmartEnemy>(getTexture(textureIndex(type)), location);
	case enemiesType::leftrightEnemy:
		return std::make_unique<LeftRightEnemy>(getTexture(textureIndex(type)), location);
	case enemiesType::randomEnemy:
		return std::make_unique<RandomEnemy>(getTexture(textureIndex(type)), location);
	default:
		return nullptr;
	}
}
//-----------------------------------------------------------------------------
std::unique_ptr<GameObjects> Board::createObject(presentsType type, Location location)
{
	switch (type)
	{
	case presentsType::lockdown:
		return std::make_unique<Lockdown>(getTexture(textureIndex(type)), location);
	case presentsType::mutation:
		return std::make_unique<Mutation>(getTexture(textureIndex(type)), location);
	case presentsType::socialDistance:
		return std::make_unique<SocialDistance>(getTexture(textureIndex(type)), location);
	default:
		return nullptr;
	}
}
//-----------------------------------------------------------------------------
std::unique_ptr<GameObjects> Board::createRandomObjects(objectsType type, int objectsNumbers, Location location)
{
	switch (type)
	{
	case objectsType::enemy:
		return createObject((enemiesType)(rand() % objectsNumbers), location);
	case objectsType::presents:
		return createObject((presentsType)(rand() % objectsNumbers), location);
	default:
		return nullptr;
	}
}
//-----------------------------------------------------------------------------
sf::Texture const& Board::getTexture(int index) const
{
	return Textures::instance().getBoardTexture(index);
}
//-----------------------------------------------------------------------------
bool Board::LevelUp() const
{
	return m_vaccines == 0;
}
//-----------------------------------------------------------------------------
void Board::draw_objects(sf::RenderWindow& window)
{
	clearUsedPresents();
	if (isPlayerDead() || LevelUp() || timesUp())
		initializeLevel();
	window.clear();
	for (int i = 0; i < m_objects.size(); i++)
		for (int j = 0; j < m_objects[i].size(); j++)
			m_objects[i][j]->draw(window);
	if (m_integratedTime)
	{
		m_showTime.setPosition(window.getView().getCenter().x - window.getSize().x / 2 + 700.f,
			window.getView().getCenter().y + window.getSize().y / 2.f - 40.f);
		window.draw(m_showTime);
	}
	window.display();
}
//-----------------------------------------------------------------------------
void Board::moveObject(objectsType type, sf::Time DeltaTime, const std::optional<sf::Keyboard::Key>& key)
{

	for (int i = 0; i < m_objects[objectIndex(type)].size(); i++)
	{
		static_cast<MovingObjects&> (*m_objects[objectIndex(type)][i]).move(DeltaTime, *this, *key);
		handleCollisions(*m_objects[objectIndex(type)][i]);
	}
	if (type == objectsType::enemy)
		if (m_integratedTime)
		{
			m_levelTime = m_levelTime - DeltaTime;
			SetTimeString();
		}
		for (int i = 0; i < m_diggedTimers.size(); i++)
		{
			m_diggedTimers[i] -= DeltaTime;
			if (m_diggedTimers[i] <= sf::Time(sf::seconds(0.f)))
				returnDiggedFloor(i);
		}
}
//-----------------------------------------------------------------------------
void Board::clearUsedPresents()
{
	m_objects[objectIndex(objectsType::presents)].erase
	(std::remove_if(m_objects[objectIndex(objectsType::presents)].begin(), //remove used presents
		m_objects[objectIndex(objectsType::presents)].end(), [&](const auto& item) 
		{
			if (static_cast<Presents&>(*item).isTaken())
				openUsedPresents(*item);
			return static_cast<Presents&>(*item).isTaken();
		}), m_objects[objectIndex(objectsType::presents)].end());
}
//-----------------------------------------------------------------------------
void Board::openUsedPresents(const GameObjects& object)
{
	if (typeid(Lockdown) == typeid(object))
		setLockDown();
	else if (typeid(Mutation) == typeid(object))
		enterMutation();
	else if (typeid(Vaccine) == typeid(object))
		m_vaccines--;

}

void Board::setLockDown()
{
	m_levelTime += sf::Time(sf::seconds(30));
}

void Board::enterMutation()
{
	m_objects[objectIndex(objectsType::enemy)].push_back(createObject(objectsType::enemy, Location(STATIC_SPRITE_SIZE - DYNAMIC_SPRITE_SIZE, getBoardHeight() - STATIC_SPRITE_SIZE)));
}

void Board::handleCollisions(GameObjects& gameObject)
{
	for (int i = 0; i < m_objects.size(); i++)
		for (int j = 0; j < m_objects[i].size(); j++)
			if (gameObject == *m_objects[i][j])
				gameObject.handleCollision(*m_objects[i][j]);	
}

bool Board::isObject(const MovingObjects &object, objectsType type) const
{
		for (int i = 0; i < m_objects[objectIndex(type)].size(); i++)
			switch (type)
			{
				case objectsType::ladder:
				{
					if (typeid(Ladder) == typeid(*m_objects[objectIndex(type)][i]) &&
						object == *m_objects[objectIndex(type)][i])
						return true;
					break;
				}
				case objectsType::wall:
				{
					if (typeid(Wall) == typeid(*m_objects[objectIndex(type)][i]) &&
						object == *m_objects[objectIndex(type)][i])
						return true;
					break;
				}
				case objectsType::rope:
				{
					if (typeid(Rope) == typeid(*m_objects[objectIndex(type)][i]) &&
						object == *m_objects[objectIndex(type)][i])
						return true;
					break;
				}
				case objectsType::player:
				{
					if (typeid(Player) == typeid(*m_objects[objectIndex(type)][i]) &&
						object == *m_objects[objectIndex(type)][i])
						return true;
					break;
				}
			}
		return false;
}

bool Board::isInBoundries(const MovingObjects& object) const
{
	return static_cast<BaseObjects&>(**m_objects[objectIndex(objectsType::baseObjects)].data()).inBounderies(object);
}

Location Board::getPlayerLocation() const
{
	for (int i = 0; i < m_objects[objectIndex(objectsType::player)].size(); i++)
		return m_objects[objectIndex(objectsType::player)][i]->getSpriteLocation();
	return Location(-1, -1);
}

bool Board::isPlayerDead() const
{
		if (m_objects[objectIndex(objectsType::player)].size() > 0 && 
			static_cast<Player&>(**m_objects[objectIndex(objectsType::player)].data()).isDead())
		{
			static_cast<Player&>(**m_objects[objectIndex(objectsType::player)].data()).reborn();
			return true;
		}
	return false;
}

void Board::SetTimeString()
{
	auto seconds = std::string(((int)m_levelTime.asSeconds() % 60 < 10) ? ("0" + std::to_string((int)m_levelTime.asSeconds() % 60)) 
		: std::to_string((int)m_levelTime.asSeconds() % 60));
	m_showTime.setString("time:0" + std::to_string((int)m_levelTime.asSeconds() / 60)
 + ':' + seconds);
}

bool Board::timesUp()
{
	if((m_integratedTime && m_levelTime.asSeconds() < 0 && m_objects[objectIndex(objectsType::player)].size() > 0))
	{
		static_cast<Player&>(**m_objects[objectIndex(objectsType::player)].data()).lessLives();
		return true;
	}
	return false;
}

void Board::digOnFloor(const MovingObjects& object)
{
	if (m_diggedWalls.size() < DIGGEDNUMBER)
		for (int i = 0; i < m_objects[objectIndex(objectsType::wall)].size(); i++)
			if (object == *m_objects[objectIndex(objectsType::wall)][i])
			{
				m_diggedWalls.push_back(std::move(m_objects[objectIndex(objectsType::wall)][i]));
				m_objects[objectIndex(objectsType::wall)].erase(m_objects[objectIndex(objectsType::wall)].begin() + i);
				m_diggedTimers.push_back(sf::Time(sf::seconds((float)FLOORTIME)));
				break;
			}
}

void Board::returnDiggedFloor(int index)
{
	for (int i = objectIndex(objectsType::player); i < m_objects.size(); i++)
		for (int j = 0; j < m_objects[i].size(); j++)
			if (*m_objects[i][j] == *m_diggedWalls[index])
				static_cast<MovingObjects&>(*m_objects[i][j]).MoveAboveWall();

	m_objects[objectIndex(objectsType::wall)].push_back(std::move(m_diggedWalls[index]));
	m_diggedWalls.erase(m_diggedWalls.begin() + index);
	m_diggedTimers.erase(m_diggedTimers.begin() + index);

}

bool Board::gameOver() const
{
	auto result = false;
	if (m_gameOver)
		result =  true;
	else
		for (int i = 0; i < m_objects[objectIndex(objectsType::player)].size(); i++)
			if (static_cast<Player&>(*m_objects[objectIndex(objectsType::player)][i]).getLives() == 0)
				result = true;
	return result;
}