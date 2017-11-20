#include "pch.h"
#include "OpenGLRenderer.h"

OpenGLRenderer::OpenGLRenderer():m_RenderName("OpenGL"),m_ClearColor(1.0f,1.0f,1.0f,1.0f),m_HasInit(0),m_iClearFlag(0),m_pWindows(nullptr),m_DrawMode(GL_TRIANGLES)
{
}

OpenGLRenderer::~OpenGLRenderer()
{
}

bool OpenGLRenderer::ReadConfig(string path)
{
	tinyxml2::XMLDocument doc;
	int errorID = doc.LoadFile(path.c_str());
	if (errorID)
	{
		E_ERROR("Failed to load file: " + path);
		return false;
	}
	tinyxml2::XMLElement* pRenderer = doc.FirstChildElement("Renderer");
	if (!pRenderer) return false;

	tinyxml2::XMLElement* pWindows = pRenderer->FirstChildElement("Windows");
	if (!pWindows) return false;

	m_WindowName = pWindows->Attribute("name");
	vec2 size;
	size.x = pWindows->DoubleAttribute("sizex", 800);
	size.y = pWindows->DoubleAttribute("sizey", 600);
	vec2 pos;
	pos.x = pWindows->DoubleAttribute("posx", 0);
	pos.y = pWindows->DoubleAttribute("posy", 0);

	m_pWindows = new Windows(m_WindowName, size.x, size.y);
	m_pWindows->InitWindow();
	m_pWindows->SetPos(pos);

	tinyxml2::XMLElement* pClearColor = pRenderer->FirstChildElement("ClearColor");

	m_ClearColor.x = pClearColor->DoubleAttribute("r", 0.3);
	m_ClearColor.y = pClearColor->DoubleAttribute("g", 0.3);
	m_ClearColor.z = pClearColor->DoubleAttribute("b", 0.3);
	m_ClearColor.w = pClearColor->DoubleAttribute("a", 1.0);

	m_Viewport = vec4(0, 0, size.x, size.y);

	return true;
}

bool OpenGLRenderer::Init()
{
	if (!ReadConfig("GameAssets\\" + string(RendererConfig)))
	{
		E_ERROR("Failed to init OpenGL Renderer");
	}

	// Initialize GLEW to setup the OpenGL Function pointers
	GLenum err = glewInit();
	if (err != GLEW_OK) 
	{
		string Error = string("glewInit failed: ");
		E_ERROR(Error);
		return false;
	}

	// Define the viewport dimensions
	glViewport(m_Viewport.x, m_Viewport.y, m_Viewport.z, m_Viewport.w);
	glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LESS);

	//glFrontFace(GL_CW);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	
	SetClearFlag(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_pWindows->ShowWindows();
	glfwSwapInterval(0);
	return true;
}

bool OpenGLRenderer::ShutDown()
{
	delete m_pWindows;
	return 1;
}

bool OpenGLRenderer::HasInit()
{
	return m_HasInit;
}

void OpenGLRenderer::ClearBuffer()
{
	glClear(m_iClearFlag);
}

void OpenGLRenderer::ClearColor()
{
	glClearColor(m_ClearColor.x, m_ClearColor.y, m_ClearColor.z, m_ClearColor.w);
}

void OpenGLRenderer::Clear()
{
	ClearBuffer();
	ClearColor();
}

void OpenGLRenderer::Draw(GLint first, GLsizei count, GLsizei primcount)
{
	if (primcount) glDrawArraysInstanced(m_DrawMode, first, count, primcount);
	else glDrawArrays(m_DrawMode, first, count);
}

void OpenGLRenderer::DrawElement(GLsizei count, GLenum type, const GLvoid * indices, GLsizei primcount)
{
	if (primcount) glDrawElementsInstanced(m_DrawMode, count, type, indices, primcount);
	else glDrawElements(m_DrawMode, count, type, indices);
}

void OpenGLRenderer::SetClearFlag(unsigned int flag)
{
	m_iClearFlag = flag;
}

void OpenGLRenderer::SetTexture(Texture * p, GLuint tex_unit)
{
	assert(p != nullptr);

	glActiveTexture(GL_TEXTURE0 + tex_unit);
	glBindTexture(GL_TEXTURE_2D, p->iIndex);

}

void OpenGLRenderer::SetViewport(int x, int y, int weight, int height)
{
	m_Viewport = vec4(x, y, weight, height);
	glViewport(x, y, weight, height);
}

void OpenGLRenderer::SetViewport(vec4 v)
{
	m_Viewport = v;
	glViewport(v.x, v.y, v.z, v.w);
}

void OpenGLRenderer::SetDrawMode(GLenum mode)
{
	m_DrawMode = mode;
}

void OpenGLRenderer::SetVertexArrayBuffer(GLuint vao)
{
	glBindVertexArray(vao);
}

vec4 OpenGLRenderer::GetViewport()
{
	return m_Viewport;
}

void OpenGLRenderer::SwapBuffer()
{
	glfwSwapBuffers(m_pWindows->Window());
	
}