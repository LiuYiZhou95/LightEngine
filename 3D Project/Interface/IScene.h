#pragma once
#include <string>
#include "..\Graphics3D\ICamera.h"
#include "IActor.h"
#include "..\Utilities\Utility.h"
namespace Light
{
	class IScene
	{
	public:
		virtual ~IScene() = default;
		virtual bool				VOnRender() = 0;
		virtual bool				VLoad(const std::string& file) = 0;
		virtual bool				VOnUpdate(float dt) = 0;
		virtual bool				VPostUpdate() = 0;
		virtual IActor*				VGetRoot() = 0;
	};
}