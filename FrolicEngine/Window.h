#pragma once

#include "GLHandler.h"
#include <memory>

struct glfwWindowDestroyer {
	void operator()(GLFWwindow* ptr) {
		glfwDestroyWindow(ptr);
	}
};

typedef std::unique_ptr<GLFWwindow, glfwWindowDestroyer> smartGLFWWindow;

class Window {
public:
	Window() {};
	~Window() {};

public:
	bool Initialize();
	void Shutdown();
	void Update();

	GLFWwindow* GetWindowRawPtr();

private:
	glfwWindowDestroyer m_windowdeleter;
	smartGLFWWindow m_glfwWindow;
	GLuint m_programID;
	GLuint m_vertexBuffer;
};