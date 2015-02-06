#ifndef Camera_And_Projection
#define Camera_And_Projection

#include "Application.h"

#define GLM_SWIZZLE
#include "glm/glm.hpp"
#include "glm/ext.hpp"

using namespace glm;

class Camera;

class CameraAndProjection : public Application
{
public:
	virtual bool StartUp();
	virtual void StopDown();

	virtual bool Update();
	virtual void Draw();

private:

	Camera* m_oCamera;

	vec4 m_v4Red, m_v4Blue, m_v4White;

	float m_fTimer;
	float m_fRotation;
	double dt;
};

#endif