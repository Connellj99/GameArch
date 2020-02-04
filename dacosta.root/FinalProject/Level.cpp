#include <iostream>
#include <map>
#include <ctime>
#include <vector>
#include <string>

#include "Trackable.h"

#include "UnitTypes.h"

#include "BufferFlags.h"
#include "FontFlags.h"

#include "Color.h"
#include "Font.h"
#include "GraphicsBuffer.h"
#include "Sprite.h"
#include "GraphicsSystem.h"

#include "Level.h"



Level::Level()
{
	//mpLayout = new int[];
}

Level::Level(std::vector<int> _layout, int _rows, int _columns, int _cellWidth, int _cellHeight, int _playerStartLength, int _playerX, int _playerY, double _playerSpeed, int _playerEndLength, int _foodPoints, int _powerUpFrequency)
{
	for (int row = 0; row < _rows; row++)
	{
		// Loop through all the rows and columns to find each wall location.
		for (int column = 0; column < _columns; column++)
		{
			// Wall location found.
			if (_layout[row * _columns + column] == 1)
			{
				// Add the column location.
				mmWallLocations.insert(std::pair<int, int>(column, row));
			}
			else if (_layout[row * _columns + column] == 2)
			{
				mmCollectableLocations.insert(std::pair<int, int>(column, row));
			}
			else if (_layout[row * _columns + column] == 3)
			{
				mmPowerUpLocations.insert(std::pair<int, int>(column, row));
			}
			// Empty location.
			else if (_layout[row * _columns + column] == 0)
			{
				mmEmptyLocations.insert(std::pair<int, int>(column, row));
			}
		}
	}

	mCellWidth = _cellWidth;
	mCellHeight = _cellHeight;
	mRows = _rows;
	mColumns = _columns;
	mPlayerStartLength = _playerStartLength;
	mPlayerStartX = _playerX;
	mPlayerStartY = _playerY;
	mPlayerSpeed = _playerSpeed;
	mPlayerEndLength = _playerEndLength;
	mFoodPoints = _foodPoints;
	mPowerUpFrequency = _powerUpFrequency;

	return;
}


Level::~Level()
{
	return;
}

std::multimap<int, int> Level::getWallLocations()
{
	return mmWallLocations;
}

std::multimap<int, int> Level::getCollectableLocations()
{
	return mmCollectableLocations;
}

std::multimap<int, int> Level::getPowerUpLocations()
{
	return mmPowerUpLocations;
}

// Check for collisions at the given grid coordinates.
bool Level::checkCollision(int _coordinateX, int _coordinateY)
{
	// Make sure there are walls.
	if (!mmWallLocations.empty())
	{
		// Create iterator to look for multiple instances of a key.
		typedef std::multimap<int, int>::iterator MMapIterator;

		// Find all instances of the key.
		std::pair<MMapIterator, MMapIterator> result = mmWallLocations.equal_range(_coordinateX);

		// Loop through all found instances of the key.
		for (MMapIterator iterator = result.first; iterator != result.second; iterator++)
		{
			// Collision.
			if (iterator->second == _coordinateY)
			{
				return true;
			}
		}
	}

	// No collision.
	return false;
}

void Level::addPlayerLocation(int _coordinateX, int _coordinateY)
{	
	bool addPlayer = false;
	bool addPlayerOverlap = false;
	
	div_t cellX = div(_coordinateX, mCellWidth);
	div_t cellY = div(_coordinateY, mCellHeight);

	int x = cellX.quot;
	int y = cellY.quot;
	int overlapX = cellX.rem;
	int overlapY = cellY.rem;

	typedef std::multimap<int, int>::iterator MMapIterator;

	std::vector<MMapIterator> removeEmpty;

	// Make sure there are player segments.
	if (!mmEmptyLocations.empty())
	{
		std::pair<MMapIterator, MMapIterator> result = mmEmptyLocations.equal_range(x);
		
		// Loop through all found instances of the key.
		for (MMapIterator iterator = result.first; iterator != result.second; iterator++)
		{
			// Player exists at the location.
			if (iterator->second == y)
			{
				removeEmpty.push_back(iterator);
				addPlayer = true;
				continue;
			}
			if (overlapY != 0 && iterator->second == y + 1)
			{
				removeEmpty.push_back(iterator);
				addPlayerOverlap = true;
				continue;
			}
		}
		
		// The player is between cells.
		if (overlapX != 0)
		{
			overlapX = 1;

			std::pair<MMapIterator, MMapIterator> result = mmEmptyLocations.equal_range(x + overlapX);
			
			// Loop through all found instances of the key.
			for (MMapIterator iterator = result.first; iterator != result.second; iterator++)
			{
				// Player exists at the location.
				if (iterator->second == y)
				{
					removeEmpty.push_back(iterator);
					addPlayerOverlap = true;
				}
			}
		}
	}

	if (overlapY != 0)
	{
		overlapY = 1;
	}

	// Add the player to the map.
	if (addPlayer)
	{
		mmPlayerLocations.insert(std::pair<int, int>(x, y));
	}

	if (addPlayerOverlap)
	{
		mmPlayerLocations.insert(std::pair<int, int>(x + overlapX, y + overlapY));
	}

	// Remove all the locations with players from the empty location map.
	for (int counter = 0; counter < removeEmpty.size(); counter++)
	{
		mmEmptyLocations.erase(removeEmpty[counter]);
	}

	return;
}

void Level::removePlayerLocation(int _coordinateX, int _coordinateY)
{
	bool addEmpty = false;
	bool addEmptyOverlap = false;
	
	div_t cellX = div(_coordinateX, mCellWidth);
	div_t cellY = div(_coordinateY, mCellHeight);

	int x = cellX.quot;
	int y = cellY.quot;
	int overlapX = cellX.rem;
	int overlapY = cellY.rem;

	typedef std::multimap<int, int>::iterator MMapIterator;

	std::vector<MMapIterator> removePlayer;

	// Make sure there are player segments.
	if (!mmPlayerLocations.empty())
	{
		std::pair<MMapIterator, MMapIterator> result = mmPlayerLocations.equal_range(x);
		
		// Loop through all found instances of the key.
		for (MMapIterator iterator = result.first; iterator != result.second; iterator++)
		{
			// Player exists at the location.
			if (iterator->second == y)
			{
				removePlayer.push_back(iterator);
				addEmpty = true;
			}
			if (overlapY != 0 && iterator->second == y + 1)
			{
				removePlayer.push_back(iterator);
				addEmptyOverlap = true;
			}
		}
		
		// The player is between cells.
		if (overlapX != 0)
		{
			overlapX = 1;

			std::pair<MMapIterator, MMapIterator> result = mmPlayerLocations.equal_range(x + overlapX);
			
			// Loop through all found instances of the key.
			for (MMapIterator iterator = result.first; iterator != result.second; iterator++)
			{
				// Player exists at the location.
				if (iterator->second == y)
				{
					removePlayer.push_back(iterator);
					addEmptyOverlap = true;
				}
			}
		}
	}

	if (overlapY != 0)
	{
		overlapY = 1;
	}

	// Add the player to the map.
	if (addEmpty)
	{
		mmEmptyLocations.insert(std::pair<int, int>(x, y));
	}

	if (addEmptyOverlap)
	{
		mmEmptyLocations.insert(std::pair<int, int>(x + overlapX, y + overlapY));
	}

	// Remove all the locations with players from the empty location map.
	for (int counter = 0; counter < removePlayer.size(); counter++)
	{
		mmPlayerLocations.erase(removePlayer[counter]);
	}
}

void Level::getEmptyLocation(int& _coordinateX, int& _coordinateY)
{
	// Create random seed
	std::srand(time(NULL));

	// Generate random coordinates.
	int location = std::rand() % mmEmptyLocations.size();

	int counter = 0;

	for (std::multimap<int, int>::iterator iterator = mmEmptyLocations.begin(); iterator != mmEmptyLocations.end(); iterator++)
	{
		if (counter == location)
		{
			_coordinateX = iterator->first * mCellWidth;
			_coordinateY = iterator->second * mCellHeight;
			mmEmptyLocations.erase(iterator);
			return;
		}

		counter++;
	}

	return;
}

void Level::draw(GraphicsSystem* _pGraphicsSystem)
{
	//for (std::multimap<int, int>::iterator iterator = mPlayerLocations.begin(); iterator != mPlayerLocations.end(); iterator++)
	//{
	//	Font font = Font("..\\..\\shared\\assets\\", "cour.ttf", 10);
	//	Color color = Color(255, 255, 255);
	//	std::string x = std::to_string(iterator->first);
	//	std::string y = std::to_string(iterator->second);
	//	GraphicsBuffer buffer = GraphicsBuffer("Sprites\\", "Block.png");
	//	Sprite sprite = Sprite(&buffer, 0, 0, 32, 32);

	//	//_pGraphicsSystem->draw(sprite, iterator->first * mCellWidth, iterator->second * mCellHeight, 1);

	//	//_pGraphicsSystem->writeText(iterator->first * mCellWidth, iterator->second * mCellHeight, font, color, x, FONT_ALIGN_CENTER);
	//	//_pGraphicsSystem->writeText(iterator->first * mCellWidth, iterator->second * mCellHeight + mCellHeight, font, color, y, FONT_ALIGN_CENTER);
	//}
}

int Level::getPlayerStartX()
{
	return mPlayerStartX * mCellWidth;
}

int Level::getPlayerStartY()
{
	return mPlayerStartY * mCellHeight;
}

int Level::getPlayerStartLength()
{
	return mPlayerStartLength;
}

double Level::getPlayerSpeed()
{
	return mPlayerSpeed;
}

int Level::getPlayerEndLength()
{
	return mPlayerEndLength;
}

int Level::getFoodPoints()
{
	return mFoodPoints;
}

int Level::getPowerUpFrequency()
{
	return mPowerUpFrequency;
}

void Level::getCellDimensions(int& _width, int& _height)
{
	_width = mCellWidth;
	_height = mCellHeight;
	return;
}

// Get the dimensions of the level grid.
void Level::getGridDimensions(int& _width, int& _height)
{
	_width = mCellWidth * mColumns;
	_height = mCellHeight * mRows;
	return;
}

void Level::getLayout(int _layout[])
{
	//_layout = mLayout;
}


