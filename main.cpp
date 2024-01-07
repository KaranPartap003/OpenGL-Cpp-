#include "config.h"
#include "triangle_mesh.h"
#include "Material.h"
#include "algebra.h"


//function to create shader modules 
unsigned int make_module(const std::string& filepath, unsigned int module_type)
{
	std::ifstream file;
	std::stringstream bufferedLine;
	std::string line;

	file.open(filepath);

	while (std::getline(file, line))
	{
		bufferedLine << line << "\n";
	}
	std::string shaderSource = bufferedLine.str();
	//converting string into C equivalent char array for glShaderSource 
	const char* shaderSrc = shaderSource.c_str();
	bufferedLine.str("");
	file.close();

	//creating shader
	unsigned int shaderModule = glCreateShader(module_type);
	//specifying shader source
	glShaderSource(shaderModule, 1, &shaderSrc, NULL);
	//compiling shader
	glCompileShader(shaderModule);

	//checking whether the shader has been compiled or not
	int status;
	glGetShaderiv(shaderModule, GL_COMPILE_STATUS, &status);//iv = integer value, int status will be used to acces the error codes(if any)
	if (!status)
	{
		char errorLog[1024];
		glGetShaderInfoLog(shaderModule, 1024, NULL, errorLog);
		std::cout << "Shader Module Compilation error :\n" << errorLog << std::endl;
	}

	return shaderModule;

}

//function to create shader program
unsigned int make_program(const std::string& vertexShader, const std::string& fragmentShader)
{
	std::vector<unsigned int> modules;
	modules.push_back(make_module(vertexShader, GL_VERTEX_SHADER));
	modules.push_back(make_module(fragmentShader, GL_FRAGMENT_SHADER));

	unsigned int program = glCreateProgram();
	//linking each module to the shader program
	for (auto shaderModule : modules)
	{
		glAttachShader(program, shaderModule);
	}
	glLinkProgram(program);

	//checking for erors
	int status;
	glGetProgramiv(program, GL_LINK_STATUS, &status);//iv = integer value, int status will be used to acces the error codes(if any)
	if (!status)
	{
		char errorLog[1024];
		glGetProgramInfoLog(program, 1024, NULL, errorLog);
		std::cout << "Shader program Linking error :\n" << errorLog << std::endl;
	}

	//deleting shaders after linking
	for (auto shaderModule : modules)
	{
		glDeleteShader(shaderModule);
	}

	return program;

}


int main() {
	GLFWwindow* window;

	if (!glfwInit()) {
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

	window = glfwCreateWindow(640, 480, "Hello Window!", NULL, NULL);
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Couldn't load opengl" << std::endl;
		glfwTerminate();
		return -1;
	}

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	//creating triangle object
	TriangleMesh* triangle = new TriangleMesh();

	//creating material
	Material* material = new Material((char*)"img/image.jpg");
	Material* mask = new Material((char*)"img/mask.jpg");

	//creating shader program
	unsigned int shaderProgram = make_program("shaders/vertexShader.txt", "shaders/fragmentShader.txt");

	//set texture units
	glUseProgram(shaderProgram);
	glUniform1i(glGetUniformLocation(shaderProgram, "material"), 0);
	glUniform1i(glGetUniformLocation(shaderProgram, "mask"), 1);

	unsigned int model_location = glGetUniformLocation(shaderProgram, "model");
	unsigned int view_location = glGetUniformLocation(shaderProgram, "view");
	unsigned int proj_location = glGetUniformLocation(shaderProgram, "projection");

	vec3 quad_position = { 0.1f, -0.2f, 0.0f };
	vec3 camera_pos = { -1.0f, 0.0f, 2.0f };
	vec3 camera_target = { 0.0f, 0.0f, 0.0f };

	mat4 view = create_look_at(camera_pos, camera_target);
	glUniformMatrix4fv(view_location, 1, GL_FALSE, view.entries);
	mat4 projection = create_prespective_projection(45.0f, 1.33f, 0.1f, 10.0f);
	glUniformMatrix4fv(proj_location, 1, GL_FALSE, projection.entries);
	
	//enabling alpha blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		//rotating image
		mat4 model = create_model_transform(quad_position, 50 * glfwGetTime());
		glUniformMatrix4fv(model_location, 1, GL_FALSE, model.entries);

		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		material->use(0);
		mask->use(1);
		triangle->draw();
		

		glfwSwapBuffers(window);
	}
	glDeleteProgram(shaderProgram);
	delete triangle;
	delete material;
	delete mask;
	glfwTerminate();
	return 0;
}

