#pragma once
#include "pch.h"

class ActorFactory :public ISubSystem
{
	ActorId m_lastActorId;
	
protected:
	std::map<std::string, std::function<ActorComponent*()>> m_ComponentFactoryMap;
	std::map<std::string, std::function<Actor*(int id)>> m_ActorFactoryMap;
	std::map<string, std::function<Shader*(const char *, const char*)>> m_ShaderFactory;
	void EventCreateWeapon(std::shared_ptr<const IEvent> pEvents);
public:
	void Init(Context* c);
	void ShutDown();
	ActorFactory();
	~ActorFactory();
	// Create Actor from file
	bool RegisterComponentFactory(string name, std::function<ActorComponent*()>);

	Actor* CreateActor(const char* actorResource, tinyxml2::XMLElement* overrides, const mat4* initialTransform);

	Shader* CreateShader(const char* type, const char* vs, const char* fs);

	virtual ActorComponent* VCreateComponent(const tinyxml2::XMLElement* pData);

private:
	ActorId GetNextActorId(void) { ++m_lastActorId; return m_lastActorId; }
};

