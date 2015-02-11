#include "VertexLoader.h"

#include "gl_core_4_4.h"
#include <GLFW\glfw3.h>
#include "Vertex.h"
#include "Gizmos.h"


bool LoaderShader(char * VertexShader, char * FragmentShader, GLuint* result)
{
	FILE* vertexFile = fopen(VertexShader, "r");
	FILE* fragmentfile = fopen(FragmentShader, "r");

	if (vertexFile == 0 || fragmentfile == 0)
	{
		fclose(vertexFile);
		fclose(fragmentfile);
		return false;
	}

	fseek(vertexFile, 0, SEEK_END);
	int vertexlength = ftell(vertexFile);
	fseek(vertexFile, 0, SEEK_SET);

	fseek(fragmentfile, 0, SEEK_END);
	int fraglength = ftell(fragmentfile);
	fseek(fragmentfile, 0, SEEK_SET);

	char *vs_Source = new char[vertexlength];
	char *fs_Source = new char[fraglength];

	vertexlength = fread(vs_Source, 1, vertexlength, vertexFile);
	fraglength = fread(fs_Source, 1, fraglength, fragmentfile);

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertexShader, 1, &vs_Source, 0);
	glCompileShader(vertexShader);

	glShaderSource(fragmentShader, 1, &fs_Source, 0);
	glCompileShader(fragmentShader);

	result = new GLUint();
	*result = glCreateProgram();

	glAttachShader(*result, vertexShader);
	glAttachShader(*result, fragmentShader);

	glLinkProgram(*result);

	int success = GL_FALSE;

	glGetProgramiv(*result, GL_LINK_STATUS, &success);
	if (success == GL_FALSE)
	{
		int infoLogLength = 0;
		glGetProgramiv(*result, GL_INFO_LOG_LENGTH, &infoLogLength);
		char* infolog = new char[infoLogLength];

		glGetProgramInfoLog(*result, infoLogLength, 0, infolog);
		printf("Error:Shader\n");
		printf("%s \n", infolog);

		delete[]infolog;

		fclose(vertexFile);
		fclose(fragmentfile);

		return false;
	}

	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);

	delete[] vs_Source;
	delete[] fs_Source;

	fclose(vertexFile);
	fclose(fragmentfile);

	return true;
}