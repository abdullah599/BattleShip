#pragma once

/* Included Files */
#include"SFML/Graphics.hpp"
#include<string>

#ifndef GAMETILE_H
#define GAMETILE_H
using namespace sf;

/* GameTile Class */
class GameTile
{
public:
	Vector2f pos;
	Texture gridT;
	Sprite sprite;
	bool isHit;
	bool isSelected;
	bool isShip;
	bool isAlreadySelected;
	bool setUpSprite(std::string);
	int id;
	GameTile(std::string, float, float);
};

/* Definitions to Methods */
GameTile::GameTile(std::string textureName, float x, float y)
{
	if (!setUpSprite(textureName))
		return;
	pos = Vector2f(x, y);
	isShip = false;
	isAlreadySelected = false;
	sprite.setPosition(pos);
}

bool GameTile::setUpSprite(std::string textureName)
{
	if (!gridT.loadFromFile(textureName))
		return false;


	gridT.setSmooth(true);
	sprite.setTexture(gridT);

	sprite.setTextureRect(sf::IntRect(0, 0, 40, 40));
	return true;
}

#endif //GAMETILE_H