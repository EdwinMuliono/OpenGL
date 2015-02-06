#include "Camera.h"

void Camera::setPerspective(float a_fFOV, float a_fNear, float a_fFar)
{
	m_m4Projection = glm::perspective(glm::pi<float>() * 0.25f, a_fFOV, a_fNear, a_fFar);
}

void Camera::setLookAt(vec3 a_v3From, vec3 a_v3To, vec3 a_v3Up)
{
	m_m4View = glm::lookAt(a_v3From, a_v3To, a_v3Up);
}

void Camera::setPosition(vec3 a_v3Position)
{
	m_m4WorldTransform = glm::inverse(m_m4View);
	m_m4WorldTransform[3].xyz = a_v3Position;

	UpdateProjectionViewTransform();
}

mat4 Camera::getWorldTransform()
{
	return m_m4WorldTransform;
}

mat4 Camera::getView()
{
	return m_m4View;
}

mat4 Camera::getProjection()
{
	return m_m4Projection;
}

mat4 Camera::getProjectionView()
{
	return m_m4ViewProjection;
}

void Camera::UpdateProjectionViewTransform()
{
	m_m4View = glm::inverse(m_m4WorldTransform);
	m_m4ViewProjection = m_m4Projection * m_m4View;
}
