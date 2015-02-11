#ifndef INTRO_TO_OPEN_GL
#define INTRO_TO_OPEN_GL

#include "Application.h"
#include "GLMHeader.h"

class IntroToOpenGL : public Application
{
public:

	virtual bool StartUp();
	virtual void StopDown();

	virtual bool Update();
	virtual void Draw();

private:

	struct Planet;

	Planet* Moon;
	mat4 m_m4View;
	mat4 m_m4Projection;

	vec4 m_v4Red, m_v4Blue, m_v4White;

	float m_fTimer;
	float m_fRotation;


};

#endif