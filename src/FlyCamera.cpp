#include "FlyCamera.h"
#include <GLFW/glfw3.h>
#include <iostream>
using namespace std;

void FlyCamera::Update(float a_fDeltaTime)
{
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_W) == GLFW_PRESS)
	{
		m_m4WorldTransform[3] -= 10 * m_m4WorldTransform[2] * a_fDeltaTime;
	}

	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_S) == GLFW_PRESS)
	{
		m_m4WorldTransform[3] += 10 * m_m4WorldTransform[2] * a_fDeltaTime;
	}

	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_A) == GLFW_PRESS)
	{
		m_m4WorldTransform[3] -= 10 * m_m4WorldTransform[0] * a_fDeltaTime;
	}

	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_D) == GLFW_PRESS)
	{
		m_m4WorldTransform[3] += 10 * m_m4WorldTransform[0] * a_fDeltaTime;
	}

	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		m_m4WorldTransform[3] += 10 * m_m4WorldTransform[1] * a_fDeltaTime;
	}

	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		m_m4WorldTransform[3] -= 10 * m_m4WorldTransform[1] * a_fDeltaTime;
	}

	glfwGetCursorPos(glfwGetCurrentContext(), &m_fXPos, &m_fYPos);
	glfwSetCursorPos(glfwGetCurrentContext(), 1280.f / 2.f, 720.f / 2.f);

	m_fXPos -= 1280.f / 2.f;
	m_fYPos -= 720.f / 2.f;

	m_fXPos /= 1280 / 2.f;
	m_fYPos /= 720 / 2.f;

	m_fXPos *= 3;
	m_fYPos *= 3;

	vec4 temp = m_m4WorldTransform[0];
	vec4 yaw = rotate((float)m_fYPos, (vec3)temp) * m_m4WorldTransform[1];
	vec4 pitch = rotate((float)m_fXPos, vec3(0, 1, 0)) * m_m4WorldTransform[2];

	m_m4WorldTransform[0] = temp;
	m_m4WorldTransform[1] = yaw;
	m_m4WorldTransform[2] = pitch;
	
	system("CLS");
	for (int i = 0; i < 4; ++i)
	{
		cout
			<< m_m4WorldTransform[i].x
			<< m_m4WorldTransform[i].y
			<< m_m4WorldTransform[i].z
			<< m_m4WorldTransform[i].w
			<< endl;
	}

	UpdateProjectionViewTransform();
}

void FlyCamera::SetSpeed(float a_fSpeed)
{
	m_fSpeed = a_fSpeed;
}
