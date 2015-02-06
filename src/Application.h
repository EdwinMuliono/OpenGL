#ifndef APPLICATION_H
#define APPLICATION_H

struct GLFWwindow;

class Application
{
public:

	Application();
	virtual ~Application();

	virtual bool StartUp();
	virtual void StopDown();

	virtual bool Update();
	virtual void Draw();

protected:

	GLFWwindow* m_pWindow;

};

#endif