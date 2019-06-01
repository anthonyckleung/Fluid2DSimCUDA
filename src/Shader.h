#ifndef SHADER_H
#define SHADER_H


#include <string>

#include "GL/glew.h"
#include "glm/glm.hpp"
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
	Shader() {}

	GLuint m_ID;

	Shader &Use();
	// Compile shader
	void Compile(const GLchar *vertexSource, const GLchar *fragmentSource, 
		            const GLchar *geometrySource = nullptr); // Note: geometry source code is optional

	// Utility functions
	void SetTextureUnit(const GLchar *name, GLint textureUnit, GLboolean useShader = false);
	void SetFloat(const GLchar *name, GLfloat value, GLboolean useShader = false);
	void SetInteger(const GLchar *name, GLint value, GLboolean useShader = false);
	void SetVector2f(const GLchar *name, GLfloat x, GLfloat y, GLboolean useShader = false);
	void SetVector2f(const GLchar *name, const glm::vec2 &value, GLboolean useShader = false);
	void SetVector3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader = false);
	void SetVector3f(const GLchar *name, const glm::vec3 &value, GLboolean useShader = false);
	void SetVector4f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader = false);
	void SetVector4f(const GLchar *name, const glm::vec4 &value, GLboolean useShader = false);
	void SetMatrix4(const GLchar *name, const glm::mat4 &matrix, GLboolean useShader = false);

private: 
	void checkCompileErrors(GLuint object, std::string type);
};

#endif //SHADER_H
