#include "pch.h"

void SkeMesh::Init()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);


	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, m_Vertexs.size()*sizeof(SkeVertex), &m_Vertexs[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(unsigned int), &m_Indices[0], GL_STATIC_DRAW);

	size_t stride = sizeof(SkeVertex);


	size_t offset = 0;

	
	glEnableVertexAttribArray(SHADER_POSITION_ATTRIBUTE);
	glVertexAttribPointer(SHADER_POSITION_ATTRIBUTE, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)offset);
	offset += 3 * sizeof(float);


	
	glEnableVertexAttribArray(SHADER_NORMAL_ATTRIBUTE);
	glVertexAttribPointer(SHADER_NORMAL_ATTRIBUTE, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)offset);
	offset += 3 * sizeof(float);



	
	glEnableVertexAttribArray(SHADER_TEXCOORD_ATTRIBUTE);
	glVertexAttribPointer(SHADER_TEXCOORD_ATTRIBUTE, 2, GL_FLOAT, GL_FALSE, stride, (GLvoid*)offset);
	offset += 2 * sizeof(float);

	
	glEnableVertexAttribArray(SHADER_BLEND1_ATTRIBUTE);
	glVertexAttribPointer(SHADER_BLEND1_ATTRIBUTE, 2, GL_FLOAT, GL_FALSE, stride, (GLvoid*)offset);
	offset += sizeof(vec2);

	
	glEnableVertexAttribArray(SHADER_BLEND2_ATTRIBUTE);
	glVertexAttribPointer(SHADER_BLEND2_ATTRIBUTE, 2, GL_FLOAT, GL_FALSE, stride, (GLvoid*)offset);
	offset += sizeof(vec2);

	
	glEnableVertexAttribArray(SHADER_BLEND3_ATTRIBUTE);
	glVertexAttribPointer(SHADER_BLEND3_ATTRIBUTE, 2, GL_FLOAT, GL_FALSE, stride, (GLvoid*)offset);
	offset += sizeof(vec2);

	
	glEnableVertexAttribArray(SHADER_BLEND4_ATTRIBUTE);
	glVertexAttribPointer(SHADER_BLEND4_ATTRIBUTE, 2, GL_FLOAT, GL_FALSE, stride, (GLvoid*)offset);

	NumIndices = m_Indices.size();
	Topology = GL_TRIANGLES;

}

void SkeMesh::Shutdown()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}
