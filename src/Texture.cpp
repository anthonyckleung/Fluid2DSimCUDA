#include "Texture.h"



Texture::Texture()
{
}


Texture::~Texture()
{
}

void Texture::Generate(GLuint width, GLuint height, unsigned char * data)
{
	this->m_Width = width;
	this->m_Height = height;
	// Create Texture
	glBindTexture(GL_TEXTURE_2D, this->m_ID);
	glTexImage2D(GL_TEXTURE_2D, 0, this->m_Internal_Format, width, height, 0, this->m_Image_Format, GL_UNSIGNED_BYTE, data);
	// Set Texture wrap and filter modes
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->m_Wrap_S);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->m_Wrap_T);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->m_Filter_Min);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->m_Filter_Max);
	// Unbind texture
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Bind() const
{
	glBindTexture(GL_TEXTURE_2D, this->m_ID);
}