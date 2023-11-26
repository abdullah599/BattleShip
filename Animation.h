#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
using namespace std;

/* Animation Class */
class Animation
{
protected:
	/* Data Members */
	sf::Vector2f pos;
	sf::SoundBuffer buffer;
	sf::Sound sound;
	sf::Vector2u img;
	sf::Texture texture;
public:
	int frameCounter;
	bool animation;
	sf::RectangleShape shape;
	/* Constructor */
	Animation()
	{
		pos.x = 735;
		pos.y = 305;
		shape.setPosition(pos.x, pos.y);
		frameCounter = 0;
		shape.setSize(sf::Vector2f(35.0f, 35.0f));
		animation = false;
	}

	/* Setter Functions */
	void setEachImage(int x, int y)
	{
		img = texture.getSize();
		img.x /= x;
		img.y /= y;
	}

	void setTexture(string fileName)
	{
		texture.loadFromFile(fileName);
		shape.setTexture(&texture);
	}

	void setBuffer(string fileName)
	{
		buffer.loadFromFile(fileName);
		sound.setBuffer(buffer);
	}

	/* Getter Functions */
	float getX()
	{
		return pos.x;
	}
	float getY()
	{
		return pos.y;
	}

	/* Movement */
	void MoveRight()
	{
		pos.x += 40;

		if (pos.x > 1095)
			pos.x = 735;

		shape.setPosition(pos.x, pos.y);
	}
	void MoveLeft()
	{
		pos.x -= 40;

		if (pos.x < 735)
			pos.x = 1095;
		shape.setPosition(pos.x, pos.y);
	}
	void MoveDown()
	{
		pos.y += 40;

		if (pos.y > 665)
			pos.y = 305;
		shape.setPosition(pos.x, pos.y);
	}
	void MoveUp()
	{
		pos.y -= 40;

		if (pos.y < 305)
			pos.y = 665;
		shape.setPosition(pos.x, pos.y);
	}

	/* Start & Stop Animation Functions */
	void StartAnimation()
	{
		animation = true;
		sound.play();
	}

	void StopAnimation()
	{
		frameCounter = 0;
		animation = false;
	}
};

/* Blast Class inherited by Animation Class */
class Blast : public Animation
{
public:
	/* Constructor */
	Blast()
	{
		setTexture("images/blast.png");
		setBuffer("images/blastSound.wav");
		setEachImage(3, 2);
	}

	/* Animation by frame Function */
	void Animate()
	{

		frameCounter++;

		if (frameCounter == 1)
		{
			shape.setTextureRect(sf::IntRect(img.x * 0, img.y * 0, img.x, img.y));
		}
		else if (frameCounter == 2)
		{
			shape.setTextureRect(sf::IntRect(img.x * 1, img.y * 0, img.x, img.y));
		}
		else if (frameCounter == 3)
		{
			shape.setTextureRect(sf::IntRect(img.x * 2, img.y * 0, img.x, img.y));
		}
		else if (frameCounter == 4)
		{
			shape.setTextureRect(sf::IntRect(img.x * 0, img.y * 1, img.x, img.y));
		}
		else if (frameCounter == 5)
		{
			shape.setTextureRect(sf::IntRect(img.x * 1, img.y * 1, img.x, img.y));
		}
		else if (frameCounter == 6)
		{
			shape.setTextureRect(sf::IntRect(img.x * 2, img.y * 1, img.x, img.y));
		}
		else
		{
			StopAnimation();
		}
	}
};

/* Water Splash Class inherited by Animation class */
class Splash : public Animation
{
public:
	/* Constructor */
	Splash()
	{
		setTexture("images/splash.png");
		setBuffer("images/splashSound.wav");
		setEachImage(3, 2);
	}

	/* Animation by frame Function */
	void Animate()
	{
		frameCounter++;

		if (frameCounter == 1)
		{
			shape.setTextureRect(sf::IntRect(img.x * 0, img.y * 0, img.x, img.y));
		}
		else if (frameCounter == 2)
		{
			shape.setTextureRect(sf::IntRect(img.x * 1, img.y * 0, img.x, img.y));
		}
		else if (frameCounter == 3)
		{
			shape.setTextureRect(sf::IntRect(img.x * 2, img.y * 0, img.x, img.y));
		}
		else if (frameCounter == 4)
		{
			shape.setTextureRect(sf::IntRect(img.x * 0, img.y * 1, img.x, img.y));
		}
		else if (frameCounter == 5)
		{
			shape.setTextureRect(sf::IntRect(img.x * 1, img.y * 1, img.x, img.y));
		}
		else if (frameCounter == 6)
		{
			shape.setTextureRect(sf::IntRect(img.x * 2, img.y * 1, img.x, img.y));
		}
		else
		{
			StopAnimation();
		}
	}
};