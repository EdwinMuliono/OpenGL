#include "Application.h"
#include "gl_core_4_4.h"
#include <GLFW\glfw3.h>
#include "Gizmos.h"
#include "GLMHeader.h"

Application::Application()
{

}

Application::~Application()
{

}

bool Application::StartUp()
{
	if (glfwInit() == 0)
	{
		return false;
	}

	//Create Window
	m_pWindow = glfwCreateWindow(1280, 720, "Monkeys: I WIN", nullptr, nullptr);

	//Check for Existance
	if (m_pWindow == nullptr)
	{
		return false;
	}

	//Make the primary window to draw
	glfwMakeContextCurrent(m_pWindow);

	//check if GL functions exist
	if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
	{
		StopDown();

		return false;
	}

	return true;
}

void Application::StopDown()
{
	glfwDestroyWindow(m_pWindow);
	glfwTerminate();
}

bool Application::Update()
{
	if (glfwWindowShouldClose(m_pWindow))
	{
		return false;
	}

	return true;
}

void Application::Draw()
{

}