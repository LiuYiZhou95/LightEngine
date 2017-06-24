#pragma once
#include "..\pch.h"


class CoreApplication : public Singleton<CoreApplication>
{
public:

	virtual void onStartUp();
	virtual void onShutDown();

	
	bool MainLoop();
private:
	Windows* m_pWindow;
	bool m_bRunMainLoop;
	Actor *p2,*p3;
	Scene* m_pScene;
};