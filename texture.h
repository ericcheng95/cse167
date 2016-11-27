#pragma once
#include "image.h"
#include "main.h"
#include "packages/nupengl.core.0.1.0.1/build/native/include/GL/glew.h"

class Texture
{
public:
	unsigned int id;
	Texture(unsigned int type, char* namePrefix)
	{
		switch(type)
		{
		case GL_TEXTURE_CUBE_MAP:
			id = cubeMap(namePrefix);
			break;
		}
	}

	void bind()
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP, id); //This binds it to 0, used by default
	}

	void bind(int activeId)
	{
		glActiveTexture(GL_TEXTURE0 + activeId);
		glBindTexture(GL_TEXTURE_CUBE_MAP, activeId);
	}

private:
	static unsigned int cubeMap(char* namePrefix)
	{
		GLuint textureID;
		glGenTextures(1, &textureID);
		glActiveTexture(GL_TEXTURE0);

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
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

		return textureID;
	}
};
