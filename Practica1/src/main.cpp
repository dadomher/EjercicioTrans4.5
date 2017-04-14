//GLEW
#define GLEW_STATIC
#include <GL\glew.h>
//GLFW
#include <GLFW\glfw3.h>
#include <iostream>
#include <shader.hpp>

using namespace std;
const GLint WIDTH = 800, HEIGHT = 600;
bool WIDEFRAME = false;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

int main() {
	//initGLFW
//TODO

	//set GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	//create a window
//TODO

	//set GLEW and inicializate
//TODO

	//set function when callback
//TODO

	//set windows and viewport
//TODO

	//fondo
//TODO


	//cargamos los shader
	GLuint programID = LoadShaders("./src/SimpleVertexShader.vertexshader", "./src/SimpleFragmentShader.fragmentshader");

	// Definir el buffer de vertices

	// Definir el EBO

	// Crear los VBO, VAO y EBO
	

	//reservar memoria para el VAO, VBO y EBO


	//Establecer el objeto
		//Declarar el VBO y el EBO

		//Enlazar el buffer con openGL

		//Establecer las propiedades de los vertices

		//liberar el buffer
	
	//liberar el buffer de vertices


	//bucle de dibujado
	while ()
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions

		//Establecer el color de fondo

		//establecer el shader
		glUseProgram(programID);

		//pitar el VAO

		//pintar con lineas
		//pintar con triangulos

		// Swap the screen buffers
	}
	// liberar la memoria de los VAO, EBO y VBO

	// Terminate GLFW, clearing any resources allocated by GLFW.
	exit(EXIT_SUCCESS);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	//TODO, comprobar que la tecla pulsada es escape para cerrar la aplicación y la tecla w para cambiar a modo widwframe
}
