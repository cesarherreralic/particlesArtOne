#include "libs.h"



enum key_state { NOTPUSHED, PUSHED } keyarr[127];

int WINDOW_WIDTH = 800;
int WINDOW_HEIGHT = 600;

float randomBetweenFloats(float min, float max) {
	return min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (min - max)));
}

float randomBetween(int min, int max) {
	return (float)(rand() % ((max)-(min)+1) + (min));
}

int randomBetweenInt(int min, int max) {
	return rand() % (max - min + 1) + min;
}

GLfloat T_Interval = 0;
GLint T_FPS_Count = 0;
GLdouble T_FPS_All = 0;

GLdouble customTimer(int lastCallTime)
{
	/* Seit dem Programmstart vergangene Zeit in Sekunden */
	T_Interval = glfwGetTime();
	glfwSetTime(0.0);

	T_FPS_Count++;
	T_FPS_All += T_Interval;

	if (T_FPS_Count >= 1000) {
		printf("FPS rate: %i\n", (GLint)(1.0 / ((GLdouble)T_FPS_All / (GLdouble)T_FPS_Count)));
		T_FPS_All = 0.0;
		T_FPS_Count = 0;
	}

	printf("deltatime: %f\n", T_Interval);

	return T_Interval;
}

const GLuint amountOfParticles = 256;

//Particle* particles;
//Particle* particles = new Particle[amountOfParticles]{
	// Position									//Velocity
	/*Particle(glm::vec3(0.f, 0.f, 0.f),			glm::vec3(0.1f, 0.2f, 0.f)),
	Particle(glm::vec3(-0.4f, 0.1f, 0.f),		glm::vec3(0.f, 0.3f, 0.f)),
	Particle(glm::vec3(0.8f, 0.3f, 0.f),		glm::vec3(-0.1f, 0.5f, 0.f)),*/

	//Particle(glm::vec3(randomBetweenFloats(-0.99f, 0.99f), randomBetweenFloats(-0.99f, 0.99f), 0.f),			glm::vec3(randomBetweenFloats(-0.99f, 0.99f), randomBetweenFloats(-0.99f, 0.99f), 0.f)),
	//Particle(glm::vec3(randomBetweenFloats(-0.99f, 0.99f), randomBetweenFloats(-0.99f, 0.99f), 0.f),			glm::vec3(randomBetweenFloats(-0.99f, 0.99f), randomBetweenFloats(-0.99f, 0.99f), 0.f)),
	//Particle(glm::vec3(randomBetweenFloats(-0.99f, 0.99f), randomBetweenFloats(-0.99f, 0.99f), 0.f),			glm::vec3(randomBetweenFloats(-0.99f, 0.99f), randomBetweenFloats(-0.99f, 0.99f), 0.f)),
	//Particle(glm::vec3(randomBetweenFloats(-0.99f, 0.99f), randomBetweenFloats(-0.99f, 0.99f), 0.f),			glm::vec3(randomBetweenFloats(-0.99f, 0.99f), randomBetweenFloats(-0.99f, 0.99f), 0.f)),
	//Particle(glm::vec3(randomBetweenFloats(-0.99f, 0.99f), randomBetweenFloats(-0.99f, 0.99f), 0.f),			glm::vec3(randomBetweenFloats(-0.99f, 0.99f), randomBetweenFloats(-0.99f, 0.99f), 0.f)),

	//Particle(glm::vec3(randomBetweenFloats(-0.99f, 0.99f), randomBetweenFloats(-0.99f, 0.99f), 0.f),			glm::vec3(randomBetweenFloats(-0.99f, 0.99f), randomBetweenFloats(-0.99f, 0.99f), 0.f)),
	//Particle(glm::vec3(randomBetweenFloats(-0.99f, 0.99f), randomBetweenFloats(-0.99f, 0.99f), 0.f),			glm::vec3(randomBetweenFloats(-0.99f, 0.99f), randomBetweenFloats(-0.99f, 0.99f), 0.f)),
	//Particle(glm::vec3(randomBetweenFloats(-0.99f, 0.99f), randomBetweenFloats(-0.99f, 0.99f), 0.f),			glm::vec3(randomBetweenFloats(-0.99f, 0.99f), randomBetweenFloats(-0.99f, 0.99f), 0.f)),
	//Particle(glm::vec3(randomBetweenFloats(-0.99f, 0.99f), randomBetweenFloats(-0.99f, 0.99f), 0.f),			glm::vec3(randomBetweenFloats(-0.99f, 0.99f), randomBetweenFloats(-0.99f, 0.99f), 0.f)),
	//Particle(glm::vec3(randomBetweenFloats(-0.99f, 0.99f), randomBetweenFloats(-0.99f, 0.99f), 0.f),			glm::vec3(randomBetweenFloats(-0.99f, 0.99f), randomBetweenFloats(-0.99f, 0.99f), 0.f)),

	//Particle(glm::vec3(randomBetweenFloats(-0.99f, 0.99f), randomBetweenFloats(-0.99f, 0.99f), 0.f),			glm::vec3(randomBetweenFloats(-0.99f, 0.99f), randomBetweenFloats(-0.99f, 0.99f), 0.f)),
	//Particle(glm::vec3(randomBetweenFloats(-0.99f, 0.99f), randomBetweenFloats(-0.99f, 0.99f), 0.f),			glm::vec3(randomBetweenFloats(-0.99f, 0.99f), randomBetweenFloats(-0.99f, 0.99f), 0.f)),
	//Particle(glm::vec3(randomBetweenFloats(-0.99f, 0.99f), randomBetweenFloats(-0.99f, 0.99f), 0.f),			glm::vec3(randomBetweenFloats(-0.99f, 0.99f), randomBetweenFloats(-0.99f, 0.99f), 0.f)),
	//Particle(glm::vec3(randomBetweenFloats(-0.99f, 0.99f), randomBetweenFloats(-0.99f, 0.99f), 0.f),			glm::vec3(randomBetweenFloats(-0.99f, 0.99f), randomBetweenFloats(-0.99f, 0.99f), 0.f)),
	//Particle(glm::vec3(randomBetweenFloats(-0.99f, 0.99f), randomBetweenFloats(-0.99f, 0.99f), 0.f),			glm::vec3(randomBetweenFloats(-0.99f, 0.99f), randomBetweenFloats(-0.99f, 0.99f), 0.f)),

	//Particle(glm::vec3(randomBetweenFloats(-0.99f, 0.99f), randomBetweenFloats(-0.99f, 0.99f), 0.f),			glm::vec3(randomBetweenFloats(-0.99f, 0.99f), randomBetweenFloats(-0.99f, 0.99f), 0.f)),
	//Particle(glm::vec3(randomBetweenFloats(-0.99f, 0.99f), randomBetweenFloats(-0.99f, 0.99f), 0.f),			glm::vec3(randomBetweenFloats(-0.99f, 0.99f), randomBetweenFloats(-0.99f, 0.99f), 0.f)),
	//Particle(glm::vec3(randomBetweenFloats(-0.99f, 0.99f), randomBetweenFloats(-0.99f, 0.99f), 0.f),			glm::vec3(randomBetweenFloats(-0.99f, 0.99f), randomBetweenFloats(-0.99f, 0.99f), 0.f)),
	//Particle(glm::vec3(randomBetweenFloats(-0.99f, 0.99f), randomBetweenFloats(-0.99f, 0.99f), 0.f),			glm::vec3(randomBetweenFloats(-0.99f, 0.99f), randomBetweenFloats(-0.99f, 0.99f), 0.f)),
	//Particle(glm::vec3(randomBetweenFloats(-0.99f, 0.99f), randomBetweenFloats(-0.99f, 0.99f), 0.f),			glm::vec3(randomBetweenFloats(-0.99f, 0.99f), randomBetweenFloats(-0.99f, 0.99f), 0.f)),

	//// particles to see the bounds
	//Particle(glm::vec3(-1.f, -1.f, 0.f),		glm::vec3(0.0f, 0.f, 0.f)), // bottom left corner
	//Particle(glm::vec3(-1.f, 1.f, 0.f),			glm::vec3(0.0f, 0.f, 0.f)), // top left corner
	//Particle(glm::vec3(1.f, 1.f, 0.f),			glm::vec3(0.0f, 0.f, 0.f)), // top right corner
	//Particle(glm::vec3(1.f, -1.f, 0.f),			glm::vec3(0.0f, 0.f, 0.f)) // bottom right corner
//};

float SmoothingKernel(float radius, float dst) {
	float volume = PI * pow(radius, 8) / 4;
	float value = std::max(0.f, radius * radius - dst * dst);
	return value * value * value / volume;
}

float calculateDensity(Particle* particles, glm::vec4 position, float mass) {
	float density = 0.f;

	for (int i = 0; i < amountOfParticles; ++i)
	{
		glm::vec2 currentParticlePosition = glm::vec2(particles[i].position[0], particles[i].position[1]);
		glm::vec2 samplePoint = glm::vec2(position[0], position[1]);
		glm::vec2 vectorsSubstracted = currentParticlePosition - samplePoint;
		float dst = sqrt((vectorsSubstracted[0] * vectorsSubstracted[0]) + (vectorsSubstracted[1] * vectorsSubstracted[1]));
		float mass = particles[i].extra[1];
		float influence = SmoothingKernel(particles[i].extra[0], dst);
		density += mass * influence;
	}

	return density;
}

Particle* fillParticlesArray(Particle* particles)
{
	// generating the seed for the random generation, so it can be different on each run.
	srand((unsigned int)time(NULL));

	particles = new Particle[amountOfParticles];
	for (int i = 0; i < amountOfParticles; i++)
	{
		particles[i].setPosition(glm::vec4(randomBetweenFloats(0.0f, 0.99f), randomBetweenFloats(0.f, 0.99f), 0.f, 0.f));
		particles[i].setVelocity(glm::vec4(randomBetweenFloats(0.f, 0.3f), randomBetweenFloats(0.f, 0.3f), 0.f, 0.f));
		//particles[i].setExtra(glm::vec4(randomBetweenFloats(0.f, 0.3f), randomBetweenFloats(0.f, 0.3f), 0.f, 0.f));
		particles[i].setRadius(randomBetweenFloats(15.f, 35.0f));
		particles[i].setMass(randomBetweenFloats(0.1f, 3.0f));
		particles[i].setProperty(1.f);
	}
	// preCalculate densities
	for (int i = 0; i < amountOfParticles; i++)
	{
		particles[i].setDensity(calculateDensity(particles, particles[i].position, particles[i].extra[1]));
	}
	return particles;
};
Particle* particles = fillParticlesArray(particles);

//unsigned int nrOfParticles = sizeof(particles) / sizeof(Particle);
unsigned int nrOfParticles = amountOfParticles;
bool printNr(unsigned int nr) {
	std::cout << "nrOfParticles: " << nr << "\n";
	return true;
};
bool result = printNr(amountOfParticles);
const GLuint particlesFloats = nrOfParticles * 12;
const int pointSize = 7;


Vertex vertices[] =
{
	// Position							// Color						// Texcoords			// Normals
	glm::vec3(-0.5f, 0.5f, 0.f),		glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, 1.f),	glm::vec3(0.f, 0.f, -1.f),
	glm::vec3(-0.5f, -0.5f, 0.f),		glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.f, 0.f),	glm::vec3(0.f, 0.f, -1.f),
	glm::vec3(0.5f, -0.5f, 0.f),		glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),	glm::vec3(0.f, 0.f, -1.f),
	glm::vec3(0.5f, 0.5f, 0.f),			glm::vec3(1.f, 1.f, 0.f),		glm::vec2(1.f, 1.f),	glm::vec3(0.f, 0.f, -1.f)
};
unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

GLuint indices[] =
{
	0, 1, 2, // Triangle 1
	0, 2, 3  // Triangle 2
};
unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);


void reshape(GLFWwindow* window, int fbW, int fbH) {

	//update resolution
	WINDOW_WIDTH = fbW;
	WINDOW_HEIGHT = fbH;

	glViewport(0, 0, fbW, fbH);
}


void updateInput(GLFWwindow* window, glm::vec3& position, glm::vec3& rotation, glm::vec3& scale)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		position.z -= 0.01f;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		position.z += 0.01f;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		position.x -= 0.01f;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		position.x += 0.01f;
	}

	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
		rotation.y -= 1.f;
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
		rotation.y += 1.f;
	}

	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
		scale += 0.1f;
	}
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
		scale -= 0.1f;
	}
}

void printBufferContent(GLuint bufferId) {
	glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, bufferId);

	// to print the value stored in the buffer
	GLfloat* view = new GLfloat[particlesFloats];
	glGetBufferSubData(GL_TRANSFORM_FEEDBACK_BUFFER, 0, particlesFloats, view);

	std::cout << "bufferContent: ";
	for (int i = 0; i < particlesFloats; i++) {
		std::cout << view[i] << " . ";
	}
	std::cout << "\n";

	glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, NULL);
}

int main() {

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

	// SHADER INIT
	Shader core_program("vertex_core.glsl", "fragment_core.glsl");

	//const GLchar* feedbackVaryings[] = { "outPosition", "outVelocity", "outExtra" };
	//Shader particles_program("vertex_particles.glsl", "fragment_particles.glsl", "", feedbackVaryings, 3);
	Shader particles_program("vertex_particles.glsl", "fragment_particles.glsl", "");

	Shader compute_program("compute_particles.glsl");

	//MODEL

	//VAO, VBO, EBO  (buffers)
	// Generate VAO and BIND, this is like a box where we want to store data
	GLuint VAO; // vertex array object
	glCreateVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// Generate VBO and BIND and SEND DATA, this sends the vertices data to the graphics card
	GLuint VBO; // vertex buffer object
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // static becase we don't wanna change this data too much, otherwise it should be GL_DYNAMIC_DRAW (have to read about this)

	// Generate EBO and BIND and SEND DATA, this sends the indices data to the graphics card
	GLuint EBO; // Element buffer object
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	// SET VERTEXATTRIBPOINTERS AND ENABLE (a process called INPUT ASSEMBLY)
	// here we let the graphics card know how is the data divided within the array, what is a pixel, what is a color and what is a texcoord
	// Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);
	// Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
	glEnableVertexAttribArray(1);
	// Texcoord
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord));
	glEnableVertexAttribArray(2);
	// Normal
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(3);

	// BIND VAO 0
	glBindVertexArray(0);

	// PARTICLES
	GLuint particles_VBO1, particles_VBO2, particles_VAO1, particles_VAO2;

	glCreateVertexArrays(1, &particles_VAO1);
	glBindVertexArray(particles_VAO1);

	glGenBuffers(1, &particles_VBO1);
	/*glBindBuffer(GL_ARRAY_BUFFER, particles_VBO1);
	glBufferData(GL_ARRAY_BUFFER, nrOfParticles * sizeof(Particle), particles, GL_DYNAMIC_COPY);*/

	glBindBuffer(GL_SHADER_STORAGE_BUFFER, particles_VBO1);
	//glBufferData(GL_SHADER_STORAGE_BUFFER, nrOfParticles * sizeof(Particle), particles, GL_DYNAMIC_COPY);
	glBufferData(GL_SHADER_STORAGE_BUFFER, nrOfParticles * sizeof(Particle), particles, GL_DYNAMIC_DRAW);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, particles_VBO1);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Particle), (GLvoid*)offsetof(Particle, position));
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Particle), (GLvoid*)offsetof(Particle, velocity));
	std::cout << "extra: ......" << particles << "\n";
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Particle), (GLvoid*)offsetof(Particle, extra));
	glEnableVertexAttribArray(0);
	//glEnableVertexAttribArray(1);
	//glEnableVertexAttribArray(2);

	glBindVertexArray(0);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

	glCreateVertexArrays(1, &particles_VAO2);
	glBindVertexArray(particles_VAO2);

	glGenBuffers(1, &particles_VBO2);
	/*glBindBuffer(GL_ARRAY_BUFFER, particles_VBO2);
	glBufferData(GL_ARRAY_BUFFER, nrOfParticles * sizeof(Particle), particles, GL_DYNAMIC_COPY);*/

	glBindBuffer(GL_SHADER_STORAGE_BUFFER, particles_VBO2);
	glBufferData(GL_SHADER_STORAGE_BUFFER, nrOfParticles * sizeof(Particle), particles, GL_DYNAMIC_DRAW);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, particles_VBO2);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Particle), (GLvoid*)offsetof(Particle, position));
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Particle), (GLvoid*)offsetof(Particle, velocity));
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Particle), (GLvoid*)offsetof(Particle, extra));
	glEnableVertexAttribArray(0);
	//glEnableVertexAttribArray(1);
	//glEnableVertexAttribArray(2);

	glBindVertexArray(0);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

	// TEXTURE INIT
	//TEXTURE0
	Texture texture0("Images/cat.png", GL_TEXTURE_2D, 0);

	//TEXTURE1
	Texture texture1("Images/container.png", GL_TEXTURE_2D, 1);

	//MATERIAL0
	Material material0(glm::vec3(0.1f), glm::vec3(1.f), glm::vec3(2.f), texture0.getTextureUnit(), texture1.getTextureUnit());


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

	//LIGHTS
	glm::vec3 lightPos0(0.f, 0.f, 2.f);

	//sending operations (rotation, translation, scaling) to the shader
	// INIT UNIFORMS

	core_program.setMat4fv(ModelMatrix, "ModelMatrix");
	core_program.setMat4fv(ViewMatrix, "ViewMatrix");
	core_program.setMat4fv(ProjectionMatrix, "ProjectionMatrix");

	core_program.setVec3f(lightPos0, "lightPos0");
	core_program.setVec3f(camPosition, "camPosition");

	particles_program.setMat4fv(ModelMatrix, "ModelMatrix");
	particles_program.setMat4fv(ViewMatrix, "ViewMatrix");
	particles_program.setMat4fv(ProjectionMatrix, "ProjectionMatrix");
	particles_program.setVec2f(glm::fvec2((GLfloat)WINDOW_WIDTH, (GLfloat)WINDOW_HEIGHT), "resolution");


	GLuint active_vao = particles_VAO1, active_vbo = particles_VBO2;  // Alternar entre los buffers

	GLdouble timeValue = customTimer(0.0);

	// MAIN LOOP
	while (!glfwWindowShouldClose(window)) {
		// UPDATE INPUT
		glfwPollEvents(); // Will let the cursor interact with the window

		//UPDATE
		updateInput(window, position, rotation, scale);

		// PER FRAME TIME LOGIC
		//GLfloat timeValue = (GLfloat)glfwGetTime();
		timeValue = customTimer(timeValue);

		//DRAW
		//Clear
		glClearColor(0.f, 0.f, 0.0f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);


		// Update Uniforms
		core_program.set1i(texture0.getTextureUnit(), "texture0");
		core_program.set1i(texture1.getTextureUnit(), "texture1");
		material0.sendToShader(core_program);

		// Move rotate and scale
		ModelMatrix = glm::mat4(1.f); // Identity matrix
		ModelMatrix = glm::translate(ModelMatrix, position);
		ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.x), glm::vec3(1.f, 0.f, 0.f));
		ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.y), glm::vec3(0.f, 1.f, 0.f));
		ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.z), glm::vec3(0.f, 0.f, 1.f));
		ModelMatrix = glm::scale(ModelMatrix, scale);

		core_program.setMat4fv(ModelMatrix, "ModelMatrix");
		particles_program.setMat4fv(ModelMatrix, "ModelMatrix");

		glfwGetFramebufferSize(window, &frameBufferWidth, &frameBufferHeight);

		ProjectionMatrix = glm::perspective(
			glm::radians(fov),
			static_cast<float>(frameBufferWidth) / frameBufferHeight,
			nearPlane,
			farPlane
		);

		core_program.setMat4fv(ProjectionMatrix, "ProjectionMatrix");
		particles_program.setMat4fv(ProjectionMatrix, "ProjectionMatrix");
		particles_program.setVec2f(glm::fvec2((GLfloat)WINDOW_WIDTH, (GLfloat)WINDOW_HEIGHT), "resolution");

		//std::cout << "time: " << timeValue << "\n";
		core_program.set1f(timeValue, "time");
		particles_program.set1f(timeValue, "time");
		compute_program.set1f(timeValue, "time");

		// Use a program
		core_program.use();

		// Activate texture
		texture0.bind();
		texture1.bind();

		// Bind vertex array object (VAO)
		glBindVertexArray(VAO);

		//Draw
		//glDrawArrays(GL_TRIANGLES, 0, nrOfVertices);// this is an alternative way to draw
		// the one used below:
		//glDrawElements(GL_TRIANGLES, nrOfIndices, GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);

		core_program.unuse();

		// USING COMPUTE SHADER (to calc physics)
		compute_program.use();

		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, active_vbo);
		glDispatchCompute(amountOfParticles / 128, 1, 1);
		//glMemoryBarrier(GL_ALL_BARRIER_BITS);
		glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);

		compute_program.unuse();


		particles_program.use();



		glEnable(GL_RASTERIZER_DISCARD);  // Deshabilitar la rasterización (solo queremos actualizar datos)


		glBindVertexArray(active_vao);

		glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, active_vbo);

		glBeginTransformFeedback(GL_POINTS);

		//glPointSize(pointSize);
		// Drawing particles without indices
		glDrawArrays(GL_POINTS, 0, nrOfParticles);

		glEndTransformFeedback();

		glBindVertexArray(0);
		glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, NULL);

		// Swap  - WHEN USING COMPUTE SHADERS AND SSBO APPARENTLY THIS IS NO NEEDED
		/*if (active_vao == particles_VAO1) {
			active_vao = particles_VAO2;
			active_vbo = particles_VBO1;
		}
		else {
			active_vao = particles_VAO1;
			active_vbo = particles_VBO2;
		}*/

		glDisable(GL_RASTERIZER_DISCARD);


		// printBufferContent(particles_VBO2);


		glBindBuffer(GL_ARRAY_BUFFER, particles_VBO1);
		glBindVertexArray(particles_VAO1);

		// Drawing particles without indices
		glDrawArrays(GL_POINTS, 0, nrOfParticles);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(0);


		//End draw
		glfwSwapBuffers(window);
		glFlush();

		// glBindVertexArray(0);
		glUseProgram(0);
		glActiveTexture(0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	//END OF PROGRAM
	glfwDestroyWindow(window);
	glfwTerminate();


	return 0;
}
