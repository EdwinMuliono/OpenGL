#include "Gizmos.h"
#include "gl_core_4_4.h"

#include <GLFW\glfw3.h>
#include <cstdio>

#define GLM_SWIZZLE
#include"glm/glm.hpp"
#include"glm/ext.hpp"

#include <iostream>
using namespace std;
using namespace glm;

int main()
{
	srand(int(0));
	//Intializer
	if (glfwInit() == 0)
	{
		cout << "Hey Guess What... I BROKED" << endl;
		system("pause");

		return -1;
	}

	//Create Window
	GLFWwindow* pgWindow = glfwCreateWindow(1280, 720, "Monkeys: I WIN", nullptr, nullptr);
	
	//Check for Existance
	if (pgWindow == nullptr)
	{
		cout << "Achievement Unlocked: Broke" << endl;
		system("pause");

		return -2;
	}

	//Make the primary window to draw
	glfwMakeContextCurrent(pgWindow);

	//check if GL functions exist
	if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
	{
		cout << "Y U BROKE" << endl;
		system("pause");

		glfwDestroyWindow(pgWindow);
		glfwTerminate();

		return -3;
	}

	//Print OpenGL version
	printf("OpenGL %i.%i\n", ogl_GetMajorVersion(), ogl_GetMinorVersion());

	//Default BGColor
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	Gizmos::create();

	mat4 m4view = glm::lookAt(vec3(10, 10, 10), vec3(0, 0, 0), vec3(0, 1, 0));
	mat4 m4projection = glm::perspective(glm::radians(60.0f), 1280.f / 720.f, 0.1f, 1000.f);

	glfwSetTime(0.0);

	double timer = 0;
	double rotation = 0;

	while (glfwWindowShouldClose(pgWindow) == false)
	{
		double dt = glfwGetTime();

		glfwSetTime(0.0);

		timer += dt;
		rotation += 5 * dt;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		Gizmos::clear();

		vec4 white(1);
		vec4 black(0, 0, 0, 1);
		vec4 red(1, 0, 0, 1);
		vec4 green(0, 1, 0, 1);
		vec4 blue(0, 0, 1, 1);

		Gizmos::addTransform(mat4(1));

		mat4 m4rotation = glm::rotate((float)timer, vec3(0, 1, 0));
		
		for (int i = 0; i < 101; ++i)
		{
			Gizmos::addLine(vec3(-50 + i, 0, -50), vec3(-50 + i, 0, 50), i % 10 == 0 ? blue : white);
			Gizmos::addLine(vec3(-50, 0, -50 + i), vec3(50, 0, -50 + i), i % 10 == 0 ? red : white);
		}

		Gizmos::addSphere(m4rotation[3].xyz, 5, 16, 16, red, &m4rotation);
		
		for (int i = 0; i < 10; ++i)
		{
			mat4 m4rotationchild = (m4rotation * glm::rotate((float)timer, vec3(i % 2, i % 3, i % 4))) * glm::translate(vec3(i * 2, 0, 0)) * glm::rotate((float)timer, vec3(i % 2, i % 3, i % 4));
			Gizmos::addSphere(m4rotationchild[3].xyz, 1, 16, 16, red, &m4rotationchild);
		}
		


		/*
		vec4 pew(.25, .5, .75, 1);

		
		Gizmos::addTri(vec3(5, 0, 0), vec3(0, 5, 0), vec3(0, 0, 5), red);
		Gizmos::addAABB(vec3(-2.5f, 2.5f, -2.5f), vec3(2.5, 2.5, 2.5), pew);
		Gizmos::addAABBFilled(vec3(-2.5f, 2.5f, -2.5f), vec3(2.5, 2.5, 2.5), pew);

		*/
		
		m4view = glm::lookAt(vec3(cos(glm::radians(rotation)) * 20, 10, sin(glm::radians(rotation)) * 20), vec3(0, 0, 0), vec3(0, 1, 0));
		Gizmos::draw(m4projection, m4view);

		glfwSwapBuffers(pgWindow);
		glfwPollEvents();
	}

	Gizmos::destroy();

	glfwDestroyWindow(pgWindow);
	glfwTerminate();

	return 0;
}