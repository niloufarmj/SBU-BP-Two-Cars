#include "stdafx.h"
#include "SBDL.h"
#include <time.h>
bool loss;
struct core {
	int y;
};
using namespace std;

int main(int argc, char *argv[])

{
	const int window_width = 440;
	const int window_height = 748;
	SBDL::InitEngine("SBDL Test", window_width, window_height);

	const int FPS = 60; //frame per second
	const int delay = 1000 / FPS; //delay we need at each frame

	Texture back = SBDL::loadTexture("assets/Background.png");
	Texture redCar = SBDL::loadTexture("assets/Cars/RedCar.png");
	Texture blueCar = SBDL::loadTexture("assets/Cars/BlueCar.png");
	Texture blueRect = SBDL::loadTexture("assets/Obstacle/BlueRect.png");
	Texture blueCir = SBDL::loadTexture("assets/Obstacle/BlueCircle.png");
	Texture redRect = SBDL::loadTexture("assets/Obstacle/RedRect.png");
	Texture redCir = SBDL::loadTexture("assets/Obstacle/RedCircle.png");
	Texture pause = SBDL::loadTexture("assets/Pause.png");
	Texture blueObstacles[6] = { blueRect,blueRect,blueRect,blueCir,blueCir,blueCir };
	Texture redObstacles[6] = { redRect,redRect,redRect,redCir,redCir,redCir };
	int blueObstaclePlace[2] = { 45,150 };
	int redObstaclePlace[2] = { 250,360 };

	int obstacleVelocity = 1;
	int score = 0;
	int bluePlace = -10;
	int redPlace = 10;
	while (SBDL::isRunning()) {
		srand(time(NULL));
		int anotherShomareArray = rand() % 2;
		int shomareArray = rand() % 6;
		int anotherShomareArray1 = rand() % 2;
		int shomareArray1 = rand() % 6;
		int startTime = SBDL::getTime();

		SBDL::updateEvents();
		SBDL::clearRenderScreen();
		core blueCar1;
		core redCar1;
		blueCar1.y = 540;
		redCar1.y = 540;
		SDL_Rect backRect = { 0,0,window_width ,window_height };
		SBDL::showTexture(back, backRect);
		SBDL::showTexture(blueCar, 25, blueCar1.y);
		SBDL::showTexture(redCar, 355, redCar1.y);
		SBDL::showTexture(pause, 10, 10);
		SDL_Rect pauseRect = { 10,10,38,52 };
		//neveshe zahra pause 
		// if (SBDL::MouseInRect(pauseRect) && SBDL::Mouse.cilck())

		//{
		//lose = false;
		/*const int window_width = 440;
		const int window_height = 748;
		SBDL::InitEngine("SBDL Test", window_width, window_height);

		const int FPS = 60; //frame per second
		const int delay = 1000 / FPS; //delay we need at each frame*/


	}
	// dar while zir hadaf in ast ke morabaa va dayere abi payin biaid
	while (bluePlace < 760 && redPlace < 760)
	{
		//if (SBDL::Mouse.x)
		SBDL::showTexture(back, backRect);
		SBDL::showTexture(blueCar, 25, blueCar1.y);
		SBDL::showTexture(redCar, 355, redCar1.y);
		SBDL::showTexture(pause, 10, 10);

		SBDL::showTexture(blueObstacles[shomareArray], blueObstaclePlace[anotherShomareArray], bluePlace);
		SBDL::showTexture(redObstacles[shomareArray1], redObstaclePlace[anotherShomareArray1], redPlace);
		bluePlace += obstacleVelocity; //y mavanee ke payin biaid
		redPlace += obstacleVelocity;
		SBDL::updateRenderScreen();
		SBDL::clearRenderScreen();
		int elapsedTime = SBDL::getTime() - startTime;
		if (elapsedTime < delay)
			SBDL::delay(delay - elapsedTime);
		if (bluePlace > 730 && redPlace > 730) //agar be payin e safhe resid random shomare haye jdid taarif miknd va be avale halghe
		{
			redPlace = 0;
			bluePlace = 0;
			srand(time(NULL));
			anotherShomareArray1 = rand() % 2;
			shomareArray1 = rand() % 6;
			anotherShomareArray = rand() % 2;
			shomareArray = rand() % 6;
		}

	}




	//Game logic code


	SBDL::updateRenderScreen();

	int elapsedTime = SBDL::getTime() - startTime;
	if (elapsedTime < delay)
		SBDL::delay(delay - elapsedTime);

}
//zahra
/*while (SBDL::isRunning())
{
SBDL::updateEvents();
int loopStartTime = SBDL::getTime();
int
}*/
