#include "ResourceManager.h"

// Constructor that passes in the games renderer(for image resources).
ResourceManager::ResourceManager(SDL_Renderer * renderer)
{
	m_renderer = renderer;
	loadFromJson();
}

// Deconstructor
ResourceManager::~ResourceManager()
{
}

// Function to parse json data containing id's and paths to resources.
void ResourceManager::loadFromJson()
{
	// Load Image Assets
	std::ifstream imageFile("./ASSETS/ImageAssetList.json");
	json jImage = json::parse(imageFile);

	std::map<std::string, std::string> m_jsonImageFile = jImage;

	for (auto key : m_jsonImageFile) {
		addImageResource(new ImageResource, key.first, key.second.c_str());
	}

	// Load sound Assets
	std::ifstream soundFile("./ASSETS/SoundAssetList.json");
	json jSound = json::parse(soundFile);

	std::map<std::string, std::string> m_jsonSoundFile = jSound;

	for (auto key : m_jsonSoundFile) {
		addSoundResource(new SoundResource, key.first, key.second.c_str());
	}
}

// Function to create new image resource,
// Set its path, id and then load the image.
// Once loaded its added to the resource managers cache of images.
void ResourceManager::addImageResource(ImageResource * resource, const std::string & name, const char * path)
{
	resource->setResourcePath(path);
	resource->setResourceId(m_imageResources.size());
	resource->loadResource(m_renderer);

	m_imageResources.insert(std::pair<std::string, ImageResource*>(name, resource));
}

// Function to create new Sound resource,
// Set its path, id and then load the Sound.
// Once loaded its added to the resource managers cache of Sounds.
void ResourceManager::addSoundResource(SoundResource * resource, const std::string & name, const char * path)
{
	resource->setResourcePath(path);
	resource->setResourceId(m_soundResources.size());
	resource->loadResource();

	m_soundResources.insert(std::pair<std::string, SoundResource*>(name, resource));
}

// Bool to ensure All assets are loaded before game starts.
bool ResourceManager::checkLoaded()
{
	for (auto i : m_imageResources) {
		std::cout << "Loading: " << i.first << std::endl;
		if (nullptr == i.second->getTexture()) {
			return false;
		}
	}

	for (auto i : m_soundResources) {
		std::cout << "Loading: " << i.first << std::endl;
		if (nullptr == i.second->getSound()) {
			return false;
		}
	}

	return true;
}
