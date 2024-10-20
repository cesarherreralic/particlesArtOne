#include "libs.h"


int main()
{
	glfwInit();

	// CREATE A WINDOW BEFORE GLEW INIT!!!

	// GLEW
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK) {
		glfwTerminate();
		throw "Error::GLEW::init";
	}

	system("PAUSE"); // this will be removed soon

	return 0;
}
