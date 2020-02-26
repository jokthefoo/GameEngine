#pragma once
#include "GLib.h"
#include "Containers/LinkedList.h"
#include "GameObjects/GameObject.h"

namespace Engine
{
	namespace Renderer
	{
		class ObjectRenderer
		{
		public:
			ObjectRenderer();
			ObjectRenderer(GameObject*, GLib::Sprites::Sprite*);
			GameObject* obj;
			GLib::Sprites::Sprite* sprite;
		};

		void RenderSprites();
		void * LoadFile(const char * i_pFilename, size_t & o_sizeFile);
		GLib::Sprites::Sprite * CreateSprite(const char * i_pFilename);
		void Shutdown();
		static LinkedList<ObjectRenderer> spriteList;
	}
}