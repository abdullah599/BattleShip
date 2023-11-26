/* Header Files */
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include"Battleship.h"
#include<iostream>
#include<vector>
#include<random>

/* Main Function */
int main()
{
restart:
	Blast blast;
	bool userTurn = true;
	Splash splash;

	/* Main Menu */
	auto image = sf::Image{};
	if (!image.loadFromFile("images/icon.jpeg"))
	{
		cout << "Error while loading icon";
	}

	sf::RenderWindow window(sf::VideoMode(1280, 720), "Battleship", sf::Style::Close);
	window.clear();
	window.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());
	sf::Event menuEvent;
	sf::Texture mainTexture;
	sf::Texture playTexture;
	sf::Texture quitTexture;

	sf::Sprite mainSprite;
	sf::Sprite playButton;
	sf::Sprite quitButton;

	mainTexture.loadFromFile("images/main menu.png");
	mainSprite.setTexture(mainTexture);
	playTexture.loadFromFile("images/playPic.png");
	playButton.setTexture(playTexture);
	quitTexture.loadFromFile("images/quitPic.png");
	quitButton.setTexture(quitTexture);


	playButton.setScale(.4, .4);
	quitButton.setScale(.4, .4);

	playButton.setPosition(50, 400);
	quitButton.setPosition(50, 550);

	while (window.isOpen())
	{
		while (window.pollEvent(menuEvent))
		{
			if (menuEvent.type == sf::Event::Closed)
			{
				window.close();
			}
			else if (menuEvent.type == sf::Event::MouseMoved)
			{
				sf::Vector2i mousePos = sf::Mouse::getPosition(window);
				sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

				/* Changing Size on hovering mouse */
				if (playButton.getGlobalBounds().contains(mousePosF))
				{
					Vector2f pos;
					pos.x = playButton.getLocalBounds().width / 2;
					pos.y = playButton.getLocalBounds().height / 2;
					playButton.setOrigin(pos);
					playButton.setPosition(170, 450);
					playButton.setScale(.35, .35);
				}
				else
				{
					playButton.setScale(.4, .4);
				}
				if (quitButton.getGlobalBounds().contains(mousePosF))
				{
					Vector2f pos;
					pos.x = quitButton.getLocalBounds().width / 2;
					pos.y = quitButton.getLocalBounds().height / 2;
					quitButton.setOrigin(pos);
					quitButton.setPosition(170, 600);
					quitButton.setScale(.35, .35);
				}
				else
				{
					quitButton.setScale(.4, .4);
				}
			}
			else if (sf::Event::MouseButtonPressed)
			{
				sf::Vector2i mousePos = sf::Mouse::getPosition(window);
				sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

				/* Mouse press on Play */
				if (playButton.getGlobalBounds().contains(mousePosF))
				{
					goto startGame;
				}

				/* Mouse press on QUIT */
				if (quitButton.getGlobalBounds().contains(mousePosF))
				{
					exit(0);
				}
			}
		}

		window.clear();

		window.draw(mainSprite);
		window.draw(playButton);
		window.draw(quitButton);
		window.display();
	}

startGame:
	
	sf::Event evnt;
	

	/* Main game objects */
	Battleship battleship;

	/* Game Loop */
	while (window.isOpen())
	{

		while (window.pollEvent(evnt)) {

			if (evnt.type == sf::Event::Closed) {

				window.close();
			}
		}

		/* Keys Controls */
		if (Event::EventType::KeyPressed)
		{
			while (1)
			{
				if (battleship.numberOfBoats <= 5)
				{
					/* For rotation from horizontal to vertical and vice versa */
					if (Keyboard::isKeyPressed(Keyboard::Key::R))
					{
						battleship.Rotate();
						break;
					}
					
					/* Boat Movement */ 
					if (Keyboard::isKeyPressed(Keyboard::Key::Right))
					{
						battleship.Right();
						break;
					}
					else if (Keyboard::isKeyPressed(Keyboard::Key::Left))
					{
						battleship.Left();
						break;
					}
					else if (Keyboard::isKeyPressed(Keyboard::Key::Down))
					{
						battleship.Down();
						break;
					}
					else if (Keyboard::isKeyPressed(Keyboard::Key::Up))
					{
						battleship.Up();
						break;
					}
					else if (Keyboard::isKeyPressed(Keyboard::Key::Enter))
					{
						battleship.ShipPlacement();


						sf::sleep(sf::milliseconds(200));
						battleship.numberOfBoats++;
						sf::sleep(sf::milliseconds(500));
						break;
					}

					break;
				}
				else
				{
					if (userTurn)
					{
						/* Set user's cursor on computer tiles */
						battleship.SetUpCompPos();

						/* Movement for bomb placement */
						if (Keyboard::isKeyPressed(Keyboard::Key::Right))
						{
							battleship.MoveRight();
							blast.MoveRight();
							splash.MoveRight();
							sf::sleep(sf::milliseconds(175));
							break;
						}
						else if (Keyboard::isKeyPressed(Keyboard::Key::Left))
						{
							battleship.MoveLeft();
							blast.MoveLeft();
							splash.MoveLeft();
							sf::sleep(sf::milliseconds(175));
							break;
						}
						else if (Keyboard::isKeyPressed(Keyboard::Key::Down))
						{
							battleship.MoveDown();
							blast.MoveDown();
							splash.MoveDown();
							sf::sleep(sf::milliseconds(175));
							break;
						}
						else if (Keyboard::isKeyPressed(Keyboard::Key::Up))
						{
							battleship.MoveUp();
							blast.MoveUp();
							splash.MoveUp();
							sf::sleep(sf::milliseconds(175));
							break;
						}
						else if (Keyboard::isKeyPressed(Keyboard::Key::Enter))
						{
							/* Animate blast only if there's a boat */
							if (battleship.IsShip(blast.shape.getPosition().x, blast.shape.getPosition().y)) {
								blast.StartAnimation();
							}
							else if (!blast.animation&& battleship.IsSplash(splash.shape.getPosition().x, splash.shape.getPosition().y)) {
								splash.StartAnimation();
							}

							battleship.isHit(userTurn);
						}
					}
					else if (splash.frameCounter == 0)
					{
						if (battleship.compBlast.frameCounter == 0 && battleship.compSplash.frameCounter == 0)
						{
							if (!battleship.CompTurn())
							{
								sf::sleep(sf::milliseconds(1200));
								userTurn = true;
							}
						}
					}

					if (battleship.compBlast.frameCounter == 0)
					{
						sf::Event endEvent;
					
						sf::Texture endTexture;
						sf::Texture restartTexture;
						sf::Sprite restartButton;

						restartTexture.loadFromFile("images/restartPic.png");
						restartButton.setTexture(restartTexture);

						restartButton.setScale(.4, .4);
						restartButton.setPosition(50, 400);

						/* You Won Menu */
						if (battleship.UserWin())
						{

							endTexture.loadFromFile("images/youWon.png");
							sf::Sprite youWon;
							youWon.setTexture(endTexture);
							sf::Event endEvent;

							/* You Won Loop */
							while (window.isOpen())
							{
								while (window.pollEvent(endEvent))
								{
									if (endEvent.type == sf::Event::Closed)
									{
										window.close();
									}
									else if (endEvent.type == sf::Event::MouseMoved)
									{
										sf::Vector2i mousePos = sf::Mouse::getPosition(window);
										sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

										/* Changing Size on hovering mouse */
										if (restartButton.getGlobalBounds().contains(mousePosF))
										{
											Vector2f pos;
											pos.x = restartButton.getLocalBounds().width / 2;
											pos.y = restartButton.getLocalBounds().height / 2;
											restartButton.setOrigin(pos);
											restartButton.setPosition(170, 450);
											restartButton.setScale(.35, .35);
										}
										else
										{
											restartButton.setScale(.4, .4);
										}
										if (quitButton.getGlobalBounds().contains(mousePosF))
										{
											Vector2f pos;
											pos.x = quitButton.getLocalBounds().width / 2;
											pos.y = quitButton.getLocalBounds().height / 2;
											quitButton.setOrigin(pos);
											quitButton.setPosition(170, 600);
											quitButton.setScale(.35, .35);
										}
										else
										{
											quitButton.setScale(.4, .4);
										}
									}
									else if (sf::Event::MouseButtonPressed)
									{
										sf::Vector2i mousePos = sf::Mouse::getPosition(window);
										sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

										/* Mouse press on restart */
										if (playButton.getGlobalBounds().contains(mousePosF))
										{
											goto restart;
										}

										/* Mouse press on QUIT */
										if (quitButton.getGlobalBounds().contains(mousePosF))
										{
											exit(0);
										}
									}

									/* Drawing you won menu */
									window.clear();
									window.draw(youWon);
									window.draw(restartButton);
									window.draw(quitButton);
									window.display();
								}
							}
						}
						/* Game Over Menu */
						else if (battleship.CompWin())
						{
							
							endTexture.loadFromFile("images/gameOver.png");
							sf::Sprite gameOver;
							gameOver.setTexture(endTexture);
							sf::Event endEvent;

							/* Game Over Loop */
							while (window.isOpen())
							{
								while (window.pollEvent(endEvent))
								{
									if (endEvent.type == sf::Event::Closed)
									{
										window.close();
									}
									else if (endEvent.type == sf::Event::MouseMoved)
									{
										sf::Vector2i mousePos = sf::Mouse::getPosition(window);
										sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

										/* Changing Size on hovering mouse */
										if (restartButton.getGlobalBounds().contains(mousePosF))
										{
											Vector2f pos;
											pos.x = restartButton.getLocalBounds().width / 2;
											pos.y = restartButton.getLocalBounds().height / 2;
											restartButton.setOrigin(pos);
											restartButton.setPosition(170, 450);
											restartButton.setScale(.35, .35);
										}
										else
										{
											restartButton.setScale(.4, .4);
										}
										if (quitButton.getGlobalBounds().contains(mousePosF))
										{
											Vector2f pos;
											pos.x = quitButton.getLocalBounds().width / 2;
											pos.y = quitButton.getLocalBounds().height / 2;
											quitButton.setOrigin(pos);
											quitButton.setPosition(170, 600);
											quitButton.setScale(.35, .35);
										}
										else
										{
											quitButton.setScale(.4, .4);
										}
									}
									else if (sf::Event::MouseButtonPressed)
									{
										sf::Vector2i mousePos = sf::Mouse::getPosition(window);
										sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

										/* Mouse press on restart */
										if (playButton.getGlobalBounds().contains(mousePosF))
										{
											
										}

										/* Mouse press on QUIT */
										if (quitButton.getGlobalBounds().contains(mousePosF))
										{
											exit(0);
										}
									}

									/* Drawing game over menu */
									window.clear();
									window.draw(gameOver);
									window.draw(restartButton);
									window.draw(quitButton);
									window.display();
								}
									
							}
						}
					}
				}
				break;
			}

			/* Checking if blast has to be animated */
			if (blast.animation == true)
			{
				sf::sleep(sf::milliseconds(120));
				blast.Animate();
			}
			/* Checking if splash has to be animated */
			if (splash.animation == true)
			{
				sf::sleep(sf::milliseconds(120));
				splash.Animate();
			}
			/* Checking if compBlast has to be animated */
			if (battleship.compBlast.animation == true)
			{
				sf::sleep(sf::milliseconds(120));
				battleship.compBlast.Animate();
			}
			/* Checking if compSplash has to be animated */
			if (battleship.compSplash.animation == true)
			{
				sf::sleep(sf::milliseconds(120));
				battleship.compSplash.Animate();
			}
		}


		/* Update */
		window.clear();
		battleship.Update();


		/* Drawing name and background */
		window.draw(battleship.background);
		window.draw(battleship.name);

		/* Drawing User Grid */
		for (int i = 0; i < battleship.gridLength; i++)
		{
			for (int j = 0; j < battleship.gridLength; j++)
			{
				window.draw(battleship.userTiles[i][j]->sprite);
			}
		}
		
		/* Drawing Computer Grid */
		for (int i = 0; i < battleship.gridLength; i++)
		{
			for (int j = 0; j < battleship.gridLength; j++)
			{
				window.draw(battleship.compTiles[i][j]->sprite);
			}
		}

		for (int i = 0; i < battleship.numberOfBoats; i++)
		{
			if (i == 5)
				window.draw(battleship.userBoats[4].boatPic);
			else
				window.draw(battleship.userBoats[i].boatPic);
		}

		/* drawing compBoats if it is completed destroyed */
		for (int i = 0; i < 5; i++)
		{
			if (battleship.compBoats[i].canDisplay)
				window.draw(battleship.compBoats[i].boatPic);
		}

		/* Displaying blast on blast */
		if (blast.animation)
		{
			window.draw(blast.shape);
		}

		if (battleship.compBlast.animation)
		{
			window.draw(battleship.compBlast.shape);
		}

		/* Displaying water splash on blast */
		if (splash.animation)
		{
			window.draw(splash.shape);
		}

		if (battleship.compSplash.animation)
		{
			window.draw(battleship.compSplash.shape);
		}
		window.display();
	}

	return 0;
}