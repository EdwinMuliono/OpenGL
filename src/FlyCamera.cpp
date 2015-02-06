#include "FlyCamera.h"
#include <GLFW/glfw3.h>

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

	m_fXPos *= -3;
	m_fYPos *= -3;

	vec4 temp = (vec3)m_m4WorldTransform[0];
	vec4 yaw = glm::rotate((float)m_fXPos,  vec3(0, 1, 0));
	vec4 pitch = rotate((float)m_fXPos, temp);

	//m_m4WorldTransform[0] = yaw * pitch;
	//m_m4WorldTransform[1] = yaw * pitch;
	//m_m4WorldTransform[2] = yaw * pitch;

	UpdateProjectionViewTransform();
}

void FlyCamera::SetSpeed(float a_fSpeed)
{
	m_fSpeed = a_fSpeed;
}
