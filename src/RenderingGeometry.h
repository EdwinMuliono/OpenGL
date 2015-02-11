#ifndef RENDERING_GEOMETRY_H
#define RENDERING_GEOMETRY_H

#include "Application.h"
#include "GLMHeader.h"
#include "VertexLoader.h"

class Camera;

class RenderingGeometry : public Application
{
public:

	virtual bool StartUp();
	virtual void StopDown();

	virtual bool Update();
	virtual void Draw();

	void GenerateGrid(unsigned int a_uiRows, unsigned int a_uiCols);

	unsigned int m_uiIndexes;

	Camera* m_oCamera;

	GLUint m_programID;

	unsigned int m_VAO;
	unsigned int m_VBO;
	unsigned int m_IBO;

	float m_fTimer;
	float m_fRotation;
	double dt;

	unsigned int m_uiIndexCount;

private:

};
#endif