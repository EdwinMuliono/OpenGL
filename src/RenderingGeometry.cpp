#include "RenderingGeometry.h"
#include "FlyCamera.h"
#include "gl_core_4_4.h"
#include <GLFW\glfw3.h>
#include "Vertex.h"
#include "Gizmos.h"

bool RenderingGeometry::StartUp()
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
	GenerateGrid(10, 10);

	m_oCamera = new FlyCamera();

	m_oCamera->setLookAt(vec3(10, 10, 10), vec3(0, 0, 0), vec3(0, 1, 0));
	m_oCamera->setPerspective(1280.f / 720.f, 0.1f, 1000.f);

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

	return true;
}

void RenderingGeometry::Draw()
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
	glBindVertexArray(m_VAO);

	glDrawElements(GL_TRIANGLES, m_uiIndexCount, GL_UNSIGNED_INT, 0);

	glfwSwapBuffers(m_pWindow);
	glfwPollEvents();
}

void RenderingGeometry::GenerateGrid(unsigned int a_uiRows, unsigned int a_uiCols)
{
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
			indexed_array[IndexLocation + 0] = j + i * (a_uiCols + 1);
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
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, a_uiRows * a_uiCols * 6 * sizeof(unsigned int), indexed_array, GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);



	delete[] vertex_array;
	delete[] indexed_array;
}
