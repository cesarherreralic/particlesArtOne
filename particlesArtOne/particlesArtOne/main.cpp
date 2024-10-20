#include "libs.h"

int WINDOW_WIDTH = 800;
int WINDOW_HEIGHT = 600;

void reshape(GLFWwindow* window, int fbW, int fbH) {

	//update resolution
	WINDOW_WIDTH = fbW;
	WINDOW_HEIGHT = fbH;

	glViewport(0, 0, fbW, fbH);
}

int main()
{
	// INIT GLFW
	glfwInit();

	// CREATE THE WINDOW
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	//this next one is just for mac to avoid errors:
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	int frameBufferWidth = 0;
	int frameBufferHeight = 0;

	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "GRAPHICS 4", NULL, NULL);

	// setting context and stuff
	glfwGetFramebufferSize(window, &frameBufferWidth, &frameBufferHeight);
	glfwSetFramebufferSizeCallback(window, reshape);

	/*glfwGetFramebufferSize(window, &frameBufferWidth, &frameBufferHeight);
	glViewport(0, 0, frameBufferWidth, frameBufferHeight);*/

	glfwMakeContextCurrent(window); // IMPORTANT FOR GLEW



	// 3 INIT GLEW (NEEDS WINDOWS AND OPENGL CONTEXT) (the comments with numbers are steps, the order in them is important)
	glewExperimental = GL_TRUE; // use new functions from opengl

	//error handling
	if (glewInit() != GLEW_OK) {
		std::cout << "ERROR::MAIN.CPP::GLEW_INIT_FAILED" << "\n";
		glfwTerminate();
	}

	// OPENGL OPTIONS
	glEnable(GL_DEPTH_TEST); // to be able to move in depth
	glEnable(GL_CULL_FACE); // avoid drawing what is behind something
	glEnable(GL_PROGRAM_POINT_SIZE); // to control de point size from the shaders
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW); // to set the front face as counter clock wise

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND); // to blend colors

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // cool to play around with this
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // fill the face with the color, just for fun.

	// generating the seed for the random generation, so it can be different on each run.
	srand((unsigned int)time(NULL));

	// INIT MATRICES
	glm::vec3 position(0.f);
	glm::vec3 rotation(0.f);
	glm::vec3 scale(1.f);

	glm::mat4 ModelMatrix(1.f); // Identity matrix
	ModelMatrix = glm::translate(ModelMatrix, position);
	ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.x), glm::vec3(1.f, 0.f, 0.f));
	ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.y), glm::vec3(0.f, 1.f, 0.f));
	ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.z), glm::vec3(0.f, 0.f, 1.f));
	ModelMatrix = glm::scale(ModelMatrix, scale);
	//note: internally the order of the operations for rotation scaling and translate are ocurring in the oposite order and not in the order they look here.
	// I mean they are operated from right to left, it est vertices with matrices

	glm::vec3 camPosition(0.f, 0.f, 1.f);
	glm::vec3 worldUp = glm::vec3(0.f, 1.f, 0.f);
	glm::vec3 camFront = glm::vec3(0.f, 0.f, -1.f);
	glm::mat4 ViewMatrix(1.f);
	ViewMatrix = glm::lookAt(camPosition, camPosition + camFront, worldUp);

	float fov = 90.f;
	float nearPlane = 0.1f;
	float farPlane = 1000.f;
	glm::mat4 ProjectionMatrix(1.f);
	ProjectionMatrix = glm::perspective(
		glm::radians(fov),
		static_cast<float>(frameBufferWidth) / frameBufferHeight,
		nearPlane,
		farPlane
	);

	// MAIN LOOP
	while (!glfwWindowShouldClose(window)) {
		// UPDATE INPUT
		glfwPollEvents(); // Will let the cursor interact with the window

		//DRAW
		//Clear
		glClearColor(0.f, 0.f, 0.0f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		// Move rotate and scale
		ModelMatrix = glm::mat4(1.f); // Identity matrix
		ModelMatrix = glm::translate(ModelMatrix, position);
		ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.x), glm::vec3(1.f, 0.f, 0.f));
		ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.y), glm::vec3(0.f, 1.f, 0.f));
		ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.z), glm::vec3(0.f, 0.f, 1.f));
		ModelMatrix = glm::scale(ModelMatrix, scale);

		glfwGetFramebufferSize(window, &frameBufferWidth, &frameBufferHeight);

		ProjectionMatrix = glm::perspective(
			glm::radians(fov),
			static_cast<float>(frameBufferWidth) / frameBufferHeight,
			nearPlane,
			farPlane
		);


		//End draw
		glfwSwapBuffers(window);
		glFlush();
	}

	//END OF PROGRAM
	glfwDestroyWindow(window);
	glfwTerminate();


	return 0;
}
