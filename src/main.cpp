#include "IntroToOpenGL.h"
#include "CameraAndProjection.h"

#include <iostream>

using namespace std;

int main()
{
	srand(int(0));
	
	CameraAndProjection app;

	if (!app.StartUp())
	{
		return -1;
	}

	while (app.Update())
	{
		app.Draw();
	}

	app.StopDown();

	return 0;
}