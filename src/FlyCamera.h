#ifndef FLY_CAMERA
#define FLY_CAMERA

#include "Camera.h"

class FlyCamera : public Camera
{
public:

	virtual void Update(float a_fDeltaTime);
	void SetSpeed(float a_fSpeed);
private:

	float m_fSpeed;
	double m_fXPos;
	double m_fYPos;
	vec3 m_v3Up;
};
#endif