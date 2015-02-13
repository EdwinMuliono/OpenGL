#ifndef RENDERING_GEOMETRY_H
#define RENDERING_GEOMETRY_H

#include "Application.h"
#include "GLMHeader.h"
#include "VertexLoader.h"

#include "tiny_obj_loader.h"

struct OpenGLData
{
	unsigned int m_VAO;
	unsigned int m_VBO;
	unsigned int m_IBO;
	unsigned int m_uiIndexCount;
};

class Camera;

class RenderingGeometry : public Application
{
public:

	virtual bool StartUp();
	virtual void StopDown();

	virtual bool Update();
	virtual void Draw();

	void GenerateGrid(unsigned int a_uiRows, unsigned int a_uiCols);
	void CreateOpenGLBuffer(std::vector<tinyobj::shape_t>& a_aShapes);
	void CleanOpenGLBufffers();

	std::vector<OpenGLData> m_gl_Data;
	Camera* m_oCamera;
	GLUint m_programID;

	float m_fTimer;
	float m_fRotation;
	double dt;

	vec3 light_dir;
	vec3 light_color;

	vec3 material_color;
	vec3 ambient_light;

	float SpecPower;

	vec3 CamPosition;

private:

};
#endif