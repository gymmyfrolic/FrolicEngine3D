#include "Window.h"

static const GLfloat g_vertexBufferData[] = {
	-1.0, -1.0f, 0.0f,
	1.0f, -1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
};

bool Window::Initialize() {
	if (!glfwInit()) {
		fprintf(stderr, "Failed to initialize GLFW\n");
		Shutdown();
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_glfwWindow = smartGLFWWindow(glfwCreateWindow(1024, 768, "Frolic Engine", NULL, NULL), m_windowdeleter);

	if (m_glfwWindow == nullptr) {
		fprintf(stderr, "Failed to open GLFW window. \n");
		Shutdown();
	}

	glfwMakeContextCurrent(GetWindowRawPtr());
	glewExperimental = true;

	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		Shutdown();
	}

	glfwSetInputMode(GetWindowRawPtr(), GLFW_STICKY_KEYS, GL_TRUE);

	// initialize vertex arrays
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
	
	// generate buffer
	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	// gives the vertices to opengl
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertexBufferData), g_vertexBufferData, GL_STATIC_DRAW);

	// compile shaders
	m_programID = LoadShaders("SimpleVertexShader.txt", "SimpleFragmentShader.txt");

	return false;
}

void Window::Shutdown() {
	glfwTerminate();
}

void Window::Update() {
	//do {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(m_programID);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(0);

	glfwSwapBuffers(GetWindowRawPtr());
	glfwPollEvents();
	//} while (glfwGetKey(GetWindowRawPtr(), GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(GetWindowRawPtr()) == 0);
}

GLFWwindow* Window::GetWindowRawPtr() {
	return m_glfwWindow.get();
}