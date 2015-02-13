#include "RenderingGeometry.h"
#include "FlyCamera.h"
#include "gl_core_4_4.h"
#include <GLFW\glfw3.h>
#include "Vertex.h"
#include "Gizmos.h"

using namespace std;

bool RenderingGeometry::StartUp()
{
	if (Application::StartUp() == false)
	{
		return false;
	}

	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	Gizmos::create();
	
	LoaderShader("light_vsSource.glsl", "light_fsSource.glsl", &m_programID);
	
	vector<tinyobj::shape_t> Shapes;
	vector<tinyobj::material_t> Material;

	string err = tinyobj::LoadObj(Shapes, Material, "./stanford_objs/buddha.obj");

	CreateOpenGLBuffer(Shapes);

	m_oCamera = new FlyCamera();

	m_oCamera->setLookAt(vec3(10, 10, 10), vec3(0, 0, 0), vec3(0, 1, 0));
	m_oCamera->setPerspective(1280.f / 720.f, 0.1f, 1000.f);

	light_dir = vec3(0, -1, 0);
	light_color = vec3(1, 1, 1);
	material_color = vec3(218.f / 255.f, 165.f / 255.f, 32.f / 255.f);
	ambient_light = vec3(0.1f);
	SpecPower = 15.f;

	return true;
}

void RenderingGeometry::StopDown()
{
	Gizmos::destroy();

	glfwDestroyWindow(m_pWindow);
	glfwTerminate();
}

bool RenderingGeometry::Update()
{
	if (!Application::Update())
		return false;
	
	dt = glfwGetTime();

	glfwSetTime(0.0);

	m_fTimer += (float)dt;
	m_fRotation += 5.f * (float)dt;

	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_R) == GLFW_PRESS)
	{
		LoaderShader("light_vsSource.glsl", "light_fsSource.glsl", &m_programID);
	}

	//Gizmos::clear();
	//
	//Gizmos::addTransform(mat4(1));
	//
	//for (int i = 0; i < 101; ++i)
	//{
	//	Gizmos::addLine(vec3(-50 + i, 0, -50), vec3(-50 + i, 0, 50), i % 10 == 0 ? vec4(0, 0, 1, 1) : vec4(1, 1, 1, 1));
	//	Gizmos::addLine(vec3(-50, 0, -50 + i), vec3(50, 0, -50 + i), i % 10 == 0 ? vec4(1, 0, 0, 1) : vec4(1, 1, 1, 1));
	//}
	
	return true;
}

void RenderingGeometry::Draw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_oCamera->Update((float)dt);
	Gizmos::draw(m_oCamera->getProjectionView());
	
	glUseProgram(m_programID);

	int pro_view_handel = glGetUniformLocation(m_programID, "ProjectionView");

	if (pro_view_handel > -1)
	{
		glUniformMatrix4fv(pro_view_handel, 1, false, glm::value_ptr(m_oCamera->getProjectionView()));
	}

	int amb = glGetUniformLocation(m_programID, "ambient_light");
	if (amb > -1)
	{
		glUniform3fv(amb, 1, (float *)&ambient_light);
	}

	int matColor = glGetUniformLocation(m_programID, "material_color");
	if (matColor > -1)
	{
		glUniform3fv(matColor, 1, (float *)&material_color);
	}

	int litColor = glGetUniformLocation(m_programID, "light_color");
	if (litColor > -1)
	{
		glUniform3fv(litColor, 1, (float *)&light_color);
	}

	int litDir = glGetUniformLocation(m_programID, "light_dir");
	if (litDir > -1)
	{
		glUniform3fv(litDir, 1, (float *)&light_dir);
	}

	int spec = glGetUniformLocation(m_programID, "SpecPower");
	if (spec > -1)
	{
		glUniform1fv(spec, 1, (float *)&SpecPower);
	}

	int CamPos = glGetUniformLocation(m_programID, "CamPos");
	if (CamPos > -1)
	{
		vec3 CamPosi = m_oCamera->getWorldTransform()[3].xyz;
		glUniform3fv(CamPos, 1, (float *)&CamPosi);
	}

	for (int i = 0; i < m_gl_Data.size(); ++i)
	{
		glBindVertexArray(m_gl_Data[i].m_VAO);
		glDrawElements(GL_TRIANGLES, m_gl_Data[i].m_uiIndexCount, GL_UNSIGNED_INT, 0);	}

	glfwSwapBuffers(m_pWindow);
	glfwPollEvents();
}

void RenderingGeometry::GenerateGrid(unsigned int a_uiRows, unsigned int a_uiCols)
{
	/*
	Vertex* vertex_array = new Vertex[(a_uiRows + 1)* (a_uiCols + 1)];

	for (unsigned int i = 0; i < a_uiRows + 1; ++i)
	{
		for (unsigned int j = 0; j < a_uiCols + 1; ++j)
		{
			vertex_array[j + i * (a_uiCols + 1)].m_Postion = vec4(j, 0, i, 1);
			vertex_array[j + i * (a_uiCols + 1)].m_Color = vec4(1, 1, 1, 1);
		}
	}

	unsigned int* indexed_array = new unsigned int[a_uiRows * a_uiCols * 6];
	m_uiIndexCount = a_uiRows * a_uiCols * 6;
	
	int IndexLocation = 0;

	for (unsigned int i = 0; i < a_uiRows; ++i)
	{
		for (unsigned int j = 0; j < a_uiCols; ++j)
		{
			indexed_array[IndexLocation] = j + i * (a_uiCols + 1);
			indexed_array[IndexLocation + 1] = (j + 1) + i * (a_uiCols + 1);
			indexed_array[IndexLocation + 2] = (j + 1) + (i + 1) * (a_uiCols + 1);
			
			indexed_array[IndexLocation + 3] = j + i * (a_uiCols + 1);
			indexed_array[IndexLocation + 4] = (j + 1) + (i + 1) * (a_uiCols + 1);
			indexed_array[IndexLocation + 5] = j + (i + 1) * (a_uiCols + 1);

			IndexLocation += 6;

		}
	}

	
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_IBO);
	glGenVertexArrays(1, &m_VAO);
	
	glBindVertexArray(m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, ((a_uiRows + 1) * (a_uiCols + 1)) * sizeof(Vertex), vertex_array, GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex),(void*)(sizeof(vec4)));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, IndexLocation * sizeof(unsigned int), indexed_array, GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	delete[] vertex_array;
	delete[] indexed_array;
	*/
}

void RenderingGeometry::CreateOpenGLBuffer(std::vector<tinyobj::shape_t>& a_aShapes)
{
	m_gl_Data.resize(a_aShapes.size());

	for (int i = 0; i < a_aShapes.size(); ++i)
	{
		std::vector<float> vertex_data;

		unsigned int float_count = a_aShapes[i].mesh.positions.size();
		float_count += a_aShapes[i].mesh.normals.size();

		vertex_data.reserve(float_count);

		vertex_data.insert(vertex_data.end(), a_aShapes[i].mesh.positions.begin(), a_aShapes[i].mesh.positions.end());
		vertex_data.insert(vertex_data.end(), a_aShapes[i].mesh.normals.begin(), a_aShapes[i].mesh.normals.end());

		m_gl_Data[i].m_uiIndexCount = a_aShapes[i].mesh.indices.size();

		glGenVertexArrays(1, &m_gl_Data[i].m_VAO);
		glGenBuffers(1, &m_gl_Data[i].m_VBO);
		glGenBuffers(1, &m_gl_Data[i].m_IBO);
		glBindVertexArray(m_gl_Data[i].m_VAO);

		glBindBuffer(GL_ARRAY_BUFFER, m_gl_Data[i].m_VBO);
		glBufferData(GL_ARRAY_BUFFER, vertex_data.size() * sizeof(float), vertex_data.data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_gl_Data[i].m_IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, a_aShapes[i].mesh.indices.size() * sizeof(unsigned int), a_aShapes[i].mesh.indices.data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(float) * a_aShapes[i].mesh.positions.size()));

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}

void RenderingGeometry::CleanOpenGLBufffers()
{
	glDeleteProgram(m_programID);

	for (int i = 0; i < m_gl_Data.size(); ++i)
	{
		glDeleteVertexArrays(1, &m_gl_Data[i].m_VAO);
		glDeleteBuffers(1, &m_gl_Data[i].m_VBO);
		glDeleteBuffers(1, &m_gl_Data[i].m_IBO);
	}
}
