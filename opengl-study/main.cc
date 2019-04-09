#include <iostream>
#include <cstdlib>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "value_sampler.h"

ValueSampler<double> sampler = ValueSampler<double>(-1, 1);
ValueSampler<double> sampler01 = ValueSampler<double>(0, 1);

void display_random()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3d(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	for (size_t i = 0; i < 100; i++)
	{
		glColor3d(sampler01.sample(), sampler01.sample(), sampler01.sample());
		glVertex3d(sampler.sample(), sampler.sample(), sampler.sample());
	}
	glEnd();
	glFlush();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_POLYGON);
	glColor3d(1.0, 0.0, 0.0); /* Ô */
	glVertex3d(-0.9, -0.9, -1);
	glColor3d(0.0, 1.0, 0.0); /* —Î */
	glVertex3d(0.9, -0.9, -1);
	glColor3d(0.0, 0.0, 1.0); /* Â */
	glVertex3d(0.9, 0.9, -1);
	glColor3d(1.0, 1.0, 0.0); /* ‰© */
	glVertex3d(-0.9, 0.9, -1);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3d(1.0, 0.0, 0.0); /* Ô */
	glVertex2d(-0.5, -0.5);
	glColor3d(0.0, 1.0, 0.0); /* —Î */
	glVertex2d(0.5, -0.5);
	glColor3d(0.0, 0.0, 1.0); /* Â */
	glVertex2d(0.5, 0.5);
	glColor3d(1.0, 1.0, 0.0); /* ‰© */
	glVertex2d(-0.5, 0.5);
	glEnd();
	glFlush();
}

void init()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
}

void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	glLoadIdentity();
	glOrtho(-w / 200.0, w / 200.0, -h / 200.0, h / 200.0, -1.0, 1.0);
	//	glOrtho(-1, 1, -1, 1, -1.0, 1.0);
}

int main()
{
	if (glfwInit() == GL_FALSE)
	{
		std::cerr << "Can't initialize GLFW" << std::endl;
		return 1;
	}

	std::atexit(glfwTerminate);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* const window(glfwCreateWindow(640, 480, "Hello!", NULL, NULL));

	if (window == NULL)
	{
		std::cerr << "Can't create GLFW window." << std::endl;
		return 1;
	}

	glfwMakeContextCurrent(window);

	// GLEW initialization
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Can't initialize GLEW" << std::endl;
		return 1;
	}

	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

	while (glfwWindowShouldClose(window) == GL_FALSE)
	{
		std::cout << "HOGE";
		glfwSwapBuffers(window);
		glfwWaitEventsTimeout(1);
	}
}