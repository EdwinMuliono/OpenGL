#ifndef LIGHTING_H
#define LIGHTING_H

#include "Application.h"
#include "GLMHeader.h"
#include "VertexLoader.h"
#include "tiny_obj_loader.h"
#include <vector>

class Camera;

struct OpenGLInfo
{
	unsigned int m_VAO;
	unsigned int m_VBO;
	unsigned int m_IBO;
	unsigned int m_uiIndexes;
};

class Lighting : public Application
{
public:

	virtual bool StartUp();
	virtual void StopDown();

	virtual bool Update();
	virtual void Draw();

	void CreateOpenGLBuffers(std::vector<tinyobj::shape_t>& shapes);

	std::vector<OpenGLInfo> m_GLinfo;

	Camera* m_oCamera;
	GLUint m_programID;

	float m_fTimer;
	float m_fRotation;
	double dt;

};

#endif