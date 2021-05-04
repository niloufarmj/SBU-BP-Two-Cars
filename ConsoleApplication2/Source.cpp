#include "stdafx.h"
#include "SBDL.h"
#include <time.h>
#include <iostream>
enum command
{
	playit, homeit, gameoverit, pauseit
};
struct core {
	int y;
	int x;
};

using namespace std;

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
Sound* scoreSound;
Sound* dieMiss;
Sound* dieCollapse;
Texture blueObstacle[6];
Texture redObstacle[6];
const int window_width = 440;
const int window_height = 748;
int velocity = 5;
int score = 0;
const int FPS = 60; //frame per second
const int delay = 1000 / FPS; //delay we need at each frame
int elapsedTime, startTime;
int i;
int which_obs_blue[3];
int which_obs_red[3];
int blue_o_y[3];
int red_o_y[3];
int blue_x[2] = { 26 , 135 };
int red_x[2] = { 245 , 355 };
int which_x_blue[3];
int which_x_red[3];
int blueCar_x = 25;
int redCar_x = 355;
SDL_Rect backRect = { 0,0,window_width ,window_height };
SDL_Rect pauseRect = { 15 , 15 , 30 , 40 };
SDL_Rect blueCarRect = { blueCar_x , 540 , 60 , 110 };
SDL_Rect redCarRect = { redCar_x , 540 , 60 , 110 };
SDL_Rect playRect = { 200 , 350 , 150 , 150 };
SDL_Rect blueObstacleRect[3];
SDL_Rect redObstacleRect[3];
command chum = homeit;
void initializer();
void moveCar();
void homePage();
void gameoverPage();
void pausePage();
void playGame();
void what_to_do(command);

int main(int argc, char *argv[])
{
	//SBDL::InitEngine("SBDL Test", window_width, window_height);
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
	dieCollapse = SBDL::loadSound("assets/sounds/die1.wav");
	dieMiss = SBDL::loadSound("assets/sounds/die2.wav");
	//finish loading assets
	for (i = 0; i < 3; i++)
		blueObstacle[i] = blueRect;
	for (i = 3; i < 6; i++)
		blueObstacle[i] = blueCir;
	for (i = 0; i < 3; i++)
		redObstacle[i] = redRect;
	for (i = 3; i < 6; i++)
		redObstacle[i] = redCir;
	srand(time(NULL));

	while (SBDL::isRunning())
	{
		startTime = SBDL::getTime();
		what_to_do(chum);
		elapsedTime = SBDL::getTime() - startTime;
		if (elapsedTime < delay)
			SBDL::delay(delay - elapsedTime);
	}
}

void initializer()
{
	blueCar_x = 25;
	redCar_x = 355;
	for (i = 0; i < 3; i++)
	{
		which_obs_blue[i] = rand() % 6;
	}

	for (i = 0; i < 3; i++)
	{
		which_obs_red[i] = rand() % 6;
	}

	for (i = 0; i < 3; i++)
	{
		blue_o_y[i] = -50 - 250 * i;
	}

	for (i = 0; i < 3; i++)
	{
		red_o_y[i] = -100 - 250 * i;
	}

	for (i = 0; i < 3; i++)
	{
		which_x_blue[i] = rand() % 2;
	}

	for (i = 0; i < 3; i++)
	{
		which_x_red[i] = rand() % 2;
	}
}
void moveCar()
{
	if (SBDL::keyPressed(SDL_SCANCODE_LEFT))
	{

		if (blueCar_x == 25)
		{
			blueCar_x = 135;
			playGame();
		}
		else
		{
			blueCar_x = 25;
			playGame();
		}

	}
	if (SBDL::keyPressed(SDL_SCANCODE_RIGHT))
	{
		if (redCar_x == 355)
		{
			redCar_x = 245;
			playGame();
		}
		else
		{
			redCar_x = 355;
			playGame();
		}
	}
}
void homePage()
{
	SDL_Rect playRect = { 145 , 300 , 150 , 150 };
	SDL_Rect blackBackRect = { 0,0,window_width ,window_height };

	SBDL::showTexture(blackBack, blackBackRect);
	SBDL::showTexture(play, playRect);
	SBDL::updateRenderScreen();
	SBDL::updateEvents();

	if (SBDL::mouseInRect(playRect) && SBDL::Mouse.clicked())
	{
		initializer();
		chum = playit;
	}

}
void gameoverPage()
{
	SDL_Rect gameoverRect = { 0 , 0 , window_width , window_height };
	SDL_Rect retryRect = { 165 , 375 , 125 , 125 };
	SDL_Rect newHomeRect = { 140 , 537 , 67 , 67 };
	SBDL::showTexture(gameover, gameoverRect);
	SBDL::updateRenderScreen();
	SBDL::updateEvents();

	if (SBDL::mouseInRect(retryRect) && SBDL::Mouse.clicked())
	{
		SBDL::updateEvents();
		SBDL::updateRenderScreen();
		chum = playit;
	}
	if (SBDL::mouseInRect(newHomeRect) && SBDL::Mouse.clicked())
	{
		SBDL::updateEvents();
		SBDL::updateRenderScreen();
		chum = homeit;
	}
}
void pausePage()
{
	SDL_Rect blackBackRect = { 0,0,window_width ,window_height };
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
		chum = playit;
	}
	if (SBDL::mouseInRect(homeRect) && SBDL::Mouse.clicked())
	{
		chum = homeit;
		SBDL::updateRenderScreen();
	}
}
void playGame()
{
	backRect = { 0,0,window_width ,window_height };
	pauseRect = { 15 , 15 , 30 , 40 };
	SBDL::updateEvents();
	moveCar();
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

	for (i = 0; i < 3; i++)
	{
		blueObstacleRect[i] = { blue_x[which_x_blue[i]], blue_o_y[i] , 60 , 60 };
		SBDL::showTexture(blueObstacle[which_obs_blue[i]], blueObstacleRect[i]);
		blue_o_y[i] += velocity;
		redObstacleRect[i] = { red_x[which_x_red[i]], red_o_y[i] , 60 , 60 };
		SBDL::showTexture(redObstacle[which_obs_red[i]], redObstacleRect[i]);
		red_o_y[i] += velocity;
	}

	for (i = 0; i < 3; i++)
	{
		if (SBDL::hasIntersectionRect(blueCarRect, blueObstacleRect[i]) && (which_obs_blue[i] == 0 || which_obs_blue[i] == 1 || which_obs_blue[i] == 2))
		{
			chum = gameoverit;
			SBDL::playSound(dieCollapse, 1);
		}
		if (SBDL::hasIntersectionRect(redCarRect, redObstacleRect[i]) && (which_obs_red[i] == 0 || which_obs_red[i] == 1 || which_obs_red[i] == 2))
		{
			chum = gameoverit;
			SBDL::playSound(dieCollapse, 1);
		}
		if (SBDL::hasIntersectionRect(blueCarRect, blueObstacleRect[i]) && (which_obs_blue[i] == 3 || which_obs_blue[i] == 4 || which_obs_blue[i] == 5))
		{
			SBDL::playSound(scoreSound, 1);
			blue_o_y[i] = -50;
			score++;
		}
		if (SBDL::hasIntersectionRect(redCarRect, redObstacleRect[i]) && (which_obs_red[i] == 3 || which_obs_red[i] == 4 || which_obs_red[i] == 5))
		{
			SBDL::playSound(scoreSound, 1);
			red_o_y[i] = -50;
			score++;
		}
	}

	for (i = 0; i < 3; i++)
	{
		if (blue_o_y[i] > 730)
		{
			if (which_obs_blue[i] == 3 || which_obs_blue[i] == 4 || which_obs_blue[i] == 5)
			{
				chum = gameoverit;
				SBDL::playSound(dieMiss, 1);
			}
			else
			{
				which_obs_blue[i] = rand() % 6;
				blue_o_y[i] = -35;
				which_x_blue[i] = rand() % 2;

			}
		}
		if (red_o_y[i] > 730)
		{
			if (which_obs_red[i] == 3 || which_obs_red[i] == 4 || which_obs_red[i] == 5)
			{
				chum = gameoverit;
				SBDL::playSound(dieMiss, 1);
			}
			else
			{
				which_obs_red[i] = rand() % 6;
				red_o_y[i] = -35;
				which_x_red[i] = rand() % 2;

			}
		}
	}
	SBDL::updateRenderScreen();

	if (SBDL::mouseInRect(pauseRect) && SBDL::Mouse.clicked())
	{
		chum = pauseit;
	}
}
void what_to_do(command chum)
{
	switch (chum)
	{
	case playit:
	{
		playGame();
		break;
	}
	case homeit:
	{
		initializer();
		homePage();
		break;
	}
	case gameoverit:
	{
		initializer();
		gameoverPage();
		break;
	}
	case pauseit:
	{
		pausePage();
		break;
	}
	}
}