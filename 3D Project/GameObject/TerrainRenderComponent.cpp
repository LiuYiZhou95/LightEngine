#include "pch.h"

const char* TerrainRenderComponent::Name = "TerrainRenderComponent";

bool TerrainRenderComponent::VInit(const tinyxml2::XMLElement* pData)
{
	m_fScale = 10.0f;
	if (!pData) return false;
	const tinyxml2::XMLElement* pModelPath = pData->FirstChildElement("Model");

	const char* pFileName = pModelPath->Attribute("File");
	if (pFileName)
	{
		HeightMap* hm = m_Context->GetSystem<Resources>()->GetHeightMap(pFileName);

		/*auto pMesh = new Mesh(hm->m_Vertexs, hm->m_Indices);
		const tinyxml2::XMLElement* pTexPath = pData->FirstChildElement("Texture");
		const char* pFileName1 = pTexPath->Attribute("File0");
		pMesh->Tex = m_Context->GetSystem<Resources>()->GetTexture(pFileName1);
		m_MeshList.push_back(pMesh);*/

		GenerateMeshData(hm);
	}

	const tinyxml2::XMLElement* pShader = pData->FirstChildElement("Shader");
	if (pShader)
	{
		m_pShader = m_Context->GetSystem<Resources>()->GetShader(pShader->Attribute("name"));
		if (m_pShader == nullptr)
			E_ERROR("Can not find shader name: " + string(pShader->Attribute("name")));
	}

	m_Material.Ks = vec3(0);
	m_Material.Ka = vec3(1.0f);
	m_Material.Kd = vec3(0.8f);
	return true;
}

void TerrainRenderComponent::Render(Scene *pScene)
{
	if (m_MeshList.empty()) return;
	m_pShader->SetupRender(pScene, m_pOwner);

	

	m_pShader->SetUniform("scale", m_fScale);

	m_pShader->SetUniform("gMaterial.Ka", m_Material.Ka);
	m_pShader->SetUniform("gMaterial.Kd", m_Material.Kd);
	m_pShader->SetUniform("gMaterial.Ks", m_Material.Ks);
	m_pShader->SetUniform("gMaterial.exp", m_Material.exp);

	for (size_t i = 0; i < m_MeshList.size(); i++)
	{
		m_MeshList[i]->Tex->Bind();

		// ------- Render mesh ----------
		//m_pRenderer->SetVertexArrayBuffer(m_MeshList[i]->VAO);
		m_MeshList[i]->VAO.Bind();
		m_pRenderer->SetDrawMode(m_MeshList[i]->Topology);
		m_pRenderer->DrawElement(m_MeshList[i]->NumIndices, GL_UNSIGNED_INT, 0);
	}
}

TerrainRenderComponent::~TerrainRenderComponent()
{
	
}

void TerrainRenderComponent::GenerateMeshData(HeightMap * hm)
{
	GLuint numMesh = hm->numSub;			// Num SubMesh device by row and collum
	GLuint numvert = hm->Width / numMesh;	// Num vertices per SubMesh in Row/Collum

	GLint xpos = 0, zpos = 0;
	int pos[2] = { xpos,zpos };

	std::vector<std::vector<DefaultVertex>> vertexList;
	for (int i = 0; i < numMesh; i++)
	{
		for (int j = 0; j < numMesh; j++)
		{
			std::vector<DefaultVertex> vertex;
			vertex = Light::Math::CopySubMatrix(hm->m_Vertexs, pos, numvert);
			vertexList.push_back(vertex);
		}
	}

}


/*
Mesh * TerrainRenderComponent::ReadFile(const string& filename)
{
	if (filename == nullptr) return nullptr;
	HeightMap* hm = m_Context->GetSystem<Resources>()->GetHeightMap(filename);
	/*GLint width, height, iType, iBpp;

	ilLoadImage(filename);

	ILenum Error;
	Error = ilGetError();

	if (Error != IL_NO_ERROR)
	{
		Log::Message(Log::LOG_ERROR, "Can't load terrain " + string(filename));
		return nullptr;
	}
	width = ilGetInteger(IL_IMAGE_WIDTH);
	height = ilGetInteger(IL_IMAGE_HEIGHT);
	iType = ilGetInteger(IL_IMAGE_FORMAT);
	ILubyte *Data = ilGetData();
	iBpp = ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL);

	float stepsize = 50; 
	GLint width = hm.Width, height = hm.Height;
	float stepsize = hm.stepsize;
	GLubyte* Data = hm.Data;
	vec2 size = vec2((width-1)*stepsize, (height-1)*stepsize);
	Mesh* p = new Mesh;

	int x = -size[0] / 2, y = 0, z = -size[1] / 2;
	float t = (hm.minH + hm.maxH) / 2.0f;
	// computer vertex xyz
	for (int i = 0; i < height; i++)
	{
		
		for (int j = 0; j < width; j++)
		{
			int b = i*width + j;
			
			y = Data[b]-t;
			vec3 pos(x, y, z);
			vec2 uv((x + size[0] / 2) / size[0], (z + size[1] / 2) / size[1]);
			vec3 normal(0, 1, 0);
			DefaultVertex vertex{ pos,normal,uv };
			p->m_Vertexs.push_back(vertex);
			x += stepsize;
		}
		x = -size[0] / 2;
		z += stepsize;
	}
	// computer indices
	GLuint cnt = 0;
	for (int i = 0; i < height - 1; i++)
		for (int j = 0; j <width - 1; j++)
		{
			p->m_Indices.push_back(j + (i + 1)*width + 1);
			p->m_Indices.push_back(j + i*width + 1);
			p->m_Indices.push_back(j + i*width);

			p->m_Indices.push_back(j + (i + 1)*width);
			p->m_Indices.push_back(j + (i + 1)*width + 1);
			p->m_Indices.push_back(j + i*width);
		}

	// computer normal
	
	auto heightF = [Data,width,height](int x,int z) {
		if (x < 0) x = 0;
		if (z < 0) z = 0;
		if (x >= width) x = width;
		if (z >= height) z = height;
		int a = (int)(x*width + z);
		return Data[a];
	};
	
	int id = 0;
	for (int i = 0; i < height ; i++)
		for (int j = 0; j < width ; j++)
		{
			vec2 P(i, j);
			float hL = heightF(j-1,i);
			float hR = heightF(j+1,i);
			float hD = heightF(j,i-1);
			float hU = heightF(j,i+1);
			vec3 N;
			N.x = hL - hR;
			N.y = hD - hU;
			N.z = 2.0;
			N = normalize(N);
			p->m_Vertexs[id].normal = N;
			id++;
		}

	return p;
}*/ 
