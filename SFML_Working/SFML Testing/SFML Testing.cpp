#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>

//The height and length of the grid
int heightCount = 10; // vertical count
int widthCount = 10; //horizontal count

int pixelSize = 16; //size of a pixel
int height = pixelSize * heightCount; //making background pixels
int width = pixelSize * widthCount; // making background pixels

int random; //random number to simulate encounters

bool upFlag; //if player is moving up
bool downFlag; // if player is moving down
bool leftFlag; // if player is moving left
bool rightFlag; // if player is moving right
bool encounter; //flag is for random encounter
bool isMoving; //flag for when player is moving
				
//struct for human 
struct Player
{
	int x;
	int y; 
}player[1]; //the human only takes one pixel cordinate


//move for the human to move to different spaces
void move()
{
	//if player does not move
	//if player does nothing cordinates do not change
	//if user inputs up
	
	if (upFlag) 
	{
		player[0].y = player[0].y - 1;
		upFlag = false; //once moved resets direction value
		//Ensures no other movement is taken
		downFlag = false;
		leftFlag = false;
		rightFlag = false;
		random = (rand() % 100) + 1; //gets random number between 1-100

		if (random < 50) // sets rate to occur at 50%
		{
			std::cout << "Encounter happened";
		}
	}
	//if user presses down
	else if (downFlag) 
	{
		player[0].y = player[0].y + 1;
		downFlag = false; //reset flag
		upFlag = false;
		leftFlag = false;
		rightFlag = false;
		random = (rand() % 100) + 1; //gets random number between 1-100

		if (random < 50)
		{
			std::cout << "Encounter happened";
		}
	}
	//if user presses left
	else if (leftFlag)
	{
		player[0].x = player[0].x - 1;
		leftFlag = false; //reset flag
		downFlag = false;
		upFlag = false;
		rightFlag = false;
		random = (rand() % 100) + 1; //gets random number between 1-100
		if (random < 50)
		{
			std::cout << "Encounter happened";
		}
	}
	//if user presses right
	else if (rightFlag)
	{
		player[0].x = player[0].x + 1;
		rightFlag = false; //reset flag
		downFlag = false;
		leftFlag = false;
		upFlag = false;
		random = (rand() % 100) + 1; //gets random number between 1-100
		if (random < 50)
		{
			std::cout << "Encounter happened";
		}
	}
	
	//can add wall collision

	//can add wall generator here 
	
}

//launches the move function by checking if player is moving
void moving()
{
	//player is moving
	if (isMoving)
	{
		//resets movement state
		isMoving = false;
		move();
	}
}

int main()
{
	//Window to play the game in set to be as large as the pixels displaying name.
	sf::RenderWindow window(sf::VideoMode(width, height,16), "Grid Test");
	sf::Texture human, map, wall;
	sf::Texture test;
	sf::RenderWindow background(sf::VideoMode(400, 400, 1), "Background");
												//start in x and y width and height
	test.loadFromFile("images/Player.png", sf::IntRect(0,64,64,64)); //loads player test
	map.loadFromFile("images/white.png"); //loads white for map tiles
	human.loadFromFile("images/red.png"); //loads red for human
	//wall.loadFromFile("images/green.png");
	//add wall pixels to with collsion

	//takes the loaded image and makes sprites
	sf::Sprite mapSprite(map); //grid tiles
	sf::Sprite humanSprite(human); //human spot
	sf::Sprite testSprit(test);
	//sf::Sprite wallSprite(wall); //wall spot
	testSprit.setPosition(0, 0);
	//Place human into inital spot
	player[0].x = 0;
	player[0].y = 0;

	//adds a clock
	sf::Clock clock;
	float timer = 0.0f;
	float delay = 0.6f;

	while (window.isOpen())
	{
		//check how this works
		float time = clock.getElapsedTime().asSeconds();

		clock.restart(); //resets the time after getting time 

		timer = timer + time; //updating the timer with time as passed

		//names the event userInput
		sf::Event exit;
		while (window.pollEvent(exit))
		{
			//if user closes the window
			if (exit.type == sf::Event::Closed)
				window.close();
			//Event for pressed key
			//when user input is not inputed anymore
		}
		while (background.pollEvent(exit)) 
		{
			if (exit.type == sf::Event::Closed)
				background.close();
		}
	
		//controls for player
		//Sets a flag to move
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			isMoving = true;
			upFlag = true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) 
		{
			isMoving = true;
			downFlag = true; 
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) 
		{ 
			isMoving = true;
			leftFlag = true; 
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) 
		{ 
			isMoving = true;
			rightFlag = true; 
		}
		if (timer > delay) //every delay or frame
		{
			timer = 0; //resets timer
			moving(); //calls move functions
		}
		//draws the state 

		window.clear(); // clears window of previous pictures
		//window.draw(shape); // draws shape
		background.clear();
		background.draw(testSprit);
		background.display();
		//draw the pixels for grid background
		for (int i = 0; i < widthCount; i++)
		{
			for (int j = 0; j < heightCount; j++) 
			{
				//sets the position of each sprite pixel by pixel
				mapSprite.setPosition(i*pixelSize, j*pixelSize);
				window.draw(mapSprite);
			}
		}

		//draw the human onto the map
		humanSprite.setPosition(player[0].x*pixelSize, player[0].y*pixelSize);
		//wallSprite.setPosition(player[0].x*pixelSize, (player[0].y*pixelSize) - 16); //16 is how many pixels apart it is
		window.draw(humanSprite);
		//window.draw(wallSprite);
		window.display(); //displays all images
	}
	return 0;
}