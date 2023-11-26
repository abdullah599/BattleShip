#pragma once

/* Included Files */
#include"SFML/Graphics.hpp"
#include"Animation.h"
#include<iostream>
#include"GameTile.h"
#include"boat.h"
#include<vector>
#include <utility>

#ifndef BATTLESHIP_H
#define BATTLESHIP_H

/* Battleship CLass */
class Battleship
{
	sf::Vector2i selectedGrid;
	sf::Vector2i computerShip;

public:
	
	int row = 0, col = 0;
	int numberOfBoats = 0;
	int tempRow, tempCol;
	int gridLength;
	int dir = 0;
	int checkCounter = 0;
	int checking = 0;

	bool isStart;
	bool attackingMode = false;
	bool oppAttack = false;
	bool correctDir = false;

	sf::Sprite name;
	sf::Sprite background;
	sf::Texture backgroundT;
	sf::Texture nameT;
	std::vector<std::vector<GameTile *>> userTiles;
	std::vector<std::vector<GameTile *>> compTiles;
	
	Boat compBoats[5];
	Boat userBoats[5];
	Vector2f posR;
	Blast compBlast;
	Splash compSplash;
	

	pair <int, int> cell;
	pair <int, int> lastCell;
	pair<int, int> initialCell;
	
	/* Constructor calling setup functions */
	Battleship()
	{
		gridLength = 10;
		numberOfBoats = 0;
		attackingMode = false;
		SetUpInitialState();
	}

	void SetUpInitialState()
	{

		SetUpBackground();
		SetUpTiles();
		SetUpBoats();
		setCompBoats();
		isShipForComp();
	}

	/* Setting background */
	int SetUpBackground()
	{

		if (!nameT.loadFromFile("images/Name.png"))
			return 0;

		name.setTexture(nameT);
		name.setPosition(sf::Vector2f(400, 50));


		if (!backgroundT.loadFromFile("images/background.png"))
			return 0;

		background.setTexture(backgroundT);


		return 1;
	}

	/* Setting user & computer boats */
	void SetUpBoats()
	{
		/* setting size for user boats */
		userBoats[0].setSize(2);
		userBoats[1].setSize(3);
		userBoats[2].setSize(4);
		userBoats[3].setSize(4);
		userBoats[4].setSize(6);

		/* setting position for user boats */
		for (int i = 0; i < 5; i++)
		{
			userBoats[i].boatPic.setPosition(140.0f, 280.0f);
		}

		/* setting size for comp boats */
		compBoats[0].setSize(2);
		compBoats[1].setSize(3);
		compBoats[2].setSize(4);
		compBoats[3].setSize(4);
		compBoats[4].setSize(6);

		/* setting position for comp boats */
		for (int i = 0; i < 5; i++)
		{
			compBoats[i].boatPic.setPosition(720.0f, 280.0f + (40 * i));
		}
	}

	/* Setting tiles */
	void SetUpTiles()
	{
		/* UserTiles */
		userTiles.clear();

		/* First Row */
		std::vector<GameTile *> firstRow;
		firstRow.push_back(new GameTile("grid1.png", 150, 300));
		firstRow.push_back(new GameTile("grid1.png", 190, 300));
		firstRow.push_back(new GameTile("grid1.png", 230, 300));
		firstRow.push_back(new GameTile("grid1.png", 270, 300));
		firstRow.push_back(new GameTile("grid1.png", 310, 300));
		firstRow.push_back(new GameTile("grid1.png", 350, 300));
		firstRow.push_back(new GameTile("grid1.png", 390, 300));
		firstRow.push_back(new GameTile("grid1.png", 430, 300));
		firstRow.push_back(new GameTile("grid1.png", 470, 300));
		firstRow.push_back(new GameTile("grid1.png", 510, 300));
		userTiles.push_back(firstRow);

		/* Second Row */
		std::vector<GameTile *> secondRow;
		secondRow.push_back(new GameTile("grid1.png", 150, 340));
		secondRow.push_back(new GameTile("grid1.png", 190, 340));
		secondRow.push_back(new GameTile("grid1.png", 230, 340));
		secondRow.push_back(new GameTile("grid1.png", 270, 340));
		secondRow.push_back(new GameTile("grid1.png", 310, 340));
		secondRow.push_back(new GameTile("grid1.png", 350, 340));
		secondRow.push_back(new GameTile("grid1.png", 390, 340));
		secondRow.push_back(new GameTile("grid1.png", 430, 340));
		secondRow.push_back(new GameTile("grid1.png", 470, 340));
		secondRow.push_back(new GameTile("grid1.png", 510, 340));
		userTiles.push_back(secondRow);

		/* Third Row */
		std::vector<GameTile *> thirdRow;
		thirdRow.push_back(new GameTile("grid1.png", 150, 380));
		thirdRow.push_back(new GameTile("grid1.png", 190, 380));
		thirdRow.push_back(new GameTile("grid1.png", 230, 380));
		thirdRow.push_back(new GameTile("grid1.png", 270, 380));
		thirdRow.push_back(new GameTile("grid1.png", 310, 380));
		thirdRow.push_back(new GameTile("grid1.png", 350, 380));
		thirdRow.push_back(new GameTile("grid1.png", 390, 380));
		thirdRow.push_back(new GameTile("grid1.png", 430, 380));
		thirdRow.push_back(new GameTile("grid1.png", 470, 380));
		thirdRow.push_back(new GameTile("grid1.png", 510, 380));
		userTiles.push_back(thirdRow);

		/* Fourth Row */
		std::vector<GameTile *> fourthRow;
		fourthRow.push_back(new GameTile("grid1.png", 150, 420));
		fourthRow.push_back(new GameTile("grid1.png", 190, 420));
		fourthRow.push_back(new GameTile("grid1.png", 230, 420));
		fourthRow.push_back(new GameTile("grid1.png", 270, 420));
		fourthRow.push_back(new GameTile("grid1.png", 310, 420));
		fourthRow.push_back(new GameTile("grid1.png", 350, 420));
		fourthRow.push_back(new GameTile("grid1.png", 390, 420));
		fourthRow.push_back(new GameTile("grid1.png", 430, 420));
		fourthRow.push_back(new GameTile("grid1.png", 470, 420));
		fourthRow.push_back(new GameTile("grid1.png", 510, 420));
		userTiles.push_back(fourthRow);

		/* Fifth Row */
		std::vector<GameTile *> fifthRow;
		fifthRow.push_back(new GameTile("grid1.png", 150, 460));
		fifthRow.push_back(new GameTile("grid1.png", 190, 460));
		fifthRow.push_back(new GameTile("grid1.png", 230, 460));
		fifthRow.push_back(new GameTile("grid1.png", 270, 460));
		fifthRow.push_back(new GameTile("grid1.png", 310, 460));
		fifthRow.push_back(new GameTile("grid1.png", 350, 460));
		fifthRow.push_back(new GameTile("grid1.png", 390, 460));
		fifthRow.push_back(new GameTile("grid1.png", 430, 460));
		fifthRow.push_back(new GameTile("grid1.png", 470, 460));
		fifthRow.push_back(new GameTile("grid1.png", 510, 460));
		userTiles.push_back(fifthRow);

		/* Sixth Row */
		std::vector<GameTile *> sixthRow;
		sixthRow.push_back(new GameTile("grid1.png", 150, 500));
		sixthRow.push_back(new GameTile("grid1.png", 190, 500));
		sixthRow.push_back(new GameTile("grid1.png", 230, 500));
		sixthRow.push_back(new GameTile("grid1.png", 270, 500));
		sixthRow.push_back(new GameTile("grid1.png", 310, 500));
		sixthRow.push_back(new GameTile("grid1.png", 350, 500));
		sixthRow.push_back(new GameTile("grid1.png", 390, 500));
		sixthRow.push_back(new GameTile("grid1.png", 430, 500));
		sixthRow.push_back(new GameTile("grid1.png", 470, 500));
		sixthRow.push_back(new GameTile("grid1.png", 510, 500));
		userTiles.push_back(sixthRow);

		/* Seventh Row */
		std::vector<GameTile *> seventhRow;
		seventhRow.push_back(new GameTile("grid1.png", 150, 540));
		seventhRow.push_back(new GameTile("grid1.png", 190, 540));
		seventhRow.push_back(new GameTile("grid1.png", 230, 540));
		seventhRow.push_back(new GameTile("grid1.png", 270, 540));
		seventhRow.push_back(new GameTile("grid1.png", 310, 540));
		seventhRow.push_back(new GameTile("grid1.png", 350, 540));
		seventhRow.push_back(new GameTile("grid1.png", 390, 540));
		seventhRow.push_back(new GameTile("grid1.png", 430, 540));
		seventhRow.push_back(new GameTile("grid1.png", 470, 540));
		seventhRow.push_back(new GameTile("grid1.png", 510, 540));
		userTiles.push_back(seventhRow);

		/* Eighth Row */
		std::vector<GameTile *> eigthRow;
		eigthRow.push_back(new GameTile("grid1.png", 150, 580));
		eigthRow.push_back(new GameTile("grid1.png", 190, 580));
		eigthRow.push_back(new GameTile("grid1.png", 230, 580));
		eigthRow.push_back(new GameTile("grid1.png", 270, 580));
		eigthRow.push_back(new GameTile("grid1.png", 310, 580));
		eigthRow.push_back(new GameTile("grid1.png", 350, 580));
		eigthRow.push_back(new GameTile("grid1.png", 390, 580));
		eigthRow.push_back(new GameTile("grid1.png", 430, 580));
		eigthRow.push_back(new GameTile("grid1.png", 470, 580));
		eigthRow.push_back(new GameTile("grid1.png", 510, 580));
		userTiles.push_back(eigthRow);

		/* Ninth Row */
		std::vector<GameTile *> ninthRow;
		ninthRow.push_back(new GameTile("grid1.png", 150, 620));
		ninthRow.push_back(new GameTile("grid1.png", 190, 620));
		ninthRow.push_back(new GameTile("grid1.png", 230, 620));
		ninthRow.push_back(new GameTile("grid1.png", 270, 620));
		ninthRow.push_back(new GameTile("grid1.png", 310, 620));
		ninthRow.push_back(new GameTile("grid1.png", 350, 620));
		ninthRow.push_back(new GameTile("grid1.png", 390, 620));
		ninthRow.push_back(new GameTile("grid1.png", 430, 620));
		ninthRow.push_back(new GameTile("grid1.png", 470, 620));
		ninthRow.push_back(new GameTile("grid1.png", 510, 620));
		userTiles.push_back(ninthRow);

		/* Tenth Row */
		std::vector<GameTile *> tenthRow;
		tenthRow.push_back(new GameTile("grid1.png", 150, 660));
		tenthRow.push_back(new GameTile("grid1.png", 190, 660));
		tenthRow.push_back(new GameTile("grid1.png", 230, 660));
		tenthRow.push_back(new GameTile("grid1.png", 270, 660));
		tenthRow.push_back(new GameTile("grid1.png", 310, 660));
		tenthRow.push_back(new GameTile("grid1.png", 350, 660));
		tenthRow.push_back(new GameTile("grid1.png", 390, 660));
		tenthRow.push_back(new GameTile("grid1.png", 430, 660));
		tenthRow.push_back(new GameTile("grid1.png", 470, 660));
		tenthRow.push_back(new GameTile("grid1.png", 510, 660));
		userTiles.push_back(tenthRow);










		/* ComputerTiles */
		compTiles.clear();

		/* First Row */
		std::vector<GameTile *> cfirstRow;
		cfirstRow.push_back(new GameTile("grid1.png", 730, 300));
		cfirstRow.push_back(new GameTile("grid1.png", 770, 300));
		cfirstRow.push_back(new GameTile("grid1.png", 810, 300));
		cfirstRow.push_back(new GameTile("grid1.png", 850, 300));
		cfirstRow.push_back(new GameTile("grid1.png", 890, 300));
		cfirstRow.push_back(new GameTile("grid1.png", 930, 300));
		cfirstRow.push_back(new GameTile("grid1.png", 970, 300));
		cfirstRow.push_back(new GameTile("grid1.png", 1010, 300));
		cfirstRow.push_back(new GameTile("grid1.png", 1050, 300));
		cfirstRow.push_back(new GameTile("grid1.png", 1090, 300));
		compTiles.push_back(cfirstRow);

		/* Second Row */
		std::vector<GameTile *> csecondRow;
		csecondRow.push_back(new GameTile("grid1.png", 730, 340));
		csecondRow.push_back(new GameTile("grid1.png", 770, 340));
		csecondRow.push_back(new GameTile("grid1.png", 810, 340));
		csecondRow.push_back(new GameTile("grid1.png", 850, 340));
		csecondRow.push_back(new GameTile("grid1.png", 890, 340));
		csecondRow.push_back(new GameTile("grid1.png", 930, 340));
		csecondRow.push_back(new GameTile("grid1.png", 970, 340));
		csecondRow.push_back(new GameTile("grid1.png", 1010, 340));
		csecondRow.push_back(new GameTile("grid1.png", 1050, 340));
		csecondRow.push_back(new GameTile("grid1.png", 1090, 340));
		compTiles.push_back(csecondRow);

		/* Third Row */
		std::vector<GameTile *> cthirdRow;
		cthirdRow.push_back(new GameTile("grid1.png", 730, 380));
		cthirdRow.push_back(new GameTile("grid1.png", 770, 380));
		cthirdRow.push_back(new GameTile("grid1.png", 810, 380));
		cthirdRow.push_back(new GameTile("grid1.png", 850, 380));
		cthirdRow.push_back(new GameTile("grid1.png", 890, 380));
		cthirdRow.push_back(new GameTile("grid1.png", 930, 380));
		cthirdRow.push_back(new GameTile("grid1.png", 970, 380));
		cthirdRow.push_back(new GameTile("grid1.png", 1010, 380));
		cthirdRow.push_back(new GameTile("grid1.png", 1050, 380));
		cthirdRow.push_back(new GameTile("grid1.png", 1090, 380));
		compTiles.push_back(cthirdRow);

		/* Fourth Row */
		std::vector<GameTile *> cfourthRow;
		cfourthRow.push_back(new GameTile("grid1.png", 730, 420));
		cfourthRow.push_back(new GameTile("grid1.png", 770, 420));
		cfourthRow.push_back(new GameTile("grid1.png", 810, 420));
		cfourthRow.push_back(new GameTile("grid1.png", 850, 420));
		cfourthRow.push_back(new GameTile("grid1.png", 890, 420));
		cfourthRow.push_back(new GameTile("grid1.png", 930, 420));
		cfourthRow.push_back(new GameTile("grid1.png", 970, 420));
		cfourthRow.push_back(new GameTile("grid1.png", 1010, 420));
		cfourthRow.push_back(new GameTile("grid1.png", 1050, 420));
		cfourthRow.push_back(new GameTile("grid1.png", 1090, 420));
		compTiles.push_back(cfourthRow);

		/* Fifth Row */
		std::vector<GameTile *> cfifthRow;
		cfifthRow.push_back(new GameTile("grid1.png", 730, 460));
		cfifthRow.push_back(new GameTile("grid1.png", 770, 460));
		cfifthRow.push_back(new GameTile("grid1.png", 810, 460));
		cfifthRow.push_back(new GameTile("grid1.png", 850, 460));
		cfifthRow.push_back(new GameTile("grid1.png", 890, 460));
		cfifthRow.push_back(new GameTile("grid1.png", 930, 460));
		cfifthRow.push_back(new GameTile("grid1.png", 970, 460));
		cfifthRow.push_back(new GameTile("grid1.png", 1010, 460));
		cfifthRow.push_back(new GameTile("grid1.png", 1050, 460));
		cfifthRow.push_back(new GameTile("grid1.png", 1090, 460));
		compTiles.push_back(cfifthRow);

		/* Sixth Row */
		std::vector<GameTile *> csixthRow;
		csixthRow.push_back(new GameTile("grid1.png", 730, 500));
		csixthRow.push_back(new GameTile("grid1.png", 770, 500));
		csixthRow.push_back(new GameTile("grid1.png", 810, 500));
		csixthRow.push_back(new GameTile("grid1.png", 850, 500));
		csixthRow.push_back(new GameTile("grid1.png", 890, 500));
		csixthRow.push_back(new GameTile("grid1.png", 930, 500));
		csixthRow.push_back(new GameTile("grid1.png", 970, 500));
		csixthRow.push_back(new GameTile("grid1.png", 1010, 500));
		csixthRow.push_back(new GameTile("grid1.png", 1050, 500));
		csixthRow.push_back(new GameTile("grid1.png", 1090, 500));
		compTiles.push_back(csixthRow);

		/* Seventh Row */
		std::vector<GameTile *> cseventhRow;
		cseventhRow.push_back(new GameTile("grid1.png", 730, 540));
		cseventhRow.push_back(new GameTile("grid1.png", 770, 540));
		cseventhRow.push_back(new GameTile("grid1.png", 810, 540));
		cseventhRow.push_back(new GameTile("grid1.png", 850, 540));
		cseventhRow.push_back(new GameTile("grid1.png", 890, 540));
		cseventhRow.push_back(new GameTile("grid1.png", 930, 540));
		cseventhRow.push_back(new GameTile("grid1.png", 970, 540));
		cseventhRow.push_back(new GameTile("grid1.png", 1010, 540));
		cseventhRow.push_back(new GameTile("grid1.png", 1050, 540));
		cseventhRow.push_back(new GameTile("grid1.png", 1090, 540));
		compTiles.push_back(cseventhRow);

		/* Eighth Row */
		std::vector<GameTile *> ceigthRow;
		ceigthRow.push_back(new GameTile("grid1.png", 730, 580));
		ceigthRow.push_back(new GameTile("grid1.png", 770, 580));
		ceigthRow.push_back(new GameTile("grid1.png", 810, 580));
		ceigthRow.push_back(new GameTile("grid1.png", 850, 580));
		ceigthRow.push_back(new GameTile("grid1.png", 890, 580));
		ceigthRow.push_back(new GameTile("grid1.png", 930, 580));
		ceigthRow.push_back(new GameTile("grid1.png", 970, 580));
		ceigthRow.push_back(new GameTile("grid1.png", 1010, 580));
		ceigthRow.push_back(new GameTile("grid1.png", 1050, 580));
		ceigthRow.push_back(new GameTile("grid1.png", 1090, 580));
		compTiles.push_back(ceigthRow);

		/* Ninth Row */
		std::vector<GameTile *> cninthRow;
		cninthRow.push_back(new GameTile("grid1.png", 730, 620));
		cninthRow.push_back(new GameTile("grid1.png", 770, 620));
		cninthRow.push_back(new GameTile("grid1.png", 810, 620));
		cninthRow.push_back(new GameTile("grid1.png", 850, 620));
		cninthRow.push_back(new GameTile("grid1.png", 890, 620));
		cninthRow.push_back(new GameTile("grid1.png", 930, 620));
		cninthRow.push_back(new GameTile("grid1.png", 970, 620));
		cninthRow.push_back(new GameTile("grid1.png", 1010, 620));
		cninthRow.push_back(new GameTile("grid1.png", 1050, 620));
		cninthRow.push_back(new GameTile("grid1.png", 1090, 620));
		compTiles.push_back(cninthRow);

		/* Tenth Row */
		std::vector<GameTile *> ctenthRow;
		ctenthRow.push_back(new GameTile("grid1.png", 730, 660));
		ctenthRow.push_back(new GameTile("grid1.png", 770, 660));
		ctenthRow.push_back(new GameTile("grid1.png", 810, 660));
		ctenthRow.push_back(new GameTile("grid1.png", 850, 660));
		ctenthRow.push_back(new GameTile("grid1.png", 890, 660));
		ctenthRow.push_back(new GameTile("grid1.png", 930, 660));
		ctenthRow.push_back(new GameTile("grid1.png", 970, 660));
		ctenthRow.push_back(new GameTile("grid1.png", 1010, 660));
		ctenthRow.push_back(new GameTile("grid1.png", 1050, 660));
		ctenthRow.push_back(new GameTile("grid1.png", 1090, 660));
		compTiles.push_back(ctenthRow);
	}

	/* Update Function */
	void Update()
	{
		CanBeDisplay();

		/* Setting Colors */
		Color color(128, 128, 128);
		Color color2(65, 105, 225);
		Color color3(255, 102, 102);
		Color color4(47, 79, 79);

		/* Changing colors on type of grid */
		for (int i = 0; i < gridLength; i++)
		{
			for (int j = 0; j < gridLength; j++)
			{

				if (userTiles[i][j]->isAlreadySelected == true)
				{

					userTiles[i][j]->sprite.setColor(color2);
				}

				if (userTiles[i][j]->isHit == true)
				{
					userTiles[i][j]->sprite.setColor(Color::Red);
				}
			}
		}

		for (int i = 0; i < gridLength; i++)
		{
			for (int j = 0; j < gridLength; j++)
			{

				if (compTiles[i][j]->isAlreadySelected == true)
				{


					compTiles[i][j]->sprite.setColor(color2);
				}

				if (compTiles[i][j]->isHit == true)
				{
					compTiles[i][j]->sprite.setColor(Color::Black);
				}
				if (compTiles[i][j]->isSelected == true)
				{
					compTiles[i][j]->sprite.setColor(Color::Green);
				}

				if (compTiles[i][j]->isSelected == true && (compTiles[i][j]->isAlreadySelected || compTiles[i][j]->isHit == false))
				{

					compTiles[i][j]->sprite.setColor(Color::Red);
				}
			}
		}

		CanBePlaced();
	}

	/* Can Ship be placed? */
	bool CanBePlaced()
	{
		posR = userBoats[numberOfBoats - 1].boatPic.getPosition();
		if (userBoats[numberOfBoats - 1].orientation == horizontal)
		{
			for (int i = 0; i < gridLength; i++)
			{
				for (int j = 0; j < gridLength; j++)
				{
					if (userTiles[i][j]->sprite.getPosition().x == (posR.x + 10) && userTiles[i][j]->sprite.getPosition().y == (posR.y + 20))
					{
						tempRow = i;
						tempCol = j;
						break;
					}
				}
			}
			if (userBoats[numberOfBoats - 1].size == 2) {
				if (userTiles[tempRow][tempCol]->isShip || userTiles[tempRow][tempCol + 1]->isShip)
				{
					userBoats[numberOfBoats - 1].boatPic.setColor(Color::Red);
					return false;
				}
				else
				{
					userBoats[numberOfBoats - 1].boatPic.setColor(Color::White);
					return true;
				}
			}
			else if (userBoats[numberOfBoats - 1].size == 3)
			{
				if (userTiles[tempRow][tempCol]->isShip || userTiles[tempRow][tempCol + 1]->isShip || userTiles[tempRow][tempCol + 2]->isShip)
				{

					userBoats[numberOfBoats - 1].boatPic.setColor(Color::Red);
					return false;
				}
				else
				{
					userBoats[numberOfBoats - 1].boatPic.setColor(Color::White);
					return true;
				}
			}
			else if (userBoats[numberOfBoats - 1].size == 4)
			{
				if (userTiles[tempRow][tempCol]->isShip || userTiles[tempRow][tempCol + 1]->isShip || userTiles[tempRow][tempCol + 2]->isShip || userTiles[tempRow][tempCol + 3]->isShip)
				{

					userBoats[numberOfBoats - 1].boatPic.setColor(Color::Red);
					return false;
				}
				else
				{
					userBoats[numberOfBoats - 1].boatPic.setColor(Color::White);
					return true;
				}
			}
			else if (userBoats[numberOfBoats - 1].size == 6)
			{
				if (userTiles[tempRow][tempCol]->isShip || userTiles[tempRow][tempCol + 1]->isShip || userTiles[tempRow][tempCol + 2]->isShip || userTiles[tempRow][tempCol + 3]->isShip || userTiles[tempRow][tempCol + 4]->isShip || userTiles[tempRow][tempCol + 5]->isShip)
				{

					userBoats[numberOfBoats - 1].boatPic.setColor(Color::Red);
					return false;
				}
				else
				{
					userBoats[numberOfBoats - 1].boatPic.setColor(Color::White);
					return true;
				}
			}


		}
		else
		{
			for (int i = 0; i < gridLength; i++)
			{
				for (int j = 0; j < gridLength; j++)
				{
					if (userTiles[i][j]->sprite.getPosition().x == (posR.x - 60) && userTiles[i][j]->sprite.getPosition().y == (posR.y + 10))
					{
						tempRow = i;
						tempCol = j;
						break;
					}

				}
			}
			if (userBoats[numberOfBoats - 1].size == 2) {
				if (userTiles[tempRow][tempCol]->isShip || userTiles[tempRow + 1][tempCol]->isShip)
				{
					userBoats[numberOfBoats - 1].boatPic.setColor(Color::Red);
					return false;
				}
				else
				{
					userBoats[numberOfBoats - 1].boatPic.setColor(Color::White);
					return true;
				}
			}
			else if (userBoats[numberOfBoats - 1].size == 3)
			{
				if (userTiles[tempRow][tempCol]->isShip || userTiles[tempRow + 1][tempCol]->isShip || userTiles[tempRow + 2][tempCol]->isShip)
				{

					userBoats[numberOfBoats - 1].boatPic.setColor(Color::Red);
					return false;
				}
				else
				{
					userBoats[numberOfBoats - 1].boatPic.setColor(Color::White);
					return true;
				}
			}
			else if (userBoats[numberOfBoats - 1].size == 4)
			{
				if (userTiles[tempRow][tempCol]->isShip || userTiles[tempRow + 1][tempCol]->isShip || userTiles[tempRow + 2][tempCol]->isShip || userTiles[tempRow + 3][tempCol]->isShip)
				{

					userBoats[numberOfBoats - 1].boatPic.setColor(Color::Red);
					return false;
				}
				else
				{
					userBoats[numberOfBoats - 1].boatPic.setColor(Color::White);
					return true;
				}
			}
			else if (userBoats[numberOfBoats - 1].size == 6)
			{
				if (userTiles[tempRow][tempCol]->isShip || userTiles[tempRow + 1][tempCol]->isShip || userTiles[tempRow + 2][tempCol]->isShip || userTiles[tempRow + 3][tempCol]->isShip || userTiles[tempRow + 4][tempCol]->isShip || userTiles[tempRow + 5][tempCol]->isShip)
				{

					userBoats[numberOfBoats - 1].boatPic.setColor(Color::Red);
					return false;
				}
				else
				{
					userBoats[numberOfBoats - 1].boatPic.setColor(Color::White);
					return true;
				}
			}
		}

	}



	/* Placing Ship */
	void ShipPlacement()
	{

		if (userBoats[numberOfBoats - 1].orientation == horizontal)
		{
			for (int i = 0; i < gridLength; i++)
			{
				for (int j = 0; j < gridLength; j++)
				{
					if (userTiles[i][j]->sprite.getPosition().x == (userBoats[numberOfBoats - 1].boatPic.getPosition().x + 10) && userTiles[i][j]->sprite.getPosition().y == (userBoats[numberOfBoats - 1].boatPic.getPosition().y + 20))
					{

						if (CanBePlaced())
						{
							for (int k = 0; k < userBoats[numberOfBoats - 1].size; k++)
							{
								userTiles[i][j + k]->isShip = true;
							}
							userBoats[numberOfBoats - 1].isPlaced = true;
						}
						else
						{
							numberOfBoats--;
						}
						sf::sleep(sf::milliseconds(200));
						break;
					}
				}
			}
		}
		else
		{

			for (int i = 0; i < gridLength; i++)
			{
				for (int j = 0; j < gridLength; j++)
				{
					if (userTiles[i][j]->sprite.getPosition().x == (userBoats[numberOfBoats - 1].boatPic.getPosition().x - 60) && userTiles[i][j]->sprite.getPosition().y == (userBoats[numberOfBoats - 1].boatPic.getPosition().y + 10))
					{

						if (CanBePlaced()) {
							for (int k = 0; k < userBoats[numberOfBoats - 1].size; k++)
							{
								userTiles[i + k][j]->isShip = true;
							}
							userBoats[numberOfBoats - 1].isPlaced = true;
						}
						else
							numberOfBoats--;

						sf::sleep(sf::milliseconds(175));
						break;
					}
				}
			}
		}



	}



	/* Rotating boats */
	void Rotate()
	{
		userBoats[numberOfBoats - 1].orientationCounter++;

		if (userBoats[numberOfBoats - 1].orientationCounter % 2 == 0)
		{
			userBoats[numberOfBoats - 1].orientation = horizontal;
		}
		else
			userBoats[numberOfBoats - 1].orientation = vertical;


		/* Horizontal Rotation */


		if (userBoats[numberOfBoats - 1].orientation == horizontal) {

			posR = userBoats[numberOfBoats - 1].boatPic.getPosition();

			/* Bounds for ship of size 2 */
			if (userBoats[numberOfBoats - 1].size == 2)
			{
				if (posR.x <= 530)
				{
					userBoats[numberOfBoats - 1].boatPic.setRotation(0.0f);
					posR = userBoats[numberOfBoats - 1].boatPic.getPosition();
					userBoats[numberOfBoats - 1].boatPic.setPosition(posR.x - 70, posR.y - 10);
				}
				else if (posR.x <= 570)
				{
					userBoats[numberOfBoats - 1].boatPic.setRotation(0.0f);
					posR = userBoats[numberOfBoats - 1].boatPic.getPosition();
					userBoats[numberOfBoats - 1].boatPic.setPosition(posR.x - 110, posR.y - 10);
				}
			}

			/* Bounds for ship of size 3 */
			else if (userBoats[numberOfBoats - 1].size == 3)
			{
				if (posR.x <= 490)
				{
					userBoats[numberOfBoats - 1].boatPic.setRotation(0.0f);
					posR = userBoats[numberOfBoats - 1].boatPic.getPosition();
					userBoats[numberOfBoats - 1].boatPic.setPosition(posR.x - 70, posR.y - 10);

				}
				else if (posR.x <= 530)
				{
					userBoats[numberOfBoats - 1].boatPic.setRotation(0.0f);
					posR = userBoats[numberOfBoats - 1].boatPic.getPosition();
					userBoats[numberOfBoats - 1].boatPic.setPosition(posR.x - 110, posR.y - 10);
				}
				else if (posR.x <= 570)
				{
					userBoats[numberOfBoats - 1].boatPic.setRotation(0.0f);
					posR = userBoats[numberOfBoats - 1].boatPic.getPosition();
					userBoats[numberOfBoats - 1].boatPic.setPosition(posR.x - 150, posR.y - 10);
				}
			}

			/* Bounds for ship of size 4 */
			else if (userBoats[numberOfBoats - 1].size == 4)
			{
				if (posR.x <= 450)
				{
					userBoats[numberOfBoats - 1].boatPic.setRotation(0.0f);
					posR = userBoats[numberOfBoats - 1].boatPic.getPosition();
					userBoats[numberOfBoats - 1].boatPic.setPosition(posR.x - 70, posR.y - 10);
				}
				else if (posR.x <= 490)
				{
					userBoats[numberOfBoats - 1].boatPic.setRotation(0.0f);
					posR = userBoats[numberOfBoats - 1].boatPic.getPosition();
					userBoats[numberOfBoats - 1].boatPic.setPosition(posR.x - 110, posR.y - 10);

				}
				else if (posR.x <= 530)
				{
					userBoats[numberOfBoats - 1].boatPic.setRotation(0.0f);
					posR = userBoats[numberOfBoats - 1].boatPic.getPosition();
					userBoats[numberOfBoats - 1].boatPic.setPosition(posR.x - 150, posR.y - 10);
				}
				else if (posR.x <= 570)
				{
					userBoats[numberOfBoats - 1].boatPic.setRotation(0.0f);
					posR = userBoats[numberOfBoats - 1].boatPic.getPosition();
					userBoats[numberOfBoats - 1].boatPic.setPosition(posR.x - 190, posR.y - 10);
				}
			}

			/* Bounds for ship of size 6 */
			else if (userBoats[numberOfBoats - 1].size == 6)
			{
				if (posR.x <= 450 - 80)
				{
					userBoats[numberOfBoats - 1].boatPic.setRotation(0.0f);
					posR = userBoats[numberOfBoats - 1].boatPic.getPosition();
					userBoats[numberOfBoats - 1].boatPic.setPosition(posR.x + 40, posR.y);
				}
				if (posR.x <= 450 - 40)
				{
					userBoats[numberOfBoats - 1].boatPic.setRotation(0.0f);
					posR = userBoats[numberOfBoats - 1].boatPic.getPosition();
					userBoats[numberOfBoats - 1].boatPic.setPosition(posR.x - 110, posR.y - 10);
				}
				else if (posR.x <= 450)
				{
					userBoats[numberOfBoats - 1].boatPic.setRotation(0.0f);
					posR = userBoats[numberOfBoats - 1].boatPic.getPosition();
					userBoats[numberOfBoats - 1].boatPic.setPosition(posR.x - 150, posR.y - 10);

				}
				else if (posR.x <= 490)
				{
					userBoats[numberOfBoats - 1].boatPic.setRotation(0.0f);
					posR = userBoats[numberOfBoats - 1].boatPic.getPosition();
					userBoats[numberOfBoats - 1].boatPic.setPosition(posR.x - 190, posR.y - 10);
				}
				else if (posR.x <= 530)
				{
					userBoats[numberOfBoats - 1].boatPic.setRotation(0.0f);
					posR = userBoats[numberOfBoats - 1].boatPic.getPosition();
					userBoats[numberOfBoats - 1].boatPic.setPosition(posR.x - 230, posR.y - 10);
				}

				else if (posR.x <= 570)
				{
					userBoats[numberOfBoats - 1].boatPic.setRotation(0.0f);
					posR = userBoats[numberOfBoats - 1].boatPic.getPosition();
					userBoats[numberOfBoats - 1].boatPic.setPosition(posR.x - 270, posR.y - 10);
				}

				else if (posR.x <= 570 + 40)
				{
					userBoats[numberOfBoats - 1].boatPic.setRotation(0.0f);
					posR = userBoats[numberOfBoats - 1].boatPic.getPosition();
					userBoats[numberOfBoats - 1].boatPic.setPosition(posR.x - 310, posR.y - 10);
				}
			}
			sf::sleep(sf::milliseconds(175));
		}
		else
		{
			posR = userBoats[numberOfBoats - 1].boatPic.getPosition();

			/* Bounds for ship of size 2 */
			if (userBoats[numberOfBoats - 1].size == 2)
			{
				if (posR.y <= 610)
				{
					userBoats[numberOfBoats - 1].boatPic.setRotation(90.0f);
					posR = userBoats[numberOfBoats - 1].boatPic.getPosition();
					userBoats[numberOfBoats - 1].boatPic.setPosition(posR.x + 70, posR.y + 10);
				}
				else if (posR.y <= 650)
				{
					userBoats[numberOfBoats - 1].boatPic.setRotation(90.0f);
					posR = userBoats[numberOfBoats - 1].boatPic.getPosition();
					userBoats[numberOfBoats - 1].boatPic.setPosition(posR.x + 70, posR.y - 30);
				}
			}

			/* Bounds for ship of size 3 */
			else if (userBoats[numberOfBoats - 1].size == 3)
			{


				if (posR.y <= 570)
				{
					userBoats[numberOfBoats - 1].boatPic.setRotation(90.0f);
					posR = userBoats[numberOfBoats - 1].boatPic.getPosition();
					userBoats[numberOfBoats - 1].boatPic.setPosition(posR.x + 70, posR.y + 10);
				}
				else if (posR.y <= 610)
				{
					userBoats[numberOfBoats - 1].boatPic.setRotation(90.0f);
					posR = userBoats[numberOfBoats - 1].boatPic.getPosition();
					userBoats[numberOfBoats - 1].boatPic.setPosition(posR.x + 70, posR.y - 30);
				}
				else if (posR.y <= 650)
				{
					userBoats[numberOfBoats - 1].boatPic.setRotation(90.0f);
					posR = userBoats[numberOfBoats - 1].boatPic.getPosition();
					userBoats[numberOfBoats - 1].boatPic.setPosition(posR.x + 70, posR.y - 70);
				}
			}

			/* Bounds for ship of size 4 */
			else if (userBoats[numberOfBoats - 1].size == 4)
			{
				if (posR.y <= 530)
				{
					userBoats[numberOfBoats - 1].boatPic.setRotation(90.0f);
					posR = userBoats[numberOfBoats - 1].boatPic.getPosition();
					userBoats[numberOfBoats - 1].boatPic.setPosition(posR.x + 70, posR.y + 10);
				}
				else if (posR.y <= 570)
				{
					userBoats[numberOfBoats - 1].boatPic.setRotation(90.0f);
					posR = userBoats[numberOfBoats - 1].boatPic.getPosition();
					userBoats[numberOfBoats - 1].boatPic.setPosition(posR.x + 70, posR.y - 30);
				}
				else if (posR.y <= 610)
				{
					userBoats[numberOfBoats - 1].boatPic.setRotation(90.0f);
					posR = userBoats[numberOfBoats - 1].boatPic.getPosition();
					userBoats[numberOfBoats - 1].boatPic.setPosition(posR.x + 70, posR.y - 70);
				}
				else if (posR.y <= 650)
				{
					userBoats[numberOfBoats - 1].boatPic.setRotation(90.0f);
					posR = userBoats[numberOfBoats - 1].boatPic.getPosition();
					userBoats[numberOfBoats - 1].boatPic.setPosition(posR.x + 70, posR.y - 110);
				}
			}

			/* Bounds for ship of size 6 */
			else if (userBoats[numberOfBoats - 1].size == 6)
			{
				if (posR.y <= 530 - 80)
				{
					userBoats[numberOfBoats - 1].boatPic.setRotation(90.0f);
					posR = userBoats[numberOfBoats - 1].boatPic.getPosition();
					userBoats[numberOfBoats - 1].boatPic.setPosition(posR.x + 70, posR.y + 10);
				}
				else if (posR.y <= 530 - 40)
				{
					userBoats[numberOfBoats - 1].boatPic.setRotation(90.0f);
					posR = userBoats[numberOfBoats - 1].boatPic.getPosition();
					userBoats[numberOfBoats - 1].boatPic.setPosition(posR.x + 70, posR.y - 30);
				}
				else if (posR.y <= 530)
				{
					userBoats[numberOfBoats - 1].boatPic.setRotation(90.0f);
					posR = userBoats[numberOfBoats - 1].boatPic.getPosition();
					userBoats[numberOfBoats - 1].boatPic.setPosition(posR.x + 70, posR.y - 70);
				}
				else if (posR.y <= 570)
				{
					userBoats[numberOfBoats - 1].boatPic.setRotation(90.0f);
					posR = userBoats[numberOfBoats - 1].boatPic.getPosition();
					userBoats[numberOfBoats - 1].boatPic.setPosition(posR.x + 70, posR.y - 110);
				}
				else if (posR.y <= 610)
				{
					userBoats[numberOfBoats - 1].boatPic.setRotation(90.0f);
					posR = userBoats[numberOfBoats - 1].boatPic.getPosition();
					userBoats[numberOfBoats - 1].boatPic.setPosition(posR.x + 70, posR.y - 150);
				}
				else if (posR.y <= 650)
				{
					userBoats[numberOfBoats - 1].boatPic.setRotation(90.0f);
					posR = userBoats[numberOfBoats - 1].boatPic.getPosition();
					userBoats[numberOfBoats - 1].boatPic.setPosition(posR.x + 70, posR.y - 190);
				}
			}
			sf::sleep(sf::milliseconds(175));
		}
	}

	/* Upward Movement */
	void Up()
	{
		posR = userBoats[numberOfBoats - 1].boatPic.getPosition();


		if (posR.y > 300)

			userBoats[numberOfBoats - 1].boatPic.setPosition(posR.x, posR.y - 40);

		sf::sleep(sf::milliseconds(175));
	}


	/* Downward Movement */
	void Down()
	{
		posR = userBoats[numberOfBoats - 1].boatPic.getPosition();

		if (userBoats[numberOfBoats - 1].orientation == horizontal)
		{
			if (posR.y < 620)
			{
				userBoats[numberOfBoats - 1].boatPic.setPosition(posR.x, posR.y + 40);
			}
		}
		else
		{
			/* Bounds for ship of size 2 */
			if (userBoats[numberOfBoats - 1].size == 2)
				if (posR.y < 520 + 80)
					userBoats[numberOfBoats - 1].boatPic.setPosition(posR.x, posR.y + 40);

			/* Bounds for ship of size 3 */
			if (userBoats[numberOfBoats - 1].size == 3)
				if (posR.y < 520 + 40)
					userBoats[numberOfBoats - 1].boatPic.setPosition(posR.x, posR.y + 40);

			/* Bounds for ship of size 4 */
			if (userBoats[numberOfBoats - 1].size == 4)
				if (posR.y < 520)
					userBoats[numberOfBoats - 1].boatPic.setPosition(posR.x, posR.y + 40);

			/* Bounds for ship of size 6 */
			if (userBoats[numberOfBoats - 1].size == 6)
				if (posR.y < 520 - 80)
					userBoats[numberOfBoats - 1].boatPic.setPosition(posR.x, posR.y + 40);
		}

		sf::sleep(sf::milliseconds(175));
	}

	/* Right Movement */
	void Right()
	{
		posR = userBoats[numberOfBoats - 1].boatPic.getPosition();
		if (userBoats[numberOfBoats - 1].orientation == vertical)
		{
			if (posR.x < 550)
				userBoats[numberOfBoats - 1].boatPic.setPosition(posR.x + 40, posR.y);
		}
		else
		{
			/* Bounds for ship of size 2 */
			if (userBoats[numberOfBoats - 1].size == 2)
			{
				if (posR.x < 350 + 80)
					userBoats[numberOfBoats - 1].boatPic.setPosition(posR.x + 40, posR.y);
			}

			/* Bounds for ship of size 3 */
			else if (userBoats[numberOfBoats - 1].size == 3)
			{
				if (posR.x < 350 + 40)
					userBoats[numberOfBoats - 1].boatPic.setPosition(posR.x + 40, posR.y);
			}


			/* Bounds for ship of size 4 */
			else if (userBoats[numberOfBoats - 1].size == 4)
			{
				if (posR.x < 350)
					userBoats[numberOfBoats - 1].boatPic.setPosition(posR.x + 40, posR.y);
			}

			/* Bounds for ship of size 6 */
			else if (userBoats[numberOfBoats - 1].size == 6)
			{
				if (posR.x < 350 - 80)
					userBoats[numberOfBoats - 1].boatPic.setPosition(posR.x + 40, posR.y);
			}
		}
		sf::sleep(sf::milliseconds(175));
	}

	/* Left Movement */
	void Left()
	{
		posR = userBoats[numberOfBoats - 1].boatPic.getPosition();
		if (userBoats[numberOfBoats - 1].orientation == horizontal)
		{
			if (posR.x > 150)
				userBoats[numberOfBoats - 1].boatPic.setPosition(posR.x - 40, posR.y);
		}
		else
		{
			if (posR.x > 240)
				userBoats[numberOfBoats - 1].boatPic.setPosition(posR.x - 40, posR.y);
		}

		sf::sleep(sf::milliseconds(175));
	}

	/* For moving within computer tiles for blast  */
	void MoveRight()
	{
		compTiles[row][col]->isSelected = false;

		if (col >= 9)
		{
			col = -1;
		}

		col++;
	}
	void MoveLeft()
	{

		compTiles[row][col]->isSelected = false;

		if (col <= 0)
		{
			col = 10;
		}

		col--;
	}
	void MoveUp()
	{
		compTiles[row][col]->isSelected = false;

		if (row <= 0)
		{
			row = 10;
		}

		row--;
	}
	void MoveDown()
	{
		compTiles[row][col]->isSelected = false;

		if (row >= 9)
		{
			row = -1;
		}

		row++;
	}

	void SetUpCompPos()
	{
		compTiles[row][col]->isSelected = true;

		for (int i = 0; i < gridLength; i++)
		{
			for (int j = 0; j < gridLength; j++)
			{

				if (compTiles[i][j]->isSelected == true)
				{
					compTiles[i][j]->sprite.setColor(Color::Green);
					row = i;
					col = j;
				}

				else
					compTiles[i][j]->sprite.setColor(Color::White);

			}
		}
	}

	/* Setting computer Boats on board */
	void setCompBoats()
	{
		srand(time(0));
		int rnd = rand() % 3;

		/* Patterns for boats */
		for (int i = 0; i < 5; i++)
		{
			compBoats[i].orientation = horizontal;
		}
		if (rnd == 0)
		{
			compBoats[0].boatPic.setPosition(720, 640);
			compBoats[1].boatPic.setPosition(960, 520);
			compBoats[2].boatPic.setPosition(800, 440 + 40 + 40);
			compBoats[3].boatPic.setPosition(920, 360);
			compBoats[4].boatPic.setPosition(1080, 280);

		}
		else if (rnd == 1)
		{
			compBoats[0].boatPic.setPosition(730 - 10, 340 - 20);
			compBoats[1].boatPic.setPosition(850 - 10, 340 - 20);
			compBoats[2].boatPic.setPosition(770 - 10, 540 - 20);
			compBoats[3].boatPic.setPosition(930 - 10, 500 - 20);
			compBoats[4].boatPic.setPosition(1090 - 10, 420 - 20);
		}
		else if (rnd == 2)
		{
			compBoats[0].boatPic.setPosition(1090 - 10, 540 - 20);
			compBoats[1].boatPic.setPosition(730 - 10, 300 - 20);
			compBoats[2].boatPic.setPosition(730 - 10, 460 - 20);
			compBoats[3].boatPic.setPosition(810 - 10, 580 - 20);
			compBoats[4].boatPic.setPosition(970 - 10, 420 - 20);
		}

		/* Bounding Rotatations */
		for (int i = 0; i < 5; i++)
		{
			int rotRnd = rand() % 2;

			if (rotRnd % 2)
			{
				compBoats[i].orientation = horizontal;
			}
			else
				compBoats[i].orientation = vertical;

			if ((compBoats[i].orientation == horizontal))
			{

				posR = compBoats[i].boatPic.getPosition();
				
				/* Bounds for ship of size 2 */
				if (compBoats[i].size == 2)
				{
					if (posR.x <= 530 + 510)
					{
						compBoats[i].boatPic.setRotation(0.0f);
						posR = compBoats[i].boatPic.getPosition();
						compBoats[i].boatPic.setPosition(posR.x, posR.y);
					}
					else if (posR.x <= 570 + 510)
					{
						compBoats[i].boatPic.setRotation(0.0f);
						posR = compBoats[i].boatPic.getPosition();
						compBoats[i].boatPic.setPosition(posR.x - 110 + 70, posR.y);
					}
				}

				/* Bounds for ship of size 3 */
				else if (compBoats[i].size == 3)
				{
					if (posR.x <= 490 + 510)
					{
						compBoats[i].boatPic.setRotation(0.0f);
						posR = compBoats[i].boatPic.getPosition();
						compBoats[i].boatPic.setPosition(posR.x, posR.y);

					}
					else if (posR.x <= 530 + 510)
					{
						compBoats[i].boatPic.setRotation(0.0f);
						posR = compBoats[i].boatPic.getPosition();
						compBoats[i].boatPic.setPosition(posR.x - 110 + 70, posR.y);
					}
					else if (posR.x <= 570 + 510)
					{
						compBoats[i].boatPic.setRotation(0.0f);
						posR = compBoats[i].boatPic.getPosition();
						compBoats[i].boatPic.setPosition(posR.x - 150 + 70, posR.y);
					}
				}

				/* Bounds for ship of size 4 */
				else if (compBoats[i].size == 4)
				{
					if (posR.x <= 450 + 510)
					{
						compBoats[i].boatPic.setRotation(0.0f);
						posR = compBoats[i].boatPic.getPosition();
						compBoats[i].boatPic.setPosition(posR.x, posR.y);
					}
					else if (posR.x <= 490 + 510)
					{
						compBoats[i].boatPic.setRotation(0.0f);
						posR = compBoats[i].boatPic.getPosition();
						compBoats[i].boatPic.setPosition(posR.x - 110 + 70, posR.y);

					}
					else if (posR.x <= 530 + 510)
					{
						compBoats[i].boatPic.setRotation(0.0f);
						posR = compBoats[i].boatPic.getPosition();
						compBoats[i].boatPic.setPosition(posR.x - 150 + 70, posR.y);
					}
					else if (posR.x <= 570 + 510)
					{
						compBoats[i].boatPic.setRotation(0.0f);
						posR = compBoats[i].boatPic.getPosition();
						compBoats[i].boatPic.setPosition(posR.x - 190 + 70, posR.y);
					}
				}

				/* Bounds for ship of size 6 */
				else if (compBoats[i].size == 6)
				{
					if (posR.x <= 450 - 80 + 510)
					{
						compBoats[i].boatPic.setRotation(0.0f);
						posR = compBoats[i].boatPic.getPosition();
						compBoats[i].boatPic.setPosition(posR.x + 40, posR.y);
					}
					if (posR.x <= 450 - 40 + 510)
					{
						compBoats[i].boatPic.setRotation(0.0f);
						posR = compBoats[i].boatPic.getPosition();
						compBoats[i].boatPic.setPosition(posR.x - 110 + 70, posR.y);
					}
					else if (posR.x <= 450 + 510)
					{
						compBoats[i].boatPic.setRotation(0.0f);
						posR = compBoats[i].boatPic.getPosition();
						compBoats[i].boatPic.setPosition(posR.x - 150 + 70, posR.y);

					}
					else if (posR.x <= 490 + 510)
					{
						compBoats[i].boatPic.setRotation(0.0f);
						posR = compBoats[i].boatPic.getPosition();
						compBoats[i].boatPic.setPosition(posR.x - 190 + 70, posR.y);
					}
					else if (posR.x <= 530 + 510)
					{
						compBoats[i].boatPic.setRotation(0.0f);
						posR = compBoats[i].boatPic.getPosition();
						compBoats[i].boatPic.setPosition(posR.x - 230 + 70, posR.y);
					}

					else if (posR.x <= 570 + 510)
					{
						compBoats[i].boatPic.setRotation(0.0f);
						posR = compBoats[i].boatPic.getPosition();
						compBoats[i].boatPic.setPosition(posR.x - 270 + 70, posR.y);
					}

					else if (posR.x <= 570 + 40 + 510)
					{
						compBoats[i].boatPic.setRotation(0.0f);
						posR = compBoats[i].boatPic.getPosition();
						compBoats[i].boatPic.setPosition(posR.x - 310 + 70, posR.y);
					}
				}
				sf::sleep(sf::milliseconds(175));
			}

			/* Bounds and Rotation */
			else 
{

				posR = compBoats[i].boatPic.getPosition();

				/* Bounds for ship of size 2 */
				if (compBoats[i].size == 2)
				{
					if (posR.y <= 610)
					{
						compBoats[i].boatPic.setRotation(90.0f);
						posR = compBoats[i].boatPic.getPosition();
						compBoats[i].boatPic.setPosition(posR.x + 70, posR.y + 10);
					}
					else if (posR.y <= 650)
					{
						compBoats[i].boatPic.setRotation(90.0f);
						posR = compBoats[i].boatPic.getPosition();
						compBoats[i].boatPic.setPosition(posR.x + 70, posR.y - 30);
					}
				}

				/* Bounds for ship of size 3 */
				else if (compBoats[i].size == 3)
				{


					if (posR.y <= 570)
					{
						compBoats[i].boatPic.setRotation(90.0f);
						posR = compBoats[i].boatPic.getPosition();
						compBoats[i].boatPic.setPosition(posR.x + 70, posR.y + 10);
					}
					else if (posR.y <= 610)
					{
						compBoats[i].boatPic.setRotation(90.0f);
						posR = compBoats[i].boatPic.getPosition();
						compBoats[i].boatPic.setPosition(posR.x + 70, posR.y - 30);
					}
					else if (posR.y <= 650)
					{
						compBoats[i].boatPic.setRotation(90.0f);
						posR = compBoats[i].boatPic.getPosition();
						compBoats[i].boatPic.setPosition(posR.x + 70, posR.y - 70);
					}
				}

				/* Bounds for ship of size 4 */
				else if (compBoats[i].size == 4)
				{
					if (posR.y <= 530)
					{
						compBoats[i].boatPic.setRotation(90.0f);
						posR = compBoats[i].boatPic.getPosition();
						compBoats[i].boatPic.setPosition(posR.x + 70, posR.y + 10);
					}
					else if (posR.y <= 570)
					{
						compBoats[i].boatPic.setRotation(90.0f);
						posR = compBoats[i].boatPic.getPosition();
						compBoats[i].boatPic.setPosition(posR.x + 70, posR.y - 30);
					}
					else if (posR.y <= 610)
					{
						compBoats[i].boatPic.setRotation(90.0f);
						posR = compBoats[i].boatPic.getPosition();
						compBoats[i].boatPic.setPosition(posR.x + 70, posR.y - 70);
					}
					else if (posR.y <= 650)
					{
						compBoats[i].boatPic.setRotation(90.0f);
						posR = compBoats[i].boatPic.getPosition();
						compBoats[i].boatPic.setPosition(posR.x + 70, posR.y - 110);
					}
				}

				/* Bounds for ship of size 6 */
				else if (compBoats[i].size == 6)
				{
					if (posR.y <= 530 - 80)
					{
						compBoats[i].boatPic.setRotation(90.0f);
						posR = compBoats[i].boatPic.getPosition();
						compBoats[i].boatPic.setPosition(posR.x + 70, posR.y + 10);
					}
					else if (posR.y <= 530 - 40)
					{
						compBoats[i].boatPic.setRotation(90.0f);
						posR = compBoats[i].boatPic.getPosition();
						compBoats[i].boatPic.setPosition(posR.x + 70, posR.y - 30);
					}
					else if (posR.y <= 530)
					{
						compBoats[i].boatPic.setRotation(90.0f);
						posR = compBoats[i].boatPic.getPosition();
						compBoats[i].boatPic.setPosition(posR.x + 70, posR.y - 70);
					}
					else if (posR.y <= 570)
					{
						compBoats[i].boatPic.setRotation(90.0f);
						posR = compBoats[i].boatPic.getPosition();
						compBoats[i].boatPic.setPosition(posR.x + 70, posR.y - 110);
					}
					else if (posR.y <= 610)
					{
						compBoats[i].boatPic.setRotation(90.0f);
						posR = compBoats[i].boatPic.getPosition();
						compBoats[i].boatPic.setPosition(posR.x + 70, posR.y - 150);
					}
					else if (posR.y <= 650)
					{
						compBoats[i].boatPic.setRotation(90.0f);
						posR = compBoats[i].boatPic.getPosition();
						compBoats[i].boatPic.setPosition(posR.x + 70, posR.y - 190);
					}
				}
				sf::sleep(sf::milliseconds(175));
			}
		}
	}

	/* For setting bool isShip true where there is comp boat */
	void isShipForComp() 
	{

		for (int ships = 0; ships < 5; ships++)
		{
			if (compBoats[ships].orientation == horizontal)
			{
				for (int i = 0; i < gridLength; i++)
				{
					for (int j = 0; j < gridLength; j++)
					{
						if (compTiles[i][j]->sprite.getPosition().x == (compBoats[ships].boatPic.getPosition().x + 10) && compTiles[i][j]->sprite.getPosition().y == (compBoats[ships].boatPic.getPosition().y + 20))
						{


							for (int k = 0; k < compBoats[ships].size; k++)
							{
								compTiles[i][j + k]->isShip = true;
								compBoats[ships].id = ships;
								compTiles[i][j + k]->id = compBoats[ships].id;	
							}
							compBoats[ships].isPlaced = true;
							break;
						}
					}
				}
			}
			else
			{

				for (int i = 0; i < gridLength; i++)
				{
					for (int j = 0; j < gridLength; j++)
					{
						if (compTiles[i][j]->sprite.getPosition().x == (compBoats[ships].boatPic.getPosition().x - 60) && compTiles[i][j]->sprite.getPosition().y == (compBoats[ships].boatPic.getPosition().y + 10))
						{
							for (int k = 0; k < compBoats[ships].size; k++)
							{
								compTiles[i + k][j]->isShip = true;
								compBoats[ships].id = ships;
								compTiles[i + k][j]->id = compBoats[ships].id;
							}
							compBoats[ships].isPlaced = true;
							break;
						}
					}
				}
			}
		}
	}


	void isHit(bool &userTurn) {


		for (int i = 0; i < gridLength; i++)
		{
			for (int j = 0; j < gridLength; j++)
			{
				if (compTiles[i][j]->isSelected == true)
				{
					row = i;
					col = j;
				}
			}
		}

		if (compTiles[row][col]->isShip == true && compTiles[row][col]->isAlreadySelected == false)
		{
			compTiles[row][col]->isHit = true;
		}

		/* Computer Turn */
		if (compTiles[row][col]->isShip == false && compTiles[row][col]->isAlreadySelected == false)
		{
			userTurn = false;
		}

		compTiles[row][col]->isAlreadySelected = true;

	}

	/* Animate blast only if there's a boat */
	bool IsShip(float x, float y)
	{
		for (int i = 0; i < gridLength; i++)
		{
			for (int j = 0; j < gridLength; j++)
			{
				if (compTiles[i][j]->sprite.getPosition().x == (x - 5) && compTiles[i][j]->sprite.getPosition().y == (y - 5) && compTiles[i][j]->isShip == true)
				{
					tempRow = i;
					tempCol = j;
					if (compTiles[i][j]->isAlreadySelected == false)
						return true;
				}
			}
		}

		return false;
	}

	/* Animate splash only if it is not selected */
	bool IsSplash(float x, float y)
	{
		for (int i = 0; i < gridLength; i++)
		{
			for (int j = 0; j < gridLength; j++)
			{
				if (compTiles[i][j]->sprite.getPosition().x == (x - 5) && compTiles[i][j]->sprite.getPosition().y == (y - 5) && compTiles[i][j]->isShip == false)
				{

					if (compTiles[i][j]->isAlreadySelected == false)
						return true;
					else
						return false;
				}
			}
		}

		return false;
	}

	bool AIBasedAttack()
	{



		if (!oppAttack)
		{
		again:
			if (checkCounter < 4) {
				if (dir == 0)
				{
					/* Left Bound */
					if (lastCell.second > 0)
					{
						cell.first = lastCell.first;
						cell.second = lastCell.second - 1;

					}
					else
					{
						if (checking >= 1)
						{
							oppAttack = true;
							checkCounter = 3;
							goto oppositeMove;
							return true;
						}
						else
						{
							checkCounter++;
							dir++;
							checking = 0;
							goto again;
						}
					}
				}

				/* Right Bound */
				else if (dir == 1)
				{

					if (lastCell.second < 9)
					{
						cell.first = lastCell.first;
						cell.second = lastCell.second + 1;

					}
					else
					{
						if (checking >= 1)
						{
							oppAttack = true;
							checkCounter = 3;
							goto oppositeMove;
							return true;
						}
						else

						{
							checkCounter++;
							dir++;
							checking = 0;
							goto again;
						}
					}

				}

				/* Up Bound */
				else if (dir == 2)
				{

					if (lastCell.first > 0)
					{
						cell.first = lastCell.first - 1;
						cell.second = lastCell.second;

					}
					else
					{
						if (checking >= 1)
						{
							oppAttack = true;
							checkCounter = 3;
							goto oppositeMove;
							return true;
						}
						else

						{

							checkCounter++;
							dir++;
							checking = 0;
							goto again;
						}
					}

				}

				/* Down Bound */
				else if (dir == 3)
				{

					if (lastCell.first < 9)
					{
						cell.first = lastCell.first + 1;
						cell.second = lastCell.second;

					}
					else
					{
						if (checking >= 1)
						{
							oppAttack = true;
							checkCounter = 3;
							goto oppositeMove;
							return true;
						}
						else

						{
							checkCounter++;
							checking = 0;
							dir++;
							goto again;
						}
					}
				}

				else
				{
					oppAttack = false;
					attackingMode = false;
					checkCounter = 0;
					checking = 0;
					dir = 0;
					return true;
				}

			}
			else
			{
				checkCounter = 0;
				return false;
			}

			if (userTiles[cell.first][cell.second]->isAlreadySelected == false)
			{
				if (userTiles[cell.first][cell.second]->isShip == true)
				{

					sf::sleep(sf::milliseconds(700));
					userTiles[cell.first][cell.second]->isHit = true;
					CompBlast(cell.first, cell.second);
					userTiles[cell.first][cell.second]->isAlreadySelected = true;

					attackingMode = true;
					checkCounter = 0;
					lastCell = cell;
					checking++;
					attackingMode = true;

					return true;



				}
				else if (userTiles[cell.first][cell.second]->isShip == false && checking >= 1) {

					userTiles[cell.first][cell.second]->isAlreadySelected = true;

					CompSplash(cell.first, cell.second);

					oppAttack = true;


					return false;
				}
				else if (userTiles[cell.first][cell.second]->isShip == false) {
					userTiles[cell.first][cell.second]->isAlreadySelected = true;
					checkCounter++;
					CompSplash(cell.first, cell.second);
					dir++;
					attackingMode = true;
					oppAttack = false;
					checking = 0;
					return false;
				}


			}

			else
			{
				if (checking <= 1)
				{
					checkCounter++;
					dir++;
					attackingMode = true;
					checking = 0;
					return true;
				}
				else
				{
					oppAttack = true;
					std::cout << checking << std::endl;
					return false;
				}

			}
		}
		else if (oppAttack&& checking >= 1)
		{
		oppositeMove:
			std::cout << checking;
			checking = 0;

			if (!correctDir)
			{
				if (dir == 0)
				{
					dir = 1;

					correctDir = true;
				}
				else if (dir == 1)
				{
					dir = 0;

					correctDir = true;
				}
				else if (dir == 2)
				{
					dir = 3;

					correctDir = true;
				}
				else if (dir == 3)
				{
					dir = 2;

					correctDir = true;
				}
				else {
					oppAttack = false;
					attackingMode = false;
					checkCounter = 0;
					checking = 0;
					dir = 0;
					return true;
				}

			}


			if (dir == 0)
			{

				if (initialCell.second > 0)
				{
					cell.first = initialCell.first;
					cell.second = initialCell.second - 1;

				}
				else
				{
					oppAttack = false;
					attackingMode = false;
					checkCounter = 0;
					checking = 0;
					dir = 0;
					return true;
				}


			}
			else if (dir == 1)
			{

				if (initialCell.second < 9)
				{
					cell.first = initialCell.first;
					cell.second = initialCell.second + 1;

				}
				else
				{
					oppAttack = false;
					attackingMode = false;
					checkCounter = 0;
					checking = 0;
					dir = 0;
					return true;
				}
			}
			else if (dir == 2)
			{

				if (initialCell.first > 0)
				{
					cell.first = initialCell.first - 1;
					cell.second = initialCell.second;

				}
				else
				{
					oppAttack = false;
					attackingMode = false;
					checkCounter = 0;
					checking = 0;
					dir = 0;
					return true;
				}

			}
			else if (dir == 3)
			{

				if (initialCell.first < 9)
				{
					cell.first = initialCell.first + 1;
					cell.second = initialCell.second;

				}
				else
				{
					oppAttack = false;
					checkCounter = 0;
					attackingMode = false;
					checking = 0;
					dir = 0;
					return true;
				}

			}
			else
				std::cout << "Error in bounds on line 1883\n";

			if (userTiles[cell.first][cell.second]->isAlreadySelected == false)
			{
				if (userTiles[cell.first][cell.second]->isShip == true)
				{

					userTiles[cell.first][cell.second]->isHit = true;
					CompBlast(cell.first, cell.second);
					userTiles[cell.first][cell.second]->isAlreadySelected = true;
					oppAttack = true;
					checking = 3;
					attackingMode = true;
					correctDir = true;
					initialCell = cell;
					return true;
				}
				else {
					attackingMode = false;
					userTiles[cell.first][cell.second]->isAlreadySelected = true;
					CompSplash(cell.first, cell.second);
					oppAttack = false;
					checking = 0;
					dir = 0;
					checkCounter = 0;
					correctDir = false;
					return false;

				}
			}
			else {
				attackingMode = false;
				userTiles[cell.first][cell.second]->isAlreadySelected = true;
				CompSplash(cell.first, cell.second);
				oppAttack = false;
				checking = 0;
				checkCounter = 0;
				dir = 0;
				correctDir = false;
				return true;
			}
		}
	}

	bool CompTurn() {
		if (!attackingMode)
		{

			srand(time(0));

			cell.first = rand() % 10;
			cell.second = rand() % 10;
			initialCell = cell;
			if (userTiles[cell.first][cell.second]->isAlreadySelected == true)
			{
				return true;
			}
			else
			{
				if (userTiles[cell.first][cell.second]->isShip == true)
				{

					userTiles[cell.first][cell.second]->isHit = true;
					CompBlast(cell.first, cell.second);
					userTiles[cell.first][cell.second]->isAlreadySelected = true;

					attackingMode = true;
					lastCell = cell;
					dir = 0;
					return true;


				}
				else if (userTiles[cell.first][cell.second]->isShip == false) {
					attackingMode = false;
					userTiles[cell.first][cell.second]->isAlreadySelected = true;

					CompSplash(cell.first, cell.second);

					return false;
				}
			}
		}
		else if (attackingMode)
			return (AIBasedAttack());

	}


	/* Computer blasting */
	void CompBlast(int row, int col)
	{

		compBlast.shape.setPosition(userTiles[row][col]->sprite.getPosition().x + 5, userTiles[row][col]->sprite.getPosition().y + 5);

		compBlast.StartAnimation();
	}
	/* Computer splash */
	void CompSplash(int row, int col)
	{

		compSplash.shape.setPosition(userTiles[row][col]->sprite.getPosition().x + 5, userTiles[row][col]->sprite.getPosition().y + 5);

		compSplash.StartAnimation();
	}
	/* check who wins */
	bool UserWin()
	{
		for (int i = 0; i < gridLength; i++)
		{
			for (int j = 0; j < gridLength; j++)
			{
				if (compTiles[i][j]->isShip && !compTiles[i][j]->isAlreadySelected)
					return false;
			}
		}

		return true;
	}
	bool CompWin()
	{
		for (int i = 0; i < gridLength; i++)
		{
			for (int j = 0; j < gridLength; j++)
			{
				if (userTiles[i][j]->isShip && !userTiles[i][j]->isAlreadySelected)
					return false;
			}
		}

		return true;
	}

	/* can be display */
	void CanBeDisplay()
	{
		int idCount[5] = { 0,0,0,0,0 };
		for (int i = 0; i < gridLength; i++)
		{
			for (int j = 0; j < gridLength; j++)
			{
				/*std::cout << compTiles[i][j]->id << std::endl;*/
				if (compTiles[i][j]->isShip && !compTiles[i][j]->isAlreadySelected && compTiles[i][j]->id == 0)
				{
					idCount[0]++;

				}
				if (compTiles[i][j]->isShip && !compTiles[i][j]->isAlreadySelected && compTiles[i][j]->id == 1)
				{
					idCount[1]++;
				}
				if (compTiles[i][j]->isShip && !compTiles[i][j]->isAlreadySelected && compTiles[i][j]->id == 2)
				{
					idCount[2]++;
				}
				if (compTiles[i][j]->isShip && !compTiles[i][j]->isAlreadySelected && compTiles[i][j]->id == 3)
				{
					idCount[3]++;
				}
				if (compTiles[i][j]->isShip && !compTiles[i][j]->isAlreadySelected && compTiles[i][j]->id == 4)
				{
					idCount[4]++;
				}
			}
		}


		for (int i = 0; i < 5; i++)
		{
			if (idCount[i] == 0)
			{
				compBoats[i].canDisplay = true;
			}
		}
	}
};
#endif // !BATTLESHIP_HF