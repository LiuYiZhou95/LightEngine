#pragma once
#include "..\Interface\IComponent.h"

namespace Light
{
	class MeshRenderComponent : public IMeshRenderComponent
	{
	protected:
		vector<IMesh*>			m_MeshList;
		Shader					*m_pShader;
		IModelResource*			m_Model;
		OpenGLRenderer			*m_pRenderer;
	public:
		static const char* Name;

		MeshRenderComponent(void);
		MeshRenderComponent(const vector<IMesh*>& v) { m_MeshList = v; }
		virtual ~MeshRenderComponent() {};

		virtual bool VInit(const tinyxml2::XMLElement* pData);
		virtual void VPostInit(void);
		virtual tinyxml2::XMLElement* VGenerateXml(tinyxml2::XMLDocument*p);
		virtual const char* VGetName() const { return Name; }

		// Question need to answer
		// Let this component render or just return m_MeshList for other sub-system
		// For easy now just render it
		// Request mesh and texture
		virtual void Render(Scene*);
		vector<IMesh*>& GetMeshList();
		vector<LTBSocket>& GetSockets();
		vector<std::unique_ptr<SkeNode>>& GetNodeList();
		Shader* GetShader() { return m_pShader; }
		void SetData(IModelResource* pModel);
	};

}
