#include "IntroToOpenGL.h"
#include <GLFW\glfw3.h>
#include "Gizmos.h"

struct IntroToOpenGL::Planet
{
	Planet(vec3 a_v3Pos, vec3 a_v3Vel, vec3 a_v3Rot)
	{
		v3Position = a_v3Pos;
		v3Velocity = a_v3Vel;
		v3Rotation = a_v3Rot;
	}

	mat4 m4Transform;
	
	vec3 v3Position;
	vec3 v3Velocity;
	vec3 v3Rotation;

	void Update(float a_fTimer, vec4 color)
	{
		m4Transform = glm::translate(v3Position) * glm::rotate(a_fTimer, v3Rotation);
		Gizmos::addSphere(m4Transform[3].xyz, 5, 16, 16, color, &m4Transform);

		v3Position += v3Velocity;
	}
};

bool IntroToOpenGL::StartUp()
{
	if (!Application::StartUp())
	{
		return false;
	}

	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	Gizmos::create();

	m_m4View = glm::lookAt(vec3(10, 10, 10), vec3(0, 0, 0), vec3(0, 1, 0));
	m_m4Projection = glm::perspective(glm::radians(60.0f), 1280.f / 720.f, 0.1f, 1000.f);

	glfwSetTime(0.0);

	m_v4Red = vec4(1, 0, 0, 1);
	m_v4Blue = vec4(0, 0, 1, 1);
	m_v4White = vec4(1, 1, 1, 1);

	Moon = new Planet(vec3(10, 10, 0), vec3(0, 0, 0), vec3(0, 1, 0));

	return true;
}

void IntroToOpenGL::StopDown()
{
	Gizmos::destroy();

	glfwDestroyWindow(m_pWindow);
	glfwTerminate();
}

bool IntroToOpenGL::Update()
{
	if (!Application::Update())
		return false;

	double dt = glfwGetTime();

	glfwSetTime(0.0);

	m_fTimer += (float)dt;
	m_fRotation += 5.f * (float)dt;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Gizmos::clear();

	Gizmos::addTransform(mat4(1));

	for (int i = 0; i < 101; ++i)
	{
		Gizmos::addLine(vec3(-50 + i, 0, -50), vec3(-50 + i, 0, 50), i % 10 == 0 ? m_v4Blue : m_v4White);
		Gizmos::addLine(vec3(-50, 0, -50 + i), vec3(50, 0, -50 + i), i % 10 == 0 ? m_v4Red : m_v4White);
	}

	Moon->Update(m_fTimer, m_v4Red);

	m_m4View = glm::lookAt(vec3(cos(glm::radians(m_fRotation)) * 20, 10, sin(glm::radians(m_fRotation)) * 20), vec3(0, 0, 0), vec3(0, 1, 0));
	Gizmos::draw(m_m4Projection, m_m4View);

	glfwSwapBuffers(m_pWindow);
	glfwPollEvents();

	return true;
}

void IntroToOpenGL::Draw()
{

}