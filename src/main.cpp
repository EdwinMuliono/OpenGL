#include "IntroToOpenGL.h"
#include "CameraAndProjection.h"
#include "RenderingGeometry.h"
#include "Lighting.h"

#include <iostream>

using namespace std;

int main()
{
	srand(int(0));
	
	Lighting app;

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