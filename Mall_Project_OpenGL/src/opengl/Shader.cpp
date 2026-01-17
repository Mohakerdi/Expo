// ==================== Shader.cpp (الكود الجديد - مع التصحيح) ====================
#include "Shader.h"
#include <iostream>
#include <fstream>
#include <vector>

// NOTE: I am assuming your error handling macros/functions (GLCall, etc.) are defined elsewhere, e.g., in Shader.h
// If not, you might need to include the file that defines them.

Shader::Shader(const std::string& filepath) : m_FilePath(filepath), m_RendererID(0)
{
	ShaderSource shaderSource = ParseShader(filepath);
	if (shaderSource.vertexSource.empty() || shaderSource.FragmentSource.empty())
	{
		std::cerr << "[Shader Error] Failed to parse shader from single file: " << filepath << std::endl;
		m_RendererID = 0; // Ensure ID is 0 on failure
		return;
	}
	m_RendererID = CreateShader(shaderSource.vertexSource, shaderSource.FragmentSource);
}

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
{
	m_FilePath = "Vertex Shader Path : " + vertexPath + " | Fragment Shader Path : " + fragmentPath;
	ShaderSource shaderSource;
	shaderSource.vertexSource = readShader(vertexPath);
	shaderSource.FragmentSource = readShader(fragmentPath);

	if (shaderSource.vertexSource.empty() || shaderSource.FragmentSource.empty())
	{
		std::cerr << "[Shader Error] One or both shader files are empty or could not be read." << std::endl;
		m_RendererID = 0; // Ensure ID is 0 on failure
		return;
	}

	m_RendererID = CreateShader(shaderSource.vertexSource, shaderSource.FragmentSource);
}

Shader::~Shader()
{
	if (m_RendererID != 0)
	{
		glDeleteProgram(m_RendererID);
	}
}

std::string Shader::readShader(const std::string& path) const
{
	std::ifstream stream(path);
	if (!stream.is_open()) {
		std::cerr << "Error: Could not open shader file at path: " << path << std::endl;
		return "";
	}
	std::string line;
	std::string s = "";
	while (getline(stream, line)) {
		s += line + "\n";
	}
	return s;
}

void Shader::Bind() const
{
	if (m_RendererID != 0)
	{
		glUseProgram(m_RendererID);
	}
}

void Shader::Unbind() const
{
	glUseProgram(0);
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		std::vector<char> message(length);
		glGetShaderInfoLog(id, length, &length, &message[0]);
		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
		std::cout << &message[0] << std::endl;
		glDeleteShader(id);
		return 0;
	}

	return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	if (vs == 0 || fs == 0)
	{
		if (vs != 0) glDeleteShader(vs);
		if (fs != 0) glDeleteShader(fs);
		glDeleteProgram(program);
		return 0;
	}

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);

	int link_result;
	glGetProgramiv(program, GL_LINK_STATUS, &link_result);
	if (link_result == GL_FALSE) {
		int length;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
		std::vector<char> message(length);
		glGetProgramInfoLog(program, length, &length, &message[0]);
		std::cout << "Failed to link shader program!" << std::endl;
		std::cout << &message[0] << std::endl;

		glDeleteProgram(program);
		glDeleteShader(vs);
		glDeleteShader(fs);
		return 0;
	}

	glValidateProgram(program);
	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

ShaderSource Shader::ParseShader(const std::string& filepath) const
{
	std::ifstream stream(filepath);
	if (!stream.is_open()) {
		std::cerr << "Error: Could not open shader file for parsing at path: " << filepath << std::endl;
		return { "", "" };
	}

	enum class Type {
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	Type type = Type::NONE;
	std::string s[2] = { "", "" };

	while (getline(stream, line)) {
		if (line.find("#shader") != std::string::npos) {
			if (line.find("vertex") != std::string::npos) {
				type = Type::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos) {
				type = Type::FRAGMENT;
			}
		}
		else {
			if (type != Type::NONE) {
				s[(int)type] += line + "\n";
			}
		}
	}

	return { s[0], s[1] };
}

// All functions below now call getUniformLoacation (with the typo) to match your .h file
void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	glUniform4f(getUniformLoacation(name), v0, v1, v2, v3);
}

void Shader::setUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
	glUniformMatrix4fv(getUniformLoacation(name), 1, GL_FALSE, &matrix[0][0]);
}

void Shader::SetUniform4fv(const std::string& name, glm::vec4 vec)
{
	glUniform4fv(getUniformLoacation(name), 1, &vec[0]);
}

void Shader::SetUniform3f(const std::string& name, float v0, float v1, float v2)
{
	glUniform3f(getUniformLoacation(name), v0, v1, v2);
}

void Shader::SetUniform3fv(const std::string& name, glm::vec3 vec)
{
	glUniform3fv(getUniformLoacation(name), 1, &vec[0]);
}

void Shader::SetUniform1i(const std::string& name, int value)
{
	glUniform1i(getUniformLoacation(name), value);
}

void Shader::SetUniform1f(const std::string& name, float value)
{
	glUniform1f(getUniformLoacation(name), value);
}

// Definition now matches the name in your .h file
int Shader::getUniformLoacation(const std::string& name)
{
	if (m_UniformLoactionCache.find(name) != m_UniformLoactionCache.end())
		return m_UniformLoactionCache[name];

	int location = glGetUniformLocation(m_RendererID, name.c_str());
	if (location == -1)
		std::cout << "Warning: uniform '" << name << "' doesn't exist or is not used." << std::endl;

	m_UniformLoactionCache[name] = location;
	return location;
}
