#include"Shader.h"

// Reads a text file and outputs a string with everything in the text file
std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

// Constructor that creates an Shader Program Object using the Builder Pattern or something similar
Shader::Shader()
{

}

// Attach Shader File to the Shader Program
void Shader::Attach(const char* file, GLenum shaderType)
{
	// Read Shader File and store the string
	std::string code = get_file_contents(file);

	// Convert the shader source string into character array
	const char* source = code.c_str();

	// Create Shader Object and get its reference
	GLuint shader = glCreateShader(shaderType);
	shaders.push_back(shader);
	// Attach Shader Source to the Shader Object
	glShaderSource(shader, 1, &source, NULL);
	// Compile the Shader into machine code
	glCompileShader(shader);
	// Checks if Shader compiled succesfully
	compileErrors(shader, file);
}

// Build the Shader Program
void Shader::Build()
{
	// Create Shader Program Object and get its reference
	ID = glCreateProgram();
	// Attach the Shaders to the Shader Program
	for (GLuint shader : shaders)
	{
		glAttachShader(ID, shader);
	}
	// Wrap-up/Link all the shaders together into the Shader Program
	glLinkProgram(ID);
	// Checks if Shaders linked succesfully
	compileErrors(ID, "PROGRAM");

	// Delete the now useless Shader objects
	for (GLuint shader : shaders)
	{
		glDeleteShader(shader);
	}
}

// Activates the Shader Program
void Shader::Activate()
{
	glUseProgram(ID);
}

// Deletes the Shader Program
void Shader::Delete()
{
	glDeleteProgram(ID);
}

// Checks if the different Shaders have compiled properly
void Shader::compileErrors(unsigned int shader, const char* type)
{
	// Stores status of compilation
	GLint hasCompiled;
	// Character array to store error message in
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for: " << type << "\n" << infoLog << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for: " << type << "\n" << infoLog << std::endl;
		}
	}
}