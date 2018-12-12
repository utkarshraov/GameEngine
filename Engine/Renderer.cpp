#include "Renderer.h"
#include "LuaScript.h"
#include "Engine.h"

GLib::Sprites::Sprite * CreateSprite(const char * i_pFilename);

namespace Engine {

	Renderer * Renderer::instance = nullptr;

	Renderer * Renderer::Instance()
	{
		if (!instance)
		{
			instance = new Renderer();
		}
		return instance;
	}
	void Renderer::Init()
	{

	}
	void Renderer::createSprite(char * file, SmartPointer<GameObject> renderObject)
	{
		renderObject->setSprite(CreateSprite(file));
		renderObjects.push_back(renderObject);
	}

	void Renderer::Run()
	{
		bool bQuit = Engine::EngineManager::Instance()->playerDied;
		GLib::Service(bQuit);
		GLib::BeginRendering();
		GLib::Sprites::BeginRendering();
		for (auto render : renderObjects)
		{
			Vector2 x = render->getPosition();
			GLib::Point2D offset = { x.getX(),x.getY() };
			GLib::Sprites::RenderSprite(*render->getSprite(), offset, 0.0f);
		}
		GLib::Sprites::EndRendering();
		GLib::EndRendering();
	}

	void Renderer::Shutdown()
	{
		for (auto render : renderObjects)
		{
			GLib::Sprites::Release(render->getSprite());
		}
		GLib::Shutdown();
	}
}

GLib::Sprites::Sprite * CreateSprite(const char * i_pFilename)
{
	assert(i_pFilename);

	size_t sizeTextureFile = 0;

	// Load the source file (texture data)
	void * pTextureFile = LoadFile(i_pFilename, sizeTextureFile);

	// Ask GLib to create a texture out of the data (assuming it was loaded successfully)
	GLib::Texture * pTexture = pTextureFile ? GLib::CreateTexture(pTextureFile, sizeTextureFile) : nullptr;

	// exit if something didn't work
	// probably need some debug logging in here!!!!
	if (pTextureFile)
		delete[] pTextureFile;

	if (pTexture == nullptr)
		return NULL;

	unsigned int width = 0;
	unsigned int height = 0;
	unsigned int depth = 0;

	// Get the dimensions of the texture. We'll use this to determine how big it is on screen
	bool result = GLib::GetDimensions(pTexture, width, height, depth);
	assert(result == true);
	assert((width > 0) && (height > 0));

	// Define the sprite edges
	GLib::Sprites::SpriteEdges    Edges = { -float(width / 2.0f), float(height), float(width / 2.0f), 0.0f };
	GLib::Sprites::SpriteUVs    UVs = { { 0.0f, 0.0f },{ 1.0f, 0.0f },{ 0.0f, 1.0f },{ 1.0f, 1.0f } };
	GLib::RGBA                            Color = { 255, 255, 255, 255 };

	// Create the sprite
	GLib::Sprites::Sprite * pSprite = GLib::Sprites::CreateSprite(Edges, 0.1f, Color, UVs);
	if (pSprite == nullptr)
	{
		GLib::Release(pTexture);
		return nullptr;
	}

	// Bind the texture to sprite
	GLib::Sprites::SetTexture(*pSprite, *pTexture);

	return pSprite;
}