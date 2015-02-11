#ifndef CAMERA
#define CAMERA

#include "GLMHeader.h"

class Camera
{
public:
	
	virtual void Update(float a_fDeltaTime) = 0;
	void setPerspective(float a_fFOV, float a_fNear, float a_fFar);
	void setLookAt(vec3 a_v3From, vec3 a_v3To, vec3 a_v3Up);
	void setPosition(vec3 a_v3Position);
	mat4 getWorldTransform();
	mat4 getView();
	mat4 getProjection();
	mat4 getProjectionView();
	

protected:

	void UpdateProjectionViewTransform();

	mat4 m_m4View;
	mat4 m_m4Projection;
	mat4 m_m4ViewProjection;
	mat4 m_m4WorldTransform;

};

#endif