#include "Model.h"

Model::Model(vector<GLfloat>& vertices, vector<GLfloat>& normals, vector<GLuint>& faceVertexIndices):vertices(vertices), normals(normals), faceVertexIndices(faceVertexIndices)
{
	findMinMax(vertices);

	count = (int)(faceVertexIndices.size());

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &VBON);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], g_BufferUsage);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

	glBindBuffer(GL_ARRAY_BUFFER, VBON);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(GLfloat), &normals[0], g_BufferUsage);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, faceVertexIndices.size() * sizeof(GLuint), &faceVertexIndices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	computeFaceSegments();
}

//void Model::updateData(vector<GLfloat>& vertices, vector<GLfloat>& normals)
//{
//	findMinMax(vertices);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(GLfloat), &vertices[0]);
//	glBindBuffer(GL_ARRAY_BUFFER, VBON);
//	glBufferSubData(GL_ARRAY_BUFFER, 0, normals.size() * sizeof(GLfloat), &normals[0]);
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//}
//
//void Model::updateData(vector<GLfloat>& vertices)
//{
//	findMinMax(vertices);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(GLfloat), &vertices[0]);
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//}

Model::Model(char* filepath):Model(filepath, nullptr)
{
	
}

Model::Model(char* filepath, Texture* texture):texture(texture)
{
	FILE* fp; // file pointer
	GLfloat x, y, z, u, v; // vertex/texture coordinates
	GLuint xi, yi, zi, xn, yn, zn, xt, yt, zt; // vertex color
	int c1, c2; // characters read from file
	fp = fopen(filepath, "rb"); // make the file name configurable so you can load other files
	if (fp == nullptr) { cout << "error loading file " << filepath << endl; } // just in case the file can't be found or is corrupt
	cout << "Loading..." << endl;
	while (!feof(fp))
	{
		c1 = fgetc(fp);
		if (c1 == 'f')
		{
			fgetc(fp);
			if (!hasTextureCoords) {
				fscanf(fp, "%d//%d %d//%d %d//%d", &xi, &xn, &yi, &yn, &zi, &zn);
				faceVertexIndices.push_back(xi - 1);
				faceVertexIndices.push_back(yi - 1);
				faceVertexIndices.push_back(zi - 1);
			}
			else
			{
				fscanf(fp, "%d/%d/%d %d/%d/%d %d/%d/%d", &xi,&xt, &xn, &yi,&yt, &yn, &zi,&zt, &zn);
				faceVertexIndices.push_back(xi - 1);
				faceVertexIndices.push_back(yi - 1);
				faceVertexIndices.push_back(zi - 1);
				textureIndices.push_back(xt - 1);
				textureIndices.push_back(yt - 1);
				textureIndices.push_back(zt - 1);
			}
		}
		else if (c1 == 'v')
		{
			c2 = fgetc(fp);
			if (c2 == ' ')
			{
				fscanf(fp, "%f %f %f", &x, &y, &z);
				vertices.push_back(x);
				vertices.push_back(y);
				vertices.push_back(z);
			}
			else if (c2 == 'n' && fgetc(fp) == ' ')
			{
				fscanf(fp, "%f %f %f", &x, &y, &z);
				normals.push_back(x);
				normals.push_back(y);
				normals.push_back(z);
			}
			else if (c2 == 't' && fgetc(fp) == ' ')
			{
				hasTextureCoords = true;
				fscanf(fp, "%f %f", &u, &v);
				textures.push_back(u);
				textures.push_back(v);
			}
		}
		while (!feof(fp) && fgetc(fp) != '\n');
	}
	fclose(fp);

	findMinMax(vertices);

	

	count = (int)(faceVertexIndices.size());

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &VBON);
	glGenBuffers(1, &EBO);
	if (hasTextureCoords)
	{
		glGenBuffers(1, &VBOT);
	}

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], g_BufferUsage);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

	glBindBuffer(GL_ARRAY_BUFFER, VBON);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(GLfloat), &normals[0], g_BufferUsage);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	
	if (hasTextureCoords) {
		glBindBuffer(GL_ARRAY_BUFFER, VBOT);
		glBufferData(GL_ARRAY_BUFFER, textures.size() * sizeof(GLfloat), &textures[0], g_BufferUsage);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, faceVertexIndices.size() * sizeof(GLuint), &faceVertexIndices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	computeFaceSegments();
}


Model::~Model()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &VBON);
	glDeleteBuffers(1, &EBO);
}

void Model::draw()
{
//	if (texture != nullptr)
//	{
//		texture->bind();
//	}
	glBindVertexArray(VAO);
	glDrawElements(g_DrawMode, count, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Model::findMinMax(vector<GLfloat>& vertices)
{
	for (int i = 0; i < vertices.size(); i++)
	{
		if (vertices[i] < minX)
		{
			minX = vertices[i];
		}
		else if (vertices[i] > maxX)
		{
			maxX = vertices[i];
		}
		i++;
		if (vertices[i] < minY)
		{
			minY = vertices[i];
		}
		else if (vertices[i] > maxY)
		{
			maxY = vertices[i];
		}
		i++;
		if (vertices[i] < minZ)
		{
			minZ = vertices[i];
		}
		else if (vertices[i] > maxZ)
		{
			maxZ = vertices[i];
		}
	}
}

void Model::computeFaceSegments()
{

	int count = vertices.size() / 3;
	vector<Segment*> map(count * count);
	for (int i = 0; i < faceVertexIndices.size(); i+=3)
	{
		int i1 = faceVertexIndices[i] * 3;
		int i2 = faceVertexIndices[i+1] * 3;
		int i3 = faceVertexIndices[i+2] * 3;
		vec3 a = vec3(vertices[i1], vertices[i1 + 1], vertices[i1 + 2]);
		vec3 b = vec3(vertices[i2], vertices[i2 + 1], vertices[i2 + 2]);
		vec3 c = vec3(vertices[i3], vertices[i3 + 1], vertices[i3 + 2]);
		Face* f = new Face{ a,b,c, cross(a-b, c-b)};
		int index = faces.size();
		faces.push_back(f);
		
		if (map[i1*count + i2] == nullptr)
		{
			Segment* s = new Segment();
			s->a = a;
			s->b = b;
			s->f1 = index;
			s->f2 = -1;
			map[i1*count + i2] = s;
			segments.push_back(s);
		}
		else
		{
			map[i1*count + i2]->f2 = index;
		}
		if (map[i2*count + i3] == nullptr)
		{
			Segment* s = new Segment();
			s->a = b;
			s->b = c;
			s->f1 = index;
			s->f2 = -1;
			map[i2*count + i3] = s;
			segments.push_back(s);
		}
		else
		{
			map[i2*count + i3]->f2 = index;
		}
		if (map[i3*count + i1] == nullptr)
		{
			Segment* s = new Segment();
			s->a = c;
			s->b = a;
			s->f1 = index;
			s->f2 = -1;
			map[i3*count + i1] = s;
			segments.push_back(s);
		}
		else
		{
			map[i3*count + i1]->f2 = index;
		}
	}
}
