#pragma once
#include "image.h"
#include "main.h"
#include "packages/nupengl.core.0.1.0.1/build/native/include/GL/glew.h"

class Texture
{
public:
	unsigned int id;
	unsigned int type;
	Texture(unsigned int type, char* name):type(type)
	{
		switch(type)
		{
		case GL_TEXTURE_CUBE_MAP:
			id = cubeMap(name);
			break;
		case GL_TEXTURE_2D:
			id = twoD(name);
				break;
		}
	}

	void bind()
	{
		glBindTexture(type, id); //This binds it to GL_TEXTURE0, used by default
	}

	void bind(int activeId)
	{
		glActiveTexture(GL_TEXTURE0 + activeId);
		glBindTexture(type, activeId);
	}

private:
	static unsigned int twoD(char* name)
	{
		GLuint textureID;
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);

		Image image(name);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.width, image.height, 0, GL_BGR, GL_UNSIGNED_BYTE, image.bgr);
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		
		glBindTexture(GL_TEXTURE_2D, 0);
		return textureID;
	}

	static unsigned int cubeMap(char* namePrefix)
	{
		GLuint textureID;
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

		char faces[6][50];
		char* names[6] = { "right.bmp", "left.bmp", "top.bmp", "bottom.bmp", "back.bmp", "front.bmp" };
		for (int i = 0;  i < 6; i++)
		{
			strcpy(faces[i], namePrefix);
			strcat(faces[i], names[i]);
		}
		for (GLuint i = 0; i < 6; i++)
		{
			Image image(faces[i]);
			glTexImage2D(
				GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0,
				GL_RGB, image.width, image.height, 0, GL_BGR, GL_UNSIGNED_BYTE, image.bgr
			);

		}
		glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
		return textureID;
	}
};
