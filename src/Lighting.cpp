#include "Lighting.h"
#include "FlyCamera.h"
#include "gl_core_4_4.h"
#include <GLFW\glfw3.h>
#include "Vertex.h"
#include "Gizmos.h"

bool Lighting::StartUp()
{
	bool result = false;
	if (Application::StartUp() == false)
	{
		return false;
	}

	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	Gizmos::create();

	LoaderShader("vsSource.glsl", "fsSource.glsl", &m_programID);

	m_oCamera = new FlyCamera();

	m_oCamera->setLookAt(vec3(10, 10, 10), vec3(0, 0, 0), vec3(0, 1, 0));
	m_oCamera->setPerspective(1280.f / 720.f, 0.1f, 1000.f);

	return true;
}

void Lighting::StopDown()
{
	Gizmos::destroy();

	glfwDestroyWindow(m_pWindow);
	glfwTerminate();

}

bool Lighting::Update()
{
	if (!Application::Update())
		return false;

	dt = glfwGetTime();

	glfwSetTime(0.0);

	m_fTimer += (float)dt;
	m_fRotation += 5.f * (float)dt;

	return true;
}

void Lighting::Draw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_oCamera->Update((float)dt);
	Gizmos::draw(m_oCamera->getProjectionView());

	glUseProgram(m_programID);

	int pro_view_handel = glGetUniformLocation(m_programID, "ProjectionView");

	if (pro_view_handel > -1)
	{
		glUniformMatrix4fv(pro_view_handel, 1, false, glm::value_ptr(m_oCamera->getProjectionView()));
	}

	for (int i = 0; i < m_GLinfo.size(); ++i)
	{
		glBindVertexArray(m_GLinfo[i].m_VAO);

		glDrawElements(GL_TRIANGLES, m_GLinfo[i].m_uiIndexes, GL_UNSIGNED_INT, 0);	}

	glfwSwapBuffers(m_pWindow);
	glfwPollEvents();
}

void Lighting::CreateOpenGLBuffers(std::vector<tinyobj::shape_t>& a_shapes)
{
	m_GLinfo.resize(a_shapes.size());

	for (int i = 0; i < a_shapes.size(); ++i)
	{
		glGenVertexArrays(1, &m_GLinfo[i].m_VAO);
		glGenBuffers(1, &m_GLinfo[i].m_VBO);
		glGenBuffers(1, &m_GLinfo[i].m_IBO);
		glBindVertexArray(m_GLinfo[i].m_IBO);

		unsigned int float_count = a_shapes[i].mesh.positions.size();
		float_count += a_shapes[i].mesh.normals.size();
		
		std::vector<float> vertex_data;
		vertex_data.reserve(float_count);

		vertex_data.insert(vertex_data.end(), a_shapes[i].mesh.positions.begin(), a_shapes[i].mesh.positions.end());
		vertex_data.insert(vertex_data.end(), a_shapes[i].mesh.normals.begin(), a_shapes[i].mesh.positions.end());

		m_GLinfo[i].m_uiIndexes = a_shapes[i].mesh.indices.size();

		glBindBuffer(GL_ARRAY_BUFFER, m_GLinfo[i].m_VBO);
		glBufferData(GL_ARRAY_BUFFER, vertex_data.size() * sizeof(float), vertex_data.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, m_GLinfo[i].m_IBO);
		glBufferData(GL_ARRAY_BUFFER, a_shapes[i].mesh.indices.size() * sizeof(unsigned int), a_shapes[i].mesh.indices.data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, (void*)(sizeof(float) * a_shapes[i].mesh.positions.size()));

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}