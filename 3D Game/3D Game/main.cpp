#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"


GLfloat vertices[] =
{ //               COORDINATES                  /     COLORS           //
	-0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f, // Lower left corner
	 0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f, // Lower right corner
	 0.0f,  0.5f * float(sqrt(3)) * 2 / 3, 0.0f,     1.0f, 0.6f,  0.32f, // Upper corner
	-0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f,     0.9f, 0.45f, 0.17f, // Inner left
	 0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f,     0.9f, 0.45f, 0.17f, // Inner right
	 0.0f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f  // Inner down
};

// Indices for vertices order
GLuint indices[] =
{
	0, 3, 5, // Lower left triangle
	3, 2, 4, // Lower right triangle
	5, 4, 1 // Upper triangle
};


int main() 
{
	//setup glfw
	glfwInit();

	// what version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// only use the current stuff
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	/*
	GLfloat vertices[] =
	{
		0.0f, 1.0f, 0.0f, 0.5f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f, 0.1f, 0.5f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		0.5f, 0.0f, 0.0f, 0.5f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.0f, 0.0f, 0.5f, 0.0f,
		0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.5f
	};

	GLuint indices[] =
	{
		0, 4, 5, //top
		4, 2, 3,
		5, 3, 1
	};
	*/


	//create window and check it is ok
	GLFWwindow* window = glfwCreateWindow(800, 800, "Test", NULL, NULL);
	if (window == NULL) 
	{
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}
	//select the window and load
	glfwMakeContextCurrent(window);

	gladLoadGL();


	// setup GLAD
	glViewport(0, 0, 800, 800);

	
	Shader shaderProgram("default.vert", "default.frag");


	//create reference for vertex array object and vertex buffer object and indeces buffer
	
	VAO VAO1;

	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6*sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3*sizeof(float)));
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");



	//change colour
	//glClearColor(0.07f, 1.0f, 0.17f, 1.0f);
	//glClear(GL_COLOR_BUFFER_BIT);
	//glfwSwapBuffers(window);

	//Keep it refreshing
	while (!glfwWindowShouldClose(window))
	{

		glClearColor(0.07f, 1.0f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//which to use
		shaderProgram.Activate();

		glUniform1f(uniID, 0.5f);

		//glUniform1f(uniID, 0.5f);
		//bind so gl can use it
		VAO1.Bind();
		//draw
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);

		glfwPollEvents();
	}
	//Turn it off when it is off

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();


	glfwDestroyWindow(window);

	glfwTerminate();
	return 0;
}