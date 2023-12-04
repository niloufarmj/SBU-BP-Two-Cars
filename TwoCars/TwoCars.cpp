#include "stdafx.h"
#include "SBDL.h"
#include <time.h>
#include <iostream>

using namespace std;

enum Command
{
	Play, Home, GameOver, Pause
};

struct Core {
	int y;
	int x;
};

const int windowWidth = 440;
const int windowHeight = 748;
const int FPS = 60; //frame per second
const int delay = 1000 / FPS; //delay we need at each frame
const int totalCurrentItems = 4;

Texture back;
Texture redCarPic;
Texture blueCarPic;
Texture blueRect;
Texture blueCir;
Texture redRect;
Texture redCir;
Texture pause;
Texture blackBack;
Texture play;
Texture home;
Texture gameover;
Texture blueObstacle[totalCurrentItems];
Texture redObstacle[totalCurrentItems];

Sound* scoreSound;
Sound* dieMissSound;
Sound* dieCollapseSound;


int velocity = 4;
int score = 0;


int elapsedTime, startTime;
int i;
int which_obs_blue[totalCurrentItems / 2];
int which_obs_red[totalCurrentItems / 2];
int blue_o_y[totalCurrentItems / 2];
int red_o_y[totalCurrentItems / 2];
int blue_x[2] = { 26 , 135 };
int red_x[2] = { 245 , 355 };
int which_x_blue[totalCurrentItems / 2];
int which_x_red[totalCurrentItems / 2];
int blueCar_x = 25;
int redCar_x = 355;

SDL_Rect backRect = { 0,0,windowWidth ,windowHeight };
SDL_Rect pauseRect = { 15 , 15 , 30 , 40 };
SDL_Rect blueCarRect = { blueCar_x , 540 , 60 , 110 };
SDL_Rect redCarRect = { redCar_x , 540 , 60 , 110 };
SDL_Rect playRect = { 200 , 350 , 150 , 150 };
SDL_Rect blueObstacleRect[totalCurrentItems / 2];
SDL_Rect redObstacleRect[totalCurrentItems / 2];

Command currentCommand = Home;

void loadAssets();
void initialize();
void moveCars();
void showHomePage();
void showGameoverPage();
void showPausePage();
void playGame();
void handleCommand();

int main(int argc, char *argv[])
{
	SBDL::InitEngine("Two Cars", windowWidth, windowHeight);

	loadAssets();
	srand(time(NULL));

	while (SBDL::isRunning())
	{
		startTime = SBDL::getTime();
		handleCommand();
		elapsedTime = SBDL::getTime() - startTime;
		if (elapsedTime < delay)
			SBDL::delay(delay - elapsedTime);
	}
}

void loadAssets() 
{
	//loading assets
	back = SBDL::loadTexture("assets/Background.png");
	redCarPic = SBDL::loadTexture("assets/Cars/RedCar.png");
	blueCarPic = SBDL::loadTexture("assets/Cars/BlueCar.png");
	blueRect = SBDL::loadTexture("assets/Obstacle/BlueRect.png");
	blueCir = SBDL::loadTexture("assets/Obstacle/BlueCircle.png");
	redRect = SBDL::loadTexture("assets/Obstacle/RedRect.png");
	redCir = SBDL::loadTexture("assets/Obstacle/RedCircle.png");
	pause = SBDL::loadTexture("assets/Pause.png");
	blackBack = SBDL::loadTexture("assets/blackback.png");
	play = SBDL::loadTexture("assets/Button/Play.png");
	home = SBDL::loadTexture("assets/Button/Home.png");
	gameover = SBDL::loadTexture("assets/GameOverBackground.png");
	scoreSound = SBDL::loadSound("assets/Sounds/score.wav");
	dieCollapseSound = SBDL::loadSound("assets/sounds/die1.wav");
	dieMissSound = SBDL::loadSound("assets/sounds/die2.wav");
	//finish loading assets

	for (i = 0; i < totalCurrentItems; i++) 
		if (i < totalCurrentItems / 2) {
			blueObstacle[i] = blueRect;
			redObstacle[i] = redRect;
		}
		else {
			blueObstacle[i] = blueCir;
			redObstacle[i] = redCir;
		}
		
}

void initialize()
{
	blueCar_x = 25;
	redCar_x = 355;

	for (i = 0; i < totalCurrentItems / 2; i++) {
		which_obs_blue[i] = rand() % totalCurrentItems;
		which_obs_red[i] = rand() % totalCurrentItems;
		blue_o_y[i] = -150 - 350 * i;
		red_o_y[i] = -100 - 350 * i;
		which_x_blue[i] = rand() % 2;
		which_x_red[i] = rand() % 2;
	}
}

void moveCars()
{
	if (SBDL::keyPressed(SDL_SCANCODE_LEFT))
	{
		blueCar_x = blueCar_x == 25 ? 135 : 25;
		playGame();
	}
	if (SBDL::keyPressed(SDL_SCANCODE_RIGHT))
	{
		redCar_x = redCar_x == 355 ? 245 : 355;
		playGame();
	}
}

void showHomePage()
{
	SDL_Rect playRect = { 145 , 300 , 150 , 150 };
	SDL_Rect blackBackRect = { 0, 0, windowWidth, windowHeight };

	SBDL::showTexture(blackBack, blackBackRect);
	SBDL::showTexture(play, playRect);
	SBDL::updateRenderScreen();
	SBDL::updateEvents();

	if (SBDL::mouseInRect(playRect) && SBDL::Mouse.clicked())
	{
		initialize();
		currentCommand = Play;
	}

}

void showGameoverPage()
{
	SDL_Rect gameoverRect = { 0 , 0 , windowWidth , windowHeight };
	SDL_Rect retryRect = { 165 , 375 , 125 , 125 };
	SDL_Rect newHomeRect = { 140 , 537 , 67 , 67 };
	SBDL::showTexture(gameover, gameoverRect);
	SBDL::updateRenderScreen();
	SBDL::updateEvents();

	if (SBDL::mouseInRect(retryRect) && SBDL::Mouse.clicked())
	{
		SBDL::updateEvents();
		SBDL::updateRenderScreen();
		currentCommand = Play;
	}
	if (SBDL::mouseInRect(newHomeRect) && SBDL::Mouse.clicked())
	{
		SBDL::updateEvents();
		SBDL::updateRenderScreen();
		currentCommand = Home;
	}
}

void showPausePage()
{
	SDL_Rect blackBackRect = { 0,0,windowWidth ,windowHeight };
	SDL_Rect playRect = { 240 , 320 , 80 , 80 };
	SDL_Rect homeRect = { 125 , 320 , 80 , 80 };
	SBDL::showTexture(blackBack, blackBackRect);
	SBDL::showTexture(play, playRect);
	SBDL::showTexture(home, homeRect);
	SBDL::updateRenderScreen();
	SBDL::updateEvents();
	if (SBDL::mouseInRect(playRect) && SBDL::Mouse.clicked())
	{
		SBDL::updateRenderScreen();
		currentCommand = Play;
	}
	if (SBDL::mouseInRect(homeRect) && SBDL::Mouse.clicked())
	{
		currentCommand = Home;
		SBDL::updateRenderScreen();
	}
}

void playGame()
{
	backRect = { 0,0,windowWidth ,windowHeight };
	pauseRect = { 15 , 15 , 30 , 40 };
	SBDL::updateEvents();
	moveCars();
	blueCarRect = { blueCar_x , 540 , 60 , 110 };
	redCarRect = { redCar_x , 540 , 60 , 110 };
	playRect = { 200 , 350 , 150 , 150 };
	SBDL::showTexture(back, backRect);
	SBDL::showTexture(blueCarPic, blueCarRect);
	SBDL::showTexture(redCarPic, redCarRect);
	SBDL::showTexture(pause, pauseRect);
	elapsedTime = SBDL::getTime() - startTime;
	if (elapsedTime < delay)
		SBDL::delay(delay - elapsedTime);

	for (i = 0; i < totalCurrentItems / 2; i++)
	{
		blueObstacleRect[i] = { blue_x[which_x_blue[i]], blue_o_y[i] , 60 , 60 };
		SBDL::showTexture(blueObstacle[which_obs_blue[i]], blueObstacleRect[i]);
		blue_o_y[i] += velocity;
		redObstacleRect[i] = { red_x[which_x_red[i]], red_o_y[i] , 60 , 60 };
		SBDL::showTexture(redObstacle[which_obs_red[i]], redObstacleRect[i]);
		red_o_y[i] += velocity;
	}

	for (i = 0; i < totalCurrentItems / 2; i++)
	{
		if (SBDL::hasIntersectionRect(blueCarRect, blueObstacleRect[i]) && (which_obs_blue[i] < totalCurrentItems / 2))
		{
			currentCommand = GameOver;
			SBDL::playSound(dieCollapseSound, 1);
		}
		if (SBDL::hasIntersectionRect(redCarRect, redObstacleRect[i]) && (which_obs_red[i] < totalCurrentItems / 2))
		{
			currentCommand = GameOver;
			SBDL::playSound(dieCollapseSound, 1);
		}
		if (SBDL::hasIntersectionRect(blueCarRect, blueObstacleRect[i]) && (which_obs_blue[i] >= totalCurrentItems / 2))
		{
			SBDL::playSound(scoreSound, 1);
			blue_o_y[i] = -50;
			score++;
		}
		if (SBDL::hasIntersectionRect(redCarRect, redObstacleRect[i]) && (which_obs_red[i] >= totalCurrentItems / 2))
		{
			SBDL::playSound(scoreSound, 1);
			red_o_y[i] = -50;
			score++;
		}
	}

	for (i = 0; i < totalCurrentItems / 2; i++)
	{
		if (blue_o_y[i] > 730)
		{
			if (which_obs_blue[i] >= totalCurrentItems / 2)
			{
				currentCommand = GameOver;
				SBDL::playSound(dieMissSound, 1);
			}
			else
			{
				which_obs_blue[i] = rand() % totalCurrentItems;
				blue_o_y[i] = -35;
				which_x_blue[i] = rand() % 2;

			}
		}
		if (red_o_y[i] > 730)
		{
			if (which_obs_red[i] >= totalCurrentItems / 2)
			{
				currentCommand = GameOver;
				SBDL::playSound(dieMissSound, 1);
			}
			else
			{
				which_obs_red[i] = rand() % totalCurrentItems;
				red_o_y[i] = -35;
				which_x_red[i] = rand() % 2;

			}
		}
	}
	SBDL::updateRenderScreen();

	if (SBDL::mouseInRect(pauseRect) && SBDL::Mouse.clicked())
	{
		currentCommand = Pause;
	}
}

void handleCommand()
{
	switch (currentCommand)
	{
	case Play:
	{
		playGame();
		break;
	}
	case Home:
	{
		initialize();
		showHomePage();
		break;
	}
	case GameOver:
	{
		initialize();
		showGameoverPage();
		break;
	}
	case Pause:
	{
		showPausePage();
		break;
	}
	}
}