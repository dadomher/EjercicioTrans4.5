//GLEW
#define GLEW_STATIC
#include <GL\glew.h>
//GLFW
#include <GLFW\glfw3.h>
#include <iostream>
//#include <shader.hpp>
#include <SOIL.h>
#include <shaderPractica.hpp>

using namespace std;
const GLint WIDTH = 800, HEIGHT = 600;
bool WIDEFRAME = false;
float transformacion = 0.5f;

int main();
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void pintar_vao(GLuint VAO);

int main() {
	//initGLFW
//TODO
//comprobar que GLFW estaactivo

	//set GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	//create a window
//TODO
	GLFWwindow* window;

	if (!glfwInit())
		exit(EXIT_FAILURE);

	window = glfwCreateWindow(WIDTH, HEIGHT, "Primera ventana", nullptr, nullptr);
	if (!window) {
		cout << "Error al crear la ventana" << endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);

	//set GLEW and inicializate
//TODO

	glewExperimental = GL_TRUE;
	if (GLEW_OK != glewInit()) {
		std::cout << "Error al inicializar glew" << std::endl;
		glfwTerminate();
		return NULL;
	}		

	//set function when callback
//TODO
	glfwSetKeyCallback(window, key_callback);

	//set windows and viewport0
//TODO
	int screenWithd, screenHeigtht;
	glfwGetFramebufferSize(window, &screenWithd, &screenHeigtht);

	//origen de la camara, dimensiones de la ventana
	glViewport(0, 0, screenWithd, screenHeigtht);

	//fondo
//TODO
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0, 1.0, 1.0, 1.0);

	//cargamos los shader
	//GLuint programID = LoadShaders("./src/SimpleVertexShader.vertexshader", "./src/SimpleFragmentShader.fragmentshader");

	Shader sh = Shader("./src/textureVertex.vertexshader", "./src/textureFragment.fragmentshader");

	// Definir el buffer de vertices
	GLfloat cubeVertex[] = { -0.5f, 0.5f, 0.0f,
							 -0.5f, -0.5f,0.0f, 
							 0.5f,-0.5f, 0.0f, 
							 0.5f, 0.5f,0.0f
							};

	GLfloat VertexBufferObject[] = {
		0.5f,  0.5f, 0.0f,  // Top Right
		0.5f, -0.5f, 0.0f,  // Bottom Right
		-0.5f, -0.5f, 0.0f,  // Bottom Left
		-0.5f,  0.5f, 0.0f   // Top Left 
	};

	GLfloat vertices[] = {
		// Positions          // Colors           // Texture Coords
		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // Top Right
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // Top Left 
	};

	// Definir el EBO
	GLuint IndexBufferObject[]{
		0,1,2,
		3,0,2};

	// Crear los VBO, VAO y EBO
	GLuint VAO;
	GLuint EBO;
	GLuint VBO;
	
	//reservar memoria para el VAO, VBO y EBO
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	//Establecer el objeto
	glBindVertexArray(VAO);
		//Declarar el VBO y el EBO
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

		//Enlazar el buffer con openGL
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(IndexBufferObject), IndexBufferObject, GL_STATIC_DRAW);

		//Establecer las propiedades de los vertices
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)0); //POSICION ARRAY, N� VALORES, LARGO TOTAL VERTICES, VALOR QUE EMPIEZA EN EL VECTOR
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)3);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);






		// Crear la textura
		GLuint texture;

		//Reservar memoria en openGL
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		//parametros
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

		float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Load and generate the texture
		int width, height;
		unsigned char* image = SOIL_load_image("./src/texture.png", &width, &height, 0, SOIL_LOAD_RGB);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

		//libera la imagen
		SOIL_free_image_data(image);

		// Crear la textura
		GLuint texture2;

		//Reservar memoria en openGL
		glGenTextures(1, &texture2);
		glBindTexture(GL_TEXTURE_2D, texture2);

		//parametros
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Load and generate the texture
		image = SOIL_load_image("./src/texture2.png", &width, &height, 0, SOIL_LOAD_RGB);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

		//libera la imagen
		SOIL_free_image_data(image);

		//libera el puntero de la textura
		glBindTexture(GL_TEXTURE_2D, 0);


		//liberar el buffer
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	//liberar el buffer de vertices
		glBindVertexArray(0);

	//bucle de dibujado
	while (!glfwWindowShouldClose(window)) {
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glClear(GL_COLOR_BUFFER_BIT);
		//Establecer el color de fondo
		glClearColor(1.0, 1.0, 1.0, 1.0);

		//establecer el shader
		//glUseProgram(programID);
		/*sh.USE();
		GLint variableShader = glGetUniformLocation(sh.Program, "offset");
		glUniform1f(variableShader, 0.5);

		GLint variableShader2 = glGetUniformLocation(sh.Program, "time");
		glUniform1f(variableShader2, glfwGetTime());*/



		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glUniform1i(glGetUniformLocation(sh.Program, "Texture1"), 0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		glUniform1i(glGetUniformLocation(sh.Program, "Texture2"), 1);

		sh.USE();

		glUniform1f(glGetUniformLocation(sh.Program, "trans"), transformacion);

		//glUniform1i(glGetUniformLocation(sh.Program, "trans"), transformacion);

		pintar_vao(VAO);

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);


		//intercambia el framebuffer
		glfwSwapBuffers(window);
		//comprueba que algun disparador se halla activado (tales como el teclado, raton, etc)
		glfwPollEvents();
	}
	// liberar la memoria de los VAO, EBO y VBO
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	//TODO, comprobar que la tecla pulsada es escape para cerrar la aplicaci�n y la tecla w para cambiar a modo widwframe
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (key == GLFW_KEY_W && action == GLFW_PRESS) WIDEFRAME = !WIDEFRAME;

	if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
		if (transformacion <= 0.9f) {
			transformacion += 0.1f;
		}
	}

	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
		if (transformacion >= 0.1f) {
			transformacion -= 0.1f;
		}
	}
}

void pintar_vao(GLuint VAO) {
	//pitar el VAO
	glBindVertexArray(VAO);

	if (WIDEFRAME) {
		//pintar con lineas
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
	else {
		//pintar con triangulos
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

	glBindVertexArray(0);
}