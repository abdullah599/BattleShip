#pragma once
/* Included Files */
#include<iostream>
#include"SFML/Graphics.hpp"

#ifndef BOAT_H
#define BOAT_H
using namespace sf;

/* For orientation */
typedef enum orientation_tag { horizontal, vertical }orientation_t;

/* Boat Class */
class Boat
{
public:
	int orientationCounter = 0;
	int size;
	int id;
	int blastedParts;
	bool isPlaced;
	bool canDisplay;
	/* Set up */
	orientation_t orientation = horizontal; // horizontal or vertical....
	Sprite boatPic;
	Texture t;
	/* Methods */
	int remainingParts();
	bool isBlasted();

	void SetupBoat();
	void setSize(int size)
	{
		this->size = size;
		SetupBoat();
	}


	Boat()
	{
		/* Constructor */
	}



};

void Boat::SetupBoat()
{
	/* Giving images according to the size */
	switch (size)
	{
	case 2:
		t.loadFromFile("images/size2.png");

		break;
	case 3:
		t.loadFromFile("images/size3.png");

		break;
	case 4:
		t.loadFromFile("images/size4.png");
		break;
	case 5:
		t.loadFromFile("images/size4.png");
		break;

	case 6:
		t.loadFromFile("images/size6.png");

		break;
	default:
		std::cout << "Errror in Boat image";
	}

	boatPic.setTexture(t);
}

/* Methods */
int Boat::remainingParts()
{
	if (blastedParts < size)
		return size - blastedParts;
	else
		return 0;
}

bool Boat::isBlasted()
{
	if (!(blastedParts < size))
		return true;
	else
		return false;
}

#endif