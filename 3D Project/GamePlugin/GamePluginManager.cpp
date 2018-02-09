#include "pch.h"
#include "GamePluginManager.h"
#include "DLLInterface.h"
#include <Windows.h>


GamePluginManager::GamePluginManager(Context * pContext):m_ContextDLL(pContext)
{
}

bool GamePluginManager::LoadPlugin(const std::string & filename)
{
	HMODULE hModule = LoadLibrary(filename.c_str());
	if (!hModule) return 0;

	CreateInterfaceFn fnCreateInterface = (CreateInterfaceFn)GetProcAddress((HMODULE)hModule, CREATEINTERFACE_PROCNAME);

	IGamePlugin* pGamePlugin = fnCreateInterface();

	if (pGamePlugin)
	{
		pGamePlugin->Init(&m_ContextDLL);

		m_GamePlugins.push_back(pGamePlugin);
	}

	return 1;

}

void GamePluginManager::UpdateGame(float dt)
{
	for (auto& el : m_GamePlugins) el->Update(dt);
}

void GamePluginManager::RenderGame()
{
	for (auto& el : m_GamePlugins) el->Render();
}