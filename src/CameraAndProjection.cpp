#include "CameraAndProjection.h"
#include <GLFW\glfw3.h>
#include "Gizmos.h"
#include "FlyCamera.h"

bool CameraAndProjection::StartUp()
{
	if (!Application::StartUp())
	{
		return false;
	}

	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	Gizmos::create();

	m_oCamera = new FlyCamera();

	m_oCamera->setLookAt(vec3(10, 10, 10), vec3(0, 0, 0), vec3(0, 1, 0));
	m_oCamera->setPerspective(1280.f / 720.f, 0.1f, 1000.f);

	return true;
}

void CameraAndProjection::StopDown()
{
	Gizmos::destroy();

	glfwDestroyWindow(m_pWindow);
	glfwTerminate();
}

bool CameraAndProjection::Update()
{
	if (!Application::Update())
		return false;

	dt = glfwGetTime();

	glfwSetTime(0.0);

	m_fTimer += (float)dt;
	m_fRotation += 5.f * (float)dt;

	Gizmos::clear();

	Gizmos::addTransform(mat4(1));

	for (int i = 0; i < 101; ++i)
	{
		Gizmos::addLine(vec3(-50 + i, 0, -50), vec3(-50 + i, 0, 50), i % 10 == 0 ? m_v4Blue : m_v4White);
		Gizmos::addLine(vec3(-50, 0, -50 + i), vec3(50, 0, -50 + i), i % 10 == 0 ? m_v4Red : m_v4White);
	}

	
	return true;
}

void CameraAndProjection::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_oCamera->Update((float)dt);
	Gizmos::draw(m_oCamera->getProjectionView());

	glfwSwapBuffers(m_pWindow);
	glfwPollEvents();

}